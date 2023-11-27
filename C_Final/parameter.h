#ifndef _H_PARAMETER
#define _H_PARAMETER
//  窗口大小
#define WindowWidth 12
#define WindowHeight 7


/***迷宫参数***/
#define mazeCountX 13
#define mazeCountY 13
int mazeMap[mazeCountX][mazeCountY];
int path[mazeCountX][mazeCountY];   //  存放路径
static int mazeLevel = 0;   //  迷宫难度
                            //  0   -   简单模式
                            //  1   -   困难模式

static int autoSolve = 0;   //  提示类型
                            //  0   -   无提示
                            //  1   -   提示最短路径
                            //  2   -   提示下一步


// 首页相关参数
#define indexButtonWidth 1.5
#define indexButtonHeight 0.5
#define indexStartButtonX 5.0
#define indexStartButtonY 5.8
#define indexHelpButtonX 5.0
#define indexHelpButtonY 4.3
#define indexExitButtonX 5
#define indexExitButtonY 2.8
#define indexIconX 4.0
#define indexIconY 0.2


/***游戏界面参数***/
//  迷宫相关
#define mazeX 1.0
#define mazeY 6.5
#define mazeOutlineHeight 5.85
#define mazeOutlineWidth 5.85
#define mazeSize 0.45


//  操作区相关
#define gameAreaX 8
#define gameAreaY1 6
#define gameAreaY2 4.0
#define gameAreaY3 1.5
#define gameAreaWidth 2.0
#define gameAreaHeight1 0.5
#define gameAreaHeight2 5.0
#define gameButtonWidth 2.0
#define gameButtonHeight 0.5


/***位置参数***/  
//  起点
int startX;
int startY;
//  当前位置
int currentX;
int currentY;
//  终点
int exitX;
int exitY;

//  其他参数
int gameOver;   //  记录游戏结束与否，1则结束
int editBlock;  //  为1则生成墙块
int pageFlag;   //  1为首页，2为游戏界面
#define CircleSize 0.05 //  弧线半径
//  节点
struct Node
{
    int x;
    int y;
    struct Node* next;
};
//  队列
struct Queue
{
    struct Node* front;
    struct Node* rear;
};
#endif