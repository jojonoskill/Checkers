#include "ManageGame.h"


void ManageGame::InitGame() {
    startTime = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    );

    time_m = 0;
    time_s = 0;

    view.x = 0;
    view.y = 0;
    view.z = 2;

    saved = false;

    game->Reset();
}

// Обробник руху миші
void ManageGame::MoveMouse(int x, int y) {
    if (mouseLastX == -1)
        mouseLastX = x;
    if (mouseLastY == -1)
        mouseLastY = y;

    mouseOffsetX = x - mouseLastX;
    mouseOffsetY = y - mouseLastY;

    mouseLastX = x;
    mouseLastY = y;

    if (isMouseDown) {
        view.y += 0.1 * mouseOffsetX;
        view.x += 0.1 * mouseOffsetY;
    }
    glutPostRedisplay();
}

// Обробник клавіш миші
void ManageGame::Mouse(int key, int state, int x, int y) {
    if (key == 2) {
        isMouseDown = (state == 1) ? false : true;
    }
    if (key == 3) {
        view.z -= 0.05;
    }
    if (key == 4) {
        view.z += 0.05;
    }
    MoveMouse(x, y);
}

// Обробник коліщатка миші
void ManageGame::mouseWheel(int button, int dir, int x, int y) {
    if (dir > 0) {
        view.z -= 0.1;
    }
    else {
        view.z += 0.1;
    }
    glutPostRedisplay();
}

// Обработчик нажатия клавиш
void ManageGame::Key(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        if (game->IsEnd())
            break;
        indicatorX--;
        if (indicatorX < 0)
            indicatorX = 0;
        if (indicatorX > 7)
            indicatorX = 7;
        break;
    case GLUT_KEY_RIGHT:
        if (game->IsEnd())
            break;
        indicatorX++;
        if (indicatorX < 0)
            indicatorX = 0;
        if (indicatorX > 7)
            indicatorX = 7;
        break;
    case GLUT_KEY_UP:
        if (game->IsEnd())
            break;
        indicatorY++;
        if (indicatorY < 0)
            indicatorY = 0;
        if (indicatorY > 7)
            indicatorY = 7;
        break;
    case GLUT_KEY_DOWN:
        if (game->IsEnd())
            break;
        indicatorY--;
        if (indicatorY < 0)
            indicatorY = 0;
        if (indicatorY > 7)
            indicatorY = 7;
        break;
    case GLUT_KEY_F1:
        InitGame();
        break;
    case GLUT_KEY_F2:
        view.z -= 0.1;
        break;
    case GLUT_KEY_F3:
        view.z += 0.1;
        break;
    case GLUT_KEY_F4:
        records = !records;
        break;
    case GLUT_KEY_F5:
        remove("score.txt");
        break;
    case GLUT_KEY_F6:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// Функція обробник клавіатури
void ManageGame::Keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case ' ':
        if (game->IsEnd())
            break;
        if (!game->IsChose())
            switch (game->Option(indicatorX, NumberOfCells - 1 - indicatorY)) {
            case GameLogic::SelectResult::Success:
                message = "Selected checker";
                break;
            case GameLogic::SelectResult::NoSteps:
                message = "Checker dont have steps";
                break;
            case GameLogic::SelectResult::KillingIsImportant:
                message = "Killing is important!";
                break;
            case GameLogic::SelectResult::IncorrectPlayer:
                message = "It`s not your checker!";
                break;
            case GameLogic::SelectResult::EmptyCell:
                message = "You can`t choose empty cell";
                break;
            default:
                break;
            }
        else
            switch (game->Put(indicatorX, NumberOfCells - 1 - indicatorY)) {
            case GameLogic::PutResult::Success:
                message = "";
                break;
            case GameLogic::PutResult::Canceled:
                message = "You cancel selection";
                break;
            case GameLogic::PutResult::IncorrectPlace:
                message = "You can`t put it here!";
                break;
            case GameLogic::PutResult::KillingIsImportant:
                message = "Killing is important!";
                break;
            case GameLogic::PutResult::PickedEmpty:
                message = "You must choose checker!";
                break;
            case GameLogic::PutResult::SuccessWithKill:
                message = "You kill checker!";
                break;
            default:
                break;
            }
        break;
    }
    glutPostRedisplay();
}