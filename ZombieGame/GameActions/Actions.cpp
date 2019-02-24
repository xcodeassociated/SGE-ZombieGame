#include "Actions.hpp"
#include <iostream>
#include <Camera2d/sge_camera2d.hpp>
#include "../Director/Director.hpp"
#include "../GameLogics/Logics.hpp"

GOTO::GOTO(SGE::Position* position) : Action(false), position(position)
{
}

void GOTO::perform() noexcept
{
	// default values...?
	this->position->x = 200;
	this->position->y = 200;
	//NOTE: we don't want this action to be active forever
}

PortalAction::PortalAction(): SGL::Action(false)
{
}

void PortalAction::perform()
{
	std::cout << "portal::main" << std::endl;
	//NOTE: we DON'T want this action to be active forever -- only when the logic condition form Portal is met
}


LogicSwitch::LogicSwitch(SGL::Logic* id) : SGL::Action(true), logic(id)
{
}

void LogicSwitch::perform()
{
	logic->toggleOn();
	//NOTE: we want this action to be active forever
}


MouseClickedAction::MouseClickedAction(SGE::MouseObject* mouseObject, SGE::Position* playerPosition) 
	: Action(true), mouseObject(mouseObject), player(player)
{
}

void MouseClickedAction::perform() noexcept
{
	glm::vec2 coords = this->mouseObject->getMouseCoords();
	glm::vec2 worldCoords = SGE::Game::getGame()->getCamera()->screenToWorld(coords);
	std::cout << "[Clicked] - x: " << worldCoords.x << ", y: " << worldCoords.y << '\n'; //No 
	std::cout << "[Player ] - x: " << this->player->getX() << ", y: " << this->player->getY() << std::endl;

	//NOTE: we want this action to be active forever
}

Load::Load(SGE::Scene* scene) : nextScene(scene)
{
}


void Load::perform()
{
	auto d = Director::getDirector();
	d->toNextScene(this->nextScene);
	this->active = false;
}
