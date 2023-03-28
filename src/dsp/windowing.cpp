#include <dsp/windowing.hpp>

dataBuf applyBlackmanHarris(dataBuf buf, float a0, float a1, float a2, float a3)
{
    dataBuf newBuf = std::make_shared<std::vector<float>>();
    for(int i = 0; i < buf->size(); i++)
    {
        // find the value at the current position of the buffer
        float val = a0;
        val -= a1 * cos( (2.0 * M_PI * i) / (float)buf->size() );
        val += a2 * cos( (4.0 * M_PI * i) / (float)buf->size() );
        val -= a3 * cos( (6.0 * M_PI * i) / (float)buf->size() );

        // multiply the current val by the buffer val
        newBuf->push_back(val * buf->at(i));
    }

    return newBuf;
}

double applyBlackmanHarrisToSingleValue(double value, int bufferSize, int bufferIndex)
{
    double val = 0.35875;
    val -= 0.48829 * cos( (2.0 * M_PI * bufferIndex) / ((float)bufferSize) );
    val += 0.14128 * cos( (4.0 * M_PI * bufferIndex) / ((float)bufferSize) );
    val -= 0.01168 * cos( (6.0 * M_PI * bufferIndex) / ((float)bufferSize) );

    return value * val;
}