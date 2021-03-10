cmake_minimum_required(VERSION 3.10)

add_executable(serialize WIN32 serialize.cpp list.cpp list_helper.cpp)
add_executable(deserialize WIN32 deserialize.cpp list.cpp list_helper.cpp)
