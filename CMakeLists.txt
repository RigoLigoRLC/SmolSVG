cmake_minimum_required(VERSION 3.15)
project(0005_SmolSVG)

set(CMAKE_CXX_STANDARD 14)
set(EXEC smolsvg)

file(GLOB SOURCES *.cpp)

add_executable(smolsvg ${SOURCES})