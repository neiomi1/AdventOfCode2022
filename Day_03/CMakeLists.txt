# CMakeList.txt : CMake project for AdventofCodeDay1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (AdventofCodeDay_03 "Day_03.cpp" "Day_03.h")

# TODO: Add tests and install targets if needed.
target_compile_options(AdventofCodeDay_03 PRIVATE /W4 /WX /permissive-)