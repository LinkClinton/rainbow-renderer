#pragma once

#include "meta-scene/entity.hpp"
#include "meta-scene/scene.hpp"

#include "rainbow-cpu/scenes/entity.hpp"
#include "rainbow-cpu/scenes/scene.hpp"

using namespace rainbow::cpus::scenes;

namespace rainbow::renderer::converter {

	std::shared_ptr<entity> create_entity(const std::shared_ptr<metascene::entity>& entity, real radius);

	std::shared_ptr<scene> create_scene(const std::shared_ptr<metascene::scene>& meta_scene);

}
