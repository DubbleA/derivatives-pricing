#ifndef SIMPLEMC_H
#define SIMPLEMC_H
#include "PayOff1.h"


double SimpleMonteCarlo2(const PayOff& thePayOff,
                         double Expiry,
                         double Spot,
                         double Vol, //vix
                         double r,
                         unsigned long NumberOfPath);

#endif