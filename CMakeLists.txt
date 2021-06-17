cmake_minimum_required(VERSION 3.1)
project(MasterMind CXX)

# setting of CMAKE_BUILD_TYPE
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)
message("Generated with build types: ${CMAKE_BUILD_TYPE}")

# setting of CMAKE_RUNTIME_OUTPUT_DIRECTORY
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY )
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
endif()
message("Binaries will be generaed in: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# add mastermind and test
add_subdirectory(src)
add_subdirectory(test)

# test
enable_testing()
add_test(
  NAME utest
  COMMAND utest
  )

