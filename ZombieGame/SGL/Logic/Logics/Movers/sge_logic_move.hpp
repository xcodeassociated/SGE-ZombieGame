#ifndef sge_logic_move_h
#define sge_logic_move_h

#include "../../sge_logic.hpp"
#include "../../../IO/Key/sge_key.hpp"

namespace SGE
{
	namespace Logics
	{
		class SimpleMove : public Logic
		{
			float speed = 0;
			
			const Key up;

			const Key down;

			const Key left;
	
			const Key right;

			Object* object = nullptr;

		public:
			SimpleMove(Object* object, const float speed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right);
	
			~SimpleMove() = default;

			void performLogic() override;
		};
	}
}

#endif //!sge_logic_move_h
