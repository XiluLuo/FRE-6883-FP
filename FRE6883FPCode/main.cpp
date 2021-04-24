#include <iostream>
#include <string>
#include <vector>
#include "Matrix.h"
#include "Util.h"

using namespace std;

int main()
{
    string input;
    char selection = 0;

    int N = -1;  // Days to retrieve

    // TODO:
    // Read from CSV file the available Russel 1000 stocks
    
    // vector<string> 

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