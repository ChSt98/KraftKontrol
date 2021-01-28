#ifndef LOW_PASS_FILTER_H
#define LOW_PASS_FILTER_H



#include "definitions.h"

#include "CircularBuffer.h"


template<typename T>
class LowPassFilter {
public:


    /**
     * Give sampleRate to improve performance
     *
     * @param values cutOffFreq and sampleRate
     * @return none.
     */
    LowPassFilter(float cutOffFreq, uint32_t sampleRate = -1) {

        _sampleRate = sampleRate;
        _cutOffFreq = cutOffFreq;
        float RC = 1.0/(cutOffFreq*2*3.14);

        if (_sampleRate != -1) {
            float dt = 1.0/_sampleRate;
            _alpha = dt/(RC+dt);
        }

    }


    /**
     *
     * @param values input value
     * @return filtered value.
     */
    T update(T input) {
        
        if (_sampleRate == -1) {
            float dt = 1.0/(micros() - _lastRun);
            _alpha = dt/(_RC+dt);
        }

        T output = _lastValue + _alpha*(input - _lastValue);
        _lastValue = output;

        return output;

    }


    /**
     * Timestamp of input value (in microseconds) to improve accuracy.
     * This overrides the sampling input at constructor.
     *
     * @param values input value and timestamp in microseconds
     * @return filtered value.
     */
    T update(T input, uint32_t timestampUS) {
        
        float dt = 1.0/(timestampUS - _lastRun);
        _alpha = dt/(_RC+dt);

        T output = _lastValue + _alpha*(input - _lastValue);
        _lastValue = output;

        return output;

    }


private:

    uint32_t _sampleRate;
    float _cutOffFreq;
    float _RC;

    float _alpha;

    T _lastValue;
    uint32_t _lastRun = 0;
    //filteredArray[i] = filteredArray[i-1] + (alpha*(data.recordedSamples[i] - filteredArray[i-1]));


};



#endif