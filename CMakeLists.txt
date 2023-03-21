cmake_minimum_required(VERSION 3.0)
project(adaboost)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

include_directories(${PROJECT_SOURCE_DIR}/include)



add_executable(train
    ./src/main.cpp
    ./src/spot.cpp
    ./src/segment.cpp
    ./include/spot.h
    ./include/segment.h
)









