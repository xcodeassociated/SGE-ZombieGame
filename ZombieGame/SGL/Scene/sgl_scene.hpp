#ifndef sge_scene_h
#define sge_scene_h

#include <vector>
#include <map>
#include "../Level/sgl_level.hpp"
#include "../Logic/sgl_logic.hpp"
#include "sge_scene_state.hpp"

namespace SGE
{
	class Scene;
	class Director;

    class Scene
    {
    public:
        using ObjectVector = std::vector<Object*>; // ecs
        using LogicVector = std::vector<Logic*>; // ecs
        using ActionVector = std::vector<Action*>;

    protected:
		Level level;
		LogicVector logics;
        ActionVector actions;
        ObjectVector objects;
	    
    public:
		unsigned long id = 0;
		SceneState state = SceneState::Standby;

		bool TextureLoaded = false;

	    LogicVector& getLogics();
        ActionVector& getActions();

		virtual ~Scene() = default;

	    virtual void loadLevel(const char* path, std::map<char, std::string> levelMask);

	    virtual Level& getLevel();

	    virtual ObjectVector& getObjects();

		virtual void addObject(SGE::Object* object);

		void removeObject(SGE::Object* object);

		void addLogic(Logic* logic);

		void removeLogic(Logic* logic);

        void addAction(Action* action);

        void removeAction(Action* action);

		virtual void loadScene();
		virtual void suspendScene();
		virtual void resumeScene();
		virtual void unloadScene();

		virtual void finalize() = 0;

        virtual void onDraw() = 0;

    };
    
}

#endif /* sge_scene_h */
