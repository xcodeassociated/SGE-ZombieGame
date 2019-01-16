#include "sgl_action.hpp"

SGL::Action::Action() : active(false)
{
}

SGL::Action::Action(bool active) : active(active)
{
}

void SGL::Action::perform()
{
}

bool SGL::Action::isActive() const
{
	return this->active;
}
