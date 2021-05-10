//
//  ZacksData.hpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/6/21.
//

#ifndef ZacksData_hpp
#define ZacksData_hpp

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <cmath>
#include "Stock.hpp"
#include "Util.hpp"

class ZacksDataRetriever
{
private:
    std::string inputfile;
    bool parsingSuccessful;
    std::map<std::string,Stock> ZacksMap;
    
    // Reset everything
    void cleanup();
    
public:
    // Default constructor
    ZacksDataRetriever()
    {
        cleanup();
    }
    
    // Getter
    std::string GetInputFilePath() const
    {
        return inputfile;
    }
    
    // Check if the parsing is successful
    bool ready()
    {
        return parsingSuccessful;
    }
    
    // Store the path to input file
    // Read from the file and store it as a map
    // Parsing status can be obtained by calling function ready()
    void build(const char *fname);
    
    std::map<std::string,Stock> retrieve()
    {
        return ZacksMap;
    }
};

#endif /* ZacksData_hpp */
