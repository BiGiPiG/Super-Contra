#include <string>
#include <iostream>
#include "raylib.h"


class Character {
private:
    Texture2D character;
    const float characterSpeed = 8.0f;
    Vector2 position;
    Rectangle frameRec;
    int countFrame; // Number of frames for animation
    int currentFrame; // Current frame for animation
    float updateTime; // Time to update frames
    float runningTime; // Accumulated time for animation

public:
    Character(std::string texturePath, float x, float y, int frames) 
        : countFrame(frames), currentFrame(0), updateTime(5.0f), runningTime(5.0f) {
        character = LoadTexture(texturePath.c_str());
        position.x = x;
        position.y = y;
        frameRec = { 0.0f, 0.0f, (float)character.width / countFrame, (float)character.height };
    }

    ~Character() {
        UnloadTexture(character);
    }

    void run() {
        if (IsKeyDown(KEY_RIGHT)) {
            position.x += characterSpeed;
            currentFrame = (currentFrame + 1) % countFrame; // Update frame for animation
        }
        if (IsKeyDown(KEY_LEFT)) {
            position.x -= characterSpeed;
            currentFrame = (currentFrame + 1) % countFrame; // Update frame for animation
        }
        
        // Update the rectangle for the current frame
        frameRec.x = (float)currentFrame * (character.width / countFrame);
    }

    void jump() {
        // Simple jump logic: implement gravity and jump height
        static bool isJumping = false;
        static float jumpHeight = 10.0f;
        
        if (IsKeyPressed(KEY_SPACE) && !isJumping) {
            position.y -= jumpHeight; // Jump up
            isJumping = true;
        }

        if (isJumping) {
            position.y += 0.5f; // Simulate gravity pulling down
            if (position.y >= GetScreenHeight() - character.height) { // Reset jump when landing
                position.y = GetScreenHeight() - character.height;
                isJumping = false;
            }
        }
    }

    void draw() const {
        DrawTextureRec(character, frameRec, position, WHITE);
    }

    Texture2D getTexture() const {
        return character;
    }

    void setX(int x) {
        position.x = x;
    }

    void setY(int y) {
        position.y = y;
    }

    int getX() {
        return position.x;
    }

    int getY() {
        return position.y;
    }
};