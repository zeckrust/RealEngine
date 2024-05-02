#pragma once

#include "ofMain.h"
#include "SceneObject.h"
#include "Triangle.h"

class Maillage : public SceneObject 
{
	public :
		Maillage();
		void draw();
		void add_point(ofVec3f point, ofColor color);

	private:
		void triangulation();
		Triangle createSuperTriangle(void);
		void updateMesh(std::vector<Triangle> triangles);

		std::vector<Point> points;
		ofVboMesh mesh;

		size_t current_id;
};