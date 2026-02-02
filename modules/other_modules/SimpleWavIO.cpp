// SimpleWavIO.cpp

# define DR_WAV_IMPLEMENTATION
# include "SimpleWavIO.h"
# include "dr_wav.h"
# include <iostream>

// get filename, then store wav in Buffer, sampleRate and Channels
bool readWav(const std::string& filename,
    std::vector<float>& buffer,
    int& sampleRate,
    int& channels)
{
    // create drwav object
    drwav wav;

    // if init failed, return false
    // need drwav object and file name (turned into c string)
    if (!drwav_init_file(&wav, filename.c_str(), nullptr))
        return false;

    // resize buffer to fit wav content (1D-interleaved-buffer)
    buffer.resize(wav.totalPCMFrameCount* wav.channels);

    //get buffer's pointer (.data()), then store wav content into buffer via frame count
    drwav_read_pcm_frames_f32(&wav, wav.totalPCMFrameCount, buffer.data());

    // pass sampleRate and channels out
    sampleRate = wav.sampleRate;
    channels = wav.channels;

    // close function
    drwav_uninit(&wav);
    return true;
}


bool readWav_Mono(const std::string& filename,
    std::vector<float>& buffer,
    int& sampleRate)
{
    std::vector<float> tempBuffer;
    int channels;
    if (!readWav(filename, tempBuffer, sampleRate, channels))
        return false;

    // only take first channel
    buffer.resize(tempBuffer.size() / channels);
    for (size_t i = 0; i < buffer.size(); i++) {
        buffer[i] = tempBuffer[i * channels];
    }
    return true;
}


// get filename, then pack buffer, sampleRate and channels in it
bool writeWav(const std::string& filename,
    const std::vector<float>& buffer,
    int sampleRate,
    int channels)
{
    // get drwav object
    drwav wav;

    // get a preset format
    drwav_data_format format{};

    // set format's.... well..... format...
    format.container = drwav_container_riff;   // a riff container
    format.format = DR_WAVE_FORMAT_IEEE_FLOAT; // PCM encoding
    format.channels = channels;
    format.sampleRate = sampleRate;
    format.bitsPerSample = 32;

    if (!drwav_init_file_write(&wav, filename.c_str(), &format, nullptr))
        return false;

    // get frame count, then write buffer into wav via frame count
    drwav_uint64 frameCount = buffer.size() / channels;
    drwav_write_pcm_frames(&wav, frameCount, buffer.data());

    // close function
    drwav_uninit(&wav);
    return true;
}


bool writeWav_MultiChannel(const std::string& filename,
    const std::vector<std::vector<float>>& buffer,
    int sampleRate)
{
    // expect buffer input to be buffer[ch][n]
    int channels = buffer.size();
    int frames = buffer[0].size();
    std::vector<float> interleaved(frames * channels);

    for (int ch = 1; ch < channels; ch++) {
        if (buffer[ch].size() != frames) return false;
    }

    for (int n = 0; n < frames; n++) {
        for (int ch = 0; ch < channels; ch++) {
            interleaved[n * channels + ch] = buffer[ch][n];
        }
    }
    return writeWav(filename, interleaved, sampleRate, channels);
}

