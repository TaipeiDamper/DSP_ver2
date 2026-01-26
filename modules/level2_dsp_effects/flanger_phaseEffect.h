#pragma once
# include "delay_comb_allpass.h"
# include "oscillator.h"
# include "filter.h"


//Feedforward Flanger / Chorus
//核心就是用一個可變的短延遲（通常幾毫秒），再把原始訊號與延遲訊號相加。
//延遲時間用 LFO（Phasor）控制 SimpleDelay::setDelayInSec。
//公式：y[n] = x[n] + g * x[n - M(n)]，M(n) 為 LFO 控制的延遲樣本數。
class FFFlanger {
protected:
	Delay delay;
	float sampleRate;
	float basicDelayInSec;
	float maxDelayInSec;
	SinOsc sinOsc;
	float modRangeInSec = 0.0;
	float wet = 0.3f;

public:
	FFFlanger() {};
	
	void prepare(float sampleRate_) {
		sampleRate = sampleRate_;
		setMaxDelayInSec(0.02f); // preset
		basicDelayInSec = 0.005; // preset
		sinOsc.prepare(sampleRate_);
		sinOsc.setFreq(1.0f); // preset

	}

	void reset() {
		delay.reset();
		sinOsc.reset();
	}

	void setBasicDelayInSec(float basicDelayInSec_) {
		basicDelayInSec = basicDelayInSec_;
	}

	void setModulationRangeInSec(float modRangeInSec_) {
		modRangeInSec = modRangeInSec_;
		
		// prevent out of range
		// a. prevent < 0 
		if (basicDelayInSec - modRangeInSec < 0)  {
			modRangeInSec = basicDelayInSec;
		}
		// b. prevent > max delay
		if (basicDelayInSec + modRangeInSec > maxDelayInSec) {
			modRangeInSec = maxDelayInSec - basicDelayInSec;
		}

	}

	void setMaxDelayInSec(float maxDelayInSec_) {
		maxDelayInSec = maxDelayInSec_;
		delay.setMaxDelayInSec(maxDelayInSec);
	}

	void setModulationFreq(float modFreq_) {
		sinOsc.setFreq(modFreq_);
	}

	void setWet(float wet_) {
		wet = wet_;
	}

	virtual float processSample(float input_) {
		//FF: y[n] = x[n] + g*x[n-mod * M]
		//公式：y[n] = x[n] + g * x[n - M(n)]，M(n) 為 LFO 控制的延遲樣本數。
		// get Osc output and calculate delayInSec for this sample
		float nextDelayInSec = modRangeInSec * sinOsc.processSample() + basicDelayInSec;
		
		// set delayInSec and get sample;
		delay.setDelayInSec(nextDelayInSec);
		float bufferOutput = delay.readSample(); // automatically set input sample

		// set buffer input
		delay.writeSample(input_);

		float output = input_ * (1.0f - wet) + bufferOutput * wet;
		return output;
	}


};




//Feedback Flanger / Chorus
//和 Feedforward 差別在於延遲輸出再回饋到延遲線。
//公式：y[n] = x[n] + g * y[n - M(n)]，這和你的 FBCombFilter 一樣概念。
//注意回饋 gain 不要 >1，避免震盪。
class FBFlanger : public FFFlanger {
public:
	FBFlanger() {};
	virtual float processSample  (float input_) override {
		//公式：y[n] = x[n] + g * y[n - M(n)]，M(n) 
		// get Osc output and calculate delayInSec for this sample
		float nextDelayInSec = modRangeInSec * sinOsc.processSample() + basicDelayInSec;

		// set delayInSec and get sample;
		delay.setDelayInSec(nextDelayInSec);
		float bufferOutput = delay.readSample(); // automatically set input sample


		float output = input_ * (1.0f - wet) + bufferOutput * wet;

		// set buffer input
		delay.writeSample(output);

		return output;
	}
};





class PhaseEffect {
protected:
	float sampleRate = 44100.0f;
	int numStages = 4;
	std::vector<APF> apfs;
	std::vector<SinOsc> sinOscs;
	float fMin = 400.0f;
	float fMax = 2500.0f;
	float lfoFreq = 0.5f;
	float Q = 0.7f;
	float wet = 0.7;

public:
	PhaseEffect() {};
	void prepare(float sampleRate_) {
		sampleRate = sampleRate_;
		// initialize apfs and oscs
		apfs.resize(numStages);
		sinOscs.resize(numStages);
		
		for (auto& apf : apfs) {
			apf.prepare(sampleRate);
			apf.setQ(Q);
		}

		for (auto& sinOsc : sinOscs) {
			sinOsc.prepare(sampleRate);
			sinOsc.setFreq(lfoFreq);
		}

		// phase offset setting
		presetPhase();

	}

	void reset() {
		for (auto& apf : apfs) {
			apf.reset();
		}
		// dummy reset, yet written for future usage
		for (auto& sinOsc : sinOscs) {
			sinOsc.reset();
		}
		// phase offset setting, dummy as well
		presetPhase();
	}
	void presetPhase() {
		for (int i = 0; i < numStages; i++) {
			sinOscs[i].setPhase(float(i) / float(numStages));
		}
	}

	void setWet(float wet_) { wet = wet_; }

	float process(float input_) {
		float output = input_;

		for (int i = 0; i < numStages; i++) {
			// produce osc value
			float oscValue = sinOscs[i].processSample();
			float normalized = (oscValue + 1.0f) / 2.0f;
			float apfFreq = fMin + (fMax - fMin) * normalized;
			apfs[i].setFreq(apfFreq);
			// run apf through sample and update output
			output = apfs[i].processSample(output);
		}


		return output * wet + (1 - wet) * input_;
	}

};