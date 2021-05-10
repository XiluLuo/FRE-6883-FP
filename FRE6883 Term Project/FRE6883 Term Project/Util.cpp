//
//  Util.cpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/6/21.
//

#include "Util.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

double str2double(std::string numstr)
{
    numstr.erase(remove_if(numstr.begin(), numstr.end(),
        [](unsigned char c)
        {
            return c == ',' || c == '"' || c == '$' || c == ' ';
        }), numstr.end());
    
    return stod(numstr);
}

time_t str2time(std::string dateStr, const char *fmt, bool isMorning)
{
    struct tm d;
    strptime(dateStr.c_str(), fmt, &d);
    
    d.tm_hour = isMorning ? 9 : 16;
    d.tm_min = 0;
    d.tm_sec = 0;
    d.tm_isdst = 0;
    
    return mktime(&d);
}

bool isNumber(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(), s.end(),
        [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void printError(std::string msg)
{
    printError(msg.c_str());
}

void printError(const char *msg)
{
    std::cerr << "ERROR: " << msg << std::endl;
}

void printMenu()
{
    std::cout << "MENU" << std::endl;
    std::cout << "A) Enter N to retrieve 2N+1 days of historical price data for all stocks." << std::endl;
    std::cout << "B) Pull information for one stock from one group." << std::endl;
    std::cout << "C) Show AAR, AAR-STD, CAAR and CAAR-STD for one group." << std::endl;
    std::cout << "D) Show the Excel or gnuplot graph with CAAR for all 3 groups." << std::endl;
    std::cout << "X) Exit your program." << std::endl;
}

int getN()
{
    int N;
    std::string buffer;
    
    std::cout << "Enter N (30<=N<=60): ";
    std::cin >> buffer;
    
    if (!isNumber(buffer))
    {
        printError("N must be a positive integer.");
        return -1;
    }
    
    N = stoi(buffer);
    
    if (N < 30)
    {
        printError("N must be >= 30.");
        return -1;
    }
    
    if (N > 60)
    {
        printError("N must be <= 60.");
        return -1;
    }
    
    return N;
}

std::pair<std::string,std::string> getPeriod(std::string dayZero, unsigned int N)
{
    std::pair<std::string,std::string> period;
    
    const char *datefmt = "%Y-%m-%d";
    
    time_t t0 = str2time(dayZero, datefmt, false);
    time_t st = t0 - (N+1) * SECONDS_IN_ONE_DAY;
    time_t et = t0 + N * SECONDS_IN_ONE_DAY;
    
    struct tm sttm = *localtime(&st);
    struct tm ettm = *localtime(&et);
    
    // Starting date
    char buf_sdate[DATE_BUF_LEN];
    std::strftime(buf_sdate, DATE_BUF_LEN, datefmt, &sttm);
    period.first = std::string(buf_sdate);
    
    // Ending date
    char buf_edate[DATE_BUF_LEN];
    std::strftime(buf_edate, DATE_BUF_LEN, datefmt, &ettm);
    period.second = std::string(buf_edate);
    
    return period;
}

double tsDistance(const std::string &dt1, const std::string &dt2)
{
    const char *datefmt = "%Y-%m-%d";
    
    struct tm dt1tm;
    struct tm dt2tm;
    
    strptime(dt1.c_str(), datefmt, &dt1tm);
    strptime(dt2.c_str(), datefmt, &dt2tm);
    
    time_t dt1ts = mktime(&dt1tm);
    time_t dt2ts = mktime(&dt2tm);
    
    return abs(difftime(dt1ts, dt2ts));
}
