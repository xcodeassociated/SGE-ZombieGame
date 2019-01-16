set (LevelSOURCES
	Level.hpp
	Level.cpp)

set (LevelParserSOURCES 
	LevelParser/LevelParser.hpp
	LevelParser/LevelParser.cpp)

add_library (Level
		${LevelSOURCES}
		${LevelParserSOURCES})

target_link_libraries(Level
		Sprite
		Utils)

install(TARGETS Level DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
