#include "InputSystem.hpp"
#include "IO/InputManager/sge_input_manager.hpp"
#include "IO/Mouse/sge_mouse.hpp"
#include <InputBinder/sgl_input_binder.hpp>
#include <Control/Action/sgl_action.hpp>

#include <glm/glm.hpp>

SGL::InputSystem::MouseHandler::MouseHandler() noexcept : mouse(new SGE::MouseObject)
{
}

void SGL::InputSystem::MouseHandler::setMouseCoords(glm::vec2 coords) noexcept
{
	this->mouse->setMouseCoords(coords);
}

glm::vec2 SGL::InputSystem::MouseHandler::getMouseCoords() const noexcept
{
	return this->mouse->getMouseCoords();
}

SGE::MouseObject* SGL::InputSystem::MouseHandler::getMouseObject() noexcept
{
	return this->mouse;
}

SGL::InputSystem::InputSystem() noexcept
		: input_manager(new SGE::InputManager), mouseHandler(new MouseHandler)
{
}

void SGL::InputSystem::mapAction(const SGL::InputBinder& bind)
{
	auto p = this->keyMap.insert(std::make_pair(bind.getKey(), bind.getAction()));
	if (!p.second)
		throw std::runtime_error("Could not map action");

	bind.getAction()->perform();
}

void SGL::InputSystem::unmapAction(const SGL::InputBinder& bind)
{
    auto action = bind.getAction();
	if (this->keyMap.erase(bind.getKey()) == 0)
		throw std::runtime_error("Could not unmap action");
}

void SGL::InputSystem::pressKey(SGE::Key k)
{
	auto it = this->keyMap.find(k);
	if (it == this->keyMap.end())
		return;
	it->second->perform();
}

void SGL::InputSystem::pollEvents() noexcept
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
			case SDL_QUIT:
			{

			}break;

			case SDL_KEYDOWN:
			{
				this->pressKey(Key(event.key.keysym.sym));
			}break;

			case SDL_MOUSEMOTION:
			{
				this->mouseHandler->setMouseCoords({ event.motion.x, event.motion.y });
			}break;

			case SDL_MOUSEBUTTONDOWN:
			{
				this->mouseHandler->setMouseCoords({ event.motion.x, event.motion.y });
				this->pressKey(Key(-10));
			}break;

			case SDL_MOUSEBUTTONUP:
			{
			}break;
		}
	}
}

SGL::InputSystem::MouseHandler* SGL::InputSystem::getMouseHandler() noexcept
{
	return this->mouseHandler;
}
