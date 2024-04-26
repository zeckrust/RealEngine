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
		ofVec3f getPosition();
		ofVec3f getDimensions();
		ofMatrix4x4 getTransformMatrix(void);
		void setSelected(bool status);
		bool getSelected(void);
		virtual void draw()=0;


	protected:
		ofVec3f position;
		ofVec3f dimensions;
		ofMatrix4x4 transformMatrix;
		int radius;
		bool selected;

};