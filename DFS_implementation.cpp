#include "DFS_implementation.h"

bool DFS_implementation::dfsPath(int x, int y, int fx, int fy) {
    visited[x][y] = true;

    path[pathLen++] = (Cell){x, y};

    if (x == fx && y == fy)
        return true;

    for (int dir = 0; dir < 4; dir++) {

        if (myMaze.maze[x][y][dir])
            continue;

        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (visited[nx][ny])
            continue;

        if (dfsPath(nx, ny, fx, fy))
            return true;
    }

    pathLen--;
    return false;
}
