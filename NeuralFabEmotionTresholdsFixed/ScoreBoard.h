#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "RainbowOutput.h"
#include "StateScore.h"
#include "BrainWaveStats.h"

class ScoreBoard {
  public:
    ScoreBoard(
      BrainWaveStats* theta,
      BrainWaveStats* delta,
      BrainWaveStats* lowAlpha,
      BrainWaveStats* highAlpha,
      BrainWaveStats* lowBeta,
      BrainWaveStats* highBeta );
    
    InternalState resolveOutput(void);
    
  private:
    BrainWaveStats* _stats;
  
    StateScore* _scoringArray[(INTERNAL_STATE_COUNT-1)];

};



#endif

