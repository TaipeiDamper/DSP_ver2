#pragma once

class Gain {
protected:
  float gain = 1.0f;
  float sampleRate = 44100; // redundant

public:
  Gain() {}
  void setGain(float gain_) { gain = gain_; }
  float processSample(float input_) { return input_ * gain; }
  void prepare(float sampleRate_) { sampleRate = sampleRate_; }
};