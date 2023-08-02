#include <stdlib.h>
#include <fstream>
#include <vector>
#include <GL/glut.h>

#include "Point.h"
#include "GameLogic.h"
#include "DrawGame.h"
#include <chrono>




using namespace std;
using namespace std::chrono;

GameLogic::Checker*** checkers = game->GetField();

DrawGame drawGame;

Point view;

bool records = false;
bool saved = false;


int time_m;
int time_s;

string message = "";

milliseconds startTime;

int mouseOffsetX = 0;
int mouseOffsetY = 0;


int mouseLastX = -1;
int mouseLastY = -1;


bool isMouseDown = false;





void InitGame() {
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


void MoveMouse(int x, int y) {
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

void Mouse(int key, int state, int x, int y) {
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

void mouseWheel(int button, int dir, int x, int y) {
    if (dir > 0) {
        view.z -= 0.1;
    }
    else {
        view.z += 0.1;
    }
    glutPostRedisplay();
}

void Key(int key, int x, int y) {
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

void Keyboard(unsigned char key, int x, int y) {
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


int width = 800;
int height = 600;

void WinSize(int w, int h) {
    if (w < 800)
        w = 800;
    if (h < 600)
        h = 600;

    width = w;
    height = h;

    glutReshapeWindow(w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    GLfloat fAspect = (GLfloat)w / (GLfloat)h;
    gluPerspective(60.0f, fAspect, 1.0, 1000.0);
    gluLookAt(100.0f, 100.0f, 100.0f, .0f, .0f, .0f, .0f, .0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

void DisplayText(string text, Point color, Point position) {
    
    glColor3f(color.x, color.y, color.z);
    glRasterPos2i(position.x, height - 24 - position.y);
    int j = 0;
    for (unsigned int i = 0; i < text.length(); i++)
        if (text[i] == '\n')
            glRasterPos2i(position.x, (height - 24 - position.y) + (++j * (-24)));
        else
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}

struct DataGame {
    GameLogic::Player player;
    int blacks;
    int whites;
    int time_m;
    int time_s;
};

void DisplayResultList() {
    string text = "Result list\n";
    ifstream fin("result.txt");
    vector<DataGame> resultList = vector<DataGame>(0);
    if (fin.is_open()) {
        while (!fin.eof()) {
            int winner;
            int blacks;
            int whites;
            int time_m;
            int time_s;

            fin >> winner;
            fin >> blacks;
            fin >> whites;
            fin >> time_m;
            fin >> time_s;

            DataGame s = DataGame();
            s.player = winner == 1 ? GameLogic::Player::White : GameLogic::Player::Black;
            s.blacks = blacks;
            s.whites = whites;
            s.time_m = time_m;
            s.time_s = time_s;

            resultList.push_back(s);
        }
        bool endOfS = false;
        while (!endOfS) {
            endOfS = true;
            for (int i = 0; i < resultList.size() - 1; i++)
                if (resultList.at(i).time_s > resultList.at(i + 1).time_s) {
                    endOfS = false;
                    iter_swap(resultList.begin() + i, resultList.begin() + i + 1);
                }
        }
        endOfS = false;
        while (!endOfS) {
            endOfS = true;
            for (int i = 0; i < resultList.size() - 1; i++)
                if (resultList.at(i).time_m > resultList.at(i + 1).time_m) {
                    endOfS = false;
                    iter_swap(resultList.begin() + i, resultList.begin() + i + 1);
                }
        }
        int dd = 0;
        for (int i = 0; i < resultList.size(); i++)
            if (dd == 3)
                break;
            else {
                text += "\n    #" + to_string(i + 1) + " Winner: ";
                text += resultList.at(i).player == GameLogic::Player::White ? "White" : "Black";
                text += " Time: ";
                text += ((resultList.at(i).time_m < 10) ? "0" : "");
                text += to_string(resultList.at(i).time_m) + ":" + ((resultList.at(i).time_s < 10) ? "0" : "");
                text += to_string(resultList.at(i).time_s);
                dd++;
            }
    }
    else
        text += "\n    List is empty";

    DisplayText(text, Point(164.0 / 255.0, 79.0 / 255.0, 255.0 / 255.0), Point(20, 200));
}


void PushResultList(GameLogic::Player winner, int blacks, int whites, int time_m, int time_s) {
    ifstream c;
    ofstream fout;
    c.open("result.txt");
    fout.open("result.txt", ios::app);
    if (c.is_open())
        fout << endl;
    fout << (winner == GameLogic::Player::White ? 1 : 0) << " " << blacks << " " << whites << " " << time_m << " " << time_s;
}

void Display() {
    glClearColor(105 / 255.0, 105 / 255.0, 105 / 255.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glScalef(view.z, view.z, view.z);
    glRotatef(135, 0, 0, 1);
    glRotatef(view.x, 1, 0, 0);
    glRotatef(view.y, 0, 0, 1);

    drawGame.DrawBoard();
    drawGame.DrawCheckers();
    drawGame.DrawIndicator();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();


    DisplayText("F1 - Restart | Mouse wheel - Zoom | F4/F5 - Show/Clear Result | F6 - Exit", Point(135.0 / 250.0, 206.0 / 255.0, 250.0 / 255.0), Point(10, 20));

    string GameInfo = "\n";
    GameInfo += "Player: ";
    GameInfo += game->GetCurrPlayer() == GameLogic::Player::Black ? "Black" : "White";
    GameInfo += "\n";
    GameInfo += "Time: ";
    if (time_m < 10)
        GameInfo += "0";
    GameInfo += to_string(time_m);
    GameInfo += ":";
    if (time_s < 10)
        GameInfo += "0";
    GameInfo += to_string(time_s);
    GameInfo += "\n";
    GameInfo += "Black: " + to_string(game->GetBl()) + "\n";
    GameInfo += "White: " + to_string(game->GetWh()) + "\n\n";
    GameInfo += message;

    DisplayText(GameInfo, Point(135.0 / 250.0, 206.0 / 255.0, 250.0 / 255.0), Point(15, 40));

    if (records)
        DisplayResultList();

    if (game->IsEnd()) {
        string winText = "          ";
        winText += game->GetWin() == GameLogic::Player::White ? "White" : "Black";
        winText += " win!\n Press F1 to restart game";
        DisplayText(winText, Point(66.0 / 255.0, 245.0 / 255.0, 66.0 / 255.0), Point((float)width / 2.0 - 11.0 * 18.0 / 2.0, 80));
        if (!saved) {
            PushResultList(game->GetWin(), game->GetBl(), game->GetWh(), time_m, time_s);
            saved = true;
        }
    }
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void Timer(int r) {
    if (!game->IsEnd()) {
        milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        unsigned long long time_c = (ms - startTime).count();
        time_s = (time_c / 1000) % 60;
        time_m = (time_c / 1000) / 60;
    }
    glutTimerFunc(16, Timer, 0);
}

int main(int argc, char** argv) {

    srand(time(NULL));
    InitGame();
    glutInit(&argc, argv);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("Checkers");

    glutReshapeFunc(WinSize);
    glutDisplayFunc(Display);
    glutIdleFunc(Display);

    glutSpecialFunc(Key);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
    glutPassiveMotionFunc(MoveMouse);
    glutMotionFunc(MoveMouse);

    glutTimerFunc(16, Timer, 0);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}
