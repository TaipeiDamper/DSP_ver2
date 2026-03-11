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

public:
  Compressor() {};
  void prepare(float sampleRate) { sampleRate = sampleRate; };
  void reset() {};
  float processSample(float input) { return input; };
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
    attackAlpha = std::exp(-5.0f / (sampleRate * attackInSec));
    releaseAlpha = std::exp(-5.0f / (sampleRate * releaseInSec));
  }
};