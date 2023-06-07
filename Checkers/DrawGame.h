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

//// Створення об'єкту класу GameLogic 
//GameLogic* game = new GameLogic();

// Відображення столу
void DrawBoard() {  
    // Нижня частина дошки
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  
    glColor3f(160.0 / 255.0, 82.0 / 255.0, 45.0 / 255.0);
    glBegin(GL_POLYGON);

    glVertex3f(-32, -32, 0);
    glVertex3f(-32, 32, 0);
    glVertex3f(32, 32, 0);
    glVertex3f(32, -32, 0);
    glEnd();

    // Рамка для дошки
    float frameThickness = 3.5;
    float frameHeight = 3.5;

    glColor3f(160.0 / 255.0, 82.0 / 255.0, 45.0 / 255.0);
    glBegin(GL_QUADS);

    // Верхня та нижня горизонтальні балки
    for (int i = 0; i < 2; i++) {
        float yPos = i == 0 ? -Posit1 - frameThickness : Posit1;
        // Верхня грань
        glVertex3f(-Posit1 - frameThickness, yPos, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos + frameThickness, frameHeight);
        glVertex3f(-Posit1 - frameThickness, yPos + frameThickness, frameHeight);

        // Нижня грань
        glVertex3f(-Posit1 - frameThickness, yPos, 0);
        glVertex3f(Posit1 + frameThickness, yPos, 0);
        glVertex3f(Posit1 + frameThickness, yPos + frameThickness, 0);
        glVertex3f(-Posit1 - frameThickness, yPos + frameThickness, 0);

        // Бічні грані
        glVertex3f(-Posit1 - frameThickness, yPos, 0);
        glVertex3f(-Posit1 - frameThickness, yPos, frameHeight);
        glVertex3f(-Posit1 - frameThickness, yPos + frameThickness, frameHeight);
        glVertex3f(-Posit1 - frameThickness, yPos + frameThickness, 0);

        glVertex3f(Posit1 + frameThickness, yPos, 0);
        glVertex3f(Posit1 + frameThickness, yPos, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos + frameThickness, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos + frameThickness, 0);

        // Сполучні грані
        glVertex3f(-Posit1 - frameThickness, yPos, 0);
        glVertex3f(-Posit1 - frameThickness, yPos, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos, 0);

        glVertex3f(-Posit1 - frameThickness, yPos + frameThickness, 0);
        glVertex3f(-Posit1 - frameThickness, yPos + frameThickness, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos + frameThickness, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos + frameThickness, 0);
    }

    // Ліва та права вертикальні балки
    for (int i = 0; i < 2; i++) {
        float xPos = i == 0 ? -Posit1 - frameThickness : Posit1;
        // Верхня грань
        glVertex3f(xPos, -Posit1 - frameThickness, frameHeight);
        glVertex3f(xPos + frameThickness, -Posit1 - frameThickness, frameHeight);
        glVertex3f(xPos + frameThickness, Posit1 + frameThickness, frameHeight);
        glVertex3f(xPos, Posit1 + frameThickness, frameHeight);

        // Нижня грань
        glVertex3f(xPos, -Posit1 - frameThickness, 0);
        glVertex3f(xPos + frameThickness, -Posit1 - frameThickness, 0);
        glVertex3f(xPos + frameThickness, Posit1 + frameThickness, 0);
        glVertex3f(xPos, Posit1 + frameThickness, 0);

        // Бічні грані
        glVertex3f(xPos, -Posit1 - frameThickness, 0);
        glVertex3f(xPos, -Posit1 - frameThickness, frameHeight);
        glVertex3f(xPos + frameThickness, -Posit1 - frameThickness, frameHeight);
        glVertex3f(xPos + frameThickness, -Posit1 - frameThickness, 0);

        glVertex3f(xPos, Posit1 + frameThickness, 0);
        glVertex3f(xPos, Posit1 + frameThickness, frameHeight);
        glVertex3f(xPos + frameThickness, Posit1 + frameThickness, frameHeight);
        glVertex3f(xPos + frameThickness, Posit1 + frameThickness, 0);

        // Сполучні грані
        glVertex3f(xPos, -Posit1 - frameThickness, 0);
        glVertex3f(xPos, -Posit1 - frameThickness, frameHeight);
        glVertex3f(xPos, Posit1 + frameThickness, frameHeight);
        glVertex3f(xPos, Posit1 + frameThickness, 0);

        glVertex3f(xPos + frameThickness, -Posit1 - frameThickness, 0);
        glVertex3f(xPos + frameThickness, -Posit1 - frameThickness, frameHeight);
        glVertex3f(xPos + frameThickness, Posit1 + frameThickness, frameHeight);
        glVertex3f(xPos + frameThickness, Posit1 + frameThickness, 0);
    }

    glEnd();

    for (int i = 0; i < NumberOfCells; i++)
        for (int j = 0; j < NumberOfCells; j++) {
            if (i % 2 == 0)
                if (j % 2 == 0)
                    glColor3f(39.0 / 207.0, 55.0 / 255.0, 77.0 / 220.0);
                else
                    glColor3f((207.0 - 39.0) / 207.0, (255.0 - 55.0) / 255.0, (220.0 - 77.0) / 220.0);
            else
                if (j % 2 == 0)
                    glColor3f((207.0 - 39.0) / 207.0, (255.0 - 55.0) / 255.0, (220.0 - 77.0) / 220.0);
                else
                    glColor3f(39.0 / 207.0, 55.0 / 255.0, 77.0 / 220.0);

            // Верхня сторона
            glBegin(GL_POLYGON);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2, 2.5);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2 + Posit2, 2.5);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2 + Posit2, 2.5);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2, 2.5);
            glEnd();

            //  Ліва сторона
            glBegin(GL_POLYGON);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2, 2.5);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2 + Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2 + Posit2, 2.5);
            glEnd();

            //  Права сторона
            glBegin(GL_POLYGON);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2, 2.5);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2 + Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2 + Posit2, 2.5);
            glEnd();

            //  Лицьова сторона
            glBegin(GL_POLYGON);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2 + Posit2, 2.5);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2 + Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2 + Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2 + Posit2, 2.5);

            // Тильна сторона
            glBegin(GL_POLYGON);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2, 2.5);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2, 2.5);
            glEnd();
        }
}

