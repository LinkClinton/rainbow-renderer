#include "convert_camera.hpp"

#include "meta-scene/cameras/perspective_camera.hpp"

#include "rainbow/cameras/perspective_camera.hpp"
#include "rainbow/shared/logs/log.hpp"

#include "convert_transform.hpp"
#include "convert_filter.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<film> create_film(
		const std::shared_ptr<metascene::cameras::film>& film)
	{
		const auto resolution = vector2i(
			static_cast<int>(film->width),
			static_cast<int>(film->height));

		const auto crop_window_min = vector2(0);
		const auto crop_window_max = vector2(1);
		
		return std::make_shared<rainbow::film>(create_filter(film->filter), resolution, bound2(crop_window_min, crop_window_max));
	}

	std::shared_ptr<camera> create_perspective_camera(
		const std::shared_ptr<metascene::cameras::perspective_camera>& camera,
		const std::shared_ptr<metascene::cameras::film>& film)
	{
		return std::make_shared<perspective_camera>(
			create_film(film), read_transform(camera->transform), radians(camera->fov));
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
