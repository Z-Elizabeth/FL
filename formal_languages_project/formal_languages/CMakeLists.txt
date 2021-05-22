cmake_minimum_required(VERSION 3.10)

set(PROJECT formal_languages)
project(&{PROJECT})

set(CMAKE_CXX_STANDARD 11)

set(HEADERS appearance.h arrow.h circle.h mainwindow.h scribblearea.h tex.h text.h)
set(SOURCES appearance.cpp arrow.cpp circle.cpp main.cpp mainwindow.cpp sqribblearea.cpp tex.cpp text.cpp)

add_executable(${PROJECT} ${HEADERS} ${SOURCES})

include_directories("./")