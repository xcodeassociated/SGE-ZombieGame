set (LogicSOURCES
		sgl_logic.hpp
		sgl_logic.cpp)

set (LogicsCameraSOURCES
		Logics/Camera/sgl_logic_camera_zoom.hpp
		Logics/Camera/sgl_logic_camera_zoom.cpp)

set (LogicMoversSOURCES
		Logics/Movers/sgl_logic_move.hpp
		Logics/Movers/sgl_logic_move.cpp)
		
set (LogicWorldSOURCES
		Logics/World/sgl_worldstep.hpp
		Logics/World/sgl_worldstep.cpp)

set (ActionSOURCES
		Action/sgl_action.hpp
		Action/sgl_action.cpp/
		Action/Actions/sgl_action_move.hpp
		Action/Actions/sgl_action_move.cpp)

add_library (Control
		${LogicSOURCES}
		${LogicsCameraSOURCES}
		${LogicMoversSOURCES}
		${LogicWorldSOURCES}
		${ActionSOURCES})

target_link_libraries(Control
		Sprite
		IO
		Utils)
		
if(WIN32)
	include(GenerateExportHeader)
	generate_export_header(Logic EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/logic_export.h)
endif()

install(TARGETS Control DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")