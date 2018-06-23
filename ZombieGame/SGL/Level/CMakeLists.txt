set (LevelSOURCES
	sgl_level.hpp
	sgl_level.cpp)

set (LevelParserSOURCES 
	LevelParser/sgl_level_parser.hpp
	LevelParser/sgl_level_parser.cpp)

add_library (Level
		${LevelSOURCES}
		${LevelParserSOURCES})

target_link_libraries(Level
		Sprite
		Utils)

install(TARGETS Level DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")