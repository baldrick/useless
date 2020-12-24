#ifndef STEPSIZE
#define STEPSIZE

#include <Arduino.h>

struct stepSize {
  unsigned int moveAmount;
  String sizeName;
};

typedef struct stepSize StepSize;

class Steps {
  public:
    static const StepSize SMALL;
    static const StepSize MEDIUM;
    static const StepSize LARGE;
};

#endif
