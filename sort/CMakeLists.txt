cmake_minimum_required(VERSION 3.7)
project(sort)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        inversionpair.h
        main.cpp
        mySort.h
        quickselection.h
        sortHelper.h maxheap.h)

add_executable(sort ${SOURCE_FILES})