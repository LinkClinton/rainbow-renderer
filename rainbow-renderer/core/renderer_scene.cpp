#include "renderer_scene.hpp"

#include "../converter/convert_integrator.hpp"
#include "../converter/convert_camera.hpp"
#include "../converter/convert_scene.hpp"

namespace rainbow::renderer {

	void renderer_scene::render_to(const std::string& filename) const
	{
		scene->build_accelerator();
	
		integrator->render(camera, scene);

		film->write(filename);
	}
	
	renderer_scene create_from_meta_scene(const std::shared_ptr<metascene::scene>& meta_scene)
	{
		renderer_scene scene;

		scene.integrator = converter::create_integrator(meta_scene->integrator, meta_scene->sampler);
		scene.camera = converter::create_camera(meta_scene->camera, meta_scene->film);
		scene.scene = converter::create_scene(meta_scene);
		scene.film = scene.camera->film();
		
		return scene;
	}

	
}