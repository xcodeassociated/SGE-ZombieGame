if (NOT INCLUDE_ENGINE_PROJECT)
	set(GAME_SOURCE_FILES main.cpp
			Actions.cpp
			Actions.hpp
			Logics.cpp
			Logics.hpp
			Objects.cpp
			Objects.hpp
			ZombieScene.cpp
			ZombieScene.hpp
			IntroScene.cpp
			IntroScene.hpp)

	add_executable(${PROJECT_NAME} ${GAME_SOURCE_FILES})

	target_link_libraries(${PROJECT_NAME}
		${SGE_LIBRARIES}
		${Boost_LIBRARIES}
		${SDL2_LIBRARY}
		${GLEW_LIBRARIES}
		${OPENGL_LIBRARIES}
		${GLM_LIBRARIES})
else()
	set(GAME_SOURCE_FILES main.cpp
		Actions.cpp
		Actions.hpp
		Logics.cpp
		Logics.hpp
		Objects.cpp
		Objects.hpp
		ZombieScene.cpp
		ZombieScene.hpp
		IntroScene.cpp
		IntroScene.hpp)

	add_executable(${PROJECT_NAME} ${GAME_SOURCE_FILES})

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
			make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)
	add_custom_command(TARGET ${PROJECT_NAME}
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E
			copy ${GLSL_DIR}/* ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders/)
elseif(COPY_SHADERS)
	if (NOT SGE_ROOT)
		message(WARNING "SGE_ROOT not provided, cannot copy SGE shaders.")
	else()
		set(GLSL_DIR ${SGE_ROOT}/include/Renderer/Shaders/res)

		add_custom_command(TARGET ${PROJECT_NAME}
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E
				copy_directory ${GLSL_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders/)
	endif()
endif()

if (COPY_GAME_RESOURCES)
	add_custom_command(TARGET ${PROJECT_NAME}
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E
			copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Resources)

	add_custom_command(TARGET ${PROJECT_NAME}
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E
			copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Levels ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Levels)
endif()