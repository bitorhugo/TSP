cmake_minimum_required(VERSION 3.17)
project(tsp C)

set(CMAKE_C_STANDARD 99)

include_directories(Porto_Pontos
        Genetic_Algorithm
        Files
        Tests)

add_executable(
        tsp main.c
        Porto_Pontos/Client_Linked_List/client_linked_list.c Porto_Pontos/Client_Linked_List/client_linked_list.h Porto_Pontos/Client_Node/client_node.c Porto_Pontos/Client_Node/client_node.h Porto_Pontos/Client/client.c Porto_Pontos/Client/client.h Porto_Pontos/Trips/trips.c Porto_Pontos/Trips/trips.h Porto_Pontos/Cities/cities.c Porto_Pontos/Cities/cities.h Porto_Pontos/Points/points.c Porto_Pontos/Points/points.h Porto_Pontos/Poi/poi.c Porto_Pontos/Poi/poi.h Porto_Pontos/Date/date.c Porto_Pontos/Date/date.h
        Genetic_Algorithm/Generation/generation.c Genetic_Algorithm/Generation/generation.h Genetic_Algorithm/Generation_Node/generation_node.c Genetic_Algorithm/Generation_Node/generation_node.h Genetic_Algorithm/Generation_Linked_List/generation_linked_list.c Genetic_Algorithm/Generation_Linked_List/generation_linked_list.h Genetic_Algorithm/main_algorithm.c Genetic_Algorithm/Population/population.c Genetic_Algorithm/Population/population.h Genetic_Algorithm/Chromosome/chromosome.c Genetic_Algorithm/Chromosome/chromosome.h Genetic_Algorithm/Gene/gene.c Genetic_Algorithm/Gene/gene.h Genetic_Algorithm/main_algorithm.h
        Tests/test_Files/test_BIN/test_bin.c Tests/test_Files/test_BIN/test_bin.h Tests/test_Files/test_TXT/test_txt.c Tests/test_Files/test_TXT/test_txt.h Tests/test_Client_List/test_client_list.c Tests/test_Client_List/test_client_list.h
        Tests/test_Trips/test_Booked_Trips/test_booked_trips.c Tests/test_Trips/test_Booked_Trips/test_booked_trips.h Tests/test_Trips/test_Finished_Trips/test_finished_trips.c Tests/test_Trips/test_Finished_Trips/test_finished_trips.h Tests/test_Cities/test_cities.c Tests/test_Cities/test_cities.h Tests/test_Description/test_description.c Tests/test_Description/test_description.h Tests/test_POI/test_poi.c Tests/test_POI/test_poi.h Tests/test_Files/test_Report/test_report.c Tests/test_Files/test_Report/test_report.h)