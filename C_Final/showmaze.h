#ifndef _H_SHOWMAZE
#define _H_SHOWMAZE

void DisplayClear();
void (*Show)(void);
void showIndex(void);
void drawIndexButton();
void drawGameButton();
void drawMazeOutline();
void drawMazeMap();
void showGame(void);
void updateMaze();
void keyboardEventProcess(int key, int event);
void mouseEventProcess(int x, int y, int button, int event);
void drawRect(double x, double y, double w, double h);
#endif