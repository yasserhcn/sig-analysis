#pragma once

#include <memory>
#include <vector>
#include <math.h>
#include <complex>

std::shared_ptr<std::vector<std::complex<float>>> fft(std::shared_ptr<std::vector<std::complex<float>>> dataPoints, float fftSize);