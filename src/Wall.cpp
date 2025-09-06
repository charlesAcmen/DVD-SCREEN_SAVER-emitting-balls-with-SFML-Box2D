#include "Wall.h"
#include "Game.h"
#include <memory>
//作用域仅限当前翻译单元
using namespace std;
Wall::Wall(b2WorldId world, sf::Vector2f sizePx, sf::Vector2f centerPx) {
    // --- Box2D 部分 ---
    b2BodyDef bd = b2DefaultBodyDef();
    bd.type = b2_staticBody;
    bd.position = Game::sfVectorToB2Vec2(centerPx);
    bodyId = b2CreateBody(world, &bd);

    b2Polygon box = b2MakeBox(Game::sfLengthToB2Length(sizePx.x * 0.5f), Game::sfLengthToB2Length(sizePx.y * 0.5f));
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.material.friction = 0.0f;
    shapeDef.material.restitution = 1.0f;
    b2CreatePolygonShape(bodyId, &shapeDef, &box);

    // --- SFML 部分 ---
    Entity::shape = make_unique<sf::RectangleShape>(sizePx);
    Entity::shape->setOrigin(sizePx.x / 2.0f, sizePx.y / 2.0f);
    Entity::shape->setFillColor(sf::Color(100, 100, 100));
    Entity::shape->setPosition(centerPx);
}

void Wall::update() {
    // 静态物体不用更新
}