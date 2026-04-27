cmake_minimum_required(VERSION 4.1)
project(P1)

set(CMAKE_CXX_STANDARD 14)

include_directories(Debug)

add_executable(P1
        Debug/DoublyLinkedList.cpp
        Debug/DoublyLinkedList.h
        Debug/DoublyLinkedListTest.cpp
        Debug/gip_mini_catch.h
        Debug/main.cpp
        Debug/Node.cpp
        Debug/Node.h)
