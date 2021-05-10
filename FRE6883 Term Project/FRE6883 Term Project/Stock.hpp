//
//  Stock.hpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/6/21.
//

#ifndef Stock_hpp
#define Stock_hpp

#include "DataStructures/Matrix.hpp"
#include <string>
#include <ostream>
#include <map>

typedef struct TradeData_
{
    std::string date;
    double open;
    double high;
    double low;
    double close;
    double adjclose;
    long volume;
    
    TradeData_(std::string date_, double open_, double high_, double low_, double close_, double adjclose_, long volume_)
    {
        this->date = date_;
        this->high = high_;
        this->low = low_;
        this->close = close_;
        this->adjclose = adjclose_;
        this->volume = volume_;
    }
} TradeData;

enum StockGroup { StkBottom, StkMiddle, StkUpper };
const unsigned short STOCK_GROUP_NUM = 3;
const StockGroup SGTable[] = { StkBottom, StkMiddle, StkUpper };
extern std::map<StockGroup,std::string> StockGroupStrMap;

class Stock
{
private:
    std::string Symbol;
    std::vector<std::string> Dates;
    Vector DailyPrices;
    Vector DailyRets;
    Vector AbDailyRets;
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

    Stock(std::string Symbol_, std::vector<std::string> &Dates_, Vector &DailyPrices_, StockGroup Group_,
        std::string EarningsAmntDate_, std::string PeriodEnding_,
        double EstEarnings_, double RptEarnings_, double Surprise_, double SurprisePct_)
    {
        Symbol = Symbol_;
        Dates = Dates_;
        DailyPrices = DailyPrices_;
        DailyRets = pct_change(DailyPrices);
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
            Dates = other.Dates;
            DailyPrices = other.DailyPrices;
            DailyRets = other.DailyRets;
            AbDailyRets = other.AbDailyRets;
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
    
    const std::vector<std::string> & GetDates() const
    {
        return Dates;
    }

    const Vector & GetDailyPrices() const
    {
        return DailyPrices;
    }

    const Vector & GetDailyRets() const
    {
        return DailyRets;
    }
    
    const Vector & GetAbDailyRets() const
    {
        return AbDailyRets;
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
    void SetDates(const std::vector<std::string> &Dates_)
    {
        Dates = Dates_;
    }
    
    void SetDailyPrices(const Vector &DailyPrices_)
    {
        DailyPrices = DailyPrices_;
        DailyRets = pct_change(DailyPrices);
    }
    
    void SetAbDailyRets(const Vector &AbDailyRets_)
    {
        AbDailyRets = AbDailyRets_;
    }

    void SetGroup(StockGroup Group_)
    {
        Group = Group_;
    }

    // Display
    friend std::ostream & operator<<(std::ostream &out, Stock &stk);
};

bool ValidateStock(const Stock &s);

#endif /* Stock_hpp */
