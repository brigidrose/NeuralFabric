#ifndef BRAINWAVESTATS_H
#define BRAINWAVESTATS_H


class BrainWaveStats {
    public:
        BrainWaveStats(int smoothing);
        
        void update(float value); // Process new value
        bool ready();             // Have we processed as many values as smoothing requires 
        
        float lastValue();        // Most recent value processed
        float meanValue();        // Average of all values processed so far
        float maxValue();         // Maximum of all values processed so far
        float minValue();         // Minimum of all values processed so far
        
        float smoothedValue();    // Average of the most recent smoothing count values processed
        
    private:
        float* _array;
        int _count;
        int _smoothing;
        float _smoothedValue;
        float _value;
        float _mean;
        float _max;
        float _min;
        
        float processSmoothing(float value);
};


#endif

