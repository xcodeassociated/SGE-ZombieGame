#ifndef sge_scene_h
#define sge_scene_h

#include <vector>
#include <map>
#include "../Level/Level.hpp"
#include <Control/Logic/sgl_logic.hpp>
#include "SceneState.hpp"

namespace SGL
{
	class Object;
	class Logic;
	class Action;
}

class Director;

class Scene
{
public:
	// using ObjectVector = std::vector<Object*>; // ecs
	// using LogicVector = std::vector<Logic*>; // ecs
	// using ActionVector = std::vector<Action*>; // ecs

protected:
	Level level;
	// LogicVector logics;
	// ActionVector actions;
	// ObjectVector objects;
	
public:
	unsigned long id = 0;
	SceneState state = SceneState::Standby;

	bool TextureLoaded = false;

	// LogicVector& getLogics();
	// ActionVector& getActions();

	virtual ~Scene() = default;

	virtual void loadLevel(const char* path, std::map<char, std::string> levelMask);
	virtual Level& getLevel();
	// virtual ObjectVector& getObjects();

	virtual void addObject(SGL::Object* object);
	void removeObject(SGL::Object* object);

	void addLogic(SGL::Logic* logic);
	void removeLogic(SGL::Logic* logic);

	void addAction(SGL::Action* action);
	void removeAction(SGL::Action* action);

	virtual void loadScene();
	virtual void suspendScene();
	virtual void resumeScene();
	virtual void unloadScene();

	virtual void finalize() = 0;

	virtual void onDraw() = 0;
};

#endif /* sge_scene_h */
