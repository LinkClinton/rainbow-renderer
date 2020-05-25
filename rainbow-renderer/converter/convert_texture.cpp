#include "convert_texture.hpp"

#include "meta-scene/textures/constant_texture.hpp"
#include "meta-scene/textures/image_texture.hpp"
#include "meta-scene/textures/scale_texture.hpp"

#include "rainbow/textures/constant_texture.hpp"
#include "rainbow/textures/image_texture.hpp"

#include "../core/resource_cache.hpp"

#include "convert_spectrum.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<texture2d<spectrum>> create_spectrum_texture(const std::shared_ptr<metascene::textures::constant_texture>& texture)
	{
		assert(texture->value_type == metascene::textures::value_type::spectrum);
		
		return std::make_shared<constant_texture2d<spectrum>>(read_spectrum(texture->spectrum));
	}

	std::shared_ptr<texture2d<spectrum>> create_spectrum_texture(const std::shared_ptr<metascene::textures::image_texture>& texture)
	{
		return resource_cache::read_spectrum_texture(texture->filename, texture->gamma);
	}

	std::shared_ptr<texture2d<spectrum>> create_spectrum_texture(const std::shared_ptr<metascene::textures::scale_texture>& texture)
	{
		// because we cache the origin image texture to reduce the time of loading
		// so if we will change the values of a image texture, we will copy it 
		const auto base_texture = create_spectrum_texture(texture->base)->copy_to();
		const auto scale_texture = std::static_pointer_cast<metascene::textures::constant_texture>(texture->scale);

		if (scale_texture->value_type == metascene::textures::value_type::real)
			base_texture->multiply(spectrum(scale_texture->real));

		if (scale_texture->value_type == metascene::textures::value_type::spectrum)
			base_texture->multiply(read_spectrum(scale_texture->spectrum));

		return base_texture;
	}
	
	std::shared_ptr<texture2d<spectrum>> create_spectrum_texture(const std::shared_ptr<metascene::textures::texture>& texture)
	{
		if (texture->type == metascene::textures::type::constant)
			return create_spectrum_texture(std::static_pointer_cast<metascene::textures::constant_texture>(texture));

		if (texture->type == metascene::textures::type::image)
			return create_spectrum_texture(std::static_pointer_cast<metascene::textures::image_texture>(texture));

		if (texture->type == metascene::textures::type::scale)
			return create_spectrum_texture(std::static_pointer_cast<metascene::textures::scale_texture>(texture));
		
		return std::make_shared<constant_texture2d<spectrum>>(spectrum(1));
	}

	std::shared_ptr<texture2d<real>> create_real_texture(const std::shared_ptr<metascene::textures::constant_texture>& texture)
	{
		assert(texture->value_type == metascene::textures::value_type::real);
		
		return std::make_shared<constant_texture2d<real>>(texture->real);
	}

	std::shared_ptr<texture2d<real>> create_real_texture(const std::shared_ptr<metascene::textures::image_texture>& texture)
	{
		return resource_cache::read_real_texture(texture->filename, texture->gamma);
	}
	
	std::shared_ptr<texture2d<real>> create_real_texture(const std::shared_ptr<metascene::textures::texture>& texture)
	{
		if (texture->type == metascene::textures::type::constant)
			return create_real_texture(std::static_pointer_cast<metascene::textures::constant_texture>(texture));
		
		return std::make_shared<constant_texture2d<real>>(static_cast<real>(0));
	}
}
