//# pragma once

// simple delay (with ring buffer)

# include <vector>
# include "ringBuffer.h"


/*
simple delay
default: set maxDelay first, then set delay
*/
class Delay {
protected:
	float sampleRate = 44100;
	float delayInSec = 0.0f;
	float maxDelayInSec = 0.001f;

	// buffer part (replaced by DelayBuffer Class)
	RingBuffer buffer;
	float delayInSample;
	bool bufferIsInit = false;

public:
	Delay() {}

	void prepare(float sampleRate_) {
		sampleRate = sampleRate_;
	}

	// set delaytime at once
	void initDelay(float maxDelayInSec_, float delayInSec_) {
		setMaxDelayInSec(maxDelayInSec_);
		setDelayInSec(delayInSec_);
	}

	void reset() {
		buffer.reset();
	}

	void setDelayInSec(float delayInSec_) {
		delayInSec = delayInSec_;
		// check if input is legal, if not, force it to be legal
		if (delayInSec < 0) { delayInSec = 0.001; }
		if (!bufferIsInit) {
			maxDelayInSec = delayInSec + 0.01;
			bufferIsInit = true;
		}
		if (delayInSec > maxDelayInSec) { delayInSec = maxDelayInSec; }

		// calculate index
		delayInSample = delayInSec * sampleRate;

		bufferIsInit = true;
	}

	// set buffer total length
	void setMaxDelayInSec(float maxDelayInSec_) {
		maxDelayInSec = maxDelayInSec_;
		buffer.setBufferLength(floor(maxDelayInSec * sampleRate));

		bufferIsInit = true;
	}

	/*
	process single sample
	*/
	float processSample(float input_) {
		// read sample from buffer
		float output = readSample();
		// write sample into buffer
		writeSample(input_);

		return output;
	}

	float readSample() {	// read sample from buffer at readIdx
		return buffer.readSample(delayInSample);
	}
	void writeSample(float input_) {
		buffer.writeSample(input_);
	}


};




/*
y[n] = x[n] + g*x[n-M]
*/
class FFCombFilter {
protected:
	float sampleRate;
	float delayGain;
	Delay delay;

public:
	FFCombFilter() {};

	void prepare(float sampleRate_) {
		sampleRate = sampleRate_;
		delay.prepare(sampleRate_);
	}

	void setDelayGain(float delayGain_) {
		delayGain = delayGain_;
	}
	void setDelayInSec(float delayInSec_) {
		delay.setDelayInSec(delayInSec_);
	}
	void setMaxDelayInSec(float maxDelayInSec_) {
		delay.setMaxDelayInSec(maxDelayInSec_);
	}

	virtual float processSample(float input_) {
		float bufferOutput = delay.processSample(input_);
		// y[n] = x[n] + g*x[n-M]
		float output = input_ + delayGain * bufferOutput;
		return output;
	}

};


class FBCombFilter :public FFCombFilter {
protected:
	float sampleReadyForBuffer = 0.0f;
public:
	FBCombFilter() {};

	virtual float processSample(float input_) override {
		float bufferOutput = delay.processSample(sampleReadyForBuffer); // take in last output to process
		// y[n] = x[n] + g*y[n-m]
		float output = input_ + delayGain * bufferOutput;
		sampleReadyForBuffer = output;
		return output;
	}

	void reset() {
		sampleReadyForBuffer = 0.0f;
		delay.reset();
	}
};


class APF_delayLine :public FBCombFilter {
protected:
public:
	APF_delayLine() {};

	float processSample(float input_) override {
		float bufferOutput = delay.processSample(sampleReadyForBuffer); // take in last output to process
		// y[n] = -g*x[n] + ( x[n-M] +  g*y[n-m] )
		float output = -delayGain * input_ + bufferOutput;
		//(sampleReadyForBuffer) = ( x[n-M] +  g*y[n-m] )
		sampleReadyForBuffer = delayGain * output + input_;
		return output;

	}

};





