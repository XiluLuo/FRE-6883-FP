//
//  Util.hpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/6/21.
//

#ifndef Util_hpp
#define Util_hpp

#include <string>
#include <map>
#include <vector>

#define DATE_BUF_LEN 16

const int SECONDS_IN_ONE_DAY = 24 * 60 * 60;

// Convert a string to string that may contain (,), ("), ($), (space) to double
double str2double(std::string numstr);

// Convert a string representing a date into a timestamp
// If isMorning=true, then the hour is set to 9 (when market opens);
//  else it is set to 16 (when market closes).
time_t str2time(std::string dateStr, const char *fmt, bool isMorning = true);

// Return true if string s is made of digits;
//  otherwise, return false
bool isNumber(const std::string &s);

// Output error message
void printError(std::string msg);

// Output error message
void printError(const char *msg);

// Print menu to console
void printMenu();

// Get a positive integer from user
// N must be >= 30 && <= 60
// If user input is invalid, return -1
int getN();

// Take a date as day zero, find the period starting from N days before day zero
//  and ending in N days after day zero.
// Return a pair of string representation of dates, the first being the start date
//  and the second one being the end date.
// There are 2N+1 days within the period.
std::pair<std::string,std::string> getPeriod(std::string dayZero, unsigned int N);

// Return the distance between two dates
double tsDistance(const std::string &dt1, const std::string &dt2);

#endif /* Util_hpp */
