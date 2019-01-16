//
//  sge_input_handler.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 11/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_input_system_h
#define sge_input_system_h

#include <unordered_map>
#include <type_traits>
#include <typeinfo>

#include <glm/glm.hpp>

#include <IO/Key/sge_key.hpp>
#include <IO/InputManager/sge_input_manager.hpp>

namespace SGE
{
    class InputManager;
    class MouseObject;
}
namespace SGL 
{
    class InputBinder;
    class Action;
}

struct KeyHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

namespace SGL
{

    class InputSystem {
        SGE::InputManager* input_manager = nullptr;
        std::unordered_map<SGE::Key, SGL::Action*> keyMap;

        void pressKey(SGE::Key k);

    public:
        InputSystem() noexcept;

        void pollEvents() noexcept;

        void mapAction(const SGL::InputBinder& bind);
        void unmapAction(const SGL::InputBinder& bind);

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
            SGE::MouseObject* mouse = nullptr;

        public:
            MouseHandler() noexcept;

            void setMouseCoords(glm::vec2 coords) noexcept;
            glm::vec2 getMouseCoords() const noexcept;

            SGE::MouseObject *getMouseObject() noexcept;
        };

    private:
        MouseHandler *mouseHandler = nullptr;

    public:
        MouseHandler *getMouseHandler() noexcept;
    };

}

#endif /* sge_input_system_h */
