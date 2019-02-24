#ifndef sge_director_h
#define sge_director_h

#include <vector>
#include <memory>
#include <Logic/sgl_logic.hpp>
#include "../Scene/Scene.hpp"

class Director final
{
	const int Width = 0;
	const int Height = 0;

	Scene* nextScene = nullptr;
	std::vector<Scene*> scenes;

	Director(const int w, const int h);
	virtual ~Director() = default;

public:
	static Director* getDirector(const int w = 0, const int h = 0);

	std::pair<int, int> getResolution();

	Scene* addScene(Scene* scene);
	void deleteScene(Scene* scene);

	void finalize();

	Scene* getNextScene();
	void setNextScene(Scene* next);

	void loadScene(Scene* scene);
	void unloadScene(Scene* scene);
	void resumeScene(Scene* scene);
	void suspendScene(Scene* scene);

	void toNextScene(Scene* scene);
};
    

#endif /* sge_director_h */
