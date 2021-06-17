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
  $<$<CONFIG:Debug>:
    -O0
    -g -pg
  >
  $<$<CONFIG:Release>:
    -O3
  >
  )

target_compile_features(
  mastermind PRIVATE
  cxx_std_17
  )

target_link_options(
  mastermind PRIVATE
  $<$<CONFIG:Debug>:
    -O0
    -g -pg
  >
)
