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
	newCylinder.setPosition(position.x, position.y, position.z);
	newCylinder.set(dimensions.x/2, dimensions.y);

	ofFill();
	ofSetColor(fill_color);
	
	newCylinder.draw();
	ofSetColor(stroke_color);
	newCylinder.drawWireframe();
	
	ofDisableDepthTest();
}

void GeObject::draw_prisme_rect() {

	ofMesh mesh;

	mesh.setMode(OF_PRIMITIVE_LINES);
	mesh.enableColors();
	mesh.enableIndices();

	mesh.addVertex(ofPoint(position.x, position.y, position.z)); //V0
	mesh.addColor(stroke_color);
	mesh.addVertex(ofPoint(position.x + dimensions.x, position.y, position.z)); //V1
	mesh.addColor(stroke_color);
	mesh.addVertex(ofPoint(position.x + dimensions.x, position.y, position.z + dimensions.z)); //V2
	mesh.addColor(stroke_color);
	mesh.addVertex(ofPoint(position.x, position.y, position.z + dimensions.z)); //V3
	mesh.addColor(stroke_color);
	mesh.addVertex(ofPoint(position.x, position.y - dimensions.y, position.z)); //V4
	mesh.addColor(stroke_color);
	mesh.addVertex(ofPoint(position.x + dimensions.x, position.y - dimensions.y, position.z)); //V5
	mesh.addColor(stroke_color);
	mesh.addVertex(ofPoint(position.x + dimensions.x, position.y - dimensions.y, position.z + dimensions.z)); //V6
	mesh.addColor(stroke_color);
	mesh.addVertex(ofPoint(position.x, position.y - dimensions.y, position.z + dimensions.z)); //V7
	mesh.addColor(stroke_color);

	mesh.addIndex(0);
	mesh.addIndex(1);
	mesh.addIndex(0);
	mesh.addIndex(3);
	mesh.addIndex(0);
	mesh.addIndex(4);
	mesh.addIndex(1);
	mesh.addIndex(2);
	mesh.addIndex(1);
	mesh.addIndex(5);
	mesh.addIndex(2);
	mesh.addIndex(3);
	mesh.addIndex(2);
	mesh.addIndex(6);
	mesh.addIndex(3);
	mesh.addIndex(7);
	mesh.addIndex(4);
	mesh.addIndex(5);
	mesh.addIndex(5);
	mesh.addIndex(6);
	mesh.addIndex(6);
	mesh.addIndex(7);
	mesh.addIndex(7);
	mesh.addIndex(4);

	//ofFill();
	//ofSetColor(fill_color);
	mesh.drawFaces();

	/*ofBoxPrimitive newBox;
	newBox.setPosition(position.x, position.y, position.z);
	newBox.set(dimensions.x, dimensions.y, dimensions.z);

	ofNoFill();
	ofSetColor(fill_color);
	newBox.drawWireframe();*/
	
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