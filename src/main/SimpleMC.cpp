#include "SimpleMC.h"
#include "Random.h"
#include <cmath>


void SimpleMonteCarlo5(const VanillaOption& TheOption,
                       double Spot,
                       const Parameters& Vol,
                       const Parameters& r,
                       unsigned long NumberOfPaths,
                       StatisticsMC& gatherer)
{
    double Expiry = TheOption.GetExpiry();
    double variance = Vol.IntegralSquare(0, Expiry);
    double rootVariance = sqrt(variance);
    
    double itoCorrection = -0.5*variance;
    double movedSpot = Spot*exp(r.Integral(0, Expiry) + itoCorrection);
    double thisSpot;
    double discounting = exp(-r.Integral(0, Expiry));
    
    for (unsigned long i = 0; i<NumberOfPaths; i++) {
        double thisGaussian = GetOneGaussianByBoxMuller();
        thisSpot = movedSpot*exp(rootVariance*thisGaussian);
        double thisPayOff = TheOption.OptionPayOff(thisSpot);
        gatherer.DumpOneResult(thisPayOff*discounting);
    }
    return;
}

// void SimpleMonteCarlo5(const VanillaOption& TheOption,
//                        double Spot,
//                        const Parameters& Vol,
//                        const Parameters& r,
//                        unsigned long NumberOfPaths,
//                        StatisticsMC& gatherer)
// {
//     double Expiry = TheOption.GetExpiry();
//     double variance = Vol.Integral(0, Expiry);
//     double rootVariance = sqrt(variance);
    
//     double itoCorrection = -0.5*variance;
//     double movedSpot = Spot*exp(r.Integral(0, Expiry)+itoCorrection);
//     double thisSpot;
//     double discounting = exp(-r.Integral(0, Expiry));
    
//     for (unsigned long i = 0; i<NumberOfPaths; i++) {
//         double thisGaussian = GetOneGaussianByBoxMuller();
//         thisSpot = movedSpot*exp(rootVariance*thisGaussian);
//         double thisPayOff = TheOption.OptionPayOff(thisSpot);
//         // all work on accounting the mean is wrapped
//         gatherer.DumpOneResult(thisPayOff*discounting);
        
//     }
//     return;
// }