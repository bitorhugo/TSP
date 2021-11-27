cmake_minimum_required(VERSION 3.17)
project(tsp C)

set(CMAKE_C_STANDARD 99)
include_directories(Client)
add_executable(tsp main.c Client/client.c Client/client.h)