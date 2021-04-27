#include "YahooScrape.hpp"
#include "Util.hpp"
#include "Stock.hpp"
#include <cstdlib>
#include <ctime>
#include <utility>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <map>
#include <curl/curl.h>

void* myrealloc(void* ptr, size_t size)
{
    return ptr ? realloc(ptr, size) : malloc(size);
}

int write_data(void *ptr, size_t size, size_t nmemb, void *data)
{
    size_t realsize = size *nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)data;

    mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory)
    {
        memcpy(&(mem->memory[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;
    }

    return (int)realsize;
}

time_t str2time(std::string datestr)
{
    struct tm d;
    strptime(datestr.c_str(), "%d-%b-%y", &d);
    d.tm_hour = 16;
    d.tm_min = 0;
    d.tm_sec = 0;
    d.tm_isdst = 0;
    return mktime(&d);
}

std::pair<std::string,std::string> GetTimeRange(std::string a_date, int N)
{
    std::pair<std::string,std::string> dates;

    time_t a_time = str2time(a_date);

    if (a_time == -1)
    {
        PrintError("GetTimeRange failed.");
        return dates;
    }

    time_t start_time = a_time - N * SecondsInDay;
    time_t end_time = a_time + N * SecondsInDay;

    std::stringstream ss;
    ss << start_time;
    dates.first = ss.str();
    ss.str("");  // clear
    ss << end_time;
    dates.second = ss.str();

    return dates;
}

// Return crumb value and write cookies to file
const char * GetCrumb(std::string Symbol, std::string cookiefname, std::string crumbfname)
{
    system("exec rm -rf ./*.txt");

    curl_global_init(CURL_GLOBAL_ALL);
    CURL *handle = curl_easy_init();
    FILE *crumbfile;
    char cookiebuffer[512];
    const char *crumb = "";

    std::string cookie_url = std::string("https://finance.yahoo.com/quote/") + Symbol + std::string("/history?p=") + Symbol;

    curl_easy_setopt(handle, CURLOPT_URL, cookie_url.c_str());
    curl_easy_setopt(handle, CURLOPT_COOKIEFILE, cookiefname.c_str());
    curl_easy_setopt(handle, CURLOPT_COOKIELIST, "ALL");
    curl_easy_setopt(handle, CURLOPT_COOKIESESSION, true);
    curl_easy_setopt(handle, CURLOPT_COOKIEJAR, cookiefname.c_str());
    curl_easy_setopt(handle, CURLOPT_COOKIELIST, cookiebuffer);
    curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(handle, CURLOPT_HEADER, 0);

    crumbfile = fopen(crumbfname.c_str(), "wb");
    if (crumbfile)
    {
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, crumbfile);
        curl_easy_perform(handle);
        fclose(crumbfile);
    }
    else
    {
        perror("INFO");
        PrintError(std::string("Unable to open ") + crumbfname + ".");
    }

    curl_easy_cleanup(handle);
    curl_global_cleanup();

    std::ifstream fin(crumbfname);
    std::string line;
    while (getline(fin, line))
    {
        size_t pos = line.find("CrumbStore\":{\"crumb\":\"");
        if (pos != std::string::npos)
        {
            crumb = line.substr(pos + 22, 11).c_str();
            break;
        }
    }

    fin.close();

    return crumb;
}

int PullDataFromYahoo(const std::map<std::string,Stock> &ZacksMap, int N, std::map<std::string,std::vector<double>> &DailyDataMap)
{
    CURL * handle;
    CURLcode status;

    curl_global_init(CURL_GLOBAL_ALL);
    handle = curl_easy_init();

    if (!handle)
    {
        PrintError("CURL init failed.");
        return -1;
    }

    for (const std::pair<const std::string,Stock> &zmp : ZacksMap)
    {
        const std::string &stk = zmp.first;

        struct MemoryStruct data;
        std::vector<double> stock_prices;

        std::string announcement_date = zmp.second.GetEarningsAmntDate();
        std::pair<std::string,std::string> p = GetTimeRange(announcement_date, N);
        std::string start_time = p.first;
        std::string end_time = p.second;

        std::string request_url = std::string("https://query1.finance.yahoo.com/v7/finance/download/") + stk + std::string("?period1=") + start_time + std::string("&period2=") + end_time + std::string("&interval=1d&events=history");

        std::cout << "URL1=" << request_url << std::endl;

        data.memory = NULL;
        data.size = 0;

        curl_easy_setopt(handle, CURLOPT_URL, request_url.c_str());
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);
        status = curl_easy_perform(handle);

        std::cout << data.memory << std::endl;

        if (status != CURLE_OK || std::string(data.memory).find("Unauthorized") != std::string::npos)
        {
            if (data.memory != NULL)
            {
                free(data.memory);
                data.memory = NULL;
                data.size = 0;
            }

            // Add crumb and cookie and try again
            std::string cookiefname = std::string("./cookie_") + stk.c_str() + ".txt";
            std::string crumbfname = std::string("./crumb_") + stk.c_str() + ".txt";

            const char *crumb = GetCrumb(stk, cookiefname, crumbfname);
            request_url += std::string("&crumb=") + std::string(crumb);

            std::cout << "URL2=" << request_url << std::endl;

            curl_easy_setopt(handle, CURLOPT_URL, request_url.c_str());
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);
            status = curl_easy_perform(handle);

            if (status != CURLE_OK || std::string(data.memory).find("Unauthorized") != std::string::npos)
            {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(status));
                std::cout << data.memory << std::endl;
                curl_easy_cleanup(handle);
                curl_global_cleanup();
                return -1;
            }
        }

        /* Add Stock Price: Start */
        std::cout << "Stock=" << stk << std::endl;
        std::stringstream sData;
        sData.str(data.memory);
        std::string sValue, sDate;
        double dValue = 0;
        std::string line;
        getline(sData, line);
        while (getline(sData, line)) {
            sDate = line.substr(0, line.find_first_of(','));
            line.erase(line.find_last_of(','));
            sValue = line.substr(line.find_last_of(',') + 1);
            dValue = strtod(sValue.c_str(), NULL);
            stock_prices.push_back(dValue);
        }
        std::cout << std::endl;

        DailyDataMap[stk] = stock_prices;

        free(data.memory);
        data.memory = NULL;
        data.size = 0;
        /* Add Stock Price: End */
    }

    curl_easy_cleanup(handle);
    curl_global_cleanup();

    return 0;
}
