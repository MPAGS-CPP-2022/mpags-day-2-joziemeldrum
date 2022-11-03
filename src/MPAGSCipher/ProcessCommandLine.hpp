#ifndef MPAGSCIPHER_PROCESSCOMMANDLINE_HPP
#define MPAGSCIPHER_PROCESSCOMMANDLINE_HPP

#include <string>
#include <vector>

//! Process the options input in commandline
bool processCmdLine(
    const std::vector<std::string>&, 
    bool&, 
    bool&, 
    std::string&,
    std::string&,
    bool&, 
    int&);

#endif // MPAGSCIPHER_PROCESSCOMMANDLINE_HPP