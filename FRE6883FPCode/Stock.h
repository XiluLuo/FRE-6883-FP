#ifndef __6883_FP_STOCK_H_
#define __6883_FP_STOCK_H_

#include "Matrix.h"
#include <string>
#include <ostream>

enum StockGroup { StkUpper, StkMiddle, StkBottom };

class Stock
{
private:
    std::string Symbol;
    Vector DailyPrices;
    Vector CumDailyRets;
    StockGroup Group;
    std::string EarningsAmntDate;
    std::string PeriodEnding;
    double EstEarnings;
    double RptEarnings;
    double Surprise;
    double SurprisePct;

public:
    // Constructor
    Stock() {}

    Stock(std::string Symbol_, std::string EarningsAmntDate_, std::string PeriodEnding_,
        double EstEarnings_, double RptEarnings_, double Surprise_, double SurprisePct_)
    {
        Symbol = Symbol_;
        EarningsAmntDate = EarningsAmntDate_;
        PeriodEnding = PeriodEnding_;
        EstEarnings = EstEarnings_;
        RptEarnings = RptEarnings_;
        Surprise = Surprise_;
        SurprisePct = SurprisePct_;
    }

    Stock(std::string Symbol_, Vector &DailyPrices_, StockGroup Group_,
        std::string EarningsAmntDate_, std::string PeriodEnding_,
        double EstEarnings_, double RptEarnings_, double Surprise_, double SurprisePct_)
    {
        Symbol = Symbol_;
        DailyPrices = DailyPrices_;
        CumDailyRets = CumReturn(DailyPrices);
        Group = Group_;
        EarningsAmntDate = EarningsAmntDate_;
        PeriodEnding = PeriodEnding_;
        EstEarnings = EstEarnings_;
        RptEarnings = RptEarnings_;
        Surprise = Surprise_;
        SurprisePct = SurprisePct_;
    }

    // Copy constructor
    Stock(const Stock &other)
    {
        *this = other;
    }

    // Override assignment operator
    Stock & operator=(const Stock &other)
    {
        if (this != &other)
        {
            Symbol = other.Symbol;
            DailyPrices = other.DailyPrices;
            CumDailyRets = other.CumDailyRets;
            Group = other.Group;
            EarningsAmntDate = other.EarningsAmntDate;
            PeriodEnding = other.PeriodEnding;
            EstEarnings = other.EstEarnings;
            RptEarnings = other.RptEarnings;
            Surprise = other.Surprise;
            SurprisePct = other.SurprisePct;
        }
        return *this;
    }

    // Getter
    std::string GetSymbol() const
    {
        return Symbol;
    }

    const Vector & GetDailyPrices() const
    {
        return DailyPrices;
    }

    const Vector & GetCumDailyRets() const
    {
        return CumDailyRets;
    }

    StockGroup GetGroup() const
    {
        return Group;
    }

    std::string GetEarningsAmntDate() const
    {
        return EarningsAmntDate;
    }

    std::string GetPeriodEnding() const
    {
        return PeriodEnding;
    }

    double GetEstEarnings() const
    {
        return EstEarnings;
    }

    double GetRptEarnings() const
    {
        return RptEarnings;
    }

    double GetSurprise() const
    {
        return Surprise;
    }

    double GetSurprisePct() const
    {
        return SurprisePct;
    }

    // Setter
    void SetDailyPrices(Vector &DailyPrices_)
    {
        DailyPrices = DailyPrices_;
        CumDailyRets = CumReturn(DailyPrices);
    }

    void SetGroup(StockGroup Group_)
    {
        Group = Group_;
    }

    // Display
    friend std::ostream & operator<<(std::ostream &out, Stock &stk);
};

#endif