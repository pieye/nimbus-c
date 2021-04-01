#basic c exmaple to use the nimbus 3D
cmake_minimum_required(VERSION 3.1)
project(
  nimbus_c
  VERSION 1.0
  LANGUAGES CXX)

#(MyLibExample simple_lib.cpp simple_lib.hpp)

#Adding main and creating executable
add_executable(nimbus_c src/main.cpp)

#link nimbus libraries
target_link_libraries(nimbus_c /usr/local/lib/libnimbus-preprocessing.so)