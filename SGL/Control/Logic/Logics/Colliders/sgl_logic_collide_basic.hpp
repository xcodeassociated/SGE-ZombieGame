//
//  sge_logic_collide_basic.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 15/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sgl_logic_collide_basic_h
#define sgl_logic_collide_basic_h

#include "sgl_logic_collide.hpp"
#include <Position/sge_position.hpp>
#include <Shape/sge_shape.hpp>
#include <Action/sgl_action.hpp>
#include <optional>
#include <functional>

namespace SGL
{
	class Action;
	using namespace SGE;

    namespace Logics
	{
        class BasicCollider : public Collide
		{
		public:
			using collisionFunc = std::function<Action(Position*, Shape*, Position*, Shape*)>;

		private:
			collisionFunc onCollision;

			Position* positionA = nullptr;
			Shape* shapeA = nullptr;
			Position* positionB = nullptr;
			Shape* shapeB = nullptr;

		public:
	        BasicCollider(Position* positionA, Shape* shapeA, 
				Position* positionB, Shape* shapeB, const collisionFunc& _onCollision);

			virtual std::optional<Action> performLogic() override;
        };
        
    }
}


#endif /* sgl_logic_collide_basic_h */
