#ifndef sge_level_parser_h
#define sge_level_parser_h

#include <vector>
#include <map>

#include "../Level.hpp"

class LevelParser
{
	std::map<char, std::string> levelMask;
	std::vector<std::string> levelData;
	
public:
	LevelParser(const char* path, const std::map<char, std::string>& mask);

	Level parse();
};

#endif