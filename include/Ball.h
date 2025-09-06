#pragma once
#include "Entity.h"

class Ball : public Entity {
public:
    Ball(b2WorldId world, float radiusPx, sf::Vector2f startPosPx, sf::Vector2f velocityPx);
    void update() override;
protected:
};
