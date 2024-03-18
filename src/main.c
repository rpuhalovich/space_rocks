#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

const i16 windowWidth = 1280;
const i16 windowHeight = 720;
const i16 targetFps = 60;

typedef struct {
    i32 time;
    i32 lastTime;
    struct {
        Vector2 position;
        Vector2* points;
        i32 numpoints;
        i32 speed;
        f32 size;
        f32 rotation;
    } player;
} State;

State state = {0};

void init() {
    InitWindow(windowWidth, windowHeight, "space_rocks");
    SetTargetFPS(targetFps);

    // player
    {
        state.player.size = 50.f;
        state.player.speed = 300.f;
        Vector2 v = {(float)windowWidth / 2 - state.player.size / 2,
                     (float)windowHeight / 2 - state.player.size / 2};
        state.player.position = v;

        i32 numpoints = 8; // must be even
        state.player.numpoints = numpoints;
        Vector2 points[8] = {
            {0, 0}, {1, 0}, {1, 0}, {1, 1}, {0, 1}, {1, 1}, {0, 0}, {0, 1},
        };
        for (int i = 0; i < state.player.numpoints; i++) {
            points[i].x *= state.player.size;
            points[i].y *= state.player.size;
        }
        state.player.points = (Vector2*)malloc(sizeof(points));
        memset(state.player.points, 0, sizeof(points));
        memcpy(state.player.points, points, sizeof(points));
    }
}

void cleanup() {
    free(state.player.points);
}

void update() {
    ClearBackground(BLACK);

    // player
    {
        f32 m = state.player.speed * GetFrameTime();
        if (IsKeyDown(KEY_DOWN))
            state.player.position.y += m;
        if (IsKeyDown(KEY_UP))
            state.player.position.y -= m;
        if (IsKeyDown(KEY_LEFT))
            state.player.position.x -= m;
        if (IsKeyDown(KEY_RIGHT))
            state.player.position.x += m;

        for (int i = 0; i < state.player.numpoints; i++) {
            state.player.points[i] =
                Vector2SubtractValue(state.player.points[i], state.player.size / 2);
            state.player.points[i] = Vector2Rotate(state.player.points[i], 1.f * GetFrameTime());
            state.player.points[i] = Vector2AddValue(state.player.points[i], state.player.size / 2);
        }

        for (int i = 0; i < state.player.numpoints; i += 2) {
            Vector2 v1 = Vector2Add(state.player.points[i], state.player.position);
            Vector2 v2 = Vector2Add(state.player.points[i + 1], state.player.position);
            DrawLineEx(v1, v2, 3.f, WHITE);
        }
    }

    // draw time
    char time[100];
    snprintf(time, sizeof(time), "Time: %d", state.time);
    DrawText(time, 20, 20, 20, WHITE);

    // draw white dot
    float w = 3.f;
    Vector2 m = {(float)windowWidth / 2 - w / 2, (float)windowHeight / 2 - w / 2};
    DrawCircleV(m, w, WHITE);

    // update state
    if (GetTime() >= state.lastTime + 1) {
        state.time += 1;
        state.lastTime = GetTime();
    }
}

int main(void) {
    init();
    while (!WindowShouldClose()) {
        BeginDrawing();
        update();
        EndDrawing();
    }
    CloseWindow();
    cleanup();
    fscanf(stdin, "c");
    return 0;
}
