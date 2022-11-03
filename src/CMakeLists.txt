# MAIN CMAKE BUILDSCRIPT FOR MPAGS-CIPHER

# Set requirements:
cmake_minimum_required(VERSION 3.2)

# Declare project
project(MPAGSCipher VERSION 0.1.0)

# Output all command lines by default
set(CMAKE_VERBOSE-MAKEFILE ON)

# Directly set C++ standard, useful if you know this but not specific compile features
# So C++ 11 or C++ 14 etc
set(CMAKE_CXX_STANDARD 11)

# Declare the build of m-c as main program
add_executable(mpags-cipher 
    mpags-cipher.cpp
    MPAGSCipher/transformChar.cpp
    MPAGSCipher/processcommandline.cpp
    MPAGSCipher/doShift.cpp)


# Include directories compiler should search for headers in
target_include_directories(mpags-cipher 
    PRIVATE MPAGSCipher)


# Use standard set of flags from mpags day 1
# # enable some common warnings, even more warnings, all warnings->errors, 
# # stop compiling on first error, warnings for shadowed variables, strict warning conditions
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic")

# Declare compile features:
# # Need to have set the above things BEFORE defining the target
# # Take name of target(=programme/library), scope flag and a scoped list of the features the targets SOURCES (#includes)
target_compile_features(mpags-cipher PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization)