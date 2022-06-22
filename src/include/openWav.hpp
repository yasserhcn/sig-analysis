#pragma once

#include <string>
#include <fstream>
#include <memory>

class Wav
{
public:
    /**
     * @brief open a wav file
     * 
     * @param path path to the file
     */
    Wav(std::string path);

    ~Wav();
private:
    std::shared_ptr<char> data;

    /**
     * @brief checkif the file is a valid riff file
     * 
     * @param bufferPtr pointer to the data buffer
     * @return true for a valid file
     */
    bool checkRiff(std::shared_ptr<char> bufferPtr);
};

