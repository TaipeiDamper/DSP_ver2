// not complete
#include <cmath>

class Compressor {
protected:
  float sampleRate = 44100.0f;
  float attackInSec = 0.005f;
  float releaseInSec = 0.02f;
  float attackAlpha = 0.0001f;
  float releaseAlpha = 0.0001f;
  float lastSample = 0.0f;
  float envelope = 1.0f;
  float threshold = 0.5f;
  float ratio = 2.0f;
  float gain = 1.0f;

public:
  Compressor() {};
  void prepare(float sampleRate) { sampleRate = sampleRate; };
  void reset() {};

  float processSample(float input_) {
    float inputAbs = std::abs(input_);

    // 1. detect input to decide which alpha to use
    float currentAlpha =
        (inputAbs > std::abs(lastSample)) ? attackAlpha : releaseAlpha;
    lastSample = input_;

    // 2. detect input to produce envelope (which represent current volume
    // level)
    envelope = (1.0f - currentAlpha) * inputAbs + currentAlpha * envelope;

    // 3. apply compression to envelope
    float targetLevel = 0.0f;
    if (envelope > threshold) {
      targetLevel = threshold + (envelope - threshold) / ratio;
    } else {
      targetLevel = envelope;
    }

    // 4. apply gain and envelope to input
    float compressRatio = envelope > 0.0001f ? (targetLevel / envelope) : 1.0f;
    float output = gain * input_ * compressRatio;

    return output;
  };
  void processBlock(float *buffer, int numSamples) {};

  // setters =============================================================
  void setAttackInSec(float attackInSec_) {
    attackInSec = attackInSec_;
    updateAlphas();
  }
  void setReleaseInSec(float releaseInSec_) {
    releaseInSec = releaseInSec_;
    updateAlphas();
  }

private:
  void updateAlphas() {
    // pre-calculate the exponential smoothing factors
    // since normal alpha would only bring 63% change in time t
    // multiplied the value by 5 to make it faster
    attackAlpha = std::exp(-2.2f / (sampleRate * attackInSec));
    releaseAlpha = std::exp(-2.2f / (sampleRate * releaseInSec));
  }
};