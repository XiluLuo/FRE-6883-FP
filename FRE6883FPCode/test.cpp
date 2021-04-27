#include <iostream>
#include <string>
#include <vector>
#include "Matrix.hpp"
#include "Stock.hpp"

using namespace std;

int main()
{
    string Symbol = "APL";
    vector<double> vtr = { 12.0, 230, 45.0 };

    Vector DailyPrices(vtr);
    // Vector DailyPrices(3);
    // DailyPrices[0] = 12.;
    // DailyPrices[1] = 23.;
    // DailyPrices[2] = 45.;
    cout << "vtr.size = " << vtr.size() << endl;

    StockGroup Group = StkMiddle;

    string EarningsAmntDate = "2012-04-23";
    string PeriodEnding = "SEP-2012";

    double EstEarnings = 12.0;
    double RptEarnings = 13.0;

    double Surprise = RptEarnings - EstEarnings;
    double SurprisePct = (RptEarnings - EstEarnings) / EstEarnings;

    Stock stock(Symbol, DailyPrices, Group, EarningsAmntDate, PeriodEnding, EstEarnings, RptEarnings, Surprise, SurprisePct);

    cout << stock << endl;

    return 0;
}