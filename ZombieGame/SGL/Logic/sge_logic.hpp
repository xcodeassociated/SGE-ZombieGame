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
	#ifdef SGE_SHARED
		#include <logic_export.h>
	#else
		#define LOGIC_EXPORT
	#endif
#else
	#define LOGIC_EXPORT
#endif

#include "sge_logic_priority.hpp"


class DynamicVectorLogic;

namespace SGE
{
	class Logic;
	class Action;
	class ActionHandler;

    class Logic
	{
	public:
		using Priority = LogicPriority;

        virtual void performLogic() = 0;

    protected:
		static LOGIC_EXPORT ActionHandler* action_handler;

	    explicit Logic(Priority _p);

        bool isOn = true;

		Priority priority;

	    void sendAction(Action* action) const;

    public:
	    Priority getPriority() const;

	    virtual void setOn(bool e) final;

	    virtual bool getOn() final;

	    virtual void toggleOn() final;

        virtual ~Logic() = 0;
        
    };

}


#endif /* sge_logic_h */
