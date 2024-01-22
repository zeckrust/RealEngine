#pragma once

#include "ofMain.h"

class Object2d
{
	public:
		Object2d();
		Object2d(glm::vec2 _position, int _radius);
		void setPosition(glm::vec2 position);
		glm::vec2 getPosition();
		int getRadius();

	private:
		glm::vec2 position;
		int radius;
};