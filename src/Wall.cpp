#include "Wall.h"
#include "Game.h"
Wall::Wall(b2WorldId world, sf::Vector2f sizePx, sf::Vector2f centerPx) {
    // --- Box2D 部分 ---
    b2BodyDef bd = b2DefaultBodyDef();
    bd.type = b2_staticBody;
    bd.position = Game::sfVectorToB2Vec2(centerPx);
    bodyId = b2CreateBody(world, &bd);

    b2Polygon box = b2MakeBox(sizePx.x * 0.5f * Game::INV_PPM, sizePx.y * 0.5f * Game::INV_PPM);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.material.friction = 0.0f;
    shapeDef.material.restitution = 1.0f;
    b2CreatePolygonShape(bodyId, &shapeDef, &box);

    // --- SFML 部分 ---
    sf::RectangleShape* rect = new sf::RectangleShape(sizePx);
    rect->setOrigin(sizePx.x / 2.0f, sizePx.y / 2.0f);
    rect->setFillColor(sf::Color(100, 100, 100));
    rect->setPosition(centerPx);
    Entity::shape = rect;
}

void Wall::update() {
    // 静态物体不用更新
}
