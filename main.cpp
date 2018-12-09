/*
Copyright (c) 2004, Lode Vandevenne
All rights reserved.
*/

#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <nlohmann/json.hpp>
// C++ equivalent of associative array
#include <unordered_map>

#include "quickcg.h"

using namespace QuickCG;
using namespace std;
using json = nlohmann::json;

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
	// load stream from JSON level file
	//std::ifstream fileStream("levels/001.json", std::ifstream::binary);
	//json myJsonObject;
	//myJsonObject << fileStream;
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

           	// calculate step and initial sideDist
          	if(rayDirX < 0){
          		stepX = -1;
          		// distance to reach next X limit
          		sideDistX = (posX - mapX) * deltaDistX;
                  }
          	else {
          		stepX = 1;
          		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
          	}
          	if(rayDirY < 0){
          		stepY = -1;
          		// distance to reach next Y limit
          		sideDistY = (posY - mapY) * deltaDistY;
          	}
          	else {
          		stepY = 1;
          		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
          	}

          	// DDA loop
          	while(hit == 0){
          		// jump to next square, either in X or Y direction
          		if(sideDistX < sideDistY){
          			// real sideDist incremented with delta
          			sideDistX += deltaDistX;
          			mapX += stepX;
          			// hit vertical side
          			side = 0;
          		}
          		else {
          			sideDistY += deltaDistY;
          			mapY += stepY;
          			// hit horizontal side
          			side = 1;
          		}

          		// check if ray hit a wall
          		if(worldMap[mapX][mapY] > 0)
          			hit = 1;
          	}

          	// then distance of ray to the wall
          	// if vertical side is hit, number of square ray crossed in X direction :
          	if(side == 0)
          		perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
          	else
          		perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

          	// From distance, deduct line height to be drawn on the screen
          	// Inverse of perpWallDist multiplied by h
          	int lineHeight = (int)(h / perpWallDist);

          	// calculate highest and lowest pixel to fill
          	int drawStart = -lineHeight / 2 + h / 2;
          	if(drawStart < 0)
          		drawStart = 0;

          	int drawEnd = lineHeight / 2 + h / 2;
          	if(drawEnd >= h)
          		drawEnd = h - 1;

          	// following case number, color chosen. If Y side, darker.
          	ColorRGB color;
          	switch(worldMap[mapX][mapY]){
          		case 1:
          			color = RGB_Red;
          			break;
          		case 2:
          			color = RGB_Green;
          			break;
          		case 3:
          			color = RGB_Blue;
          			break;
          		case 4:
          			color = RGB_White;
          			break;
          		default:
          			color = RGB_Yellow;
          			break;
          	}

          	// x and y brightness variations
          	if(side == 1){
          		color = color / 2;
          	}

          	// draw pixels of stripe
          	verLine(x, drawStart, drawEnd, color);
          }

        	// input and FPS counter
        	oldTime = time;
        	time = getTicks();
        	// time this frame took in seconds
        	double frameTime = (time - oldTime) / 1000.0;
        	print(1.0 / frameTime); // FPS counter
        	redraw();
        	cls();

        	// speed modifiers
        	double moveSpeed = frameTime * 5.0; // in squares/sec
        	double rotSpeed = frameTime * 3.0; // in radians/sec

        	// controls (if new position inside wall, won't move). Single check for now
        	readKeys();
        	if(keyDown(SDLK_UP)){
        		if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false){
        			posX += dirX * moveSpeed;
        		}
        		if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false){
        			posY += dirY * moveSpeed;
        		}
        	}
        	if(keyDown(SDLK_DOWN)){
        		if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false){
        			posX -= dirX * moveSpeed;
        		}
        		if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false){
        			posY -= dirY * moveSpeed;
        		}
        	}

        	// rotate
        	if(keyDown(SDLK_RIGHT)){
        		double oldDirX = dirX;
        		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);

        		double oldPlaneX = planeX;
        		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        	}
          if(keyDown(SDLK_LEFT)){
        		double oldDirX = dirX;
        		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);

        		double oldPlaneX = planeX;
        		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        	}
      }

      ////////////////////////
      // UNCOMMENT IF SDL TEST
      ////////////////////////
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
