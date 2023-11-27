#ifndef _H_PARAMETER
#define _H_PARAMETER
//  ���ڴ�С
#define WindowWidth 12
#define WindowHeight 7


/***�Թ�����***/
#define mazeCountX 13
#define mazeCountY 13
int mazeMap[mazeCountX][mazeCountY];
int path[mazeCountX][mazeCountY];   //  ���·��
static int mazeLevel = 0;   //  �Թ��Ѷ�
                            //  0   -   ��ģʽ
                            //  1   -   ����ģʽ

static int autoSolve = 0;   //  ��ʾ����
                            //  0   -   ����ʾ
                            //  1   -   ��ʾ���·��
                            //  2   -   ��ʾ��һ��


// ��ҳ��ز���
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


/***��Ϸ�������***/
//  �Թ����
#define mazeX 1.0
#define mazeY 6.5
#define mazeOutlineHeight 5.85
#define mazeOutlineWidth 5.85
#define mazeSize 0.45


//  ���������
#define gameAreaX 8
#define gameAreaY1 6
#define gameAreaY2 4.0
#define gameAreaY3 1.5
#define gameAreaWidth 2.0
#define gameAreaHeight1 0.5
#define gameAreaHeight2 5.0
#define gameButtonWidth 2.0
#define gameButtonHeight 0.5


/***λ�ò���***/  
//  ���
int startX;
int startY;
//  ��ǰλ��
int currentX;
int currentY;
//  �յ�
int exitX;
int exitY;

//  ��������
int gameOver;   //  ��¼��Ϸ�������1�����
int editBlock;  //  Ϊ1������ǽ��
int pageFlag;   //  1Ϊ��ҳ��2Ϊ��Ϸ����
#define CircleSize 0.05 //  ���߰뾶
//  �ڵ�
struct Node
{
    int x;
    int y;
    struct Node* next;
};
//  ����
struct Queue
{
    struct Node* front;
    struct Node* rear;
};
#endif