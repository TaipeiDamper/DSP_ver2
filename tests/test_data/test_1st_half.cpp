// 在這裡測試module
// 輸出結果給test_2nd_half.py去作圖+聽+看效果

// # include 要測試的module
#include "SimpleWavIO.h" // 必須保留標頭檔才能呼叫 writeWav
#include "filter.h"
#include <iostream>
#include <vector>

int main() {
  // for setting
  float sampleRate = 44100.0f;
  float durationInSec = 2.0f;

  int numSamples = (int)(durationInSec * sampleRate);

  // set impulse input
  std::vector<float> input(numSamples, 0.0f);
  input[0] = 1.0f;

  // output container
  std::vector<float> output(numSamples, 0.0f);

  // dsp start
  LPF lpf;
  lpf.prepare(sampleRate);
  lpf.setFreq(1000.0f);
  lpf.setQ(0.707f);
  lpf.setGain(0.0f);

  // process
  for (int i = 0; i < numSamples; i++) {
    output[i] = lpf.processSample(input[i]);
  }

  // Save WAV only
  if (writeWav("filter_ir_results.wav", output, (int)sampleRate, 1)) {
    std::cout << "Successfully saved to WAV." << std::endl;
  } else {
    std::cerr << "Failed to save WAV." << std::endl;
  }

  return 0;
}