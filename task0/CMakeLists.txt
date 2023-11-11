cmake_minimum_required(VERSION 3.26)
project(task0)

set(CMAKE_CXX_STANDARD 17)

add_executable(task0 main.cpp
        FileReader.cpp
        FileReader.h
        Parser.cpp
        Parser.h
        StatisticStorage.cpp
        StatisticStorage.h
        CSVFileWriter.cpp
        CSVFileWriter.h)

add_subdirectory(Google_Tests)
