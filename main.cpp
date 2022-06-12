#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <conio.h>
#include <unistd.h>

using namespace std;

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

const int width = 80;
const int height = 30;
const int x = width / 2;
const int y = height / 2;
char activeKEY;
int mouseX, mouseY, score;
vector<pair<int, int>> coordinates = {};

bool coordinatInVector(int indexX, int indexY)
{
    for (int i = 0; i < coordinates.size(); i++)
        if (coordinates[i].first == indexX && coordinates[i].second == indexY)
            return true;
    return false;
}

bool isGameOver(int x, int y)
{
    if ((x == width - 1 || x == 0) || (y == height - 1 || y == 0))
        return true;
    return false;
}

void repeat(char c, int num)
{
    for (int i = 0; i < num; i++)
        cout << c;
}

void Setup()
{
    score = 0;
    activeKEY = 0;
    srand(time(0));
    mouseX = rand() % (width - 2) + 1;
    mouseY = rand() % (height - 2) + 1;
    coordinates = {{x, y}};
}

void drawScoreTable()
{
    repeat(' ', 33);
    cout << "--------------\n";

    repeat(' ', 33);
    cout << "|Score : " << score;
    int spaceN = score != 0 ? (int)log10(score) : 0;
    repeat(' ', 3 - spaceN);
    cout << "|\n";

    repeat(' ', 33);
    cout << "--------------\n";
}

void Draw()
{
    drawScoreTable();
    for (int i = 0; i < height; i++)
    {
        cout << "#";
        for (int j = 1; j < width; j++)
        {
            if (i == 0 || i == height - 1)
            {
                cout << "#";
                continue;
            }

            if (coordinatInVector(j, i))
                cout << "*";
            else if (i == mouseY && j == mouseX)
                cout << "@";
            else
                cout << " ";
        }
        cout << "#\n";
    }
    usleep(50000);
}

void Input()
{
    int value = 0;
    if (kbhit())
    {
        char key = getch();
        value = key;
    }

    switch (value)
    {
    case KEY_W:
        activeKEY = KEY_W;
        break;
    case KEY_A:
        activeKEY = KEY_A;
        break;
    case KEY_S:
        activeKEY = KEY_S;
        break;
    case KEY_D:
        activeKEY = KEY_D;
        break;
    default:
        break;
    }
}

void Logic()
{
    int lastX = coordinates.back().first;
    int lastY = coordinates.back().second;

    if (mouseX == lastX && mouseY == lastY)
    {
        score++;
        coordinates.insert(coordinates.begin(), coordinates.front());
        srand(time(0));
        mouseX = rand() % (width - 2) + 1;
        mouseY = rand() % (height - 2) + 1;
    }

    switch (activeKEY)
    {
    case KEY_W:
        lastY--;
        break;
    case KEY_A:
        lastX--;
        break;
    case KEY_S:
        lastY++;
        break;
    case KEY_D:
        lastX++;
        break;
    default:
        break;
    }

    pair<int, int> newCoordinate = {lastX, lastY};
    coordinates.erase(coordinates.begin());
    coordinates.push_back(newCoordinate);

    if (isGameOver(lastX, lastY))
    {
        system("clear");
        cout << "GAME OVER" << endl;
        sleep(10);
        Setup();
    }
}

int main()
{
    Setup();
    while (1)
    {
        system("clear");
        Draw();
        Input();
        Logic();
    }
    return 0;
}