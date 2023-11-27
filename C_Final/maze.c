#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#include "parameter.h"
#include "showMaze.h"
#include "maze.h"



#include "../C_Final/src/libgraphics/graphics.h"
#include "../C_Final/src/libgraphics/genlib.h"
#include "../C_Final/src/simpleGUI/imgui.h"
#include "../C_Final/src/libgraphics/extgraph.h"

//	初始化迷宫
void initMaze()
{

	//	将地图初始化成全0的
	for (int i = 0; i < mazeCountX; i++)
	{
		for (int j = 0; j < mazeCountY; j++)
		{
			mazeMap[i][j] = 0;
		}
	}
	//	实现空地与墙壁间隔
	for (int i = 0; i < mazeCountX; i++)
	{
		for (int j = 0; j < mazeCountY; j++)
		{

			if (i != 0 && j != 0 && i != mazeCountX - 1 && j != mazeCountY - 1)
			{
				if (i % 2 != 0)
				{
					if (j % 2 == 1)
					{
						mazeMap[i][j] = 1;
					}
				}
			}
		}
	}
	//	mazeLevel == 0，简单模式生成地图
	if (mazeLevel == 0)
	{
		createEasyMaze(1, 1);
	}
	//	mazeLevel == 1，困难模式生成地图
	else if (mazeLevel == 1)
	{
		mazeMap[1][1] = 5;
		mazeMap[1][2] = 6;
		mazeMap[2][1] = 6;
		createHardMaze(1, 1);
	}
	for (int i = 0; i < mazeCountX; i++)
	{
		for (int j = 0; j < mazeCountY; j++)
		{
			if (mazeMap[i][j] == 5)
			{
				mazeMap[i][j] = 1;

			}
		}
	}
	mazeMap[1][0] = 3;
	mazeMap[mazeCountX - 1][mazeCountY - 2] = 4;
}

//	保存迷宫
void saveMaze()
{
	OPENFILENAME ofn;	//	公共对话框结构
	char szFile[MAX_PATH] = "";	//	同来保存获取文件名称的缓冲区
	ZeroMemory(&ofn, sizeof(ofn));	//	初始化文件选择窗口大小
	ofn.lStructSize = sizeof(ofn);	//	指定结构的大小，以字节为单位
	ofn.hwndOwner = NULL;	//	
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";	//	打开文件类型，文本类型
	ofn.lpstrFile = szFile;	//	打开的文件的全路径
	ofn.nMaxFile = MAX_PATH;	//	指定lpstrFile缓冲的大小，以TCHARs为单位
	ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT;	//	位标记的设置，用来初始化对话框

	if (GetSaveFileName(&ofn) == TRUE)
	{
		char filePath[MAX_PATH];
		strcpy(filePath, szFile);
		const char* fileExtension = ".txt";
		size_t extensionPos = strlen(filePath) - 4;
		if (extensionPos == 0 || strcmp(filePath + extensionPos, fileExtension) != 0)
		{
			strcat(filePath, fileExtension);
		}
		strcpy(szFile, filePath);
		FILE* file = fopen(szFile, "w");	//	写
		if (file != NULL)
		{
			for (int i = 0; i < mazeCountX; i++)
			{
				for (int j = 0; j < mazeCountY; j++)
				{
					fprintf(file, "%d,", mazeMap[i][j]);
				}
				fprintf(file, "\n");
			}
			fclose(file);
		}
	}
}

//	打开迷宫
void openMaze()
{
	OPENFILENAME ofn;
	char szFile[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		FILE* file = fopen(szFile, "r");	//	读
		if (file != NULL)
		{
			for (int i = 0; i < mazeCountX; i++)
			{
				for (int j = 0; j < mazeCountY; j++)
				{
					if (fscanf(file, "%d,", &mazeMap[i][j]) != 1)
					{
						fclose(file);
						return;
					}
				}
			}
			fclose(file);
		}
	}
}

//	判断迷宫是否可解
int judgeMaze()
{
	int flag = 0;

	if (findPath(startX, startY, exitX, exitY) == 1)
	{
		flag = 1;
	}
		
	
	return flag;
}

