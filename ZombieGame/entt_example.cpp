#include <iostream>
#include <cstdint>
#include <tuple>
#include <entt/entt.hpp>

/* <entt example> */
struct c_Position {
	double x = 0;
	double y = 0;
};

struct c_Velocity {
	double dx = 0;
	double dy = 0;
};

void s_update(entt::DefaultRegistry &registry) {
	// create view fo the register -- c_Position & c_Velocity are all of the components
	//      cannot be reduced -- all used components in the register as the template parameters
	auto view = registry.view<c_Position, c_Velocity>();

	// iterate over the view -> enitity after entity
	for (auto entity : view) {

		// get component `velocity` instance from created view
		auto &velocity = view.get<c_Velocity>(entity);

		velocity.dx *= 1.f;
		velocity.dy *= 1.f;

		std::tuple<c_Position&, c_Velocity&> elem = view.get<c_Position, c_Velocity>(entity);
		std::get<1>(elem).dx *= 1.f;
		std::get<1>(elem).dy *= 1.f;
	}
}

void s_update(std::uint64_t dt, entt::DefaultRegistry &registry) {
	// gets all the components of the view at once using `each` -- format: entity, COMP_1, (...), COMP_n
	//      cannot be reduced -- all used components in the register as the template parameters
	registry.view<c_Position, c_Velocity>().each([dt](auto entity, auto &position, auto &velocity) {
		position.x += velocity.dx * dt;
		position.y += velocity.dy * dt;

	});

}

void s_printout_position(entt::DefaultRegistry &registry) {
	// TODO: it would be nice to have a logger able to print all the entity data and components to some kind of JSON format
	registry.view<c_Position>().each([](const auto& entity, const auto& position) {
		std::cout << "{ entity: " << entity << ": position: { x: " << position.x << ", y: " << position.y
			<< " } }" << std::endl;
	});
}

void s_printout_has_velocity(entt::DefaultRegistry &registry) {
	registry.view<c_Position, c_Velocity>().each([](const auto& entity, const auto& position, const auto& velocity) {
		std::cout << "{ entity: " << entity << ": position: { x: " << position.x << ", y: " << position.y
			<< " }, velocity: { dx: " << velocity.dx << ", dy: " << velocity.dy << " } }" << std::endl;
	});
}

#ifndef _WINDOWS
void velocity_create_callback(entt::DefaultRegistry &registry, entt::DefaultRegistry::entity_type entity) {
	std::cout << "c_Velocity created! - function" << std::endl;
}

// callback manager class for `c_Velocity` component
struct CallbackManager {
	void velocity_create_callback(entt::DefaultRegistry &registry, entt::DefaultRegistry::entity_type entity) {
		std::cout << " c_Velocity created! - instance" << std::endl;
	};
};
#endif

void s_remove_velocity(entt::DefaultRegistry &registry) {
	auto view = registry.view<c_Velocity>();
	for (auto entity : view) {
		// remove `velocity` component form entity
		registry.remove<c_Velocity>(entity);
	}
}

void s_iterate_over_each(entt::DefaultRegistry &registry) {
	registry.each([&registry](auto entity) {

		// check if entity has component `c_Velocity` and replace with new one, if entity doesn't have it add new
		if (registry.has<c_Velocity>(entity)) {
			auto e = registry.replace<c_Velocity>(entity, 1., 1.);
			(void)e;
		}
		else {
			auto e = registry.assign<c_Velocity>(entity, 1., 1.);
			(void)e;
		}

#ifndef _WINDOWS
		// the same functionality can be done using accomadate
		// a) pass args to the call
		registry.accommodate<c_Velocity>(entity, 1., 1.);

		// b) make c_Velocity instance ant modify atributes later
		c_Velocity &velocity = registry.accommodate<c_Velocity>(entity);
		velocity.dx = 1.;
		velocity.dy = 1.;
#endif
	});
}

