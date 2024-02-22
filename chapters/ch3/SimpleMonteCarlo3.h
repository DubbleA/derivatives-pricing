#ifndef __Option_Class__SimpleMonteCarlo3__
#define __Option_Class__SimpleMonteCarlo3__

#include <iostream>
#include "Vanilla1.h"

double SimpleMonteCarlo3(const VanillaOption& TheOption,
                         double Spot,
                         double Vol,
                         double r,
                         unsigned long NumberOfPaths);


#endif /* defined(__Option_Class__SimpleMonteCarlo3__) */