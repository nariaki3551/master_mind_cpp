cmake_minimum_required(VERSION 3.12)
project(MasterMind CXX)

#
# setting
#
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)
message("Generated with build types: ${CMAKE_BUILD_TYPE}")

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY )
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
endif()
message("Binaries will be generaed in: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


#
# find packages
#
option(USE_OPENMP "Use OpenMP" ON)
if(USE_OPENMP)
  find_package(OpenMP)
  set(OpenMPLib OpenMP::OpenMP_CXX)
  set(OpenMp_CXX_DEFS -DOMP_VERBOSE)
else()
  set(OpenMPLib "")
  set(OpenMp_CXX_DEFS "")
endif()


#
# add mastermind and test
#
add_subdirectory(src)
add_subdirectory(test)


#
# test
#
enable_testing()
add_test(
  NAME utest
  COMMAND utest
  )


#
# coverage test
#
add_custom_target(
  coverage
  DEPENDS utest
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMAND ctest
  COMMAND lcov -d test/CMakeFiles/utest.dir/ -c -o coverage.info > lcov.log 2>&1
  COMMAND lcov -e coverage.info ${PROJECT_SOURCE_DIR}/src/* -o filtered_coverage.info >> lcov.log 2>&1
  COMMAND genhtml -o lcovHtml --num-spaces 4 -s --legend filtered_coverage.info >> lcov.log 2>&1
  COMMENT [[create coverage report as lcovHtml/index.html, and log as lcov.log]]
  )
