cmake_minimum_required( VERSION 2.8 )
project(Project1)

set( CMAKE_BUILD_TYPE "Debug")

find_package( OpenCV REQUIRED )
include_directories( $(OpenCV_INCLUDE_DIRS) )

add_library( seed2des SHARED seed2des.cpp )

add_executable( imgsci main.cpp )
target_link_libraries( imgsci ${OpenCV_LIBS} seed2des)
