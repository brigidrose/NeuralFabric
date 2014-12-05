#ifndef BRAINWAVESTATS_H
#define BRAINWAVESTATS_H

#define SMOOTHING_FACTOR 10

class BrainWaveStats {
    public:
        BrainWaveStats();
        
        void update(float value);
        bool ready();
        float lastValue();
        float mean();
        float maxValue();
        float minValue();
        float smoothedValue();
        
    private:
        float _history[SMOOTHING_FACTOR];
        int _count;
        int _smoothedValue;
        float _value;
        float _mean;
        float _max;
        float _min;
};


#endif

