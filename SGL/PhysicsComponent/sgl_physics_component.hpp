#ifndef sge_physics_component_hpp
#define sge_physics_component_hpp

#include "../Box2D/Dynamics/b2Body.h"
#include "../Box2D/Dynamics/b2Fixture.h"

namespace SGL
{
    class PhysicsComponent
    {
    protected:
		b2Body* body = nullptr;

    public:
        PhysicsComponent(b2Body* body);

	    void setBody(b2Body* b2Body, const b2Vec2& position);

	    b2Body* getBody();
		const b2Body* getBody() const;

	    b2Fixture* addFixture(const b2FixtureDef& fixtureDef);
	    b2Fixture* addFixture(const b2Shape& shape);
    };
    
}

#endif /* sge_physics_component_hpp */
