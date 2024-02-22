#include "Random1.h"
#include "SimpleMCMain1.cpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

void randomValueTest(){
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Generate random parameters within reasonable ranges
    double Expiry = static_cast<double>(rand() % 10 + 1); // 1 to 10 years
    double Strike = static_cast<double>(rand() % 100 + 100); // 100 to 200
    double Spot = static_cast<double>(rand() % 50 + 100); // 100 to 150
    double Vol = static_cast<double>(rand() % 20 + 5) / 100.0; // 0.05 to 0.25
    double r = static_cast<double>(rand() % 10 + 1) / 100.0; // 0.01 to 0.1
    unsigned long NumberOfPaths = static_cast<unsigned long>(rand() % 10000 + 1000); // 1000 to 11000

    // Print generated parameters
    cout << "Using generated parameters:" << endl;
    cout << "Expiry: " << Expiry << endl;
    cout << "Strike: " << Strike << endl;
    cout << "Spot: " << Spot << endl;
    cout << "Vol: " << Vol << endl;
    cout << "r: " << r << endl;
    cout << "NumberOfPaths: " << NumberOfPaths << endl;

    // Call your Monte Carlo function
    double result = SimpleMonteCarlo1(Expiry, Strike, Spot, Vol, r, NumberOfPaths);

    // Print the result
    cout << "The price is " << result << "\n";
}

void BlackScholesCallTest1() {
    // Generate random parameters within reasonable ranges
    double Expiry = 0.5; // (6 months)
    double Strike = 40;
    double Spot = 42;
    double Vol = 0.2; 
    double r = 0.1;

    // Print generated parameters
    cout << "Using generated parameters:" << endl;
    cout << "Expiry: " << Expiry << endl;
    cout << "Strike: " << Strike << endl;
    cout << "Spot: " << Spot << endl;
    cout << "Vol: " << Vol << endl;
    cout << "r: " << r << endl;

    for (int i = 0; i < 200; i += 10){
        unsigned long NumberOfPaths = i * i;
        double result = SimpleMonteCarlo1(Expiry, Strike, Spot, Vol, r, NumberOfPaths);
        cout << "callPrice: " << result << ", for " << NumberOfPaths << " paths" << "\n";
    }
}

//should be $3-6 for 100 paths, and tighten the range based on #s of paths

void BlackScholesPutTest2() {
    // Generate random parameters within reasonable ranges
    // #TODO feed in outside test cases instead of hard coding them
    // #TODO Create file of test cases with priced outputs
    // #TODO all tests when we build program
    double Expiry = 0.5; // (6 months)
    double Strike = 40;
    double Spot = 42;
    double Vol = 0.2; 
    double r = 0.1;

    // Print generated parameters
    cout << "Using generated parameters:" << endl;
    cout << "Expiry: " << Expiry << endl;
    cout << "Strike: " << Strike << endl;
    cout << "Spot: " << Spot << endl;
    cout << "Vol: " << Vol << endl;
    cout << "r: " << r << endl;

    for (int i = 0; i < 200; i += 10){
        unsigned long NumberOfPaths = i * i;
        double result = SimpleMonteCarlo1Put(Expiry, Strike, Spot, Vol, r, NumberOfPaths);
        cout << "putPrice: " << result << ", for " << NumberOfPaths << " paths" << "\n";
    }
}

//example comes from: https://www.quantstart.com/articles/Double-digital-option-pricing-with-C-via-Monte-Carlo-methods
void DoubleDigitOptionTest() {
    // Generate random parameters within reasonable ranges
    double Expiry = 1; 
    double LowerStrike = 100;
    double UpperStrike = 120;
    double Spot = 100;
    double Vol = 0.2; 
    double r = 0.05;

    // Print generated parameters
    cout << "Using generated parameters:" << endl;
    cout << "Expiry: " << Expiry << endl;
    cout << "Strike: " << UpperStrike << endl;
    cout << "Spot: " << Spot << endl;
    cout << "Vol: " << Vol << endl;
    cout << "r: " << r << endl;

    for (int i = 0; i < 200; i += 10){
        unsigned long NumberOfPaths = i * i;
        double result = SimpleMonteCarlo1DoubleDigit(Expiry, UpperStrike, LowerStrike, Spot, Vol, r, NumberOfPaths);
        cout << "callPrice: " << result << ", for " << NumberOfPaths << " paths" << "\n";
    }
}

void testTemplateMonteCarlo() {
    // Generate random parameters within reasonable ranges
    double Expiry = 0.5; // (6 months)
    double Strike = 40;
    double Spot = 42;
    double Vol = 0.2; 
    double r = 0.1;

    // Print generated parameters
    cout << "Using generated parameters:" << endl;
    cout << "Expiry: " << Expiry << endl;
    cout << "Strike: " << Strike << endl;
    cout << "Spot: " << Spot << endl;
    cout << "Vol: " << Vol << endl;
    cout << "r: " << r << endl;

    for (int i = 0; i < 200; i += 10){
        unsigned long NumberOfPaths = i * i;
        double result = SimpleMonteCarlo1(Expiry, Strike, Spot, Vol, r, NumberOfPaths, "call");
        cout << "callPrice: " << result << ", for " << NumberOfPaths << " paths" << "\n";
    }

    for (int i = 0; i < 200; i += 10){
        unsigned long NumberOfPaths = i * i;
        double result = SimpleMonteCarlo1(Expiry, Strike, Spot, Vol, r, NumberOfPaths, "put");
        cout << "putPrice: " << result << ", for " << NumberOfPaths << " paths" << "\n";
    }

}


int main() {
    cout << "The random value Test: " << "\n";
    randomValueTest();
    cout << "\n";

    cout << "Black Scholes model test: output should be 4.76" << "\n";
    BlackScholesCallTest1();

    cout << "Black Scholes model test: put price should be 0.81 (lower than the call since its OTM)" << "\n";
    BlackScholesPutTest2();

    cout << "Double Digit Option test: put price should be 0.32009" << "\n";
    DoubleDigitOptionTest();

    cout << "template test: call output should be 4.76, put output 0.81" << "\n";
    testTemplateMonteCarlo();
    return 0;

    
}

// if you buy call & put OTM if volatility is higher than expected maybe one or both pop off
// if you expect low volatility you sell the option. 

//price is a real function

// #TODO Real option prices
// #Tests for each piece of code
