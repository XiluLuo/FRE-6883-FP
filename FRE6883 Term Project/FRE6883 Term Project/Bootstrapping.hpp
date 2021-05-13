//
//  Bootstrapping.hpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/8/21.
//

#ifndef Bootstrapping_hpp
#define Bootstrapping_hpp

#include "DataStructures/Matrix.hpp"
#include "Stock.hpp"
#include <unordered_set>
#include <map>
#include <vector>

// stockMtx is a m x (2N+1) Matrix storing the abnormal return
//  (difference of a stock's daily return and IWB daily return on the same date).
// Return a Vector with each element equal to the average value of its corresponding column.
Vector AAR(const Matrix &stockARMtx);

// Return the cumulative AAR on each day
Vector CAAR(const Vector &AARVec);

// Generate M indices ranging from 0 to size-1
std::unordered_set<long> genRandomIndex(unsigned int M, unsigned long size);

// Populate valid abnormal daily return of each stock in ZacksMap to its corresponding Matrix
void createAbMatrix(std::map<std::string,Stock> &ZacksMap, std::vector<Matrix> &stockAbMatrices);

// N: period margin
// M: number of rows in each matrix
// K: number of times to perform bootstrapping
// lowMtx: Matrix for stocks labeled StkBottom
// midMtx: Matrix for stocks labeled StkMiddle
// highMtx: Matrix for stocks labeled StkUpper
// AARAvgMap: key=StkGroup, value=AAR average Vector
// CAARAvgMap: key=StkGroup, value=CAAR average Vector
// AARStdMap: key=StkGroup, value=AAR stdev Vector
// CAARStdMap: key=StkGroup, value=CAAR stdev Vector
void bootstrappingPerform(unsigned int N, unsigned int M, unsigned int K, const std::vector<Matrix> &stockAbMatrices,
                          std::map<StockGroup,Vector> &AARAvgMap, std::map<StockGroup,Vector> &CAARAvgMap,
                          std::map<StockGroup,Vector> &AARStdMap, std::map<StockGroup,Vector> &CAARStdMap);

// Perform one time bootstrapping
void boostrap(unsigned int M, const std::vector<Matrix> &stockAbMatrices,
              std::map<StockGroup,Matrix> &AARMatrixMap, std::map<StockGroup,Matrix> &CAARMatrixMap);

#endif /* Bootstrapping_hpp */
