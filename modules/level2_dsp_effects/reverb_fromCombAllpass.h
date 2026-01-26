# pragma once

# include "delay_comb_allpass.h"


class SchroederReverb {
	/*
	# | Comb Filter | Delay Time (ms) | Gain (feedback) |
	# | ----------- | --------------- | --------------- |
	# | Comb 1      | 29.7            | 0.805           |
	# | Comb 2      | 37.1            | 0.827           |
	# | Comb 3      | 41.1            | 0.783           |
	# | Comb 4      | 43.7            | 0.764           |
	# | All-Pass Filter | Delay Time (ms) | Gain |
	# | --------------- | --------------- | ---- |
	# | APF 1           | 5.0             | 0.7  |
	# | APF 2           | 1.7             | 0.7  |
	*/
protected:
	float sampleRate = 44100;
	FBCombFilter comb1, comb2, comb3, comb4;
	APF_delayLine apf1, apf2;

public:
	SchroederReverb() {};
	void prepare(float sampleRate_) {
		sampleRate = sampleRate_;
		comb1.prepare(sampleRate);
		comb2.prepare(sampleRate);
		comb3.prepare(sampleRate);
		comb4.prepare(sampleRate);
		apf1.prepare(sampleRate);
		apf2.prepare(sampleRate);

		// set preset param
		comb1.setMaxDelayInSec(0.1);
		comb1.setDelayInSec(0.0297);
		comb1.setDelayGain(0.805);

		comb2.setMaxDelayInSec(0.1);
		comb2.setDelayInSec(0.0371);
		comb2.setDelayGain(0.827);

		comb3.setMaxDelayInSec(0.1);
		comb3.setDelayInSec(0.0411);
		comb3.setDelayGain(0.783);

		comb4.setMaxDelayInSec(0.1);
		comb4.setDelayInSec(0.0437);
		comb4.setDelayGain(0.764);

		apf1.setMaxDelayInSec(0.1);
		apf1.setDelayInSec(0.005);
		apf1.setDelayGain(0.7);

		apf2.setMaxDelayInSec(0.1);
		apf2.setDelayInSec(0.0017);
		apf2.setDelayGain(0.7);
	}

	void reset() {
		comb1.reset();
		comb2.reset();
		comb3.reset();
		comb4.reset();
		apf1.reset();
		apf2.reset();
	}

	float processSample(float input_) {
		float output = 0;
		// 4 fb parallel
		output = comb1.processSample(input_) + comb2.processSample(input_) + comb3.processSample(input_) + comb4.processSample(input_);

		// 2 apf series
		output = apf1.processSample(output);
		output = apf2.processSample(output);

		return output;
	}

};

