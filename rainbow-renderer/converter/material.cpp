#include "material.hpp"

#include "meta-scene/materials/diffuse_material.hpp"

#include "rainbow/textures/constant_texture.hpp"
#include "rainbow/materials/matte_material.hpp"
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

	std::shared_ptr<material> create_material(const std::shared_ptr<metascene::materials::material>& material)
	{
		if (material == nullptr) return nullptr;
		
		if (material->type == metascene::materials::type::diffuse)
			return create_diffuse_material(std::static_pointer_cast<metascene::materials::diffuse_material>(material));

		logs::error("unknown material.");

		return std::make_shared<matte_material>(
			std::make_shared<constant_texture2d<spectrum>>(spectrum(1)),
			std::make_shared<constant_texture2d<real>>(static_cast<real>(0)));
	}
}
