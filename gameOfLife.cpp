#include<raylib.h>
#include<vector>
using namespace std;

const int winWidth = 900;
const int winHeight = 900;

int cellSize = 10;
int rows = winHeight/cellSize;
int columns = winWidth/cellSize;

vector<vector<int>> cells(rows, vector<int> (columns, 0));
vector<vector<int>> grid(rows, vector<int> (columns, 0));

void SetValue(int row, int column, int value){
    if(row >=0 && row < rows && column >=0 && column < columns){
        cells[row][column] = value;
    }
}

int countNeighbors(int x, int y) {
    int neighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;  
            int newX = (x + i + rows) % rows;  
            int newY = (y + j + columns) % columns;
            neighbors += cells[newX][newY];
        }
    }
    return neighbors;
}

void initializeRandomly() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cells[i][j] = GetRandomValue(0, 1);
        }
    }
}


int main(){
    InitWindow(winWidth, winHeight, "GameOfLife");
    SetTargetFPS(7);

    Color color =  { 29, 29, 29, 255 };

    initializeRandomly();

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(color);

        for(int x=0; x<rows; ++x){
            for(int y=0; y<columns; ++y){
                int cnt = countNeighbors(x, y);
                if(cells[x][y]){
                    if(cnt < 2 || cnt > 3) grid[x][y] = 0;
                    else if(cnt == 3 || cnt == 2) grid[x][y] = 1; 
                }
                else{
                    if(cnt == 3) grid[x][y] = 1;
                }
            }
        }

        for(int row=0; row < rows; ++row){
            for(int column=0; column < columns; ++column){
                Color color = grid[row][column] ? Color{ 0, 255, 0, 255 } : Color{ 55, 55, 55, 255 };
                DrawRectangle(row * cellSize, column * cellSize, cellSize-1, cellSize-1, color);
            }
        }

        for(int x=0; x<rows; ++x){
            for(int y=0; y<columns; ++y){
                cells[x][y] = grid[x][y];
            }
        }

        EndDrawing();
    }

    CloseWindow();


}
