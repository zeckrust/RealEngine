#include "Camera2d.h"

Camera2d::Camera2d() {
	lastMousePosition = glm::vec2();
	images = std::vector<SceneObject*>();
}

void Camera2d::setLastMousePosition(glm::vec2 position) {
	lastMousePosition = position;
}

void Camera2d::moveCamera(int x, int y) {
	glm::vec2 mousePosition = glm::vec2(x, y);
	glm::vec2 mouseMovement = mousePosition - lastMousePosition;
	for (int i = 0; i < std::size(images); i++) {
		if (images[i] != nullptr) {
			glm::vec3 imagePosition = images[i]->getPosition() + mouseMovement;

			images[i]->setPosition(imagePosition);

		}
	}
	lastMousePosition = mousePosition;
}

void Camera2d::addImage(SceneObject* image) {
	images.push_back(image);
}

void Camera2d::removeImage(SceneObject* image) {
	for (int i = 0; i < std::size(images); i++) {
		if (images[i] != nullptr && image == images[i]) {
			images.erase(images.begin()+i);
		}
	}
}