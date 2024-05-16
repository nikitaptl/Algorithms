cmake_minimum_required(VERSION 3.26)
project(Algorithms)

set(CMAKE_CXX_STANDARD 23)

add_executable(Algorithms main.cpp
        Sort.cpp
        algorithms.h
        StringMergeSort.cpp
        StringQuickSort.cpp
        MSDRadixSort.cpp)