//	生成简单难度迷宫
void createEasyMaze(int xCur, int yCur)
{
	gameOver = 0;
	int x = xCur;
	int y = yCur;
	int flag = 0;
	int randPos = 0;

	//	如果四个方向都没有墙了，返回上一步，否则继续
	while (1)
	{
		flag = 0;
		flag = isHaveNeighbor(xCur, yCur);
		if (flag == 0)
		{
			return;
		}
		else
		{
			mazeMap[xCur][yCur] = 5;
			x = xCur;
			y = yCur;
			while (1)
			{
				randPos = rand() % 4;
				if (randPos == 0 && xCur >= 3 && mazeMap[xCur - 2][yCur] == 1)	//	上
				{
					xCur = xCur - 2;
				}
				else if (randPos == 1 && xCur < mazeCountX - 3 && mazeMap[xCur + 2][yCur] == 1)	//	下
				{
					xCur = xCur + 2;
				}
				else if (randPos == 2 && yCur >= 3 && mazeMap[xCur][yCur - 2] == 1)	//	左
				{
					yCur = yCur - 2;
				}
				else if (randPos == 3 && yCur < mazeCountX - 3 && mazeMap[xCur][yCur + 2] == 1)	//	右
				{
					yCur = yCur + 2;
				}
				else
				{
					if (isHaveNeighbor(x, y) == 0)
					{

						break;
					}
					else
					{

						continue;
					}
				}

				mazeMap[(x + xCur) / 2][(y + yCur) / 2] = 5;
				mazeMap[xCur][yCur] = 5;
				createEasyMaze(xCur, yCur);	//	递归
				break;
			}

		}
	}


}

//	生成困难难度迷宫
void createHardMaze(int xCur, int yCur)
{
	gameOver = 0;
	int i = 0;
	int j = 0;
	int randPoint = 0;
	int x = 1;
	int y = 2;
	int flag = 0;
	while (1)
	{
		flag = isHaveNeighbor(xCur, yCur);
		if (flag == 0)
			return;
		else
		{
			while (1)
			{
				//	如果目前剩余1个蓝色方块
				if (flag == 1)
				{
					randPoint = 0;
				}

				else
				{
					randPoint = rand() % flag;	//	随机一个小于flag的数，用于随机选取蓝色方块
				}

				for (i = 0; i < mazeCountX; i++)
				{
					for (j = 0; j < mazeCountY; j++)
					{
						if (mazeMap[i][j] == 6 && randPoint == 0)
						{
							x = i;
							y = j;
							break;
						}
						else if (mazeMap[i][j] == 6)
						{
							randPoint--;
						}
					}
					if (mazeMap[i][j] == 6 && randPoint == 0)
					{
						break;
					}
				}
				if (mazeMap[x + 1][y] == 5)	//	向上
				{
					if (mazeMap[x - 1][y] == 1)
					{
						mazeMap[x - 1][y] = 5;
						mazeMap[x][y] = 5;
						x = x - 1;
					}
					else
					{
						mazeMap[x][y] = 0;
						break;
					}
				}
				else if (mazeMap[x - 1][y] == 5)	//	向下
				{
					if (mazeMap[x + 1][y] == 1)
					{
						mazeMap[x + 1][y] = 5;
						mazeMap[x][y] = 5;
						x = x + 1;
					}
					else
					{
						mazeMap[x][y] = 0;
						break;
					}
				}
				else if (mazeMap[x][y + 1] == 5)	//	向左
				{
					if (mazeMap[x][y - 1] == 1)
					{
						mazeMap[x][y - 1] = 5;
						mazeMap[x][y] = 5;
						y = y - 1;
					}
					else
					{
						mazeMap[x][y] = 0;
						break;
					}
				}
				else if (mazeMap[x][y - 1] == 5)	//	向右
				{
					if (mazeMap[x][y + 1] == 1)
					{
						mazeMap[x][y + 1] = 5;
						mazeMap[x][y] = 5;
						y = y + 1;
					}
					else
					{
						mazeMap[x][y] = 0;
						break;
					}
				}
				if (xCur > 1 && mazeMap[xCur - 1][yCur] == 0)
				{
					mazeMap[xCur - 1][yCur] = 6;
				}

				if (yCur > 1 && mazeMap[xCur][yCur - 1] == 0)
				{
					mazeMap[xCur][yCur - 1] = 6;
				}
				if (xCur < mazeCountX - 2 && mazeMap[xCur + 1][yCur] == 0)
				{
					mazeMap[xCur + 1][yCur] = 6;
				}

				if (yCur < mazeCountY - 2 && mazeMap[xCur][yCur + 1] == 0)
				{
					mazeMap[xCur][yCur + 1] = 6;
				}
				xCur = x;
				yCur = y;
				break;
			}
		}

	}

}

