#ifndef sge_box2dscene_h
#define sge_box2dscene_h

#include "../Scene.hpp"
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>

class Box2DScene : public Scene
{
protected:
	b2World world;
	
public:
	explicit Box2DScene(const b2Vec2& gravity);
	explicit Box2DScene(const b2World& world);
};

#endif
