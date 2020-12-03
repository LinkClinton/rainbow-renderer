#include "convert_shape.hpp"

#include "rainbow-cpu/shapes/sphere.hpp"
#include "rainbow-cpu/shapes/curve.hpp"
#include "rainbow-cpu/shapes/mesh.hpp"
#include "rainbow-cpu/shapes/disk.hpp"
#include "rainbow-core/logs/log.hpp"

#include "../core/renderer_config.hpp"
#include "../core/resource_cache.hpp"
#include "convert_texture.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<shape> create_obj_mesh(const meta_scene::objects::shape& mesh)
	{
		return resource_cache::read_obj_mesh(renderer_config::directory_path + mesh.mesh.filename);
	}

	std::shared_ptr<shape> create_ply_mesh(const meta_scene::objects::shape& mesh)
	{
		return resource_cache::read_ply_mesh(mesh);
	}
	
	std::shared_ptr<shape> create_mesh(const meta_scene::objects::shape& mesh)
	{
		if (mesh.mesh.type == "obj") return create_obj_mesh(mesh);
		if (mesh.mesh.type == "ply") return create_ply_mesh(mesh);
		
		logs::error("unknown mesh type.");

		return nullptr;
	}

	std::shared_ptr<shape> create_sphere(const meta_scene::objects::shape& sphere)
	{
		return std::make_shared<cpus::shapes::sphere>(sphere.sphere.radius, sphere.reverse_orientation);
	}

	std::shared_ptr<shape> create_curve(const meta_scene::objects::shape& curve)
	{
		return std::make_shared<cpus::shapes::curve>(
			curve.curve.control_points, 
			curve.curve.width, 
			curve.curve.u_min, 
			curve.curve.u_max, 
			curve.reverse_orientation);
	}
	
	std::shared_ptr<shape> create_disk(const meta_scene::objects::shape& disk)
	{
		return std::make_shared<cpus::shapes::disk>(disk.disk.radius, disk.disk.height, disk.reverse_orientation);
	}

	std::shared_ptr<shape> create_triangles(const meta_scene::objects::shape& triangles)
	{
		return std::make_shared<mesh>(
			triangles.triangles.mask == std::nullopt ? nullptr : create_real_texture(triangles.triangles.mask.value()),
			triangles.triangles.positions,
			std::vector<vector3>(),
			triangles.triangles.normals,
			triangles.triangles.uvs,
			triangles.triangles.indices,
			triangles.reverse_orientation);
	}
	
	std::shared_ptr<shape> create_shape(const std::optional<meta_scene::objects::shape>& shape)
	{
		if (!shape.has_value()) return nullptr;

		if (shape->type == "triangles") return create_triangles(shape.value());
		if (shape->type == "sphere") return create_sphere(shape.value());
		if (shape->type == "curve") return create_curve(shape.value());
		if (shape->type == "mesh") return create_mesh(shape.value());
		if (shape->type == "disk") return create_disk(shape.value());
		
		logs::error("unknown shape.");

		return std::make_shared<sphere>(static_cast<real>(1));
	}
}
