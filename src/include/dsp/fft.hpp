#pragma once

#include <memory>
#include <vector>
#include <math.h>
#include <complex>

std::shared_ptr<std::vector<std::complex<double>>> fft(std::shared_ptr<std::vector<std::complex<double>>> dataPoints, float fftSize);