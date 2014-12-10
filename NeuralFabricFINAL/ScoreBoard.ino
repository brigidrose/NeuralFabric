#include "ScoreBoard.h"
#include "RainbowOutput.h"
#include "BrainWaveScore.h"
#include "BrainWaveStats.h"


ScoreBoard::ScoreBoard (
  BrainWaveStats* theta,
  BrainWaveStats* delta,
  BrainWaveStats* lowAlpha,
  BrainWaveStats* highAlpha,
  BrainWaveStats* lowBeta,
  BrainWaveStats* highBeta ) {

  int count = 0;
    
  _stats = theta;  
    
  _scoringArray[count++] = new StateScore ( HAPPY, 6,
    new BrainWaveScore( delta,     MEAN_PEAK ),
    new BrainWaveScore( theta,     MEAN_PEAK ),
    new BrainWaveScore( lowAlpha,  MEAN_PEAK ),
    new BrainWaveScore( highAlpha, MEAN_PEAK ),
    new BrainWaveScore( lowBeta,   MEAN_PEAK ),
    new BrainWaveScore( highBeta,  MEAN_PEAK )
    );
  
  _scoringArray[count++] = new StateScore ( ANXIOUS, 5,
    new BrainWaveScore( theta,     DIRECT  ),
    new BrainWaveScore( lowAlpha,  INVERSE  ),
    new BrainWaveScore( highAlpha, INVERSE  ),
    new BrainWaveScore( lowBeta,   DIRECT  ),
    new BrainWaveScore( highBeta,  DIRECT  )
    );

  _scoringArray[count++] = new StateScore ( RELAXED, 3,
    new BrainWaveScore( delta,     DIRECT  ),
    new BrainWaveScore( lowBeta,   INVERSE  ),
    new BrainWaveScore( highBeta,  INVERSE  )
    );

  _scoringArray[count++] = new StateScore ( DROWSY, 6,
    new BrainWaveScore( delta,     DIRECT ),
    new BrainWaveScore( theta,     INVERSE ),
    new BrainWaveScore( lowAlpha,  INVERSE ),
    new BrainWaveScore( highAlpha, INVERSE ),
    new BrainWaveScore( lowBeta,   INVERSE ),
    new BrainWaveScore( highBeta,  INVERSE )
    );
}
    
    
InternalState ScoreBoard::resolveOutput(void) {
  
  int i;
  int arraySize = sizeof(_scoringArray) / sizeof(StateScore*);
  
  float maxScore = 0.0f;
  InternalState result = NONE;
  
  if (!_stats->ready())
    return NONE;
    
  for (i = 0; i < arraySize; i++) {
    (_scoringArray[i])->calculate();
    
    Serial.print((_scoringArray[i])->getState());
    Serial.print(" ");
    Serial.println((_scoringArray[i])->getScore());
  }
  Serial.println();
  
  for (i = 0; i < arraySize; i++) {
    if ((_scoringArray[i])->getScore() > maxScore) {
      maxScore = (_scoringArray[i])->getScore();
      result = (_scoringArray[i])->getState();
    }
  }
  
  return result;
}


