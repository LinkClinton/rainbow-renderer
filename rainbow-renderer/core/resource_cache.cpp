#include "resource_cache.hpp"

#include "../converter/convert_texture.hpp"

#include "../importers/image_importer.hpp"
#include "../importers/obj_importer.hpp"
#include "../importers/ply_importer.hpp"

std::shared_ptr<image_texture_t<2, color_spectrum>> rainbow::renderer::resource_cache::read_spectrum_texture(
	const std::string& filename, bool gamma)
{
	if (spectrum_textures.find(filename) != spectrum_textures.end())
		return spectrum_textures.at(filename);

	return spectrum_textures[filename] = importers::read_texture2d<spectrum>(filename, gamma);
}

std::shared_ptr<image_texture_t<2, float>> rainbow::renderer::resource_cache::read_real_texture(
	const std::string& filename, bool gamma)
{
	if (real_textures.find(filename) != real_textures.end())
		return real_textures.at(filename);

	return real_textures[filename] = importers::read_texture2d<real>(filename, gamma);
}

std::shared_ptr<mesh> rainbow::renderer::resource_cache::read_ply_mesh(
	const std::shared_ptr<metascene::shapes::mesh>& mesh)
{
	const auto index = mesh->to_string();

	if (meshes.find(index) != meshes.end()) return meshes.at(index);

	const auto triangles = importers::load_ply_mesh(mesh->filename);

	return meshes[index] = std::make_shared<cpus::shapes::mesh>(
		mesh->mask == nullptr ? nullptr : converter::create_real_texture(mesh->mask),
		triangles->positions, std::vector<vector3>(), triangles->normals,
		triangles->uvs, triangles->indices, mesh->reverse_orientation);
}

std::shared_ptr<mesh> rainbow::renderer::resource_cache::read_obj_mesh(const std::string& filename)
{
	if (meshes.find(filename) != meshes.end()) return meshes.at(filename);

	return meshes[filename] = importers::load_obj_mesh(filename)[0];
}
