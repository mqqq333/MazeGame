#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#include "parameter.h"
#include "showmaze.h"
#include "maze.h"

#include"parameter.h"
#include "src/libgraphics/graphics.h"
#include "src/libgraphics/genlib.h"
#include "src/simpleGUI/imgui.h"
#include "src/libgraphics/extgraph.h"

//	������ҳ
void showIndex(void)
{
	DisplayClear();
	drawIndexButton();
}

//	������ҳ��ť��ͼ��
void drawIndexButton()
{
	double startX, startY;

	//	��ߺ�ɫ����
	SetPenSize(3);
	SetPenColor("Red");
	startX = indexIconX - 7.0 * indexIconX / 10.0;
	startY = indexIconY + 9.5 * WindowHeight / 10.0;
	MovePen(startX + 0.3 * mazeSize, startY - mazeSize);
	DrawLine(0, -7 * mazeSize);
	DrawLine(4 * mazeSize, 0);
	DrawLine(0, 7 * mazeSize);
	DrawLine(-4 * mazeSize, 0);
	MovePen(startX + 1 * mazeSize, startY - 3.2 * mazeSize);
	DrawArc(CircleSize, 0, 360);


	//	�����ɫ��MAZE������
	MovePen(startX +  1.60*mazeSize, startY - 4.5*mazeSize);
	SetPointSize(30);
	SetPenColor("Blue");
	DrawTextString("MAZE");


	//	�ұ���ɫ��GAME������
	startX = -indexIconX + WindowWidth;
	MovePen(startX + 1.60 * mazeSize, startY - 4.5 * mazeSize);
	SetPointSize(30);
	SetPenColor("Blue");
	DrawTextString("GAME");


	//	�ұ���ɫ����
	SetPenColor("Green");
	startX = -indexIconX + WindowWidth;
	startY = indexIconY + 9.5 * WindowHeight / 10.0;
	MovePen(startX + 0.3 * mazeSize, startY - mazeSize);
	DrawLine(0, -7 * mazeSize);
	DrawLine(4 * mazeSize, 0);
	DrawLine(0, 7 * mazeSize);
	DrawLine(-4 * mazeSize, 0);
	MovePen(startX + 1 * mazeSize, startY - 3.2 * mazeSize);
	DrawArc(CircleSize, 0, 360);


	//	��ߺ�ɫС��
	SetPenColor("Black");
	startX = indexIconX - 7.0 * indexIconX / 10.0;
	startY = indexIconY + WindowHeight;
	MovePen(startX + 1.3 * mazeSize, startY - 11.0 * mazeSize);
	DrawLine(2 * mazeSize, 0);
	DrawLine(1 * mazeSize, -1 * mazeSize);
	DrawLine(-4 * mazeSize, 0);
	DrawLine(1 * mazeSize, 1 * mazeSize);
	MovePen(startX + 1.3 * mazeSize, startY - 12.0 * mazeSize - 5 * CircleSize);
	DrawArc(5 * CircleSize, 0, 360);
	MovePen(startX + 4.3 * mazeSize, startY - 12.0 * mazeSize - 5 * CircleSize);
	DrawArc(5 * CircleSize, 0, 360);
	SetPenColor("Red");
	MovePen(startX + 2.0 * mazeSize, startY - 11.0 * mazeSize);
	DrawLine(0, mazeSize);
	DrawLine(0.5 * mazeSize, -0.5 * mazeSize);
	DrawLine(-0.5 * mazeSize, 0);


	//	�ұ���ɫ����
	startX = -indexIconX + WindowWidth;
	startY = indexIconY + WindowHeight;
	SetPenColor("Green");
	MovePen(startX + 1.5 * mazeSize, startY - 9.5 * mazeSize);
	DrawLine(0, -3.5 * mazeSize);
	MovePen(startX + 1.5 * mazeSize, startY - 9.5 * mazeSize);
	DrawLine(2 * mazeSize, -1.0 * mazeSize);
	DrawLine(-2.0 * mazeSize, -1.0 * mazeSize);

	
	SetFont("����");
	button(GenUIID(0), -0.1, -0.1, 0.1, 0.1, " ");


	//	��ʼ��Ϸ��ť
	if (button(GenUIID(0), indexStartButtonX, indexStartButtonY, indexButtonWidth, indexButtonHeight, "��ʼ"))
	{
		DisplayClear();
		pageFlag = 2;
		Show = showGame;
		return;
	}


	//	������ť
	if (button(GenUIID(0), indexHelpButtonX, indexHelpButtonY, indexButtonWidth, indexButtonHeight, "����"))
	{
		system("start .\\help\\�û�ʹ���ֲ�.pdf");
	}


	//	�˳���ť
	if (button(GenUIID(0), indexExitButtonX, indexExitButtonY, indexButtonWidth, indexButtonHeight, "�˳�"))
	{
		exit(0);
	}


	//	�ײ���ɫ����
	SetPointSize(15);
	MovePen(indexExitButtonX + 0.25, indexIconY + mazeSize);
	SetPenColor("Black");
	DrawTextString("By mqqq333");

}

