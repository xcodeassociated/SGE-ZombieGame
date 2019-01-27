//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sgl_input_binder.hpp"

SGL::InputBinder::InputBinder(Action* action, SGE::Key key) : action(action), key(key)
{
}

SGL::Action* SGL::InputBinder::getAction() const
{
    return this->action;
}

SGE::Key SGL::InputBinder::getKey() const
{
    return this->key;
}
