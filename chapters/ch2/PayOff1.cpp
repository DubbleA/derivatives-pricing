#include "PayOff1.h"
#include <algorithm>
using namespace std;

PayOff::PayOff(double Strike_, OptionType TheOptionType_) : Strike(Strike_),TheOptionType(TheOptionType_)
{

}

PayOff::PayOff(double LowerStrike_, double UpperStrike_, OptionType TheOptionType_) : LowerStrike(LowerStrike_), Strike(UpperStrike_), TheOptionType(TheOptionType_)
{

}

double PayOff::operator()(double Spot) const
{
    switch (TheOptionType)
    {
        case call:
            return max(Spot - Strike, 0.0);
        case put:
            return max(Strike - Spot, 0.0);
        //Exercise 2.1 Modify the pay-off class so that it can handle digital options
        case digital_call:
            return (Spot >= Strike) ? 1 : 0;
        case digital_put:
            return (Spot <= Strike) ? 1 : 0;
        case double_digital:
            return (LowerStrike <= Spot && Spot <= Strike) ? 1 : 0;
        default:
            throw("unknown option type found.");
    }
}

//#TODO have a class called option, then in option have subclasses called call and put // european vs american vs asian
//things are classes, actions (verbs) are methods 