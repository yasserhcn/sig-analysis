#pragma once

#include <iostream>
#include <cassert>
#include <files/wav/openWav.hpp>


namespace wav
{
    /**
     * @brief first test: opens file "test.wav" and ensures its validity
     * 
     * @return <=0 if the test isn't passed 
     */
    int test1();

    /**
     * @brief second test: checks the size of the file
     * 
     * @return <=0 if the test isn't passed 
     */
    int test2();

    /**
     * @brief third test: checks the amount of channels, sample rate, and amount of samples
     * 
     * @return <=0 if the test isn't passed 
     */
    int test3();
}