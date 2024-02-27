#include "openWavTest.hpp"

int wav::test1()
{
    // open the file without parsing
    Wav file(std::string("build/test.wav"), true);

    // check the validity of the file
    bool valid = file.checkValid();
    assert(valid == true);

    std::cout<<"test 1 passed successfully"<<std::endl;
}

int wav::test2()
{

}

int wav::test3()
{
    
}