#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <vector>
#include <memory>
#include "Entity.h"
using namespace std;
class Game {
public:
    static const int WINDOW_W = 1280;
    static const int WINDOW_H = 720;
    static constexpr float PPM = 80.0f;
    static constexpr float INV_PPM = 1.0f / PPM;

    static const int frameRate = 60;
    static constexpr float TIME_STEP = 1.0f / frameRate;
    static const int SUBSTEP_COUNT = 4;

    sf::RenderWindow window;
    // --- 实体 ---
    vector<unique_ptr<Entity>> entities;


    // 坐标转换：Box2D -> SFML
    static inline sf::Vector2f b2Vec2ToSfVector(const b2Vec2& vec) {
        return sf::Vector2f(vec.x * PPM, WINDOW_H - (vec.y * PPM));
    }

    // 坐标转换：SFML -> Box2D
    static inline b2Vec2 sfVectorToB2Vec2(const sf::Vector2f& vec) {
        return b2Vec2{vec.x * INV_PPM, (WINDOW_H - vec.y) * INV_PPM};
    }

    static inline float sfAngleToB2Angle(float angle) {
        return -angle * B2_PI / 180.0f;
    }

    static inline float b2AngleToSfAngle(float angle) {
        return -angle * 180.0f / B2_PI;
    }

    static inline float sfLengthToB2Length(float length) {
        return length * INV_PPM;
    }

    static inline float b2LengthToSfLength(float length) {
        return length * PPM;
    }

    Game() : window(sf::VideoMode(WINDOW_W, WINDOW_H), "SFML + Box2D") {
        window.setFramerateLimit(frameRate);
        entities = vector<unique_ptr<Entity>>();
    }

    void run();
};
