#include "../../modules/level0_dsp_core/smoother.h"
#include <iomanip>
#include <iostream>
#include <vector>


int main() {
    ParamSmoother smoother;
    float fs = 44100.0f;
    float timeConst = 0.01f; // 10ms

    smoother.prepare(fs);
    smoother.setTimeConst(timeConst);
    smoother.reset();

    std::cout << "--- ParamSmoother Validation ---" << std::endl;
    std::cout << "Sample Rate: " << fs << " Hz" << std::endl;
    std::cout << "Time Constant: " << timeConst * 1000.0f << " ms" << std::endl;
    std::cout << std::fixed << std::setprecision(6);

    // Test Step Response: 0.0 -> 1.0
    float target = 1.0f;
    std::cout << "\nStep Response (0.0 -> 1.0):" << std::endl;

    // We expect it to reach ~63.2% of target at t = timeConst
    int samplesToPrint = 20;
    for (int i = 0; i < samplesToPrint; ++i) {
        float output = smoother.processSample(target);
        std::cout << "Sample " << std::setw(2) << i << ": " << output << std::endl;
    }

    // Run many samples to see if it reaches exactly 1.0
    std::cout << "..." << std::endl;
    bool reached = false;
    for (int i = 20; i < 5000; ++i) {
        float output = smoother.processSample(target);
        if (output == target) {
            std::cout << "Reached target exactly at sample " << i << std::endl;
            reached = true;
            break;
        }
    }

    if (!reached) {
        std::cout << "Did not reach target exactly after 5000 samples."
                            << std::endl;
    }

    // Test Block Processing
    std::cout << "\nBlock Processing Test:" << std::endl;
    std::vector<float> buffer(10, 0.5f); // Smooth towards 0.5 (from current 1.0)
    smoother.processBlock(buffer.data(), (int)buffer.size());

    for (size_t i = 0; i < buffer.size(); ++i) {
        std::cout << "Block Sample " << i << ": " << buffer[i] << std::endl;
    }

    std::cout << "\n--- Validation Complete ---" << std::endl;
    return 0;
}
