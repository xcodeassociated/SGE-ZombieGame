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

#include "GameCode/ZombieScene.hpp"
#include "GameCode/IntroScene.hpp"

namespace fs = boost::filesystem;

/* <entt example> */
struct Position {
	double x = 0;
    double y = 0;
};

struct Velocity {
    double dx = 0;
    double dy = 0;
};

void s_update(entt::DefaultRegistry &registry) {
	// create view fo the register -- Position & Velocity are all of the components
    //      cannot be reduced -- all used components in the register as the template parameters
    auto view = registry.view<Position, Velocity>();

    // iterate over the view -> enitity after entity
	for (auto entity : view) {

	    // get component `velocity` instance from created view
		auto &velocity = view.get<Velocity>(entity);

		velocity.dx *= 1.f;
		velocity.dy *= 1.f;

		std::tuple<Position&, Velocity&> elem = view.get<Position, Velocity>(entity);
		std::get<1>(elem).dx *= 1.f;
        std::get<1>(elem).dy *= 1.f;
	}
}

void s_update(std::uint64_t dt, entt::DefaultRegistry &registry) {
    // gets all the components of the view at once using `each` -- format: entity, COMP_1, (...), COMP_n
    //      cannot be reduced -- all used components in the register as the template parameters
    registry.view<Position, Velocity>().each([dt](auto entity, auto &position, auto &velocity) {
		position.x += velocity.dx * dt;
		position.y += velocity.dy * dt;

	});

}

void s_printout_position(entt::DefaultRegistry &registry) {
    registry.view<Position>().each([](const auto& entity, const auto& position) {
        std::cout << "{ entity: " << entity << ": position: { x: " << position.x << ", y: " << position.y
                  << " } }" << std::endl;
    });
}

void s_printout_has_velocity(entt::DefaultRegistry &registry) {
    registry.view<Position, Velocity>().each([](const auto& entity, const auto& position, const auto& velocity) {
        std::cout << "{ entity: " << entity << ": position: { x: " << position.x << ", y: " << position.y
                  << " }, velocity: { dx: " << velocity.dx <<  ", dy: " << velocity.dy << " } }" << std::endl;
    });
}

void velocity_create_callback(entt::DefaultRegistry &registry, entt::DefaultRegistry::entity_type entity) {
    std::cout << __PRETTY_FUNCTION__ << ": Velocity created! - function" << std::endl;
}

// callback manager class for `Velocity` component
struct CallbackManager {
	void velocity_create_callback(entt::DefaultRegistry &registry, entt::DefaultRegistry::entity_type entity) {
		std::cout << __PRETTY_FUNCTION__ << ": Velocity created! - instance" << std::endl;
	};
};

void s_remove_velocity(entt::DefaultRegistry &registry) {
	auto view = registry.view<Velocity>();
	for (auto entity : view) {
		// remove `velocity` component form entity
		registry.remove<Velocity>(entity);
	}
}

void s_iterate_over_each(entt::DefaultRegistry &registry) {
    registry.each([&registry](auto entity) {

        // check if entity has component `Velocity` and replace with new one, if entity doesn't have it add new
        if(registry.has<Velocity>(entity)) {
            auto e = registry.replace<Velocity>(entity, 1., 1.);
            (void)e;
        } else {
            auto e = registry.assign<Velocity>(entity, 1., 1.);
            (void)e;
        }

        // the same functionality can be done using accomadate
        // a) pass args to the call
        registry.accommodate<Velocity>(entity, 1., 1.);

        // b) make Velocity instance ant modify atributes later
        Velocity &velocity = registry.accommodate<Velocity>(entity);
        velocity.dx = 1.;
        velocity.dy = 1.;
    });
}

void s_iterate_orphans(entt::DefaultRegistry &registry) {
    registry.orphans([](auto entity) {

    });
}

void s_iterate_using_persistant_view(entt::DefaultRegistry &registry) {
    static auto view = registry.view<Position, Velocity>(entt::persistent_t{});
    for (auto entity : view) {

    }
}

void s_iterate_using_raw_view(entt::DefaultRegistry &registry) {
    auto raw = registry.view<Position>(entt::raw_t{});
    for (auto && component : raw) {

    }
}

/// TODO:
// serialize
// identifires
// resource manager & scheduler-process
// signals delegate & event dispatcher

/* </entt_example> */

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;

	/* <entt example> */
	{
	    // create default registry for the ECS
		entt::DefaultRegistry registry;



		// add component dependencies -- add Velocity when Position is assiged to the entity
        entt::dependency<Velocity>(registry.construction<Position>());

        // remove component dependencies
        entt::dependency<Velocity>(entt::break_t{}, registry.construction<Position>());



        // register callback for `Velocity` component - if the component is created the callback function will be triggered
        registry.construction<Velocity>().connect<&velocity_create_callback>();

        // register callback member function form callback manager
        CallbackManager callbackManager;
		registry.construction<Velocity>().connect<CallbackManager, &CallbackManager::velocity_create_callback>(&callbackManager);

		// dissconnect `Velocity` create callback function (uncomment)
		//registry.construction<Velocity>().disconnect<&velocity_create_callback>();


		//some value to used by system
		std::uint64_t dt = 1;

		for (auto i = 0; i < 10; ++i)
		{
			// create entity
		    auto entity = registry.create();

		    // assigne component
			registry.assign<Position>(entity, i * 1.f, i * 1.f);

			// assigne `velocity component` to the even enities
			if (i % 2 == 0) {
                if(!registry.has<Velocity>(entity)) {
                    auto v = registry.assign<Velocity>(entity, i * 1.f, i * 1.f);

                    // let's check replace the `velocity` on the same one
                    auto v_r = registry.replace<Velocity>(entity, i * 1.f, i * 1.f);
                }
			}
		}

		// assigne one more enitity -- without any component - orphans to iterate
        auto empty_entity = registry.create();
        (void)empty_entity;

		// sort the entities by pos.x -- note: this will be seen only when iterating over the view with `Postion` only,
		//      entities that has also velocity will not be affected
        registry.sort<Position>([](const auto &lhs, const auto &rhs) {
            return lhs.x < rhs.y;
        });

		// sort the entities with `velocity` as well. if the above sort will not be present only view that has Velocity will be sorted.
        //      the view with `Position` only will not be sorted.
        registry.sort<Velocity>([](const auto &lhs, const auto &rhs) {
            return lhs.dx < rhs.dx;
        });

 		// invoke system update with given param -- first iterate over `velocity` and update the components
		s_update(dt, registry);

		// invoke system update no params -- scond iterate over `velocity` and `position` to update position using velocity
		s_update(registry);




		// print out system -- all enities - all have `position`
        s_printout_position(registry);

            std::cout << std::endl;

		// print out system -- entities that has `velocity` - even
        s_printout_has_velocity(registry);


        s_remove_velocity(registry);
		s_remove_velocity(registry); // can be called many times - this time there is no `velocity` so the view is empty


            std::cout << std::endl;

        // print out system -- entities that has `velocity` - even, but now the component is removed, so no entity will be printed
        s_printout_has_velocity(registry);


        s_iterate_over_each(registry);
        s_iterate_orphans(registry);
        s_iterate_using_persistant_view(registry);
        s_iterate_using_raw_view(registry);

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
