#include "shape.hpp"

#include "meta-scene/shapes/sphere.hpp"
#include "meta-scene/shapes/mesh.hpp"

#include "rainbow/shared/logs/log.hpp"
#include "rainbow/shapes/sphere.hpp"
#include "rainbow/shapes/mesh.hpp"

#include "../importers/obj_importer.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<shape> create_obj_mesh(const std::shared_ptr<metascene::shapes::mesh>& mesh)
	{
		return importers::load_obj_mesh(mesh->filename)[0];
	}

	std::shared_ptr<shape> create_mesh(const std::shared_ptr<metascene::shapes::mesh>& mesh)
	{
		if (mesh->mesh_type == metascene::shapes::mesh_type::obj)
			return create_obj_mesh(mesh);

		logs::error("unknown mesh type.");

		return nullptr;
	}

	std::shared_ptr<shape> create_sphere(const std::shared_ptr<metascene::shapes::sphere>& sphere)
	{
		return std::make_shared<shapes::sphere>(sphere->radius, sphere->reverse_orientation);
	}

	std::shared_ptr<shape> create_shape(const std::shared_ptr<metascene::shapes::shape>& shape)
	{
		if (shape == nullptr) return nullptr;
		
		if (shape->type == metascene::shapes::type::mesh)
			return create_mesh(std::static_pointer_cast<metascene::shapes::mesh>(shape));

		if (shape->type == metascene::shapes::type::sphere)
			return create_sphere(std::static_pointer_cast<metascene::shapes::sphere>(shape));
		
		logs::error("unknown shape.");

		return std::make_shared<sphere>(static_cast<real>(1));
	}
}
