#include "tests.h"
//Check my previous task, please, if it is possible. If I got 0 put 0 so i now that you saw S_P_blocks.
Tests::Tests(){
    bitSequence = "";
}

Tests::Tests(const std::string &bitSequence) {
    if (bitSequence.length() == 20000) {
        this->bitSequence = bitSequence;
    } else {
        throw std::invalid_argument("The bit sequence must be exactly 20,000 bits long.");
    }
}

std::string Tests::Sequence_gen(){
    int length = 20000;
    std::string result;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 1);

    for (int i = 0; i < length; i++) {
        result += std::to_string(distribution(gen));
    }

    return result;
}

void Tests::SplitAndStoreSequence() {
    bitSequenceParts.clear(); // Clear the vector to start fresh
    for (size_t i = 0; i < bitSequence.length(); i += 32) {
        // Extract and store each 32-bit part of the sequence
        bitSequenceParts.push_back(bitSequence.substr(i, 32));
    }
    // Clear the original bitSequence
    bitSequence.clear();

    
}


void Tests::Show_vbits(){
    std::cout<<"\n "<< std::endl;
    for (const std::string& part : bitSequenceParts) {
        std::cout << part << std::endl;
    }
}

bool Tests::MonobitTest(){
    if (bitSequenceParts.empty()) {
            throw std::runtime_error("Bit sequence is empty.");
    }
    int countOnes = 0;
    int countZeros = 0;

    for (const std::string &part : bitSequenceParts) {
        for (char bit : part) {
            if (bit == '1') {
                countOnes++;
            } else if (bit == '0') {
                countZeros++;
            }
        }
    }

    return (countOnes >= 9654 && countOnes <= 10346) && (countZeros >= 9654 && countZeros <= 10346);
}

bool Tests::MaxLengthRunTest(){
    if (bitSequenceParts.empty()) {
        throw std::runtime_error("Bit sequence parts are empty.");
    }

    int maxRunZeros = 0; 
    int maxRunOnes = 0; 

    int currentRunZeros = 0;
    int currentRunOnes = 0;

    for (const std::string &part : bitSequenceParts) {
        for (char bit : part) {
            if (bit == '0') {
                currentRunOnes = 0;
                currentRunZeros++;
                if (currentRunZeros > maxRunZeros) {
                    maxRunZeros = currentRunZeros;
                }
            } else if (bit == '1') {
                currentRunZeros = 0;
                currentRunOnes++;
                if (currentRunOnes > maxRunOnes) {
                    maxRunOnes = currentRunOnes;
                }
            }
        }
    }

    return (maxRunZeros <= 36) && (maxRunOnes <= 36);
} 

bool Tests:: Poker(){
    float X;
    int Y=32;
    int m =4;
    int k =8;
    std::vector<int> ni(16, 0);
    bool isRandom = true; // Assume it's random by default

    for (const std::string &part : bitSequenceParts) { // part - 32 bits
        for (size_t i = 0; i <= Y - m; i += m) {
            std::string m_part = part.substr(i, m);

            int block_index = std::stoi(m_part, nullptr, 2);
            ni[block_index]++;
        }

        int sumOfSquares = 0;
        for (int count : ni) {
            sumOfSquares += count * count;
        }
        int numerator = (1 << m) / k; // (2^m) / k
        float X3 = (float)(sumOfSquares * numerator) - k;

        if (X3 < 1.03 || X3 > 57.4) {
            isRandom = false; // Mark it as not random
            break;
        }
        //std::cout<<"\n poker:\n"<<X3;
        std::fill(ni.begin(), ni.end(), 0);
    }

    if (isRandom) {
        return true; 
    } else {
        std::cout << "Not a poker face, mission failed" << std::endl;
        return false; 
    }
}

bool Tests::SeriesTest() {
    int Y = 20000;
    std::vector<int> onesSeriesLengths(7, 0); 
    std::vector<int> zerosSeriesLengths(7, 0);
    char currentChar = ' ';
    int currentSeriesLength = 0;
    for (const std::string &part : bitSequenceParts) {
        for (char bit : part) {
            if (bit == currentChar) {
                currentSeriesLength++;
            } else {
                // Update the counts based on the completed series
                if (currentChar == '1') {
                    onesSeriesLengths[currentSeriesLength]++;
                } else if (currentChar == '0') {
                    zerosSeriesLengths[currentSeriesLength]++;
                }
                // Reset the current series length and character
                currentSeriesLength = 1;
                currentChar = bit;
            }
        }
    }
    if (currentChar == '1') {
    onesSeriesLengths[currentSeriesLength]++;
    } else if (currentChar == '0') {
        zerosSeriesLengths[currentSeriesLength]++;
    }

    onesSeriesLengths.erase(onesSeriesLengths.begin());
    zerosSeriesLengths.erase(zerosSeriesLengths.begin());

    std::cout << "onesSeriesLengths: ";
    for (int count : onesSeriesLengths) {
        std::cout << count << " ";
    }
    std::cout << std::endl;
    std::cout << "zerosSeriesLengths: ";
    for (int count : zerosSeriesLengths) {
        std::cout << count << " ";
    }
    std::cout << std::endl;

    std::vector<int> up_interval = {2733, 1421, 748, 402, 223, 123};
    std::vector<int> down_interval = {2267, 1079, 502, 223, 90, 60};
    int counter = 0;

    for (int count : onesSeriesLengths) {
        if (count > up_interval[counter] || count < down_interval[counter]) {
            return false; // Exit the function immediately if a series is outside the interval
        }
        counter++;
    }

    counter = 0; // Reset the counter for zeros series lengths

    for (int count : zerosSeriesLengths) {
        if (count > up_interval[counter] || count < down_interval[counter]) {
            return false; // Exit the function immediately if a series is outside the interval
        }
        counter++;
    }

    
    return true;

    


}