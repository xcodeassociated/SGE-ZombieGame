#include "sgl_logic_collide.hpp"
#include <Action/Actions/sgl_action_move.hpp>
#include <Shape/sge_shape.hpp>
#include <Shape/sge_shape_circle.hpp>
#include <Shape/sge_shape_rectangle.hpp>
#include <glm/geometric.hpp>

SGL::Action* SGL::Logics::Collide::RectangleCollisionVec(Position* stillPosition, Shape* stillShape, 
	Position* toMove, Shape* toMoveShape)
{
	float vx = toMove->getX() - stillPosition->getX();
	float vy = toMove->getY() - stillPosition->getY();

	float penx = (reinterpret_cast<Rectangle*>(toMoveShape)->getWidth()
		+ reinterpret_cast<Rectangle*>(stillShape)->getWidth()) * 0.5f - std::abs(vx);
	float peny = (reinterpret_cast<Rectangle*>(toMoveShape)->getHeight() 
		+ reinterpret_cast<Rectangle*>(stillShape)->getHeight()) * 0.5f - std::abs(vy);
	
	if (penx < peny)
		return new ACTION::Move(toMove, (vx > 0 ? penx : -penx), 0, true);
	else
		return new ACTION::Move(toMove, 0, (vy > 0 ? peny : -peny), true);
}

SGL::Action* SGL::Logics::Collide::CircleCollisionVec(Position* stillPosition, Shape* stillShape, 
	Position* toMove, Shape* toMoveShape)
{
	glm::vec2 pen = toMove->getPosition() - stillPosition->getPosition();
	float dist = reinterpret_cast<Circle*>(toMoveShape)->getRadius() 
		+ reinterpret_cast<Circle*>(stillShape)->getRadius();
	float l = glm::length(pen);
	pen *= ((dist - l) / l);
	return new ACTION::Move(toMove, pen.x, pen.y, true);
}

SGL::Action* SGL::Logics::Collide::CircleToRectCollisionVec(Position* stillPosition, Shape* stillShape,
	Position* toMove, Shape* toMoveShape)
{
	glm::vec2 halfs(reinterpret_cast<Rectangle*>(stillShape)->getWidth() * 0.5f,
		reinterpret_cast<Rectangle*>(stillShape)->getHeight() * 0.5f);
	glm::vec2 difference = toMove->getPosition() - stillPosition->getPosition();
	glm::vec2 clamps = glm::clamp(difference, -halfs, halfs);
	halfs = stillPosition->getPosition() + clamps;
	difference = toMove->getPosition() - halfs;
	const float l = glm::length(difference);
	difference *= ((reinterpret_cast<Circle*>(toMoveShape)->getRadius() - l) / l);
	return new ACTION::Move(toMove, difference.x, difference.y, true);
}

bool SGL::Logics::Collide::collideWithSameShape(Position* selfPosition, Shape* selfShape,
	Position* oponentPosition, Shape* oponentShape)
{
	ShapeType commonShape = selfShape->getType();

	switch (commonShape)
	{
	case ShapeType::Circle:
		{
			Circle* selfCircle = reinterpret_cast<Circle*>(selfShape);
			Circle* oponCircle = reinterpret_cast<Circle*>(oponentShape);
			glm::vec2 selfPos = selfPosition->getPosition();
			glm::vec2 oponPos = oponentPosition->getPosition();
			if (glm::length(selfPos - oponPos) < (selfCircle->getRadius() + oponCircle->getRadius()))
			{
				return true;
			}
		}
		break;

	case ShapeType::Rectangle:
		{
			Rectangle* selfRect = reinterpret_cast<Rectangle*>(selfShape);
			Rectangle* oponRect = reinterpret_cast<Rectangle*>(oponentShape);
			return (std::abs(selfPosition->getX() - oponentPosition->getX()) * 2 < selfRect->getWidth() + oponRect->getWidth()
				&& std::abs(selfPosition->getY() - oponentPosition->getY()) * 2 < selfRect->getHeight() + oponRect->getHeight());
		}
		break;

	case ShapeType::None:
		{
		}
	}

	return false;;
}

