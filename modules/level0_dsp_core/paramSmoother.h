

#include <cmath>
class ParamSmoother {
protected:
    float sampleRate = 44100.0f;
    float t = 0.2f;
    float alpha = 0.0f;
    float y1 = 0.0f;
    float targetValue = 0.0f;

public:
    ParamSmoother() {}
    void prepare(float sampleRate_) {
        sampleRate = sampleRate_;
        setAlpha();
    }
    void reset() {
        y1 = 0.0f;
        targetValue = 0.0f;
    }
    float processSample() {
        // thresholding
        if (std::abs(targetValue - y1) < 1e-6f) {
            y1 = targetValue;
            return y1;
        }

        float y = y1 + alpha * (targetValue - y1);
        y1 = y;
        return y;
    }
    void setTarget(float newTargetValue) { targetValue = newTargetValue; }

    void processBlock(float *buffer, int numSamples) {
        for (int i = 0; i < numSamples; i++) {
            buffer[i] = processSample();
        }
    }

    void setCurrentValue(float value) { y1 = value; }

    void setTimeToTarget(float timeInSec) {
        // 5.0f is the factor that the value will approach to target value by 99%
        const float toTarget99Factor = 5.0f;
        setTimeConst(timeInSec / toTarget99Factor);
    }

protected:
    // update change coeff of approaching line
    void setAlpha() { alpha = 1.0f - expf(-1.0f / (t * sampleRate)); }

    // set time const for updating
    // over "t" sec, the value will approach to target value by 63.2%
    void setTimeConst(float t_) {
        t = t_;
        if (t < 0.0001f) {
            t = 0.0001f;
        }
        setAlpha();
    }
};
