cmake_minimum_required(VERSION 3.0)
project(adaboost)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

add_executable(train
    ./include/segment.h
    ./include/spot.h
    ./include/utility.h
    ./include/FWL.h
    ./include/ThreadPool.h
    ./src/segment.cpp
    ./src/spot.cpp
    ./src/adaboost.cpp
    ./src/stump.cpp
    ./src/WeakLearner.h
    ./src/utility.cpp
)

target_include_directories(train
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/ThirdParty
)

find_package(Python3 COMPONENTS Interpreter Development NumPy)
find_package(Threads REQUIRED)

target_include_directories(train PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(train 
  Threads::Threads
  ${Python3_LIBRARIES}
)


# cmake_minimum_required(VERSION 3.0)
# project(adaboost)


# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")


# add_executable(train
#     ./include/segment.h
#     ./src/segment.cpp
#     ./include/spot.h
#     ./include/utility.h
#     ./src/spot.cpp
#     ./src/main.cpp
#     ./src/stump.cpp
#     ./src/WeakLearner.h
# )

# target_include_directories(train
#     PUBLIC 
#         ${PROJECT_SOURCE_DIR}/include
#         ${PROJECT_SOURCE_DIR}/ThirdParty
# )

# include_directories(usr/local/include)
# include_directories(${PYTHON_INCLUDE_DIRS})


# find_package(Python3 COMPONENTS Interpreter Development NumPy)
# find_package(Threads REQUIRED)
# target_link_libraries(train 
#   Threads::Threads
#   ${Python3_LIBRARIES}
# )

