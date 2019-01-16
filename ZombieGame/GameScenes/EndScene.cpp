#include "EndScene.hpp"

void EndScene::loadScene()
{
	auto o = new Image(0, 0, new SGE::Rectangle(1024, 768, true));
	o->setVisible(true);
	o->setDrawable(true);
	auto g = SGE::Game::getGame();
	g->textureObject(o, path);
	this->addObject(o);
	this->addLogic(new OnKey(SGE::Key::Return, next));
	g->getCamera()->setPosition(0, 0);
	g->getCamera()->setScale(1.f);
}
