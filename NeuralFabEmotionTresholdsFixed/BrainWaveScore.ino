#include "Arduino.h"
#include "BrainWaveScore.h"

BrainWaveScore::BrainWaveScore(BrainWaveStats* stats, BrainWaveScoring scoring) {
  
  _stats = stats;
  _scoring = scoring;
}

float BrainWaveScore::calculate(float fraction) {

  float score = 0;
  
  _statsRange = (_stats->maxValue() - _stats->minValue());
  
  switch(_scoring) {
    case DIRECT:
      score = scoreDirect( _stats->smoothedValue() );
      break;  

    case INVERSE:
      score = scoreInverse( _stats->smoothedValue() );
      break;  
    
    case MEAN_PEAK:
      score = scoreMeanPeak( _stats->smoothedValue() );
      break;
  }
  
  return (score * fraction);
}
  
float BrainWaveScore::scoreDirect(float value) {
  return ((value - _stats->minValue()) / _statsRange);
}

float BrainWaveScore::scoreInverse(float value) {
  return (1.0f - scoreDirect(value));
}

float BrainWaveScore::scoreMeanPeak(float value) {
  float result;
  
  if (value > _stats->meanValue()) {
    result = (_stats->maxValue() - value) / (_stats->maxValue() - _stats->meanValue());
  }
  else {
    result = (value - _stats->minValue()) / (_stats->meanValue() - _stats->minValue());    
  }
    
  return result;
} 
  

