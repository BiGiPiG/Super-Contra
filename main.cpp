#include "raylib.h"
#include "character.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1080;
    const int screenHeight = 800;
    const int countFrame = 6;

    // Initialize window
    InitWindow(screenWidth, screenHeight, "SuperContra");

    // Create the character instance
    Character bill("resources/runForwardBill.png", 350.0f, 400.0f, countFrame);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update character movement and jumping
        bill.run();
        bill.jump();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        bill.draw(); // Draw the character

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();         // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}