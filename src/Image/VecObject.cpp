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
		ofSetColor(255, 255, 255, 255);
		//shape->getImage().draw(shape->getPosition().x, shape->getPosition().y, shape->getDimensions().x, shape->getDimensions().y);
		imported_image.draw(position.x, position.y, dimensions.x, dimensions.y);
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
	ofPushStyle();

	ofFill();
	ofSetLineWidth(stroke_width);
	ofSetColor(fill_color);

	ofDrawRectangle(position, dimensions.x, dimensions.y);

	ofNoFill();
	ofSetColor(stroke_color);
	ofDrawRectangle(position, dimensions.x, dimensions.y);

	ofPopStyle();
}

void VecObject::draw_line() const {
	ofPolyline line;

	ofPushStyle();

	ofSetLineWidth(stroke_width);
	ofSetColor(stroke_color);

	line.addVertex(position);
	line.addVertex(dimensions + position);
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

	ofPushStyle();

	ofSetLineWidth(stroke_width);
	ofSetColor(fill_color);

	ofDrawRectangle(position, formatX, formatY);

	ofNoFill();
	ofSetColor(stroke_color);
	ofDrawRectangle(position, formatX, formatY);

	ofPopStyle();
}

void VecObject::draw_circle() const {

	int radius = sqrt(pow(dimensions.x, 2) + pow(dimensions.y, 2));

	ofPushStyle();
	ofFill();

	ofSetCircleResolution(100);

	ofSetLineWidth(stroke_width);
	ofSetColor(fill_color);

	ofDrawCircle(position, radius);

	ofNoFill();
	ofSetColor(stroke_color);
	ofDrawCircle(position, radius);

	ofPopStyle();
}

void VecObject::draw_ellipse() const {
	ofPushStyle();

	ofFill();
	ofSetLineWidth(stroke_width);
	ofSetColor(fill_color);

	ofDrawEllipse(position, 2 * dimensions.x, 2 * dimensions.y);

	ofNoFill();
	ofSetColor(stroke_color);
	ofDrawEllipse(position, 2 * dimensions.x, 2 * dimensions.y);

	ofPopStyle();
}

void VecObject::draw_stage_1() const {

	ofPushStyle();

	ofFill();
	ofSetLineWidth(stroke_width);
	ofSetColor(fill_color);

	glm::vec3 v0 = glm::vec3(position.x, position.y, position.z);
	glm::vec3 v1 = glm::vec3(position.x + dimensions.x, position.y, position.z);
	glm::vec3 v2 = glm::vec3(position.x + (dimensions.x * 0.9), position.y + (dimensions.y * 0.5), position.z);
	glm::vec3 v3 = glm::vec3(position.x + (dimensions.x * 0.95), position.y + dimensions.y, position.z);
	glm::vec3 v4 = glm::vec3(position.x + (dimensions.x * 0.5), position.y + (dimensions.y * 0.9), position.z);
	glm::vec3 v5 = glm::vec3(position.x + (dimensions.x * 0.05), position.y + dimensions.y, position.z);
	glm::vec3 v6 = glm::vec3(position.x + (dimensions.x * 0.1), position.y + (dimensions.y * 0.5), position.z);
	glm::vec3 v7 = glm::vec3(position.x, position.y, position.z);

	ofBeginShape();

	ofVertex(v0);
	ofVertex(v1);
	ofVertex(v2);
	ofVertex(v3);
	ofVertex(v4);
	ofVertex(v5);
	ofVertex(v6);
	ofVertex(v7);

	ofEndShape(true);

	ofNoFill();
	ofSetColor(stroke_color);
	ofBeginShape();

	ofVertex(v0);
	ofVertex(v1);
	ofVertex(v2);
	ofVertex(v3);
	ofVertex(v4);
	ofVertex(v5);
	ofVertex(v6);
	ofVertex(v7);

	ofEndShape(true);

	ofPopStyle();
}


void VecObject::draw_stage_2() const {
	ofPushStyle();

	ofFill();
	ofSetLineWidth(stroke_width);
	ofSetColor(fill_color);

	glm::vec3 v0 = glm::vec3(position.x, position.y, position.z);
	glm::vec3 v1 = glm::vec3(position.x + dimensions.x, position.y, position.z);

	glm::vec3 v2 = glm::vec3(position.x + (dimensions.x * 0.9), position.y + (dimensions.y * 0.65), position.z);
	glm::vec3 v3 = glm::vec3(position.x + (dimensions.x * 0.65), position.y + (dimensions.y * 0.65), position.z);

	glm::vec3 v4 = glm::vec3(position.x + (dimensions.x * 0.65), position.y + dimensions.y, position.z);
	glm::vec3 v5 = glm::vec3(position.x + (dimensions.x * 0.35), position.y + dimensions.y, position.z);

	glm::vec3 v6 = glm::vec3(position.x + (dimensions.x * 0.35), position.y + (dimensions.y * 0.65), position.z);
	glm::vec3 v7 = glm::vec3(position.x + (dimensions.x * 0.1), position.y + (dimensions.y * 0.65), position.z);

	glm::vec3 v8 = glm::vec3(position.x, position.y, position.z);

	ofBeginShape();

	ofVertex(v0);
	ofVertex(v1);
	ofVertex(v2);
	ofVertex(v3);
	ofVertex(v4);
	ofVertex(v5);
	ofVertex(v6);
	ofVertex(v7);
	ofVertex(v8);

	ofEndShape(true);

	ofNoFill();
	ofSetColor(stroke_color);
	ofBeginShape();

	ofVertex(v0);
	ofVertex(v1);
	ofVertex(v2);
	ofVertex(v3);
	ofVertex(v4);
	ofVertex(v5);
	ofVertex(v6);
	ofVertex(v7);
	ofVertex(v8);

	ofEndShape(true);


	ofPopStyle();
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