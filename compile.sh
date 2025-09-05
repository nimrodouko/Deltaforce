#! /bin/bash

g++ main.cpp shader.cpp -lglfw -lGLEW -lGL -o deltaforce
./deltaforce
