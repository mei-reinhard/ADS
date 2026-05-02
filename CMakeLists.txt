cmake_minimum_required(VERSION 4.1)
project(Prakt)

set(CMAKE_CXX_STANDARD 14)

include_directories(P1Template/Debug)

add_executable(Prakt
        P1Template/Debug/DoublyLinkedList.cpp
        P1Template/Debug/DoublyLinkedList.h
        P1Template/Debug/DoublyLinkedListTest.cpp
        P1Template/Debug/gip_mini_catch.h
        P1Template/Debug/main.cpp
        P1Template/Debug/Node.cpp
        P1Template/Debug/Node.h)
