#include "MazeRepresentation.h"

MazeRepresentation::MazeRepresentation() {
    //sets all walls in the maze and on its borders to be false, meaning there are no walls currently
    mouseHeading = East;
    memset(maze, false, sizeof(maze));
    memset(checkedCells , false , sizeof(checkedCells));
    //sets the walls above each cell in the first row to be true, meaning the north border now exists
    for (int i = 0 ; i < 6 ; i++) {
        maze[0][i][1]=true;
    }
    //sets the walls left of each cell in the first column to be true, meaning the west border now exists
    for (int i = 0 ; i < 6 ; i++) {
        maze[i][0][0]=true;
    }
    //sets the walls under each cell in the last row to be true, meaning the south border now exists
    for (int i = 0 ; i < 6 ; i++) {
        maze[5][i][3]=true;
    }
    //sets the walls right of each cell in the last column to be true, meaning the east border now exists
    for (int i = 0 ; i < 6 ; i++) {
        maze[i][5][2]=true;
    }
}

void MazeRepresentation::updateCellSurroundingWalls(int x, int y, heading head) {
    //the expression (head+3)%4 guarantees that it gives you the correct direction when the robot turns right
    //same as (head+1)%4 for the direction when the robot turns left
    //since the wall to the right of a cell is the same as the wall to the left of the cell to its right then they should have the same value
    //for example the wall to the left of the cell (4,3) is the same as the wall to the right of the cell (4,2)

    //these long if statements just basically check whether the robot is at the edge of the maze
    //which if it is and the heading is in a specific way, then there is no cell to the left(or some direction based on the heading) of it doesn't exist
    //so it would be an out of bounds exception since the number of the cell that doesn't exist in the map is not in the set {0 --> 5}
    maze[x][y][(head+3)%4] = checkIfWallIsInDirection(Left);
    if( (!(x == 0 && head == East)) && (!(x == 5 && head == West)) && (!(y == 0 && head == North)) && (!(y == 5 && head == South)) )
        maze[getLeftCell(x,y,head).first][getLeftCell(x,y,head).second][(head+2)%4] = maze[x][y][(head+3)%4];

    maze[x][y][head] = checkIfWallIsInDirection(Front);
    if( (!(x == 0 && head == North)) && (!(x == 5 && head == South)) && (!(y == 0 && head == West)) && (!(y == 5 && head == East)) )
        maze[getFrontCell(x,y,head).first][getFrontCell(x,y,head).second][(head+2)%4] = maze[x][y][head];

    maze[x][y][(head+1)%4] = checkIfWallIsInDirection(Right);
    if( (!(x == 0 && head == West)) && (!(x == 5 && head == East)) && (!(y == 0 && head == South)) && (!(y == 5 && head == North)) )
        maze[getRightCell(x,y,head).first][getRightCell(x,y,head).second][(head+2)%4] = maze[x][y][(head+1)%4];
}


std::pair<int,int> MazeRepresentation::getLeftCell(int x , int y , heading head) {
    if (head == West)       return std::make_pair( x + 1 ,y );

    if (head == North)      return std::make_pair( x , y - 1 );

    if (head == East)       return std::make_pair( x - 1 ,y );

    return std::make_pair( x , y + 1);
}

std::pair<int,int> MazeRepresentation::getFrontCell(int x , int y , heading head) {
    if (head == West)       return std::make_pair( x , y - 1 );

    if (head == North)      return std::make_pair( x - 1 ,y );

    if (head == East)       return std::make_pair( x , y + 1);

    return std::make_pair( x + 1 , y );
};

std::pair<int, int> MazeRepresentation::getRightCell(int x, int y, heading head) {
    if (head == West)       return std::make_pair( x - 1 , y );

    if (head == North)      return std::make_pair( x , y + 1 );

    if (head == East)       return std::make_pair( x + 1 , y );

    return std::make_pair( x , y - 1);
}

std::pair<int,int> MazeRepresentation::getBackCell(int x , int y , heading head) {
    if (head == West)       return std::make_pair( x , y + 1 );

    if (head == North)      return std::make_pair( x + 1 , y );

    if (head == East)       return std::make_pair( x , y - 1);

    return std::make_pair( x - 1 , y );
}

void MazeRepresentation::changeHeading(int turn){
  if (turn == East/*to right*/) {
      mouseHeading=(heading)((mouseHeading+1)%4);
  }
  else if (turn == West/*to left*/) {
      mouseHeading=(heading)((mouseHeading+3)%4);
  }
}

int MazeRepresentation::relative_to_absolute(int relative_direction) {
    return (mouseHeading + (relative_direction == 0 ? 3 :
                       relative_direction == 1 ? 0 :
                       relative_direction == 2 ? 1 : 2)) % 4;
}

void MazeRepresentation::goingToLeftCell(){
    turnLeft();
    changeHeading(West);
    moveForward();
    currentPosition.first = getLeftCell(currentPosition.first , currentPosition.second , mouseHeading).first;
    currentPosition.second = getLeftCell(currentPosition.first , currentPosition.second , mouseHeading).second;
}

void MazeRepresentation::goingToRightCell(){
    turnRight();
    changeHeading(East);
    moveForward();
    currentPosition.first = getRightCell(currentPosition.first , currentPosition.second , mouseHeading).first;
    currentPosition.second = getRightCell(currentPosition.first , currentPosition.second , mouseHeading).second;
}
