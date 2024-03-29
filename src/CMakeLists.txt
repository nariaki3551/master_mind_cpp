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
  run.cpp
  $<$<BOOL:${USE_MPI}>:runMpi.cpp>
  )

target_include_directories(
  master_mind_lib PRIVATE
  ${PROJECT_SOURCE_DIR}/source/argparse/include
  )

target_compile_options(
  master_mind_lib PRIVATE
  -Wall
  $<$<CXX_COMPILER_ID:AppleClang>:
    -Xclang -fopenmp
  >
  $<$<NOT:$<CXX_COMPILER_ID:AppleClang>>:
    ${OpenMP_CXX_FLAGS}
  >
  $<$<CONFIG:Debug>:
    -O0
    -g -pg
  >
  $<$<CONFIG:Release>:
    -O3
  >
  )

target_include_directories(
  master_mind_lib PRIVATE
  ${PROJECT_SOURCE_DIR}/source/argparse/include
  ${PROJECT_SOURCE_DIR}/source/progress-cpp/include
  )


target_compile_features(
  master_mind_lib PRIVATE
  cxx_std_17
  )

target_compile_definitions(
  master_mind_lib PRIVATE
  ${OpenMp_CXX_DEFS}
  )


#
# mastermind execution
#
add_executable(
  mastermind
  main.cpp
  )

target_compile_options(
  mastermind PRIVATE
  -Wall
  $<$<CONFIG:Debug>:
    -O0 -g -pg
  >
  $<$<CONFIG:Release>:
    -O3
  >
  )

target_compile_features(
  mastermind PRIVATE
  cxx_std_17
  )

target_compile_definitions(
  mastermind PRIVATE
  ${OpenMp_CXX_DEFS}
  $<$<BOOL:${USE_MPI}>: -DUSE_MPI>
  )

target_link_libraries(
  mastermind PRIVATE
  master_mind_lib
  ${OpenMPLib}
  )

