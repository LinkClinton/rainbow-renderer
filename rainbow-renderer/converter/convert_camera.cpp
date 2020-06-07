#include "convert_camera.hpp"

#include "meta-scene/cameras/perspective_camera.hpp"

#include "rainbow-cpu/cameras/perspective_camera.hpp"
#include "rainbow-core/logs/log.hpp"

#include "../core/renderer_config.hpp"

#include "convert_transform.hpp"
#include "convert_filter.hpp"

#undef near
#undef far

namespace rainbow::renderer::converter {

	std::shared_ptr<film> create_film(
		const std::shared_ptr<metascene::cameras::film>& film)
	{
		const auto resolution = vector2i(
			static_cast<int>(film->width),
			static_cast<int>(film->height));

		const auto crop_window_min = vector2(0);
		const auto crop_window_max = vector2(1);
		
		return std::make_shared<cpus::cameras::film>(create_filter(film->filter), resolution, bound2(crop_window_min, crop_window_max), film->scale);
	}

	std::shared_ptr<camera> create_perspective_camera(
		const std::shared_ptr<metascene::cameras::perspective_camera>& camera,
		const std::shared_ptr<metascene::cameras::film>& film)
	{
		const auto width = static_cast<real>(film->width);
		const auto height = static_cast<real>(film->height);
		const auto fov = radians(camera->fov);
		
		const auto projective =
			renderer_config::camera_system == coordinate_system::right_hand ?
			perspective_right_hand(fov, width, height, camera->near, camera->far) :
			perspective_left_hand(fov, width, height, camera->near, camera->far);

		const auto screen_window = bound2(vector2(-1), vector2(1));

		return std::make_shared<perspective_camera>(create_film(film), screen_window, projective, read_transform(camera->transform),
			camera->focus, camera->lens);
	}
	
	std::shared_ptr<camera> create_camera(
		const std::shared_ptr<metascene::cameras::camera>& camera,
		const std::shared_ptr<metascene::cameras::film>& film)
	{
		if (camera->type == metascene::cameras::type::perspective)
			return create_perspective_camera(std::static_pointer_cast<metascene::cameras::perspective_camera>(camera), film);

		logs::error("unknown camera.");

		return std::make_shared<perspective_camera>(
			create_film(film), transform(), radians(static_cast<real>(45.0)));
	}
}
