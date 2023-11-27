#include "src/libgraphics/boolean.h"
#ifndef _H_MAZE
#define _H_MAZE
void createHardMaze(int xCur, int yCur);
void createEasyMaze(int xCur, int yCur);
int isHaveNeighbor(int xCur, int yCur);
void initMaze();
int judgeMaze();
void initQueue(struct Queue* queue);
bool isQueueEmpty(struct Queue* queue);
void enqueue(struct Queue* queue, int x, int y);
struct Node* dequeue(struct Queue* queue);
bool isPath(int x, int y);
bool isValid(int x, int y);
int findPath(int pathStartX, int pathStartY, int pathEndX, int pathEndY);
void printPath(int pathStartX, int pathStartY, int pathEndX, int pathEndY);
void printNextStep(int pathStartX, int pathStartY, int pathEndX, int pathEndY);
#endif