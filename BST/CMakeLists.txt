cmake_minimum_required(VERSION 3.7)
project(BST)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        binarySearch.h
        BST.h
        main.cpp)

add_executable(BST ${SOURCE_FILES})