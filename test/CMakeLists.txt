find_package(GTest)
if(NOT GTest_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

add_executable(
  utest
  testCodeGenerator.cpp
  testItertools.cpp
  testPolicy.cpp
  testTrial.cpp
  testUtils.cpp
  )

target_include_directories(
  utest PRIVATE
  ${PROJECT_SOURCE_DIR}/src
  )

target_compile_options(
  utest PRIVATE
  -Wall
  -g
  --coverage
  )

target_compile_features(
  utest PRIVATE
  cxx_std_17
  )

target_link_libraries(
  utest PRIVATE
  master_mind_lib
  gtest
  gtest_main
  pthread
  )

target_link_options(
  utest PRIVATE
  -g
  --coverage
)
