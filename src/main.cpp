#include <raylib.h>

int main()
{
    InitWindow(800, 600, "Platformer");
    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
}