//	������Ϸ����
void showGame(void)
{
	DisplayClear();
	drawMazeMap();
	drawMazeOutline();
	drawGameButton();
}

//	�����Թ�����
void drawMazeMap()
{
	/*
		0	-	ǽ
		1	-	·
		3	-	���
		4	-	�յ�
		6	-	��ʾ
	*/
	for (int i = 0; i < mazeCountX; i++)
	{
		for (int j = 0; j < mazeCountY; j++)
		{
			double startX = mazeX + j * mazeSize;
			double startY = mazeY - i * mazeSize;
			

			//	ǽ
			if (mazeMap[i][j] == 0)
			{
				SetPenColor("Black");
				SetPenSize(2);
				double len = mazeSize / 8.0;


				// �ⲿ����
				MovePen(startX, startY);
				DrawLine(0, -mazeSize);
				DrawLine(mazeSize, 0);
				DrawLine(0, mazeSize);
				DrawLine(-mazeSize, 0);


				// �ڲ�
				int k;
				for (k = 1; k <= 8; k++)
				{
					MovePen(startX + k * len, startY);
					DrawLine(-k * len, -k * len);
					MovePen(startX + mazeSize - k * len, startY - mazeSize);
					DrawLine(k * len, k * len);
				}

			}
			//	���
			else if (mazeMap[i][j] == 3) 
			{
				SetPenColor("Red");
				SetPenSize(2);
				MovePen(startX + 0.4 * mazeSize, startY - mazeSize);
				DrawLine(0, 0.7 * mazeSize);
				DrawLine(0.3 * mazeSize, -0.2 * mazeSize);
				DrawLine(-0.3 * mazeSize, -0.1 * mazeSize);
				SetPenColor("Black");
				SetPenSize(1);
			}
			//	�յ�
			else if (mazeMap[i][j] == 4) 
			{
				SetPenColor("Green");
				SetPenSize(2);
				MovePen(startX + 0.4 * mazeSize, startY - mazeSize);
				DrawLine(0, 0.7 * mazeSize);
				DrawLine(0.3 * mazeSize, -0.2 * mazeSize);
				DrawLine(-0.3 * mazeSize, -0.1 * mazeSize);


				SetPenColor("Black");
				SetPenSize(1);

			}
			//	��ʾ
			else if (mazeMap[i][j] == 6) 
			{
				SetPenColor("Green");
				SetPenSize(2);
				MovePen(startX + 0.68 * mazeSize, startY - 0.5 * mazeSize);
				DrawArc(CircleSize*1.25, 0, 360);


				SetPenSize(1);
				SetPenColor("Black");
			}
			
		}

	}
}

//	�����Թ��߿�
void drawMazeOutline()
{
	MovePen(mazeX, mazeY);
	SetPenColor("Black");
	SetPenSize(3);
	DrawLine(0.0, -mazeOutlineHeight);
	DrawLine(mazeOutlineWidth, 0.0);
	DrawLine(0.0, mazeOutlineHeight);
	DrawLine(-mazeOutlineWidth, 0.0);
	SetPenSize(1);
}

