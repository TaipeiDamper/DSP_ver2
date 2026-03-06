// not complete

class Compressor {
protected:
  float sampleRate = 44100.0f;

public:
  Compressor() {};
  void prepare(float sampleRate) {};
  void reset() {};
  float processSample(float input) { return input; };
  void processBlock(float *buffer, int numSamples) {};

private:
};