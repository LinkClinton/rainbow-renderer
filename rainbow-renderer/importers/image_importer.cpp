#include "image_importer.hpp"

#include "../core/renderer_config.hpp"

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

		if (renderer_config::uv_system == coordinate_system::left_hand) {

			for (size_t index = 0; index < info.data.size(); index++) {
				const auto value = static_cast<real>(data[index]) / 255;

				info.data[index] = gamma ? inverse_gamma_correct(value) : value;
			}
			
		}else {

			for (size_t y = 0; y < height; y++) {
				const auto invert_y = height - y - 1;

				for (size_t x = 0; x < width; x++) {
					const auto index0 = (y * width + x) * 4;
					const auto index1 = (invert_y * width + x) * 4;

					for (size_t component = 0; component < 4; component++) {
						const auto value = static_cast<real>(data[index1 + component]) / 255;

						info.data[index0 + component] = gamma ? inverse_gamma_correct(value) : value;
					}
				}
			}
			
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


		if (renderer_config::uv_system == coordinate_system::left_hand) {

			for (size_t index = 0; index < info.data.size(); index++)
				info.data[index] = gamma ? inverse_gamma_correct(data[index]) : data[index];

		}else {

			for (size_t y = 0; y < height; y++) {
				const auto invert_y = height - y - 1;

				for (size_t x = 0; x < width; x++) {
					const auto index0 = (y * width + x) * 4;
					const auto index1 = (invert_y * width + x) * 4;

					for (size_t component = 0; component < 4; component++) {
						const auto value = data[index1 + component];

						info.data[index0 + component] = gamma ? inverse_gamma_correct(value) : value;
					}
				}
			}
			
		}
			
		stbi_image_free(data);

		return info;
	}

}

#endif