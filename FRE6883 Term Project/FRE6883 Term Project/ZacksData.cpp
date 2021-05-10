//
//  ZacksData.cpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/6/21.
//

#include "ZacksData.hpp"

void ZacksDataRetriever::cleanup()
{
    this->inputfile.clear();
    this->parsingSuccessful = false;
    this->ZacksMap.clear();
}

void ZacksDataRetriever::build(const char *fname)
{
    cleanup();
    
    this->inputfile = std::string(fname);
    std::ifstream fin(inputfile);
    
    if (!fin.is_open())
    {
        // Failed to open the file
        parsingSuccessful = false;
        return;
    }
    
    parsingSuccessful = true;
    
    std::vector<std::pair<std::string,double>> stocks;
    
    std::string line;
    std::getline(fin, line);  // Skip the header
    
    while (std::getline(fin, line))
    {
        std::istringstream iss(line);
        std::string word;
        std::vector<std::string> words;
        
        while (getline(iss, word, ','))
        {
            // Remove whitespace
            word.erase(std::remove_if(word.begin(), word.end(), ::isspace), word.end());
            words.push_back(word);
        }
        
        std::string Symbol = words[0];
        std::string EarningsAmntDate = words[1];
        std::string PeriodEnding = words[2];
        double EstEarnings = str2double(words[3]);
        double RptEarnings = str2double(words[4]);
        double Surprise = str2double(words[5]);
        double SurprisePct = str2double(words[6]);
        
        // Change the format of the date
        struct tm EADateTM;
        char date_buf[DATE_BUF_LEN];
        strptime(EarningsAmntDate.c_str(), "%d-%b-%y", &EADateTM);
        strftime(date_buf, DATE_BUF_LEN, "%Y-%m-%d", &EADateTM);
        EarningsAmntDate = std::string(date_buf);
        
        Stock stock(Symbol, EarningsAmntDate, PeriodEnding, EstEarnings, RptEarnings, Surprise, SurprisePct);
        
        if (ValidateStock(stock))
        {
            ZacksMap.insert({ Symbol, stock });
            stocks.push_back(std::pair<std::string,double>(Symbol, SurprisePct));
        }
    }
    
    unsigned long num_stocks = ZacksMap.size();
    unsigned int num_stocks_per_group = (unsigned int) std::round(static_cast<double>(num_stocks) / STOCK_GROUP_NUM);

    // Sort the stocks based on their SurprisePct from lowest to highest
    sort(stocks.begin(), stocks.end(),
         [](const std::pair<std::string,double> &a,
            const std::pair<std::string,double> &b)
         { return a.second < b.second; }
    );
    
    // Assign a label to each stock
    int index = 0;
    for (unsigned short i = 0; i < STOCK_GROUP_NUM; i++)
    {
        StockGroup label = SGTable[i];
        
        for (int k = 0; k < num_stocks_per_group && index < stocks.size(); k++)
        {
            const std::string &Symbol = stocks[index].first;
            ZacksMap[Symbol].SetGroup(label);
            index++;
        }
    }
}

