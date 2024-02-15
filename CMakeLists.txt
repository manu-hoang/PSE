cmake_minimum_required(VERSION 3.27)
project(PSE)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(tinyxml)

add_executable(PSE
        tinyxml/tinystr.cpp
        tinyxml/tinystr.h
        tinyxml/tinyxml.cpp
        tinyxml/tinyxml.h
        tinyxml/tinyxmlerror.cpp
        tinyxml/tinyxmlparser.cpp
        main.cpp)
