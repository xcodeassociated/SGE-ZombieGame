#ifndef ZOMBIEGAME_ACTIONS
#define ZOMBIEGAME_ACTIONS

#include <Control/Action/sgl_action.hpp>
#include <Control/Logic/sgl_logic.hpp>
#include <IO/Mouse/sge_mouse.hpp>
#include <Position/sge_position.hpp>
#include "../Scene/Scene.hpp"

class GOTO : public SGL::Action
{
	SGE::Position* position = nullptr;

public:
	GOTO(SGE::Position* position);

	virtual void perform() noexcept override;
};

class PortalAction : public SGL::Action
{
public:
	PortalAction();

	virtual void perform() override;
};

class LogicSwitch : public SGL::Action
{
	SGL::Logic* logic = nullptr;

public:
	LogicSwitch(SGL::Logic* id);
	void perform() override;
};

class MouseClickedAction : public SGL::Action
{
	SGE::MouseObject* mouseObject = nullptr;
	SGE::Position* player = nullptr;

public:
	MouseClickedAction(SGE::MouseObject* mouseObject, SGE::Position* player);
	virtual void perform() noexcept override;
};

class Load : public SGL::Action
{
	Scene* nextScene = nullptr;

public:
	explicit Load(Scene* scene);
	void perform() override;
};

#endif
