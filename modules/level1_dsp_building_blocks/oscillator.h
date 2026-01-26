// oscillator
# pragma once
# include <cmath>
# include "constant.h"

/* 2026 / 01 / 07
now it support getVal(offset) + phaseUpdate() for multichannel-phaseOffset tuning
*/

/*
simple Phasor, from 0 to 1
*/
class Phasor {
protected:
	float sampleRate = 44100.0f;
	float phase = 0.0f;
	float freq = 440.0f;
	float phaseDelta = 0.0f;
public:
	Phasor() {};

	void prepare(float sampleRate_) {
		sampleRate = sampleRate_;
		setFreq(freq);
	}

	void reset() {
		phase = 0.0f;
	}

	/*
	All-in-one function
	including process sample and phase increment
	*/
	float processSample() {
		float output = evalPhase(phase);
		phaseUpdate();
		return output;
	}

	/*
	get current osc value,
	support phase offset from 0~1
	*/
	float getVal(float phaseOffset = 0.0f) {
		return evalPhase(wrapPhase(phase + phaseOffset));
	}


	void setFreq(float freq_) {
		freq = freq_;
		phaseDelta = freq / sampleRate;
	}

	void setPhase(float phase_) {
		phase = phase_;
	}

	float getPhase() {
		return phase;
	}

	float getSampleRate() {
		return sampleRate;
	}

	/*
	phase update for next loop
	*/
	void phaseUpdate() {
		phase = wrapPhase(phase + phaseDelta);
	}
protected:
	/*
	update new sample,
	would be replaced in son class
	*/
	virtual float evalPhase(float phase_) {
		return phase_;
	}

	/*
	wrap the phase back to 0 and 1
	*/
	float wrapPhase(float phase_) {
		phase_ = std::fmodf(phase_, 1.0f);
		if (phase_ < 0.0f) phase_ += 1.0f;
		return phase_;
	}
};


class SinOsc :public Phasor {
protected:
	virtual float evalPhase(float phase_) override {
		return std::sin(2 * pi * phase_);
	}
};


class SquareOsc : public Phasor {
protected:
	virtual float evalPhase(float phase_) override {
		float output = 1.0f;
		if (phase_ >= 0.5) {
			output = -1.0f;
		}
		return output;
	}
};


class SawOsc :public Phasor {
protected:
	virtual float evalPhase(float phase_) override {
		return (1.0f - phase_) * 2 - 1.0f;
	}
};


class TriOsc : public Phasor {
protected:
	virtual float evalPhase(float phase_) override {
		return 4 * (std::abs(phase_ - 0.5) - 0.25);
	}

};


class AMOsc {
protected:
	SinOsc carrierOsc, modulatorOsc;
	float depth = 1.0;
	float sampleRate;
public:
	AMOsc() {};

	void prepare(float sampleRate_) {
		sampleRate = sampleRate_;
		carrierOsc.prepare(sampleRate_);
		modulatorOsc.prepare(sampleRate_);
		setCarrierOscFreq(440.0f); // set default value
		setModulatorOscFreq(1.0f); // set default value
	}

	void setCarrierOscFreq(float carrierFreq_) {
		carrierOsc.setFreq(carrierFreq_);
	}

	void setModulatorOscFreq(float modulatorFreq_) {
		modulatorOsc.setFreq(modulatorFreq_);
	}

	void setDepth(float depth_) {
		depth = depth_;
	}

	void reset() {
		carrierOsc.reset();
		modulatorOsc.reset();
	};

	virtual float processSample() {
		float c = carrierOsc.processSample();
		float m = modulatorOsc.processSample();
		return c * (1 + depth * m);
	}

	virtual float getVal(float phaseOffset_) {
		float c = carrierOsc.getVal(phaseOffset_);
		float m = modulatorOsc.getVal(phaseOffset_);
		return c * (1 + depth * m);
	}

	void phaseUpdate() {
		carrierOsc.phaseUpdate();
		modulatorOsc.phaseUpdate();
	}

};

// phase modulation
class PMOsc : public AMOsc {
protected:
	float baseFreq = 440.0f;
public:
	virtual float processSample() override {
		float fmValue = modulatorOsc.processSample() * depth; // mmodulated phase
		float fmPhase = fmValue / sampleRate;
		carrierOsc.setPhase(carrierOsc.getPhase() + fmPhase);
		return carrierOsc.processSample();
	}

	virtual float getVal(float phaseOffset_) override {
		float fmValue = modulatorOsc.getVal(phaseOffset_) * depth;
		float fmPhase = fmValue / sampleRate;
		return carrierOsc.getVal(carrierOsc.getPhase() + fmPhase + phaseOffset_);
	}

	void setCarrierOscBasicFreq(float carrierOscBasicFreq_) {
		baseFreq = carrierOscBasicFreq_;
		carrierOsc.setFreq(baseFreq);
	}

};


// Frequency modulation
class FMOsc :public PMOsc {
public:
	float processSample() override {
		float fmHz = modulatorOsc.processSample() * depth; // modulated frequency offset in Hz
		carrierOsc.setFreq(baseFreq + fmHz);
		return carrierOsc.processSample();
	}

	float getVal(float phaseOffset_) override {
		float fmHz = modulatorOsc.getVal(phaseOffset_) * depth;
		carrierOsc.setFreq(baseFreq + fmHz);
		return carrierOsc.getVal(phaseOffset_);
	}
};
