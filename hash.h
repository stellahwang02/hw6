#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
      // Compute w[i] values for the string
        HASH_INDEX_T w[5] = {0};

        // Start index of the current substring
        int start = k.length()-1;

        // Iterate over the string in groups of 6 characters
        for (int i = 4; i >= 0; --i) {
            HASH_INDEX_T val = 0;
            int power = 1;
            // Extract characters from the string and compute the value
            for (int j = start; j > start-6 && j >= 0; --j) {
                val += letterDigitToNumber(k[j]) * power;
                power *= 36;
            }
            
            w[i] = val;
            std::cout << "TEST" << std::endl;
            std::cout << w[i] << std::endl;
            start -= 6;
        }

        // Compute the hash value using r values
        HASH_INDEX_T hashValue = 0;
        for (int i = 0; i < 5; ++i) {
            hashValue += rValues[i] * w[i];
        }

        return hashValue;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (isdigit(letter)) {
            return letter - '0' + 26; // '0' corresponds to 26 in base-36
        } else if (isalpha(letter)) {
            return tolower(letter) - 'a'; // Convert to lowercase and map to 0-25
        }
        // Handle other characters if needed
        return 0; // Default value for non-letter and non-digit characters

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
