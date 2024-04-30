#pragma once

#include "ofMain.h"
#include "SceneObject.h"

class BezierPlane : public SceneObject
{
	public:
		BezierPlane(ofVec3f p1, ofVec3f p2, ofVec3f p3, ofVec3f p4, int s_width, ofColor s_color, ofColor f_color);

	private:
		int stroke_width;
		ofColor stroke_color;
		ofColor fill_color;
		int resolution;
		std::vector<ofVec3f> ctrl_pts;

		std::vector<std::vector<ofVec3f>> input;
		std::vector<std::vector<ofVec3f>> output;
		ofVec3f curve_pts_position(double u, double v);
		void generate_ctrl_pts();
		void setup_mesh(void);

		void draw(void);

		ofVboMesh mesh;
		ofVboMesh wire_mesh;

};