//
//  Bootstrapping.cpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/8/21.
//

#include "Bootstrapping.hpp"
#include <utility>
#include <thread>

std::mutex MatrixMapMtx;

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

void bootstrappingPerform(unsigned int N, unsigned int M, unsigned int K, const std::vector<Matrix> &stockAbMatrices,
                          std::map<StockGroup,Vector> &AARAvgMap, std::map<StockGroup,Vector> &CAARAvgMap,
                          std::map<StockGroup,Vector> &AARStdMap, std::map<StockGroup,Vector> &CAARStdMap)
{
    std::map<StockGroup,Matrix> AARMatrixMap;
    std::map<StockGroup,Matrix> CAARMatrixMap;
    
    // Initialize
    for (int i = 0; i < STOCK_GROUP_NUM; i++)
    {
        const StockGroup label = SGTable[i];
        
        AARMatrixMap.insert({ label, Matrix() });
        CAARMatrixMap.insert({ label, Matrix() });
    }
    
    std::vector<std::thread> threadVec;
    for (auto i = 0; i < K; i++)
    {
        std::thread t(boostrap, M, std::ref(stockAbMatrices), std::ref(AARMatrixMap), std::ref(CAARMatrixMap));
        threadVec.push_back(std::move(t));
    }
    for (std::thread &t : threadVec)
    {
        t.join();
    }
    
    for (int i = 0; i < STOCK_GROUP_NUM; i++)
    {
        const StockGroup label = SGTable[i];
        AARAvgMap.insert({ label, mean(AARMatrixMap[label]) });
        AARStdMap.insert({ label, stdevp(AARMatrixMap[label]) });
        CAARAvgMap.insert({ label, mean(CAARMatrixMap[label]) });
        CAARStdMap.insert({ label, stdevp(CAARMatrixMap[label]) });
    }
}

void boostrap(unsigned int M, const std::vector<Matrix> &stockAbMatrices, std::map<StockGroup,Matrix> &AARMatrixMap, std::map<StockGroup,Matrix> &CAARMatrixMap)
{
    for (int i = 0; i < STOCK_GROUP_NUM; i++)
    {
        const StockGroup label = SGTable[i];
        const Matrix &origMtx = stockAbMatrices[i];
        
        std::unordered_set<long> indices = genRandomIndex(M, origMtx.row());

        Matrix mtx;
        for (const long &index : indices)
        {
            mtx.append(origMtx[index]);
        }

        Vector AARVec = AAR(mtx);
        Vector CAARVec = CAAR(AARVec);

        MatrixMapMtx.lock();
        
        AARMatrixMap[label].append(AARVec);
        CAARMatrixMap[label].append(CAARVec);
        
        MatrixMapMtx.unlock();
    }
}
