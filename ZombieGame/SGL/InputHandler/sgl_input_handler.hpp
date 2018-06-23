//
//  sge_input_handler.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 11/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_input_handler_h
#define sge_input_handler_h

#include <unordered_map>
#include <glm/glm.hpp>

#include "IO/Key/sge_key.hpp"

namespace SGE
{
    class InputManager;
    class MouseObject;
    class InputBinder;
	class Action;

    class InputHandler {
        InputManager* input_manager = nullptr;
        std::unordered_map <Key, Action*, KeyHashAlias<Key>> keyMap;

        void pressKey(Key k);

    public:
        explicit InputHandler(Game* game) noexcept;

        void pollEvents() noexcept;

        void mapAction(const InputBinder& bind);

        void unmapAction(const InputBinder& bind);

	    void clear()
	    {
		    for(auto bind : this->keyMap)
		    {
				delete bind.second;
		    }
			this->keyMap.clear();
	    }

        class MouseHandler
        {

            MouseObject* mouse = nullptr;

        public:

            MouseHandler() noexcept;

            void setMouseCoords(glm::vec2 coords) noexcept;

            glm::vec2 getMouseCoords() const noexcept;

            MouseObject *getMouseObject() noexcept;
        };

    private:
        MouseHandler *mouseHandler = nullptr;

    public:
        MouseHandler *getMouseHandler() noexcept;
    };

}

#endif /* sge_input_handler_h */
