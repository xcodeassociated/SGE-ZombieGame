#ifndef SGE_WORLDSTEP
#define SGE_WORLDSTEP

#include "../../../../Box2D/Dynamics/b2World.h"
#include "../../sgl_logic.hpp"

namespace SGL
{
		class WorldStep : public Logic
	{
		b2World* world;
		int vel = 8;
		int pos = 3;

	public:
		using Logic::Logic;
		explicit WorldStep(b2World*) noexcept;
		WorldStep(b2World*,int,int) noexcept;
		virtual std::optional<Action> performLogic() override;
		int getVelocityIterations() const;
		int getPositionIterations() const;
		void setVelocityIterations(int);
		void setPositionIterations(int);
	};
}

#endif
