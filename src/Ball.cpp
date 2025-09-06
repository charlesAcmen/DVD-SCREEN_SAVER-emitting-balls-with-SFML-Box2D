#include "Ball.h"
#include "Game.h"
#include <memory>
using namespace std;
Ball::Ball(b2WorldId world, float radiusPx, sf::Vector2f startPosPx,sf::Vector2f velocityPx = sf::Vector2f(0.0f,0.0f)) {
    // --- Box2D 部分 ---
    b2BodyDef bd = b2DefaultBodyDef();
    bd.type = b2_dynamicBody;
    // bd.isBullet = true; // 高速物体防止穿透
    
    bd.position = Game::sfVectorToB2Vec2(startPosPx);
    bodyId = b2CreateBody(world, &bd);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.0f;
    shapeDef.material.restitution = 1.0f;

    b2Circle cd = {0};
    cd.center = {0.0f, 0.0f};
    cd.radius = Game::sfLengthToB2Length(radiusPx);
    b2CreateCircleShape(bodyId, &shapeDef, &cd);

    // 初速度
    b2Vec2 vel = Game::sfVectorToB2Vec2(velocityPx);
    // printf("Initial Velocity: (%.2f, %.2f) in pixels\n", vel.x, vel.y);
    b2Body_SetLinearVelocity(bodyId, vel);

    // --- SFML 部分 ---
    //60:point count for smooth circle
    shape = make_unique<sf::CircleShape>(radiusPx, 60);
    shape->setOrigin(radiusPx, radiusPx);
    shape->setFillColor(sf::Color::Yellow);


}

void Ball::update() {
    b2Vec2 pos = b2Body_GetPosition(bodyId);
    b2Rot rot = b2Body_GetRotation(bodyId);

    shape->setPosition(Game::b2Vec2ToSfVector(pos));
    shape->setRotation(Game::b2AngleToSfAngle(b2Rot_GetAngle(rot)));
}
