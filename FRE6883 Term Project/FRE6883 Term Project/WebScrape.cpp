//
//  WebScrape.cpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/8/21.
//

#include "WebScrape.hpp"
#include "json/json.h"
#include "Util.hpp"
#include "Matrix.hpp"
#include <sstream>
#include <thread>
#include <future>
#include <iostream>

const std::string WebScraper::API_TOKEN = "605f41c6a29c69.96773141";

// Writing call back function for storing fetched values in memory
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *) userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string WebScraper::BuildRequestURL(const std::string &symbol, const std::string &start_date, const std::string &end_date)
{
    std::ostringstream oss;
    oss << "https://eodhistoricaldata.com/api/eod/" << symbol << ".US?from="
        << start_date << "&to=" << end_date << "&api_token=" << API_TOKEN << "&period=d&fmt=json";
    
    return oss.str();
}

int WebScraper::ParseJson(const std::string &read_buffer, std::vector<TradeData> &TradeDataVec)
{
    Json::CharReaderBuilder builder;
    Json::CharReader *reader = builder.newCharReader();
    Json::Value root;
    std::string errors;

    bool parsingSuccessful = reader->parse(read_buffer.c_str(), read_buffer.c_str() + read_buffer.size(), &root, &errors);
    if (!parsingSuccessful) { return -1; }

    std::string date;
    double open;
    double high;
    double low;
    double close;
    double adjclose;
    long volume;

    for (Json::Value::const_iterator itr = root.begin(); itr != root.end(); itr++)
    {
        date = (*itr)["date"].asString();
        open = (*itr)["open"].asFloat();
        high = (*itr)["high"].asFloat();
        low = (*itr)["low"].asFloat();
        close = (*itr)["close"].asFloat();
        adjclose = (*itr)["adjusted_close"].asFloat();
        volume = (*itr)["volume"].asInt64();

        TradeData td(date, open, high, low, close, adjclose, volume);
        TradeDataVec.push_back(td);
    }

    return 0;
}

int WebScraper::PullMarketData(const std::string &url_request, std::string &read_buffer)
{
    CURL *handle;
    CURLcode result;
    
    handle = curl_easy_init();
    
    curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());
    curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &read_buffer);
    
    result = curl_easy_perform(handle);
    
    if (result != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        return -1;
    }
    
    curl_easy_cleanup(handle);
    
    return 0;
}

int WebScraper::PopulateStockDailyInfo(std::map<std::string,Stock> &ZacksMap, int N)
{
    std::string symbol = "IWB";
    std::string dayZero = "2020-10-15";
    std::pair<std::string,std::string> period = getPeriod(dayZero, 2 * N + 60);
    std::string url_request = BuildRequestURL(symbol, period.first, period.second);
    std::string read_buffer;
    std::vector<TradeData> TradeDataVec;
    
    if (PullMarketData(url_request, read_buffer)) { return -1; }
    if (ParseJson(read_buffer, TradeDataVec)) { return -1; }
    
    std::map<std::string,double> IWBMap;
    
    for (const TradeData &td : TradeDataVec)
    {
        IWBMap.insert({ td.date, td.adjclose });
    }
    
    for (std::pair<const std::string,Stock> &zm : ZacksMap)
    {
        Stock &stock = zm.second;
        PopulateDailyInfo(stock, N, IWBMap);
    }
    
    return 0;
}

void WebScraper::PopulateDailyInfo(Stock &stock, int N, std::map<std::string,double> &IWBMap)
{
    const std::string &symbol = stock.GetSymbol();
    std::pair<std::string,std::string> period = getPeriod(stock.GetEarningsAmntDate(), 2 * N);  // Calendar day vs. Business day
    
    std::string url_request = BuildRequestURL(symbol, period.first, period.second);
    std::string read_buffer;
    std::vector<TradeData> TradeDataVec;
    
    if (PullMarketData(url_request, read_buffer)) { return; }
    if (ParseJson(read_buffer, TradeDataVec)) { return; }
    
    int index = -1;
    double distance_min = std::numeric_limits<double>::max();
    
    for (auto i = 0; i < TradeDataVec.size(); i++)
    {
        const TradeData &td = TradeDataVec[i];
        // Note: If the announcement day is not business day, this can help
        double distance = tsDistance(td.date, stock.GetEarningsAmntDate());
        
        if (index == -1 || distance < distance_min)
        {   // Update
            index = i;
            distance_min = distance;
        }
    }
    
    // We need 2N+2 items for price => 2N+1 returns
    if (index - (N + 1) < 0 || index + N >= TradeDataVec.size())
    {
        // Not enough data available
        // Possible for stocks like MCFE, MSP, VNT when N=30
        std::cerr << "Symbol=" << symbol << std::endl;
        std::cerr << "TradeDataVec.size()=" << TradeDataVec.size() << std::endl;
        std::cerr << "index=" << index << ", N=" << N << std::endl;
        std::cerr << "index-(N+1)=" << (index-(N+1)) << ", index+N=" << (index+N) << std::endl;
        std::cerr << "Failed to populate daily trade info for " << stock.GetSymbol() << std::endl;
        
        return;
    }
    
    std::vector<std::string> dateVec;
    std::vector<double> stockPriceVec;
    std::vector<double> IWBPriceVec;
    
    for (int i = index - (N + 1); i <= index + N; i++)
    {
        const TradeData &td = TradeDataVec[i];
        
        double stockPrice = td.adjclose;
        double IWBPrice = IWBMap[td.date];
        
        dateVec.push_back(td.date);
        stockPriceVec.push_back(stockPrice);
        IWBPriceVec.push_back(IWBPrice);
    }
    
    Vector stockDailyPrices(stockPriceVec);
    Vector IWBDailyPrices(IWBPriceVec);
    
    stock.SetDates(dateVec);
    stock.SetDailyPrices(stockDailyPrices);
    stock.SetAbDailyRets(stock.GetDailyRets() - pct_change(IWBDailyPrices));
}
