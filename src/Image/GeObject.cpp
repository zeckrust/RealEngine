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
	ofMesh mesh;

	//mesh.setMode(OF_PRIMITIVE_LINES);
	//mesh.enableColors();
	//mesh.enableIndices();

	float radius = sqrt(pow(dimensions.x/2, 2) + pow(dimensions.z/2, 2));

	// Top octogone
	mesh.addVertex(transformMatrix * ofPoint(position.x - radius, position.y, position.z)); //V0
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x - (radius * sqrt(2) / 2), position.y, position.z + (radius * sqrt(2) / 2))); //V1
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y, position.z + radius)); //V2
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + (radius * sqrt(2) / 2), position.y, position.z + (radius * sqrt(2) / 2))); //V3
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + radius, position.y, position.z)); //V4
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + (radius * sqrt(2) / 2), position.y, position.z - (radius * sqrt(2) / 2))); //V5
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y, position.z - radius)); //V6
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x - (radius * sqrt(2) / 2), position.y, position.z - (radius * sqrt(2) / 2))); //V7
	mesh.addColor(stroke_color);

	//Botom octogone
	mesh.addVertex(transformMatrix * ofPoint(position.x - radius, position.y - dimensions.y, position.z)); //V8
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x - (radius * sqrt(2) / 2), position.y - dimensions.y, position.z + (radius * sqrt(2) / 2))); //V9
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y - dimensions.y, position.z + radius)); //V10
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + (radius * sqrt(2) / 2), position.y - dimensions.y, position.z + (radius * sqrt(2) / 2))); //V11
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + radius, position.y - dimensions.y, position.z)); //V12
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + (radius * sqrt(2) / 2), position.y - dimensions.y, position.z - (radius * sqrt(2) / 2))); //V13
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y - dimensions.y, position.z - radius)); //V14
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x - (radius * sqrt(2) / 2), position.y - dimensions.y, position.z - (radius * sqrt(2) / 2))); //V15
	mesh.addColor(stroke_color);

	mesh.addTriangle(0, 1, 2);
	mesh.addTriangle(0, 2, 3);
	mesh.addTriangle(0, 3, 4);
	mesh.addTriangle(0, 4, 5);
	mesh.addTriangle(0, 5, 6);
	mesh.addTriangle(0, 6, 7);

	mesh.addTriangle(0, 9, 8);
	mesh.addTriangle(0, 9, 1);

	mesh.addTriangle(1, 10, 9);
	mesh.addTriangle(1, 10, 2);

	mesh.addTriangle(2, 11, 10);
	mesh.addTriangle(2, 11, 3);

	mesh.addTriangle(3, 12, 11);
	mesh.addTriangle(3, 12, 4);

	mesh.addTriangle(4, 13, 12);
	mesh.addTriangle(4, 13, 5);

	mesh.addTriangle(5, 14, 13);
	mesh.addTriangle(5, 14, 6);

	mesh.addTriangle(6, 15, 14);
	mesh.addTriangle(6, 15, 7);

	mesh.addTriangle(7, 8, 15);
	mesh.addTriangle(7, 8, 0);

	mesh.addTriangle(8, 9, 10);
	mesh.addTriangle(8, 10, 11);
	mesh.addTriangle(8, 11, 12);
	mesh.addTriangle(8, 12, 13);
	mesh.addTriangle(8, 13, 14);
	mesh.addTriangle(8, 14, 15);

	//mesh.addIndex(0);
	//mesh.addIndex(1);
	//mesh.addIndex(1);
	//mesh.addIndex(2);
	//mesh.addIndex(2);
	//mesh.addIndex(3);
	//mesh.addIndex(3);
	//mesh.addIndex(4);
	//mesh.addIndex(4);
	//mesh.addIndex(5);
	//mesh.addIndex(5);
	//mesh.addIndex(6);
	//mesh.addIndex(6);
	//mesh.addIndex(7);
	//mesh.addIndex(7);
	//mesh.addIndex(0);

	//mesh.addIndex(0);
	//mesh.addIndex(8);
	//mesh.addIndex(1);
	//mesh.addIndex(9);
	//mesh.addIndex(2);
	//mesh.addIndex(10);
	//mesh.addIndex(3);
	//mesh.addIndex(11);
	//mesh.addIndex(4);
	//mesh.addIndex(12);
	//mesh.addIndex(5);
	//mesh.addIndex(13);
	//mesh.addIndex(6);
	//mesh.addIndex(14);
	//mesh.addIndex(7);
	//mesh.addIndex(15);

	//mesh.addIndex(8);
	//mesh.addIndex(9);
	//mesh.addIndex(9);
	//mesh.addIndex(10);
	//mesh.addIndex(10);
	//mesh.addIndex(11);
	//mesh.addIndex(11);
	//mesh.addIndex(12);
	//mesh.addIndex(12);
	//mesh.addIndex(13);
	//mesh.addIndex(13);
	//mesh.addIndex(14);
	//mesh.addIndex(14);
	//mesh.addIndex(15);
	//mesh.addIndex(15);
	//mesh.addIndex(8);

	//ofFill();
	//ofSetColor(fill_color);
	//mesh.drawWireframe();

	mesh.draw();

}

void GeObject::draw_prisme_rect() {

	ofMesh mesh;

	//mesh.setMode(OF_PRIMITIVE_LINES);
	//mesh.enableColors();
	//mesh.enableIndices();

	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y, position.z)); //V0
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + dimensions.x, position.y, position.z)); //V1
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + dimensions.x, position.y, position.z + dimensions.z)); //V2
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y, position.z + dimensions.z)); //V3
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y - dimensions.y, position.z)); //V4
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + dimensions.x, position.y - dimensions.y, position.z)); //V5
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x + dimensions.x, position.y - dimensions.y, position.z + dimensions.z)); //V6
	mesh.addColor(stroke_color);
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y - dimensions.y, position.z + dimensions.z)); //V7
	mesh.addColor(stroke_color);

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

	//mesh.addIndex(0);
	//mesh.addIndex(1);
	//mesh.addIndex(0);
	//mesh.addIndex(3);
	//mesh.addIndex(0);
	//mesh.addIndex(4);
	//mesh.addIndex(1);
	//mesh.addIndex(2);
	//mesh.addIndex(1);
	//mesh.addIndex(5);
	//mesh.addIndex(2);
	//mesh.addIndex(3);
	//mesh.addIndex(2);
	//mesh.addIndex(6);
	//mesh.addIndex(3);
	//mesh.addIndex(7);
	//mesh.addIndex(4);
	//mesh.addIndex(5);
	//mesh.addIndex(5);
	//mesh.addIndex(6);
	//mesh.addIndex(6);
	//mesh.addIndex(7);
	//mesh.addIndex(7);
	//mesh.addIndex(4);

	//mesh.draw(OF_MESH_FILL);
	mesh.draw();
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
