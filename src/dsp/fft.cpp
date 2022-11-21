#include <dsp/fft.hpp>

std::shared_ptr<std::vector<std::complex<float>>> fft(std::shared_ptr<std::vector<std::complex<float>>> dataPoints, float fftSize)
{

    // validate that the size is a power of 2
    if(fftSize != 256 && fftSize != 512 && fftSize != 1024 && fftSize != 2048)
    {
        return nullptr;
    }
    
    std::shared_ptr<std::vector<std::complex<float>>> ret = std::make_shared<std::vector<std::complex<float>>>();

    // return on the trivial case
    if(dataPoints->size() == 1){
        ret->push_back(dataPoints->at(0));
        return ret;
    }
    
    // if not trivial case split the fft

    // spliting the fft
    std::shared_ptr<std::vector<std::complex<float>>> first = std::make_shared<std::vector<std::complex<float>>>();
    std::shared_ptr<std::vector<std::complex<float>>> second = std::make_shared<std::vector<std::complex<float>>>();
    for (int i = 0; i < dataPoints->size() - 1; i = i + 2)
    {
        first->push_back(dataPoints->at(i));
        second->push_back(dataPoints->at(i + 1));
    }
    
    std::shared_ptr<std::vector<std::complex<float>>> firstRes = fft(first, fftSize);
    std::shared_ptr<std::vector<std::complex<float>>> secondRes = fft(second, fftSize);

    // calculate the fft
    // GOD i hate this, if there's any better way to do it please make an issue and lmk
    // i know how inefficient my implementation is but it works
    std::complex<float> iComplex(0, 1);
    std::complex<float> piComplex(M_PI, 0);
    std::complex<float> minusTwo(-2, 0);
    std::complex<float> sizeComplex(dataPoints->size(), 0);
    for (int i = 0; i < (dataPoints->size() / 2) - 1; i++)
    {
        std::complex<float> iteratorComplex(i, 0);
        std::complex<float> p = firstRes->at(i);   
        std::complex<float> q = std::exp(((minusTwo * piComplex * iComplex) / sizeComplex) * iteratorComplex) * secondRes->at(i);
        firstRes->at(i) = p + q;
        secondRes->at(i) = p - q;
    }

    // return the fft
    // get the whole vector and concatenate it
    float size = dataPoints->size();
    for (int i = 0; i < size; i++)
    {
        if(i < (size / 2))
        {
            ret->push_back(firstRes->at(i));
        }else
        {
            ret->push_back(secondRes->at(i - (size / 2)));
        }
    }
    
    return ret;
}