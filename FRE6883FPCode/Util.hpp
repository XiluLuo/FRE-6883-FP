#ifndef __6883_FP_UTIL_H_
#define __6883_FP_UTIL_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Stock.hpp"

double str2double(std::string numstr);
int RetrieveZacksData(const char * inputfile, std::map<std::string,Stock> &ZacksMap);
bool IsNumber(const std::string s);
int GetN();
void PrintMenu();
void PrintError(std::string msg);
void PrintError(const char *msg);

#endif