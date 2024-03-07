#include "VecObject.h"

VecObject::VecObject(Primitype vType) : SceneObject() {
	type = vType;
}

Primitype VecObject::getType() {
	return type;
}

float VecObject::getStrokeWidth() {
	return stroke_width;
}

ofColor VecObject::getFillColor() {
	return fill_color;
}

ofColor VecObject::getStrokeColor() {
	return stroke_color;
}

ofImage VecObject::getImage() {
	return imported_image;
}

void VecObject::setType(Primitype vType) {
	type = vType;
}

void VecObject::setStrokeWidth(float width) {
	stroke_width = width;
}

void VecObject::setStrokeColor(ofColor color) {
	stroke_color = color;
}

void VecObject::setFillColor(ofColor color) {
	fill_color = color;
}

void VecObject::setImage(ofImage _imported_image) {
	imported_image = _imported_image;
}