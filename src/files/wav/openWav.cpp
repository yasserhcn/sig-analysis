#include <openWav.hpp>


Wav::Wav(std::string path, bool autoParse)
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

    if(autoParse)
    {
        parseHeader();
        parseFmt();
    }
}

bool Wav::checkValid()
{
    bool isValid = true;
    CHECK_BOOL(isValid, checkRiff());

    return isValid;
}

void Wav::parseHeader()
{
    bool riffValid = checkRiff();
    getHeaderSize();
    bool wavValid = checkWav();
}

void Wav::parseFmt()
{
    bool fmtIdValid = checkFmtId();
    getFmtSize();
    getFmtFormat();
    getFmtNumChannels();
    getFmtByteRate();
    getFmtByteRate();
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
    if(
        value[0] == riffChunk.chunkId[0] && 
        value[1] == riffChunk.chunkId[1] &&
        value[2] == riffChunk.chunkId[2] &&
        value[3] == riffChunk.chunkId[3]
      ){
        return 1;
    }
    return 0;
}

int Wav::getHeaderSize()
{
    u_int32_t size;
    size = *((u_int32_t*) (buffer.get() + OFFSET_TO_SIZE) );
    riffChunk.chunkDataSize = size;
    return size;
}

bool Wav::checkWav()
{
    // copy the bytes to an array
    char value[4];
    value[0] = buffer.get()[8 + 0];
    value[1] = buffer.get()[8 + 1];
    value[2] = buffer.get()[8 + 2];
    value[3] = buffer.get()[8 + 3];

    // check
    if(
        value[0] == riffChunk.riffTypeId[0] && 
        value[1] == riffChunk.riffTypeId[1] &&
        value[2] == riffChunk.riffTypeId[2] &&
        value[3] == riffChunk.riffTypeId[3]
      ){
        return 1;
    }
    return 0;
}

bool Wav::checkFmtId()
{
    char value[4];
    value[0] = buffer.get()[OFFSET_TO_FMT + 0];
    value[1] = buffer.get()[OFFSET_TO_FMT + 1];
    value[2] = buffer.get()[OFFSET_TO_FMT + 2];
    value[3] = buffer.get()[OFFSET_TO_FMT + 3];

    if( 
        value[0] == fmtChunk.chunkId[0] && 
        value[1] == fmtChunk.chunkId[1] &&
        value[2] == fmtChunk.chunkId[2] &&
        value[3] == fmtChunk.chunkId[3]
      )
    {
        return 1;
    }
    return 0;
}

int Wav::getFmtSize()
{
    u_int32_t size;
    size = *((u_int32_t*) (buffer.get() + OFFSET_TO_FMT + 4) );
    fmtChunk.chunkSize = size;
    return size;
}

int Wav::getFmtFormat()
{
    u_int16_t size;
    size = *((u_int16_t*) (buffer.get() + OFFSET_TO_FMT + 8) );
    fmtChunk.audioFormat = size;
    debugVar[0] = size;
    return size;
}

int Wav::getFmtNumChannels()
{
    u_int16_t size;
    size = *((u_int16_t*) (buffer.get() + OFFSET_TO_FMT + 10) );
    fmtChunk.audioFormat = size;
    debugVar[1] = size;
    return size;
}

int Wav::getFmtSampleRate()
{
    uint32_t size;
    size = *((uint32_t*) (buffer.get() + OFFSET_TO_FMT + 14) );
    fmtChunk.sampleRate = size;
    return size;
}

int Wav::getFmtByteRate()
{
    uint32_t size;
    size = *((uint32_t*) (buffer.get() + OFFSET_TO_FMT + 16) );
    fmtChunk.byteRate = size;
    return size;
}

uint32_t Wav::debugVal()
{
    return fmtChunk.sampleRate;
}

Wav::~Wav()
{
}

