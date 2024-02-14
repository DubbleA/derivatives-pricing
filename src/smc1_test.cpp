#include "Random1.h"
#include "SimpleMCMain1.cpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Your SimpleMonteCarlo1 function declaration or include statement here

int main() {
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
    double result = SimpleMonteCarlo1(2, 104, 109, Vol, r, NumberOfPaths);

    // Print the result
    cout << "The price is " << result << "\n";

    return 0;
}
