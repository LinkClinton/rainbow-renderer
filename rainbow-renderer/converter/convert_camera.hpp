#pragma once

#include "meta-scene/objects/camera.hpp"
#include "meta-scene/objects/film.hpp"

#include "rainbow-cpu/cameras/camera.hpp"
#include "rainbow-cpu/cameras/film.hpp"

using namespace rainbow::cpus::cameras;

namespace rainbow::renderer::converter {

	std::shared_ptr<film> create_film(const meta_scene::objects::film& film);

	std::shared_ptr<camera> create_camera(
		const meta_scene::objects::camera& camera,
		const meta_scene::objects::film& film);
	
}