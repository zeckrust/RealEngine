#include "VecObject.h"

VecObject::VecObject(Primitype vType) : SceneObject() {
	type = vType;
}

VecObject::VecObject(Primitype vType, float sWidth, ofColor sColor, ofColor fColor, ofImage image) {
	type = vType;
	stroke_width = sWidth;
	stroke_color = sColor;
	fill_color = fColor;
	imported_image = image;
}

VecObject::VecObject(Primitype vType, float sWidth, ofColor sColor, ofColor fColor) {
	type = vType;
	stroke_width = sWidth;
	stroke_color = sColor;
	fill_color = fColor;
}

void VecObject::draw() {
	switch (type)
	{
	case Primitype::none:
		break;

	case Primitype::square:
		draw_square();
		break;

	case Primitype::line:
		draw_line();
		break;

	case Primitype::rectangle:
		draw_rectangle();
		break;

	case Primitype::ellipse:
		draw_ellipse();
		break;

	case Primitype::circle:
		draw_circle();
		break;
	case Primitype::image:
	case Primitype::sample:
		draw_image();
		break;

	case Primitype::stage1:
		draw_stage_1();
		break;

	case Primitype::stage2:
		draw_stage_2();
		break;
	default:
		break;
	}
}

void VecObject::draw_rectangle() const {
	draw_rectangle_from_param(position, dimensions);
}

void VecObject::draw_rectangle_from_param(ofVec3f _position, ofVec3f _dimension) const {
	ofPushStyle();

	ofFill();
	ofSetLineWidth(stroke_width);
	ofSetColor(fill_color);

	ofVec3f v0 = ofVec3f(_position.x, _position.y, _position.z);
	ofVec3f v1 = ofVec3f(_position.x + _dimension.x, _position.y, _position.z);
	ofVec3f v2 = ofVec3f(_position.x + _dimension.x, _position.y + _dimension.y, _position.z);
	ofVec3f v3 = ofVec3f(_position.x, _position.y + _dimension.y, _position.z);


	ofBeginShape();

	ofVertex(transformMatrix * v0);
	ofVertex(transformMatrix * v1);
	ofVertex(transformMatrix * v2);
	ofVertex(transformMatrix * v3);

	ofEndShape(true);

	ofNoFill();
	ofSetColor(stroke_color);
	ofBeginShape();

	ofVertex(transformMatrix * v0);
	ofVertex(transformMatrix * v1);
	ofVertex(transformMatrix * v2);
	ofVertex(transformMatrix * v3);

	ofEndShape(true);

	ofPopStyle();
}

void VecObject::draw_line() const {
	ofPolyline line;

	ofPushStyle();

	ofSetLineWidth(stroke_width);
	ofSetColor(stroke_color);
	
	line.addVertex(transformMatrix * position);
	line.addVertex(transformMatrix * (dimensions + position));
	line.draw();

	ofPopStyle();
}

void VecObject::draw_square() const {
	int formatX = dimensions.x;
	int formatY = dimensions.y;

	if (formatX < 0 && formatY < 0) {
		if (abs(formatX) > abs(formatY)) {
			formatY = formatX;
		}
		else {
			formatX = formatY;
		}
	}
	else if ((formatX > 0 && formatY < 0) || (formatX < 0 && formatY > 0)) {
		if (abs(formatX) > abs(formatY)) {
			formatY = -formatX;
		}
		else {
			formatX = -formatY;
		}
	}
	else {
		if (formatX > formatY) {
			formatY = formatX;
		}
		else {
			formatX = formatY;
		}
	}
	ofVec3f _dimension = ofVec3f(formatX, formatY, 0);

	draw_rectangle_from_param(position, _dimension);
}

void VecObject::draw_circle() const {

	int radius = sqrt(pow(dimensions.x, 2) + pow(dimensions.y, 2));

	ofPushStyle();
	ofFill();

	ofSetCircleResolution(100);

	ofSetLineWidth(stroke_width);
	ofSetColor(fill_color);

	ofDrawCircle(transformMatrix * position, transformMatrix.getScale().x * radius);

	ofNoFill();
	ofSetColor(stroke_color);
	ofDrawCircle(transformMatrix * position, transformMatrix.getScale().x * radius);

	ofPopStyle();
}

void VecObject::draw_ellipse() const {
	ofPushStyle();

	ofFill();
	ofSetLineWidth(stroke_width);
	ofSetColor(fill_color);

	ofDrawEllipse(transformMatrix * position, transformMatrix.getScale().x * 2 * dimensions.x, transformMatrix.getScale().y * 2 * dimensions.y);

	ofNoFill();
	ofSetColor(stroke_color);
	ofDrawEllipse(transformMatrix * position, transformMatrix.getScale().x * 2 * dimensions.x, transformMatrix.getScale().y * 2 * dimensions.y);

	ofPopStyle();
}

