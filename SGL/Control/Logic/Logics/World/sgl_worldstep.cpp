#include "Utils/Timing/sge_fps_limiter.hpp"
#include "sgl_worldstep.hpp"

SGL::WorldStep::WorldStep(b2World* w) noexcept : Logic(LogicPriority::Highest), world(w)
{
}

SGL::WorldStep::WorldStep(b2World* w, int v, int p) noexcept
	: Logic(LogicPriority::Highest), world(w), vel(v), pos(p)
{
}

std::optional<SGL::Action> SGL::WorldStep::performLogic()
{
	this->world->Step(SGE::delta_time, this->vel, this->pos);
	return {};
}

int SGL::WorldStep::getVelocityIterations() const
{
	return this->vel;
}

int SGL::WorldStep::getPositionIterations() const
{
	return this->pos;
}

void SGL::WorldStep::setVelocityIterations(int iter)
{
	this->vel = iter;
}

void SGL::WorldStep::setPositionIterations(int iter)
{
	this->pos = iter;
}
