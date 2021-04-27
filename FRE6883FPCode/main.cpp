#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Matrix.hpp"
#include "Util.hpp"
#include "YahooScrape.hpp"

using namespace std;

const char * zacks_filename = "./ZacksData.csv";

int main()
{
    string input;
    char selection = 0;

    int N = -1;  // Days to retrieve

    map<string,Stock> ZacksMap;
    if (RetrieveZacksData(zacks_filename, ZacksMap) == -1) return -1;

    // vector<string> BottomStocks;
    // vector<string> MiddleStocks;
    // vector<string> UpperStocks;

    // for (pair<const string,Stock> &p : ZacksMap)
    // {
    //     StockGroup group = p.second.GetGroup();
    //     if (group == StkBottom) BottomStocks.push_back(p.first);
    //     if (group == StkMiddle) MiddleStocks.push_back(p.first);
    //     if (group == StkUpper) UpperStocks.push_back(p.first);
    // }

    // for (pair<const string,Stock> &p : ZacksMap)
    // {
    //     cout << p.second << endl;
    // }

    // cout << "Bottom Stocks:" << endl;
    // for (string &bs : BottomStocks)
    // {
    //     cout << "Stock=" << bs << ",SurprisePct=" << ZacksMap[bs].GetSurprisePct() << endl;
    // }

    // cout << "Middle Stocks:" << endl;
    // for (string &ms : MiddleStocks)
    // {
    //     cout << "Stock=" << ms << ",SurprisePct=" << ZacksMap[ms].GetSurprisePct() << endl;
    // }

    // cout << "Upper Stocks:" << endl;
    // for (string &us : UpperStocks)
    // {
    //     cout << "Stock=" << us << ",SurprisePct=" << ZacksMap[us].GetSurprisePct() << endl;
    // }

    // // Delete the following
    // return 0;

    do
    {
        PrintMenu();
        cout << "Enter selection: ";
        cin >> input;

        if (input.length() > 1)
        {
            cout << "Invalid selection." << endl;
            continue;
        }

        // Convert the input to uppercase
        transform(input.begin(), input.end(), input.begin(), [](unsigned char c){ return toupper(c); });
        selection = input.c_str()[0];

        switch (selection)
        {
        case 'A':
        {
            N = GetN();
            if (N == -1) continue;

            map<string,vector<double>> DailyDataMap;
            if (PullDataFromYahoo(ZacksMap, N, DailyDataMap) != 0)
            {
                PrintError("PullDataFromYahoo failed...");
            }

            cout << "There are " << ZacksMap.size() << " stocks in Zacks" << endl;
            cout << "There are " << DailyDataMap.size() << " stocks in DailyData" << endl;

            break;
        }

        case 'B':
        {
            // TODO:
            // Pull information for one stock from one group:
            // - Daily Prices
            // - Cumulative Daily Returns
            // - The group the stock belongs to
            // - Earning Announcement Date, Period Ending, Estimated, Reported Earnings, Surprise and Surprise %.
            break;
        }

        case 'C':
        {
            // TODO:
            // Show AAR, AAR-SD, CAAR and CAAR-STD for one group.
            break;
        }

        case 'D':
        {
            // TODO:
            // Show the Excel or gnuplot graph with CAAR for all 3 groups.
            break;
        }

        default:
            break;
        }
    } while (selection != 'X');

    return 0;
}