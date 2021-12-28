cmake_minimum_required(VERSION 3.17)
project(tsp C)

set(CMAKE_C_STANDARD 99)
include_directories(Porto_Pontos AG)
add_executable(tsp main.c Porto_Pontos/Client_Linked_List/client_linked_list.c Porto_Pontos/Client_Linked_List/client_linked_list.h Porto_Pontos/Client_Node/client_node.c Porto_Pontos/Client_Node/client_node.h Porto_Pontos/Client/client.c Porto_Pontos/Client/client.h Porto_Pontos/Trips/trips.c Porto_Pontos/Trips/trips.h Porto_Pontos/Cities/cities.c Porto_Pontos/Cities/cities.h Porto_Pontos/Points/points.c Porto_Pontos/Points/points.h Porto_Pontos/Poi/poi.c Porto_Pontos/Poi/poi.h Porto_Pontos/Date/date.c Porto_Pontos/Date/date.h)