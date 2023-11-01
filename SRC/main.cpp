#include <iostream>
#include "tests.h"


int main(){

    Tests tests;

    //random sequence of bits
    std::string randomBitSequence = tests.Sequence_gen();
    //std::cout << randomBitSequence << std::endl;

    Tests sequence(randomBitSequence);
    sequence.SplitAndStoreSequence();

    sequence.Show_vbits();

    std::cout<<"\n MonobitTest: \n"<<sequence.MonobitTest();
    std::cout<<"\n MaxLengthRunTest: \n"<<sequence.MaxLengthRunTest();
    std::cout<<"\n Poker: \n"<<sequence.Poker();
    std::cout<<"\n SeriesLength: \n"<<sequence.SeriesTest();



    return 0;

}