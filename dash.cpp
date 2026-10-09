#include "raylib.h"

int main()
{

    const int windowWidth(512);
    const int windowHeight{380};

    InitWindow(windowWidth, windowHeight, "Dasher Game");

    const int gravity{1'200};

    // nebula variables
    Texture2D nebula = LoadTexture("texture/12_nebula_spritesheet.png");
    Rectangle nebulaRec{0.0, 0.0, nebula.width / 8, nebula.height = 8};
    Vector2 nebpos{windowWidth, windowHeight - nebulaRec.height};
    int nebFrame;
    const float nebUpdateTime{1.0 / 12.0};
    float nebRunningTime{};

    // nebula x velocity (pixel/sec)
    int nebVel = -200;

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = 0;
    scarfyPos.y = windowHeight - scarfyRec.height;

    int frame{};

    const float updateTime{1.0 / 9.0};
    float runningTime{};

    SetTargetFPS(60);

    int velocity{0};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};

    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX{};

    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX{};

    bool isInAir{};

    // jump velocity
    const int jumpVel{-600};

    while (!WindowShouldClose())
    {

        // delta time
        const float dT{GetFrameTime()};
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        bgX -= 30 * dT;
        if (bgX <= -background.width * 2)
        {
            bgX = 0.0;
        }

        mgX -= 50 * dT;
        if (mgX <= -midground.width * 2)
        {
            mgX = 0.0;
        }

        fgX -= 80 * dT;
        if (fgX <= -foreground.width * 2)
        {
            fgX = 0.0;
        }

        // draw backround
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);

        Vector2 bg2Pos{bgX + background.width * 2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        // draw midground
        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);

        Vector2 mg2Pos{mgX + midground.width * 2, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

        // draw foreground
        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);

        Vector2 fg2Pos{fgX + foreground.width * 2, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

        if (scarfyPos.y > windowHeight - scarfyRec.width)
        {
            // On ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // apply gravity rectangle in air
            velocity += gravity * dT;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // nebula position
        nebpos.x += nebVel * dT;

        // update y position
        scarfyPos.y += velocity * dT;

        // update scarfy
        if (!isInAir)
        {
            // update running time
            runningTime += dT;
            if (runningTime >= updateTime)
            {
                runningTime = 0.0;
                scarfyRec.x = frame * scarfyRec.width;
                frame++;

                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }

        // update nebula

        nebRunningTime = +dT;
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            nebulaRec.x = nebFrame * nebulaRec.width;
            nebFrame++;

            if (nebFrame > 8)
            {
                nebFrame = 0;
            }
        }

        // draw nebula
        DrawTextureRec(nebula, nebulaRec, nebpos, WHITE);

        // draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // End drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);

    CloseWindow();
}