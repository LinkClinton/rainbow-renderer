#include "importers/mitsuba_importer.hpp"

using namespace rainbow;

int main() {
	const auto scene = renderer::importers::import_mitsuba_scene("./../scenes/cbox/cbox.xml");

	scene.render_to("image");

	system("pause");
}