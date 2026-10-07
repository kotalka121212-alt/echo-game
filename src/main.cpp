#include <raylib.h>
#include <raymath.h>
#include <iostream>


#include "voxel/voxel.h"

#include "camera/camera.h"
#include "model/model.h"

int main() {
    InitWindow(1280, 720, "Echo — Lighting");
    SetTargetFPS(60);

    FlyCamera camera({0, 5, 10});

    // Шейдер
    Shader shader = LoadShader("../assets/shaders/lighting.vs", "../assets/shaders/lighting.fs");
    int lightPosLoc   = GetShaderLocation(shader, "lightPos");
    int viewPosLoc    = GetShaderLocation(shader, "viewPos");
    int lightColorLoc = GetShaderLocation(shader, "lightColor");
    int objectColorLoc = GetShaderLocation(shader, "objectColor");

    // Модель
    Model model = LoadModel("../Untitled.glb");
    // Навешиваем шейдер на все материалы модели
    for (int i = 0; i < model.materialCount; i++) {
        model.materials[i].shader = shader;
    }

    Vector3 lightPos = { 5.0f, 10.0f, 5.0f };
    Vector3 lightColor = { 1.0f, 1.0f, 1.0f };
    Vector3 objectColor = { 0.8f, 0.6f, 0.4f };

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        camera.update(dt);

        Vector3 viewPos = camera.getPosition();

        // Передаём данные в шейдер
        SetShaderValue(shader, lightPosLoc,   &lightPos,   SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, viewPosLoc,    &viewPos,    SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, lightColorLoc, &lightColor, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, objectColorLoc,&objectColor,SHADER_UNIFORM_VEC3);

        BeginDrawing();
        ClearBackground(BLUE_DARK);
        BeginMode3D(camera.get());
        
        DrawModel(model, {0, 0, 0}, 1.0f, WHITE);

        DrawGrid(50, 1.0f);



        
        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadShader(shader);
    UnloadModel(model);
    EnableCursor();
    CloseWindow();
    return 0;
}






