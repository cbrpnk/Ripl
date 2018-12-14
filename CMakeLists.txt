cmake_minimum_required(VERSION 3.12.3)
project(ripl)

SET(GCC_COMPILE_FLAGS "-g -Ofast -ffinite-math-only -Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

add_subdirectory(src/snd)
add_executable(ripl src/main.cc)
target_link_libraries(ripl LINK_PUBLIC Snd GL GLU GLEW X11 Xrandr Xi)
install(TARGETS ripl DESTINATION /usr/bin)
