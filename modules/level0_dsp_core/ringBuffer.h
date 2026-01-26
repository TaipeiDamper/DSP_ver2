# pragma once 

// Ring buffer

# include <vector>
# include "interpolation.h"

class RingBuffer {
protected:
	std::vector<float> buffer = { 0 };
	int bufferLength = 1;
	int writeIdx = 0;
public:
	RingBuffer() {};
	void prepare() {};										// pure buffer, no need to init itself
	void reset() {
		std::fill(buffer.begin(), buffer.end(), 0.0f);		// when reset, fill buffer with all 0
		writeIdx = 0;										// reset write ptr (calculate read ptr in normal cases)
	};

	
	void setBufferLength(int bufferLength_) {
		bufferLength = std::max(1, bufferLength_) + 4;		// 4 for extra margin for interpolation
		buffer.assign(bufferLength, 0.0f);
		writeIdx = 0;
	}

	void writeSample(float sample_) {

		buffer[writeIdx] = sample_;							// write sample into buffer
		writeIdx = wrapIdx(writeIdx + 1);					// update write index�]circular�^
	}

	// [default]  read sample before write
	float readSample(int indexOffset_) { return buffer[wrapIdx(writeIdx - indexOffset_)]; }

	// readSample after "writeSample" (since the index had changed)
	float readTap(int indexOffset_) { return buffer[wrapIdx(writeIdx - 1 - indexOffset_)]; }

	// interpolation ver.
	float readSample(float indexOffsetFrac_) {
		float readPos = writeIdx - indexOffsetFrac_; // calculate readIdx
		float delayFrac = readPos - floor(readPos);  // get frac part
		int readIdx = wrapIdx(static_cast<int>(floor(readPos)));		// wrap readIdx and get int part

		float x_1 = buffer[wrapIdx(readIdx - 1)];
		float x0 = buffer[readIdx];
		float x1 = buffer[wrapIdx(readIdx + 1)];
		float x2 = buffer[wrapIdx(readIdx + 2)];
		
		float output = Interp::lagrangeCubic(x_1, x0, x1, x2, delayFrac);

		return output;
	}

protected:
	int wrapIdx(int idx_) {
		return (idx_ + bufferLength) % bufferLength;
	}
};