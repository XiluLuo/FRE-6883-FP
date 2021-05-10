//
//  WebScrape.hpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/8/21.
//

#ifndef WebScrape_hpp
#define WebScrape_hpp

#include "Stock.hpp"
#include <curl/curl.h>
#include <string>
#include <map>

class WebScraper
{
private:
    static const std::string API_TOKEN;

public:
    // Default constructor
    WebScraper()
    {
        curl_global_init(CURL_GLOBAL_ALL);
    }
    
    // Default destructor
    ~WebScraper()
    {
        curl_global_cleanup();
    }
    
    // Static Functions
    
    // Build a request URL to EOD
    static std::string BuildRequestURL(const std::string &symbol, const std::string &start_date, const std::string &end_date);
    
    // Parse Json result into TradeData and store objects into vector container
    static int ParseJson(const std::string &read_buffer, std::vector<TradeData> &TradeDataVec);
    
    // Non-static Functions
    
    // Send GET request to EOD and store results into read_buffer
    // Return 0 upon success; otherwise, -1
    int PullMarketData(const std::string &url_request, std::string &read_buffer);
    
    // Populdate stock daily trades info into ZacksMap with margin width N
    int PopulateStockDailyInfo(std::map<std::string,Stock> &ZacksMap, int N);
    
    // Populate daily trades info for stock with margin width N (thread function)
    void PopulateDailyInfo(Stock &stock, int N, std::map<std::string,double> &IWBMap);
};

#endif /* WebScrape_hpp */
