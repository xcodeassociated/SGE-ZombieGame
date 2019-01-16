#ifndef ZOMBIEGAME_ACTIONS
#define ZOMBIEGAME_ACTIONS

#include <Control/Action/sgl_action.hpp>
#include <Control/Logic/sgl_logic.hpp>
#include <IO/Mouse/sge_mouse.hpp>
#include "../Scene/Scene.hpp"

class GOTO : public SGL::Action
{
	SGL::Object* object = nullptr;

public:
	GOTO(SGL::Object* object);

	virtual void action_begin() noexcept override;
	virtual void action_main() noexcept override;
	virtual void action_ends() noexcept override;
};

class PortalAction : public SGL::Action
{
public:
	PortalAction();

	virtual void action_begin() override;
	virtual void action_main() override;
	virtual void action_ends() override;
};

class LogicSwitch : public SGL::Action
{
	SGL::Logic* logic = nullptr;

public:
	LogicSwitch(SGL::Logic* id);

	void action_begin() override;
	void action_main() override;
	void action_ends() override;
};

class MouseClickedAction : public SGL::Action
{
	SGE::MouseObject* mouseObject = nullptr;
	SGE::Object* player = nullptr;

public:
	MouseClickedAction(SGE::MouseObject* mouseObject, SGL::Object* player);

	virtual void action_begin() noexcept override;
	virtual void action_ends() noexcept override;
	virtual void action_main() noexcept override;
};

class Load : public SGL::Action
{
	Scene* nextScene = nullptr;

public:
	explicit Load(Scene* scene);
	void action_begin() override;
	void action_main() override;
	void action_ends() override;
	
};

#endif
