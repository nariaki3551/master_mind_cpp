#
# master_mind_lib library
#
add_library(
  master_mind_lib
  STATIC
  utils.cpp
  itertools.cpp
  policy.cpp
  trial.cpp
  codeGenerator.cpp
  )

target_compile_options(
  master_mind_lib PRIVATE
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
  master_mind_lib PRIVATE
  cxx_std_17
  )


#
# mastermind execution
#
add_executable(
  mastermind
  main.cpp
  )

target_include_directories(
  mastermind PRIVATE
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

target_link_libraries(
  mastermind PRIVATE
  master_mind_lib
  )

