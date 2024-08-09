cmake_minimum_required(VERSION 3.5)

project(chess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "" CACHE PATH "QT Installation Folder")

add_subdirectory(chess2)
