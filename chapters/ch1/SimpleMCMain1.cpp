// A simple implementation of a Monte Carlo call option pricer

#include "Random1.h"
#include <iostream>
#include <cmath>

using namespace std;

// calculates average payoff through simulation. therefore all negative cases end up at 0. 
// Expiry in years (0.5 = 6 months); Strike is pretermined price the option ca be exerised; Spot price is the curret price of the option
// for call options: calculates thisPayoff = thisSpot - Strike
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
        if(thisPayoff < 0) thisPayoff = 0;
        runningSum += thisPayoff;
    }

    double mean = runningSum / NumberOfPaths;
    mean *= exp(-r * Expiry);
    return mean;
}

// Exercise 1.1 modify the program to price puts
// for put options: calculates thisPayoff = Strike - thisSpot
double SimpleMonteCarlo1Put(double Expiry, double Strike,
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
        double thisPayoff = Strike - thisSpot; //key line
        if(thisPayoff < 0) thisPayoff = 0;
        runningSum += thisPayoff;
    }

    double mean = runningSum / NumberOfPaths;
    mean *= exp(-r * Expiry);
    return mean;
}

//Exercise 1.2 Modify the program to process double digitals
// A double digital option is a financial instrument that pays 1 if the underlying asset is between two strike prices or 0 if not.
double SimpleMonteCarlo1DoubleDigit(double Expiry, double StrikeUpper, double StrikeLower,
                         double Spot, double Vol, double r,
                         unsigned long NumberOfPaths)
{
    double variance = Vol * Vol * Expiry;
    double rootVariance = sqrt(variance);
    double itoCorrection = -0.5 * variance;

    double movedSpot = Spot * exp(r * Expiry + itoCorrection);
    double thisSpot, runningSum = 0;

    if(StrikeLower > StrikeUpper) swap(StrikeLower, StrikeUpper);

    for (unsigned long i = 0; i < NumberOfPaths; ++i){
        double thisGaussian = GetOneGaussianByBoxMuller();
        thisSpot = movedSpot * exp(rootVariance * thisGaussian);
        double thisPayoff;
        if(StrikeLower <= thisSpot and thisSpot <= StrikeUpper) thisPayoff = 1;
        else thisPayoff = 0;
        runningSum += thisPayoff;
    }

    double mean = runningSum / NumberOfPaths;
    mean *= exp(-r * Expiry);
    return mean;
}

//template for exercise 1.3 add multiple opcodes
template <typename T, typename U, typename V>
T SimpleMonteCarlo1 (T Expiry, T Strike,
                     T Spot, T Vol, T r,
                     U NumberOfPaths, V OptionType) 
{
    auto variance = Vol * Vol * Expiry;
    auto rootVariance = sqrt(variance);
    auto itoCorrection = -0.5 * variance;

    auto movedSpot = Spot * exp(r * Expiry + itoCorrection);
    auto thisSpot = 0.0, runningSum = 0.0;
    if (OptionType == "call") {
        for (auto i = 0; i < NumberOfPaths; ++i) {
            auto thisGaussian = GetOneGaussianByBoxMuller();
            thisSpot = movedSpot * exp(rootVariance * thisGaussian);
            auto thisPayoff = thisSpot - Strike;
            if (thisPayoff < 0) thisPayoff = 0;
            runningSum += thisPayoff;
        }
    } else if (OptionType == "put") {
        for (auto i = 0; i < NumberOfPaths; ++i) {
            auto thisGaussian = GetOneGaussianByBoxMuller();
            thisSpot = movedSpot * exp(rootVariance * thisGaussian);
            auto thisPayoff = Strike - thisSpot;
            if (thisPayoff < 0) thisPayoff = 0;
            runningSum += thisPayoff;
        }
    } else {
        // Option type not recognized
    }

    auto mean = runningSum / NumberOfPaths;
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
