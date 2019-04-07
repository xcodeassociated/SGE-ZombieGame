//
//  main.cpp
//  ZombieGame
//
//  Created by Hamashy on 13.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#include <iostream>
#include <cstdint>
#include <tuple>
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

namespace fs = boost::filesystem;

int main(int argc, char * argv[])
{
    (void)argc;
    (void)argv;
	
	std::cout.setf(std::ios::boolalpha);
	std::cout.sync_with_stdio(true);

	const fs::path app_path = fs::system_complete(argv[0]).remove_filename();
	const fs::path shader_path = app_path / fs::path("shaders");

	SGE::Color window_color(0, 0, 0, 1);
	SGE::Window window({ 800, 600 });
	window.createWindow(window_color);
	
	SGE::Camera2d camera(800, 600);
	camera.setPosition(0, 0);
	camera.setScale(1);

	SGE::TextureCache* texture_cache = SGE::TextureCache::getSingleton();

	SGE::Texture sprite0_texture;
	sprite0_texture.path = (app_path / "Resources/Textures/circle.png").string();
	sprite0_texture.texture = texture_cache->getTexture(sprite0_texture.path.c_str());

	SGE::Renderer renderer((shader_path / "colorShader.vert").string(), (shader_path / "colorShader.frag").string(), {800, 600});
	window.showWindow();

	SGE::Circle circle(0.5);
	SGE::Shape* sprite0_shape = &circle;
	SGE::Sprite sprit0(0.0f, 0.0f, sprite0_shape, &sprite0_texture);
	sprit0.setVisible(true);
	sprit0.setDrawable(true);

	camera.update();
	renderer.setContext(&camera);

	//while (true) {

		static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
		static SGE::Color color(255, 255, 255, 255);
		SGE::Rectangle tile(64, 64, 0);
		const float width = tile.getWidth();
		const float height = tile.getHeight();
		glm::vec4 destRect(sprit0.getX() - width * .5f, sprit0.getY() - height * .5f, width, height);

		renderer.render(&sprit0, uv, color, destRect);

	//}
	renderer.usetContext(0, window.getWindow());


#ifdef _WINDOWS
	system("pause");
#endif
    return 0;
}
