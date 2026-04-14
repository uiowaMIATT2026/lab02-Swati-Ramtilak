cmake_minimum_required(VERSION 3.22.1)
cmake_policy(VERSION 3.22.1...3.31.1)

#-----------------------------------------------------------------------------
# Enable C++17
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()
if(NOT CMAKE_CXX_STANDARD_REQUIRED)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()
set(VALID_CXX_STANDARDS "17" "20" "23")
if(NOT CMAKE_CXX_STANDARD IN_LIST VALID_CXX_STANDARDS)
    message(FATAL_ERROR "CMAKE_CXX_STANDARD:STRING=${CMAKE_CXX_STANDARD} not in known standards list\n ${VALID_CXX_STANDARDS}.")
endif()
#-----------------------------------------------------------------------------

project(RegisterCirclesLab
        VERSION 0.0.2026
        LANGUAGES CXX)

find_package(ITK 6.0 REQUIRED)
include(${ITK_USE_FILE})

find_package(SlicerExecutionModel REQUIRED GenerateCLP)
include(${GenerateCLP_USE_FILE})
include(${SlicerExecutionModel_USE_FILE})
include(${SlicerExecutionModel_CMAKE_DIR}/SEMMacroBuildCLI.cmake)

set(MYHAWKID "sramtilak") # <----- YOU MUST CHANGE THIS!

add_subdirectory(GenerateCircles)
add_subdirectory(RegisterImages)
add_subdirectory(ResampleImage)
