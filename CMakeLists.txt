cmake_minimum_required(VERSION 3.12.3)
project(ripl)

SET(GCC_COMPILE_FLAGS "-g -O3 -Wall -ffast-math")

add_subdirectory(src/snd)
add_executable(ripl src/main.c)
target_link_libraries(ripl LINK_PUBLIC Snd lua)
install(TARGETS ripl DESTINATION /usr/bin)
