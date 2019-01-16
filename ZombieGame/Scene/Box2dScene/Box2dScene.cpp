#include "Box2dScene.hpp"

Box2DScene::Box2DScene(const b2Vec2& gravity) : world(gravity)
{
}

Box2DScene::Box2DScene(const b2World& world) : world(world)
{
}
