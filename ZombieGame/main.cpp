#include <iostream>
#include <cstdint>
#include <tuple>
#include <memory>
#include <boost/filesystem.hpp>

#include <entt/entt.hpp>

#include <RenderSystem/sge_renderer.hpp>
#include <RenderSystem/Window/sge_window.hpp>
#include <Camera2d/sge_camera2d.hpp>
#include <RenderSystem/Texture/sge_texture_cache.hpp>
#include <Shape/sge_shape.hpp>
#include <Shape/sge_shape_circle.hpp>
#include <Shape/sge_shape_rectangle.hpp>
#include <Sprite/sge_sprite.hpp>

#include "SDL.h"
#include "RenderSystem/Vertex/sge_vertex.hpp"

namespace fs = boost::filesystem;
int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;

	std::cout.setf(std::ios::boolalpha);
	std::cout.sync_with_stdio(true);

 	const fs::path app_path = fs::system_complete(argv[0]).remove_filename();
	const fs::path shader_path = app_path / fs::path("shaders");

	SGE::Color window_color{255, 255, 255, 255};
	SGE::Window window({800, 600});
	window.createWindow(window_color);
		
	SGE::Camera2d camera{800, 600};
	camera.setPosition(0, 0);
	camera.setScale(1);
    camera.update();

    SGE::TextureCache* texture_cache = SGE::TextureCache::getSingleton();
	SGE::Renderer renderer((shader_path / "colorShader.vert").string(), 
		(shader_path / "colorShader.frag").string(), {800, 600});

	window.showWindow();

    SGE::Texture sprite0_texture;
	sprite0_texture.path = (app_path / "Resources/Textures/red_bricks.png").string();
	sprite0_texture.texture = texture_cache->getTexture(sprite0_texture.path.c_str());
	std::unique_ptr<SGE::Rectangle> rect = std::make_unique<SGE::Rectangle>(32, 32);
	SGE::Shape* sprite0_shape = rect.get();
	SGE::Sprite sprit0(-32.f, 0.f, sprite0_shape, &sprite0_texture);
	sprit0.setVisible(true);
	sprit0.setDrawable(true);

	SGE::Texture sprite1_texture;
	sprite1_texture.path = (app_path / "Resources/Textures/zombie.png").string();
	sprite1_texture.texture = texture_cache->getTexture(sprite1_texture.path.c_str());
	std::unique_ptr<SGE::Circle> circle = std::make_unique<SGE::Circle>(16);
	SGE::Shape* sprite1_shape = circle.get();
	SGE::Sprite sprit1(32.f, 0.f, sprite1_shape, &sprite1_texture);
	sprit1.setVisible(true);
	sprit1.setDrawable(true);

	// Game Loop
	bool quit = false;
	while (!quit) {
		// IO	
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		// Render 
		camera.update();

		renderer.setContext(&camera);
		
		glm::vec4 uv(.0f, .0f, 1.0f, 1.0f);
		SGE::Color color(255, 255, 255, 255);

		renderer.render(&sprit0, uv, color);
		renderer.render(&sprit1, uv, color);

		renderer.usetContext(0, window.getWindow());
    }

	// quit...
	std::cout << "finished" << std::endl;
	SDL_Quit();

	return 0;
}
