#include "GeObject.h"

GeObject::GeObject(Geotype gType, float sWidth, ofColor sColor, ofColor fColor) :SceneObject() {
	type = gType;
	stroke_width = sWidth;
	stroke_color = sColor;
	fill_color = fColor;
}

void GeObject::draw() {
	switch (type)
	{
	case Geotype::none:
		break;
	case Geotype::rectangulaire:
		draw_prisme_rect();
		break;
	case Geotype::cylindre:
		draw_cylindre();
		break;
	default:
		break;
	}
}

void GeObject::draw_cylindre() {

	ofEnableDepthTest();

	ofCylinderPrimitive newCylinder;
	newCylinder.set(dimensions.x/2, dimensions.y);
	newCylinder.setPosition(position.x, position.y, 25);

	ofFill();
	ofSetColor(fill_color);
	
	newCylinder.draw();

	ofSetColor(stroke_color);
	newCylinder.drawWireframe();
	
	ofDisableDepthTest();
}

void GeObject::draw_prisme_rect() {
	ofBoxPrimitive newBox;
	newBox.set(dimensions.x, dimensions.y, 40);
	newBox.setPosition(position.x, position.y, 15);

	ofNoFill();
	ofSetColor(fill_color);
	newBox.panDeg(45);
	newBox.drawWireframe();
	
	//newBox.draw();
	//ofDrawBox(position, dimensions.x);
	//ofNoFill();
	//ofSetColor(stroke_color);
	//ofDrawBox(position, sqrt(pow(dimensions.x, 2) + pow(dimensions.y, 2)));
}

Geotype GeObject::getType(void) {
	return type;
}

float GeObject::getStrokeWidth(void) {
	return stroke_width;
}

ofColor GeObject::getStrokeColor(void) {
	return stroke_color;
}

ofColor GeObject::getFillColor(void) {
	return fill_color;
}

void GeObject::setType(Geotype gType) {
	type = gType;
}

void GeObject::setStrokeWidth(float width) {
	stroke_width = width;
}

void GeObject::setStrokeColor(ofColor color) {
	stroke_color = color;
}

void GeObject::setFillColor(ofColor color) {
	fill_color = color;
}