//
//  sge_action_move.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 06/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sgl_action_move_h
#define sgl_action_move_h

#include "../sgl_action.hpp"

#include <Position/sge_position.hpp>

using namespace SGE;

namespace SGL
{
	
    namespace ACTION
	{
        class Move : virtual public Action
		{
			Position position;

	        float destX = 0;
	        float destY = 0;

        public:
	        Move(Position && position, float _x, float _y, bool active);

		private:
	        virtual void perform() override;        
		};
    }
}

#endif
