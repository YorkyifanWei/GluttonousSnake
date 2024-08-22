cmake_minimum_required(VERSION 3.29)
project(GluttonousSnake C)

set(CMAKE_C_STANDARD 11)

aux_source_directory(. SRC_LIST)
add_executable(gluttonousSnake ${SRC_LIST})