#include "DrawGame.h"


GameLogic* game = new GameLogic();
int indicatorX = 0;
int indicatorY = 0;


void DrawGame::DrawBoard() {
    // Bottom side of the board
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(160.0 / 255.0, 82.0 / 255.0, 45.0 / 255.0);
    glBegin(GL_POLYGON);

    glVertex3f(-32, -32, 0);
    glVertex3f(-32, 32, 0);
    glVertex3f(32, 32, 0);
    glVertex3f(32, -32, 0);
    glEnd();

    //board frame
    float frameThickness = 3.5;
    float frameHeight = 3.5;

    glColor3f(160.0 / 255.0, 82.0 / 255.0, 45.0 / 255.0);
    glBegin(GL_QUADS);

    // Bottom and top beams
    for (int i = 0; i < 2; i++) {
        float yPos = i == 0 ? -Posit1 - frameThickness : Posit1;
        // Top face
        glVertex3f(-Posit1 - frameThickness, yPos, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos + frameThickness, frameHeight);
        glVertex3f(-Posit1 - frameThickness, yPos + frameThickness, frameHeight);

        // Bottom face
        glVertex3f(-Posit1 - frameThickness, yPos, 0);
        glVertex3f(Posit1 + frameThickness, yPos, 0);
        glVertex3f(Posit1 + frameThickness, yPos + frameThickness, 0);
        glVertex3f(-Posit1 - frameThickness, yPos + frameThickness, 0);

        // Side faces
        glVertex3f(-Posit1 - frameThickness, yPos, 0);
        glVertex3f(-Posit1 - frameThickness, yPos, frameHeight);
        glVertex3f(-Posit1 - frameThickness, yPos + frameThickness, frameHeight);
        glVertex3f(-Posit1 - frameThickness, yPos + frameThickness, 0);

        glVertex3f(Posit1 + frameThickness, yPos, 0);
        glVertex3f(Posit1 + frameThickness, yPos, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos + frameThickness, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos + frameThickness, 0);

        // front faces
        glVertex3f(-Posit1 - frameThickness, yPos, 0);
        glVertex3f(-Posit1 - frameThickness, yPos, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos, 0);

        glVertex3f(-Posit1 - frameThickness, yPos + frameThickness, 0);
        glVertex3f(-Posit1 - frameThickness, yPos + frameThickness, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos + frameThickness, frameHeight);
        glVertex3f(Posit1 + frameThickness, yPos + frameThickness, 0);
    }

    // Left and right beams
    for (int i = 0; i < 2; i++) {
        float xPos = i == 0 ? -Posit1 - frameThickness : Posit1;
        // Top faces
        glVertex3f(xPos, -Posit1 - frameThickness, frameHeight);
        glVertex3f(xPos + frameThickness, -Posit1 - frameThickness, frameHeight);
        glVertex3f(xPos + frameThickness, Posit1 + frameThickness, frameHeight);
        glVertex3f(xPos, Posit1 + frameThickness, frameHeight);

        // Bottom faces
        glVertex3f(xPos, -Posit1 - frameThickness, 0);
        glVertex3f(xPos + frameThickness, -Posit1 - frameThickness, 0);
        glVertex3f(xPos + frameThickness, Posit1 + frameThickness, 0);
        glVertex3f(xPos, Posit1 + frameThickness, 0);

        // Side faces
        glVertex3f(xPos, -Posit1 - frameThickness, 0);
        glVertex3f(xPos, -Posit1 - frameThickness, frameHeight);
        glVertex3f(xPos + frameThickness, -Posit1 - frameThickness, frameHeight);
        glVertex3f(xPos + frameThickness, -Posit1 - frameThickness, 0);

        glVertex3f(xPos, Posit1 + frameThickness, 0);
        glVertex3f(xPos, Posit1 + frameThickness, frameHeight);
        glVertex3f(xPos + frameThickness, Posit1 + frameThickness, frameHeight);
        glVertex3f(xPos + frameThickness, Posit1 + frameThickness, 0);

        // Front faces
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

    //Black and white cells
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

            // Top side
            glBegin(GL_POLYGON);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2, 2.5);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2 + Posit2, 2.5);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2 + Posit2, 2.5);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2, 2.5);
            glEnd();

            //  left side
            glBegin(GL_POLYGON);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2, 2.5);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2 + Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2 + Posit2, 2.5);
            glEnd();

            //  right side
            glBegin(GL_POLYGON);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2, 2.5);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2 + Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2 + Posit2, 2.5);
            glEnd();

            //  front side
            glBegin(GL_POLYGON);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2 + Posit2, 2.5);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2 + Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2 + Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2 + Posit2, 2.5);

            // back side
            glBegin(GL_POLYGON);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2, 2.5);
            glVertex3f(-Posit1 + j * Posit2 + Posit2, -Posit1 + i * Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2, 0);
            glVertex3f(-Posit1 + j * Posit2, -Posit1 + i * Posit2, 2.5);
            glEnd();
        }
}

