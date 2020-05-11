#include "renderer_scene.hpp"

#include "meta-scene/cameras/perspective_camera.hpp"
#include "meta-scene/materials/diffuse_material.hpp"
#include "meta-scene/spectrums/sampled_spectrum.hpp"
#include "meta-scene/emitters/surface_emitter.hpp"
#include "meta-scene/shapes/mesh.hpp"

#include "rainbow/integrators/path_integrator.hpp"
#include "rainbow/cameras/perspective_camera.hpp"
#include "rainbow/samplers/random_sampler.hpp"
#include "rainbow/filters/gaussian_filter.hpp"
#include "rainbow/emitters/surface_light.hpp"

#include "rainbow/textures/constant_texture.hpp"

#include "rainbow/materials/matte_material.hpp"

using namespace rainbow::materials;
using namespace rainbow::textures;
using namespace rainbow::samplers;

#include "../importers/obj_importer.hpp"

namespace rainbow::renderer {

	void renderer_scene::render_to(const std::string& filename) const
	{
		scene->build_accelerator();

		integrator->render(camera, scene);

		film->write(filename);
	}

	spectrum read_spectrum(const std::shared_ptr<metascene::spectrum>& spectrum)
	{
		const auto sampled = std::static_pointer_cast<metascene::sampled_spectrum>(spectrum);

		return spectrums::spectrum(sampled->lambda, sampled->value);
	}

	transform read_transform(const metascene::matrix4x4& matrix)
	{
		return transform(matrix, inverse(matrix));
	}

	std::shared_ptr<integrator> build_integrator(const std::shared_ptr<metascene::scene>& meta_scene)
	{
		return std::make_shared<path_integrator>(
			std::make_shared<random_sampler2d>(meta_scene->sampler->sample_per_pixel),
			std::make_shared<random_sampler1d>(meta_scene->sampler->sample_per_pixel),
			meta_scene->integrator->depth);
	}

	std::shared_ptr<camera> build_camera(const std::shared_ptr<metascene::scene>& meta_scene, const std::shared_ptr<film>& film)
	{
		return std::make_shared<perspective_camera>(film,
			read_transform(meta_scene->camera->transform),
			radians(std::static_pointer_cast<metascene::perspective_camera>(meta_scene->camera)->fov));
	}

	std::shared_ptr<material> build_material(const std::shared_ptr<metascene::material>& material)
	{
		if (material == nullptr) return nullptr;

		const auto diffuse_material = std::static_pointer_cast<metascene::diffuse_material>(material);

		return std::make_shared<matte_material>(
			std::make_shared<constant_texture2d<spectrum>>(read_spectrum(diffuse_material->reflectance)),
			std::make_shared<constant_texture2d<real>>(0.f));
	}

	std::shared_ptr<shape> build_shape(const std::shared_ptr<metascene::shape>& shape)
	{
		if (shape == nullptr) return nullptr;

		const auto mesh = std::static_pointer_cast<metascene::mesh>(shape);

		return importers::load_obj_mesh(mesh->filename)[0];
	}

	std::shared_ptr<emitter> build_emitter(const std::shared_ptr<metascene::emitter>& emitter)
	{
		if (emitter == nullptr) return nullptr;

		const auto surface_emitter = std::static_pointer_cast<metascene::surface_emitter>(emitter);

		return std::make_shared<surface_light>(read_spectrum(surface_emitter->radiance));
	}

	std::shared_ptr<entity> build_entity(const std::shared_ptr<metascene::entity>& entity)
	{
		return std::make_shared<scenes::entity>(
			build_material(entity->material),
			build_emitter(entity->emitter),
			build_shape(entity->shape),
			read_transform(entity->transform)
			);
	}

	std::shared_ptr<scene> build_scene(const std::shared_ptr<metascene::scene>& meta_scene)
	{
		const auto scene = std::make_shared<scenes::scene>();

		for (const auto& entity : meta_scene->entities)
			scene->add_entity(build_entity(entity));

		return scene;
	}

	std::shared_ptr<filter> build_filter(const std::shared_ptr<metascene::filter>& filter)
	{
		return std::make_shared<gaussian_filter>();
	}

	std::shared_ptr<film> build_film(const std::shared_ptr<metascene::scene>& meta_scene)
	{
		const auto crop_window_min = vector2(0);
		const auto crop_window_max = vector2(1);

		return std::make_shared<film>(
			build_filter(meta_scene->film->filter),
			vector2i(
				static_cast<int>(meta_scene->film->width),
				static_cast<int>(meta_scene->film->height)),
			bound2(crop_window_min, crop_window_max));
	}
	
	renderer_scene create_from_meta_scene(const std::shared_ptr<metascene::scene>& meta_scene)
	{
		renderer_scene scene;

		scene.integrator = build_integrator(meta_scene);
		scene.film = build_film(meta_scene);
		scene.camera = build_camera(meta_scene, scene.film);
		scene.scene = build_scene(meta_scene);

		return scene;
	}

	
}