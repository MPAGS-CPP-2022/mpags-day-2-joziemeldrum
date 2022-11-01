#include <string>
#include <vector>
#include <iostream>
#include <exception>

#include "ProcessCommandLine.hpp"


bool processCmdLine(
    const std::vector<std::string>& args, 
    bool& helpRequested, 
    bool & versionRequested, 
    std::string& inputFile,
    std::string& outputFile,
    bool& encrypt,
    int& shift ){

    const std::size_t nCmdLineArgs{args.size()};
    

    for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (args[i] == "-h" || args[i] == "--help") {
            helpRequested = true;
        } else if (args[i] == "--version") {
            versionRequested = true;
        } else if (args[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return false;
            } else {
                // Got filename, so assign value and advance past it
                inputFile = args[i + 1];
                ++i;
            }
        } else if (args[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return false;
            } else {
                // Got filename, so assign value and advance past it
                outputFile = args[i + 1];
                ++i;
            }
        } else if (args[i] == "-encrypt" || args[i] == "-decrypt") {
            // Ceaser shift mode
            // check next element is value of shift and convert from string -> int
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -encypt requires a shift value argument"
                          << std::endl;
                return false;
            }
            
            try{
                shift = stoi(args[i+1]); 
                // ^This also truncates floats (is that the right word? so 1.9 -> 1?) maybe a wat to fix this to reject floats also?
            }catch (...){
                std::cerr << "[error] shift value must be number"
                          << std::endl;
                return false;
            }
            // Check which of encrypt or decrypt it is
            if (args[i] == "-decrypt"){
                encrypt = false;
            }
            i++;
        } else {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << args[i]
                      << "'\n";
            return false;
        }
    }
    
    return true;
    }

