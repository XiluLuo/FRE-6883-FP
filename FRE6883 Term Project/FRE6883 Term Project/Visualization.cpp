//
//  Visualization.cpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/8/21.
//

#include "Visualization.hpp"
#include "Stock.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

int plotResults(int nitem, double *xData, std::vector<double *> yData)
{
    std::vector<std::string> tempDataFileNames;
    for (auto const &sgsm : StockGroupStrMap)
    {
        tempDataFileNames.push_back(sgsm.second);
    }
    
    FILE *gnuplotPipe, *tempDataFile;
    gnuplotPipe = popen("/opt/local/bin/gnuplot", "w");
    
    if (!gnuplotPipe) return -1;
    
    fprintf(gnuplotPipe, "set title \"CAAR\"font \"Helvetica, 16\"\n");
    fprintf(gnuplotPipe, "set xlabel \"Days\"font \"Helvetica, 16\"\n");
    fprintf(gnuplotPipe, "set ylabel \"Percentage\"font \"Helvetica, 16\"\n");
    
    std::stringstream ss;
    ss << "plot ";
    for (int i = 0; i < tempDataFileNames.size(); i++)
    {
        const std::string &tdfname = tempDataFileNames[i];
        if (i != 0) { ss << ","; }
        ss << " \"" << tdfname << "\" with lines";
    }
    ss << "\n";
    std::string gnuplotCommand = ss.str();
    
    fprintf(gnuplotPipe, "%s", gnuplotCommand.c_str());
    fflush(gnuplotPipe);
    
    for (int i = 0; i < tempDataFileNames.size(); i++)
    {
        tempDataFile = fopen(tempDataFileNames[i].c_str(), "w");
        
        for (int k = 0; k < nitem; k++)
        {
            fprintf(tempDataFile, "%lf %lf\n", xData[k], yData[i][k]);
        }
        
        fclose(tempDataFile);
    }

    fprintf(gnuplotPipe, "exit\n");
    
    return 0;
}

bool cleanup()
{
    bool success = true;
    
    for (auto const &sgsm : StockGroupStrMap)
    {
        int retCode = std::remove(sgsm.second.c_str());
        if (retCode) { success = false; }
    }
    
    return success;
}
