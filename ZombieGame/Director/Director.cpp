#include "Director.hpp"
#include "../Scene/SceneState.hpp"

#include <algorithm>
#include <iostream>

Director::Director(const int w, const int h) : Width(w), Height(h)
{
}

Director* Director::getDirector(const int w, const int h)
{
	static Director* director = new Director(w, h);
	return director;
}

std::pair<int, int> Director::getResolution()
{
	return std::make_pair(this->Width, this->Height);
}

Scene* Director::addScene(Scene* scene)
{
	this->scenes.push_back(scene);
	return scene;
}

void Director::deleteScene(Scene* scene)
{
	auto sceneIt = std::find(this->scenes.begin(), this->scenes.end(), scene);
	if (sceneIt != this->scenes.end())
	{
		this->scenes.erase(std::remove(this->scenes.begin(), this->scenes.end(), *sceneIt), this->scenes.end());
	}
}

void Director::finalize()
{
}

Scene* Director::getNextScene()
{
	Scene* next = this->nextScene;
	this->nextScene = nullptr;
	return next;
}

void Director::setNextScene(Scene* next)
{
	this->nextScene = next;
}

void Director::loadScene(Scene* scene)
{
	switch(scene->state)
	{
	case SceneState::Standby:
		scene->loadScene();
		break;
	case SceneState::Suspended:
		scene->resumeScene();
		break;
	case SceneState::Ready:
		break;
	default:
		throw std::runtime_error("Cannot load Scene ID:" + std::to_string(scene->id) + " State:" + toString(scene->state));
	}
	scene->state = SceneState::Ready;
}

void Director::unloadScene(Scene* scene)
{
	switch (scene->state)
	{
	case SceneState::Ready:
	case SceneState::Suspended:
		scene->unloadScene();
		break;
	case SceneState::Standby:
		break;
	default:
		throw std::runtime_error("Cannot prepare Scene ID:" + std::to_string(scene->id) + " State:" + toString(scene->state));
	}
	scene->state = SceneState::Standby;
}

void Director::resumeScene(Scene* scene)
{
	switch (scene->state)
	{
	case SceneState::Suspended:
		scene->resumeScene();
		break;
	case SceneState::Ready:
		break;
	default:
		throw std::runtime_error("Cannot resume Scene ID:" + std::to_string(scene->id) + " State:" + toString(scene->state));
	}
	scene->state = SceneState::Ready;
}

void Director::suspendScene(Scene* scene)
{
	switch (scene->state)
	{
	case SceneState::Ready:
		scene->suspendScene();
		break;
	case SceneState::Suspended:
		break;
	default:
		throw std::runtime_error("Cannot resume Scene ID:" + std::to_string(scene->id) + " State:" + toString(scene->state));
	}
	scene->state = SceneState::Suspended;
}

void Director::toNextScene(Scene* scene)
{
	this->nextScene = scene;
}