bool SGL::Logics::Collide::collideWithDifferentShape(Position* selfPosition, Shape* selfShape,
	Position* oponentPosition, Shape* oponentShape)
{
	ShapeType selfShapeType = selfShape->getType();
	ShapeType oponentShapeType = oponentShape->getType();

	if (selfShapeType == ShapeType::None || oponentShapeType == ShapeType::None)
		return false;

	Circle* circle = nullptr;
	glm::vec2 circlePos;
	Rectangle* rect = nullptr;
	glm::vec2 rectPos;

	if ((selfShapeType == ShapeType::Circle && oponentShapeType == ShapeType::Rectangle) 
		|| (selfShapeType == ShapeType::Rectangle && oponentShapeType == ShapeType::Circle))
	{
		//Set up data for collision;
		if (selfShapeType == ShapeType::Circle)
		{
			circle = reinterpret_cast<Circle*>(selfShape);
			rect = reinterpret_cast<Rectangle*>(oponentShape);
			circlePos = selfPosition->getPosition();
			rectPos = oponentPosition->getPosition();
		}
		else
		{
			rect = reinterpret_cast<Rectangle*>(selfShape);
			circle = reinterpret_cast<Circle*>(oponentShape);
			rectPos = selfPosition->getPosition();
			circlePos = oponentPosition->getPosition();
		}

		//Quick AABB-AABB test;
		if (std::abs(circlePos.x - rectPos.x) < circle->getRadius() + rect->getWidth() *  0.5f
			&& std::abs(circlePos.y - rectPos.y) < circle->getRadius() + rect->getHeight() *  0.5f)
		{
			glm::vec2 halfs(rect->getWidth() * 0.5f, rect->getHeight() * 0.5f);
			glm::vec2 difference = circlePos - rectPos;
			glm::vec2 clamps = glm::clamp(difference, -halfs, halfs);
			halfs = rectPos + clamps;
			difference = circlePos - halfs;
			return glm::length(difference) < circle->getRadius();
		}
	}

	return false;
}

bool SGL::Logics::Collide::collideWithEdgesDifferentShape(Position* selfPosition, Shape* selfShape,
	Position* oponentPosition, Shape* oponentShape)
{
	ShapeType selfShapeType = selfShape->getType();
	ShapeType oponentShapeType = oponentShape->getType();

	if (selfShapeType == ShapeType::None || oponentShapeType == ShapeType::None)
		return false;

	Circle* circle = nullptr;
	glm::vec2 circlePos;
	Rectangle* rect = nullptr;
	glm::vec2 rectPos;

	if ((selfShapeType == ShapeType::Circle && oponentShapeType == ShapeType::Rectangle) 
		|| (selfShapeType == ShapeType::Rectangle && oponentShapeType == ShapeType::Circle))
	{
		//Set up data for collision;
		if (selfShapeType == ShapeType::Circle)
		{
			circle = reinterpret_cast<Circle*>(selfShape);
			rect = reinterpret_cast<Rectangle*>(oponentShape);
			circlePos = selfPosition->getPosition();
			rectPos = oponentPosition->getPosition();
		}
		else
		{
			rect = reinterpret_cast<Rectangle*>(selfShape);
			circle = reinterpret_cast<Circle*>(oponentShape);
			rectPos = selfPosition->getPosition();
			circlePos = oponentPosition->getPosition();
		}
		//Quick AABB-AABB test;
		if (std::abs(circlePos.x - rectPos.x) <= circle->getRadius() + rect->getWidth() * 0.5
			&& std::abs(circlePos.y - rectPos.y) <= circle->getRadius() + rect->getHeight() * 0.5)
		{
			glm::vec2 halfs(rect->getWidth() * 0.5f, rect->getHeight() * 0.5f);
			glm::vec2 difference = circlePos - rectPos;
			glm::vec2 clamps = glm::clamp(difference, -halfs, halfs);
			halfs = rectPos + clamps;
			difference = halfs - circlePos;
			return glm::length(difference) <= circle->getRadius();
		}
	}
	return false;
}

SGL::Logics::Collide::Collide(const LogicPriority& logicPriority) : Logic(logicPriority)
{
}
