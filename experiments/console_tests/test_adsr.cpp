// recall ADSR memory
#include <iostream>

enum class State { Idle, Attack, Decay, Sustain, Release };

class Envelope {
private:
  State state = State::Idle;

  float attackInSec = 0.5f;
  float decayInSec = 0.5f;
  float sustain = 0.5f;
  float releaseInSec = 0.5f;

  float attackDelta = 0.0f;
  float decayDelta = 0.0f;
  float releaseDelta = 0.0f;

  float currentLevel = 0.0f;

  float sampleRate = 44100.f;

public:
  Envelope() {}
  void prepare(float sampleRate_) {
    sampleRate = sampleRate_;
    updateDelta();
  }

  float processSample() {
    switch (state) {
    case State::Idle:
      currentLevel = 0.0f;
      break;
    case State::Attack:
      currentLevel += attackDelta;
      if (currentLevel >= 1.0f) {
        currentLevel = 1.0f;
        state = State::Decay;
      }
      break;
    case State::Decay:
      currentLevel -= decayDelta;
      if (currentLevel <= sustain) {
        currentLevel = sustain;
        state = State::Sustain;
      }
      break;
    case State::Sustain:
      currentLevel = sustain;
      break;
    case State::Release:
      currentLevel -= releaseDelta;
      if (currentLevel <= 0.0f) {
        currentLevel = 0.0f;
        state = State::Idle;
      }
      break;
    }
    return currentLevel;
  };

  void setAttack(float attackInSec_) {
    attackInSec = attackInSec_;
    updateDelta();
  }

  void setDelay(float delayInSec_) {
    decayInSec = delayInSec_;
    updateDelta();
  }

  void setSustain(float sustain_) {
    sustain = sustain_;
    updateDelta();
  }

  void setRelease(float releaseInSec_) {
    releaseInSec = releaseInSec_;
    updateDelta();
  }

  void updateDelta() {
    if (attackInSec < 0.0001f)
      attackInSec = 0.0001f;
    if (decayInSec < 0.0001f)
      decayInSec = 0.0001f;
    if (sustain < 0.0001f)
      sustain = 0.0001f;
    if (releaseInSec < 0.0001f)
      releaseInSec = 0.0001f;
    attackDelta = 1.0f / (attackInSec * sampleRate);
    decayDelta = (1.0f - sustain) / (decayInSec * sampleRate);
    releaseDelta = sustain / (releaseInSec * sampleRate);
  }

  void reset() {
    state = State::Idle;
    currentLevel = 0.0f;
  }

  void noteOn() { state = State::Attack; };
  void noteOff() { state = State::Release; };
};

int main() {
  Envelope adsr;
  adsr.prepare(44100.0f);
  adsr.setAttack(0.01f); // 10ms
  adsr.setSustain(0.5f);

  std::cout << "--- ADSR Test Start ---" << std::endl;
  adsr.noteOn();

  for (int i = 0; i < 10; ++i) {
    std::cout << "Sample " << i << ": " << adsr.processSample() << std::endl;
  }

  std::cout << "--- Test Complete ---" << std::endl;
  return 0;
}


