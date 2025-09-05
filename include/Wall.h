#pragma once
#include "Entity.h"

class Wall : public Entity {
public:
    Wall(b2WorldId world, sf::Vector2f sizePx, sf::Vector2f centerPx);
    void update() override;
};
