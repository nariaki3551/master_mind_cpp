add_executable(
  utest
  test.cpp
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
  gtest
  gtest_main
  pthread
  )

target_link_options(
  utest PRIVATE
  -g
  --coverage
)
