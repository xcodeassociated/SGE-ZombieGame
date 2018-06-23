#include "sgl_action.hpp"


SGL::Action::Action(bool active) : active(active)
{
}

bool SGL::Action::isActive() const
{
	return this->active;
}
