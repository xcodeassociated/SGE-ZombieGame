#include "sgl_logic_camera_zoom.hpp"
#include <IO/KeyboardState/sge_keyboard_state.hpp>
#include <Camera2d/sge_camera2d.hpp>
#include <Utils/Timing/sge_fps_limiter.hpp>

SGL::Logics::CameraZoom::CameraZoom(SGE::Camera2d* camera, const float speed, const float min, 
	const float max, const SGE::Key in, const SGE::Key out)
		: Logic(LogicPriority::Highest), cameraObject(camera), speed(speed), minZoom(min), 
			maxZoom(max), zoomIn(in), zoomOut(out)
{
}

std::optional<SGL::Action> SGL::Logics::CameraZoom::performLogic()
{
	using namespace SGE;
	
	auto scale = this->cameraObject->getScale();

	if (isPressed(this->zoomIn)) scale += this->speed * delta_time;
	if (this->minZoom < scale) scale = this->minZoom;
	if (isPressed(this->zoomOut)) scale -= this->speed * delta_time;
	if (this->maxZoom > scale) scale = this->maxZoom;

	this->cameraObject->setScale(scale);

	return {};
}
