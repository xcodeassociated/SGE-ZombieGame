#ifndef sge_logic_camera_zoom_h
#define sge_logic_camera_zoom_h

#include "../../sgl_logic.hpp"
#include "IO/Key/sge_key.hpp"

#include <optional>

namespace SGE
{
	class Camera2d;
}

namespace SGL
{
	namespace Logics
	{
		using namespace SGE;
		class CameraZoom : public Logic
		{
			Camera2d* cameraObject = nullptr;
			float speed = 0.f;
			float maxZoom = 0.f;
			float minZoom = 0.f;
			const Key zoomIn;
			const Key zoomOut;

		public:
			using Logic::Logic;
			CameraZoom(Camera2d* camera, const float speed, const float min, const float max, 
				const SGE::Key in, const SGE::Key out);
			virtual ~CameraZoom() = default;

			virtual std::optional<Action> performLogic() override;
		};
	}
}

#endif // !sge_logic_camera_zoom_h
