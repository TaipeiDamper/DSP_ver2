// 2026/05/12 rewrite ADSR

// ADSR
// ADSR is a type of envelope generator that is used to shape the amplitude of a
// sound. It is composed of four stages: Attack, Decay, Sustain, and Release.
// Attack is the time it takes for the sound to reach its maximum amplitude.
// Decay is the time it takes for the sound to decay from its maximum amplitude
// to its sustain level. Sustain is the level at which the sound is held after
// the attack and decay stages. Release is the time it takes for the sound to
// decay from its sustain level to zero.

class Envelope {
private:
  float attack = 0.1f;
  float decay = 0.5f;
  float sustain = 0.5f;
  float release = 0.1f;

  float attackDelta = 0.0f;
  float decayDelta = 0.0f;
  float releaseDelta = 0.0f;

  float sampleRate = 44100.0f;

  // state machine
  enum state { Idle, Attack, Decay, Sustain, Release };
  state currentState = Idle;

  float currentValue = 0.0f;

public:
  Envelope() {};

  float processSample(float input) {
    switch (currentState) {
    case Idle:
      break;
    case Attack:
      currentValue += attackDelta;
      if (currentValue > 1.0f) {
        currentValue = 1.0f;
        currentState = Decay;
      }
      break;
    case Decay:
      currentValue += decayDelta;
      if (currentValue < sustain) {
        currentValue = sustain;
        currentState = Sustain;
      }
      break;
    case Sustain:
      break;
    case Release:
      currentValue += releaseDelta;
      if (currentValue < 0.0f) {
        currentValue = 0.0f;
        currentState = Idle;
      }
    }

    return currentValue;
  };

  void updateDelta() {
    if (attack < 0.0001f)
      attack = 0.0001f;
    if (decay < 0.0001f)
      decay = 0.0001f;
    if (sustain < 0.0001f)
      sustain = 0.0001f;
    if (release < 0.0001f)
      release = 0.0001f;
    attackDelta = 1.0f / (attack * sampleRate);
    decayDelta = -(1.0f - sustain) / (decay * sampleRate);
    releaseDelta = -sustain / (release * sampleRate);
  }

  void setAttack(float attack_) {
    attack = attack_;
    updateDelta();
  }

  void setDecay(float decay_) {
    decay = decay_;
    updateDelta();
  }

  // sustain doesn't need to update delta
  void setSustain(float sustain_) {
    sustain = sustain_;
    updateDelta();
  }

  void setRelease(float release_) {
    release = release_;
    updateDelta();
  }

  // external control noteOn
  void noteOn() { currentState = Attack; }

  // external control noteOff
  void noteOff() { currentState = Release; }

  void prepare(float sampleRate_) {
    sampleRate = sampleRate_;
    updateDelta();
  };

  void reset() { currentState = Idle; }
};