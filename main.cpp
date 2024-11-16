#include "raylib.h"

const int screenWidth = 1080;
const int screenHeight = 800;
const int countFrameRun = 6; // Количество кадров анимации бега
const int countFrameJump = 4;
const int countFrame = 6;
const int billSpeed = 5;   // Скорость движения персонажа
const float gravity = 0.5;
const int groundPos = 400;
const int BillHight = 128;
const float jumpHeight = 17.0f;

bool isOnGround(const Vector2 &position) {
    return position.y >= groundPos;
}
//------------------------------------------------------------------------------------
// Программа: основная точка входа
//------------------------------------------------------------------------------------
int main(void)
{
    // Инициализация
    //--------------------------------------------------------------------------------------
    

    // Инициализация окна
    InitWindow(screenWidth, screenHeight, "SuperContra");

    // Загрузка текстуры персонажа
    Texture2D bill = LoadTexture("resources/runForwardBill.png");
    
    SetTargetFPS(60); // Установка FPS игры

    // Переменные для управления анимацией
    int frameDelay = 7; // Задержка между кадрами
    int frameDelayCounter = 0;
    Vector2 position = {groundPos, screenHeight / 2.0f}; // Позиция персонажа
    Rectangle frameRec = { 0.0f, 0.0f, (float)bill.width / countFrame, (float)bill.height / 2 }; // Рамка для текущего кадра
    int currentFrame = 0; // Текущий кадр анимации
    
    bool isJumping = false; // Флаг для проверки состояния прыжка
    float jumpVelocity = 0.0f; // Начальная скорость прыжка

    //--------------------------------------------------------------------------------------

    // Основной игровой цикл
    while (!WindowShouldClose()) // Проверка на закрытие окна или нажатие ESC
    {
        // Обновление движения персонажа и анимации
        bool billMoving = false;
        if (isOnGround(position) && IsKeyPressed(KEY_SPACE)) {
            isJumping = true;
            jumpVelocity = -jumpHeight;
        }
        
        if (isJumping) {
            position.y += jumpVelocity; // Обновляем вертикальную позицию персонажа
            jumpVelocity += gravity; // Применяем гравитацию

            if (isOnGround(position)) { // Проверка на приземление
                position.y = groundPos; // Сброс позиции на землю
                isJumping = false; // Завершение прыжка
                jumpVelocity = 0.0f; // Сброс скорости прыжка
            }
        }
        
        
        
        if (IsKeyDown(KEY_RIGHT)) {
            position.x += billSpeed;
            billMoving = true;
            if (frameRec.width < 0) {
                frameRec.width = -frameRec.width;
            }
        } else if (IsKeyDown(KEY_LEFT)) {
            position.x -= billSpeed;
            billMoving = true;
            if (frameRec.width > 0) {
                frameRec.width = -frameRec.width;
            }
        } else {
            billMoving = false;
        }
        
        if (!isOnGround(position)) {
            position.y += gravity;
        } else {
            position.y = groundPos;
        }
    
        
        ++frameDelayCounter;
        if (frameDelayCounter > frameDelay) {
            frameDelayCounter = 0;
            if (isJumping) {
                currentFrame = (currentFrame + 1) % countFrameJump;
                frameRec.x = (float) bill.width / countFrameRun * currentFrame;
                frameRec.y = (float) bill.height / 2;
            } else if (billMoving) {
                currentFrame = (currentFrame + 1) % countFrameRun;
                frameRec.x = (float)bill.width / countFrameRun * currentFrame;
                frameRec.y = 0;
            } else {
                currentFrame = 0; 
                frameRec.x = 0;
                frameRec.y = 0;
            }
        }

        // Отрисовка
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureRec(bill, frameRec, position, WHITE); // Отрисовка текущего кадра персонажа
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // Де-инициализация
    //--------------------------------------------------------------------------------------
    UnloadTexture(bill);   // Освобождение текстуры персонажа
    CloseWindow();         // Закрытие окна и контекста OpenGL
    //--------------------------------------------------------------------------------------

    return 0;
}