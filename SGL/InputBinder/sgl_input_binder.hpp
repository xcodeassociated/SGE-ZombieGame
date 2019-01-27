//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP
#define SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP

#ifdef _WIN32
	#ifdef SHARED
		#include <input_binder_export.h>
	#else
		#define INPUT_BINDER_EXPORT
	#endif
#else
	#define INPUT_BINDER_EXPORT
#endif

#include "IO/Key/sge_key.hpp"

namespace SGL
{
    class Action;
    
    class InputBinder
    {
        Action* action = nullptr;
	    SGE::Key key;

    public:
        InputBinder(Action* action, SGE::Key key);

        Action* getAction() const;
	    SGE::Key getKey() const;
    };

}

#endif //SGE_ZOMBIEGAME_SGE_INPUT_BINDER_HPP