// Відображення шашок
void DrawCheckers() {
    /*GameLogic::Checker*** checkers = game->GetField();*/
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    for (int i = 0; i < NumberOfCells; i++)
        for (int j = 0; j < NumberOfCells; j++) {
            GameLogic::Checker* checker = checkers[7 - i][j];
            if (checker == null)
                continue;

            int height = game->IsChose(j, 7 - i) ? 5 : 0;
            // Бокова частина шашок
            // Проста біла
            if (checker->type == GameLogic::Checker::Type::Simple && checker->player == GameLogic::Player::White) {
                glColor3f(252.0 / 255.0, 202.0 / 255.0, 241.0 / 255.0);
            }
            // Проста чорна
            else if (checker->type == GameLogic::Checker::Type::Simple && checker->player == GameLogic::Player::Black) {
                glColor3f(30.0 / 255.0, 144.0 / 255.0, 255.0 / 255.0);
            }
            // Дамка біла
            if (checker->type == GameLogic::Checker::Type::King && checker->player == GameLogic::Player::White) {
                glColor3f(255.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0);
            }
            // Дамка чорна
            else if (checker->type == GameLogic::Checker::Type::King && checker->player == GameLogic::Player::Black) {
                glColor3f(0.0 / 255.0, 0.0 / 255.0, 0.0 / 255.0);
            }
            glPushMatrix();
            glTranslatef(-Posit1 + j * Posit2 + 4, -Posit1 + i * Posit2 + 4, 2.5 + height);
            gluCylinder(gluNewQuadric(), 3.5, 3.5, 2, 32, 32);
            glPopMatrix();
            // Вернхя частина шашок
            // Проста біла
            if (checker->type == GameLogic::Checker::Type::Simple && checker->player == GameLogic::Player::White) {
                glColor3f(255.0 / 255.0, 228.0 / 255.0, 196.0 / 255.0);
            }
            // Проста чорна
            else if (checker->type == GameLogic::Checker::Type::Simple && checker->player == GameLogic::Player::Black) {
                glColor3f(83.0 / 255.0, 113.0 / 255.0, 136.0 / 255.0);
            }
            // Дамка біла
            if (checker->type == GameLogic::Checker::Type::King && checker->player == GameLogic::Player::White) {
                glColor3f(220.0 / 255.0, 20.0 / 255.0, 60.0 / 255.0);
            }
            // Дамка чорна
            else if (checker->type == GameLogic::Checker::Type::King && checker->player == GameLogic::Player::Black) {
                glColor3f(220.0 / 255.0, 20.0 / 255.0, 60.0 / 255.0);
            }

            glPushMatrix();
            glTranslatef(-Posit1 + j * Posit2 + 4, -Posit1 + i * Posit2 + 4, 4.5 + height);
            gluDisk(gluNewQuadric(), 0, 3.5, 32, 1);
            glPopMatrix();
        }
}

// Відображення стрілки
void DrawIndicator() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(219.0f / 255.0f, 112.0f / 255.0f, 147.0f / 255.0f);

    #include <cmath>
    #ifndef M_PI
    #define M_PI 3.14159265358979323846
    #endif

    int h = 5;
    float radius = 2;
    // Кількість сегментів для створення основи конуса
    int num_segments = 20; 

    glPushMatrix();
    glTranslatef(-Posit1 + indicatorX * Posit2 + 4, -Posit1 + indicatorY * Posit2 + 4, 5 + h);

    // Малюємо конус
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, -h); // Вершина конуса
    for (int i = 0; i <= num_segments; ++i) {
        float angle = 2 * M_PI * i / num_segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();   
    glPopMatrix();
}

#endif