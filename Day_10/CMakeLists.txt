# CMakeList.txt : CMake project for AdventofCodeDay1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (AdventofCodeDay_10 "Day_10.cpp" "Day_10.h")

# TODO: Add tests and install targets if needed.
target_compile_options(AdventofCodeDay_10 PRIVATE /W4 /WX /permissive-)