#include "Util.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>

double str2double(std::string numstr)
{
    numstr.erase(remove_if(numstr.begin(), numstr.end(), [](unsigned char c)
        {
            return c == ',' || c == '"' || c == '$' || c == ' ';
        }), numstr.end());
    return stod(numstr);
}

int RetrieveZacksData(const char * inputfile, std::map<std::string,Stock> &ZacksMap)
{
    std::ifstream fin(inputfile);

    if (!fin.is_open())
    {
        std::cerr << "ERROR: Unable to open " << inputfile << std::endl;
        return -1;
    }

    std::vector<std::pair<std::string,double>> stocks;

    std::string line;
    std::getline(fin, line);  // Skip the header
    while (std::getline(fin, line))
    {
        std::istringstream iss(line);
        std::string word;
        std::vector<std::string> words;

        while (getline(iss, word, ','))
            words.push_back(word);

        std::string Symbol = words[0];
        std::string EarningsAmntDate = words[1];
        std::string PeriodEnding = words[2];
        double EstEarnings = str2double(words[3]);
        double RptEarnings = str2double(words[4]);
        double Surprise = str2double(words[5]);
        double SurprisePct = str2double(words[6]);

        Stock s(Symbol, EarningsAmntDate, PeriodEnding, EstEarnings, RptEarnings, Surprise, SurprisePct);

        if (ValidateStock(s))
        {
            ZacksMap.insert({ Symbol, s });
            stocks.push_back(std::pair<std::string,double>(Symbol, SurprisePct));
        }
    }

    int tot_stocks = ZacksMap.size();
    int num_stocks_per_group = tot_stocks / 3;
    if (tot_stocks % 3 != 0) num_stocks_per_group++;

    sort(stocks.begin(), stocks.end(),
        [](const std::pair<std::string,double> &a,
            const std::pair<std::string,double> &b)
        { return a.second < b.second; });

    for (int i = 0; i < stocks.size(); i++)
    {
        std::string Symbol = stocks[i].first;

        StockGroup Group = StkBottom;
        if (i >= num_stocks_per_group)
            Group = (i >= 2 * num_stocks_per_group) ? StkUpper : StkMiddle;

        ZacksMap[Symbol].SetGroup(Group);
    }

    return 0;
}

bool IsNumber(const std::string s)
{
    for (int i = 0; i < s.size(); i++)
        if (!isdigit(s[i]))
            return false;
    return true;
}

int GetN()
{
    std::string buffer;
    int N;

    std::cout << "Please enter N (N>=30): ";
    std::cin >> buffer;

    if (!IsNumber(buffer))
    {
        PrintError("N must be a positive integer.");
        return -1;
    }

    N = stoi(buffer);

    if (N < 30)
    {
        PrintError("N must be >= 30.");
        return -1;
    }

    return N;
}

void PrintMenu()
{
    std::cout << "MENU" << std::endl;
    std::cout << "A) Enter N to retrieve 2N+1 days of historical price data for all stocks." << std::endl;
    std::cout << "B) Pull information for one stock from one group." << std::endl;
    std::cout << "C) Show AAR, AAR-SD, CAAR and CAAR-STD for one group." << std::endl;
    std::cout << "D) Show the Excel or gnuplot graph with CAAR for all 3 groups." << std::endl;
    std::cout << "X) Exit your program." << std::endl;
}

void PrintError(std::string msg)
{
    PrintError(msg.c_str());
}

void PrintError(const char *msg)
{
    std::cerr << "ERROR: " << msg << std::endl;
}