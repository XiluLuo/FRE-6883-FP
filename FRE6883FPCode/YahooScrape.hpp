#ifndef __6883_FP_YAHOOSCRAPE_H_
#define __6883_FP_YAHOOSCRAPE_H_

#include "Stock.hpp"
#include <string>
#include <map>
#include <vector>
#include <cstdlib>

const int SecondsInDay = 24 * 60 * 60;

struct MemoryStruct {
    char *memory;
    size_t size;
};

int write_data(void *ptr, size_t size, size_t nmemb, void *data);
int PullDataFromYahoo(const std::map<std::string,Stock> &ZacksMap, int N, std::map<std::string,std::vector<double>> &DailyDataMap);

#endif
