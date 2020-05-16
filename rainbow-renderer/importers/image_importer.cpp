#include "image_importer.hpp"

#ifdef __IMAGE_IMPORTER__

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

namespace rainbow::renderer::importers {

	image_info read_image(const std::string& name, bool gamma)
	{
		auto channel = 0;
		auto width = 0;
		auto height = 0;

		image_info info;

		const auto data = stbi_load(name.c_str(), &width, &height, &channel, STBI_rgb_alpha);

		info.width = width;
		info.height = height;
		info.data = std::vector<real>(info.width * info.height * 4);

		for (size_t index = 0; index < info.data.size(); index++) {
			const auto value = static_cast<real>(data[index]) / 255;

			info.data[index] = gamma ? inverse_gamma_correct(value) : value;
		}

		stbi_image_free(data);

		return info;
	}
	
	image_info read_image_hdr(const std::string& name, bool gamma)
	{
		auto channel = 0;
		auto width = 0;
		auto height = 0;

		image_info info;

		const auto data = stbi_loadf(name.c_str(), &width, &height, &channel, STBI_rgb_alpha);

		info.width = width;
		info.height = height;
		info.data = std::vector<real>(info.width * info.height * 4);

		for (size_t index = 0; index < info.data.size(); index++)
			info.data[index] = gamma ? inverse_gamma_correct(data[index]) : data[index];

		stbi_image_free(data);

		return info;
	}

}

#endif