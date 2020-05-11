#include "importers/mitsuba_importer.hpp"

int main() {
	const auto scene = rainbow::renderer::importers::load_mitsuba_scene("./../scenes/cbox/cbox.xml");

	scene.render_to("image");

	system("pause");
}