#pragma once

#include "meta-scene/scene.hpp"

#include "rainbow/integrators/integrator.hpp"
#include "rainbow/cameras/camera.hpp"
#include "rainbow/scenes/scene.hpp"

namespace rainbow {

	using namespace integrators;
	using namespace cameras;
	using namespace scenes;
	
	namespace renderer {

		struct renderer_scene final {
			std::shared_ptr<integrator> integrator;
			std::shared_ptr<camera> camera;
			std::shared_ptr<scene> scene;
			std::shared_ptr<film> film;

			renderer_scene() = default;

			void render_to(const std::string& filename) const;
		};

		renderer_scene create_from_meta_scene(const std::shared_ptr<metascene::scene>& meta_scene);
	}	
}
