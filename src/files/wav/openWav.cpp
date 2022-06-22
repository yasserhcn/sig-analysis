#include <openWav.hpp>


Wav::Wav(std::string path)
{
    std::ifstream file(path, std::ifstream::binary);

    // get the file size    
    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);

    // copy data to a buffer
    std::shared_ptr<char> buffer(new char[length], std::default_delete<char[]>());
    //char * buffer = new char [length];
    file.read(buffer.get(), length);

    if(!checkRiff(buffer)){
        return;
    }

    
}

bool Wav::checkRiff(std::shared_ptr<char> bufferPtr)
{
    // copy the riff part into a char array
    char value[4];
    value[0] = bufferPtr.get()[0];
    value[1] = bufferPtr.get()[1];
    value[2] = bufferPtr.get()[2];
    value[3] = bufferPtr.get()[3];

    if(value == "RIFF"){
        return 1;
    }
    return 0;
}

Wav::~Wav()
{
}