// Checkers
void DrawGame::DrawCheckers() {
    GameLogic::Checker*** checkers = game->GetField();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    for (int i = 0; i < NumberOfCells; i++)
        for (int j = 0; j < NumberOfCells; j++) {
            GameLogic::Checker* checker = checkers[7 - i][j];
            if (checker == null)
                continue;

            int height = game->IsChose(j, 7 - i) ? 5 : 0;
            // side part of the checkers
            // white
            if (checker->type == GameLogic::Checker::Type::Simple && checker->player == GameLogic::Player::White) {
                glColor3f(252.0 / 255.0, 202.0 / 255.0, 241.0 / 255.0);
            }
            // black
            else if (checker->type == GameLogic::Checker::Type::Simple && checker->player == GameLogic::Player::Black) {
                glColor3f(30.0 / 255.0, 144.0 / 255.0, 255.0 / 255.0);
            }
            // white queen
            if (checker->type == GameLogic::Checker::Type::King && checker->player == GameLogic::Player::White) {
                glColor3f(255.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0);
            }
            // black queen
            else if (checker->type == GameLogic::Checker::Type::King && checker->player == GameLogic::Player::Black) {
                glColor3f(0.0 / 255.0, 0.0 / 255.0, 0.0 / 255.0);
            }
            glPushMatrix();
            glTranslatef(-Posit1 + j * Posit2 + 4, -Posit1 + i * Posit2 + 4, 2.5 + height);
            gluCylinder(gluNewQuadric(), 3.5, 3.5, 2, 32, 32);
            glPopMatrix();
            // top part
            // white
            if (checker->type == GameLogic::Checker::Type::Simple && checker->player == GameLogic::Player::White) {
                glColor3f(255.0 / 255.0, 228.0 / 255.0, 196.0 / 255.0);
            }
            // black
            else if (checker->type == GameLogic::Checker::Type::Simple && checker->player == GameLogic::Player::Black) {
                glColor3f(83.0 / 255.0, 113.0 / 255.0, 136.0 / 255.0);
            }
            // white queen
            if (checker->type == GameLogic::Checker::Type::King && checker->player == GameLogic::Player::White) {
                glColor3f(220.0 / 255.0, 20.0 / 255.0, 60.0 / 255.0);
            }
            // black queen
            else if (checker->type == GameLogic::Checker::Type::King && checker->player == GameLogic::Player::Black) {
                glColor3f(220.0 / 255.0, 20.0 / 255.0, 60.0 / 255.0);
            }

            glPushMatrix();
            glTranslatef(-Posit1 + j * Posit2 + 4, -Posit1 + i * Posit2 + 4, 4.5 + height);
            gluDisk(gluNewQuadric(), 0, 3.5, 32, 1);
            glPopMatrix();
        }
}

//Indicator
void DrawGame::DrawIndicator() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(219.0f / 255.0f, 112.0f / 255.0f, 147.0f / 255.0f);

#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

    int h = 5;
    float radius = 2;
    int num_segments = 20;

    glPushMatrix();
    glTranslatef(-Posit1 + indicatorX * Posit2 + 4, -Posit1 + indicatorY * Posit2 + 4, 5 + h);

    // cone drawing
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, -h); //cone apex
    for (int i = 0; i <= num_segments; ++i) {
        float angle = 2 * M_PI * i / num_segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();
    glPopMatrix();
}