//	������Ϸ���水ť
void drawGameButton()
{
	/***�༭��***/
	SetPenColor("Black");
	SetPenSize(1);
	SetPointSize(30);
	MovePen(gameAreaX+gameButtonWidth/4, gameAreaY2 + 3.2*gameButtonHeight);
	DrawTextString("�༭��");
	SetPointSize(15);
	//	���ǽ
	 if (button(GenUIID(0), gameAreaX, gameAreaY2 + 2*gameButtonHeight, gameButtonWidth/2, gameButtonHeight, "���ǽ"))
	{
		 editBlock = 0;
		 Show();
	}
	//	ɾ��ǽ
	 if (button(GenUIID(0), gameAreaX+gameButtonWidth/2, gameAreaY2 + 2*gameButtonHeight, gameButtonWidth/2, gameButtonHeight, "ɾ��ǽ"))
	{
		 editBlock = 1;
		 Show();
	}
	//	�򿪵�ͼ
	 if (button(GenUIID(0), gameAreaX, gameAreaY2+gameButtonHeight, gameButtonWidth/2, gameButtonHeight, "�򿪵�ͼ"))
	{
		 editBlock = -1;
		 openMaze();
		 Show();
		 
	}
	//	�����ͼ
	if (button(GenUIID(0), gameAreaX+gameButtonWidth/2, gameAreaY2 + gameButtonHeight, gameButtonWidth/2, gameButtonHeight, "�����ͼ"))
	{
		editBlock = -1;
		saveMaze();
		Show();
	}

	//	��ģʽ
	if (button(GenUIID(0), gameAreaX, gameAreaY2, gameButtonWidth/2, gameButtonHeight, "��ģʽ"))
	{
		mazeLevel = 0;
		initMaze();
		Show();
	}
	//	����ģʽ
	if (button(GenUIID(0), gameAreaX + gameButtonWidth / 2, gameAreaY2, gameButtonWidth / 2, gameButtonHeight, "����ģʽ"))
	{
		mazeLevel = 1;
		initMaze();
		Show();
	}


	/***������***/
	SetPenColor("Black");
	SetPenSize(1);
	SetPointSize(30);
	MovePen(gameAreaX + gameButtonWidth / 4, gameAreaY2- 0.8*gameButtonHeight);
	DrawTextString("������");
	SetPointSize(15);
	// �Զ����·��
	if (button(GenUIID(0), gameAreaX, gameAreaY2 - 2 * gameButtonHeight, gameButtonWidth, gameButtonHeight, "��ʾ���·��"))
	{
		autoSolve = 1;

		if (findPath(currentX, currentY, exitX, exitY) == 1)
		{
			printPath(currentX, currentY, exitX, exitY);
		}
		Show();
		
	}
	// ��ʾ��һ��
	if (button(GenUIID(0), gameAreaX, gameAreaY2 - 3 * gameButtonHeight, gameButtonWidth, gameButtonHeight, "��ʾ��һ��"))
	{
		autoSolve = 2;
		if (findPath(currentX, currentY, exitX, exitY) == 1)
		{
			printNextStep(currentX, currentY, exitX, exitY);
		}
		Show();
		
		
	}
	// ����Թ�������
	if (button(GenUIID(0), gameAreaX, gameAreaY2 - 4 * gameButtonHeight, gameButtonWidth, gameButtonHeight, "����Թ�������"))
	{
		if (judgeMaze())
		{
			MessageBox(NULL, "�Թ����У��뿪ʼ��Ϸ��", "�ɹ�", MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			MessageBox(NULL, "�Թ�����������޸ģ�", "����", MB_OK | MB_ICONINFORMATION);
		}
	}
	//	����˵��
	if (button(GenUIID(0), gameAreaX, gameAreaY2 - 5 * gameButtonHeight, gameButtonWidth, gameButtonHeight, "����˵��"))
	{
		MessageBox(NULL, "��ʹ���������������Ҽ������ƶ�", "������ʾ", MB_OK | MB_ICONINFORMATION);
	}

	// �˳���Ϸ
	if (button(GenUIID(0), gameAreaX, gameAreaY2 - 6 * gameButtonHeight, gameButtonWidth, gameButtonHeight, "������ҳ"))
	{
		DisplayClear();
		pageFlag = 1;
		Show = showIndex;
		for (int i = 0; i < mazeCountX; i++)
		{
			for (int j = 0; j < mazeCountY; j++)
			{
				mazeMap[i][j] = 0;
			}
		}
		return;
	}

	// ���ƹ������߿�
	SetPenColor("Black");
	SetPenSize(3);

	//	�����߿�	
	drawRect(gameAreaX, gameAreaY1, gameAreaWidth, gameAreaHeight2);
	
	//	�༭������������������ҳ�߿�	
	drawRect(gameAreaX, gameAreaY1, gameAreaWidth, gameAreaHeight1);
	drawRect(gameAreaX, gameAreaY2, gameAreaWidth, gameAreaHeight1);
	drawRect(gameAreaX, gameAreaY3, gameAreaWidth, gameAreaHeight1);
	
	SetPenSize(1);
}

//	�����Թ�
void updateMaze()
{
	for (int i = 0; i < mazeCountX; i++)
	{
			for (int j = 0; j < mazeCountY; j++)
			{
				if (mazeMap[i][j] == 3)	//	���
				{
					startX = i;
					startY = j;
					currentX = i;
					currentY = j;
					if (pageFlag == 2)
					{
						mazeMap[i][j] = 3;
					}
				}
				else if (mazeMap[i][j] == 4)	//	�յ�
				{
					exitX = i;
					exitY = j;
				}
				
		}
	}

}

//	���ƾ���
void drawRect(double x, double y, double w, double h)
{
	MovePen(x, y);
	DrawLine(0, -h);
	DrawLine(w, 0);
	DrawLine(0, h);
	DrawLine(-w, 0);
}


void mouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);
	if (event == BUTTON_DOWN)
	{
		int blockX, blockY;
		blockY = (ScaleXInches(x) * 1.0 - mazeX) / mazeSize;
		blockX = (mazeY - ScaleYInches(y) * 1.0) / mazeSize;
		if (editBlock >= 0 && blockX >= 0 && blockX < mazeCountX && blockY >= 0 && blockY < mazeCountY)
		{
			mazeMap[blockX][blockY] = editBlock;	//	����/ɾ��ǽ

		}
	}
	
	updateMaze();
	Show();
}


void keyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event);
	if (event == KEY_DOWN && gameOver == 0)
	{
		if (key == VK_LEFT)	//	����
		{
			if (currentY != 0)
			{

				if (mazeMap[currentX][currentY - 1] == 4)
				{
					gameOver = 1;
				 }

				if ((mazeMap[currentX][currentY - 1] == 1) || (mazeMap[currentX][currentY - 1] == 6))
				{
					mazeMap[currentX][currentY-1] = 3;
					
					mazeMap[currentX][currentY] = 1;
				}
			}
			if (gameOver == 1)
			{
				int result = MessageBox(NULL, "��ϲ����ͨ������һ�Ѷȣ�", "��ϲ", MB_OK | MB_ICONINFORMATION);
				if (result == IDOK)
				{
					Show = showIndex;
				}
			}
		}
		if (key == VK_RIGHT)	//	����
		{
			if (currentY != mazeCountY-1)
			{
				if (mazeMap[currentX][currentY + 1] == 4)
				{
					gameOver = 1;
				}
				if ((mazeMap[currentX][currentY + 1] == 1) || (mazeMap[currentX][currentY + 1] == 6))
				{
					mazeMap[currentX][currentY+1] = 3;
					
					mazeMap[currentX][currentY] = 1;
				}
			}
			if (gameOver == 1)
			{
				int result = MessageBox(NULL, "��ϲ����ͨ������һ�Ѷȣ�", "��ϲ", MB_OK | MB_ICONINFORMATION);
				if (result == IDOK)
				{
					Show = showIndex;
				}
			}
		}
		if (key == VK_UP)	//	����
		{
			if (currentX != 0)
			{

				if (mazeMap[currentX - 1][currentY] == 4)
				{
					gameOver = 1;
				}

				if ((mazeMap[currentX - 1][currentY] == 1) || (mazeMap[currentX-1][currentY] == 6))
				{
					mazeMap[currentX-1][currentY] = 3;
					
					mazeMap[currentX][currentY] = 1;
				}
			}
			if (gameOver == 1)
			{
				int result = MessageBox(NULL, "��ϲ����ͨ������һ�Ѷȣ�", "��ϲ", MB_OK | MB_ICONINFORMATION);
				if (result == IDOK)
				{
					Show = showIndex;
				}

			}
		}


		if (key == VK_DOWN)	//	����
		{
			if (currentX != mazeCountX-1)
			{

				if (mazeMap[currentX + 1][currentY] == 4)
				{
					gameOver = 1;
				}
				if ((mazeMap[currentX + 1][currentY] == 1 ) || (mazeMap[currentX+1][currentY] == 6))
				{
					mazeMap[currentX+1][currentY] = 3;
					
					mazeMap[currentX][currentY] = 1;
				}
			}
			if (gameOver == 1)
			{
				int result = MessageBox(NULL, "��ϲ����ͨ������һ�Ѷȣ�", "��ϲ", MB_OK | MB_ICONINFORMATION);
				if (result == IDOK)
				{
					Show = showIndex;
				}

			}
		}
		if (autoSolve == 1)	//	autoSolve==1��չʾ���·��
		{
			if (findPath(currentX, currentY, exitX, exitY) == 1)
			{
				printPath(currentX, currentY, exitX, exitY);
			}
		}
		else if (autoSolve == 2)	//	autoSolve==2�������һ��
		{

			if (findPath(currentX, currentY, exitX, exitY) == 1)
			{
				printNextStep(currentX, currentY, exitX, exitY);
			}
		}
		else if (autoSolve == 0)
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

		updateMaze();
	}

	Show();
}
