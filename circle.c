#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h"

#define MAX_FRAME_DELAY 20
#define MIN_FRAME_DELAY 1
#define MAX_CIRCLES 100
#define MAX_COLORS_COUNT 21
#define NUM_FRAMES  3
#ifndef DATA_TYPE
    #define DATA_TYPE Circle
    #define DATA_TYPE Line
#endif

typedef struct Circle {
    Color color;
    float radius;
    float w;
    float positionX;
    float positionY;
} Circle;

typedef struct Line {
    float positionX;
    float positionY;
} Line;


int main() {
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Circle up, kiddo!");

    //Images Initialisation------------------------------------------------------------
    Image image = LoadImage("resources/sadant.png");
    Texture2D sadant = LoadTextureFromImage(image);
    UnloadImage(image);

    Image image2 = LoadImage("resources/lmao.png");
    Texture2D lmao = LoadTextureFromImage(image2);
    UnloadImage(image2);

    Image image3 = LoadImage("resources/eepy.png");
    Texture2D eepy = LoadTextureFromImage(image3);
    UnloadImage(image3);

    Image image4 = LoadImage("resources/buried.png");
    Texture2D buried = LoadTextureFromImage(image4);
    UnloadImage(image4);

    Image image5 = LoadImage("resources/sisyphus.png");
    Texture2D sisyphus = LoadTextureFromImage(image5);
    UnloadImage(image5);

    Image image6 = LoadImage("resources/bob.png");
    Texture2D bob = LoadTextureFromImage(image6);
    UnloadImage(image6);

    Image image7 = LoadImage("resources/burber.png");
    Texture2D burber = LoadTextureFromImage(image7);
    UnloadImage(image7);

    Image image8 = LoadImage("resources/bleh.png");
    Texture2D bleh = LoadTextureFromImage(image8);
    UnloadImage(image8);

    Image image9 = LoadImage("resources/sukuna.png");
    Texture2D sukuna = LoadTextureFromImage(image9);
    UnloadImage(image9);

    Image image10 = LoadImage("resources/geto.png");
    Texture2D geto = LoadTextureFromImage(image10);
    UnloadImage(image10);

    //GIF Initialisation-------------------------------------------------------------------
    int animFrames = 0;

    Image imGojo = LoadImageAnim("resources/gojorun.gif", &animFrames);

    Texture2D texGojo = LoadTextureFromImage(imGojo);

    unsigned int nextFrameDataOffset = 0;  

    int currentAnimFrame = 0;       
    int frameDelay = 8;             
    int frameCounter = 0;           

    SetTargetFPS(60);

    //Button Initialisation-----------------------------------------------------------------

    InitAudioDevice();

    Sound fxButton = LoadSound("resources/buttonfx.wav");
    SetSoundVolume(fxButton, 1.0);
    Texture2D button = LoadTexture("resources/button.png");

    float frameHeight = (float)button.height / NUM_FRAMES;
    Rectangle sourceRec = { 0, 0, (float)button.width, frameHeight };

    Rectangle btnBounds = { screenWidth / 5.3f - button.width, screenHeight / 2.5f - button.height, (float)button.width, frameHeight };

    int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    bool btnAction = false;         // Button action should be activated
    bool addCircles = false;        // Initialise circle-drawing
    int buttonClicks = 0;
    Vector2 mousePoint = { 0.0f, 0.0f };

    SetTargetFPS(60);
    //-----------------------------------------------------------------------------------------
    //Colour, Radius and Velocity Randomisation------------------------------------------------

    const char* colorNames[MAX_COLORS_COUNT] = {
        "DARKGRAY", "MAROON", "ORANGE", "DARKGREEN", "DARKBLUE", "DARKPURPLE",
        "DARKBROWN", "GRAY", "RED", "GOLD", "LIME", "BLUE", "VIOLET", "BROWN",
        "LIGHTGRAY", "PINK", "YELLOW", "GREEN", "SKYBLUE", "PURPLE", "BEIGE" };

    Color colors[MAX_COLORS_COUNT] = {
        DARKGRAY, MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, DARKBROWN,
        GRAY, RED, GOLD, LIME, BLUE, VIOLET, BROWN, LIGHTGRAY, PINK, YELLOW,
        GREEN, SKYBLUE, PURPLE, BEIGE };

    srand(time(NULL));
    int randomIndexC = rand() % 21;
    Color randomColor;
    randomColor = colors[randomIndexC];

    float angularVelocity[14] = { 0.02, 0.05, 0.10, 0.12, 0.14, 0.15, 0.17, 0.18, 0.20, 0.21, 0.23, 0.25, 0.27, 0.31 };
    srand(time(NULL));
    int randomIndexV = rand() % 14;
    float randomVelocity;
    randomVelocity = angularVelocity[randomIndexV];

    float radii[11] = { 7.0, 9.0, 10.0, 12.0, 15.0, 17.0, 18.0, 20.0, 21.0, 23.0, 25.0 };
    srand(time(NULL));
    int randomIndexR = rand() % 11;
    float randomRadius;
    randomRadius = radii[randomIndexR];

    float lineArr[7] = { 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0 };
    srand(time(NULL));
    int randomIndexL = rand() % 7;
    float randomLine;
    randomLine = lineArr[randomIndexL];
    //----------------------------------------------------------------------------------------
    float x0, y0, theta, posX, posY;
    x0 = 600.0;
    y0 = 400.0;
    theta = 0.0;

    posX = 0;
    posY = 0;

    Circle circles;
    circles.color = randomColor;
    circles.radius = randomRadius;
    circles.w = randomVelocity;
    circles.positionX = posX;
    circles.positionY = posY;
    Circle circleArr[MAX_CIRCLES];
    for (int i = 0; i < 100; i++) {
        circleArr[i] = circles;
    }
    //----------------------------------------------------------------------------------------

    while (!WindowShouldClose()) {
        posX = x0 + randomLine * cos(theta);
        posY = y0 + randomLine * sin(theta);
        theta += randomVelocity;

        posX += GetFrameTime() * 100;
        posY += GetFrameTime() * 100;

        //----------------------------------------------------------------------------------
        // Button Update--------------------------------------------------------------------

        mousePoint = GetMousePosition();
        btnAction = false;

        if (CheckCollisionPointRec(mousePoint, btnBounds)) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
            else btnState = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
        }
        else btnState = 0;

        sourceRec.y = btnState * frameHeight;
        //-------------------------------------------------------------------------------------
        // GIF Update (USELESS EFFORT)

        frameCounter++;
        if (frameCounter >= frameDelay)
        {
            currentAnimFrame++;
            if (currentAnimFrame >= animFrames) currentAnimFrame = 0;

            nextFrameDataOffset = imGojo.width * imGojo.height * 4 * currentAnimFrame;

            UpdateTexture(texGojo, ((unsigned char*)imGojo.data) + nextFrameDataOffset);

            frameCounter = 0;
        }
        //--------------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTextureRec(button, sourceRec, (Vector2) { btnBounds.x, btnBounds.y }, WHITE);
        DrawCircle(screenWidth / 2.0, screenHeight / 2.0, 5, DARKGRAY);
        DrawCircleLines(screenWidth / 2.0, screenHeight / 2.0, 5, BLACK);

        if (btnAction) {
            addCircles = true;
            buttonClicks++;
            PlaySound(fxButton);
        }
        if (addCircles) {
            DrawLine(screenWidth / 2.0, screenHeight / 2.0, posX, posY, BLACK);
            DrawCircle(posX, posY, randomRadius, randomColor);
            DrawCircle(posX, posY, 2, BLACK);
            DrawCircleLines(posX, posY, randomRadius, DARKGRAY);
            DrawText(TextFormat("VELOCITY= %f", randomVelocity), screenWidth / 2.0 - 59, 15, 16, GRAY);
            if (randomVelocity > 0.20) {
                DrawTexture(texGojo, GetScreenWidth() / 2 - texGojo.width / 2, 500, RAYWHITE);
            }
        }
        if (buttonClicks == 2) {
            DrawTexture(bob, screenWidth / 2 - bob.width / 2, screenHeight / 2 - bob.height / 2, RAYWHITE);
        }
        if (buttonClicks == 4) {
            DrawTexture(sisyphus, screenWidth / 2 - sisyphus.width / 2, screenHeight / 2 - sisyphus.height / 2, RAYWHITE);
        }
        if (buttonClicks == 6) {
            DrawTexture(bleh, screenWidth / 2 - bleh.width / 2, screenHeight / 2 - bleh.height / 2, RAYWHITE);
        }
        if (buttonClicks == 8) {
            DrawTexture(sadant, screenWidth / 2 - sadant.width / 2, screenHeight / 2 - sadant.height / 2, RAYWHITE);
        }
        if (buttonClicks == 10) {
            DrawTexture(burber, screenWidth / 2 - burber.width / 2, screenHeight / 2 - burber.height / 2, RAYWHITE);
        }
        if (buttonClicks == 12) {
            DrawTexture(lmao, screenWidth / 2 - lmao.width / 2, screenHeight / 2 - lmao.height / 2, RAYWHITE);
        }
        if (buttonClicks == 14) {
            DrawTexture(eepy, screenWidth / 2 - eepy.width / 2, screenHeight / 2 - eepy.height / 2, RAYWHITE);
        }
        if (buttonClicks == 15) {
            DrawTexture(buried, screenWidth / 2 - buried.width / 2, screenHeight / 2 - buried.height / 2, RAYWHITE);
        }
        if (buttonClicks == 17) {
            DrawTexture(sukuna, screenWidth / 2 - sukuna.width / 2, screenHeight / 2 - sukuna.height / 2, RAYWHITE);
        }
        if (buttonClicks == 18) {
            DrawTexture(geto, screenWidth / 2 - geto.width / 2, screenHeight / 2 - geto.height / 2, RAYWHITE);
        }
        
        EndDrawing();

    }
    UnloadTexture(sadant);
    UnloadTexture(buried);
    UnloadTexture(lmao);
    UnloadTexture(eepy);
    UnloadTexture(sisyphus);
    UnloadTexture(bob);
    UnloadTexture(burber);
    UnloadTexture(bleh);
    UnloadTexture(sukuna);
    UnloadTexture(geto);


    CloseWindow();

    return 0;
}