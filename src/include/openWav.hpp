#pragma once

#include <string>
#include <fstream>
#include <memory>
#include <algorithm>

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
     * @brief used for debugging
     * 
     * @return int value
     */
    uint32_t debugVal();
    char debugVar[4];

    ~Wav();
private:
    std::shared_ptr<uint8_t> data;
    std::shared_ptr<uint8_t> buffer;

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
        u_int8_t audioFormat;
        u_int8_t numChannels;
        uint32_t sampleRate;
        uint32_t byteRate;
        u_int8_t blockAlign;
        u_int8_t bitsPerSample;
    }fmtChunk;
    
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
    int getHeaderSize();

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
    int getFmtSize();

    /**
     * @brief get thee audio format
     * 
     * @return int with format value
     */
    int getFmtFormat();

    /**
     * @brief get the number of channels in the file
     * 
     * @return int with the number of channels
     */
    int getFmtNumChannels();

    /**
     * @brief get the sample rate
     * 
     * @return int with the sample rate
     */
    int getFmtSampleRate();

    /**
     * @brief get the byte rate
     * 
     * @return int with the bytee rate
     */
    int getFmtByteRate();
};

