#include "scene.hpp"

#include "transform.hpp"

#include "material.hpp"
#include "emitter.hpp"
#include "shape.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<entity> create_entity(const std::shared_ptr<metascene::entity>& entity)
	{
		return std::make_shared<scenes::entity>(
			create_material(entity->material), create_emitter(entity->emitter), create_shape(entity->shape), 
			read_transform(entity->transform));
	}

	std::shared_ptr<scene> create_scene(const std::shared_ptr<metascene::scene>& meta_scene)
	{
		const auto scene = std::make_shared<scenes::scene>();

		for (const auto& entity : meta_scene->entities) 
			scene->add_entity(create_entity(entity));

		return scene;
	}


}
