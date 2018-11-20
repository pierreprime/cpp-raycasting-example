## Goal

Raycasting example in C++ language with SDL 1.2, see install guide here https://lodev.org/cgtutor/quickcg.html
Follow tutorial, test speed change, texture & sprite size change (64x64 to 128x128) with pre-made images

Determine if C++ can easily be compiled for Atari and Dreamcast. If not convert this program to C in next repo.
Test adding GFXEngine layer on C++. No networking for now.

A CG library is provided by lodev : quickcg.

## Build with g++ and run

With g++ it's quite easy: place all .cpp and .h files of QuickCG in the same directory, put the example code of tutorials in the main.cpp file, and then you can compile it with the following command:

```
g++ *.cpp -lSDL -O3
```

The -O3 is optional if you want compiler optimization. The -lSDL lets it link to SDL. This requires you to have SDL installed on your distro (look for sdl and sdl-devel packages or similar). 

## Notes

FastCG includes a FPS counter.
