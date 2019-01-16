#include "Scene.hpp"
#include "../Level/LevelParser/LevelParser.hpp"

#include <stdexcept>
#include <algorithm>

// Scene::LogicVector& Scene::getLogics()
// {
// 	return this->logics;
// }

// Scene::ActionVector& Scene::getActions()
// {
// 	return this->actions;
// }

// Scene::ObjectVector& Scene::getObjects()
// {
// 	return this->objects;
// }

void Scene::loadLevel(const char* path, std::map<char, std::string> levelMask)
{
	// LevelParser parser(path, levelMask);
	// this->level = parser.parse();
	// this->TextureLoaded = true;
}

Level& Scene::getLevel()
{
	// return this->level;
}

void Scene::addObject(SGL::Object* object)
{
	// this->objects.emplace_back(object);
}

void Scene::removeObject(SGL::Object* object)
{
	// auto it = std::find(this->objects.begin(), this->objects.end(), object);
	// if (it == this->objects.end())
	// 	throw std::runtime_error{"Object not found -- cannot be removed"};

	// this->objects.erase(std::remove(this->objects.begin(), this->objects.end(), *it), this->objects.end());
}

void Scene::addLogic(SGL::Logic* logic)
{
	// this->logics.push_back(logic);
	// std::stable_sort(this->logics.begin(), this->logics.end(), [](Logic* lhs, Logic* rhs)->bool { return lhs->getPriority() < rhs->getPriority(); });
}

void Scene::removeLogic(SGL::Logic* logic)
{
	// auto it = std::find(this->logics.begin(), this->logics.end(), logic);
	// if (it == this->logics.end())
	// 	throw std::runtime_error{"Could not find LogicBinder to remove from Scene"};

	// this->logics.erase(std::remove(this->logics.begin(), this->logics.end(), logic), this->logics.end());
}

void Scene::addAction(SGL::Action* action)
{
	// this->actions.push_back(action);
}

void Scene::removeAction(SGL::Action* action)
{
	// auto it = std::find(this->actions.begin(), this->actions.end(), action);
	// if (it == this->actions.end())
	// 	throw std::runtime_error{"Could not find Action to remove from Scene"};

	// this->actions.erase(std::remove(this->actions.begin(), this->actions.end(), action), this->actions.end());
}

void Scene::loadScene()
{
}

void Scene::suspendScene()
{
}

void Scene::resumeScene()
{
}

void Scene::unloadScene()
{
}
