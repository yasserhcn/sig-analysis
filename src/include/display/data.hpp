#pragma once

#include <vector>
#include <memory>

class signalData
{
public:
    /**
     * @brief Construct a new signal Data object
     * 
     */
    signalData();

    /**
     * @brief add a value to the waveform
     * 
     * @param value value to add
     */
    void addWaveformPoint(int64_t value);

    /**
     * @brief Get the amount of data points in the waveform
     * 
     * @return uint64_t 
     */
    uint64_t getWaveformSize();

    /**
     * @brief Get the waveform data at an index
     * 
     * @param index index of the point
     * @return int64_t 
     */
    int64_t getWaveformData(uint64_t index);
    
    /**
     * @brief erase all the waveform data
     * 
     */
    void eraseWaveformData();

    /**
     * @brief Set the amount of samples per second
     * 
     * @param val samplerate value
     */
    void setSampleRate(int32_t val);

    /**
     * @brief get the amount of samples for every second
     * 
     * @return int32_t 
     */
    int32_t getSampleRate();

    /**
     * @brief Destroy the signal Data object
     * 
     */
    ~signalData();
    
private:

    std::vector<int64_t> waveformDataPoints;

    int32_t sampleRate;
};
