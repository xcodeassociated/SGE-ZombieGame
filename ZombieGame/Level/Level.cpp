#include "Level.hpp"
#include <string>

Level::Level(size_t x, size_t y): height(y), width(x)
{
}

const std::size_t& Level::getHeight() const
{
	return this->height;
}

const std::size_t& Level::getWidth() const
{
	return this->width;
}

// std::vector<BackgroundElement>& Level::getBackground()
// {
// 	return this->background;
// }

// std::vector<WorldElement>& Level::getWorld()
// {
// 	return this->world;
// }

void Level::clear()
{
	// this->background.clear();
	// this->world.clear();
}
