add_executable(
  mastermind
  main.cpp
  )

target_compile_options(
  mastermind PRIVATE
  -Wall
  )

target_compile_features(
  mastermind PRIVATE
  cxx_std_17
  )
