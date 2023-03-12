cmake_minimum_required(VERSION 3.25)
project(CourseDesign)
aux_source_directory(../src SRC)
add_executable(${PROJECT_NAME} ${SRC})


set(CMAKE_BUILD_TYPE "Debug")