#include "sgl_logic.hpp"

SGL::Logic::~Logic() {}

SGL::Logic::Logic(Priority _p): priority(_p)
{
}

void SGL::Logic::sendAction(Action* action) const
{
	action_handler->performSingleAction(action, this->priority);
}

SGL::Logic::Priority SGE::Logic::getPriority() const
{
	return this->priority;
}

void SGL::Logic::setOn(bool e)
{
	this->isOn = e;
}

bool SGL::Logic::getOn()
{
	return this->isOn;
}

void SGL::Logic::toggleOn()
{
	this->isOn = !this->isOn;
}
