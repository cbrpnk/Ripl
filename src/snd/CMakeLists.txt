cmake_minimum_required(VERSION 3.12.3)

file(GLOB_RECURSE SND "./*.c")
add_library(Snd ${SND})
target_link_libraries(Snd LINK_PUBLIC m portaudio asound jack pthread) 
