cmake_minimum_required(VERSION 3.20)
project(esercitazione4) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla -Wno-sign-compare")

set(SRC_rf esempio_randfiller.cpp)
add_executable(esempio_randfiller ${SRC_rf})

set(SRC_tc esempio_timecounter.cpp timecounter.cpp)
add_executable(esempio_timecounter ${SRC_tc})

add_executable(test_bubblesort test_bubblesort.cpp)
add_test(NAME bubblesort COMMAND test_bubblesort)

add_executable(test_insertion_sort test_insertion_sort.cpp)
add_test(NAME insertion_sort COMMAND test_insertion_sort)

add_executable(test_selection_sort test_selection_sort.cpp)
add_test(NAME selection_sort COMMAND test_selection_sort)

enable_testing()

set(SRC_test_sorts timecounter.cpp measure_sorts.cpp)
add_executable(measure_sorts ${SRC_test_sorts})