cmake_minimum_required(VERSION 3.17)
project(ResistorsAndCapacitors)

set(CMAKE_CXX_STANDARD 14)

add_executable(ResistorsAndCapacitors main.cpp)
add_executable(resistors resistors.cpp)
#add_executable(yageo_cap_cs yageo_cap_cs.cpp)
add_executable(cc_x7r cc_x7r.cpp)