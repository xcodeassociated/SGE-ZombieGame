#include "sgl_action_move.hpp"

#include <glm/detail/type_vec2.hpp>
#include <cassert>
#include <utility>

SGL::ACTION::Move::Move(Position && position, float _x, float _y, bool active) 
	: SGL::Action(active), position(std::forward<Position>(position)), destX(_x), destY(_y)
{
}

void SGL::ACTION::Move::perform()
{
	position.x += this->destX;
	position.y += this->destY;
}
