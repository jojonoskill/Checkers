#include <stdlib.h>
#include <fstream>
#include <vector>
#include <GL/glut.h>

#include "Point.h"
#include "GameLogic.h"
#include "DrawGame.h"
#include "ManageGame.h"
#include <chrono>



using namespace std;
using namespace std::chrono;

GameLogic::Checker*** checkers = game->GetField();


ManageGame manageGame;


void MoveMouse(int x, int y) {
    manageGame.MoveMouse(x, y);
}
void Mouse(int key, int state, int x, int y) {
    manageGame.Mouse(key, state, x, y);
}
void mouseWheel(int button, int dir, int x, int y) {
    manageGame.mouseWheel(button, dir, x, y);
}
void Key(int key, int x, int y) {
    manageGame.Key(key, x, y);
}
void Keyboard(unsigned char key, int x, int y) {
    manageGame.Keyboard(key, x, y);
}



// Створення об'єкту класу GameLogic 

// Розмір вікна (стартовий та поточний)
int width = 800;
int height = 600;

//Обробник зміни розміру вікна
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

// Функція відображення тексту
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

// Структура даних гри
struct DataGame {
    GameLogic::Player player;
    int blacks;
    int whites;
    int time_m;
    int time_s;
};

// Функція показу аркуша рекордів
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

// Додати рекорд у файл
void PushResultList(GameLogic::Player winner, int blacks, int whites, int time_m, int time_s) {
    ifstream c;
    ofstream fout;
    c.open("result.txt");
    fout.open("result.txt", ios::app);
    if (c.is_open())
        fout << endl;
    fout << (winner == GameLogic::Player::White ? 1 : 0) << " " << blacks << " " << whites << " " << time_m << " " << time_s;
}

// Відображення об'єктів
void Display() {
    glClearColor(105 / 255.0, 105 / 255.0, 105 / 255.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Відображення 3д об'єктів
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glScalef(view.z, view.z, view.z);
    glRotatef(135, 0, 0, 1);
    glRotatef(view.x, 1, 0, 0);
    glRotatef(view.y, 0, 0, 1);

    // Відображення гри 
    DrawBoard();
    DrawCheckers();
    DrawIndicator();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glPopMatrix();

    // Відображення тексту
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

    // Відображення графіки
    glFlush();
    glutSwapBuffers();
}

// Функція відліку часу
void Timer(int r) {
    if (!game->IsEnd()) {
        milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        unsigned long long time_c = (ms - startTime).count();
        time_s = (time_c / 1000) % 60;
        time_m = (time_c / 1000) / 60;
    }
    glutTimerFunc(16, Timer, 0);
}

// Головна функція
int main(int argc, char** argv) {

    srand(time(NULL));
    manageGame.InitGame();
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
