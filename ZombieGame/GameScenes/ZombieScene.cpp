﻿#include <fstream>
#include <set>
#include <functional>

#include "ZombieScene.hpp"
#include "Logics.hpp"
#include "Actions.hpp"

#include <Logic/Logics/Colliders/sge_logic_collide_level_precise.hpp>
#include <Logic/Logics/Movers/sge_logic_move.hpp>
#include <Logic/Logics/Camera/sge_logic_camera_zoom.hpp>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Logic/Logics/World/sge_worldstep.hpp>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Game/Director/sge_director.hpp>


bool CullingListener::cull(b2Fixture* A, b2Fixture* B)
{
	if(isCat(A, Category::Camera) && !B->IsSensor())
	{
		SGE::Object* o = reinterpret_cast<SGE::Object*>(B->GetUserData());
		o->setVisible(true);
		return true;
	}
	if(isCat(B, Category::Camera) && !A->IsSensor())
	{
		SGE::Object* o = reinterpret_cast<SGE::Object*>(A->GetUserData());
		o->setVisible(true);
		return true;
	}
	return false;
}

bool CullingListener::uncull(b2Fixture* A, b2Fixture* B)
{
	if (isCat(A, Category::Camera) && !B->IsSensor())
	{
		SGE::Object* o = reinterpret_cast<SGE::Object*>(B->GetUserData());
		o->setVisible(false);
		return true;
	}
	if (isCat(B, Category::Camera) && !A->IsSensor())
	{
		SGE::Object* o = reinterpret_cast<SGE::Object*>(A->GetUserData());
		o->setVisible(false);
		return true;
	}
	return false;
}

void CullingListener::BeginContact(b2Contact* contact)
{
	b2Fixture* A = contact->GetFixtureA();
	b2Fixture* B = contact->GetFixtureB();
	this->cull(A, B);
}

void CullingListener::EndContact(b2Contact* contact)
{
	b2Fixture* A = contact->GetFixtureA();
	b2Fixture* B = contact->GetFixtureB();
	this->uncull(A, B);
}

void ZListener::BeginContact(b2Contact* contact)
{
	b2Fixture* A = contact->GetFixtureA();
	b2Fixture* B = contact->GetFixtureB();
	if(this->cull(A, B))
	{
		return;
	}
	if (isCat(A, Category::Human) && isCat(B, Category::ZombieSensor))
	{
		reinterpret_cast<Human*>(B->GetUserData())->getBodies().push_front(reinterpret_cast<Human*>(A->GetUserData()));
	}
	else if (isCat(A, Category::ZombieSensor) && isCat(B, Category::Human))
	{
		reinterpret_cast<Human*>(A->GetUserData())->getBodies().push_front(reinterpret_cast<Human*>(B->GetUserData()));
	}
	else if (isCat(A, Category::Zombie) && isCat(B, Category::HumanSensor))
	{
		reinterpret_cast<Human*>(B->GetUserData())->getBodies().push_front(reinterpret_cast<Human*>(A->GetUserData()));
	}
	else if (isCat(A, Category::HumanSensor) && isCat(B, Category::Zombie))
	{
		reinterpret_cast<Human*>(B->GetUserData())->getBodies().push_front(reinterpret_cast<Human*>(A->GetUserData()));
	}
	else if (isCat(A, Category::Human) && isCat(B, Category::Zombie))
	{
		reinterpret_cast<Human*>(A->GetUserData())->Zombify();
	}
	else if (isCat(A, Category::Zombie) && isCat(B, Category::Human))
	{
		reinterpret_cast<Human*>(B->GetUserData())->Zombify();
	}
}//We really need a better way of texturing objects
void ZListener::EndContact(b2Contact* contact)
{
	b2Fixture* A = contact->GetFixtureA();
	b2Fixture* B = contact->GetFixtureB();
	if (this->uncull(A, B))
	{
		return;
	}
	if (isCat(A, Category::Human) && isCat(B, Category::ZombieSensor))
	{
		reinterpret_cast<Human*>(B->GetUserData())->getBodies().remove(reinterpret_cast<Human*>(A->GetUserData()));
	}
	else if (isCat(A, Category::ZombieSensor) && isCat(B, Category::Human))
	{
		reinterpret_cast<Human*>(A->GetUserData())->getBodies().remove(reinterpret_cast<Human*>(B->GetUserData()));
	}
	else if (isCat(A, Category::Zombie) && isCat(B, Category::HumanSensor))
	{
		reinterpret_cast<Human*>(B->GetUserData())->getBodies().remove(reinterpret_cast<Human*>(A->GetUserData()));
	}
	else if (isCat(A, Category::HumanSensor) && isCat(B, Category::Zombie))
	{
		reinterpret_cast<Human*>(B->GetUserData())->getBodies().remove(reinterpret_cast<Human*>(A->GetUserData()));
	}
}

