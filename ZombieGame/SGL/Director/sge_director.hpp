#ifndef sge_director_h
#define sge_director_h

#include <vector>
#include <memory>
#include "../../Logic/sge_logic.hpp"
#include "../../Scene/sge_scene.hpp"
#include "../../Utils/Logger/sge_logger.hpp"

namespace SGE
{
    class Director final
    {
		static std::shared_ptr<Logger> logger;
        static std::shared_ptr<LoggerError> logger_err;

		Game* game = nullptr;

		int Width = 0;

		int Height = 0;

	    Scene* nextScene = nullptr;

	    Director(int w, int h);
	 
	    ~Director(); //Will prevent user form deleting Director, should be useful with ARC system in place.
		
		std::vector<Scene*> scenes;

	public:
	    static Director* getDirector(int w = 0, int h = 0);

	    std::pair<int, int> getResolution();

	    Scene* addScene(Scene* scene);

	    void deleteScene(Scene* scene);

	    void finalize();

	    void bindGame(Game* game);

	    Scene* getNextScene();
	    void setNextScene(Scene* next);

		void loadScene(Scene* scene);
		void unloadScene(Scene* scene);
		void resumeScene(Scene* scene);
		void suspendScene(Scene* scene);

		void toNextScene(Scene* scene);
    };
    
}

#endif /* sge_director_h */
