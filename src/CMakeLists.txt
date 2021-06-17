add_executable(
  mastermind
  main.cpp
  )

target_include_directories(
  mastermind PUBLIC
  ${PROJECT_SOURCE_DIR}/source/argparse/include
  )

target_compile_options(
  mastermind PRIVATE
  -Wall
  )

target_compile_features(
  mastermind PRIVATE
  cxx_std_17
  )
