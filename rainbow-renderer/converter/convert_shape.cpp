#include "convert_shape.hpp"

#include "meta-scene/shapes/triangles.hpp"
#include "meta-scene/shapes/sphere.hpp"
#include "meta-scene/shapes/mesh.hpp"
#include "meta-scene/shapes/disk.hpp"

#include "rainbow/shared/logs/log.hpp"
#include "rainbow/shapes/sphere.hpp"
#include "rainbow/shapes/mesh.hpp"
#include "rainbow/shapes/disk.hpp"

#include "../importers/obj_importer.hpp"
#include "../importers/ply_importer.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<shape> create_obj_mesh(const std::shared_ptr<metascene::shapes::mesh>& mesh)
	{
		return importers::load_obj_mesh(mesh->filename)[0];
	}

	std::shared_ptr<shape> create_ply_mesh(const std::shared_ptr<metascene::shapes::mesh>& mesh)
	{
		return importers::load_ply_mesh(mesh->filename);
	}
	
	std::shared_ptr<shape> create_mesh(const std::shared_ptr<metascene::shapes::mesh>& mesh)
	{
		if (mesh->mesh_type == metascene::shapes::mesh_type::obj)
			return create_obj_mesh(mesh);

		if (mesh->mesh_type == metascene::shapes::mesh_type::ply)
			return create_ply_mesh(mesh);
		
		logs::error("unknown mesh type.");

		return nullptr;
	}

	std::shared_ptr<shape> create_sphere(const std::shared_ptr<metascene::shapes::sphere>& sphere)
	{
		return std::make_shared<shapes::sphere>(sphere->radius, sphere->reverse_orientation);
	}

	std::shared_ptr<shape> create_disk(const std::shared_ptr<metascene::shapes::disk>& disk)
	{
		return std::make_shared<shapes::disk>(disk->radius, disk->height, disk->reverse_orientation);
	}

	std::shared_ptr<shape> create_triangles(const std::shared_ptr<metascene::shapes::triangles>& triangles)
	{
		return std::make_shared<mesh>(
			triangles->positions,
			std::vector<vector3>(),
			triangles->normals,
			triangles->uvs,
			triangles->indices,
			triangles->reverse_orientation);
	}
	
	std::shared_ptr<shape> create_shape(const std::shared_ptr<metascene::shapes::shape>& shape)
	{
		if (shape == nullptr) return nullptr;

		if (shape->type == metascene::shapes::type::disk)
			return create_disk(std::static_pointer_cast<metascene::shapes::disk>(shape));
		
		if (shape->type == metascene::shapes::type::mesh)
			return create_mesh(std::static_pointer_cast<metascene::shapes::mesh>(shape));

		if (shape->type == metascene::shapes::type::sphere)
			return create_sphere(std::static_pointer_cast<metascene::shapes::sphere>(shape));

		if (shape->type == metascene::shapes::type::triangles)
			return create_triangles(std::static_pointer_cast<metascene::shapes::triangles>(shape));
		
		logs::error("unknown shape.");

		return std::make_shared<sphere>(static_cast<real>(1));
	}
}
