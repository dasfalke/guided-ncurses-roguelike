#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>

void AddPositionYX(int **frontier, int y, int x, int count);
int AddNeighbors(int **frontier, int ***cameFrom, int count, int y, int x);
void *SafeMalloc(size_t size);

#endif /* UTILS_H */
