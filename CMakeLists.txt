cmake_minimum_required(VERSION 3.17)
project(tsp C)

set(CMAKE_C_STANDARD 99)
include_directories(Client AG)
add_executable(tsp main.c Client/client.c Client/client.h AG/ag.c AG/ag.h Client/client_trips.c Client/client_city.c Client/client_PoI.c AG/generation_list.c)