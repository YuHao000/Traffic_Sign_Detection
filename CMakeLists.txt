cmake_minimum_required(VERSION 2.8)
project( $ENV{env_filename} )

file(GLOB_RECURSE SOURCES
	"header/*.hpp"
	"src/*.cpp"
	"../Academic_ComputerVision/code/header/*.hpp"	# Temporary location of cv_lib
	"../Academic_ComputerVision/code/src/*.cpp"	# Temporary location of cv_lib
)

SET(CMAKE_CXX_FLAGS "-std=c++14")

find_package( OpenCV REQUIRED )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable( ${PROJECT_NAME} ${PROJECT_NAME}.cpp ${SOURCES})

#target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} Threads::Threads)


# Why C++14?
#   use of ‘auto’ in parameter declaration only available with -std=c++14

# cmake_minimum_required(VERSION 2.8)
#   This line must go first in the file

# project($ENV{env_filename})
#   avoids creating a variable for the name, allowing to use ${PROJECT_NAME} whenever its necessary
#   This allows to place project() before anything else but cmake_minimum_required()


#
# Author:      Eduardo Cáceres de la Calle
# Subject:     Visión Artificial
# Degree:      Industrial Electronics and Automatic Control Engineering
# University:  Universidad de Valladolid (UVa) - EII
#
# Code written in 2017, during my first contact with OpenCV.
# Uploaded for educational purposes only.
#
#
