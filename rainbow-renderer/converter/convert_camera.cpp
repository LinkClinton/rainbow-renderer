#include "convert_camera.hpp"

#include "rainbow-cpu/cameras/perspective_camera.hpp"
#include "rainbow-core/logs/log.hpp"

#include "../core/renderer_config.hpp"

#include "convert_transform.hpp"
#include "convert_filter.hpp"

#undef near
#undef far

namespace rainbow::renderer::converter {

	std::shared_ptr<film> create_film(const meta_scene::objects::film& film)
	{
		const auto resolution = vector2i(
			static_cast<int>(film.size_x),
			static_cast<int>(film.size_y));

		const auto crop_window_min = vector2(0);
		const auto crop_window_max = vector2(1);
		
		return std::make_shared<cpus::cameras::film>(
			create_filter(film.filter), resolution, bound2(crop_window_min, crop_window_max), film.scale);
	}

	std::shared_ptr<camera> create_perspective_camera(const meta_scene::objects::camera& camera, const meta_scene::objects::film& film)
	{
		const auto width = static_cast<real>(film.size_x);
		const auto height = static_cast<real>(film.size_y);
		const auto fov = radians(camera.perspective.fov);
		
		const auto projective =
			renderer_config::camera_system == coordinate_system::right_hand ?
			perspective_right_hand(fov, width, height, 0.01f, 1000) :
			perspective_left_hand(fov, width, height, 0.01f, 1000);

		const auto screen_window = bound2(vector2(-1), vector2(1));
		const auto camera_system = renderer_config::camera_system == coordinate_system::right_hand ?
			camera_system::right_hand : camera_system::left_hand;
		
		return std::make_shared<perspective_camera>(create_film(film), camera_system, screen_window, projective, 
			read_transform(camera.transform), camera.depth_of_field.focus, camera.depth_of_field.lens);
	}
	
	std::shared_ptr<camera> create_camera(const meta_scene::objects::camera& camera, const meta_scene::objects::film& film)
	{
		if (camera.type == "perspective") return create_perspective_camera(camera, film);

		logs::error("unknown camera.");

		return nullptr;
	}
}
