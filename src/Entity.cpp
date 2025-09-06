#include "Entity.h"

Entity::~Entity() {
    
}
void Entity::draw(sf::RenderWindow& window) {
    if (shape) {
        window.draw(*shape);
    }
}
