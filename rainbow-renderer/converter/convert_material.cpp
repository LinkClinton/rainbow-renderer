#include "convert_material.hpp"

#include "meta-scene/materials/translucent_material.hpp"
#include "meta-scene/materials/subsurface_material.hpp"
#include "meta-scene/materials/substrate_material.hpp"
#include "meta-scene/materials/plastic_material.hpp"
#include "meta-scene/materials/diffuse_material.hpp"
#include "meta-scene/materials/mixture_material.hpp"
#include "meta-scene/materials/mirror_material.hpp"
#include "meta-scene/materials/glass_material.hpp"
#include "meta-scene/materials/metal_material.hpp"
#include "meta-scene/materials/uber_material.hpp"

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

	std::shared_ptr<material> create_translucent_material(const std::shared_ptr<metascene::materials::translucent_material>& material)
	{
		return std::make_shared<translucent_material>(
			create_spectrum_texture(material->transmission),
			create_spectrum_texture(material->reflectance),
			create_spectrum_texture(material->specular),
			create_spectrum_texture(material->diffuse),
			create_real_texture(material->roughness),
			material->remapped_roughness_to_alpha);
	}

	std::shared_ptr<material> create_subsurface_material(const std::shared_ptr<metascene::materials::subsurface_material>& material)
	{
		return std::make_shared<subsurface_material>(
			create_spectrum_texture(material->transmission),
			create_spectrum_texture(material->reflectance),
			create_spectrum_texture(material->diffuse),
			create_spectrum_texture(material->mfp),
			create_real_texture(material->roughness_u),
			create_real_texture(material->roughness_v),
			create_real_texture(material->eta),
			material->remapped_roughness_to_alpha);
	}
	
	std::shared_ptr<material> create_substrate_material(const std::shared_ptr<metascene::materials::substrate_material>& material)
	{
		return std::make_shared<substrate_material>(
			create_spectrum_texture(material->specular),
			create_spectrum_texture(material->diffuse),
			create_real_texture(material->roughness_u),
			create_real_texture(material->roughness_v),
			material->remapped_roughness_to_alpha);
	}
	
	std::shared_ptr<material> create_diffuse_material(const std::shared_ptr<metascene::materials::diffuse_material>& material)
	{
		return std::make_shared<matte_material>(
			create_spectrum_texture(material->reflectance),
			create_real_texture(material->sigma));
	}

	std::shared_ptr<material> create_plastic_material(const std::shared_ptr<metascene::materials::plastic_material>& material)
	{
		return std::make_shared<plastic_material>(
			create_spectrum_texture(material->specular),
			create_spectrum_texture(material->diffuse),
			create_real_texture(material->roughness),
			create_real_texture(material->eta),
			material->remapped_roughness_to_alpha);
	}

	std::shared_ptr<material> create_mirror_material(const std::shared_ptr<metascene::materials::mirror_material>& material)
	{
		return std::make_shared<mirror_material>(
			create_spectrum_texture(material->reflectance));
	}

	std::shared_ptr<material> create_glass_material(const std::shared_ptr<metascene::materials::glass_material>& material)
	{
		return std::make_shared<glass_material>(
			create_spectrum_texture(material->reflectance),
			create_spectrum_texture(material->transmission),
			create_real_texture(material->roughness_u),
			create_real_texture(material->roughness_v),
			create_real_texture(material->eta),
			material->remapped_roughness_to_alpha);
	}

	std::shared_ptr<material> create_metal_material(const std::shared_ptr<metascene::materials::metal_material>& material)
	{
		return std::make_shared<metal_material>(
			create_spectrum_texture(material->eta),
			create_spectrum_texture(material->k),
			create_real_texture(material->roughness_u),
			create_real_texture(material->roughness_v),
			material->remapped_roughness_to_alpha);
	}

	std::shared_ptr<material> create_uber_material(const std::shared_ptr<metascene::materials::uber_material>& material)
	{
		return std::make_shared<uber_material>(
			create_spectrum_texture(material->transmission),
			create_spectrum_texture(material->reflectance),
			create_spectrum_texture(material->specular),
			create_spectrum_texture(material->diffuse),
			create_spectrum_texture(material->opacity),
			create_real_texture(material->roughness_u),
			create_real_texture(material->roughness_v),
			create_real_texture(material->eta),
			material->remapped_roughness_to_alpha);
	}

	std::shared_ptr<material> create_mixture_material(const std::shared_ptr<metascene::materials::mixture_material>& material)
	{
		return std::make_shared<mixture_material>(
			create_spectrum_texture(material->alpha),
			create_material(material->materials[0]),
			create_material(material->materials[1]));
	}

	std::shared_ptr<material> create_material(const std::shared_ptr<metascene::materials::material>& material)
	{
		if (material == nullptr) return nullptr;

		if (material->type == metascene::materials::type::translucent)
			return create_translucent_material(std::static_pointer_cast<metascene::materials::translucent_material>(material));

		if (material->type == metascene::materials::type::subsurface)
			return create_subsurface_material(std::static_pointer_cast<metascene::materials::subsurface_material>(material));
		
		if (material->type == metascene::materials::type::substrate)
			return create_substrate_material(std::static_pointer_cast<metascene::materials::substrate_material>(material));
		
		if (material->type == metascene::materials::type::diffuse)
			return create_diffuse_material(std::static_pointer_cast<metascene::materials::diffuse_material>(material));

		if (material->type == metascene::materials::type::plastic)
			return create_plastic_material(std::static_pointer_cast<metascene::materials::plastic_material>(material));

		if (material->type == metascene::materials::type::mixture)
			return create_mixture_material(std::static_pointer_cast<metascene::materials::mixture_material>(material));
		
		if (material->type == metascene::materials::type::mirror)
			return create_mirror_material(std::static_pointer_cast<metascene::materials::mirror_material>(material));
		
		if (material->type == metascene::materials::type::glass)
			return create_glass_material(std::static_pointer_cast<metascene::materials::glass_material>(material));

		if (material->type == metascene::materials::type::metal)
			return create_metal_material(std::static_pointer_cast<metascene::materials::metal_material>(material));

		if (material->type == metascene::materials::type::uber)
			return create_uber_material(std::static_pointer_cast<metascene::materials::uber_material>(material));
		
		logs::error("unknown material.");

		return std::make_shared<matte_material>(
			std::make_shared<constant_texture2d<spectrum>>(spectrum(1)),
			std::make_shared<constant_texture2d<real>>(static_cast<real>(0)));
	}
}
