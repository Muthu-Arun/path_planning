cmake_minimum_required(VERSION 3.10)
project(OpenCVProject)

# Find OpenCV
find_package(OpenCV REQUIRED)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include OpenCV headers
include_directories(
	${OpenCV_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/src
)
# Add executable
add_executable(test
	./src/video_lane_detection.cpp



)

# Link OpenCV libraries
target_link_libraries(test ${OpenCV_LIBS})

