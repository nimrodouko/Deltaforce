#! /bin/bash

g++ main.cpp shader.cpp stb_image.cpp -lglfw -lGLEW -lGL -o deltaforce
./deltaforce
