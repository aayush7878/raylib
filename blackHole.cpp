#include<iostream>
#include<vector>
#include<raylib.h>
using namespace std;

int main(){
    const int winHeight = 900;
    const int winWidth = 900;

    InitWindow(winWidth, winHeight, "floating particles");

    Color ballColor = BLACK;

    Vector2 mousePosition = {-100, -100};

    vector<Vector2> ballPosition(500);
    for(int i=0; i<500; ++i){
        ballPosition[i] = {(float) GetRandomValue(0, 900), (float) GetRandomValue(0, 900)};
    }

    SetTargetFPS(60);

    vector<Vector2> direction;
    for(int i=0; i<500; ++i) direction.push_back({0.0, 0.0});

    bool check = false;

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            mousePosition = GetMousePosition();
            check = true;
        }

        if(check){
            for(int i=0; i<500; ++i){
                direction[i].x = mousePosition.x - ballPosition[i].x;
                direction[i].y = mousePosition.y - ballPosition[i].y;
            }

            for(int i=0; i<500; ++i){
                ballPosition[i].x += direction[i].x * (0.01);
                ballPosition[i].y += direction[i].y * (0.01);
            }
 
        }

        for(int i=0; i<500; ++i){
            DrawCircleV(ballPosition[i], 5, ballColor);
        }

        DrawCircleV(mousePosition, 50, ballColor);

        EndDrawing();
    }

    CloseWindow();

}
