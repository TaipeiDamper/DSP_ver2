// not complete
#include <cmath>

class Compressor
{
  protected:
    float sampleRate = 44100.0f;
    float coeff = 0.0f;
    float attackInSec = 0.01f;
    float releaseInSec = 0.1f;
    float attackCoeff = 0.0f;
    float releaseCoeff = 0.0f;
    float envelope = 0.0f;

    float threshold = 0.5f;
    float ratio = 4.0f;
    float makeupGain = 1.0f;

  public:
    Compressor() {};

    void prepare(float sampleRate_)
    {
        sampleRate = sampleRate_;
        updateAlphas();
    }

    float processSample(float input_)
    {
        // 01 Envelope follower
        float inputAbs = std::abs(input_);
        float coeff = (inputAbs > envelope) ? attackCoeff : releaseCoeff;
        envelope = (1.0f - coeff) * inputAbs + coeff * envelope;

        // 02 Gain Compute
        float gain = (envelope > threshold) ? (threshold + (envelope - threshold) / ratio) / envelope : 1.0f;

        // 03 Gain Application
        float output = input_ * gain * makeupGain;
        return output;
    }

    // setter
    void setThreshold(float threshold_)
    {
        threshold = threshold_;
    }
    void setRatio(float ratio_)
    {
        ratio = ratio_;
    }
    void setMakeupGain(float makeupGain_)
    {
        makeupGain = makeupGain_;
    }
    void setAttackInSec(float attackInSec_)
    {
        attackInSec = attackInSec_;
        updateAlphas();
    }
    void setReleaseInSec(float releaseInSec_)
    {
        releaseInSec = releaseInSec_;
        updateAlphas();
    }

  protected:
    void updateAlphas()
    {
        attackCoeff = std::exp(-2.2f / (sampleRate * attackInSec));
        releaseCoeff = std::exp(-2.2f / (sampleRate * releaseInSec));
    }
};