#ifndef _WINDOWS
void s_iterate_orphans(entt::DefaultRegistry &registry) {
	registry.orphans([](auto entity) {
		std::cout << "orphan: " << entity << std::endl;
	});
}

void s_iterate_using_persistant_view(entt::DefaultRegistry &registry) {
	// view should be saved somehow -- `persistent` means that the view container is prepared and created only once, 
	// so it can increase performance if iterating over static entity sets
	auto view = registry.view<c_Position, c_Velocity>(entt::persistent_t{});
	for (auto entity : view) {
		(void)entity;
	}
}

void s_iterate_using_raw_view(entt::DefaultRegistry &registry) {
	auto raw = registry.view<c_Position>(entt::raw_t{});
	for (auto && component : raw) {
		(void)component;
	}
}
#endif

// NOTE: Only core `entt` features works on WINDOWS! 
// TODO:
// serialize -- can be used to save game state (game dump)
// identifires 
// resource manager & scheduler-process
// signals delegate & event dispatcher

/* </entt_example> */

int main(int argc, char * argv[])
{
	(void)argc;
	(void)argv;

	std::cout.setf(std::ios::boolalpha);
	std::cout.sync_with_stdio(true);

	/* <entt example> */
	{
		// create default registry for the ECS
		entt::DefaultRegistry registry;

#ifndef _WINDOWS
		// add component dependencies -- add c_Velocity when c_Position is assiged to the entity
		entt::dependency<c_Velocity>(registry.construction<c_Position>());

		// remove component dependencies
		entt::dependency<c_Velocity>(entt::break_t{}, registry.construction<c_Position>());

		// register callback for `c_Velocity` component - if the component is created the callback function will be triggered
		registry.construction<c_Velocity>().connect<&velocity_create_callback>();

		// register callback member function form callback manager
		CallbackManager callbackManager;
		registry.construction<c_Velocity>().connect<CallbackManager, &CallbackManager::velocity_create_callback>(&callbackManager);

		// dissconnect `c_Velocity` create callback function (uncomment)
		registry.construction<c_Velocity>().disconnect<&velocity_create_callback>();
#endif

		//some value to used by system
		std::uint64_t dt = 1;

		for (auto i = 0; i < 10; ++i)
		{
			// create entity
			auto entity = registry.create();

			// assigne component
			registry.assign<c_Position>(entity, i * 1.f, i * 1.f);

			// assigne `velocity component` to the even enities
			if (i % 2 == 0) {
				if (!registry.has<c_Velocity>(entity)) {
					auto v = registry.assign<c_Velocity>(entity, i * 1.f, i * 1.f);

					// let's check replace the `velocity` on the same one
					auto v_r = registry.replace<c_Velocity>(entity, i * 1.f, i * 1.f);
				}
			}
		}

		// assigne one more enitity -- without any component - orphans to iterate
		auto empty_entity = registry.create();
		(void)empty_entity;

		// sort the entities by pos.x -- note: this will be seen only when iterating over the view with `Postion` only,
		//      entities that has also velocity will not be affected
		registry.sort<c_Position>([](const auto &lhs, const auto &rhs) {
			return lhs.x < rhs.y;
		});

		// sort the entities with `velocity` as well. if the above sort will not be present only view that has c_Velocity will be sorted.
		//      the view with `c_Position` only will not be sorted.
		registry.sort<c_Velocity>([](const auto &lhs, const auto &rhs) {
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


		// other way for iterating over the entities in the registry
		s_iterate_over_each(registry);

#ifndef _WINDOWS
		// iterate over `orphans1 in registry -- entities that have no assigned components 
		s_iterate_orphans(registry);

		// iterate over entities in the registry using persistent view
		s_iterate_using_persistant_view(registry);

		// iterate over the entities using raw view
		s_iterate_using_raw_view(registry);
#endif

	}

#ifdef _WINDOWS
	system("pause");
#endif
	return 0;
}
