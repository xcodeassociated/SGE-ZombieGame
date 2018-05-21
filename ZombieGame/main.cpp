//
//  main.cpp
//  ZombieGame
//
//  Created by Hamashy on 13.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#include <iostream>
#include <boost/filesystem.hpp>

#include <entt/entt.hpp>
#include <cstdint>

#include <Game/sge_game.hpp>
#include <Game/Director/sge_director.hpp>
#include <Scene/sge_scene.hpp>

#include "ZombieScene.hpp"
#include "IntroScene.hpp"

namespace fs = boost::filesystem;

/* <entt example> */
struct Position {
	float x;
	float y;
};

struct Velocity {
	float dx;
	float dy;
};

void update(entt::DefaultRegistry &registry) {
	auto view = registry.view<Position, Velocity>();

	for (auto entity : view) {
		// gets only the components that are going to be used ...

		auto &velocity = view.get<Velocity>(entity);

		velocity.dx = 0.;
		velocity.dy = 0.;

		// ...
	}
}

void update(std::uint64_t dt, entt::DefaultRegistry &registry) {
	registry.view<Position, Velocity>().each([dt](auto entity, auto &position, auto &velocity) {
		// gets all the components of the view at once ...

		position.x += velocity.dx * dt;
		position.y += velocity.dy * dt;

		// ...
	});
}
/* </entt_example> */

int main(int argc, char * argv[])
{
    (void)argc; (void)argv;

	/* <entt example> */
	{
		entt::DefaultRegistry registry;
		std::uint64_t dt = 16;

		for (auto i = 0; i < 10; ++i)
		{
			auto entity = registry.create();
			registry.assign<Position>(entity, i * 1.f, i * 1.f);
			if (i % 2 == 0) { registry.assign<Velocity>(entity, i * .1f, i * .1f); }
		}

		update(dt, registry);
		update(registry);
	}
	/* </entt_example> */

    std::cout.setf(std::ios::boolalpha);
    std::cout.sync_with_stdio(true);

	const fs::path app_path = fs::system_complete(argv[0]).remove_filename();
	const fs::path shader_path = app_path / fs::path("shaders");

	SGE::Director* director = SGE::Director::getDirector(1024, 768);
	SGE::Game* game = SGE::Game::getGame();
	game->bindDirector(director);
	game->init(60, shader_path.string());
	game->setGamePath({app_path.string() + '/'});

	ZombieScene* S1 = new ZombieScene(game, "Levels/level1.txt");
	SGE::Scene* S0 = new IntroScene(S1, "Resources/Textures/zombie-game.png");
	SGE::Scene* S2 = new EndScene(S1, "Resources/Textures/end-game.png");
	
	S1->endScene = S2;

	director->addScene(S0);
	director->addScene(S1);
	director->addScene(S2);

	director->setNextScene(S0);
	
	game->run();

	director->deleteScene(S0);
	director->deleteScene(S1);
	director->deleteScene(S2);
	
	game->finalize();
	director->finalize();

    return 0;
}
