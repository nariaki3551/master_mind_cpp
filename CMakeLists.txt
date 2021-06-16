cmake_minimum_required(VERSION 3.1)
project(MasterMind CXX)

# setting of CMAKE_RUNTIME_OUTPUT_DIRECTORY
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY )
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
# endif(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
endif()

# add mastermind
add_subdirectory(src)
