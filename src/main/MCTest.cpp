#include "SimpleMC.h"
#include <iostream>
#include "Vanilla.h"
#include "MCStatistics.h"
#include "ConvergenceTable.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//get historical data and try and generate our own volatility value
// put strike and current market price of stock
// as well as difference from 
// expected price / market / actual price

//test put price generation
//setup polygon.io 
//see if we can create our own volatility estimate
//more heavily weight recent data

int main() {
    ifstream file("parameters.csv");
    string line;

    // Skip the header line
    getline(file, line);

    int testsPassed = 0;
    int totalTests = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string item, type;
        string ticker;
        double Expiry, Strike, Spot, Vol, r, ExpectedPrice, Tolerance;
        unsigned long NumberOfPaths;


        getline(ss, ticker, ',');

        getline(ss, type, ',');


        getline(ss, item, ',');
        Spot = stod(item);
        getline(ss, item, ',');
        Strike = stod(item);
        getline(ss, item, ',');
        Expiry = stod(item);
        getline(ss, item, ',');
        Vol = stod(item);
        getline(ss, item, ',');
        r = stod(item);
        getline(ss, item, ',');
        NumberOfPaths = stoul(item);
        getline(ss, item, ',');
        ExpectedPrice = stod(item);
        getline(ss, item, ',');
        Tolerance = stod(item);

        PayOff* payOffPtr;
        if (type == "call") {
            payOffPtr = new PayOffCall(Strike);
        } else if (type == "put") {
            payOffPtr = new PayOffPut(Strike);
        } else {
            cout << "Error: Unknown option type." << endl;
            continue;
        }

        VanillaOption theOption(*payOffPtr, Expiry);
        ParametersConstant VolParam(Vol);
        ParametersConstant rParam(r);
        StatisticsMean gatherer;
        SimpleMonteCarlo5(theOption, Spot, VolParam, rParam, NumberOfPaths, gatherer);

        double priceResult = gatherer.GetResultsSoFar()[0][0];
        cout << "\n" << ticker << "\n";
        cout << "\nFor the " << type << " option, the simulation results are: \n";
        cout << "Generated Price: " << priceResult << endl;
        cout << "Expected Price: " << ExpectedPrice << endl;
        cout << "Tolerance: " << Tolerance << endl;

        // Check if the result is within the expected tolerance
        if (abs(priceResult - ExpectedPrice) <= Tolerance) {
            cout << "Test Passed: Price is within the expected tolerance." << endl;
            testsPassed++;
        } else {
            cout << "Test Failed: Price is not within the expected tolerance." << endl;
        }

        totalTests++;
        delete payOffPtr; // Clean up
    }

    cout << "\nSummary: " << testsPassed << " out of " << totalTests << " tests passed." << endl;

    return 0;
}