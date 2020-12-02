#include "ply_importer.hpp"

#ifdef __PLY_IMPORTER__

#define TINYPLY_IMPLEMENTATION

#include "tinyply.h"

#include <fstream>

using namespace rainbow::core::math;
using namespace rainbow::core;

namespace rainbow::renderer::importers {

	size_t size_of_type(const tinyply::Type& type) {
		switch (type) {
		case tinyply::Type::INT8: return 1;
		case tinyply::Type::INT16: return 2;
		case tinyply::Type::INT32: return 4;
		case tinyply::Type::UINT8: return 1;
		case tinyply::Type::UINT16: return 2;
		case tinyply::Type::UINT32: return 4;
		case tinyply::Type::FLOAT32: return 4;
		case tinyply::Type::FLOAT64: return 8;
		case tinyply::Type::INVALID: throw "invalid type.";
		}

		return 0;
	}

	unsigned read_unsigned(const tinyply::Type& type, void* data)
	{
		switch (type) {
		case tinyply::Type::INT8: return static_cast<unsigned>(*static_cast<char*>(data));
		case tinyply::Type::INT16: return static_cast<unsigned>(*static_cast<short*>(data));
		case tinyply::Type::INT32: return static_cast<unsigned>(*static_cast<int*>(data));
		case tinyply::Type::UINT8: return static_cast<unsigned>(*static_cast<unsigned char*>(data));
		case tinyply::Type::UINT16: return static_cast<unsigned>(*static_cast<unsigned short*>(data));
		case tinyply::Type::UINT32: return static_cast<unsigned>(*static_cast<unsigned int*>(data));
		case tinyply::Type::FLOAT32:
		case tinyply::Type::FLOAT64:
		case tinyply::Type::INVALID:
			throw "invalid type";
		}

		return 0;
	}

	real read_real(const tinyply::Type& type, void* data)
	{
		if (type == tinyply::Type::FLOAT32) return static_cast<real>(*static_cast<float*>(data));
		if (type == tinyply::Type::FLOAT64) return static_cast<real>(*static_cast<double*>(data));

		throw "invalid type";
	}

	void read_unsigned_from_data(const std::shared_ptr<tinyply::PlyData>& data, std::vector<unsigned>& values)
	{
		const auto offset = size_of_type(data->t);
		const auto buffer = data->buffer.get();
		
		for (size_t index = 0; index < data->buffer.size_bytes(); index += offset) 
			values.push_back(read_unsigned(data->t, buffer + index));
	}

	void read_vector3_from_data(const std::shared_ptr<tinyply::PlyData>& data, std::vector<vector3>& values)
	{
		const auto offset = size_of_type(data->t) * 3;
		const auto buffer = data->buffer.get();

		for (size_t index = 0; index < data->buffer.size_bytes(); index += offset) {
			const auto x = read_real(data->t, buffer + index + sizeof(real) * 0);
			const auto y = read_real(data->t, buffer + index + sizeof(real) * 1);
			const auto z = read_real(data->t, buffer + index + sizeof(real) * 2);

			values.push_back(vector3(x, y, z));
		}
	}

	void read_vector2_from_data(const std::shared_ptr<tinyply::PlyData>& data, std::vector<vector3>& values)
	{
		const auto offset = size_of_type(data->t) * 2;
		const auto buffer = data->buffer.get();

		for (size_t index = 0; index < data->buffer.size_bytes(); index += offset) {
			const auto x = read_real(data->t, buffer + index + sizeof(real) * 0);
			const auto y = read_real(data->t, buffer + index + sizeof(real) * 1);
			
			values.push_back(vector3(x, y, 0));
		}
	}

	std::shared_ptr<meta_scene::objects::internal::triangles> load_ply_mesh(const std::string& filename)
	{
		auto stream = std::ifstream(filename, std::ios::binary);

		tinyply::PlyFile file;

		file.parse_header(stream);

		std::string normal_element = "vertex";
		std::string uv_element = "vertex";

		/*for (const auto& element : file.get_elements()) {
			for (const auto& property : element.properties) {
				if (property.name == "nx" || property.name == "ny" || property.name == "nz")
					normal_element = element.name;

				if (property.name == "u" || property.name == "v")
					uv_element = element.name;
			}
		}*/
		
		const auto indices = file.request_properties_from_element("face", { "vertex_indices" });

		const auto positions = file.request_properties_from_element("vertex", { "x", "y", "z" });

		std::shared_ptr<PlyData> normals;
		std::shared_ptr<PlyData> uvs;


		if (!normal_element.empty())
			normals = file.request_properties_from_element(normal_element, { "nx", "ny", "nz" });
		
		if (!uv_element.empty())
			uvs = file.request_properties_from_element(uv_element, { "u", "v" });
		
		file.read(stream);

		auto triangles = std::make_shared<meta_scene::objects::internal::triangles>();
		
		if (indices) read_unsigned_from_data(indices, triangles->indices);
		
		if (positions) read_vector3_from_data(positions, triangles->positions);
		if (normals) read_vector3_from_data(normals, triangles->normals);
		if (uvs) read_vector2_from_data(uvs, triangles->uvs);

		return triangles;
	}
	
}

#endif