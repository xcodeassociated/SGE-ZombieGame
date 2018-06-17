set (SceneSOURCES
		sgl_scene_state.hpp
		sgl_scene.hpp
		sgl_scene.cpp
		sgl_box2dscene.hpp
		sgl_box2dscene.cpp)

add_library (Scene
		${SceneSOURCES})

target_link_libraries(Scene 
		Object
		Level
		Logic
		Utils
		Box2D)

install(TARGETS Scene DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")