#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time() with cstdlib and ctime it prevents to generete same random number sequence

using namespace std;

bool gameOver;
const int width = 70;
const int height = 25;
int x, y, score;
int enemyX, enemyY; // Enemy position
vector<int> bulletX;
vector<int> bulletY;
int enemyMoveCounter = 0; // Counter to control enemy movement
int difficulty = 4;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{   // Display instructions
    cout << "Instructions:" << endl;
    cout << "- Try to kill the enemies and make the best score," << endl;
    cout << "- If you touch them or if they pass you the game will over." << endl;
    cout << "- Use 'a' to move left." << endl;
    cout << "- Use 'd' to move right." << endl;
    cout << "- Press Spacebar to shoot." << endl;

    cout << endl << "Press Enter to start the game...";

    // Wait for the Enter key press before starting the game
    while (_getch() != 13); // 13 is the ASCII code for Enter

    system("cls");

    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height - 4;
    score = 0;
    srand(time(NULL));              // Seed the random number generator.With this rand generates different number sequences
    enemyX = rand() % (width - 10) + 5; // Generate random number between 5 and width - 5

    enemyY = 0;
    bulletX.clear();
    bulletY.clear();

    // Hide the cursor
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Draw()
{
    // Move cursor to the top-left corner of the console window
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    cout << endl;
    cout << " Score: " << score << endl;
    cout << " Level: " << 5 - difficulty << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == y && j == x)
            {
                cout << "  /O\\";
            }
            if (i == y + 1 && j == x )
            {
                cout << " /+|+\\";
            }
            if (i == y + 2 && j == x)
            {
                cout << "/__|__\\";
            }

            if (i == enemyY && j == enemyX)
            {
                cout << "/ | \\";
            }
            if (i == enemyY + 1 && j == enemyX)
            {
                cout << "--O--";
            }
            if (i == enemyY + 2 && j == enemyX)
            {
                cout << "\\ | /";
            }
            else
            {
                bool printBullet = false;
                for (int k = 0; k < bulletX.size(); k++)
                {
                    if (bulletX[k]+3 == j && bulletY[k] == i)
                    {
                        cout << ".";
                        printBullet = true;
                        break;
                    }
                }
                if (!printBullet)
                {
                    if(i == enemyY && j == enemyX+1 || i == enemyY && j == enemyX+2 || i == enemyY && j == enemyX + 3 || i == enemyY && j == enemyX + 4 || i == enemyY && j == enemyX + 5)
                    {
                        continue;
                    }
                    if(i == enemyY+1 && j == enemyX+1 || i == enemyY+1 && j == enemyX+2 || i == enemyY+1 && j == enemyX + 3 || i == enemyY+1 && j == enemyX + 4 || i == enemyY+1 && j == enemyX + 5)
                    {
                        continue;
                    }
                    if(i == enemyY+2 && j == enemyX+2 || i == enemyY+2 && j == enemyX+2 || i == enemyY+2 && j == enemyX + 3|| i == enemyY+2 && j == enemyX + 4 || i == enemyY+2 && j == enemyX + 5)
                    {
                        continue;
                    }
                    if(i == y && j == x+1 || i == y && j == x+2 || i == y && j == x + 3 || i == y && j == x + 4 || i == y && j == x + 5)
                    {
                        continue;
                    }
                    if(i == y+1 && j == x+1 || i == y+1 && j == x+2 || i == y+1 && j == x + 3 || i == y+1 && j == x + 4 || i == y+1 && j == x + 5 || i == y+1 && j == x + 6)
                    {
                        continue;
                    }
                    if(i == y+2 && j == x+2 || i == y+2 && j == x+2 || i == y+2 && j == x + 3|| i == y+2 && j == x + 4 || i == y+2 && j == x + 5 || i == y+2 && j == x + 6 || i == y+2 && j == x + 7|| i == y+2 && j == x + 8)
                    {
                        continue;
                    }
                    else
                    {
                        cout << " ";
                    }
                }

            }
        }
        cout << endl;
    }

    // Move cursor to the position to display score and difficulty
    cursorPosition.X = 0;
    cursorPosition.Y = height;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    // Displaying the score on the right side of the console window

}


void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case ' ':
            bulletX.push_back(x);
            bulletY.push_back(y - 1);
            break;
        }
    }
    else
    {
        dir = STOP;
    }
}

void Logic()
{
    switch (dir)
    {
    case STOP:
        break;
    case LEFT:
        if (x - 5 == 0)
            break;
        x -= 2;
        break;
    case RIGHT:
        if (x + 5 == width - 2)
            break;
        x += 2;
        break;
    default:
        break;
    }

// Move enemy down every frame
if (enemyMoveCounter >= difficulty)
{
    if (enemyY < height)
    {
        enemyY++;
        if(enemyY == height)
        {
        gameOver = true; // End the game if collision detected
        }
    }
    else {
        enemyX = rand() % (width - 10) + 5; // Generate random number between 5 and width - 5
        enemyY = 0;
    }
    enemyMoveCounter = 0; // Reset counter
}
else {
    enemyMoveCounter++; // Increment counter
}


    // Check collision between bullets and enemy
    for (int i = 0; i < bulletX.size(); i++)
    {
        if ((bulletX[i] >= enemyX - 4 && bulletX[i] <= enemyX + 4) && (bulletY[i] >= enemyY && bulletY[i] <= enemyY + 3))
        {
            score++; // Increase score
            enemyX = rand() % (width - 10) + 5; // Generate random number between 5 and width - 5
            enemyY = 0;

            // When the difficulty decrease the speeds up
            if (score >= 50)
                difficulty = 0;
            else if (score >= 30)
                difficulty = 1;
            else if (score >= 20)
                difficulty = 2;
            else if (score >= 10)
                difficulty = 3;
            else
                difficulty = 4;

            bulletY[i] = -1;
        }
    }

    // Check collision between player and enemy
    if ((x >= enemyX - 5 && x <= enemyX + 5) && (y >= enemyY && y <= enemyY + 2))
    {
        system("cls");
        gameOver = true; // End the game if collision detected
    }


    // Move bullets up
    for (int i = 0; i < bulletY.size(); i++)
    {
        bulletY[i]--;
        if (bulletY[i] < 0) // Remove bullets when they go out of the screen
        {
            bulletX.erase(bulletX.begin() + i);
            bulletY.erase(bulletY.begin() + i);
        }
    }
}


int main()
{
    char restartChoice;

    do {
        Setup();
        while (!gameOver)
        {
            Draw();
            Input();
            Logic();
            Sleep(50); // Adjust this value as needed
        }
        system("cls");
        cout << "Game Over!" << endl;
        cout << "Your Final Score: " << score << endl;
        cout << "Press any key to play again . . .";

        restartChoice = _getch(); // Get the key pressed by the user

        system("cls");

        // Reset the game if the player chooses to restart
        gameOver = false;
        score = 0;
        difficulty = 5;
        enemyMoveCounter = 0;

    } while (true);

    return 0;
}

