#pragma once

#include "ofMain.h"
#include "../Image/SceneObject.h"

class Camera2d
{
	public:
		Camera2d();
		void setLastMousePosition(glm::vec2 position);
		void moveCamera(int x, int y);
		void addImage(SceneObject* image);
		void removeImage(SceneObject* image);

	private:
		glm::vec2 lastMousePosition;
		std::vector<SceneObject*> images;
};
