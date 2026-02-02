//SimpleWavIO.h

#pragma once
# include <vector>
# include <string>


// get filename, then store wav in buffer, sampleRate and channels
bool readWav(const std::string& filename,
    std::vector<float>& buffer,
    int& sampleRate,
    int& channels);


// get mono buffer from external wav (only get first channel)
// first do readWav, then only select first channel
bool readWav_Mono(const std::string& filename,
    std::vector<float>& buffer,
    int& sampleRate);



// get filename, then pack buffer, sampleRate and channels in it
bool writeWav(const std::string& filename,
    const std::vector<float>& buffer,
    int sampleRate,
    int channels);

// write multiChannel structure's wav, eg. buffer[ch][n], break it into interleaved structure, then store
bool writeWav_MultiChannel(const std::string& filename,
    const std::vector<std::vector<float>>& buffer,
    int sampleRate);



