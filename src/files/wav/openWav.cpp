#include <openWav.hpp>


Wav::Wav(std::string path)
{
    std::ifstream file(path, std::ifstream::binary);

    // get the file size    
    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);

    // copy data to a buffer
    std::shared_ptr<uint8_t> bufferData(new uint8_t[length], std::default_delete<uint8_t[]>());
    //char * buffer = new char [length];
    file.read( (char *)bufferData.get(), length );

    buffer = bufferData;

    
}

bool Wav::checkValid()
{
    bool isValid = true;
    CHECK_BOOL(isValid, checkRiff());

    return isValid;
}

bool Wav::checkRiff()
{
    // copy the first riff part into a char array
    char value[4];
    value[0] = buffer.get()[0];
    value[1] = buffer.get()[1];
    value[2] = buffer.get()[2];
    value[3] = buffer.get()[3];

    // check
    if(value == "RIFF"){
        return 1;
    }
    return 0;
}

int Wav::getSize()
{
    u_int32_t size;
    size = *((u_int32_t*) (buffer.get() + OFFSET_TO_SIZE) );

    return size;
}

Wav::~Wav()
{
}

