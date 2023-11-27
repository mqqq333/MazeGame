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

//	绘制首页
void showIndex(void)
{
	DisplayClear();
	drawIndexButton();
}

//	绘制首页按钮与图形
void drawIndexButton()
{
	double startX, startY;

	//	左边红色的门
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


	//	左边蓝色‘MAZE’字样
	MovePen(startX +  1.60*mazeSize, startY - 4.5*mazeSize);
	SetPointSize(30);
	SetPenColor("Blue");
	DrawTextString("MAZE");


	//	右边蓝色‘GAME’字样
	startX = -indexIconX + WindowWidth;
	MovePen(startX + 1.60 * mazeSize, startY - 4.5 * mazeSize);
	SetPointSize(30);
	SetPenColor("Blue");
	DrawTextString("GAME");


	//	右边绿色的门
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


	//	左边黑色小车
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


	//	右边绿色旗子
	startX = -indexIconX + WindowWidth;
	startY = indexIconY + WindowHeight;
	SetPenColor("Green");
	MovePen(startX + 1.5 * mazeSize, startY - 9.5 * mazeSize);
	DrawLine(0, -3.5 * mazeSize);
	MovePen(startX + 1.5 * mazeSize, startY - 9.5 * mazeSize);
	DrawLine(2 * mazeSize, -1.0 * mazeSize);
	DrawLine(-2.0 * mazeSize, -1.0 * mazeSize);

	
	SetFont("宋体");
	button(GenUIID(0), -0.1, -0.1, 0.1, 0.1, " ");


	//	开始游戏按钮
	if (button(GenUIID(0), indexStartButtonX, indexStartButtonY, indexButtonWidth, indexButtonHeight, "开始"))
	{
		DisplayClear();
		pageFlag = 2;
		Show = showGame;
		return;
	}


	//	帮助按钮
	if (button(GenUIID(0), indexHelpButtonX, indexHelpButtonY, indexButtonWidth, indexButtonHeight, "帮助"))
	{
		system("start .\\help\\用户使用手册.pdf");
	}


	//	退出按钮
	if (button(GenUIID(0), indexExitButtonX, indexExitButtonY, indexButtonWidth, indexButtonHeight, "退出"))
	{
		exit(0);
	}


	//	底部黑色字样
	SetPointSize(15);
	MovePen(indexExitButtonX + 0.25, indexIconY + mazeSize);
	SetPenColor("Black");
	DrawTextString("By mqqq333");

}

//	绘制游戏界面
void showGame(void)
{
	DisplayClear();
	drawMazeMap();
	drawMazeOutline();
	drawGameButton();
}

