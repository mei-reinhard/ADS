cmake_minimum_required(VERSION 4.1)
project(Prakt)

set(CMAKE_CXX_STANDARD 14)

include_directories(P1/Debug)

add_executable(Prakt
        P1/Debug/DoublyLinkedList.cpp
        P1/Debug/DoublyLinkedList.h
        P1/Debug/DoublyLinkedListTest.cpp
        P1/Debug/gip_mini_catch.h
        P1/Debug/main.cpp
        P1/Debug/Node.cpp
        P1/Debug/Node.h)
