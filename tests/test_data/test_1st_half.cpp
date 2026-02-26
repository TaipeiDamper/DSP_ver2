// 在這裡測試module
// 輸出結果給test_2nd_half.py去作圖+聽+看效果

// # include 要測試的module
#include "../../modules/level1_dsp_building_blocks/filter.h"
#include <vector>

int main() {

  // for setting
  float sampleRate = 44100.0f;
  float durationInSec = 5.0f;

  int numSamples = durationInSec * sampleRate;

  // set impulse input
  std::vector<float> input(numSamples, 0.0f);
  input[0] = 1.0f;

  // dsp start
  LPF lpf;
  lpf.prepare(sampleRate);
  lpf.setFreq(1000.0f);
  lpf.setQ(0.707f);
  lpf.setGain(0.0f);

  for (int i = 0; i < numSamples; i++) {
  }

  return 0;
}