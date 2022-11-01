#include <string>
#include <cctype>
#include <iostream>

#include "TransformChar.hpp"
#include "DoShift.hpp"

bool transform_char(const char in_char, std::string& out_str, const bool encrypt, const int shift){
    // If in decryption mode, only decrypt input, don't do conversion to capitals
    if (!encrypt){
        // check if letter
        if(!std::isalpha(in_char)){
            // error and quit
            std::cerr << "[error] - for decryption input must be letters" << std::endl;
            return false;
        } else{
        // do decryption, needs negative of shift capital letters only
        out_str = do_shift(std::toupper(in_char), shift*-1);
        }
    }
    
    // Otherwise do previous code to turn everyone to a capital string and then do forwards shift on that
    else{
        // Temporary variable to hold the transformed letter/number, this is then split into characters for do_string
        std::string temp_str{};

        // Uppercase alphabetic characters
        if (std::isalpha(in_char)) {
            temp_str = std::toupper(in_char);
        }

        // Transliterate digits to English words
        switch (in_char) {
            case '0':
                temp_str = "ZERO";
                break;
            case '1':
                temp_str = "ONE";
                break;
            case '2':
                temp_str = "TWO";
                break;
            case '3':
                temp_str = "THREE";
                break;
            case '4':
                temp_str = "FOUR";
                break;
            case '5':
                temp_str = "FIVE";
                break;
            case '6':
                temp_str = "SIX";
                break;
            case '7':
                temp_str = "SEVEN";
                break;
            case '8':
                temp_str = "EIGHT";
                break;
            case '9':
                temp_str = "NINE";
                break;
        }

        out_str = ""; // otherwise will double count previous character converted
        for (char& t : temp_str)
        {
            out_str += do_shift(t, shift);
        }
    }
    return true;
}

