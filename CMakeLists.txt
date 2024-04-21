cmake_minimum_required(VERSION 3.22)

project(AHE)

set(CMAKE_CXX_STANDARD 17)

# add_subdirectory(src)

aux_source_directory(. DIR_SRCS)

add_executable(AHE ${DIR_SRCS})