#pragma once

#include "ofMain.h"

class SceneObject
{
	public:
		SceneObject();
		SceneObject(glm::vec3 _position, glm::vec3 _dimensions);
		void setPosition(glm::vec3 _position);
		void setDimensions(glm::vec3 _dimensions);
		void setTransformMatrix(ofMatrix4x4 _transformMatrix);
		glm::vec3 getPosition();
		glm::vec3 getDimensions();
		ofMatrix4x4 getTransformMatrix(void);

	private:
		glm::vec3 position;
		glm::vec3 dimensions;
		ofMatrix4x4 transformMatrix;
		int radius;

};