//	寻找相邻路径
int isHaveNeighbor(int xCur, int yCur)
{
	int flag = 0;
	if (mazeLevel == 0)
	{


		if ((xCur >= 3 && mazeMap[xCur - 2][yCur] == 1) || (xCur < mazeCountX - 3 && mazeMap[xCur + 2][yCur] == 1)
			|| (yCur >= 3 && mazeMap[xCur][yCur - 2] == 1) || (yCur < mazeCountY - 3 && mazeMap[xCur][yCur + 2] == 1))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	if (mazeLevel == 1)
	{
		for (int i = 0; i < mazeCountX; i++)
		{
			for (int j = 0; j < mazeCountY; j++)
			{
				if (mazeMap[i][j] == 6)	//	还存在蓝色方块
				{
					flag++;
				}

			}
		}
		return flag;
	}


}

//	队列初始化
void initQueue(struct Queue* queue)
{
	//	初始化队列
	queue->front = NULL;
	queue->rear = NULL;
}

//	判断队列是否为空
bool isQueueEmpty(struct Queue* queue)
{
	return queue->front == NULL;
}

//	判断是否可走
bool isPath(int x, int y)
{
	return (mazeMap[x][y] != 0);
}

//	判断当前位置是否有效
bool isValid(int x, int y)
{
	return (x >= 0 && x < mazeCountX && y >= 0 && y < mazeCountY);
}

//	入列
void enqueue(struct Queue* queue, int x, int y)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	if (!newNode)
	{
		return;
	}
	newNode->x = x;
	newNode->y = y;
	newNode->next = NULL;

	if (queue->rear == NULL) 
	{
		queue->front = newNode;
		queue->rear = newNode;
	}
	else 
	{
		queue->rear->next = newNode;
		queue->rear = newNode;
	}
}

//	出列
struct Node* dequeue(struct Queue* queue)
{
	if (queue->front == NULL) 
	{
		return NULL;
	}

	struct Node* node = queue->front;
	queue->front = queue->front->next;

	if (queue->front == NULL) 
	{
		queue->rear = NULL;
	}

	return node;
}

//	寻找可行路径
int findPath(int pathStartX, int pathStartY, int pathEndX, int pathEndY)
{
	int recordStart = mazeMap[pathStartX][pathStartY];
	int recordEnd = mazeMap[pathEndX][pathEndY];

	mazeMap[pathStartX][pathStartY] = 1;
	mazeMap[pathEndX][pathEndY] = 1;
	//	用于控制上、下、左、右四个方向
	int directionX[] = { -1, 1, 0, 0 };
	int directionY[] = { 0, 0, -1, 1 };

	struct Queue queue;
	initQueue(&queue);

	//	初始化路径数组
	for (int i = 0; i < mazeCountX; i++)
	{
		for (int j = 0; j < mazeCountY; j++)
		{
			path[i][j] = -1;
		}
	}

	enqueue(&queue, pathStartX, pathStartY);
	path[pathStartX][pathStartY] = -2;

	while (!isQueueEmpty(&queue))
	{
		struct Node* currentNode = dequeue(&queue);
		int currentX = currentNode->x;
		int currentY = currentNode->y;
		free(currentNode);

		if (currentX == pathEndX && currentY == pathEndY)
		{
			mazeMap[pathStartX][pathStartY] = recordStart;
			mazeMap[pathEndX][pathEndY] = recordEnd;
			return 1;
		}
		//	记录当前位置行进方向
		for (int i = 0; i < 4; i++)
		{
			int newX = currentX + directionX[i];
			int newY = currentY + directionY[i];

			if (isValid(newX, newY) && isPath(newX, newY) && path[newX][newY] == -1)
			{
				enqueue(&queue, newX, newY);
				path[newX][newY] = i;
			}
		}
	}

	mazeMap[pathStartX][pathStartY] = recordStart;
	mazeMap[pathEndX][pathEndY] = recordEnd;
	return 0;
}

