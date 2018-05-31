set(GAME_SOURCE_FILES main.cpp
		GameCode/Actions.cpp
		GameCode/Actions.hpp
		GameCode/Logics.cpp
		GameCode/Logics.hpp
		GameCode/Objects.cpp
		GameCode/Objects.hpp
		GameCode/ZombieScene.cpp
		GameCode/ZombieScene.hpp
		GameCode/IntroScene.cpp
		GameCode/IntroScene.hpp)

add_executable(${PROJECT_NAME} ${GAME_SOURCE_FILES})

if (NOT INCLUDE_ENGINE_PROJECT)
	target_link_libraries(${PROJECT_NAME}
		${SGE_LIBRARIES}
		${Boost_LIBRARIES}
		${SDL2_LIBRARY}
		${GLEW_LIBRARIES}
		${OPENGL_LIBRARIES}
		${GLM_LIBRARIES})
else()
	target_link_libraries(${PROJECT_NAME}

		${Boost_LIBRARIES}
		${SDL2_LIBRARY}
		${GLEW_LIBRARIES}
		${OPENGL_LIBRARIES}
		${GLM_LIBRARIES}

		Action
		ActionHandler
		IO
		Level
		Logic
		Object
		Game
		Renderer
		Scene
		Utils
		PicoPNG
		Box2D)
endif()

if (INCLUDE_ENGINE_PROJECT)
	get_filename_component(SGE_RELATIVE_PARENT ${CMAKE_CURRENT_SOURCE_DIR} PATH)
	set(GLSL_DIR "${SGE_RELATIVE_PARENT}/SGE/SimpleGameEngine/Renderer/Shaders/res")

	add_custom_command(TARGET ${PROJECT_NAME} 
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E 
			make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders/)
	add_custom_command(TARGET ${PROJECT_NAME}
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E
			copy ${GLSL_DIR}/colorShader.frag ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders/)
	add_custom_command(TARGET ${PROJECT_NAME}
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E
			copy ${GLSL_DIR}/colorShader.vert ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders/)

elseif(COPY_SHADERS)

	if (NOT SGE_ROOT)
		message(WARNING "SGE_ROOT not provided, cannot copy SGE shaders.")
	else()
		set(GLSL_DIR ${SGE_ROOT}/include/Renderer/Shaders/res)

		add_custom_command(TARGET ${PROJECT_NAME} 
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E 
				make_directory${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders/)
		add_custom_command(TARGET ${PROJECT_NAME}
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E
				copy ${GLSL_DIR}/colorShader.frag ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders/)
		add_custom_command(TARGET ${PROJECT_NAME}
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E
				copy ${GLSL_DIR}/colorShader.vert ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders/)
	endif()
endif()

if (COPY_GAME_RESOURCES)
	add_custom_command(TARGET ${PROJECT_NAME}
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E
			copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Data/Resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Resources)

	add_custom_command(TARGET ${PROJECT_NAME}
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E
			copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Data/Levels ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Levels)
endif()