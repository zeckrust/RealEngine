#include "GeObject.h"

GeObject::GeObject(Geotype gType, float sWidth, ofColor sColor, ofColor fColor) :SceneObject() {
	type = gType;
	stroke_width = sWidth;
	stroke_color = sColor;
	fill_color = fColor;
	imported_texture = ofImage();
	texture_filter = nullptr;
	is_texture_loaded = false;
}

void GeObject::draw() {
	ofMesh filled_mesh;
	ofMesh wire_mesh;
	ofEnableDepthTest();

	ofPushStyle();
	ofSetLineWidth(stroke_width);
	switch (type)
	{
	case Geotype::none:
		break;
	case Geotype::rectangulaire:
		filled_mesh = draw_prisme_rect(fill_color);
		wire_mesh = draw_prisme_rect(stroke_color);
		ofSetColor(fill_color);
		filled_mesh.draw();
		break;
	case Geotype::cylindre:
		filled_mesh = draw_cylindre(fill_color);
		wire_mesh = draw_cylindre(stroke_color);
		ofSetColor(fill_color);
		filled_mesh.draw();
		ofSetColor(stroke_color);
		wire_mesh.drawWireframe();
		break;
	case Geotype::releif_effect:
		draw_releif_effect();
		break;
	default:
		break;
	}
	ofPopStyle();

	ofDisableDepthTest();
}

ofMesh GeObject::draw_cylindre(ofColor color) {
	ofMesh mesh;

	float radius = sqrt(pow(dimensions.x/2, 2) + pow(dimensions.z/2, 2));

	// Top octogone
	mesh.addVertex(transformMatrix * ofPoint(position.x - radius, position.y, position.z)); //V0
	mesh.addVertex(transformMatrix * ofPoint(position.x - (radius * sqrt(2) / 2), position.y, position.z + (radius * sqrt(2) / 2))); //V1
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y, position.z + radius)); //V2
	mesh.addVertex(transformMatrix * ofPoint(position.x + (radius * sqrt(2) / 2), position.y, position.z + (radius * sqrt(2) / 2))); //V3
	mesh.addVertex(transformMatrix * ofPoint(position.x + radius, position.y, position.z)); //V4
	mesh.addVertex(transformMatrix * ofPoint(position.x + (radius * sqrt(2) / 2), position.y, position.z - (radius * sqrt(2) / 2))); //V5
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y, position.z - radius)); //V6
	mesh.addVertex(transformMatrix * ofPoint(position.x - (radius * sqrt(2) / 2), position.y, position.z - (radius * sqrt(2) / 2))); //V7

	//Botom octogone
	mesh.addVertex(transformMatrix * ofPoint(position.x - radius, position.y - dimensions.y, position.z)); //V8
	mesh.addVertex(transformMatrix * ofPoint(position.x - (radius * sqrt(2) / 2), position.y - dimensions.y, position.z + (radius * sqrt(2) / 2))); //V9
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y - dimensions.y, position.z + radius)); //V10
	mesh.addVertex(transformMatrix * ofPoint(position.x + (radius * sqrt(2) / 2), position.y - dimensions.y, position.z + (radius * sqrt(2) / 2))); //V11
	mesh.addVertex(transformMatrix * ofPoint(position.x + radius, position.y - dimensions.y, position.z)); //V12
	mesh.addVertex(transformMatrix * ofPoint(position.x + (radius * sqrt(2) / 2), position.y - dimensions.y, position.z - (radius * sqrt(2) / 2))); //V13
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y - dimensions.y, position.z - radius)); //V14
	mesh.addVertex(transformMatrix * ofPoint(position.x - (radius * sqrt(2) / 2), position.y - dimensions.y, position.z - (radius * sqrt(2) / 2))); //V15

	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y, position.z)); //V16
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y - dimensions.y, position.z)); //V17

	for (int i = 0; i < 8; i++) {
		mesh.addTriangle(i, i + 1, 16);
	}
	mesh.addTriangle(7, 0, 16);

	for (int i = 0; i < 7; i++) {
		mesh.addTriangle(i, i + 9, i + 8);
		mesh.addTriangle(i, i + 9, i + 1);
	}

	mesh.addTriangle(7, 8, 15);
	mesh.addTriangle(7, 8, 0);

	for (int i = 8; i < 16; i++) {
		mesh.addTriangle(i, i + 1, 17);
	}
	mesh.addTriangle(15, 8, 17);

	return mesh;
}