void VecObject::draw_stage_1() const {

	ofPushStyle();

	ofFill();
	ofSetLineWidth(stroke_width);
	ofSetColor(fill_color);

	ofVec3f v0 = ofVec3f(position.x, position.y, position.z);
	ofVec3f v1 = ofVec3f(position.x + dimensions.x, position.y, position.z);
	ofVec3f v2 = ofVec3f(position.x + (dimensions.x * 0.9), position.y + (dimensions.y * 0.5), position.z);
	ofVec3f v3 = ofVec3f(position.x + (dimensions.x * 0.95), position.y + dimensions.y, position.z);
	ofVec3f v4 = ofVec3f(position.x + (dimensions.x * 0.5), position.y + (dimensions.y * 0.9), position.z);
	ofVec3f v5 = ofVec3f(position.x + (dimensions.x * 0.05), position.y + dimensions.y, position.z);
	ofVec3f v6 = ofVec3f(position.x + (dimensions.x * 0.1), position.y + (dimensions.y * 0.5), position.z);
	ofVec3f v7 = ofVec3f(position.x, position.y, position.z);

	ofBeginShape();

	ofVertex(transformMatrix * v0);
	ofVertex(transformMatrix * v1);
	ofVertex(transformMatrix * v2);
	ofVertex(transformMatrix * v3);
	ofVertex(transformMatrix * v4);
	ofVertex(transformMatrix * v5);
	ofVertex(transformMatrix * v6);
	ofVertex(transformMatrix * v7);

	ofEndShape(true);

	ofNoFill();
	ofSetColor(stroke_color);
	ofBeginShape();

	ofVertex(transformMatrix * v0);
	ofVertex(transformMatrix * v1);
	ofVertex(transformMatrix * v2);
	ofVertex(transformMatrix * v3);
	ofVertex(transformMatrix * v4);
	ofVertex(transformMatrix * v5);
	ofVertex(transformMatrix * v6);
	ofVertex(transformMatrix * v7);

	ofEndShape(true);

	ofPopStyle();
}

void VecObject::draw_stage_2() const {
	ofPushStyle();

	ofFill();
	ofSetLineWidth(stroke_width);
	ofSetColor(fill_color);

	ofVec3f v0 = ofVec3f(position.x, position.y, position.z);
	ofVec3f v1 = ofVec3f(position.x + dimensions.x, position.y, position.z);

	ofVec3f v2 = ofVec3f(position.x + (dimensions.x * 0.9), position.y + (dimensions.y * 0.65), position.z);
	ofVec3f v3 = ofVec3f(position.x + (dimensions.x * 0.65), position.y + (dimensions.y * 0.65), position.z);

	ofVec3f v4 = ofVec3f(position.x + (dimensions.x * 0.65), position.y + dimensions.y, position.z);
	ofVec3f v5 = ofVec3f(position.x + (dimensions.x * 0.35), position.y + dimensions.y, position.z);

	ofVec3f v6 = ofVec3f(position.x + (dimensions.x * 0.35), position.y + (dimensions.y * 0.65), position.z);
	ofVec3f v7 = ofVec3f(position.x + (dimensions.x * 0.1), position.y + (dimensions.y * 0.65), position.z);

	ofVec3f v8 = ofVec3f(position.x, position.y, position.z);

	ofBeginShape();

	ofVertex(transformMatrix * v0);
	ofVertex(transformMatrix * v1);
	ofVertex(transformMatrix * v2);
	ofVertex(transformMatrix * v3);
	ofVertex(transformMatrix * v4);
	ofVertex(transformMatrix * v5);
	ofVertex(transformMatrix * v6);
	ofVertex(transformMatrix * v7);
	ofVertex(transformMatrix * v8);

	ofEndShape(true);

	ofNoFill();
	ofSetColor(stroke_color);
	ofBeginShape();

	ofVertex(transformMatrix * v0);
	ofVertex(transformMatrix * v1);
	ofVertex(transformMatrix * v2);
	ofVertex(transformMatrix * v3);
	ofVertex(transformMatrix * v4);
	ofVertex(transformMatrix * v5);
	ofVertex(transformMatrix * v6);
	ofVertex(transformMatrix * v7);
	ofVertex(transformMatrix * v8);

	ofEndShape(true);


	ofPopStyle();
}

void VecObject::draw_image() const {
	ofSetColor(255, 255, 255, 255);
	ofVec4f test = transformMatrix.getRowAsVec4f(0);
	imported_image.draw(
		transformMatrix.getRowAsVec4f(0).w + position.x,
		transformMatrix.getRowAsVec4f(1).w + position.y,
		transformMatrix.getScale().x * dimensions.x,
		transformMatrix.getScale().y * dimensions.y);
}

Primitype VecObject::getType() {
	return type;
}

float VecObject::getStrokeWidth() {
	return stroke_width;
}

ofColor VecObject::getFillColor() {
	return fill_color;
}

ofColor VecObject::getStrokeColor() {
	return stroke_color;
}

ofImage VecObject::getImage() {
	return imported_image;
}

void VecObject::setType(Primitype vType) {
	type = vType;
}

void VecObject::setStrokeWidth(float width) {
	stroke_width = width;
}

void VecObject::setStrokeColor(ofColor color) {
	stroke_color = color;
}

void VecObject::setFillColor(ofColor color) {
	fill_color = color;
}

void VecObject::setImage(ofImage _imported_image) {
	imported_image = _imported_image;
}