SGE::GLTexture ZombieScene::zombieTexture;
SGE::GLTexture ZombieScene::deadZombieTexture;
SGE::GLTexture ZombieScene::deadHumanTexture;
b2Filter ZombieScene::zombieFilter;
b2Filter ZombieScene::zombieSensorFilter;
b2Filter ZombieScene::playerFilter;
b2Filter ZombieScene::humanFilter;
b2Filter ZombieScene::humanSensorFilter;
b2CircleShape ZombieScene::sensorShape;
b2FixtureDef ZombieScene::sensorFixture;
b2BodyDef ZombieScene::humanBodyDef;
b2CircleShape ZombieScene::humanShape;
b2PolygonShape ZombieScene::worldShape;
b2BodyDef ZombieScene::worldBodyDef;
b2Filter ZombieScene::worldFilter;

bool ZombieScene::init()
{
	playerFilter.categoryBits = uint16(Category::Player);
	playerFilter.maskBits = Category::Player | Category::Human | Category::Zombie | Category::Level | Category::Camera;

	zombieFilter.categoryBits = uint16(Category::Zombie);
	zombieFilter.maskBits = Category::Player | Category::Human | Category::Zombie | Category::Level | Category::HumanSensor | Category::Camera;

	zombieSensorFilter.categoryBits = uint16(Category::ZombieSensor);
	zombieSensorFilter.maskBits = uint16(Category::Human);

	humanFilter.categoryBits = uint16(Category::Human);
	humanFilter.maskBits = Category::Player | Category::Human | Category::Zombie | Category::Level | Category::ZombieSensor | Category::Camera;

	humanSensorFilter.categoryBits = uint16(Category::HumanSensor);
	humanSensorFilter.maskBits = uint16(Category::Zombie);

	sensorShape.m_p = b2Vec2_zero;
	sensorShape.m_radius = 5;

	sensorFixture.isSensor = true;
	sensorFixture.shape = &sensorShape;

	humanBodyDef.fixedRotation = true;
	humanBodyDef.type = b2_dynamicBody;

	humanShape.m_radius = 0.5f;
	humanShape.m_p = b2Vec2_zero;

	worldBodyDef.type = b2_staticBody;
	worldShape.SetAsBox(0.5f, 0.5f);

	worldFilter.categoryBits = uint16(Category::Level);
	worldFilter.maskBits = Category::Player | Category::Human | Category::Zombie | Category::Camera | Category::Corpse;

	return true;
}

void ZombieScene::zombify(Human* human)
{
	++this->zombieCount;
	b2Body* body = human->getBody();
	for(b2Fixture* next = body->GetFixtureList(), *temp = nullptr; next!=nullptr ; next=temp)
	{
		temp = next->GetNext();
		body->DestroyFixture(next);
	}
	human->texture = zombieTexture;
	human->setSpeed(3);
	human->addFixture(sensorFixture)->SetFilterData(zombieSensorFilter);
	human->addFixture(humanShape)->SetFilterData(zombieFilter);
}

ZombieScene::ZombieScene(SGE::Game* game, const char* path)
		: Box2DScene(b2Vec2_zero), game(game),
		  path([game](const char* path) { return game->getGamePath() + path; }(path))
{
	static bool initialized = init();
}

