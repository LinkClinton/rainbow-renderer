#include "convert_scene.hpp"

#include "convert_transform.hpp"

#include "convert_material.hpp"
#include "convert_emitter.hpp"
#include "convert_medium.hpp"
#include "convert_shape.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<entity> create_entity(const std::shared_ptr<metascene::entity>& entity, real radius)
	{
		return std::make_shared<cpus::scenes::entity>(
			create_material(entity->material), create_emitter(entity->emitter, radius), 
			create_shape(entity->shape), create_media(entity->media),
			read_transform(entity->transform));
	}

	std::shared_ptr<scene> create_scene(const std::shared_ptr<metascene::scene>& meta_scene)
	{
		const auto scene = std::make_shared<cpus::scenes::scene>();

		std::vector<std::shared_ptr<metascene::entity>> special_emitters;
		
		for (const auto& entity : meta_scene->entities) {
			// we skip the directional and environment emitter and create them later
			if (entity->emitter != nullptr) {
				if (entity->emitter->type == metascene::emitters::type::directional ||
					entity->emitter->type == metascene::emitters::type::environment) {

					special_emitters.push_back(entity);
					
					continue;
				}
			}
			
			scene->add_entity(create_entity(entity, 0));
		}

		const auto [center, radius] = scene->bounding_sphere();

		for (const auto& emitter : special_emitters) 
			scene->add_entity(create_entity(emitter, radius));

		return scene;
	}


}
