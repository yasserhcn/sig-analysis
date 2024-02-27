#include "openWavTest.hpp"

#define FILE_NAME "test.wav"
#define FILE_SIZE_BYTES 529280
#define FILE_AMOUNT_CHANNELS 1
#define FILE_AMOUNT_SAMPLES 44099
#define FILE_SAMPLE_RATE 44100

int wav::test1()
{
    // open the file without parsing
    Wav file(std::string(FILE_NAME), true);

    // check the validity of the file
    assert(file.checkValid() == true);

    std::cout<<"test 1 passed successfully"<<std::endl;
    return 0;
}

int wav::test2()
{
    // open the file without parsing
    Wav file(std::string("test.wav"), true);

    // ensure the file has the correct size
    assert(file.getFileSize() == FILE_SIZE_BYTES);

    std::cout<<"test 2 passed successfully"<<std::endl;
    return 0;
}

int wav::test3()
{
    // open the file without parsing
    Wav file(std::string("test.wav"), true);

    // check metadata
    assert(file.getAmountOfChannels() == FILE_AMOUNT_CHANNELS);
    assert(file.getAmountOfSamples() == FILE_AMOUNT_SAMPLES);
    assert(file.getSampleRate() == FILE_SAMPLE_RATE);

    std::cout<<"test 3 passed successfully"<<std::endl;
    return 0;
}