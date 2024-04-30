#include "GeObject.h"

GeObject::GeObject(Geotype gType, float sWidth, ofColor sColor, ofColor fColor) :SceneObject() {
	type = gType;
	stroke_width = sWidth;
	stroke_color = sColor;
	fill_color = fColor;
}

void GeObject::draw() {
	ofMesh filled_mesh;
	ofMesh wire_mesh;
	ofEnableDepthTest();
	ofSetLineWidth(stroke_width);
	switch (type)
	{
	case Geotype::none:
		break;
	case Geotype::rectangulaire:
		filled_mesh = draw_prisme_rect(fill_color);
		wire_mesh = draw_prisme_rect(stroke_color);
		filled_mesh.draw();
		wire_mesh.drawWireframe();
		break;
	case Geotype::cylindre:
		filled_mesh = draw_cylindre(fill_color);
		wire_mesh = draw_cylindre(stroke_color);
		filled_mesh.draw();
		wire_mesh.drawWireframe();
		break;
	default:
		break;
	}
	ofDisableDepthTest();
}

ofMesh GeObject::draw_cylindre(ofColor color) {
	ofMesh mesh;

	float radius = sqrt(pow(dimensions.x/2, 2) + pow(dimensions.z/2, 2));

	// Top octogone
	mesh.addVertex(transformMatrix * ofPoint(position.x - radius, position.y, position.z)); //V0
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x - (radius * sqrt(2) / 2), position.y, position.z + (radius * sqrt(2) / 2))); //V1
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y, position.z + radius)); //V2
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + (radius * sqrt(2) / 2), position.y, position.z + (radius * sqrt(2) / 2))); //V3
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + radius, position.y, position.z)); //V4
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + (radius * sqrt(2) / 2), position.y, position.z - (radius * sqrt(2) / 2))); //V5
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y, position.z - radius)); //V6
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x - (radius * sqrt(2) / 2), position.y, position.z - (radius * sqrt(2) / 2))); //V7
	mesh.addColor(color);

	//Botom octogone
	mesh.addVertex(transformMatrix * ofPoint(position.x - radius, position.y - dimensions.y, position.z)); //V8
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x - (radius * sqrt(2) / 2), position.y - dimensions.y, position.z + (radius * sqrt(2) / 2))); //V9
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y - dimensions.y, position.z + radius)); //V10
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + (radius * sqrt(2) / 2), position.y - dimensions.y, position.z + (radius * sqrt(2) / 2))); //V11
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + radius, position.y - dimensions.y, position.z)); //V12
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + (radius * sqrt(2) / 2), position.y - dimensions.y, position.z - (radius * sqrt(2) / 2))); //V13
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y - dimensions.y, position.z - radius)); //V14
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x - (radius * sqrt(2) / 2), position.y - dimensions.y, position.z - (radius * sqrt(2) / 2))); //V15
	mesh.addColor(color);

	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y, position.z)); //V16
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y - dimensions.y, position.z)); //V17
	mesh.addColor(color);

	for (int i = 0; i < 8; i++) {
		mesh.addTriangle(i, i + 1, 16);
	}

	for (int i = 0; i < 7; i++) {
		mesh.addTriangle(i, i + 9, i + 8);
		mesh.addTriangle(i, i + 9, i + 1);
	}

	mesh.addTriangle(7, 8, 15);
	mesh.addTriangle(7, 8, 0);

	for (int i = 8; i < 16; i++) {
		mesh.addTriangle(i, i + 1, 17);
	}

	return mesh;
}

ofMesh GeObject::draw_prisme_rect(ofColor color) {

	ofMesh mesh;

	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y, position.z)); //V0
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + dimensions.x, position.y, position.z)); //V1
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + dimensions.x, position.y, position.z + dimensions.z)); //V2
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y, position.z + dimensions.z)); //V3
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y - dimensions.y, position.z)); //V4
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + dimensions.x, position.y - dimensions.y, position.z)); //V5
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + dimensions.x, position.y - dimensions.y, position.z + dimensions.z)); //V6
	mesh.addColor(color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y - dimensions.y, position.z + dimensions.z)); //V7
	mesh.addColor(color);

	mesh.addTriangle(0, 2, 1);
	mesh.addTriangle(0, 2, 3);

	mesh.addTriangle(0, 7, 4);
	mesh.addTriangle(0, 7, 3);

	mesh.addTriangle(0, 5, 1);
	mesh.addTriangle(0, 5, 4);

	mesh.addTriangle(6, 1, 5);
	mesh.addTriangle(6, 1, 2);

	mesh.addTriangle(6, 4, 5);
	mesh.addTriangle(6, 4, 7);

	mesh.addTriangle(6, 3, 2);
	mesh.addTriangle(6, 3, 7);

	return mesh;
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
