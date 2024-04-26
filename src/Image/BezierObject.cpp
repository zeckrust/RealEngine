#include "BezierObject.h"

BezierObject::BezierObject(ofVec3f p1, ofVec3f p2, ofVec3f p3, ofVec3f p4, float width, ofColor stroke) : SceneObject () {
	ctrl_point1 = p1;
	ctrl_point2 = p2;
	ctrl_point3 = p3;
	ctrl_point4 = p4;

	resolution = 100;

	stroke_width = width;
	stroke_color = stroke;

	for (int index = 0; index < resolution; index++)
		line_renderer.addVertex(ofPoint());
	
	update();
}

void BezierObject::postitionCalc(float t) {
	float u = 1 - t;
	float uu = u * u;
	float uuu = uu * u;
	float tt = t * t;
	float ttt = tt * t;

	position.x = uuu * ctrl_point1.x + 3 * uu * t * ctrl_point2.x + 3 * u * tt * ctrl_point3.x + ttt * ctrl_point4.x;
	position.y = uuu * ctrl_point1.y + 3 * uu * t * ctrl_point2.y + 3 * u * tt * ctrl_point3.y + ttt * ctrl_point4.y;
	position.z = uuu * ctrl_point1.z + 3 * uu * t * ctrl_point2.z + 3 * u * tt * ctrl_point3.z + ttt * ctrl_point4.z;

}

float interpolation_smoothstep(float value1, float value2, float t)
{
	if (t < 0.0f)
		return t = 0.0f;

	if (t > 1.0f)
		return t = 1.0f;

	t = t * t * (3.0f - 2.0f * t);

	return (1.0 - t) * value1 + t * value2;
}

void BezierObject::update() {
	for (int index = 0; index < resolution; index++) {
		postitionCalc(index / (float)resolution);
		line_renderer[index] = position;
	}
}

void BezierObject::draw() {
	//Ligne
	ofSetColor(stroke_color);
	ofSetLineWidth(stroke_width);
	line_renderer.draw();

	//Points de controles
	if (selected)
	{
		ofSetColor(255, 0, 0);
		ofDrawEllipse(ctrl_point1.x, ctrl_point1.y, 16.0f, 16.0f);
		ofDrawEllipse(ctrl_point2.x, ctrl_point2.y, 16.0f, 16.0f);
		ofDrawEllipse(ctrl_point3.x, ctrl_point3.y, 16.0f, 16.0f);
		ofDrawEllipse(ctrl_point4.x, ctrl_point4.y, 16.0f, 16.0f);
	}
}

ofColor BezierObject::getStrokeColor(void) {
	return stroke_color;
}

float BezierObject::getStrokeWidth(void) {
	return stroke_width;
}