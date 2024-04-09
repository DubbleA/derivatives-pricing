#ifndef SIMPLE_MC_H
#define SIMPLE_MC_H

/*
easily extendible to handle any pay-off and time dependent parameters
*/

#include "Vanilla.h" // use vanilla option class
#include "Parameters.h" // parameter class for IR and volatility
#include "MCStatistics.h"// store result from MC simulation paths

// previous return double, since now stored in gatherer, no return required
void SimpleMonteCarlo5(const VanillaOption& TheOption,
                       double Spot,
                       const Parameters& Vol,
                       const Parameters& r,
                       unsigned long NumberOfPaths,
                       StatisticsMC& gatherer);
// StatisticsMC is passed by reference and not constant


#endif //end SIMPLE_MC_H