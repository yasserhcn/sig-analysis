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
    int debugVal();

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
        u_int32_t sampleRate;
        u_int32_t byteRate;
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
};

