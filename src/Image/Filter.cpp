#include "Filter.h"

Filter::Filter() {

}

void Filter::setup(FilterType type) {
	switch (type) {
		case GRAY:
			shader.load("shaders/gray_filter_vert.glsl", "shaders/gray_filter_frag.glsl");
			texture_location = 0;
			break;
		case KELVIN:
			shader.load("shaders/kelvin_filter_vert.glsl", "shaders/kelvin_filter_frag.glsl");
			texture_location = 1;
			break;
		case NASHVILLE:
			shader.load("shaders/nashville_filter_vert.glsl", "shaders/kelvin_filter_frag.glsl");
			texture_location = 2;
			break;
		default:
			break;
	}
}

void Filter::begin(void) {
	shader.begin();
}

void Filter::end(void) {
	shader.end();
}

void Filter::setTexture(ofImage &texture) {
	shader.setUniformTexture("texture_image", texture.getTexture(), texture_location);
}
