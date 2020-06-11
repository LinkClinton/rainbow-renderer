#include "convert_medium.hpp"

#include "meta-scene/media/heterogeneous_medium.hpp"
#include "meta-scene/media/homogeneous_medium.hpp"

#include "rainbow-cpu/media/heterogeneous_medium.hpp"
#include "rainbow-cpu/media/homogeneous_medium.hpp"

#include "rainbow-cpu/textures/constant_texture.hpp"
#include "rainbow-cpu/textures/image_texture.hpp"

#include "rainbow-core/logs/log.hpp"

#include "convert_transform.hpp"
#include "convert_spectrum.hpp"
#include "convert_texture.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<medium> create_homogeneous_medium(const std::shared_ptr<metascene::media::homogeneous_medium>& medium)
	{
		return std::make_shared<homogeneous_medium>(read_spectrum(medium->sigma_a), read_spectrum(medium->sigma_s), medium->g);
	}

	std::shared_ptr<medium> create_heterogeneous_medium(const std::shared_ptr<metascene::media::heterogeneous_medium>& medium)
	{
		return std::make_shared<heterogeneous_medium>(
			std::make_shared<constant_texture3d<spectrum>>(read_spectrum(medium->albedo)),
			std::make_shared<image_texture3d<real>>(vector3_t<size_t>(medium->x, medium->y, medium->z), medium->sigma_t),
			std::make_shared<constant_texture3d<real>>(medium->g),
			read_transform(medium->transform));
	}
	
	std::shared_ptr<medium> create_medium(const std::shared_ptr<metascene::media::medium>& medium)
	{
		if (medium == nullptr) return nullptr;

		if (medium->type == metascene::media::type::heterogeneous)
			return create_heterogeneous_medium(std::static_pointer_cast<metascene::media::heterogeneous_medium>(medium));
		
		if (medium->type == metascene::media::type::homogeneous)
			return create_homogeneous_medium(std::static_pointer_cast<metascene::media::homogeneous_medium>(medium));
		
		logs::error("unknown medium.");

		return nullptr;
	}

	std::shared_ptr<media> create_media(const std::shared_ptr<metascene::media::media>& media)
	{
		if (media == nullptr) return nullptr;
		
		return std::make_shared<cpus::media::media>(create_medium(media->outside), create_medium(media->inside));
	}
}
