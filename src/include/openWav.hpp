#pragma once

#include <string>
#include <fstream>
#include <memory>
#include <algorithm>

#define CHECK_BOOL(x, y) (x = x && y)

#define OFFSET_TO_SIZE 4

class Wav
{
public:
    /**
     * @brief open a wav file
     * 
     * @param path path to the file
     */
    Wav(std::string path);

    /**
     * @brief check if the file is a valid wav file
     * 
     * @return true whe valid
     */
    bool checkValid();

    
    /**
     * @brief get the size of the file
     * 
     * @return the size of the file in bytes
     */
    int getSize();

    ~Wav();
private:
    std::shared_ptr<uint8_t> data;
    std::shared_ptr<uint8_t> buffer;

    /**
     * @brief checkif the file is a valid riff file
     * 
     * @param bufferPtr pointer to the data buffer
     * @return true for a valid file
     */
    bool checkRiff();
};

