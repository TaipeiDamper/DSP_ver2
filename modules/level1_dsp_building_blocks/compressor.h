// not complete

class Compressor {
protected:
  float sampleRate = 44100.0f;
  float attackInSec = 0.005f;
  float releaseInSec = 0.02f;
  float attackAlpha = 0.0001f;
  float releaseAlpha = 0.0001f;

public:
  Compressor() {};
  void prepare(float sampleRate) { sampleRate = sampleRate; };
  void reset() {};
  float processSample(float input) { return input; };
  void processBlock(float *buffer, int numSamples) {};

private:
};