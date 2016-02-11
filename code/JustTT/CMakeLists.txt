cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project( wasd )
set(CMAKE_BUILD_TYPE Debug)


add_executable( wasd TipTilt.cpp main.cpp TipTilt.hpp)
target_compile_features( wasd PRIVATE cxx_thread_local)
target_link_libraries( wasd -lpthread)

