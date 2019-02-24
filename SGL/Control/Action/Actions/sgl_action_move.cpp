#include "sgl_action_move.hpp"

#include <glm/detail/type_vec2.hpp>
#include <cassert>
#include <utility>

SGL::ACTION::Move::Move(Position* position, const float _x, const float _y, const bool active) 
	: SGL::Action(active), position(position), destX(_x), destY(_y)
{
}

void SGL::ACTION::Move::perform()
{
	position->x += this->destX;
	position->y += this->destY;
}
