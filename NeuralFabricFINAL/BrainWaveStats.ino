#include "Arduino.h"
#include "BrainWaveStats.h"

BrainWaveStats::BrainWaveStats(int smoothing) {

  _count = 0;
  _smoothing = smoothing;
  
  _value = 0;
  _mean = 0;
  _smoothedValue = 0;
    
  _max = -3.4028235E+38;
  _min =  3.4028235E+38;
  
  _array = (float*) malloc(sizeof(float) * smoothing);
  
  for (int i = 0; i < smoothing; i++) {
    _array[i] = 0;  
  }
}

void BrainWaveStats::update(float value) {

  _value = value;
  
  _max = max(_max, value);
  _min = min(_min, value);
  
  _mean *= _count;
  _mean += value;

  _count++;

  _mean /= _count;

  _smoothedValue = processSmoothing(value);
  
  Serial.print("  Smoothed: ");
  Serial.println(_smoothedValue);
  Serial.print("  Max: ");
  Serial.println(_max);
  Serial.print("  Min: ");
  Serial.println(_min);
  Serial.print("  Mean: ");
  Serial.println(_mean);
}

bool BrainWaveStats::ready(void) {
  return (_count >= _smoothing);
}

float BrainWaveStats::lastValue(void) {
  return _value;
}

float BrainWaveStats::meanValue(void) {
  return _mean;
}

float BrainWaveStats::maxValue(void) {
  return _max;
}

float BrainWaveStats::minValue(void) {
  return _min;
}

float BrainWaveStats::smoothedValue(void) {
 return _smoothedValue; 
}

float BrainWaveStats::processSmoothing(float value) {
  int i;
  int divisor;
  float sum = 0;
  
  // Shift all values
  for (i = (_smoothing-1); i > 0; i--) {
    _array[i] = _array[i-1];
  }
  
  // Insert new value
  _array[0] = value;
  
  divisor = min(_count, _smoothing);
  
  // Add up all values
  for (i = 0; i < divisor; i++) {
    sum += _array[i];
  }

  // Return mean
  return (sum / divisor);
}


