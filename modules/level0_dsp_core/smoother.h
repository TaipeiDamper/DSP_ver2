#include <cmath>

class ParamSmoother {
protected:
  float t = 0.2f;
  float alpha = 0.0f;
  float sampleRate = 44100.0f;
  float y1 = 0.0f;

public:
  ParamSmoother() {};

  void prepare(float sampleRate_) {
    sampleRate = sampleRate_;
    calAlpha();
  }

  void reset() {
    y1 = 0.0f;
    calAlpha();
  };

  float processSample(float input_) {
    float y = (1 - alpha) * y1 + alpha * input_;

    // check if |y - input| is too small
    if (std::abs(y - input_) < 1e-6f) {
      y = input_;
    }

    y1 = y; // pass to next calculate
    return y;
  }

  float processBlock(float input_, float blocksize) {
    for (int i = 0; i < blocksize; i++) {
      input_ = processSample(input_);
    }
    return input_;
  }

  void setTimeConst(float t_) {
    t = t_;
    calAlpha();
  }

protected:
  void calAlpha() { alpha = 1.0f - std::expf(-1.0f / (t * sampleRate)); }
};