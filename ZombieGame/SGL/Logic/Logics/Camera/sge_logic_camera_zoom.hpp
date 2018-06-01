#ifndef sge_logic_camera_zoom_h
#define sge_logic_camera_zoom_h

#include "../../sge_logic.hpp"
#include "../../../IO/Key/sge_key.hpp"

namespace SGE
{
	class Camera2d;

	namespace Logics
	{
		class CameraZoom : public Logic
		{
			Camera2d* cameraObject = nullptr;

			float speed;

			float maxZoom;
	
			float minZoom;

			const Key zoomIn;

			const Key zoomOut;

		public:

			CameraZoom(Camera2d* camera, const float speed, const float min, const float max, const SGE::Key in, const SGE::Key out);

			~CameraZoom() = default;

			void performLogic() override;
		};
	}
}

#endif // !sge_logic_camera_zoom_h
