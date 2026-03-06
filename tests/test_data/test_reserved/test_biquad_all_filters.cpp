// 在這裡測試module
// 輸出結果給test_2nd_half.py去作圖+聽+看效果

// # include 要測試的module
#include "SimpleWavIO.h" // 必須保留標頭檔才能呼叫 writeWav
#include "filter.h"
#include <functional>
#include <iostream>
#include <string>
#include <vector>


int main() {
  // for setting
  float sampleRate = 44100.0f;
  float durationInSec = 2.0f;

  int numSamples = (int)(durationInSec * sampleRate);

  // set impulse input
  std::vector<float> input(numSamples, 0.0f);
  input[0] = 1.0f; // True impulse

  // dsp start
  Biquad filter;
  filter.prepare(sampleRate);

  float testFreq = 1000.0f;
  float testQ = 0.7071f; // Butterworth Q
  float testGain = 6.0f;

  struct FilterTest {
    std::string name;
    std::function<void()> setup;
  };

  FilterTest tests[] = {
      {"LPF", [&]() { filter.setLPF(testFreq, testQ); }},
      {"HPF", [&]() { filter.setHPF(testFreq, testQ); }},
      {"BPF", [&]() { filter.setBPF(testFreq, testQ); }},
      {"Notch", [&]() { filter.setNotch(testFreq, testQ); }},
      {"Peaking", [&]() { filter.setPeaking(testFreq, testQ, testGain); }},
      {"LShelf", [&]() { filter.setLShelf(testFreq, testQ, testGain); }},
      {"HShelf", [&]() { filter.setHShelf(testFreq, testQ, testGain); }}};

  for (const auto &t : tests) {
    t.setup();
    // process
    std::vector<float> output(numSamples, 0.0f);
    for (int i = 0; i < numSamples; i++) {
      output[i] = filter.processSample(input[i]);
    }

    std::string filename = "testOutput_" + t.name + ".wav";
    if (writeWav(filename.c_str(), output, (int)sampleRate, 1)) {
      std::cout << "Successfully saved " << filename << std::endl;
    } else {
      std::cerr << "Failed to save " << filename << std::endl;
    }
  }

  return 0;
}