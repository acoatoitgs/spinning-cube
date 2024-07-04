#include <bits/stdc++.h>
#include "rotation.h"
using namespace std;

#define WIDTH 160
#define HEIGHT 44

char display[HEIGHT][WIDTH];
double zPriority[HEIGHT][WIDTH];
array<double, 3> rotation;
double rotationTime = 0.0;
double cK = 40;

// Custom variables
char background = ' ';
double cubeSize = 20;
double horizontalOffset = cubeSize + WIDTH / 2;
double verticalOffset = HEIGHT / 2;
double incrementSpeed = 0.6;
double distFromCam = 100;
double rotationSpeed = 0.04;

void printDisplay()
{
    printf("\x1b[H");
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int k = 0; k < WIDTH; k++)
        {
            putchar(display[i][k]);
        }
        putchar('\n');
    }
}

void computeFace(array<double, 3> pos, int ch)
{
    array<double, 3> nc = f_Rotate(pos, rotation);

    nc[2] += distFromCam;
    double z_prior = 1 / nc[2];

    int xp = (int)(horizontalOffset + cK * z_prior * nc[0] * 2);
    int yp = (int)(verticalOffset + cK * z_prior * nc[1]);

    if (xp >= 0 && xp < WIDTH && yp >= 0 && yp < HEIGHT)
    {
        if (z_prior > zPriority[yp][xp])
        {
            zPriority[yp][xp] = z_prior;
            display[yp][xp] = ch;
        }
    }
}
void drawCube()
{
    for (double i = -cubeSize; i < cubeSize; i += incrementSpeed)
    {
        //      Back
        //      Up
        // Left Front Right
        //      Down
        for (double k = -cubeSize; k < cubeSize; k += incrementSpeed)
        {
            // Back
            computeFace({i, k, -cubeSize}, '@');
            // Right
            computeFace({cubeSize, k, i}, '$');
            // Left
            computeFace({-cubeSize, k, -i}, '~');
            // Front
            computeFace({-i, k, cubeSize}, '#');
            // Up
            computeFace({i, -cubeSize, -k}, ';');
            // Down
            computeFace({i, cubeSize, k}, '+');
        }
    }
}
int main()
{
    while (1)
    {
        memset(display, background, sizeof(display));
        memset(zPriority, 0, sizeof(zPriority));

        drawCube();
        printDisplay();
        rotation[0] = sin(rotationTime * 0.2) * M_PI;
        rotation[1] = sin(rotationTime * 0.15) * M_PI;
        rotation[2] = sin(rotationTime * 0.25) * M_PI;
        rotationTime += rotationSpeed;

        // force deltaTime
        usleep(2 * 8000);
    }
}