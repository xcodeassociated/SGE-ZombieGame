#ifndef INTRO_SCENE
#define INTRO_SCENE

#include <string>
#include <Scene/sge_scene.hpp>

class IntroScene : public SGE::Scene
{
protected:
	std::string path;
	SGE::Scene* next;

public:
	IntroScene(SGE::Scene* next, const char* path);
	virtual ~IntroScene();
	
	virtual void loadScene() override;
	virtual void finalize() override;
	virtual void onDraw() override;
};

#endif
