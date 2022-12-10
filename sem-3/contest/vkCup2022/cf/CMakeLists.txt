cmake_minimum_required(VERSION 3.23)
project(cf)

set(CMAKE_CXX_STANDARD 20)

add_executable(A A.cpp C.cpp)
add_executable(B B.cpp)
add_executable(C C.cpp)
add_executable(main main.cpp)
