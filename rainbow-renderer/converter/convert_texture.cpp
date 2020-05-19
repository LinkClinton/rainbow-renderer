#include "convert_texture.hpp"

#include "meta-scene/textures/constant_texture.hpp"

#include "rainbow/textures/constant_texture.hpp"

#include "convert_spectrum.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<texture2d<spectrum>> create_spectrum_texture(const std::shared_ptr<metascene::textures::constant_texture>& texture)
	{
		return std::make_shared<constant_texture2d<spectrum>>(read_spectrum(texture->spectrum));
	}
	
	
	std::shared_ptr<texture2d<spectrum>> create_spectrum_texture(const std::shared_ptr<metascene::textures::texture>& texture)
	{
		if (texture->type == metascene::textures::type::constant)
			return create_spectrum_texture(std::static_pointer_cast<metascene::textures::constant_texture>(texture));

		return std::make_shared<constant_texture2d<spectrum>>(spectrum(1));
	}

	std::shared_ptr<texture2d<vector2>> create_vector2_texture(
		const std::shared_ptr<metascene::textures::constant_texture>& texture0,
		const std::shared_ptr<metascene::textures::constant_texture>& texture1)
	{
		return std::make_shared<constant_texture2d<vector2>>(vector2(texture0->real, texture1->real));
	}
	
	std::shared_ptr<texture2d<vector2>> create_vector2_texture(
		const std::shared_ptr<metascene::textures::texture>& texture0,
		const std::shared_ptr<metascene::textures::texture>& texture1)
	{
		assert(texture0->type == texture1->type);

		if (texture0->type == metascene::textures::type::constant)
			return create_vector2_texture(
				std::static_pointer_cast<metascene::textures::constant_texture>(texture0),
				std::static_pointer_cast<metascene::textures::constant_texture>(texture1));

		return std::make_shared<constant_texture2d<vector2>>(vector2(0));
	}

	std::shared_ptr<texture2d<real>> create_real_texture(const std::shared_ptr<metascene::textures::constant_texture>& texture)
	{
		return std::make_shared<constant_texture2d<real>>(texture->real);
	}
	
	std::shared_ptr<texture2d<real>> create_real_texture(const std::shared_ptr<metascene::textures::texture>& texture)
	{
		if (texture->type == metascene::textures::type::constant)
			return create_real_texture(std::static_pointer_cast<metascene::textures::constant_texture>(texture));

		return std::make_shared<constant_texture2d<real>>(static_cast<real>(0));
	}
}
