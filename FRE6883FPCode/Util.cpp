#include "Util.h"
#include <fstream>
#include <sstream>
#include <vector>

int RetrieveZacksData(const char * inputfile, std::map<std::string,Stock> &ZacksMap)
{
    std::ifstream fin(inputfile);

    if (!fin.is_open())
    {
        std::cerr << "ERROR: Unable to open " << inputfile << std::endl;
        return -1;
    }

    std::vector<std::string> stocks;

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
        double EstEarnings = stod(words[3]);
        double RptEarnings = stod(words[4]);
        double Surprise = stod(words[5]);
        double SurprisePct = stod(words[6]);

        Stock s(Symbol, EarningsAmntDate, PeriodEnding, EstEarnings, RptEarnings, Surprise, SurprisePct);
        stocks.push_back(Symbol);
        ZacksMap.insert({ Symbol, s });
    }

    int tot_stocks = ZacksMap.size();
    int num_stocks_per_group = tot_stocks / 3;
    if (tot_stocks % 3 != 0) num_stocks_per_group++;

    for (int i = 0; i < stocks.size(); i++)
    {
        std::string Symbol = stocks[i];

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
    std::cout << "R) Enter N to retrieve 2N+1 days of historical price data for all stocks." << std::endl;
    std::cout << "F) Pull information for one stock from one group." << std::endl;
    std::cout << "S) Show AAR, AAR-SD, CAAR and CAAR-STD for one group." << std::endl;
    std::cout << "P) Show the Excel or gnuplot graph with CAAR for all 3 groups." << std::endl;
    std::cout << "X) Exit your program." << std::endl;
}

void PrintError(std::string msg)
{
    std::cerr << "ERROR: " << msg << std::endl;
}