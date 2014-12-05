#include "Arduino.h"
#include "BrainWaveStats.h"


BrainWaveStats::BrainWaveStats() {

  _count = 0;
  _value = 0;
  _mean = 0;

  _smoothedValue = 0;
  
  _max = -3.4028235E+38;
  _min =  3.4028235E+38;
}

void BrainWaveStats::update(float value) {

  _value = value;
  
  _max = max(_max, value);
  _min = min(_min, value);
  
  _mean *= _count;
  _mean += value;
  _mean /= (_count + 1);

  _smoothedValue = rollingAverage(_history, SMOOTHING_FACTOR, value);

  _count++;
}

bool BrainWaveStats::ready(void) {
  return (_count >= SMOOTHING_FACTOR);
}

float BrainWaveStats::lastValue(void) {
  return _value;
}

float BrainWaveStats::mean(void) {
  return _mean;
}

float BrainWaveStats::maxValue(void) {
  return _max;
}

float BrainWaveStats::minValue(void) {
  return _min;
}

float BrainWaveStats::smoothedValue(void) {
 return 0.0f; 
}

