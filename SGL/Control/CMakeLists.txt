set (LogicSOURCES
		Logic/sgl_logic.hpp
		Logic/sgl_logic.cpp)

set (LogicsCameraSOURCES
		Logic/Logics/Camera/sgl_logic_camera_zoom.hpp
		Logic/Logics/Camera/sgl_logic_camera_zoom.cpp)

set (LogicsCollidersSOURCES
		Logic/Logics/Colliders/sgl_logic_collide.hpp
		Logic/Logics/Colliders/sgl_logic_collide.cpp
		Logic/Logics/Colliders/sgl_logic_collide_basic.hpp
		Logic/Logics/Colliders/sgl_logic_collide_basic.cpp)

set (LogicMoversSOURCES
		Logic/Logics/Movers/sgl_logic_move.hpp
		Logic/Logics/Movers/sgl_logic_move.cpp)
		
set (LogicWorldSOURCES
		Logic/Logics/World/sgl_worldstep.hpp
		Logic/Logics/World/sgl_worldstep.cpp)

set (ActionSOURCES
		Action/sgl_action.hpp
		Action/sgl_action.cpp
		Action/Actions/sgl_action_move.hpp
		Action/Actions/sgl_action_move.cpp)

add_library (Control
		${LogicSOURCES}
		${LogicsCollidersSOURCES}
		${LogicsCameraSOURCES}
		${LogicMoversSOURCES}
		${LogicWorldSOURCES}
		${ActionSOURCES})

target_link_libraries(Control
		Shape
		Sprite
		IO
		Utils
		Box2D
		Camera2d)
		
if(WIN32)
	include(GenerateExportHeader)
	generate_export_header(Control EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/control_export.h)
endif()

install(TARGETS Control DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
