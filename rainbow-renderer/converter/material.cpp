#include "material.hpp"

#include "meta-scene/materials/plastic_material.hpp"
#include "meta-scene/materials/diffuse_material.hpp"
#include "meta-scene/materials/glass_material.hpp"

#include "rainbow/textures/constant_texture.hpp"
#include "rainbow/materials/plastic_material.hpp"
#include "rainbow/materials/matte_material.hpp"
#include "rainbow/materials/glass_material.hpp"
#include "rainbow/shared/logs/log.hpp"

#include "spectrum.hpp"

using namespace rainbow::textures;

namespace rainbow::renderer::converter {

	std::shared_ptr<material> create_diffuse_material(const std::shared_ptr<metascene::materials::diffuse_material>& material)
	{
		return std::make_shared<matte_material>(
			std::make_shared<constant_texture2d<spectrum>>(read_spectrum(material->reflectance)),
			std::make_shared<constant_texture2d<real>>(static_cast<real>(0)));
	}

	std::shared_ptr<material> create_plastic_material(const std::shared_ptr<metascene::materials::plastic_material>& material)
	{
		return std::make_shared<plastic_material>(
			std::make_shared<constant_texture2d<spectrum>>(read_spectrum(material->specular)),
			std::make_shared<constant_texture2d<spectrum>>(read_spectrum(material->diffuse)),
			std::make_shared<constant_texture2d<real>>(material->roughness),
			std::make_shared<constant_texture2d<real>>(material->eta),
			material->remapped_roughness_to_alpha);
	}

	std::shared_ptr<material> create_glass_material(const std::shared_ptr<metascene::materials::glass_material>& material)
	{
		return std::make_shared<glass_material>(
			std::make_shared<constant_texture2d<spectrum>>(read_spectrum(material->reflectance)),
			std::make_shared<constant_texture2d<spectrum>>(read_spectrum(material->transmission)),
			std::make_shared<constant_texture2d<vector2>>(vector2(material->roughness_u, material->roughness_v)),
			std::make_shared<constant_texture2d<real>>(material->eta),
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
		
		logs::error("unknown material.");

		return std::make_shared<matte_material>(
			std::make_shared<constant_texture2d<spectrum>>(spectrum(1)),
			std::make_shared<constant_texture2d<real>>(static_cast<real>(0)));
	}
}