ofMesh GeObject::draw_prisme_rect(ofColor color) {

	ofMesh mesh;

	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y, position.z)); //V0
	mesh.addVertex(transformMatrix * ofPoint(position.x + dimensions.x, position.y, position.z)); //V1
	mesh.addVertex(transformMatrix * ofPoint(position.x + dimensions.x, position.y, position.z + dimensions.z)); //V2
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y, position.z + dimensions.z)); //V3
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y - dimensions.y, position.z)); //V4
	mesh.addVertex(transformMatrix * ofPoint(position.x + dimensions.x, position.y - dimensions.y, position.z)); //V5
	mesh.addVertex(transformMatrix * ofPoint(position.x + dimensions.x, position.y - dimensions.y, position.z + dimensions.z)); //V6
	mesh.addVertex(transformMatrix * ofPoint(position.x, position.y - dimensions.y, position.z + dimensions.z)); //V7

	if (is_texture_loaded) {
		float tex_width = imported_texture.getWidth();
		float tex_height = imported_texture.getHeight();

		ofVec2f tex_v0 = ofVec2f(tex_width/4, tex_height/3);
		ofVec2f tex_v1 = ofVec2f(2*tex_width/4, tex_height/3);
		ofVec2f tex_v2 = ofVec2f(3*tex_width/4, tex_height/3);
		ofVec2f tex_v3 = ofVec2f(0, tex_height/3);
		ofVec2f tex_v4 = ofVec2f(tex_width/4, 2*tex_height/3);
		ofVec2f tex_v5 = ofVec2f(2*tex_width/4, 2*tex_height/3);
		ofVec2f tex_v6 = ofVec2f(3*tex_width/4, 2*tex_height/3);
		ofVec2f tex_v7 = ofVec2f(0, 2*tex_height/3);

		// Bottom face
		mesh.addTexCoord(tex_v3); 
		mesh.addTexCoord(tex_v0);
		mesh.addTexCoord(tex_v1);
		mesh.addTexCoord(tex_v2);

		// Top face
		mesh.addTexCoord(tex_v4);
		mesh.addTexCoord(tex_v7);
		mesh.addTexCoord(tex_v6);
		mesh.addTexCoord(tex_v5);

		// Front face
		mesh.addTexCoord(tex_v0);
		mesh.addTexCoord(tex_v4);
		mesh.addTexCoord(tex_v5);
		mesh.addTexCoord(tex_v1);

		// Back face
		mesh.addTexCoord(tex_v2);
		mesh.addTexCoord(tex_v6);
		mesh.addTexCoord(tex_v7);
		mesh.addTexCoord(tex_v3);

		// Left face
		mesh.addTexCoord(tex_v3);
		mesh.addTexCoord(tex_v7);
		mesh.addTexCoord(tex_v4);
		mesh.addTexCoord(tex_v0);
		
		// Right face
		mesh.addTexCoord(tex_v1);
		mesh.addTexCoord(tex_v5);
		mesh.addTexCoord(tex_v6);
		mesh.addTexCoord(tex_v2);

		// Bottom face
		mesh.addIndex(3); mesh.addIndex(0); mesh.addIndex(1);
		mesh.addIndex(3); mesh.addIndex(1); mesh.addIndex(2);

		// Top face
		mesh.addIndex(4); mesh.addIndex(7); mesh.addIndex(6);
		mesh.addIndex(4); mesh.addIndex(6); mesh.addIndex(5);

		// Front face
		mesh.addIndex(0); mesh.addIndex(4); mesh.addIndex(5);
		mesh.addIndex(0); mesh.addIndex(5); mesh.addIndex(1);

		// Back face
		mesh.addIndex(2); mesh.addIndex(6); mesh.addIndex(7);
		mesh.addIndex(2); mesh.addIndex(7); mesh.addIndex(3);

		// Left face
		mesh.addIndex(3); mesh.addIndex(7); mesh.addIndex(4);
		mesh.addIndex(3); mesh.addIndex(4); mesh.addIndex(0);

		// Right face
		mesh.addIndex(1); mesh.addIndex(5); mesh.addIndex(6);
		mesh.addIndex(1); mesh.addIndex(6); mesh.addIndex(2);

		ofPushStyle();
		ofSetColor(255, 255, 255, 255);

		imported_texture.bind();
		mesh.draw();
		imported_texture.unbind();

		ofPopStyle();
	}
	else {
		mesh.addTriangle(0, 1, 2);
		mesh.addTriangle(0, 2, 3);

		mesh.addTriangle(0, 7, 4);
		mesh.addTriangle(0, 3, 7);

		mesh.addTriangle(0, 5, 1);
		mesh.addTriangle(0, 4, 5);

		mesh.addTriangle(6, 1, 5);
		mesh.addTriangle(6, 2, 1);

		mesh.addTriangle(6, 2, 3);
		mesh.addTriangle(6, 3, 7);

		mesh.addTriangle(6, 5, 4);
		mesh.addTriangle(6, 4, 7);

		mesh.addTriangle(6, 3, 2);
		mesh.addTriangle(6, 3, 7);
	}

	return mesh;
}

void draw_releif_effect(void) {
	ofMesh mesh;

	
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

void GeObject::setTexture(ofImage texture) {
	imported_texture = texture;
	is_texture_loaded = true;
}

void GeObject::setFilter(Filter *filter) {
	texture_filter = filter;
}
