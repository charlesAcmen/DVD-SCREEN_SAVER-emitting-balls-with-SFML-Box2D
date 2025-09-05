#include "Game.h"
#include "Ball.h"
#include "Wall.h"
#include <vector>
#include <memory>
using namespace std;
void Game::run(){
    // --- 创建物理世界 ---
    b2WorldDef wdef = b2DefaultWorldDef();
    wdef.gravity = {0.0f, 0.0f};
    b2WorldId world = b2CreateWorld(&wdef);


    // --- 实体 ---
    vector<unique_ptr<Entity>> entities;
    
    // 添加球
    entities.emplace_back(make_unique<Ball>(world, 30.0f, sf::Vector2f{WINDOW_W / 4.0f, WINDOW_H / 2.0f}));

    // 添加墙
    entities.emplace_back(make_unique<Wall>(world, sf::Vector2f{WINDOW_W, 10.0f}, sf::Vector2f{WINDOW_W / 2.0f, WINDOW_H - 5.0f}));
    entities.emplace_back(make_unique<Wall>(world, sf::Vector2f{WINDOW_W, 10.0f}, sf::Vector2f{WINDOW_W / 2.0f, 5.0f}));
    entities.emplace_back(make_unique<Wall>(world, sf::Vector2f{10.0f, WINDOW_H}, sf::Vector2f{5.0f, WINDOW_H / 2.0f}));
    entities.emplace_back(make_unique<Wall>(world, sf::Vector2f{10.0f, WINDOW_H}, sf::Vector2f{WINDOW_W - 5.0f, WINDOW_H / 2.0f}));


    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev))
            if (ev.type == sf::Event::Closed) window.close();

        // 更新物理
        b2World_Step(world, TIME_STEP, SUBSTEP_COUNT);

        // 更新实体
        for(auto& entity : entities) {
            entity->update();
        }

        window.clear(sf::Color::Black);
        for (auto& entity : entities) {
            entity->draw(window);
        }
        
        window.display();
    }

    b2DestroyWorld(world);
}