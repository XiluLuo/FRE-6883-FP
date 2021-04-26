#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Matrix.h"
#include "Util.h"

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
    //     cout << bs << endl;
    // }

    // cout << "Middle Stocks:" << endl;
    // for (string &ms : BottomStocks)
    // {
    //     cout << ms << endl;
    // }

    // cout << "Upper Stocks:" << endl;
    // for (string &us : BottomStocks)
    // {
    //     cout << us << endl;
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

        selection = input.c_str()[0];

        switch (selection)
        {
        case 'R':
        case 'r':
        {
            N = GetN();
            if (N == -1) continue;

            break;
        }

        case 'F':
        case 'f':
        {
            // TODO:
            // Pull information for one stock from one group:
            // - Daily Prices
            // - Cumulative Daily Returns
            // - The group the stock belongs to
            // - Earning Announcement Date, Period Ending, Estimated, Reported Earnings, Surprise and Surprise %.
            break;
        }

        case 'S':
        case 's':
        {
            // TODO:
            // Show AAR, AAR-SD, CAAR and CAAR-STD for one group.
            break;
        }

        case 'P':
        case 'p':
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