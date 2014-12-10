#ifndef STATESCORE_H
#define STATESCORE_H

#include <stdarg.h>
#include <stdio.h>
#include "BrainWaveScore.h"
#include "RainbowOutput.h"

class StateScore {
  public:
    StateScore(InternalState state, int count, ...);
    
    void calculate(void);
      
    float getScore(void);
    
    InternalState getState(void);
    
  private:
    InternalState _state;
    float _score;
    int _scoreObjectsCount;
    BrainWaveScore** _array;
};


#endif
