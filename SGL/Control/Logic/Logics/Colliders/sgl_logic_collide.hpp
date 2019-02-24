//
//  sge_logic_collide.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 15/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sgl_logic_collide_h
#define sgl_logic_collide_h

#include <Logic/sgl_logic.hpp>
#include <Position/sge_position.hpp>
#include <Shape/sge_shape.hpp>

namespace SGL
{
	class Action;
	using namespace SGE;
    namespace Logics
	{
        class Collide : public Logic
		{
        public:
	        static Action* RectangleCollisionVec(Position* stillPosition, Shape* stillShape, 
				Position* toMove, Shape* toMoveShape);

	        static Action* CircleCollisionVec(Position* stillPosition, Shape* stillShape, 
				Position* toMove, Shape* toMoveShape);

	        static Action* CircleToRectCollisionVec(Position* stillPosition, Shape* stillShape, 
				Position* toMove, Shape* toMoveShape);

        protected:
	        virtual bool collideWithSameShape(Position* selfPosition, Shape* selfShape, 
				Position* oponentPosition, Shape* oponentShape);

	        virtual bool collideWithDifferentShape(Position* selfPosition, Shape* selfShape, 
				Position* oponentPosition, Shape* oponentShape);

	        virtual bool collideWithEdgesDifferentShape(Position* selfPosition, Shape* selfShape, 
				Position* oponentPosition, Shape* oponentShape);

	        explicit Collide(const LogicPriority& logicPriority);
        };
        
    }
}

#endif /* sgl_logic_collide_h */

