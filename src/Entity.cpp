#include "Entity.h"

Entity::~Entity() {
    delete shape; // 防止内存泄漏
}
void Entity::draw(sf::RenderWindow& window) {
    if (shape) {
        window.draw(*shape);
    }
}
