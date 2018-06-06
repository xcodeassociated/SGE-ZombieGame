#include "sgl_physics_component.hpp"

SGL::PhysicsComponent::PhysicsComponent(b2Body * body)
{
	this->setBody(body);
}

void SGL::PhysicsComponent::setBody(b2Body* b2Body)
{
	this->body = b2Body;
	this->body->SetTransform(b2Vec2(this->X, this->Y), this->body->GetAngle());
	this->body->SetUserData(this);
}

b2Body* SGL::PhysicsComponent::getBody()
{
	return this->body;
}

const b2Body* SGL::PhysicsComponent::getBody() const
{
	return this->body;
}

b2Fixture* SGL::PhysicsComponent::addFixture(const b2FixtureDef& fixtureDef)
{
	b2Fixture* fixture = this->body->CreateFixture(&fixtureDef);
	fixture->SetUserData(this);
	return fixture;
}

b2Fixture* SGL::PhysicsComponent::addFixture(const b2Shape& shape)
{
	b2Fixture* fixture = this->body->CreateFixture(&shape, 0);
	fixture->SetUserData(this);
	return fixture;
}
