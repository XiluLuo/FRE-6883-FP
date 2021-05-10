//
//  Visualization.hpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/8/21.
//

#ifndef Visualization_hpp
#define Visualization_hpp

#include <vector>

// Plot the results (x -> multiple y) to Gnuplot
// Temporary files created at this step
int plotResults(int nitem, double *xData, std::vector<double *> yData);

// Remove the temporary files
bool cleanup();

#endif /* Visualization_hpp */
