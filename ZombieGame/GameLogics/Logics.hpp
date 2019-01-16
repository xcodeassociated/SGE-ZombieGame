﻿#ifndef ZOMBIEGAME_LOGICS
#define ZOMBIEGAME_LOGICS

#include <vector>
#include <random>
#include <functional>

#include <Logic/sge_logic.hpp>
#include <Logic/Logics/Colliders/sge_logic_collide.hpp>
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <IO/Key/sge_key.hpp>
#include <Object/Camera2d/sge_camera2d.hpp>
#include <IO/Mouse/sge_mouse.hpp>

#include "Objects.hpp"

namespace SGE {
	class Scene;
}

struct CheckWall : public b2RayCastCallback
{
	bool hitWall = false;
	virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
};

class SimpleMove : public SGE::Logic
{
	float speed = 0;
	const SGE::Key up;
	const SGE::Key down;
	const SGE::Key left;
	const SGE::Key right;
	SGE::Reactive* object = nullptr;
public:
	SimpleMove(SGE::Reactive* object, const float speed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right);
	void performLogic() override;
};

class BiCollider : public SGE::Logic
{
	SGE::Object* a = nullptr;
	SGE::Object* b = nullptr;

public:
	BiCollider(SGE::Object* a, SGE::Object* b);

	virtual void performLogic() override;
};

class PortalLogic : public SGE::Logics::Collide
{
	SGE::Object* portal = nullptr;
	SGE::Object* player = nullptr;

public:
	PortalLogic(SGE::Object* portal, SGE::Object* player);

	virtual void performLogic() override;
};

class HumanRandomMovement : public SGE::Logic
{
protected:
	std::vector<Human*>* humans = nullptr;
	std::default_random_engine engine;
	std::uniform_real_distribution<float> angle;

	void randomMovement(Human* human);

public:
	explicit HumanRandomMovement(std::vector<Human*>* humans);
	virtual void performLogic() override;
};

class HumanMovement : public HumanRandomMovement
{
	using ZombifyFunc = std::function<void(Human*)>;
protected:
	ZombifyFunc zombifier = nullptr;
	b2World* world = nullptr;
	void zombieMovement(Human* human);
	void humanMovement(Human* human);
public:
	explicit HumanMovement(std::vector<Human*>* humans, ZombifyFunc fun, b2World* world);

	virtual void performLogic() override;
};

class SnapCamera : public SGE::Logic
{
	const float speed = 0;
	const SGE::Key up, down, left, right, snapKey;
	bool snapped = true;
	SGE::Object* snapTo = nullptr;
	SGE::Camera2d* cam = nullptr;

public:
	SnapCamera(const float specamed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right, const SGE::Key snapKey, SGE::Object* snapTo, SGE::Camera2d* cam);

	~SnapCamera() = default;

	void performLogic() override;
};

class Timer : public SGE::Logic
{
	float time = .0f;
	SGE::Action* action = nullptr;
public:
	Timer(float time, SGE::Action* action);
	void performLogic() override;
};

class OnKey : public SGE::Logic
{
	SGE::Key key;
	SGE::Scene* scene = nullptr;
public:
	OnKey(SGE::Key key, SGE::Scene* scene);
	void performLogic() override;
};

struct Aimcast: b2RayCastCallback
{
	b2Vec2 point = b2Vec2_zero;
	bool hit = false;
	b2Fixture* fixture;
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
};

class AimPointer : public SGE::Logic
{
protected:
	b2World* world;
	SGE::Object* aimer;
	Pointer* pointer;
	SGE::MouseObject* mouse;
	SGE::Camera2d* cam;
	float range;
	float reload = -1.f;
	std::size_t& counter;
	b2Filter corpseFilter;
	void aim(b2Vec2 pos, b2Vec2 target);
public:
	AimPointer(b2World* world, SGE::Reactive* aimer, Pointer* pointer, SGE::MouseObject* mouse, SGE::Camera2d* cam, std::size_t& counter, float range);
	void performLogic() override;
};

namespace SGE
{
	class Scene;
}

class WinCondition : public SGE::Logic
{
protected:
	volatile size_t& zombies;
	volatile size_t& killedZombies;
	SGE::Scene* endGame = nullptr;
public:
	WinCondition(size_t& zombies, size_t& killedZombies, SGE::Scene* endGame);
	virtual void performLogic() override;
};
#endif
