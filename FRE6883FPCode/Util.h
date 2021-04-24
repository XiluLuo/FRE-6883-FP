#ifndef __6883_FP_UTIL_H_
#define __6883_FP_UTIL_H_

#include <iostream>
#include <string>
#include "Matrix.h"

Matrix PctChange(const Matrix &mtx);
bool IsNumber(const std::string s);
int GetN();
void PrintMenu();
void PrintError(std::string msg);

#endif