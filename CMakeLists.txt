cmake_minimum_required(VERSION 3.16)
project(Smart_Pointer)

set(CMAKE_CXX_STANDARD 14)

add_executable(Smart_Pointer main.cpp include/scoped_ptr.hpp include/shared_ptr.hpp include/test_shared_ptr.hpp include/test_scoped_ptr.hpp)