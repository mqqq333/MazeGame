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

//	��ʼ���Թ�
void initMaze()
{

	//	����ͼ��ʼ����ȫ0��
	for (int i = 0; i < mazeCountX; i++)
	{
		for (int j = 0; j < mazeCountY; j++)
		{
			mazeMap[i][j] = 0;
		}
	}
	//	ʵ�ֿյ���ǽ�ڼ��
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
	//	mazeLevel == 0����ģʽ���ɵ�ͼ
	if (mazeLevel == 0)
	{
		createEasyMaze(1, 1);
	}
	//	mazeLevel == 1������ģʽ���ɵ�ͼ
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

//	�����Թ�
void saveMaze()
{
	OPENFILENAME ofn;	//	�����Ի���ṹ
	char szFile[MAX_PATH] = "";	//	ͬ�������ȡ�ļ����ƵĻ�����
	ZeroMemory(&ofn, sizeof(ofn));	//	��ʼ���ļ�ѡ�񴰿ڴ�С
	ofn.lStructSize = sizeof(ofn);	//	ָ���ṹ�Ĵ�С�����ֽ�Ϊ��λ
	ofn.hwndOwner = NULL;	//	
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";	//	���ļ����ͣ��ı�����
	ofn.lpstrFile = szFile;	//	�򿪵��ļ���ȫ·��
	ofn.nMaxFile = MAX_PATH;	//	ָ��lpstrFile����Ĵ�С����TCHARsΪ��λ
	ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT;	//	λ��ǵ����ã�������ʼ���Ի���

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
		FILE* file = fopen(szFile, "w");	//	д
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

//	���Թ�
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
		FILE* file = fopen(szFile, "r");	//	��
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

//	�ж��Թ��Ƿ�ɽ�
int judgeMaze()
{
	int flag = 0;

	if (findPath(startX, startY, exitX, exitY) == 1)
	{
		flag = 1;
	}
		
	
	return flag;
}

//	���ɼ��Ѷ��Թ�
void createEasyMaze(int xCur, int yCur)
{
	gameOver = 0;
	int x = xCur;
	int y = yCur;
	int flag = 0;
	int randPos = 0;

	//	����ĸ�����û��ǽ�ˣ�������һ�����������
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
				if (randPos == 0 && xCur >= 3 && mazeMap[xCur - 2][yCur] == 1)	//	��
				{
					xCur = xCur - 2;
				}
				else if (randPos == 1 && xCur < mazeCountX - 3 && mazeMap[xCur + 2][yCur] == 1)	//	��
				{
					xCur = xCur + 2;
				}
				else if (randPos == 2 && yCur >= 3 && mazeMap[xCur][yCur - 2] == 1)	//	��
				{
					yCur = yCur - 2;
				}
				else if (randPos == 3 && yCur < mazeCountX - 3 && mazeMap[xCur][yCur + 2] == 1)	//	��
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
				createEasyMaze(xCur, yCur);	//	�ݹ�
				break;
			}

		}
	}


}

//	���������Ѷ��Թ�
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
				//	���Ŀǰʣ��1����ɫ����
				if (flag == 1)
				{
					randPoint = 0;
				}

				else
				{
					randPoint = rand() % flag;	//	���һ��С��flag�������������ѡȡ��ɫ����
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
				if (mazeMap[x + 1][y] == 5)	//	����
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
				else if (mazeMap[x - 1][y] == 5)	//	����
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
				else if (mazeMap[x][y + 1] == 5)	//	����
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
				else if (mazeMap[x][y - 1] == 5)	//	����
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

//	Ѱ������·��
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
				if (mazeMap[i][j] == 6)	//	��������ɫ����
				{
					flag++;
				}

			}
		}
		return flag;
	}


}

//	���г�ʼ��
void initQueue(struct Queue* queue)
{
	//	��ʼ������
	queue->front = NULL;
	queue->rear = NULL;
}

//	�ж϶����Ƿ�Ϊ��
bool isQueueEmpty(struct Queue* queue)
{
	return queue->front == NULL;
}

//	�ж��Ƿ����
bool isPath(int x, int y)
{
	return (mazeMap[x][y] != 0);
}

//	�жϵ�ǰλ���Ƿ���Ч
bool isValid(int x, int y)
{
	return (x >= 0 && x < mazeCountX && y >= 0 && y < mazeCountY);
}

//	����
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

//	����
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

//	Ѱ�ҿ���·��
int findPath(int pathStartX, int pathStartY, int pathEndX, int pathEndY)
{
	int recordStart = mazeMap[pathStartX][pathStartY];
	int recordEnd = mazeMap[pathEndX][pathEndY];

	mazeMap[pathStartX][pathStartY] = 1;
	mazeMap[pathEndX][pathEndY] = 1;
	//	���ڿ����ϡ��¡������ĸ�����
	int directionX[] = { -1, 1, 0, 0 };
	int directionY[] = { 0, 0, -1, 1 };

	struct Queue queue;
	initQueue(&queue);

	//	��ʼ��·������
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
		//	��¼��ǰλ���н�����
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

//	��ʾ���·��
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

	//	����·�������н�
	while (x != pathStartX || y != pathStartY)
	{
		int direction = path[x][y];
		x = x - directionX[direction];
		y = y - directionY[direction];
		count++;
	}

	int pathLength = count + 1;	//	�����յ�
	struct Node** pathArray = (struct Node**)malloc(pathLength * sizeof(struct Node*));
	count = 0;

	x = pathEndX;
	y = pathEndY;

	while (x != pathStartX || y != pathStartY)
	{
		//	����·�������н�
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
		//	�洢��ʾλ����Ϣ
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

//	��ʾ��һ��
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
		//	��·�����鷽���н�
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
	//	ÿ��ֻ���һ��
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