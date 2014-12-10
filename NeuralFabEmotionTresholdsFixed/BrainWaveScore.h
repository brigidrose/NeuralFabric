#ifndef BRAINWAVESCORE_H
#define BRAINWAVESCORE_H

enum BrainWaveScoring {
  DIRECT, INVERSE, MEAN_PEAK
};

class BrainWaveScore {
    public:
        BrainWaveScore(BrainWaveStats* stats, BrainWaveScoring scoring);
        
        float calculate(float fraction);
        
    private:
        BrainWaveStats* _stats;
        BrainWaveScoring _scoring;
        float _scalingFactor;
        
        float _statsRange;
        
        float scoreDirect(float value);
        float scoreInverse(float value);
        float scoreMeanPeak(float value);
};


#endif
