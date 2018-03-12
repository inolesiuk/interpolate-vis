cmake_minimum_required(VERSION 3.9)
project(Interpolate)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)

add_executable(Interpolate main.cpp Train.h Train.cpp Visualisation.h Point.h Visualisation.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(Interpolate ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

