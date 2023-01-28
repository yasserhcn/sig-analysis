#pragma once

#include <memory>
#include <vector>
#include <math.h>
#include <complex>

// frequencies of the sample
typedef std::shared_ptr<std::vector<std::complex<float>>> fftVec;

fftVec fft(fftVec dataPoints, float fftSize);