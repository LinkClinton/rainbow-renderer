#include "convert_material.hpp"

#include "rainbow-cpu/textures/constant_texture.hpp"

#include "rainbow-cpu/materials/translucent_material.hpp"
#include "rainbow-cpu/materials/subsurface_material.hpp"
#include "rainbow-cpu/materials/substrate_material.hpp"
#include "rainbow-cpu/materials/plastic_material.hpp"
#include "rainbow-cpu/materials/mixture_material.hpp"
#include "rainbow-cpu/materials/mirror_material.hpp"
#include "rainbow-cpu/materials/matte_material.hpp"
#include "rainbow-cpu/materials/glass_material.hpp"
#include "rainbow-cpu/materials/metal_material.hpp"
#include "rainbow-cpu/materials/uber_material.hpp"

#include "rainbow-core/logs/log.hpp"

#include "convert_texture.hpp"

using namespace rainbow::cpus::textures;

namespace rainbow::renderer::converter {

	std::shared_ptr<material> create_translucent_material(const meta_scene::objects::material& material)
	{
		return std::make_shared<translucent_material>(
			create_spectrum_texture(material.translucent.transmission),
			create_spectrum_texture(material.translucent.reflectance),
			create_spectrum_texture(material.translucent.specular),
			create_spectrum_texture(material.translucent.diffuse),
			create_real_texture(material.translucent.roughness),
			material.translucent.remapping);
	}

	std::shared_ptr<material> create_subsurface_material(const meta_scene::objects::material& material)
	{
		return std::make_shared<subsurface_material>(
			create_spectrum_texture(material.subsurface.transmission),
			create_spectrum_texture(material.subsurface.reflectance),
			create_spectrum_texture(material.subsurface.diffuse),
			create_spectrum_texture(material.subsurface.mfp),
			create_real_texture(material.subsurface.roughness_u),
			create_real_texture(material.subsurface.roughness_v),
			create_real_texture(material.subsurface.eta),
			material.subsurface.remapping);
	}
	
	std::shared_ptr<material> create_substrate_material(const meta_scene::objects::material& material)
	{
		return std::make_shared<substrate_material>(
			create_spectrum_texture(material.substrate.specular),
			create_spectrum_texture(material.substrate.diffuse),
			create_real_texture(material.substrate.roughness_u),
			create_real_texture(material.substrate.roughness_v),
			material.substrate.remapping);
	}
	
	std::shared_ptr<material> create_diffuse_material(const meta_scene::objects::material& material)
	{
		return std::make_shared<matte_material>(
			create_spectrum_texture(material.diffuse.reflectance),
			create_real_texture(material.diffuse.sigma));
	}

	std::shared_ptr<material> create_plastic_material(const meta_scene::objects::material& material)
	{
		return std::make_shared<plastic_material>(
			create_spectrum_texture(material.plastic.specular),
			create_spectrum_texture(material.plastic.diffuse),
			create_real_texture(material.plastic.roughness),
			create_real_texture(material.plastic.eta),
			material.plastic.remapping);
	}

	std::shared_ptr<material> create_mirror_material(const meta_scene::objects::material& material)
	{
		return std::make_shared<mirror_material>(
			create_spectrum_texture(material.mirror.reflectance));
	}

	std::shared_ptr<material> create_glass_material(const meta_scene::objects::material& material)
	{
		return std::make_shared<glass_material>(
			create_spectrum_texture(material.glass.reflectance),
			create_spectrum_texture(material.glass.transmission),
			create_real_texture(material.glass.roughness_u),
			create_real_texture(material.glass.roughness_v),
			create_real_texture(material.glass.eta),
			material.glass.remapping);
	}

	std::shared_ptr<material> create_metal_material(const meta_scene::objects::material& material)
	{
		return std::make_shared<metal_material>(
			create_spectrum_texture(material.metal.eta),
			create_spectrum_texture(material.metal.k),
			create_real_texture(material.metal.roughness_u),
			create_real_texture(material.metal.roughness_v),
			material.metal.remapping);
	}

	std::shared_ptr<material> create_uber_material(const meta_scene::objects::material& material)
	{
		return std::make_shared<uber_material>(
			create_spectrum_texture(material.uber.transmission),
			create_spectrum_texture(material.uber.reflectance),
			create_spectrum_texture(material.uber.specular),
			create_spectrum_texture(material.uber.diffuse),
			create_spectrum_texture(material.uber.opacity),
			create_real_texture(material.uber.roughness_u),
			create_real_texture(material.uber.roughness_v),
			create_real_texture(material.uber.eta),
			material.uber.remapping);
	}

	std::shared_ptr<material> create_mixture_material(const meta_scene::objects::material& material)
	{
		return std::make_shared<mixture_material>(
			create_spectrum_texture(material.mixture.alpha),
			create_material(*material.mixture.material0),
			create_material(*material.mixture.material1));
	}

	std::shared_ptr<material> create_material(const std::optional<meta_scene::objects::material>& material)
	{
		if (!material.has_value()) return nullptr;

		if (material->type == "translucent") return create_translucent_material(material.value());
		if (material->type == "subsurface") return create_subsurface_material(material.value());
		if (material->type == "substrate") return create_substrate_material(material.value());
		if (material->type == "diffuse") return create_diffuse_material(material.value());
		if (material->type == "plastic") return create_plastic_material(material.value());
		if (material->type == "mixture") return create_mixture_material(material.value());
		if (material->type == "mirror") return create_mirror_material(material.value());
		if (material->type == "glass") return create_glass_material(material.value());
		if (material->type == "metal") return create_metal_material(material.value());
		if (material->type == "uber") return create_uber_material(material.value());
		
		logs::error("unknown material.");

		return std::make_shared<matte_material>(
			std::make_shared<constant_texture2d<spectrum>>(spectrum(1)),
			std::make_shared<constant_texture2d<real>>(static_cast<real>(0)));
	}
}
