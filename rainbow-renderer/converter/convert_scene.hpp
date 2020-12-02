#pragma once

#include "meta-scene/scene.hpp"

#include "rainbow-cpu/scenes/entity.hpp"
#include "rainbow-cpu/scenes/scene.hpp"

using namespace rainbow::cpus::scenes;

namespace rainbow::renderer::converter {

	std::shared_ptr<entity> create_entity(const meta_scene::objects::entity& entity, real radius);

	std::shared_ptr<scene> create_scene(const meta_scene::scene& meta_scene);

}
