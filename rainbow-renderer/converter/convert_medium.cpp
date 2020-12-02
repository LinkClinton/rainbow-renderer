#include "convert_medium.hpp"

#include "rainbow-cpu/media/heterogeneous_medium.hpp"
#include "rainbow-cpu/media/homogeneous_medium.hpp"

#include "rainbow-cpu/textures/constant_texture.hpp"
#include "rainbow-cpu/textures/image_texture.hpp"

#include "rainbow-core/logs/log.hpp"

#include "convert_transform.hpp"
#include "convert_spectrum.hpp"
#include "convert_texture.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<medium> create_homogeneous_medium(const meta_scene::objects::medium& medium)
	{
		return std::make_shared<homogeneous_medium>(
			read_spectrum(medium.homogeneous.sigma_a), 
			read_spectrum(medium.homogeneous.sigma_s), 
			medium.homogeneous.g);
	}

	std::shared_ptr<medium> create_heterogeneous_medium(const meta_scene::objects::medium& medium)
	{
		return std::make_shared<heterogeneous_medium>(
			std::make_shared<constant_texture3d<spectrum>>(read_spectrum(medium.heterogeneous.albedo)),
			std::make_shared<image_texture3d<real>>(vector3_t<size_t>(
				medium.heterogeneous.size_x, 
				medium.heterogeneous.size_y,
				medium.heterogeneous.size_z), medium.heterogeneous.sigma_t),
			std::make_shared<constant_texture3d<real>>(medium.heterogeneous.g),
			read_transform(medium.heterogeneous.transform));
	}
	
	std::shared_ptr<medium> create_medium(const std::optional<meta_scene::objects::medium>& medium)
	{
		if (!medium.has_value()) return nullptr;

		if (medium->type == "heterogeneous") return create_heterogeneous_medium(medium.value());
		if (medium->type == "homogeneous") return create_homogeneous_medium(medium.value());
		
		logs::error("unknown medium.");

		return nullptr;
	}

	std::shared_ptr<media> create_media(const std::optional<meta_scene::objects::media>& media)
	{
		if (!media.has_value()) return nullptr;
		
		return std::make_shared<cpus::media::media>(create_medium(media->outside), create_medium(media->inside));
	}
}
