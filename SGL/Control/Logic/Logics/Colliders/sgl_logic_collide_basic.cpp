#include "sgl_logic_collide_basic.hpp"
#include "Shape/sge_shape.hpp"
#include "Shape/sge_shape_circle.hpp"
#include "Shape/sge_shape_rectangle.hpp"

SGL::Logics::BasicCollider::BasicCollider(SGL::Position* positionA, SGL::Shape* shapeA,
	SGL::Position* positionB, SGL::Shape* shapeB, const collisionFunc& _onCollision)
		: Collide(LogicPriority::Highest), onCollision(_onCollision), 
		positionA(positionA), shapeA(shapeA), positionB(positionB), shapeB(shapeB)
{
}

std::optional<SGL::Action> SGL::Logics::BasicCollider::performLogic()
{

	Shape* selfShape = this->shapeA;
	Shape* oponentShape = this->shapeB;

	bool collision = false;

	if (selfShape->getType() == oponentShape->getType())
		collision = this->collideWithSameShape(this->positionA, this->shapeA, this->positionB, this->shapeB);
	else
		collision = this->collideWithDifferentShape(this->positionA, this->shapeA, this->positionB, this->shapeB);

	if (collision)
	{
		return {this->onCollision(this->positionA, this->shapeA, this->positionB, this->shapeB)};
	}

	return {};
}
