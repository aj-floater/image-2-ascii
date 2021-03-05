cmake_minimum_required(VERSION 3.0.0)
set( "OpenCV_DIR" "E:\\OpenCVDirs\\opencv3\\install" )
project(image-2-ascii VERSION 0.1.0)

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories( ${OpenCV_INCLUDE_DIRS} ./src )

add_executable( image-2-ascii ./src/main.cpp )
TARGET_LINK_LIBRARIES ( image-2-ascii ${OpenCV_LIBS} )