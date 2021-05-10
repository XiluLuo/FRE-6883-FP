//
//  Bootstrapping.cpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/8/21.
//

#include "Bootstrapping.hpp"
#include <utility>

#include <iostream>

Vector AAR(const Matrix &stockARMtx)
{
    return mean(stockARMtx, 0);
}

Vector CAAR(const Vector &AARVec)
{
    double tot = 0.;
    Vector v(AARVec.len());
    
    for (unsigned long i = 0; i < AARVec.len(); i++)
    {
        tot += AARVec[i];
        v[i] = tot;
    }
    
    return v;
}

std::unordered_set<long> genRandomIndex(unsigned int M, unsigned long size)
{
    std::unordered_set<long> indices;
    
    while (indices.size() < M)
    {
        int index = rand() % size;
        
        if (indices.find(index) == indices.end())
        {
            // Not in the set. Add it
            indices.insert(index);
        }
    }
    
    return indices;
}

void createAbMatrix(std::map<std::string,Stock> &ZacksMap, std::vector<Matrix> &stockAbMatrices)
{
    for (int i = 0; i < STOCK_GROUP_NUM; i++)
    {
        stockAbMatrices.push_back(Matrix());
    }
    
    for (const std::pair<const std::string,Stock> &zm : ZacksMap)
    {
        if (zm.second.GetAbDailyRets().len() == 0) continue;
        
        for (int i = 0; i < STOCK_GROUP_NUM; i++)
        {
            if (zm.second.GetGroup() == SGTable[i])
            {
                stockAbMatrices[i].append(zm.second.GetAbDailyRets());
                break;
            }
        }
    }
}

void bootstrappingPerform(unsigned int N, unsigned int M, unsigned int K, const std::vector<Matrix> stockAbMatrices,
                          std::map<StockGroup,Vector> &AARAvgMap, std::map<StockGroup,Vector> &CAARAvgMap,
                          std::map<StockGroup,Vector> &AARStdMap, std::map<StockGroup,Vector> &CAARStdMap)
{
//    for (int i = 0; i < STOCK_GROUP_NUM; i++)
//    {
//        AARAvgMap.insert({ SGTable[i], Vector(2 * N + 1) });
//        CAARAvgMap.insert({ SGTable[i], Vector(2 * N + 1) });
//    }
    
    std::map<StockGroup,Matrix> AARMatrixMap;
    std::map<StockGroup,Matrix> CAARMatrixMap;
    
    // Initialize
    for (int i = 0; i < STOCK_GROUP_NUM; i++)
    {
        const StockGroup label = SGTable[i];
        
        AARMatrixMap.insert({ label, Matrix() });
        CAARMatrixMap.insert({ label, Matrix() });
    }
    
    for (auto i = 0; i < K; i++)
    {
        std::map<StockGroup,Vector> AARMap;
        std::map<StockGroup,Vector> CAARMap;
        
        boostrap(M, stockAbMatrices, AARMap, CAARMap);
        
        for (int i = 0; i < STOCK_GROUP_NUM; i++)
        {
            const StockGroup label = SGTable[i];
//            AARAvgMap[label] += AARMap[label];
//            CAARAvgMap[label] += CAARMap[label];
            AARMatrixMap[label].append(AARMap[label]);
            CAARMatrixMap[label].append(CAARMap[label]);
        }
    }
    
    for (int i = 0; i < STOCK_GROUP_NUM; i++)
    {
        const StockGroup label = SGTable[i];
//        AARAvgMap[label] *= 1./K;
//        CAARAvgMap[label] *= 1./K;
        AARAvgMap.insert({ label, mean(AARMatrixMap[label]) });
        AARStdMap.insert({ label, stdevp(AARMatrixMap[label]) });
        CAARAvgMap.insert({ label, mean(CAARMatrixMap[label]) });
        CAARStdMap.insert({ label, stdevp(CAARMatrixMap[label]) });
    }
}

void boostrap(unsigned int M, const std::vector<Matrix> stockAbMatrices, std::map<StockGroup,Vector> &AARMap, std::map<StockGroup,Vector> &CAARMap)
{
    for (int i = 0; i < stockAbMatrices.size(); i++)
    {
        const Matrix &origMtx = stockAbMatrices[i];
        const StockGroup label = SGTable[i];
        std::unordered_set<long> indices = genRandomIndex(M, origMtx.row());
        
        Matrix mtx;
        for (const long &index : indices)
        {
            mtx.append(origMtx[index]);
        }
        
        Vector AARVec = AAR(mtx);
        Vector CAARVec = CAAR(AARVec);
        
        AARMap.insert({ label, AARVec });
        CAARMap.insert({ label, CAARVec });
    }
}
