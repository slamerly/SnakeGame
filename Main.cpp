#include "raylib.h"
#include <string>
#include <iostream>
#include <vector>
#include "projects/VS2017/examples/Snake.h"
#include "projects/VS2017/examples/Board.h"


using namespace std;

void Update();
void Draw();
void InitGame();

const int screenWidth = 910;
const int screenHeight = 540;
const int squareSize = 31;
const Vector2 startingArea = { 250, 50 };
int frames = 0;
int bestScore = 0;

Snake snake;
Board board;
Food food;

int main(int argc, char* argv[])
{
    // Initialization
    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(60);  

    snake.SetLoose(true);

    // Main game loop
    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }

    CloseWindow();

    return 0;
}

void Update()
{
    if (!snake.GetLoose())
    {
        snake.Update(frames, &food);
        frames++;
    }
    else
    {
        if (food.GetScore() > bestScore)
            bestScore = food.GetScore();
        if (IsKeyPressed(KEY_ENTER))
        {
            frames = 0;
            InitGame();
        }
    }
}

void Draw()
{
    BeginDrawing();

    ClearBackground(BLACK);
    
    if (!snake.GetLoose())
    {
        snake.Draw();
        food.Draw();
        board.Draw();
        DrawText(FormatText("BEST: %i", bestScore), squareSize, squareSize*3, 25, YELLOW);
    }
    else
    {
        DrawText("Press ENTER for new game", GetScreenWidth() / 2 - MeasureText("Press ENTER for new game", 25) / 2, GetScreenHeight() / 2 - 50, 25, GRAY);
        if (bestScore != 0) 
        {
            DrawText(FormatText("BEST SCORE: %i", bestScore), GetScreenWidth() / 2 - MeasureText(FormatText("BEST SCORE : %i", bestScore), 25) / 2, GetScreenHeight() * 0.6f, 25, YELLOW);
            DrawText(FormatText("Score: %i", food.GetScore()), GetScreenWidth() / 2 - MeasureText(FormatText("Score : %i", food.GetScore()), 20) / 2, GetScreenHeight() * 0.5f, 20, GRAY);
        }
    }

    EndDrawing();
}

void InitGame()
{
    board = Board(screenWidth / 2, screenHeight - 100, squareSize, startingArea);
    snake = Snake({ (float)(board.GetAreaWidth() / 2) + startingArea.x, (float)(board.GetAreaHeight() / 2) + startingArea.y}, squareSize, &board);
    food = Food({ (float)(board.GetNbColumn() / 2) + startingArea.x, (float)(board.GetNbLine() / 2) + startingArea.y }, squareSize, RED);
}