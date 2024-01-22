#include "Object2d.h"

Object2d::Object2d() {
	position = glm::vec2(ofGetWidth() * .5, ofGetHeight() * .5);
	radius = 50;
}

Object2d::Object2d(glm::vec2 _position, int _radius) : position(_position), radius(_radius) {

}

void Object2d::setPosition(glm::vec2 _position) {
	position = _position;
}

glm::vec2 Object2d::getPosition() {
	return position;
}

int Object2d::getRadius() {
	return radius;
}