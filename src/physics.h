#pragma once
#include <vector>
#include <cmath>

struct Vec2 {
    float x, y;
    Vec2(float x = 0, float y = 0) : x(x), y(y) {}
    Vec2 operator+(const Vec2& o) const { return {x + o.x, y + o.y}; }
    Vec2 operator-(const Vec2& o) const { return {x - o.x, y - o.y}; }
    Vec2 operator*(float s) const { return {x * s, y * s}; }
    float length() const { return std::sqrt(x * x + y * y); }
};

struct Particle {
    Vec2 pos;
    Vec2 prev_pos;
    float inv_mass = 1.0f;
    float radius = 0.5f;
};

struct Constraint {
    int p1, p2;
    float rest_length;
    bool broken = false;
};

class World {
public:
    std::vector<Particle> particles;
    std::vector<Constraint> constraints;
    Vec2 gravity = {0.0f, 9.8f}; 

    void addParticle(float x, float y) {
        particles.push_back({Vec2(x, y), Vec2(x, y), 1.0f, 0.5f});
    }

    void addConstraint(int i1, int i2) {
        float dx = particles[i1].pos.x - particles[i2].pos.x;
        float dy = particles[i1].pos.y - particles[i2].pos.y;
        float len = std::sqrt(dx * dx + dy * dy);
        constraints.push_back({i1, i2, len, false});
    }

    void step(float dt) {
        // 1. 积分
        for (auto& p : particles) {
            if (p.inv_mass == 0) continue;
            Vec2 vel = p.pos - p.prev_pos;
            p.prev_pos = p.pos;
            p.pos = p.pos + vel + gravity * (dt * dt);
        }

        // 2. 约束求解和断裂
        for (int iter = 0; iter < 10; ++iter) {
            for (auto& c : constraints) {
                if (c.broken) continue;
                Particle& a = particles[c.p1];
                Particle& b = particles[c.p2];
                Vec2 delta = b.pos - a.pos;
                float dist = delta.length();
                if (dist == 0) continue;

                if (dist > c.rest_length * 1.5f) { // 断裂阈值
                    c.broken = true;
                    continue;
                }

                float diff = (dist - c.rest_length) / dist;
                Vec2 correction = delta * (0.5f * diff);
                if (a.inv_mass > 0) a.pos = a.pos + correction;
                if (b.inv_mass > 0) b.pos = b.pos - correction;
            }
        }

        // 3. 地面碰撞
        for (auto& p : particles) {
            if (p.pos.y + p.radius > 10.0f) {
                p.pos.y = 10.0f - p.radius;
                Vec2 vel = p.pos - p.prev_pos;
                p.prev_pos = p.pos + Vec2(vel.x * 0.5f, 0); 
            }
        }
    }
};
