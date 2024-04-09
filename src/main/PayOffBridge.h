#ifndef PAYOFF_BRIDGE_H
#define PAYOFF_BRIDGE_H

#include "PayOff.h"

/*

To make sure we do not need to write special code for assignment, construction, and destruction between 
our Vanilla option class and PayOff class we can create a bridge class. The bridge handles its own 
memory management. 

THE BRIDGE PATTERN connection between options and payoff classes. 

For testing can have a worthless payoff class that returns 0. (options that expire worthless)

Blue circle red circle. Can have shape contain a color. 

Bridge patterns allows us to give us something to feed in. Option -> has different payoff classes that calculate the payoff.
can have a vanilla option but give it european style payoff. 

Vanilla Option -> inheret put and call from that. Bridge is good when you're inheriting more than one dimension.

*/

class PayOffBridge
{
public:
    PayOffBridge(const PayOffBridge& original); // copy constructor
    PayOffBridge(const PayOff& innerPayOff);
    
    inline double operator()(double Spot) const;
    ~PayOffBridge();
    PayOffBridge& operator=(const PayOffBridge& original);
    
private:
    PayOff* ThePayOffPtr;
};

inline double PayOffBridge::operator()(double Spot) const
{
    return ThePayOffPtr->operator()(Spot); // call the method in PayOff class to get the payoff
}

#endif //end PAYOFF_BRIDGE_H