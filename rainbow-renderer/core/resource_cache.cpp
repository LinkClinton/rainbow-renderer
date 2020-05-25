#include "resource_cache.hpp"

#include "../importers/image_importer.hpp"
#include "../importers/obj_importer.hpp"
#include "../importers/ply_importer.hpp"

std::shared_ptr<rainbow::image_texture_t<2, rainbow::color_spectrum>> rainbow::renderer::resource_cache::read_spectrum_texture(
	const std::string& filename, bool gamma)
{
	if (spectrum_textures.find(filename) != spectrum_textures.end())
		return spectrum_textures.at(filename);

	return spectrum_textures[filename] = importers::read_texture2d<spectrum>(filename, gamma);
}

std::shared_ptr<rainbow::image_texture_t<2, float>> rainbow::renderer::resource_cache::read_real_texture(
	const std::string& filename, bool gamma)
{
	if (real_textures.find(filename) != real_textures.end())
		return real_textures.at(filename);

	return real_textures[filename] = importers::read_texture2d<real>(filename, gamma);
}

std::shared_ptr<rainbow::mesh> rainbow::renderer::resource_cache::read_ply_mesh(const std::string& filename)
{
	if (meshes.find(filename) != meshes.end()) return meshes.at(filename);

	return meshes[filename] = importers::load_ply_mesh(filename);
}

std::shared_ptr<rainbow::mesh> rainbow::renderer::resource_cache::read_obj_mesh(const std::string& filename)
{
	if (meshes.find(filename) != meshes.end()) return meshes.at(filename);

	return meshes[filename] = importers::load_obj_mesh(filename)[0];
}
