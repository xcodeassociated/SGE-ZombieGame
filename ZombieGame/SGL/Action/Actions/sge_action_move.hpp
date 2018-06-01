//
//  sge_action_move.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 06/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_action_move_h
#define sge_action_move_h

#include "../sge_action.hpp"

namespace SGE
{
	class Object;

    namespace ACTION
	{
        class Move : virtual public Action
		{
			Object* object = nullptr;

	        float destX = 0;
	    
	        float destY = 0;

        public:
	        Move(Object* object, float _x, float _y, bool active);

		private:
	        virtual void action_begin() noexcept override;

	        virtual void action_main() noexcept override;

	        virtual void action_ends() noexcept override;
        };
    }
}

#endif /* sge_action_move_h */
