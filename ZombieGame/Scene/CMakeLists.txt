set (SceneSOURCES
		SceneState.hpp
		Scene.hpp
		Scene.cpp
		Box2dScene/Box2dScene.hpp
		Box2dScene/Box2dScene.cpp)

add_library (Scene ${SceneSOURCES})

target_link_libraries(Scene 
		Sprite
		Control
		Utils
		Box2D)

install(TARGETS Scene DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
