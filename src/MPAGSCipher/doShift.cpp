#include <string>
#include <map>
#include <vector>
#include <cctype>

#include "DoShift.hpp"


char do_shift(char in_char, int shift){
    // first if shift = 0 can skip all the processing
    if (shift == 0){
        return in_char;
    }

    // Create maps to convert between numbers and letters
    char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                      'W', 'X', 'Y', 'Z'};
    std::vector<char> alphabet{letters, letters + 26};

    // made a separate map for going int <-> char, is there a way to make a map where you can use the value as a key as well, so only need one map?
    std::map<char, int> convert{};
    std::map<int, char> devert{};
    for(int i{0}; i < 26; ++i)
    {
        convert.insert({alphabet[i], i});
        devert.insert({i, alphabet[i]});
    }

    // convert input character to number
    int num{convert[in_char]};

    // shift then check output in range 0-25
    num += shift;

    // make sure positive
    while(num < 0){
        num += 26;
    }

    // wrap around if went over 26
    while(num >25){
        num %= 26;
    }

    // convert back to capital letter and output
    return devert[num];
}
