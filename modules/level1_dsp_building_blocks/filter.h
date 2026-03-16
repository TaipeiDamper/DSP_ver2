// from audio handbook

#pragma once
#include "constant.h"
#include <cmath>
#include <iostream>
#include <vector>

class Biquad {
public:
    enum class Type { LPF, HPF, BPF, Notch, Peaking, LShelf, HShelf, APF };

private:
    Type type = Type::LPF;
    float sampleRate = 44100.0f;
    float freq = 1000.0f;
    float Q = 0.707f;
    float dBGain = 0.0f;

    // Intermediate coefficients
    float b0 = 1.0f, b1 = 0.0f, b2 = 0.0f;
    float a0 = 1.0f, a1 = 0.0f, a2 = 0.0f;

    // Final coefficients (normalized by a0)
    float B0 = 1.0f, B1 = 0.0f, B2 = 0.0f;
    float A1 = 0.0f, A2 = 0.0f;

    // State registers (previous samples)
    float x1 = 0.0f, x2 = 0.0f, y1 = 0.0f, y2 = 0.0f;

public:
    Biquad() { updateCoeff(); }

    void prepare(float newSampleRate) {
        sampleRate = newSampleRate;
        updateCoeff();
    }

    void reset() { x1 = x2 = y1 = y2 = 0.0f; }

    // --- Parameter Setters ---
    void setType(Type newType) {
        if (type != newType) {
            type = newType;
            reset(); // Protect against clicks when changing modes
            updateCoeff();
        }
    }

    void setFreq(float newFreq) {
        freq = newFreq;
        updateCoeff();
    }

    void setQ(float newQ) {
        Q = newQ;
        updateCoeff();
    }

    void setGain(float newDBGain) {
        dBGain = newDBGain;
        updateCoeff();
    }

    // --- Semantic Shortcuts (Easy to remember) ---
    void setLPF(float f, float q) {
        type = Type::LPF;
        freq = f;
        Q = q;
        reset();
        updateCoeff();
    }
    void setHPF(float f, float q) {
        type = Type::HPF;
        freq = f;
        Q = q;
        reset();
        updateCoeff();
    }
    void setBPF(float f, float q) {
        type = Type::BPF;
        freq = f;
        Q = q;
        reset();
        updateCoeff();
    }
    void setNotch(float f, float q) {
        type = Type::Notch;
        freq = f;
        Q = q;
        reset();
        updateCoeff();
    }
    void setPeaking(float f, float q, float gain) {
        type = Type::Peaking;
        freq = f;
        Q = q;
        dBGain = gain;
        reset();
        updateCoeff();
    }
    void setLShelf(float f, float q, float gain) {
        type = Type::LShelf;
        freq = f;
        Q = q;
        dBGain = gain;
        reset();
        updateCoeff();
    }
    void setHShelf(float f, float q, float gain) {
        type = Type::HShelf;
        freq = f;
        Q = q;
        dBGain = gain;
        reset();
        updateCoeff();
    }

    // --- Processing ---
    float processSample(float input) {
        float output = B0 * input + B1 * x1 + B2 * x2 - A1 * y1 - A2 * y2;

        x2 = x1;
        x1 = input;
        y2 = y1;
        y1 = output;

        return output;
    }

    void processBlock(float *buffer, int numSamples) {
        for (int i = 0; i < numSamples; i++) {
            buffer[i] = processSample(buffer[i]);
        }
    }

private:
    void updateCoeff() {
        float w0 = 2.0f * pi * freq / sampleRate;
        float alpha = sin(w0) / (2.0f * Q);
        float cos_w0 = cos(w0);
        float A = pow(10.0f, dBGain / 40.0f); // Square root of 10^(dB/20)

        switch (type) {
        case Type::LPF:
            b0 = (1.0f - cos_w0) / 2.0f;
            b1 = 1.0f - cos_w0;
            b2 = (1.0f - cos_w0) / 2.0f;
            a0 = 1.0f + alpha;
            a1 = -2.0f * cos_w0;
            a2 = 1.0f - alpha;
            break;

        case Type::HPF:
            b0 = (1.0f + cos_w0) / 2.0f;
            b1 = -(1.0f + cos_w0);
            b2 = (1.0f + cos_w0) / 2.0f;
            a0 = 1.0f + alpha;
            a1 = -2.0f * cos_w0;
            a2 = 1.0f - alpha;
            break;

        case Type::BPF:
            b0 = alpha;
            b1 = 0.0f;
            b2 = -alpha;
            a0 = 1.0f + alpha;
            a1 = -2.0f * cos_w0;
            a2 = 1.0f - alpha;
            break;

        case Type::Notch:
            b0 = 1.0f;
            b1 = -2.0f * cos_w0;
            b2 = 1.0f;
            a0 = 1.0f + alpha;
            a1 = -2.0f * cos_w0;
            a2 = 1.0f - alpha;
            break;

        case Type::APF:
            b0 = 1.0f - alpha;
            b1 = -2.0f * cos_w0;
            b2 = 1.0f + alpha;
            a0 = 1.0f + alpha;
            a1 = -2.0f * cos_w0;
            a2 = 1.0f - alpha;
            break;

        case Type::Peaking:
            b0 = 1.0f + alpha * A;
            b1 = -2.0f * cos_w0;
            b2 = 1.0f - alpha * A;
            a0 = 1.0f + alpha / A;
            a1 = -2.0f * cos_w0;
            a2 = 1.0f - alpha / A;
            break;

        case Type::LShelf:
            b0 = A * ((A + 1.0f) - (A - 1.0f) * cos_w0 + 2.0f * sqrt(A) * alpha);
            b1 = 2.0f * A * ((A - 1.0f) - (A + 1.0f) * cos_w0);
            b2 = A * ((A + 1.0f) - (A - 1.0f) * cos_w0 - 2.0f * sqrt(A) * alpha);
            a0 = (A + 1.0f) + (A - 1.0f) * cos_w0 + 2.0f * sqrt(A) * alpha;
            a1 = -2.0f * ((A - 1.0f) + (A + 1.0f) * cos_w0);
            a2 = (A + 1.0f) + (A - 1.0f) * cos_w0 - 2.0f * sqrt(A) * alpha;
            break;

        case Type::HShelf:
            b0 = A * ((A + 1.0f) + (A - 1.0f) * cos_w0 + 2.0f * sqrt(A) * alpha);
            b1 = -2.0f * A * ((A - 1.0f) + (A + 1.0f) * cos_w0);
            b2 = A * ((A + 1.0f) + (A - 1.0f) * cos_w0 - 2.0f * sqrt(A) * alpha);
            a0 = (A + 1.0f) - (A - 1.0f) * cos_w0 + 2.0f * sqrt(A) * alpha;
            a1 = 2.0f * ((A - 1.0f) - (A + 1.0f) * cos_w0);
            a2 = (A + 1.0f) - (A - 1.0f) * cos_w0 - 2.0f * sqrt(A) * alpha;
            break;
        }

        // Normalize
        B0 = b0 / a0;
        B1 = b1 / a0;
        B2 = b2 / a0;
        A1 = a1 / a0;
        A2 = a2 / a0;
    }
};
