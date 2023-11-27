#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include "parameter.h"
#include "src/libgraphics/graphics.h"
#include "src/libgraphics/genlib.h"
#include "src/simpleGUI/imgui.h"
#include "src/libgraphics/extgraph.h"
#include "showmaze.h"
#include "maze.h"


void Main()
{

    SetWindowSize(WindowWidth, WindowHeight);
    SetWindowTitle("Maze Game");
    InitGraphics();
    initMaze();
    registerKeyboardEvent(keyboardEventProcess);
    registerMouseEvent(mouseEventProcess);
    pageFlag = 1;
    Show=showIndex;
    

}