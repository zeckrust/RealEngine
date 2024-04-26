#include "SceneObject.h"

SceneObject::SceneObject(glm::vec3 _position, glm::vec3 _dimensions) : position(_position), dimensions(_dimensions) {
	transformMatrix.makeIdentityMatrix();
	selected = false;
}

SceneObject::SceneObject() {
	selected = false;
}

//void SceneObject::draw(void) {}

void SceneObject::setPosition(glm::vec3 _position) {
	position = _position;
}

void SceneObject::setDimensions(glm::vec3 _dimensions) {
	dimensions = _dimensions;
}

void SceneObject::setTransformMatrix(ofMatrix4x4 _transformMatrix) {
	transformMatrix = _transformMatrix;
}

ofVec3f SceneObject::getPosition() {
	return position;
}

ofVec3f SceneObject::getDimensions() {
	return dimensions;
}

ofMatrix4x4 SceneObject::getTransformMatrix(void) {
	return transformMatrix;
}

void SceneObject::setSelected(bool status) {
	selected = status;
}

bool SceneObject::getSelected(void) {
	return selected;
}