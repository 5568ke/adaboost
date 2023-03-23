cmake_minimum_required(VERSION 3.0)
project(adaboost)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")


add_executable(train
    ./include/segment.h
    ./src/segment.cpp
    ./include/spot.h
    ./src/spot.cpp
    ./src/main.cpp
)

target_include_directories(train
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/ThirdParty
)

