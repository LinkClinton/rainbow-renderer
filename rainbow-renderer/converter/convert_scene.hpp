#pragma once

#include "meta-scene/entity.hpp"
#include "meta-scene/scene.hpp"

#include "rainbow/scenes/entity.hpp"
#include "rainbow/scenes/scene.hpp"

namespace rainbow {

	using namespace scenes;
	
	namespace renderer {

		namespace converter {

			std::shared_ptr<entity> create_entity(const std::shared_ptr<metascene::entity>& entity);

			std::shared_ptr<scene> create_scene(const std::shared_ptr<metascene::scene>& meta_scene);
		}
	}
}
