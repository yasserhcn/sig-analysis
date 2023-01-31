#pragma once

#include <string>
#include <fstream>
#include <memory>
#include <algorithm>
#include <vector>

#define CHECK_BOOL(x, y) (x = x && y)

#define OFFSET_TO_SIZE 4
#define OFFSET_TO_FMT 12
#define OFFSET_TO_DATA_CHUNK 36
#define OFFSET_TO_DATA 44

class Wav
{
public:
    /**
     * @brief open a wav file
     * 
     * @param path path to the file
     * @param autoParse automatically parse file after opening
     */
    Wav(std::string path, bool autoParse = true);

    /**
     * @brief check if the file is a valid wav file
     * 
     * @return true whe valid
     */
    bool checkValid();

    /**
     * @brief return the size of the file
     * 
     * @return uint64_t 
     */
    uint64_t getFileSize();

    /**
     * @brief return the amount of channels in the file
     * 
     * @return uint8_t 
     */
    uint8_t getAmountOfChannels();

    /**
     * @brief return the amount of samples
     * 
     * @return int 
     */
    int64_t getAmountOfSamples();

    /**
     * @brief Get the sample rate of the file
     * 
     * @return uint32_t with the amount of samples in one second
     */
    uint32_t getSampleRate();

    /**
     * @brief return the sample value
     * 
     * @param position the index of the sample
     * @param channel the channel the sample is in (must not be more than the amount of channels in the file)
     * @return uint64_t 
     */
    uint64_t getSample(uint32_t position, uint8_t channel = 0);

    /**
     * @brief used for debugging
     * 
     * @return int value
     */
    int32_t debugVal();
    char debugVar[4];

    ~Wav();
private:
    // vector of channels, each channel has a pointer to an array with the data
    std::vector<std::shared_ptr<int64_t>> channels;
    // amount of data points
    uint64_t dataPointsSize;

    // pointer to the file buffer
    std::shared_ptr<int8_t> buffer;
    // size of the file buffer
    uint64_t bufferSize;

    // indicates a fail in opening the file or another operation
    bool fail = false;

    struct riffHeaderData
    {
        const char chunkId[4] = { 'R', 'I', 'F', 'F'};
        uint32_t chunkDataSize = 0;
        const char riffTypeId[4] = {'W', 'A', 'V', 'E'};
    }riffChunk;
    
    struct fmtChunkData
    {
        const char chunkId[4] = {'f', 'm', 't', ' '};
        uint32_t chunkSize = 0;
        int8_t audioFormat;
        int8_t numChannels;
        int32_t sampleRate;
        uint32_t byteRate;
        int8_t blockAlign;
        int8_t bitsPerSample;
    }fmtChunk;

    struct dataChunkData
    {
        const char chunkId[4] = { 'd', 'a', 't', 'a'};
        uint32_t chunkSize;
    }dataChunk;
    
    /**
     * @brief parse the header of the file
     * 
     */
    void parseHeader();

    /**
     * @brief parse the fmt sub chunk
     * 
     */
    void parseFmt();

    /**
     * @brief parse the data
     * 
     */
    void parseData();

    /**
     * @brief checkif the file is a valid riff file
     * 
     * @param bufferPtr pointer to the data buffer
     * @return true for a valid file
     */
    bool checkRiff();

    /**
     * @brief Get the size in the header
     * 
     * @return int size
     */
    uint32_t getHeaderSize();

    /**
     * @brief check if the file is wave
     * 
     * @return true if file is valid
     */
    bool checkWav();

    /**
     * @brief check if the fmt id is valid
     * 
     * @return true when valid
     */
    bool checkFmtId();

    /**
     * @brief get the size in the fmt header
     * 
     * @return int size
     */
    uint32_t getFmtSize();

    /**
     * @brief get thee audio format
     * 
     * @return int with format value
     */
    int16_t getFmtFormat();

    /**
     * @brief get the number of channels in the file
     * 
     * @return int with the number of channels
     */
    int16_t getFmtNumChannels();

    /**
     * @brief get the sample rate
     * 
     * @return int with the sample rate
     */
    int32_t getFmtSampleRate();

    /**
     * @brief get the byte rate
     * 
     * @return int with the bytee rate
     */
    uint32_t getFmtByteRate();

    /**
     * @brief get thte block align value
     * 
     * @return int with the value of block align
     */
    int16_t getFmtBlockAlign();

    /**
     * @brief get the bits per sample field
     * 
     * @brief int with the amount of bits per sample
     */
    uint16_t getFmtBitsPerSample();

    /**
     * @brief validate the data header
     * 
     * @return true if the data header is valid
     */
    bool checkData();
    
    /**
     * @brief Get the size of the data section
     * 
     * @return int with the size of the data section
     */
    uint32_t getDataChunkSize();

    // get the data from the data chunk
    void fetchData();
};

