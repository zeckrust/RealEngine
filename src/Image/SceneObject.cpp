#include "SceneObject.h"

SceneObject::SceneObject(glm::vec3 _position, glm::vec3 _dimensions) : position(_position), dimensions(_dimensions) {
	transformMatrix.makeIdentityMatrix();
}

SceneObject::SceneObject() {

}

void SceneObject::setPosition(glm::vec3 _position) {
	position = _position;
}

void SceneObject::setDimensions(glm::vec3 _dimensions) {
	dimensions = _dimensions;
}

void SceneObject::setTransformMatrix(ofMatrix4x4 _transformMatrix) {
	transformMatrix = _transformMatrix;
}

glm::vec3 SceneObject::getPosition() {
	return position;
}

glm::vec3 SceneObject::getDimensions() {
	return dimensions;
}

ofMatrix4x4 SceneObject::getTransformMatrix(void) {
	return transformMatrix;
}