//	绘制迷宫界面
void drawMazeMap()
{
	/*
		0	-	墙
		1	-	路
		3	-	起点
		4	-	终点
		6	-	提示
	*/
	for (int i = 0; i < mazeCountX; i++)
	{
		for (int j = 0; j < mazeCountY; j++)
		{
			double startX = mazeX + j * mazeSize;
			double startY = mazeY - i * mazeSize;
			

			//	墙
			if (mazeMap[i][j] == 0)
			{
				SetPenColor("Black");
				SetPenSize(2);
				double len = mazeSize / 8.0;


				// 外部轮廓
				MovePen(startX, startY);
				DrawLine(0, -mazeSize);
				DrawLine(mazeSize, 0);
				DrawLine(0, mazeSize);
				DrawLine(-mazeSize, 0);


				// 内部
				int k;
				for (k = 1; k <= 8; k++)
				{
					MovePen(startX + k * len, startY);
					DrawLine(-k * len, -k * len);
					MovePen(startX + mazeSize - k * len, startY - mazeSize);
					DrawLine(k * len, k * len);
				}

			}
			//	起点
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
			//	终点
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
			//	提示
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

//	绘制迷宫边框
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

//	绘制游戏界面按钮
void drawGameButton()
{
	/***编辑区***/
	SetPenColor("Black");
	SetPenSize(1);
	SetPointSize(30);
	MovePen(gameAreaX+gameButtonWidth/4, gameAreaY2 + 3.2*gameButtonHeight);
	DrawTextString("编辑区");
	SetPointSize(15);
	//	添加墙
	 if (button(GenUIID(0), gameAreaX, gameAreaY2 + 2*gameButtonHeight, gameButtonWidth/2, gameButtonHeight, "添加墙"))
	{
		 editBlock = 0;
		 Show();
	}
	//	删除墙
	 if (button(GenUIID(0), gameAreaX+gameButtonWidth/2, gameAreaY2 + 2*gameButtonHeight, gameButtonWidth/2, gameButtonHeight, "删除墙"))
	{
		 editBlock = 1;
		 Show();
	}
	//	打开地图
	 if (button(GenUIID(0), gameAreaX, gameAreaY2+gameButtonHeight, gameButtonWidth/2, gameButtonHeight, "打开地图"))
	{
		 editBlock = -1;
		 openMaze();
		 Show();
		 
	}
	//	保存地图
	if (button(GenUIID(0), gameAreaX+gameButtonWidth/2, gameAreaY2 + gameButtonHeight, gameButtonWidth/2, gameButtonHeight, "保存地图"))
	{
		editBlock = -1;
		saveMaze();
		Show();
	}

	//	简单模式
	if (button(GenUIID(0), gameAreaX, gameAreaY2, gameButtonWidth/2, gameButtonHeight, "简单模式"))
	{
		mazeLevel = 0;
		initMaze();
		Show();
	}
	//	困难模式
	if (button(GenUIID(0), gameAreaX + gameButtonWidth / 2, gameAreaY2, gameButtonWidth / 2, gameButtonHeight, "困难模式"))
	{
		mazeLevel = 1;
		initMaze();
		Show();
	}


	/***操作区***/
	SetPenColor("Black");
	SetPenSize(1);
	SetPointSize(30);
	MovePen(gameAreaX + gameButtonWidth / 4, gameAreaY2- 0.8*gameButtonHeight);
	DrawTextString("操作区");
	SetPointSize(15);
	// 自动最近路线
	if (button(GenUIID(0), gameAreaX, gameAreaY2 - 2 * gameButtonHeight, gameButtonWidth, gameButtonHeight, "提示最近路线"))
	{
		autoSolve = 1;

		if (findPath(currentX, currentY, exitX, exitY) == 1)
		{
			printPath(currentX, currentY, exitX, exitY);
		}
		Show();
		
	}
	// 提示下一步
	if (button(GenUIID(0), gameAreaX, gameAreaY2 - 3 * gameButtonHeight, gameButtonWidth, gameButtonHeight, "提示下一步"))
	{
		autoSolve = 2;
		if (findPath(currentX, currentY, exitX, exitY) == 1)
		{
			printNextStep(currentX, currentY, exitX, exitY);
		}
		Show();
		
		
	}
	// 检查迷宫可行性
	if (button(GenUIID(0), gameAreaX, gameAreaY2 - 4 * gameButtonHeight, gameButtonWidth, gameButtonHeight, "检查迷宫可行性"))
	{
		if (judgeMaze())
		{
			MessageBox(NULL, "迷宫可行，请开始游戏！", "成功", MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			MessageBox(NULL, "迷宫错误，请进行修改！", "错误", MB_OK | MB_ICONINFORMATION);
		}
	}
	//	操作说明
	if (button(GenUIID(0), gameAreaX, gameAreaY2 - 5 * gameButtonHeight, gameButtonWidth, gameButtonHeight, "操作说明"))
	{
		MessageBox(NULL, "请使用数字区上下左右键控制移动", "操作提示", MB_OK | MB_ICONINFORMATION);
	}

	// 退出游戏
	if (button(GenUIID(0), gameAreaX, gameAreaY2 - 6 * gameButtonHeight, gameButtonWidth, gameButtonHeight, "返回首页"))
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

	// 绘制工作区边框
	SetPenColor("Black");
	SetPenSize(3);

	//	整体大边框	
	drawRect(gameAreaX, gameAreaY1, gameAreaWidth, gameAreaHeight2);
	
	//	编辑区、操作区、返回首页边框	
	drawRect(gameAreaX, gameAreaY1, gameAreaWidth, gameAreaHeight1);
	drawRect(gameAreaX, gameAreaY2, gameAreaWidth, gameAreaHeight1);
	drawRect(gameAreaX, gameAreaY3, gameAreaWidth, gameAreaHeight1);
	
	SetPenSize(1);
}

//	更新迷宫
void updateMaze()
{
	for (int i = 0; i < mazeCountX; i++)
	{
			for (int j = 0; j < mazeCountY; j++)
			{
				if (mazeMap[i][j] == 3)	//	起点
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
				else if (mazeMap[i][j] == 4)	//	终点
				{
					exitX = i;
					exitY = j;
				}
				
		}
	}

}

//	绘制矩形
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
			mazeMap[blockX][blockY] = editBlock;	//	生成/删除墙

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
		if (key == VK_LEFT)	//	向左
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
				int result = MessageBox(NULL, "恭喜！你通过了这一难度！", "恭喜", MB_OK | MB_ICONINFORMATION);
				if (result == IDOK)
				{
					Show = showIndex;
				}
			}
		}
		if (key == VK_RIGHT)	//	向右
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
				int result = MessageBox(NULL, "恭喜！你通过了这一难度！", "恭喜", MB_OK | MB_ICONINFORMATION);
				if (result == IDOK)
				{
					Show = showIndex;
				}
			}
		}
		if (key == VK_UP)	//	向上
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
				int result = MessageBox(NULL, "恭喜！你通过了这一难度！", "恭喜", MB_OK | MB_ICONINFORMATION);
				if (result == IDOK)
				{
					Show = showIndex;
				}

			}
		}


		if (key == VK_DOWN)	//	向下
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
				int result = MessageBox(NULL, "恭喜！你通过了这一难度！", "恭喜", MB_OK | MB_ICONINFORMATION);
				if (result == IDOK)
				{
					Show = showIndex;
				}

			}
		}
		if (autoSolve == 1)	//	autoSolve==1，展示最短路径
		{
			if (findPath(currentX, currentY, exitX, exitY) == 1)
			{
				printPath(currentX, currentY, exitX, exitY);
			}
		}
		else if (autoSolve == 2)	//	autoSolve==2，输出下一步
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
