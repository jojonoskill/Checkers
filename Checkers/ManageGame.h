#ifndef MANAGEGAME_H
#define MANAGEGAME_H

#include <chrono>
#include <vector>

#include <GL/glut.h>
#include "Point.h"
#include "GameLogic.h"

#include "DrawGame.h"

using namespace std::chrono;

// Поворот камери та відстань (зум)
Point view;

bool records = false;
bool saved = false;

// Час (хвилини та секунди)
int time_m;
int time_s;

string message = "";

// Час початку раунду
milliseconds startTime;

// Відступ миші (за час між попереднім та поточним кадром)
int mouseOffsetX = 0;
int mouseOffsetY = 0;

// Координати миші у попередньому кадрі
int mouseLastX = -1;
int mouseLastY = -1;

// Чи натиснута ліва кнопка миші
bool isMouseDown = false;

// Функція ініцілізації даних


class ManageGame {
public:
   /* ManageGame();*/
    void InitGame();
    void MoveMouse(int x, int y);
    void Mouse(int key, int state, int x, int y);
    void mouseWheel(int button, int dir, int x, int y);
    void Key(int key, int x, int y);
    void Keyboard(unsigned char key, int x, int y);
};


#endif