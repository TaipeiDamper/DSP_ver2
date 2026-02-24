

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
  void reset() { y1 = 0.0f; }
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

  void setTimeConst(float t_) {
    t = t_;
    if (t < 0.001f) {
      t = 0.001f;
    }
    setAlpha();
  }

  void processBlock(float *buffer, int numSamples) {
    for (int i = 0; i < numSamples; i++) {
      buffer[i] = processSample();
    }
  }

  void jumpToTarget() { y1 = targetValue; }

protected:
  void setAlpha() { alpha = 1.0f - expf(-1.0f / (t * sampleRate)); }
};