#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <exception>


#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"


int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};
    int shift{0}; // if --encrypt not used, shift by 0 i.e. don't shift
    bool encrypt{true}; // if false will decrypt, i.e. move by by -shift

    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it
    if (!processCmdLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile, encrypt, shift)){
        return 1;
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << "  -encrypt         Specify value to encrypt input with Ceaser Shift \n"
            << "                   Ceaser Shift will not be implemented if not supplied \n\n"
            << "  -decrypt         Specify value to decrypt input with Ceaser Shift \n"
            << "                   Decryption will not be implemented if not supplied \n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }


    // Initialise variables
    char inputChar{'x'};
    std::string inputText{""};
    std::string outputStr{""};

    // Read in user input from stdin/file
    if (!inputFile.empty()) {
        std::ifstream inFile {inputFile};

        if(!inFile.good()){
            std::cout << "[error] - unable to open input file" << std::endl;
            return 1;
        }

        while (inFile >> inputChar){
            if(!transform_char(inputChar, outputStr, encrypt, shift)){
                return 1;
            }
            inputText += outputStr;
        }
        inFile.close();
    }

    // loop over each character from user input if no file specified
    else{
        while (std::cin >> inputChar) {
            if(!transform_char(inputChar, outputStr, encrypt, shift)){
                return 1;
            }
            inputText += outputStr;
        }
    }

    // Output to file if specified, otherwise print in terminal
    if (!outputFile.empty()) {
        std::ofstream outFile{outputFile};

        if(!outFile.good()){
            std::cout << "[error] - unable to open output file" << std::endl;
            return 1;
        }

        outFile << inputText;
        outFile.close();
    }

    else{
        std::cout << inputText << std::endl;
    }

    return 0;

}

