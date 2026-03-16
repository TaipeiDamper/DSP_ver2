#pragma once

// ADSR Envelope Generator
// Level 1 Building Block
// Integrated Version 2.0 (2026-02-23)

#include "paramSmoother.h"
class Envelope {
public:
    enum class State { Idle, Attack, Decay, Sustain, Release };
    enum class CurveType { Linear, Exponential };

private:
    State state = State::Idle;
    CurveType attackCurveType = CurveType::Linear;
    CurveType decayCurveType = CurveType::Linear;
    CurveType releaseCurveType = CurveType::Linear;

    ParamSmoother attackSmoother;
    ParamSmoother decaySmoother;
    ParamSmoother releaseSmoother;

    float attackInSec = 0.1f;
    float decayInSec = 0.5f;
    float sustain = 0.5f;
    float releaseInSec = 0.5f;

    float attackDelta = 0.0f;
    float decayDelta = 0.0f;
    float releaseDelta = 0.0f;

    float currentLevel = 0.0f;
    float sampleRate = 44100.0f;

public:
    Envelope() { updateDelta(); }

    void prepare(float newSampleRate) {
        sampleRate = newSampleRate;
        updateDelta();
        noteOff();
        attackSmoother.prepare(sampleRate);
        decaySmoother.prepare(sampleRate);
        releaseSmoother.prepare(sampleRate);
    }

    float processSample() {
        switch (state) {
        case State::Idle:
            currentLevel = 0.0f;
            break;

        case State::Attack:
            if (attackCurveType == CurveType::Linear) {
                currentLevel += attackDelta;
            } else {
                currentLevel = attackSmoother.processSample();
            }
            if (currentLevel >= 1.0f) {
                currentLevel = 1.0f;
                state = State::Decay;
                decaySmoother.setCurrentValue(currentLevel);
            }
            break;

        case State::Decay:
            if (decayCurveType == CurveType::Linear) {
                currentLevel -= decayDelta;
            } else {
                currentLevel = decaySmoother.processSample();
            }
            if (currentLevel <= sustain) {
                currentLevel = sustain;
                state = State::Sustain;
            }
            break;

        case State::Sustain:
            currentLevel = sustain;
            break;

        case State::Release:
            if (releaseCurveType == CurveType::Linear) {
                currentLevel -= releaseDelta;
            } else {
                currentLevel = releaseSmoother.processSample();
            }
            if (currentLevel <= 0.0f) {
                currentLevel = 0.0f;
                state = State::Idle;
            }
            break;
        }

        return currentLevel;
    }

    void updateDelta() {
        // Protect against short times causing infinity or division by zero
        float safeAttack = attackInSec < 0.0001f ? 0.0001f : attackInSec;
        float safeDecay = decayInSec < 0.0001f ? 0.0001f : decayInSec;
        float safeRelease = releaseInSec < 0.0001f ? 0.0001f : releaseInSec;

        attackDelta = 1.0f / (safeAttack * sampleRate);
        decayDelta = (1.0f - sustain) / (safeDecay * sampleRate);
        releaseDelta = 1.0f / (safeRelease * sampleRate);

        // exponential
        attackSmoother.setTimeToTarget(attackInSec);
        decaySmoother.setTimeToTarget(decayInSec);
        releaseSmoother.setTimeToTarget(releaseInSec);

        attackSmoother.setTarget(1.02f); // 1.02 force to reach target
        decaySmoother.setTarget(sustain);
        releaseSmoother.setTarget(-0.02f); // -0.02 force to reach target
    }

    // Setters
    void setAttack(float attackInSec_) {
        attackInSec = attackInSec_;
        updateDelta();
    }

    void setDecay(float decayInSec_) {
        decayInSec = decayInSec_;
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

    // External Controls
    void noteOn() {
        state = State::Attack;
        attackSmoother.setCurrentValue(currentLevel);
    }

    void noteOff() {
        state = State::Release;
        releaseSmoother.setCurrentValue(currentLevel);
    }

    void reset() {
        state = State::Idle;
        currentLevel = 0.0f;
        noteOff();
    }

    void setCurveType(CurveType attack, CurveType decay, CurveType release) {
        attackCurveType = attack;
        decayCurveType = decay;
        releaseCurveType = release;
    }

    void setAllCurveTypes(CurveType type) {
        attackCurveType = decayCurveType = releaseCurveType = type;
    }

    void setAttackCurveType(CurveType type) { attackCurveType = type; }
    void setDecayCurveType(CurveType type) { decayCurveType = type; }
    void setReleaseCurveType(CurveType type) { releaseCurveType = type; }

    State getState() const { return state; }
};
