#pragma once

#include "ofMain.h"
#include "SceneObject.h"

class BezierObject : public SceneObject
{
	public:
		BezierObject(ofVec3f p1, ofVec3f p2, ofVec3f p3, ofVec3f p4, float width, ofColor stroke);
		void draw() override;
		void update();
		ofColor getStrokeColor(void);
		float getStrokeWidth(void);

	private:
		void postitionCalc(float t);
		ofPolyline line_renderer;

		ofVec3f* selected_ctrl_point;

		ofVec3f ctrl_point1;
		ofVec3f ctrl_point2;
		ofVec3f ctrl_point3;
		ofVec3f ctrl_point4;

		ofVec3f position;

		float stroke_width;
		ofColor stroke_color;

		int resolution;
};