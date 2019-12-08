cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(Prototipo)

set(OpenCV_STATIC ON)
set(BUILD_SHARED_LIBS OFF)
SET(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/opencv/lib/cmake/opencv4")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenCV REQUIRED PATHS "${OpenCV_DIR}")
find_package (Threads)
add_subdirectory(src/niclib)

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${nic_INCLUDE_DIRS} )
message(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)
add_executable(${PROJECT_NAME}2 main2.cpp)

target_link_libraries ( ${PROJECT_NAME} PUBLIC ${OpenCV_LIBS} )
target_link_libraries ( ${PROJECT_NAME}2 PUBLIC ${OpenCV_LIBS} )
target_link_libraries(${PROJECT_NAME} PRIVATE nic)
target_link_libraries(${PROJECT_NAME}2 PRIVATE nic)

target_link_libraries ( ${PROJECT_NAME} PUBLIC ${CMAKE_THREAD_LIBS_INIT} )