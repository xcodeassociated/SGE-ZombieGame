//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP
#define SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP

#include "IO/Key/sge_key.hpp"

namespace SGE
{
    class Action;

    class InputBinder
    {
        Action* action = nullptr;
	  
        Key key;

    public:
        InputBinder(Action* action, Key key);

        Action* getAction() const;

        Key getKey() const;
    };

}


#endif //SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP
