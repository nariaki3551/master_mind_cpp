add_executable(
  utest
  test.cpp
  )

target_include_directories(
  utest PRIVATE
  ${PROJECT_SOURCE_DIR}/src  # -I./src/
  )

target_compile_options(  # -Wall
  utest PRIVATE
  -Wall
  )

target_compile_features(  # -std=c++17
  utest PRIVATE
  cxx_std_17
  )

target_link_libraries(  # -lgtest -lgtest_main
  utest PRIVATE
  gtest
  gtest_main
  pthread
  )
