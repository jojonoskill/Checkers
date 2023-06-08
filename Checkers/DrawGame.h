#ifndef DrawGame_h
#define DrawGame_h

#include <vector>
#include <GL/glut.h>
#include "Point.h"
#include "GameLogic.h"


int indicatorX = 0;
int indicatorY = 0;

const int NumberOfCells = 8;
const int Posit1 = 32;
const int Posit2 = 8;

GameLogic* game = new GameLogic();

class DrawGame {
public:
    void DrawBoard();
    void DrawCheckers();
    void DrawIndicator();

};

#endif