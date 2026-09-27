#include <iostream>
#include <conio.h> // For kbhit() and getch()
#include <windows.h> // For Sleep()
using namespace std; 
const int WIDTH = 20, HEIGHT = 10; 
int snakeX = WIDTH / 2, snakeY = HEIGHT / 2; //snake's position at the center of the board.
int fruitX = rand() % WIDTH, fruitY = rand() % HEIGHT; 
int score = 0; //starting score
bool gameOver = false; //bool=boolean (true,false)
// Function to set the console cursor position
void SetCursorPosition(int x, int y) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, position);
}
void Draw() //fun to draw boundary,snake,fruit
{
    SetCursorPosition(0, 0); // Move cursor to the top-left corner
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1)
                cout << "#"; // Boundary
            else if (x == snakeX && y == snakeY)
                cout << "O"; // Snake
            else if (x == fruitX && y == fruitY)
                cout << "F"; // Fruit
            else
                cout << " "; // Empty space
        }
        cout << endl;
    }
    cout << "Score: " << score << endl; //score show
}

void Input() //fun
{
    if (_kbhit()) // Check if a key is pressed
	 { 
        switch (_getch()) {
        case 'u': snakeY--; break; // Move up
        case 'd': snakeY++; break; // Move down
        case 'l': snakeX--; break; // Move left
        case 'r': snakeX++; break; // Move right
        }
    }
}

void Logic() 
{
    // Check if snake eats the fruit
    if (snakeX == fruitX && snakeY == fruitY) {
        score++;
        fruitX = rand() % (WIDTH - 2) +1;
        fruitY = rand() % (HEIGHT - 2) +1;
    }

    // Check for collisions with walls
    if (snakeX <= 0 || snakeX >= WIDTH - 1 || snakeY <= 0 || snakeY >= HEIGHT - 1)
        gameOver = true;
}

int main() 
{
    // Hide cursor for smoother display
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    while (!gameOver) //condition specify to over the game 
	 {
        Draw();
        Input();
        Logic();
        Sleep(100); // Slow down the game- speed
    }

    cout << "Game Over! Final Score: " << score << endl;
    return 0;
}

