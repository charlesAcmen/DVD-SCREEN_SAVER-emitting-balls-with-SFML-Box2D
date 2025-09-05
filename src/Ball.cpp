#include "Ball.h"
#include "Game.h"
Ball::Ball(b2WorldId world, float radiusPx, sf::Vector2f startPosPx) {
    // --- Box2D 部分 ---
    b2BodyDef bd = b2DefaultBodyDef();
    bd.type = b2_dynamicBody;
    bd.isBullet = true; // 高速物体防止穿透
    bd.position = Game::sfVectorToB2Vec2(startPosPx);
    bodyId = b2CreateBody(world, &bd);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.0f;
    shapeDef.material.restitution = 0.8f;

    b2Circle cd;
    cd.radius = radiusPx * Game::INV_PPM;
    b2CreateCircleShape(bodyId, &shapeDef, &cd);

    // 初速度
    b2Body_SetLinearVelocity(bodyId, { 3.0f, 5.0f });

    // --- SFML 部分 ---
    //60:point count for smooth circle
    sf::CircleShape* circle = new sf::CircleShape(radiusPx, 60);
    circle->setOrigin(radiusPx, radiusPx);
    circle->setFillColor(sf::Color::Yellow);
    Entity::shape = circle;
}

void Ball::update() {
    b2Vec2 pos = b2Body_GetPosition(bodyId);
    b2Rot rot = b2Body_GetRotation(bodyId);

    Entity::shape->setPosition(Game::b2Vec2ToSfVector(pos));
    Entity::shape->setRotation(-b2Rot_GetAngle(rot) * 180.0f / B2_PI);
}
