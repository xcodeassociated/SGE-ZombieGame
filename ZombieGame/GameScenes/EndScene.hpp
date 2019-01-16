#ifndef ENDSCENE_SCENE
#define ENDSCENE_SCENE

#include "IntroScene.hpp"

class EndScene: public IntroScene
{
public:
    using IntroScene::IntroScene;
	virtual void loadScene() override;
};

#endif
