/*
Copyright (c) 2004, Lode Vandevenne
All rights reserved.
*/

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;
using namespace std;

//place the example code below here:
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main(int /*argc*/, char */*argv*/[])
{
  // position vector of player
  double posX = 22, posY = 12;
  // ratio between length of direction and camera plane determines FOV. Here the FOV is 66°
  // initial direction vector
  double dirX = -1, dirY = 0;
  // initial camera plane (line) of player
  double planeX = 0, planeY = 0.66;

  // time of current and previous frames
  double time = 0;
  double oldTime = 0;

  screen(640, 480, "Raycaster");

  // game loop
  while (!done()) {
      // raycasting loop
      for(int x=0; x<w; x++){
        // ray position and direction

        // cameraX is the x coordinate on camera place that represents x of screen. From -1 (left) to 1 (right)
        double cameraX = 2 * x / double(w) - 1; // x coordinate in camera space
        double rayDirX =  dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        // mapX and mapY are coordinate in terms of MAP BLOCKS
        int mapX = int(posX);
        int mapY = int(posY);

        // sideDistX and sideDistY are distance to reach next X or Y square limit
        double sideDistX, sideDistY;

        // deltaDistX and deltaDistY are distance for the ray between a X or Y limit and the next one
        double deltaDistX = std::abs(1 / rayDirX);
        double deltaDistY = std::abs(1 / rayDirY);
        double perpWallDist;

        // stepX and stepY tell if we have positive (1) or negative (-1) Direction
        int stepX, stepY;
        int hit = 0; // wall hit ?
        int side; // North-South or East-West ?

        
      }
  }

  // screen(256, 256, 0, "Small Test Script");
  // for(int x = 0; x < w; x++)
  // for(int y = 0; y < h; y++)
  // {
  //   pset(x, y, ColorRGB(x, y, 128));
  // }
  // print("Hello, world!", 8, 8);
  //
  // std::string test;
  // test.resize(20);
  //
  // redraw();
  // sleep();
}
