#include <iostream>
#include <string>
#include "Matrix.h"
#include "Stock.h"

using namespace std;

int main()
{

    string Symbol = "APL";

    Vector DailyPrices(3);
    DailyPrices[0] = 12.;
    DailyPrices[1] = 23.;
    DailyPrices[2] = 45.;

    Vector CumDailyRets(2);
    CumDailyRets[0] = (DailyPrices[1] - DailyPrices[0]) / DailyPrices[0];
    CumDailyRets[1] = (DailyPrices[2] - DailyPrices[1]) / DailyPrices[1];

    StockGroup Group = StkMiddle;

    string EarningsAmntDate = "2012-04-23";
    string PeriodEnding = "SEP-2012";

    double EstEarnings = 12.0;
    double RptEarnings = 13.0;

    double Surprise = RptEarnings - EstEarnings;
    double SurprisePct = (RptEarnings - EstEarnings) / EstEarnings;
    
    Stock stock(Symbol, DailyPrices, CumDailyRets, Group, EarningsAmntDate, PeriodEnding, EstEarnings, RptEarnings, Surprise, SurprisePct);

    cout << stock << endl;

    return 0;
}