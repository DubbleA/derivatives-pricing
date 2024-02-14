// A simple implementation of a Monte Carlo call option pricer

#include "Random1.h"
#include <iostream>
#include <cmath>

using namespace std;

//calculates average payoff through simulation. therefore all negative cases end up at 0. 
double SimpleMonteCarlo1(double Expiry, double Strike,
                         double Spot, double Vol, double r,
                         unsigned long NumberOfPaths)
{
    double variance = Vol * Vol * Expiry;
    double rootVariance = sqrt(variance);
    double itoCorrection = -0.5 * variance;

    double movedSpot = Spot * exp(r * Expiry + itoCorrection);
    double thisSpot, runningSum = 0;
    for (unsigned long i = 0; i < NumberOfPaths; ++i){
        double thisGaussian = GetOneGaussianByBoxMuller();
        thisSpot = movedSpot * exp(rootVariance * thisGaussian);
        double thisPayoff = thisSpot - Strike;
        thisPayoff = thisPayoff > 0 ? thisPayoff : 0;
        runningSum += thisPayoff;
    }

    double mean = runningSum / NumberOfPaths;
    mean *= exp(-r * Expiry);
    return mean;
}

// int main()
// {
//     double Expiry;
//     double Strike;
//     double Spot;
//     double Vol;
//     double r;
//     unsigned long NumberOfPath;
    
//     //read in parameters
//     cout << "\nEnter expiry\n";
//     cin >> Expiry;
    
//     cout << "\nEnter Strike\n";
//     cin >> Strike;
    
//     cout << "\nEnter spot\n";
//     cin >> Spot;
    
//     cout << "\nEnter vol\n";
//     cin >> Vol;
    
//     cout << "\nEnter r\n";
//     cin >> r;
    
//     cout << "\n Number of paths\n";
//     cin >> NumberOfPath;
    
//     double result = SimpleMonteCarlo1(Expiry,
//                                       Strike,
//                                       Spot,
//                                       Vol,
//                                       r,
//                                       NumberOfPath);
//     cout << "the price is " << result << "\n";
    
//     double tmp;
//     cin >> tmp;

//     return 0;
// }

//g++ -std=c++20 -I. -o smc1 SimpleMCMain1.cpp Random1.cpp && ./smc1
