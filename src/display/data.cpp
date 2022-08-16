#include <display/data.hpp>

signalData::signalData()
{
}

void signalData::addWaveformPoint(int64_t value)
{
    waveformDataPoints.push_back(value);
}

uint64_t signalData::getWaveformSize()
{
    return waveformDataPoints.size();
}

int64_t signalData::getWaveformData(uint64_t index)
{
    return waveformDataPoints[index];
}

void signalData::eraseWaveformData()
{
    waveformDataPoints.clear();
}

void signalData::setSampleRate(int32_t val)
{
    sampleRate = val;
}

int32_t signalData::getSampleRate()
{
    return sampleRate;
}

signalData::~signalData()
{
}