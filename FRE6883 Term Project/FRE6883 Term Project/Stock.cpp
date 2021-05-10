//
//  Stock.cpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/6/21.
//

#include "Stock.hpp"
#include "Util.hpp"
#include <cmath>
#include <iomanip>

std::map<StockGroup,std::string> StockGroupStrMap = {
   { StkBottom, "Miss Estimate Group" },
   { StkMiddle, "Meet Estimate Group" },
   { StkUpper, "Beat Estimate Group" }
};

std::ostream & operator<<(std::ostream &out, Stock &stk)
{
    out << "Stock: " << stk.Symbol << std::endl;
    out << "  Group                     = " << StockGroupStrMap[stk.Group] << std::endl;
    out << "  Earning Announcement Date = " << stk.EarningsAmntDate << std::endl;
    out << "  Period Ending             = " << stk.PeriodEnding << std::endl;
    out << "  Estimated Earnings        = " << stk.EstEarnings << std::endl;
    out << "  Reported Earnings         = " << stk.RptEarnings << std::endl;
    out << "  Surprise                  = " << stk.Surprise << std::endl;
    out << "  Surprise %                = " << stk.SurprisePct << std::endl;
    
    const std::vector<std::string> &Dates = stk.GetDates();
    const Vector &DailyPrices = stk.GetDailyPrices();
    const Vector &DailyRets = stk.GetDailyRets();
    const Vector &AbDailyRets = stk.GetAbDailyRets();
    
    for (int i = 0; i < DailyRets.len(); i++)
    {
        out << std::setiosflags(std::ios::fixed);
        out << "[" << Dates[i+1] << "] Price=" << std::setprecision(2) << DailyPrices[i+1] << std::setprecision(10)
            << ", Return=" << (DailyRets[i] < 0 ? "" : " ") << DailyRets[i]
            << ", Abnormal Return=" << (AbDailyRets[i] < 0 ? "" : " ") << AbDailyRets[i] << std::endl;
    }
    
    return out;
}

bool ValidateStock(const Stock &s)
{
    // Originally "%d-%b-%y"
    return abs(s.GetSurprisePct()) < 1000 &&                         // Validate SurprisePct
        str2time(s.GetEarningsAmntDate(), "%Y-%m-%d", false) != -1;  // Valid EarningsAmntDate
}
