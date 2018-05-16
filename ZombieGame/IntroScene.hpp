#ifndef INTRO_SCENE
#define INTRO_SCENE

#include <string>

#ifndef SGE_INCLUDED
#include <Scene/sge_scene.hpp>
#else
#include "sge_scene.hpp"
#endif

class IntroScene : public SGE::Scene
{
protected:
	std::string path;
	SGE::Scene* next;
public:

	IntroScene(SGE::Scene* next, const char* path);

	virtual void loadScene() override;

	virtual ~IntroScene();

	virtual void finalize() override;

	virtual void onDraw() override;
};

class EndScene: public IntroScene
{
public:
	using IntroScene::IntroScene;
	virtual void loadScene() override;
};

#endif
