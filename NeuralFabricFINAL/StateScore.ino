#include "Arduino.h"
#include "StateScore.h"

#include <stdarg.h>
#include <stdio.h>


StateScore::StateScore(InternalState state, int count, ...) {
  
  _state = state;
  _scoreObjectsCount = count;
  _array = (BrainWaveScore**) malloc(sizeof(BrainWaveScore*) * count);
  
  va_list args;
  va_start(args, count);  

  for (int i = 0; i < count; i++) {
    _array[i] = va_arg(args, BrainWaveScore*);
  }
  
  va_end(args);
}

void StateScore::calculate(void) {
  
  _score = 0;
  
  for (int i = 0; i < _scoreObjectsCount; i++) {
    _score += _array[i]->calculate( 1.0f / _scoreObjectsCount );
  }
}

float StateScore::getScore(void) {
  return _score;
}

InternalState StateScore::getState(void) {
  return _state;  
}