//	提示最短路径
void printPath(int pathStartX, int pathStartY, int pathEndX, int pathEndY)
{
	if (autoSolve == 1)
	{
		for (int i = 0; i < mazeCountX; i++)
		{
			for (int j = 0; j < mazeCountY; j++)
			{
				if (mazeMap[i][j] == 6)
				{
					mazeMap[i][j] = 1;
				}
			}
		}
	}

	int x = pathEndX;
	int y = pathEndY;
	int count = 0;

	int directionX[] = { -1, 1, 0, 0 };
	int directionY[] = { 0, 0, -1, 1 };

	//	根据路径数组行进
	while (x != pathStartX || y != pathStartY)
	{
		int direction = path[x][y];
		x = x - directionX[direction];
		y = y - directionY[direction];
		count++;
	}

	int pathLength = count + 1;	//	加上终点
	struct Node** pathArray = (struct Node**)malloc(pathLength * sizeof(struct Node*));
	count = 0;

	x = pathEndX;
	y = pathEndY;

	while (x != pathStartX || y != pathStartY)
	{
		//	根据路径数组行进
		int direction = path[x][y];
		x = x - directionX[direction];
		y = y - directionY[direction];

		struct Node* node = (struct Node*)malloc(sizeof(struct Node));
		if (!node)
		{
			return;
		}
		node->x = x;
		node->y = y;
		node->next = NULL;
		//	存储提示位置信息
		pathArray[count] = node;
		count++;
	}

	for (int i=pathLength-3; i>=0; i--)
	{
		if (mazeMap[pathArray[i]->x][pathArray[i]->y] == 1)
		{
			mazeMap[pathArray[i]->x][pathArray[i]->y] = 6;
		}
	}
	Show();

	for (int i = 0; i < pathLength - 1; i++)
	{
		free(pathArray[i]);
	}
	free(pathArray);
}

//	提示下一步
void printNextStep(int pathStartX, int pathStartY, int pathEndX, int pathEndY)
{
	for (int i = 0; i < mazeCountX; i++)
	{
		for (int j = 0; j < mazeCountY; j++)
		{
			if (mazeMap[i][j] == 6)
			{
				mazeMap[i][j] = 1;
			}
		}
	}

	int x = pathEndX;
	int y = pathEndY;
	int count = 0;
	int directionX[] = { -1, 1, 0, 0 };
	int directionY[] = { 0, 0, -1, 1 };

	while (x != pathStartX || y != pathStartY)
	{
		//	沿路径数组方向行进
		int direction = path[x][y];
		x = x - directionX[direction];
		y = y - directionY[direction];
		count++;
	}

	int pathLength = count + 1;
	struct Node** pathArray = (struct Node**)malloc(pathLength * sizeof(struct Node*));
	count = 0;
	x = pathEndX;
	y = pathEndY;

	while (x != pathStartX || y != pathStartY)
	{
		int direction = path[x][y];
		x = x - directionX[direction];
		y = y - directionY[direction];
		struct Node* node = (struct Node*)malloc(sizeof(struct Node));
		if (!node)
		{
			return;
		}
		node->x = x;
		node->y = y;
		node->next = NULL;
		pathArray[count++] = node;
	}

	int i = pathLength - 3;
	//	每次只输出一步
	if (i >= 0 && mazeMap[pathArray[i]->x][pathArray[i]->y] == 1)
	{
		mazeMap[pathArray[i]->x][pathArray[i]->y] = 6;
	}
	Show();

	for (int i = 0; i < pathLength - 1; i++)
	{
		free(pathArray[i]);
	}
	free(pathArray);
}