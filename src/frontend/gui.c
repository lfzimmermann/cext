#include "gui.h"
#include "raylib.h"

void run_ed_gui(void){

    InitWindow(400, 200, "raygui - controls test suite");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();


    return 0;
}
