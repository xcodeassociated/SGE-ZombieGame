#ifndef sge_logic_move_h
#define sge_logic_move_h

#include "../../sgl_logic.hpp"
#include "IO/Key/sge_key.hpp"
#include <Position/sge_position.hpp>

#include <optional>

using namespace SGE;

namespace SGL
{
	namespace Logics
	{
		class SimpleMove : public Logic
		{
			Position position;

			float speed = 0;
			const Key up;
			const Key down;
			const Key left;
			const Key right;

		public:
			using Logic::Logic;
			SimpleMove(Position && position, const float speed, const SGE::Key up, const SGE::Key down, 
				const SGE::Key left, const SGE::Key right);
	
			~SimpleMove() = default;

			virtual std::optional<Action> performLogic() override;
		};
	}
}

#endif //!sge_logic_move_h
