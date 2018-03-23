cmake_minimum_required(VERSION 3.0)

# Set the project name
project(SoteriaRover)

# Bring all header files in
include_directories(include include/mavlink/SoteriaRover)

# Add all sources files to SOURCES variable
file(GLOB SOURCES "src/*.cpp")

# Create the library for the program
add_library(LibsModule SHARED ${SOURCES})

# Add GPIO pin library
target_link_libraries(LibsModule -lbcm2835)

# Create the executable and link it to all the libraries
add_executable(SoteriaRover src/SoteriaRover.cpp)

# Link to the LibsModule library
target_link_libraries(SoteriaRover LibsModule)