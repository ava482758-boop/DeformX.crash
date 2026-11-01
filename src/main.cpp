#include "raylib.h"
#include "physics.h"

int main() {
    InitWindow(0, 0, "DeformX.crash");
    SetTargetFPS(60);

    World world;
    
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float scale = screenWidth / 20.0f; // 缩放适应屏幕

    // 1. 创建质点 (模拟你图里的橙色圆球)
    world.addParticle(-4, -4); // 0 左上
    world.addParticle( 4, -4); // 1 右上
    world.addParticle( 0, -2); // 2 中上
    world.addParticle( 4,  4); // 3 右下
    world.addParticle(-4,  4); // 4 左下
    world.addParticle( 0,  2); // 5 中下
    world.addParticle(-6,  0); // 6 极左
    world.addParticle( 6,  0); // 7 极右
    world.addParticle( 0,  0); // 8 正中心

    // 2. 创建连杆 (模拟你图里的黑色管子)
    world.addConstraint(0, 2); world.addConstraint(2, 1);
    world.addConstraint(6, 0); world.addConstraint(6, 4);
    world.addConstraint(4, 5); world.addConstraint(5, 3);
    world.addConstraint(1, 7); world.addConstraint(3, 7);
    
    world.addConstraint(0, 8); world.addConstraint(1, 8);
    world.addConstraint(3, 8); world.addConstraint(4, 8);
    world.addConstraint(2, 8); world.addConstraint(5, 8);
    world.addConstraint(6, 8); world.addConstraint(7, 8);
    world.addConstraint(0, 4); world.addConstraint(1, 3);

    while (!WindowShouldClose()) {
        world.step(1.0f / 60.0f);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 origin = { screenWidth / 2.0f, screenHeight / 4.0f };

        // 画连杆
        for (auto& c : world.constraints) {
            if (c.broken) continue;
            Particle& p1 = world.particles[c.p1];
            Particle& p2 = world.particles[c.p2];
            Vector2 v1 = { origin.x + p1.pos.x * scale, origin.y + p1.pos.y * scale };
            Vector2 v2 = { origin.x + p2.pos.x * scale, origin.y + p2.pos.y * scale };
            DrawLineEx(v1, v2, 5.0f, BLACK);
        }

        // 画质点
        for (auto& p : world.particles) {
            Vector2 v = { origin.x + p.pos.x * scale, origin.y + p.pos.y * scale };
            DrawCircleV(v, 15.0f, ORANGE);
        }

        // 画地面
        DrawRectangle(0, origin.y + 10.0f * scale, screenWidth, screenHeight, LIGHTGRAY);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}