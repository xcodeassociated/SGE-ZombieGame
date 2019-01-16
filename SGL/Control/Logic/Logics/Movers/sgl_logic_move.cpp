#include "sgl_logic_move.hpp"
#include "../../../Action/Actions/sgl_action_move.hpp"
#include "IO/KeyboardState/sge_keyboard_state.hpp"
#include "Utils/Timing/sge_fps_limiter.hpp"

#include <glm/glm.hpp>
#include <utility>

SGL::Logics::SimpleMove::SimpleMove(Position && position, const float speed, const SGE::Key up, 
	const SGE::Key down, const SGE::Key left, const SGE::Key right)
        : Logic(LogicPriority::Highest), position(std::forward<Position>(position)), 
			speed(speed), up(up), down(down), left(left), right(right)
{
}

std::optional<SGL::Action> SGL::Logics::SimpleMove::performLogic()
{
	using namespace SGE;

	glm::vec2 move = {0,0};

	if (isPressed(this->up)) move.y += this->speed;
	if (isPressed(this->down)) move.y -= this->speed;
	if (isPressed(this->right)) move.x += this->speed;
	if (isPressed(this->left)) move.x -= this->speed;

	if (glm::vec2{ 0,0 } != move)
	{
		move *= delta_time;
		return {SGL::ACTION::Move(std::forward<Position>(position), move.x, move.y, 0)};
	}
}
