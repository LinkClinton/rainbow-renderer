#pragma once

#include "meta-scene/scene.hpp"

#include "rainbow-cpu/integrators/integrator.hpp"
#include "rainbow-cpu/cameras/camera.hpp"
#include "rainbow-cpu/scenes/scene.hpp"

using namespace rainbow::cpus::integrators;
using namespace rainbow::cpus::cameras;
using namespace rainbow::cpus::scenes;

namespace rainbow::renderer {

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
