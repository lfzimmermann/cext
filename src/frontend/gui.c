#include "../backend/gap_buffer.h"
#include "gui.h"
#include "raylib.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

int run_ed_gui(struct Gap_Buffer_Struct* gp){

    InitWindow(800, 600, "raygui - controls test suite");
    SetTargetFPS(60);

    int font_size = 22;

    while (!WindowShouldClose())
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(DARKGRAY);
        char c;
        if ((c = GetCharPressed()) != 0 ){
            gp_insert(gp, c);
        }

        int k;
        k = GetKeyPressed();
        switch(k){

            case KEY_BACKSPACE:
                gp_delete(gp);
                break;

            case KEY_LEFT:
                gp_move_cursor(gp, gp->gap.start - 1);
                break;


            case KEY_RIGHT:
                gp_move_cursor(gp, gp->gap.start + 1);
                break;

            case KEY_ENTER:
                gp_insert(gp, '\n');
                break;

            case KEY_UP:
                char* text = malloc(gp->gap.start);
                memcpy(text, gp->buffer, gp->gap.start);
                char pos_c[20];
                int pos = strrchr(text, '\n') - text;
                sprintf(pos_c, "%d", pos);
                DrawText(pos_c, 10, 100, font_size, RED);
                free(text);
                gp_move_cursor(gp, pos);
                break;
            
            case KEY_DOWN:
                break;





        }

        DrawText(gp_get_buffer_content(gp), 10, 10, font_size, WHITE);

        EndDrawing();
    }

    CloseWindow();


    return 0;
}
