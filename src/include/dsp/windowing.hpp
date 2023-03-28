#pragma once

#include <vector>
#include <memory>
#include <math.h>

typedef std::shared_ptr<std::vector<float>> dataBuf;

/**
 * @brief applies the blackman harris to the buffer
 * 
 * @param buf the buffer containing the data
 * @param a0 first a value, usually 0.35875
 * @param a1 second a value, usually 0.48829
 * @param a2 third a value, usually 0.14128
 * @param a3 fourth a value, usually 0.01168
 * @return ptr to the buffer vector
 */
dataBuf applyBlackmanHarris(dataBuf buf, float a0 = 0.35875, float a1 = 0.48829, float a2 = 0.14128, float a3 = 0.01168);

/**
 * @brief applies simple blackman harris to a single value
 * 
 * @param val the value
 * @param bufferSize size fo the data buffer
 * @param bufferIndex current index in the buffer
 * @return float value after being passed to the windowing function
 */
double applyBlackmanHarrisToSingleValue(double value, int bufferSize, int bufferIndex);