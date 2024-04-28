cmake_minimum_required(VERSION 3.6)
project(ProjectTitle)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
# Remove the "-O2" flag if you have problems with the debugger.
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(./gtest/include)

# Set Library dir
link_directories(./gtest/lib)

# Find SFML
set(SFML_DIR "path/to/SFML/cmake/modules" CACHE PATH "SFML config directory")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)


# Set source files for RELEASE target
# Only add cpp files, no h files!
# Only add files with functionality here, no test files!
set(RELEASE_SOURCE_FILES src/SystemExporter.cpp src/SystemImporter.cpp src/Job.cpp src/Compensation.cpp src/Device.cpp src/System.cpp
        src/PrinterMain.cpp tinyxml/tinyxml.cpp tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp sfml/State.cpp
        sfml/stateManager.cpp)

# Set source files for DEBUG target
# Only add cpp files, no h files!
set(DEBUG_SOURCE_FILES
        src/SystemImporter.cpp
        src/Device.cpp
        src/Job.cpp
        src/System.cpp
        src/SystemExporter.cpp
        tinyxml/tinyxml.cpp tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp
        tests/PrinterInputTests.cpp
        tests/FunctonalityTests.cpp
        src/Compensation.cpp
        tests/TestUtils.cpp
        tests/PrinterOutputTests.cpp
)

# Create RELEASE target
add_executable(release_target ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(debug_target ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(debug_target gtest)
target_link_libraries(release_target sfml-graphics sfml-window sfml-system)