#pragma once

#define __IMAGE_IMPORTER__
#ifndef __IMAGE_IMPORTER__
#else

#include "rainbow/shared/spectrums/spectrum.hpp"
#include "rainbow/textures/image_texture.hpp"

#include "../core/renderer_config.hpp"

#include <filesystem>

namespace rainbow {

	using namespace textures;
	using namespace spectrums;
	
	namespace renderer {

		namespace importers {

			struct image_info {
				std::vector<real> data;

				size_t height;
				size_t width;
			};

			image_info read_image(const std::string& name, const coordinate_system& system, bool gamma = false);
			
			image_info read_image_hdr(const std::string& name, const coordinate_system& system, bool gamma = false);
			
			template <typename T>
			std::shared_ptr<image_texture2d<T>> read_texture2d(const std::string& name, bool gamma = false);

			template <typename T>
			std::shared_ptr<image_texture2d<T>> read_texture2d_hdr(const std::string& name, bool gamma = false);
			
			template <typename T>
			std::shared_ptr<image_texture2d<T>> import_texture2d(const std::string& name, bool gamma = false)
			{
				if (std::filesystem::path(name).extension() == ".hdr")
					return read_texture2d_hdr<T>(name, gamma);

				return read_texture2d<T>(name, gamma);
			}

			std::shared_ptr<image_texture2d<spectrum>> import_environment_map(const std::string& name, bool gamma = false);
			
			template <>
			inline std::shared_ptr<image_texture2d<spectrum>> read_texture2d_hdr(const std::string& name, bool gamma)
			{
				const auto image_info = read_image_hdr(name, renderer_config::uv_system, false);

				auto values = std::vector<spectrum>(image_info.width * image_info.height);

				for (size_t index = 0; index < values.size(); index++) {
					values[index].coefficient[0] = gamma ? inverse_gamma_correct(image_info.data[index * 4 + 0]) : image_info.data[index * 4 + 0];
					values[index].coefficient[1] = gamma ? inverse_gamma_correct(image_info.data[index * 4 + 1]) : image_info.data[index * 4 + 1];
					values[index].coefficient[2] = gamma ? inverse_gamma_correct(image_info.data[index * 4 + 2]) : image_info.data[index * 4 + 2];
				}

				return std::make_shared<image_texture2d<spectrum>>(texture_size<2>(image_info.width, image_info.height), values);
			}

			template <>
			inline std::shared_ptr<image_texture2d<real>> read_texture2d(const std::string& name, bool gamma)
			{
				const auto image_info = read_image(name, renderer_config::uv_system, false);

				auto values = std::vector<real>(image_info.width * image_info.height);

				for (size_t index = 0; index < values.size(); index++)
					values[index] = gamma ? inverse_gamma_correct(image_info.data[index * 4]) : image_info.data[index * 4];

				return std::make_shared<image_texture2d<real>>(texture_size<2>(image_info.width, image_info.height), values);
			}

			template <>
			inline std::shared_ptr<image_texture2d<vector2>> read_texture2d(const std::string& name, bool gamma)
			{
				const auto image_info = read_image(name, renderer_config::uv_system, false);

				auto values = std::vector<vector2>(image_info.width * image_info.height);

				for (size_t index = 0; index < values.size(); index++) {
					values[index].x = gamma ? inverse_gamma_correct(image_info.data[index * 4 + 0]) : image_info.data[index * 4 + 0];
					values[index].y = gamma ? inverse_gamma_correct(image_info.data[index * 4 + 1]) : image_info.data[index * 4 + 1];
				}

				return std::make_shared<image_texture2d<vector2>>(texture_size<2>(image_info.width, image_info.height), values);
			}

			template <>
			inline std::shared_ptr<image_texture2d<spectrum>> read_texture2d(const std::string& name, bool gamma)
			{
				const auto image_info = read_image(name, renderer_config::uv_system, false);

				auto values = std::vector<spectrum>(image_info.width * image_info.height);

				for (size_t index = 0; index < values.size(); index++) {
					values[index].coefficient[0] = gamma ? inverse_gamma_correct(image_info.data[index * 4 + 0]) : image_info.data[index * 4 + 0];
					values[index].coefficient[1] = gamma ? inverse_gamma_correct(image_info.data[index * 4 + 1]) : image_info.data[index * 4 + 1];
					values[index].coefficient[2] = gamma ? inverse_gamma_correct(image_info.data[index * 4 + 2]) : image_info.data[index * 4 + 2];
				}

				return std::make_shared<image_texture2d<spectrum>>(texture_size<2>(image_info.width, image_info.height), values);
			}
		}
	}
}

#endif