//#ifndef DrawGame_h
//#define DrawGame_h

#include <vector>
#include <GL/glut.h>
#include "Point.h"
#include "GameLogic.h"


extern int indicatorX;
extern int indicatorY;

const int NumberOfCells = 8;
const int Posit1 = 32;
const int Posit2 = 8;

extern GameLogic* game;

class DrawGame {
public:
    void DrawBoard();
    void DrawCheckers();
    void DrawIndicator();

};

//#endif