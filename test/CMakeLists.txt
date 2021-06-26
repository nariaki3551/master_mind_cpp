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

target_compile_definitions(
  utest PRIVATE
  ${OpenMp_CXX_DEFS}
  )

target_link_libraries(
  utest PRIVATE
  master_mind_lib
  gtest
  gtest_main
  pthread
  ${OpenMPLib}
  )

target_link_options(
  utest PRIVATE
  -g
  --coverage
)
