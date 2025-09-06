#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>
using namespace std;
class Entity {
public:
    virtual ~Entity();
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window);

protected:
    b2BodyId bodyId;     // 物理 body
    //unique ptr不可拷贝，只能移动
    unique_ptr<sf::Shape> shape;    // 渲染形状
};