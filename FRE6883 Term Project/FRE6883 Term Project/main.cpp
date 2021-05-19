//
//  main.cpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/6/21.
//

#include "Stock.hpp"
#include "DataStructures/Matrix.hpp"
#include "ZacksData.hpp"
#include "WebScrape.hpp"
#include "Bootstrapping.hpp"
#include "Visualization.hpp"
#include <iostream>
#include <map>
#include <string>

using namespace std;

const char *ZACKS_FNAME = "./ZacksData.csv";

int main(int argc, const char * argv[]) {
    string userInput;
    char selection = NULL;
    int N = 0;
    
    ZacksDataRetriever zdr;
    zdr.build(ZACKS_FNAME);
    
    if (!zdr.ready())
    {
        printError("Failed to retrieve Zacks data.");
        return -1;
    }
    
    map<string,Stock> ZacksMap = zdr.retrieve();
    
    map<StockGroup,Vector> AARAvgMap;
    map<StockGroup,Vector> CAARAvgMap;
    map<StockGroup,Vector> AARStdMap;
    map<StockGroup,Vector> CAARStdMap;
    
    WebScraper ws;
    
    do
    {
        printMenu();
        cout << "Enter selection: ";
        cin >> userInput;
        
        if (userInput.length() != 1)
        {
            cerr << "Invalid selection." << endl;
            continue;
        }
        
        transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
        selection = userInput.c_str()[0];
        
        switch (selection) {
            case 'A':
            {
                N = getN();
                if (N == -1) continue;
                
                if (ws.PopulateStockDailyInfo(ZacksMap, N))
                {
                    printError("Failed to populate stocks' daily trade info.");
                    return -1;
                }
                
                break;
            }
            
            case 'B':
            {
                string symbol;
                
                cout << "Enter stock symbol: ";
                cin >> symbol;
                
                // Prof. Tang inquired why we did not make stock symbols case-insensitive
                // I know you said it's not required, but I'll add that feature here anyway
                transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
                
                if (ZacksMap.find(symbol) == ZacksMap.end())
                {
                    // Not found
                    printError("Stock " + symbol + " does not exist in the map. Going back to menu.");
                    continue;
                }
                
                cout << ZacksMap[symbol] << endl;
                
                break;
            }
            
            case 'C':
            {
                unsigned int M = 50;
                unsigned int K = 40;
                
                vector<Matrix> stockAbMatrices;
                AARAvgMap.clear();
                AARStdMap.clear();
                CAARAvgMap.clear();
                CAARStdMap.clear();
                
                createAbMatrix(ZacksMap, stockAbMatrices);
                bootstrappingPerform(N, M, K, stockAbMatrices, AARAvgMap, CAARAvgMap, AARStdMap, CAARStdMap);
                
                /* BEGIN 3D Matrix */// Added for meeting project requirement
                vector<Matrix> resMtx;
                for (int i = 0; i < STOCK_GROUP_NUM; i++)
                {
                    const StockGroup label = SGTable[i];
                    Matrix groupResMtx;
                    
                    groupResMtx.append(AARAvgMap[label]);
                    groupResMtx.append(AARStdMap[label]);
                    groupResMtx.append(CAARAvgMap[label]);
                    groupResMtx.append(CAARStdMap[label]);
                    
                    resMtx.push_back(groupResMtx);
                }
                
                // Print out the 3D matrix
                cout << "[" << endl;
                for (auto i = 0; i < resMtx.size(); i++)
                {
                    cout << resMtx[i] << (i == resMtx.size() - 1 ? "" : ", ") << endl;
                }
                cout << "]" << endl << endl;
                /* END 3D Matrix */
                
                for (int i = 0; i < STOCK_GROUP_NUM; i++)
                {
                    const StockGroup label = SGTable[i];
                    cout << "==================================================" << endl;
                    cout << "StockGroup=" << StockGroupStrMap[label] << endl;
                    
                    cout << "AAR Avg:" << endl;
                    cout << AARAvgMap[label] << endl;
                    
                    cout << "AAR Stdev:" << endl;
                    cout << AARStdMap[label] << endl;
                    
                    cout << "CAAR Avg:" << endl;
                    cout << CAARAvgMap[label] << endl;
                    
                    cout << "CAAR Stdev:" << endl;
                    cout << CAARStdMap[label] << endl;
                    
                    cout << endl;
                }
                
                break;
            }
            
            case 'D':
            {
                int nitem = 2 * N + 1;
                double *xData = (double *) malloc(nitem * sizeof(double));
                vector<double *> yData;
                for (int i = 0; i < STOCK_GROUP_NUM; i++)
                {
                    yData.push_back(static_cast<double *>(malloc(nitem * sizeof(double))));
                }
                
                for (int i = 0; i < nitem; i++)
                {
                    xData[i] = i - N;
                }
                
                for (int i = 0; i < STOCK_GROUP_NUM; i++)
                {
                    const StockGroup label = SGTable[i];
                    const Vector &CAARAvg = CAARAvgMap[label];
                    
                    for (int j = 0; j < nitem; j++)
                    {
                        yData[i][j] = CAARAvg[j] * 100;
                    }
                }
                
                int plotStatus = plotResults(nitem, xData, yData);
                
                // Free the allocated memory
                free(xData);
                for (double * &ydp : yData)
                {
                    free(ydp);
                }

                if (plotStatus)
                {
                    printError("Gnuplot not installed.");
                    return -1;
                }
                
                break;
            }
            
            default:
                break;
        }
        
    } while (selection != 'X');
    
    cleanup();  // Remove temporary files
    
    return 0;
}
