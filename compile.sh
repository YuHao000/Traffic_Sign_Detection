#!/bin/bash
clear
set -e
export env_filename=Traffic_Sign_Detection
n_cores=`cat /proc/cpuinfo | grep processor | wc -l`
let "n_cores++"
mkdir -p build && cd build
cmake ..  &> /dev/null 
make -j$n_cores -b

./Traffic_Sign_Detection


# set -e
#   Any subsequent(*) commands failing makes the shell script to exit.

# mkdir -p
#   creates a folder only if it doesn't exist

# &> /dev/null
#   Suppreses output

# make -j N
#   For minimum build times, you want to use a value of N that is one more than the number of cores on the machine


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
