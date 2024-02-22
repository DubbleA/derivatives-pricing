#include "Random1.h"
#include "SimpleMC.cpp"
#include "PayOff1.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// //example comes from: https://www.quantstart.com/articles/Double-digital-option-pricing-with-C-via-Monte-Carlo-methods
// void DoubleDigitOptionTest() {
//     // Generate random parameters within reasonable ranges
//     double Expiry = 1; 
//     double LowerStrike = 100;
//     double UpperStrike = 120;
//     double Spot = 100;
//     double Vol = 0.2; 
//     double r = 0.05;

//     // Print generated parameters
//     cout << "Using generated parameters:" << endl;
//     cout << "Expiry: " << Expiry << endl;
//     cout << "Strike: " << UpperStrike << endl;
//     cout << "Spot: " << Spot << endl;
//     cout << "Vol: " << Vol << endl;
//     cout << "r: " << r << endl;

//     for (int i = 0; i < 200; i += 10){
//         unsigned long NumberOfPaths = i * i;
//         double result = SimpleMonteCarlo1DoubleDigit(Expiry, UpperStrike, LowerStrike, Spot, Vol, r, NumberOfPaths);
//         cout << "callPrice: " << result << ", for " << NumberOfPaths << " paths" << "\n";
//     }
// }

void testTemplateMonteCarlo() {
    // Generate random parameters within reasonable ranges
    double Expiry = 0.5; // (6 months)
    double Strike = 40;
    double Spot = 42;
    double Vol = 0.2; 
    double r = 0.1;

    PayOff callPayoff (Strike, PayOff::OptionType::call);
    PayOff putPayoff (Strike, PayOff::OptionType::put);

    // Print generated parameters
    cout << "Using generated parameters:" << endl;
    cout << "Expiry: " << Expiry << endl;
    cout << "Strike: " << Strike << endl;
    cout << "Spot: " << Spot << endl;
    cout << "Vol: " << Vol << endl;
    cout << "r: " << r << endl;

    for (int i = 0; i < 200; i += 10){
        unsigned long NumberOfPaths = i * i;
        double result = SimpleMonteCarlo2(callPayoff, Expiry, Spot, Vol, r, NumberOfPaths);
        cout << "callPrice: " << result << ", for " << NumberOfPaths << " paths" << "\n";
    }

    for (int i = 0; i < 200; i += 10){
        unsigned long NumberOfPaths = i * i;
        double result = SimpleMonteCarlo2(putPayoff, Expiry, Spot, Vol, r, NumberOfPaths);
        cout << "putPrice: " << result << ", for " << NumberOfPaths << " paths" << "\n";
    }

}


int main() {

    // cout << "Double Digit Option test: put price should be 0.32009" << "\n";
    // DoubleDigitOptionTest();

    cout << "template test: call output should be 4.76, put output 0.81" << "\n";
    testTemplateMonteCarlo();

    //source for digital option results: https://www.quantstart.com/articles/Digital-option-pricing-with-C-via-Monte-Carlo-methods

    //Expected Call Price: 0.532424
    //Expected Put Price: 0.418726

    cout << "Digital Option Test: Expected Call Price: 0.532424\n";
    PayOff callPayoff (100, PayOff::OptionType::digital_call);
    cout << "Digital Option Test: Expected Put Price: 0.418726\n";
    double result = SimpleMonteCarlo2(callPayoff, 1, 100, 0.2, 0.05, 10000000);
    cout << "callPrice: " << result << ", for " << 10000000 << " paths" << "\n";

    PayOff putPayoff (100, PayOff::OptionType::digital_put);
    result = SimpleMonteCarlo2(putPayoff, 1, 100, 0.2, 0.05, 10000000);
    cout << "callPrice: " << result << ", for " << 10000000 << " paths" << "\n";

    PayOff ddPayoff (100, 120, PayOff::OptionType::double_digital);
    result = SimpleMonteCarlo2(ddPayoff, 1, 100, 0.2, 0.05, 10000000);
    cout << "doubleDigital: expected 0.3196: " << result << ", for " << 10000000 << " paths" << "\n";
    return 0;
}

