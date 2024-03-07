#pragma once

#include "ofMain.h"

class SceneObject
{
	public:
		SceneObject();
		SceneObject(glm::vec3 _position, glm::vec3 _dimensions);
		void setPosition(glm::vec3 _position);
		void setDimensions(glm::vec3 _dimensions);
		glm::vec3 getPosition();
		glm::vec3 getDimensions();

	private:
		glm::vec3 position;
		glm::vec3 dimensions;
		int radius;

};