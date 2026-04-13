// learn to keep code to be clear

#include <cmath>
#include <iostream>
#include <vector>

class MyDelay
{

private:
    // 01 constant
    float sampleRate{44100.0f};
    int maxDelayInSample{0};

    // 03 DSP state
    std::vector<float> buffer;
    int writeIndex{0};
    float delayInSample{0.0f};
    float feedback{0.5f};

public:
    MyDelay() {};

    void prepare(float sampleRate_)
    {
        sampleRate = sampleRate_;
    };

float processSample(float input_)
    {
        // 1. read from buffer and interpolate
        float bufferOutput = getInterploatedSample(delayInSample);
        // 2. write input into buffer with feedback(ratio)
        writeSampleIntoBuffer(input_ + bufferOutput * feedback);
        // 3. Advance Index
        advanceReadIndex();
        // 4. return
        return bufferOutput;
    };
    void reset()
    {
        // reset buffer and index
        buffer.assign(maxDelayInSample, 0.0f);
        writeIndex = 0;
    };

    //
float getInterploatedSample(float delayInSample_)
    {
        float readIndex = writeIndex - delayInSample_;
        int readIndexLeft = static_cast<int>(std::floorf(readIndex));
        float ratio = readIndex - (float)readIndexLeft;
        int readIndexRight = readIndexLeft + 1;
        wrapIndex(readIndexLeft);
        wrapIndex(readIndexRight);

        float interpolatedOutput = buffer[readIndexLeft] + (buffer[readIndexRight] - buffer[readIndexLeft]) * ratio;
        return interpolatedOutput;
    };

    //
void writeSampleIntoBuffer(float input_)
    {
        buffer[writeIndex] = input_;
    };

    // setter
void setDelayInSec(float delayInSecond_)
    {
        delayInSample = delayInSecond_ * sampleRate;
    }

void setMaxDelayInSec(float maxDelayInSecond_)
    {
        maxDelayInSample = static_cast<int>(std::floorf(maxDelayInSecond_ * sampleRate));
    }

private:
    // set index to next step
void advanceReadIndex()
    {
        writeIndex += 1;
        wrapIndex(writeIndex);
    }

    // wrap index
void wrapIndex(int &index)
    {
        index = (index + maxDelayInSample) % maxDelayInSample;
    };
void wrapIndex(float &index)
    {
        index = std::fmod(index + (float)maxDelayInSample, (float)maxDelayInSample);
    };
};
