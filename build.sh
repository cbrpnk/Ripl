#!/bin/bash

mkdir build
cd build
cmake ..
make && ./ripl ../example/song.lua
