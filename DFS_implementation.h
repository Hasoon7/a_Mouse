#pragma once

typedef struct {
    int x;
    int y;
} Cell;

bool visited[6][6];
Cell path[6 * 6];
int pathLen = 0;

int dx[4] = { 0, -1, 0, 1 };
int dy[4] = { -1, 0, 1, 0 };

bool dfsPath(int x, int y, int fx, int fy);