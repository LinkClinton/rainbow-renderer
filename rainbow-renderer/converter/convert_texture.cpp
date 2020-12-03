#include "convert_texture.hpp"

#include "rainbow-cpu/textures/constant_texture.hpp"
#include "rainbow-cpu/textures/mixture_texture.hpp"
#include "rainbow-cpu/textures/image_texture.hpp"
#include "rainbow-cpu/textures/scale_texture.hpp"

#include "../core/renderer_config.hpp"
#include "../core/resource_cache.hpp"

#include "convert_spectrum.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<texture2d<spectrum>> create_constant_spectrum_texture(const meta_scene::objects::texture& texture)
	{
		return std::make_shared<constant_texture2d<spectrum>>(read_spectrum(texture.constant.value));
	}

	std::shared_ptr<texture2d<spectrum>> create_mixture_spectrum_texture(const meta_scene::objects::texture& texture)
	{
		return std::make_shared<mixture_texture2d<spectrum>>(
			create_spectrum_texture(*texture.mixture.texture0),
			create_spectrum_texture(*texture.mixture.texture1),
			create_real_texture(*texture.mixture.alpha));
	}

	std::shared_ptr<texture2d<spectrum>> create_image_spectrum_texture(const meta_scene::objects::texture& texture)
	{
		return resource_cache::read_spectrum_texture(renderer_config::directory_path + texture.image.filename, texture.image.gamma);
	}

	std::shared_ptr<texture2d<spectrum>> create_scale_spectrum_texture(const meta_scene::objects::texture& texture)
	{
		return std::make_shared<scale_texture2d<spectrum>>(
			create_spectrum_texture(*texture.scale.scale),
			create_spectrum_texture(*texture.scale.base));
	}
	
	std::shared_ptr<texture2d<spectrum>> create_spectrum_texture(const meta_scene::objects::texture& texture)
	{
		if (texture.type == "constant") return create_constant_spectrum_texture(texture);
		if (texture.type == "mixture") return create_mixture_spectrum_texture(texture);
		if (texture.type == "image") return create_image_spectrum_texture(texture);
		if (texture.type == "scale") return create_scale_spectrum_texture(texture);
		
		return std::make_shared<constant_texture2d<spectrum>>(spectrum(1));
	}

	std::shared_ptr<texture2d<real>> create_constant_real_texture(const meta_scene::objects::texture& texture)
	{	
		return std::make_shared<constant_texture2d<real>>(texture.constant.value.r);
	}

	std::shared_ptr<texture2d<real>> create_mixture_real_texture(const meta_scene::objects::texture& texture)
	{
		return std::make_shared<mixture_texture2d<real>>(
			create_real_texture(*texture.mixture.texture0),
			create_real_texture(*texture.mixture.texture1),
			create_real_texture(*texture.mixture.alpha));
	}
	
	std::shared_ptr<texture2d<real>> create_image_real_texture(const meta_scene::objects::texture& texture)
	{
		return resource_cache::read_real_texture(renderer_config::directory_path + texture.image.filename, texture.image.gamma);
	}
	
	std::shared_ptr<texture2d<real>> create_real_texture(const meta_scene::objects::texture& texture)
	{
		if (texture.type == "constant") return create_constant_real_texture(texture);
		if (texture.type == "mixture") return create_mixture_real_texture(texture);
		if (texture.type == "image") return create_image_real_texture(texture);
		
		return std::make_shared<constant_texture2d<real>>(static_cast<real>(0));
	}
}
