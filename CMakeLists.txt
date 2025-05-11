cmake_minimum_required(VERSION 3.28.3)
project(OS_project)
set(CMAKE_CXX_STANDARD 20)

add_executable(
        OS_project src/main.cpp
        include/schedulerServices.h
        include/MetricsServices.h
        include/ProcessServices.h
        include/GUI.h
)