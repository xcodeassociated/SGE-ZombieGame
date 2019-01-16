#include "sgl_logic.hpp"

SGL::Logic::Logic(Priority priority) : priority(priority)
{
}

SGL::Logic::Priority SGL::Logic::getPriority() const
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
