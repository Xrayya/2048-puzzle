cmake_minimum_required(VERSION 3.0.0)

set( CMAKE_CXX_COMPILER "C:/Users/Hary/scoop/apps/gcc/current/bin/g++.exe" )
set( CMAKE_C_COMPILER "C:/Users/Hary/scoop/apps/gcc/current/bin/gcc.exe" )

# find_program(CMAKE_C_COMPILER NAMES $ENV{CC} gcc PATHS ENV PATH NO_DEFAULT_PATH)
# find_program(CMAKE_CXX_COMPILER NAMES $ENV{CXX} g++ PATHS ENV PATH NO_DEFAULT_PATH)

# project(ClangdTest VERSION 0.1.0 C CXX)
project("2048")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB CPP_SOURCE
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# include_directories(C:/Users/Hary/scoop/apps/gcc/current/include)

add_executable(main ${CPP_SOURCE})
