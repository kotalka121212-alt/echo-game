#include <raylib.h>
#include <raymath.h>

#include "voxel/voxel.h"
#include <lua.hpp>


int main() {
    InitWindow(1280, 720, "Echo Engine — Free Flight");
    SetTargetFPS(60);


    Camera3D camera = { 0 };
    camera.position = Vector3{ 0.0f, 2.0f, 5.0f };
    camera.target   = Vector3{ 0.0f, 2.0f, 0.0f };
    camera.up       = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy     = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float moveSpeed = 10.0f;
    float mouseSensitivity = 0.003f;

    // Углы обзора (в градусах)
    float yaw = 180.0f;   // поворот влево-вправо
    float pitch = 0.0f;   // наклон вверх-вниз

    DisableCursor();

    Vector3 cubePos = { 0.0f, 1.0f, 0.0f };

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // --- Поворот камеры мышью ---
        Vector2 mouseDelta = GetMouseDelta();

        yaw   += mouseDelta.x * mouseSensitivity * 100.0f;
        pitch -= mouseDelta.y * mouseSensitivity * 100.0f;

        // Ограничиваем наклон, чтобы камера не переворачивалась
        if (pitch > 89.0f)  pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        // Пересчитываем направление камеры
        Vector3 forward;
        forward.x = cosf(DEG2RAD * yaw) * cosf(DEG2RAD * pitch);
        forward.y = sinf(DEG2RAD * pitch);
        forward.z = sinf(DEG2RAD * yaw) * cosf(DEG2RAD * pitch);
        forward = Vector3Normalize(forward);

        camera.target = Vector3Add(camera.position, forward);

        // --- Движение WASD ---
        Vector3 flatForward = Vector3Normalize(Vector3{ forward.x, 0.0f, forward.z });
        Vector3 flatRight = Vector3Normalize(Vector3CrossProduct(flatForward, Vector3{ 0.0f, 1.0f, 0.0f }));

        Vector3 move = { 0 };
        if (IsKeyDown(KEY_W)) move = Vector3Add(move, flatForward);
        if (IsKeyDown(KEY_S)) move = Vector3Subtract(move, flatForward);
        if (IsKeyDown(KEY_A)) move = Vector3Subtract(move, flatRight);
        if (IsKeyDown(KEY_D)) move = Vector3Add(move, flatRight);
        if (IsKeyDown(KEY_SPACE)) move.y += 1.0f;
        if (IsKeyDown(KEY_LEFT_SHIFT)) move.y -= 1.0f;

        if (Vector3Length(move) > 0.0f) {
            move = Vector3Normalize(move);
            move = Vector3Scale(move, moveSpeed * deltaTime);
            camera.position = Vector3Add(camera.position, move);
            camera.target = Vector3Add(camera.target, move);
        }

        // --- Отрисовка ---
        BeginDrawing();
        ClearBackground(BLUE_DARK);

        BeginMode3D(camera);

        DrawGrid(50, 1.0f);








            voxel::draw_rectangle(
                Vector3{ 0, 0, 0 }, // ниж лев
                Vector3{ 1, 0, 0 }, // верх лев
                Vector3{ 0, 1, 0 }, // ниж прав
                Vector3{ 1, 1, 0 }, // верх прав
                RAYWHITE
            );
 







        //DrawCube(Vector3{ 5.0f, 1.0f, -5.0f }, 2.0f, 2.0f, 2.0f, BLUE);
        //DrawCube(Vector3{ -5.0f, 1.0f, 5.0f }, 2.0f, 2.0f, 2.0f, GREEN);

        EndMode3D();

        DrawFPS(10, 40);

        EndDrawing();
    }

    EnableCursor();
    CloseWindow();
    return 0;
}






