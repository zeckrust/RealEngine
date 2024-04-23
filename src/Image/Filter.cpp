#include "Filter.h"

Filter::Filter() {

}

void Filter::setup(FilterType type) {
	switch (type) {
		case GRAY:
			shader.load("shaders/gray_filter_vert.glsl", "shaders/gray_filter_frag.glsl");
			break;
		case KELVIN:
			shader.load("shaders/kelvin_filter_vert.glsl", "shaders/kelvin_filter_frag.glsl");
			break;
		case NASHVILLE:
			shader.load("shaders/nashville_filter_vert.glsl", "shaders/kelvin_filter_frag.glsl");
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
	shader.setUniformTexture("image", texture.getTexture(), 0);
}
