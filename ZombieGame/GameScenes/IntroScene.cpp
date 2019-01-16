﻿#include "IntroScene.hpp"

#include <Object/Shape/sge_shape_rectangle.hpp>
#include <Game/sge_game.hpp>
#include <Game/Director/sge_director.hpp>
#include "Objects.hpp"
#include "Logics.hpp"
#include "Actions.hpp"


IntroScene::IntroScene(SGE::Scene* next, const char* path) : path(path), next(next)
{
}

void IntroScene::loadScene()
{
	auto o = new Image(0, 0, new SGE::Rectangle(1024, 768, true));
	auto g = SGE::Game::getGame();
	o->setVisible(true);
	o->setDrawable(true);
	g->textureObject(o, path);
	this->addObject(o);
	this->addLogic(new Timer(5, new Load(next)));
	g->getCamera()->setPosition(0, 0);
	g->getCamera()->setScale(1.f);
}

IntroScene::~IntroScene()
{
}

void IntroScene::finalize()
{
}

void IntroScene::onDraw()
{
	auto g = SGE::Game::getGame();
	g->getCamera()->setPosition(0, 0);
	g->getCamera()->setScale(1.f);
	SGE::Director::getDirector()->unloadScene(next);
}
