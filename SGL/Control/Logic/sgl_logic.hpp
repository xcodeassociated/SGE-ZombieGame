//
//  sge_logic.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 15/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_logic_h
#define sge_logic_h

#ifdef _WIN32
	#ifdef SHARED
		#include <control_export.h>
	#else
		#define CONTROL_EXPORT
	#endif
#else
	#define CONTROL_EXPORT
#endif

#include "sgl_logic_priority.hpp"
#include "../Action/sgl_action.hpp"

#include <optional>
class DynamicVectorLogic;

namespace SGL
{
    class Logic
	{
	public:
		using Priority = LogicPriority;
        virtual std::optional<Action> performLogic() = 0;

    protected:
	    Logic(Priority priority);

        bool isOn = true;
		Priority priority;

    public:
	    Priority getPriority() const;

	    virtual void setOn(bool e);
	    virtual bool getOn();
	    virtual void toggleOn();
        virtual ~Logic() = default;
    };
}


#endif /* sge_logic_h */