void ZombieScene::loadScene()
{
	this->killCount = 0;
	this->zombieCount = 0;
	std::map<char, std::string> mask = {
		{ 'R', {game->getGamePath() + "Resources/Textures/red_bricks.png"} },
		{ 'B', {game->getGamePath() + "Resources/Textures/red_bricks.png"} },
		{ 'G', {game->getGamePath() + "Resources/Textures/glass.png"} },
		{ 'L', {game->getGamePath() + "Resources/Textures/light_bricks.png"} }
	};
	this->Scene::loadLevel(this->path.c_str(), mask);

	for(SGE::WorldElement& e: this->getLevel().getWorld())
	{
		b2Body* body = world.CreateBody(&worldBodyDef);
		body->SetTransform(b2Vec2(e.getX()/64.f, e.getY()/64.f), 0);
		b2Fixture* worldfix = body->CreateFixture(&worldShape, 0);
		worldfix->SetFilterData(worldFilter);
		worldfix->SetUserData(&e);
	}

	SGE::Object* Dummy1 = new Image(-1000, -1000);
	game->textureObject(Dummy1, "Resources/Textures/deadzombie.png");
	deadZombieTexture = Dummy1->texture;
	this->addObject(Dummy1);
	SGE::Object* Dummy2 = new Image(-1000, -1000);
	game->textureObject(Dummy2, "Resources/Textures/deadhuman.png");
	deadHumanTexture = Dummy2->texture;
	this->addObject(Dummy2);

	SGE::Camera2d* camera = game->getCamera();
	camera->setScale(0.5f);
	SGE::MouseObject* mouse = game->getMouse();

	Player* player = new Player(200, 200,true,getCircle());

	auto L3 = new SimpleMove(player, 6, SGE::Key::W, SGE::Key::S, SGE::Key::A, SGE::Key::D);

	auto camLogic = new SnapCamera(8, SGE::Key::Up, SGE::Key::Down, SGE::Key::Left, SGE::Key::Right, SGE::Key::O, player, camera);
	auto camZoom = new SGE::Logics::CameraZoom(camera, 0.1f, 0.5f, 0.15f, SGE::Key::Q, SGE::Key::E);

	this->addLogic(L3);
	this->addLogic(camLogic);
	this->addLogic(camZoom);
	this->addLogic(new SGE::WorldStep(&this->world));
	
	std::vector<std::string> l;
	std::fstream is;
	is.open(path);
	std::string s;
	is >> s;
	while (is >> s)
	{
		l.push_back(s);
	}

	std::pair<int, int> portal_location;
	std::vector<std::pair<float, float>> free;
	int x = 0, y = 0; const int w = 64, h = 64;

	for (auto& ee : l)
	{
		for (auto& e : ee)
		{
			if (e == '.')
			{
				free.push_back(std::make_pair(float(x * w), float(y * h)));
			}
			else if (e == '*') {
				portal_location = std::make_pair(x * w, y * h);
			}
			x++;
		}y++;
		x = 0;
	}

	const int humans = 100;
	srand(time(NULL));

	std::set<int> r;
	for (int i = 0; i < humans; i++)
	{
		int index = rand() % free.size();
		r.insert(index);
	}

	for (const int& e : r)
	{
		std::pair<float, float> pos = free.at(e);
		Human* temp = new Human(pos.first, pos.second, 60 + rand() % 120);
		game->textureObject(temp, "Resources/Textures/circle.png");
		this->addReactive(temp,&humanBodyDef);
		temp->setPosition(pos.first, pos.second);
		this->humans.push_back(temp);
		temp->addFixture(sensorFixture)->SetFilterData(humanSensorFilter);
		temp->addFixture(humanShape)->SetFilterData(humanFilter);
	}

	this->zombify(this->humans.at(0));
	game->textureObject(this->humans.at(0), "Resources/Textures/zombie.png");
	zombieTexture = this->humans.at(0)->texture;
	this->humans.at(0)->Zombify();

	this->addLogic(new HumanMovement(&this->humans,std::bind(&ZombieScene::zombify,this,std::placeholders::_1),&world));

	world.SetContactListener(new ZListener());

	Pointer* pointer = new Pointer();
	this->addObject(pointer);
	this->game->textureObject(pointer, "Resources/Textures/pointer.png");
	
	this->addLogic(new AimPointer(&this->world, player, pointer, mouse, camera, this->killCount, 8));
	this->addLogic(new WinCondition(this->zombieCount, this->killCount, endScene));

	//Puts player on top
	game->textureObject(player, "Resources/Textures/player.png");
	this->addReactive(player, &humanBodyDef);
	player->setPosition(200, 200);
	//Will hijack player for now
	b2PolygonShape camBox;
	b2FixtureDef camFixtureDef;
	camBox.SetAsBox(camera->getWidth()/64.f, camera->getHeight()/64.f);
	camFixtureDef.shape = &camBox;
	camFixtureDef.isSensor = true;
	camFixtureDef.filter.categoryBits = (unsigned short)(Category::Camera);
	auto cf = player->addFixture(camFixtureDef);
	cf->SetUserData(camera);
	cf->GetBody()->SetSleepingAllowed(false);
	player->setVisible(true);
	//Generalize this after finals
	player->addFixture(humanShape);
	player->getBody()->SetLinearDamping(16);
	player->getBody()->GetFixtureList()->SetFilterData(playerFilter);



}

void ZombieScene::unloadScene()
{
	while (this->world.GetBodyList())
	{
		this->world.DestroyBody(this->world.GetBodyList());
	}
	this->finalize();
}

ZombieScene::~ZombieScene()
{
	std::cout << "~MainScene" << std::endl;
}

template<typename Vec>
void vec_clear(Vec& vec)
{
	for (auto h : vec)
	{
		delete h;
	}
	vec.clear();
}

void ZombieScene::finalize()
{
	this->level.clear();
	this->humans.clear();
	vec_clear(this->getLogics());
	vec_clear(this->getActions());
	vec_clear(this->getObjects());
}

void ZombieScene::onDraw()
{
}

void ZombieScene::addReactive(SGE::Reactive* object, const b2BodyDef* bodyDef)
{
	this->Scene::addObject(object);
	object->setBody(this->world.CreateBody(bodyDef));
}
