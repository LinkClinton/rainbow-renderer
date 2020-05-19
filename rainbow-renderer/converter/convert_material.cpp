#include "convert_material.hpp"

#include "meta-scene/materials/plastic_material.hpp"
#include "meta-scene/materials/diffuse_material.hpp"
#include "meta-scene/materials/glass_material.hpp"
#include "meta-scene/materials/metal_material.hpp"

#include "rainbow/textures/constant_texture.hpp"
#include "rainbow/materials/plastic_material.hpp"
#include "rainbow/materials/matte_material.hpp"
#include "rainbow/materials/glass_material.hpp"
#include "rainbow/materials/metal_material.hpp"
#include "rainbow/shared/logs/log.hpp"

#include "convert_texture.hpp"

using namespace rainbow::textures;

namespace rainbow::renderer::converter {

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

	std::shared_ptr<material> create_glass_material(const std::shared_ptr<metascene::materials::glass_material>& material)
	{
		return std::make_shared<glass_material>(
			create_spectrum_texture(material->reflectance),
			create_spectrum_texture(material->transmission),
			create_vector2_texture(material->roughness_u, material->roughness_v),
			create_real_texture(material->eta),
			material->remapped_roughness_to_alpha);
	}

	std::shared_ptr<material> create_metal_material(const std::shared_ptr<metascene::materials::metal_material>& material)
	{
		return std::make_shared<metal_material>(
			create_spectrum_texture(material->eta),
			create_spectrum_texture(material->k),
			create_vector2_texture(material->roughness_u, material->roughness_v),
			material->remapped_roughness_to_alpha);
	}
	
	std::shared_ptr<material> create_material(const std::shared_ptr<metascene::materials::material>& material)
	{
		if (material == nullptr) return nullptr;
		
		if (material->type == metascene::materials::type::diffuse)
			return create_diffuse_material(std::static_pointer_cast<metascene::materials::diffuse_material>(material));

		if (material->type == metascene::materials::type::plastic)
			return create_plastic_material(std::static_pointer_cast<metascene::materials::plastic_material>(material));

		if (material->type == metascene::materials::type::glass)
			return create_glass_material(std::static_pointer_cast<metascene::materials::glass_material>(material));

		if (material->type == metascene::materials::type::metal)
			return create_metal_material(std::static_pointer_cast<metascene::materials::metal_material>(material));
		
		logs::error("unknown material.");

		return std::make_shared<matte_material>(
			std::make_shared<constant_texture2d<spectrum>>(spectrum(1)),
			std::make_shared<constant_texture2d<real>>(static_cast<real>(0)));
	}
}
