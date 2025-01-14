cmake_minimum_required(VERSION 3.10)
project(OpenCVProject)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable
add_executable(main ./source/main.cpp)

# Link OpenCV libraries
target_link_libraries(main ${OpenCV_LIBS})

