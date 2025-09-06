#include "Game.h"
#include "Ball.h"
#include "Wall.h"
#include <memory>
#include <random>
using namespace std;

mt19937 rng{random_device{}()};
//sfml uses degrees and pixels
//box2d uses radians and meters
uniform_real_distribution<float> angleDist(0.0f, 2.f * B2_PI);
uniform_real_distribution<float> speedDist(1.0f, 10.0f);
void Game::run(){
    // --- 创建物理世界 ---
    b2WorldDef wdef = b2DefaultWorldDef();
    wdef.gravity = {0.0f, 0.0f};
    b2WorldId world = b2CreateWorld(&wdef);


    // 添加墙
    entities.emplace_back(make_unique<Wall>(world, sf::Vector2f{WINDOW_W, 10.0f}, sf::Vector2f{WINDOW_W / 2.0f, WINDOW_H - 5.0f}));
    entities.emplace_back(make_unique<Wall>(world, sf::Vector2f{WINDOW_W, 10.0f}, sf::Vector2f{WINDOW_W / 2.0f, 5.0f}));
    entities.emplace_back(make_unique<Wall>(world, sf::Vector2f{10.0f, WINDOW_H}, sf::Vector2f{5.0f, WINDOW_H / 2.0f}));
    entities.emplace_back(make_unique<Wall>(world, sf::Vector2f{10.0f, WINDOW_H}, sf::Vector2f{WINDOW_W - 5.0f, WINDOW_H / 2.0f}));

    sf::Clock clock;
    sf::Time elapsedSinceShot = sf::Time::Zero;
    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev))
            if (ev.type == sf::Event::Closed) window.close();

        sf::Time dt = clock.restart();
        elapsedSinceShot += dt;
        if (elapsedSinceShot.asSeconds() > 0.2f) {
            elapsedSinceShot = sf::Time::Zero;

            float angle = angleDist(rng);
            float speed = speedDist(rng);
            // printf("Angle: %.2f in radians, Speed: %.2f m/s\n", angle, speed);
            sf::Vector2f velocity(Game::b2Vec2ToSfVector(b2Vec2{cos(angle) * speed, sin(angle) * speed}));

            // 发射点在屏幕中心
            sf::Vector2f pos(WINDOW_W / 2.f, WINDOW_H / 2.f);

            // TODO: 在这里检查重叠（可用 b2TestOverlap）
            entities.emplace_back(make_unique<Ball>(world, 15.0f, pos, velocity));
        }

        // 更新物理
        b2World_Step(world, TIME_STEP, SUBSTEP_COUNT);

        

        // 更新实体
        for(auto& entity : entities) {
            entity->update();
        }
        //Grey
        window.clear(sf::Color(50, 50, 50));
        for (const auto& entity : entities) {
            entity->draw(window);
        }
        
        window.display();
    }

    b2DestroyWorld(world);
}