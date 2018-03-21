cmake_minimum_required(VERSION 3.0)
project(SoteriaRover)

#set the project source code directory
set(PROJECT_SOURCE_DIR ../)

#create the library for the program and include external ones
add_library(LibsModule
    ${PROJECT_SOURCE_DIR}/Motor/MotorModule.cpp
    ${PROJECT_SOURCE_DIR}/Manager/ManagerModule.cpp
    ${PROJECT_SOURCE_DIR}/Sonar/SonarModule.cpp    
    ${PROJECT_SOURCE_DIR}/Inert/InertModule.cpp   
    ${PROJECT_SOURCE_DIR}/Utils/Utils.cpp
    ${PROJECT_SOURCE_DIR}/Inert/I2Cdev.cpp
    ${PROJECT_SOURCE_DIR}/Comms/CommsModule.cpp
    ${PROJECT_SOURCE_DIR}/Telec/TelecModule.cpp    
)
#for accessing GPIO pins
target_link_libraries(LibsModule -lbcm2835)

#set the source files
set(SOURCES 
    ${PROJECT_SOURCE_DIR}/SoteriaRover.cpp 
    ${PROJECT_SOURCE_DIR}/Manager/ManagerModule.h 
    ${PROJECT_SOURCE_DIR}/Motor/MotorModule.h 
    ${PROJECT_SOURCE_DIR}/Sonar/SonarModule.h   
    ${PROJECT_SOURCE_DIR}/Comms/CommsModule.h
    ${PROJECT_SOURCE_DIR}/mavlink/SoteriaRover/mavlink.h
    ${PROJECT_SOURCE_DIR}/mavlink/mavlink_helpers.h
    ${PROJECT_SOURCE_DIR}/Inert/InertModule.h
    ${PROJECT_SOURCE_DIR}/Utils/Utils.h
    ${PROJECT_SOURCE_DIR}/Inert/I2Cdev.h
    ${PROJECT_SOURCE_DIR}/Telec/TelecModule.h   

)

#create the xecutable and link it to all the libraries
add_executable(SoteriaRover ${SOURCES})
target_link_libraries(SoteriaRover LibsModule)