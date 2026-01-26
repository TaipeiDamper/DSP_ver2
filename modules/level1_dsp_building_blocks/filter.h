// from audio handbook

# pragma once
# include <vector>
# include <iostream>
# include "constant.h"


struct FilterCoeff {
	float sampleRate = 44100;
	float freq = 1000;
	float Q = 0.707;
	float dBGain = 0.0;
};

// parent class of all filters
class Filter {
protected:
	float sampleRate = 44100;

	// raw biquad coefficient
	float a0 = 1.0f, a1 = 0.0f, a2 = 0.0f, b0 = 0.0f, b1 = 0.0f, b2 = 0.0f;

	// computed coefficient
	float A1 = 0.0f, A2 = 0.0f, B0 = 0.0f, B1 = 0.0f, B2 = 0.0f;

	// previous sample
	float x1 = 0.0f, x2 = 0.0f, y1 = 0.0f, y2 = 0.0f;

	// other coefficient
	float Q = 0.707f, w0 = 0.0f, freq = 0.0f, alpha = 0, A = 1.0f;

public:
	Filter() {}
	void prepare(float sampleRate_) {
		sampleRate = sampleRate_;
	}

	void reset() {
		x1 = 0.0f, x2 = 0.0f, y1 = 0.0f, y2 = 0.0f;
	}

	/*
	set filter frequency and (re)calculate params
	*/
	void setFreq(float freq_) {
		freq = freq_;
		w0 = 2 * pi * freq / sampleRate;
		updateCoeff();
	}

	/*
	update whenever Q, A, Alpha update
	rewritten in each filter
	*/
	virtual void setCoeff() = 0;

	void setQ(float Q_) {
		Q = Q_;
		updateCoeff();
	}

	void setGain(float dBGain_) {
		A = pow(10.0f, dBGain_ / 40.0f);
		updateCoeff();
	}

	/*
	take in input_ and produce output
	*/
	float processSample(float input_) {
		float output = B0 * input_ + B1 * x1 + B2 * x2 - A1 * y1 - A2 * y2;

		// update previous sample
		x2 = x1;
		x1 = input_;
		y2 = y1;
		y1 = output;

		return output;
	}

private:
	void setAlpha() {
		alpha = sin(w0) / (2 * Q);
	}

	void updateCoeff() {
		setAlpha();
		setCoeff();
		A1 = a1 / a0;
		A2 = a2 / a0;
		B0 = b0 / a0;
		B1 = b1 / a0;
		B2 = b2 / a0;
	}
};


class LPF :public Filter {
public:
	LPF() :Filter() {}
	virtual void setCoeff() override {
		b0 = (1 - cos(w0)) / 2;
		b1 = (1 - cos(w0));
		b2 = (1 - cos(w0)) / 2;
		a0 = 1 + alpha;
		a1 = -2 * cos(w0);
		a2 = 1 - alpha;
	}
};

class HPF :public Filter {
public:
	HPF() :Filter() {}
	virtual void setCoeff() override {
		b0 = (1 + cos(w0)) / 2;
		b1 = -(1 + cos(w0));
		b2 = (1 + cos(w0)) / 2;
		a0 = 1 + alpha;
		a1 = -2 * cos(w0);
		a2 = 1 - alpha;
	}
};

class BPF :public Filter {
public:
	BPF() : Filter() {}
	virtual void setCoeff() override {
		b0 = sin(w0) / 2;
		b1 = 0;
		b2 = -sin(w0) / 2;
		a0 = 1 + alpha;
		a1 = -2 * cos(w0);
		a2 = 1 - alpha;
	}
};

class NotchFilter :public Filter {
public:
	NotchFilter() : Filter() {}
	virtual void setCoeff() override {
		b0 = 1;
		b1 = -2 * cos(w0);
		b2 = 1;
		a0 = 1 + alpha;
		a1 = -2 * cos(w0);
		a2 = 1 - alpha;
	}
};

class APF :public Filter {
public:
	APF() : Filter() {}
	virtual void setCoeff() override {
		b0 = 1 - alpha;
		b1 = -2 * cos(w0);
		b2 = 1 + alpha;
		a0 = 1 + alpha;
		a1 = -2 * cos(w0);
		a2 = 1 - alpha;
	}
};

class PeakingEQ :public Filter {
public:
	PeakingEQ() : Filter() {}
	virtual void setCoeff() override {
		b0 = 1 + alpha * A;
		b1 = -2 * cos(w0);
		b2 = 1 - alpha * A;
		a0 = 1 + alpha / A;
		a1 = -2 * cos(w0);
		a2 = 1 - alpha / A;
	}
};

class LShelf :public Filter {
public:
	LShelf() : Filter() {}
	virtual void setCoeff() override {
		b0 = A * ((A + 1) - (A - 1) * cos(w0) + 2 * sqrt(A) * alpha);
		b1 = 2 * A * ((A - 1) - (A + 1) * cos(w0));
		b2 = A * ((A + 1) - (A - 1) * cos(w0) - 2 * sqrt(A) * alpha);
		a0 = (A + 1) + (A - 1) * cos(w0) + 2 * sqrt(A) * alpha;
		a1 = -2 * ((A - 1) + (A + 1) * cos(w0));
		a2 = (A + 1) + (A - 1) * cos(w0) - 2 * sqrt(A) * alpha;
	}
};

class HShelf :public Filter {
public:
	HShelf() : Filter() {}
	virtual void setCoeff() override {
		b0 = A * ((A + 1) + (A - 1) * cos(w0) + 2 * sqrt(A) * alpha);
		b1 = -2 * A * ((A - 1) + (A + 1) * cos(w0));
		b2 = A * ((A + 1) + (A - 1) * cos(w0) - 2 * sqrt(A) * alpha);
		a0 = (A + 1) - (A - 1) * cos(w0) + 2 * sqrt(A) * alpha;
		a1 = 2 * ((A - 1) - (A + 1) * cos(w0));
		a2 = (A + 1) - (A - 1) * cos(w0) - 2 * sqrt(A) * alpha;
	}
};


