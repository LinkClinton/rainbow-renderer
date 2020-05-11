#include "obj_importer.hpp"

#include "rainbow/shared/logs/log.hpp"

#ifdef __OBJ_LOADER__

#include <tiny_obj_loader.h>

#endif

#ifdef __OBJ_LOADER__

std::vector<std::shared_ptr<rainbow::mesh>> rainbow::renderer::importers::load_obj_mesh(const std::string& file_name)
{
	std::vector<tinyobj::material_t> materials;
	std::vector<tinyobj::shape_t> shapes;
	tinyobj::attrib_t attribute;

	std::string warning;
	std::string error;

	const auto ret = LoadObj(&attribute, &shapes, &materials, &warning, &error, file_name.c_str());

	if (!warning.empty()) logs::warn(warning);
	if (!error.empty()) logs::error(error);

	if (!ret) return {};

	std::vector<std::shared_ptr<mesh>> meshes;

	for (const auto& shape : shapes) {
		std::vector<unsigned> indices;
		std::vector<vector3> positions;
		std::vector<vector3> normals;
		std::vector<vector3> uvs;

		for (const auto& index : shape.mesh.indices) {

			if (attribute.vertices.empty() == false)
				positions.push_back(vector3(
					attribute.vertices[3ULL * index.vertex_index + 0],
					attribute.vertices[3ULL * index.vertex_index + 1],
					attribute.vertices[3ULL * index.vertex_index + 2]
				));

			if (attribute.normals.empty() == false)
				normals.push_back(vector3(
					attribute.normals[3ULL * index.normal_index + 0],
					attribute.normals[3ULL * index.normal_index + 1],
					attribute.normals[3ULL * index.normal_index + 2]
				));

			if (attribute.texcoords.empty() == false)
				uvs.push_back(vector3(
					attribute.texcoords[2ULL * index.texcoord_index + 0],
					attribute.texcoords[2ULL * index.texcoord_index + 1],
					0
				));

			indices.push_back(static_cast<unsigned>(indices.size()));
		}

		meshes.push_back(std::make_shared<mesh>(positions, std::vector<vector3>(), normals, uvs, indices));
	}

	return meshes;
}

#endif