#ifndef TESTS
#define TESTS

#include <string>
#include <iostream>
#include <random>
#include <vector>
//Check my previous task, please, if it is possible. If I got 0 put 0 so i now that you saw S_P_blocks.
class Tests{
    public:
        Tests();
        Tests(const std::string& bitSequence);
        std::string Sequence_gen();
        void SplitAndStoreSequence();
        void Show_vbits();

        //1
        bool MonobitTest();
        //2
        bool MaxLengthRunTest() ;
        //Poker face
        bool Poker();
        //3
        bool SeriesTest();

    private:
        std::string bitSequence;
        std::vector<std::string> bitSequenceParts; // Vector to store 32-bit parts


};

#endif