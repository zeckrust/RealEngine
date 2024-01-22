#pragma once

#include "ofMain.h"
#include "../Image/Object2d.h"

class Camera2d
{
	public:
		Camera2d();
		void setLastMousePosition(glm::vec2 position);
		void moveCamera(int x, int y);
		void addImage(Object2d* image);
		void removeImage(Object2d* image);

	private:
		glm::vec2 lastMousePosition;
		std::vector<Object2d*> images;
};
