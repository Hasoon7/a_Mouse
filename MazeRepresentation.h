#pragma once
#include <bits/stdc++.h>
using namespace std;
/*
to get a basic idea of how the code (or rather the way of implementing the robot moving through the maze) works.
is by understanding that the maze and its cells are constant, as in the north side of a cell is always pointed upwards in each and every cell.
however the robot since it turns in all directions and is moving around the map constantly
there had to be a variable assigned to it that tells you where it is directed.
the maze representation is just a 6*6*4 booleans telling you if there is a wall in the direction(heading) at the cell (x,y)
this is done by a 3D array, the first 'D' in the array is the x coordinates(not the mathematical default distribution)
the second one is the y coordinates, both of which are contained in the set {0,1,2,3,4,5} , and the last one is the direction of the wall with respect to the coordinates.
the coordinates are represented as such:
(0,0)  (0,1) .....

(1,0)  .....

(2,0)  ....

  |
  |
*/

//enum definitions
enum heading : int
{West , North , East , South};
enum direction : int
{Left , Front , Right};

//functions used in both .ino and .cpp
int readLeftSensor();
int readFrontSensor();
int readRightSensor();
bool checkIfWallIsInDirection(int d);
void turnLeft();
void moveForward();
void turnRight();


//properties
bool maze[6][6][4];
bool checkedCells[6][6];
heading mouseHeading = East;
pair <int,int> currentPosition = std::make_pair(0 , 0);


void initializeMaze();

pair<int,int> getLeftCell(int x , int y , heading head);
pair<int,int> getFrontCell(int x , int y , heading head);
pair<int,int> getRightCell(int x , int y , heading head);
pair<int,int> getBackCell(int x , int y , heading head);

void updateCellSurroundingWalls(int x , int y , heading head);

void changeHeading(int turn);

void goingToLeftCell();
void goingToRightCell();

int relative_to_absolute(int relative_direction);

