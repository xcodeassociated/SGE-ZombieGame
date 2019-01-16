#ifndef SGE_LEVEL_HPP
#define SGE_LEVEL_HPP

#include <string>

class Level
{
	std::size_t height = 0;
	std::size_t width = 0;

	// std::vector<BackgroundElement> background;
	// std::vector<WorldElement> world;

public:
	Level() = default;
	Level(size_t x, size_t y);
	Level(Level&&) = default;

	Level& operator=(Level&&) = default;

	const size_t& getHeight() const;
	const size_t& getWidth() const;

	// std::vector<BackgroundElement>& getBackground();
	// std::vector<WorldElement>& getWorld();

	void clear();
};

#endif // !SGE_LEVEL_HPP
