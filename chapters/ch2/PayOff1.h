#ifndef PAYOFF_H //make sure only defined once
#define PAYOFF_H

class PayOff
{
public:
    enum OptionType {call, put, digital_call, digital_put, double_digital};
    // the constructor
    PayOff(double Strike_, OptionType TheOptionType_);
    // given a value of a spot, return the value of the payoff
    // constructor for Double Digitals
    PayOff(double LowerStrike_, double UpperStrike_, OptionType TheOptionType_);
    double operator()(double Spot) const;
    
private:
    double Strike;
    double LowerStrike;
    OptionType TheOptionType;
};

#endif

//Extensibility problems
//If we want to add new features we do not have to 
//touch our Monte Carlo pricer, 
//however we still have to modify the class, 
//we will use the concept of inheretance to avoid doing so.