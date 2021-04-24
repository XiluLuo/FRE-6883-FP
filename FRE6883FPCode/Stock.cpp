#include "Stock.h"

std::ostream & operator<<(std::ostream &out, Stock &stk)
{
    out << "Stock: " << stk.Symbol << std::endl;
    out << "  Daily Prices              = " << stk.DailyPrices << std::endl;
    out << "  Cumulative Daily Returns  = " << stk.CumDailyRets << std::endl;
    out << "  Group                     = " << stk.Group << std::endl;
    out << "  Earning Announcement Date = " << stk.EarningsAmntDate << std::endl;
    out << "  Period Ending             = " << stk.PeriodEnding << std::endl;
    out << "  Estimated Earnings        = " << stk.EstEarnings << std::endl;
    out << "  Reported Earnings         = " << stk.RptEarnings << std::endl;
    out << "  Surprise                  = " << stk.Surprise << std::endl;
    out << "  Surprise %                = " << stk.SurprisePct << std::endl;

    return out;
}