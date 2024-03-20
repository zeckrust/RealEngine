#include "Skybox.h"

void Skybox::draw() {
	calculate_vertex();
	mesh.setupIndicesAuto();
	calculate_normal();
	calculate_tex_coord(image.getWidth()/4, image.getHeight()/3);
	draw_mesh();
}

void Skybox::set_texture(ofImage _image) {
	image = _image;
}

ofImage Skybox::generate_texture() {
	ofImage imageGenerated;
	ofPixels pixels;
	pixels.allocate(1400, 1050, OF_IMAGE_COLOR_ALPHA);
	int redRatio = ofRandom(1, 255);
	int blueRatio = ofRandom(1, 255);
	int greenRatio = ofRandom(1, 255);

	for (int i = 0; i < 1400 * 1050 * 4; i++) {
		int r = 255 - (i % redRatio);
		int b = 255 - (i % blueRatio);
		int g = 255 - (i % greenRatio);
		if (i % 4 == 0) {
			pixels.setColor(i, ofColor(r, g, b, 255));
		}
	}

	imageGenerated.setFromPixels(pixels);
	pixels.clear();
	return imageGenerated;
}

void Skybox::calculate_vertex() {
	ofPoint v0 = ofPoint(position.x - 1000, position.y - 1000, position.z - 1000);
	ofPoint v1 = ofPoint(position.x - 1000, position.y - 1000, position.z + 1000);
	ofPoint v2 = ofPoint(position.x - 1000, position.y + 1000, position.z + 1000);
	ofPoint v3 = ofPoint(position.x - 1000, position.y + 1000, position.z - 1000);
	ofPoint v4 = ofPoint(position.x + 1000, position.y - 1000, position.z - 1000);
	ofPoint v5 = ofPoint(position.x + 1000, position.y - 1000, position.z + 1000);
	ofPoint v6 = ofPoint(position.x + 1000, position.y + 1000, position.z + 1000);
	ofPoint v7 = ofPoint(position.x + 1000, position.y + 1000, position.z - 1000);

	mesh.addVertex(v0); mesh.addVertex(v3); mesh.addVertex(v2);
	mesh.addVertex(v0); mesh.addVertex(v2); mesh.addVertex(v1);
	mesh.addVertex(v0); mesh.addVertex(v1); mesh.addVertex(v5);
	mesh.addVertex(v0); mesh.addVertex(v5); mesh.addVertex(v4);
	mesh.addVertex(v0); mesh.addVertex(v4); mesh.addVertex(v7);
	mesh.addVertex(v0); mesh.addVertex(v7); mesh.addVertex(v3);

	mesh.addVertex(v6); mesh.addVertex(v7); mesh.addVertex(v3);
	mesh.addVertex(v6); mesh.addVertex(v3); mesh.addVertex(v2);
	mesh.addVertex(v6); mesh.addVertex(v1); mesh.addVertex(v2);
	mesh.addVertex(v6); mesh.addVertex(v1); mesh.addVertex(v5);
	mesh.addVertex(v6); mesh.addVertex(v5); mesh.addVertex(v4);
	mesh.addVertex(v6); mesh.addVertex(v7); mesh.addVertex(v4);
}

void Skybox::calculate_normal() {
	//The number of the vertices
	int nV = mesh.getNumVertices();
	//The number of the triangles
	int nT = mesh.getNumIndices() / 3;
	vector<ofDefaultVertexType> norm(nV); //Array for the normals
	//Scan all the triangles. For each triangle add its
	//normal to norm's vectors of triangle's vertices
	for (int t = 0; t < nT; t++) {
		//Get indices of the triangle t
		int i1 = mesh.getIndex(3 * t);
		int i2 = mesh.getIndex(3 * t + 1);
		int i3 = mesh.getIndex(3 * t + 2);
		//Get vertices of the triangle
		const ofPoint& v1 = mesh.getVertex(i1);
		const ofPoint& v2 = mesh.getVertex(i2);
		const ofPoint& v3 = mesh.getVertex(i3);
		//Compute the triangle's normal
		ofPoint dir = ((v2 - v1).crossed(v3 - v1)).normalized();
		//Accumulate it to norm array for i1, i2, i3
		norm[i1] += dir;
		norm[i2] += dir;
		norm[i3] += dir;
	}
	//Normalize the normal's length
	for (int i = 0; i < nV; i++) {
		norm[i].x /= max(max(norm[i].x, norm[i].y), norm[i].z);
		norm[i].y /= max(max(norm[i].x, norm[i].y), norm[i].z);
		norm[i].z /= max(max(norm[i].x, norm[i].y), norm[i].z);
	}
	//Set the normals to mesh
	mesh.clearNormals();
	mesh.addNormals(norm);
}

void Skybox::calculate_tex_coord(int w, int h) {
	mesh.addTexCoord(ofDefaultTexCoordType(1 * w, 1 * h + 1)); //v0
	mesh.addTexCoord(ofDefaultTexCoordType(1 * w, 2 * h - 1)); //v3
	mesh.addTexCoord(ofDefaultTexCoordType(0 * w, 2 * h - 1)); //v2
	mesh.addTexCoord(ofDefaultTexCoordType(1 * w, 1 * h + 1)); //v0
	mesh.addTexCoord(ofDefaultTexCoordType(0 * w, 2 * h - 1)); //v2
	mesh.addTexCoord(ofDefaultTexCoordType(0 * w, 1 * h + 1)); //v1

	mesh.addTexCoord(ofDefaultTexCoordType(1 * w + 1, 1 * h)); //v0
	mesh.addTexCoord(ofDefaultTexCoordType(1 * w + 1, 0 * h + 1)); //v1
	mesh.addTexCoord(ofDefaultTexCoordType(2 * w - 1, 0 * h + 1)); //v5
	mesh.addTexCoord(ofDefaultTexCoordType(1 * w + 1, 1 * h)); //v0
	mesh.addTexCoord(ofDefaultTexCoordType(2 * w - 1, 0 * h + 1)); //v5
	mesh.addTexCoord(ofDefaultTexCoordType(2 * w - 1, 1 * h)); //v4

	mesh.addTexCoord(ofDefaultTexCoordType(1 * w, 1 * h)); //v0
	mesh.addTexCoord(ofDefaultTexCoordType(2 * w, 1 * h)); //v4
	mesh.addTexCoord(ofDefaultTexCoordType(2 * w, 2 * h)); //v7
	mesh.addTexCoord(ofDefaultTexCoordType(1 * w, 1 * h)); //v0
	mesh.addTexCoord(ofDefaultTexCoordType(2 * w, 2 * h)); //v7
	mesh.addTexCoord(ofDefaultTexCoordType(1 * w, 2 * h)); //v3

	mesh.addTexCoord(ofDefaultTexCoordType(2 * w - 1, 3 * h)); //v6
	mesh.addTexCoord(ofDefaultTexCoordType(2 * w - 1, 2 * h)); //v7
	mesh.addTexCoord(ofDefaultTexCoordType(1 * w + 1, 2 * h)); //v3
	mesh.addTexCoord(ofDefaultTexCoordType(2 * w - 1, 3 * h)); //v6
	mesh.addTexCoord(ofDefaultTexCoordType(1 * w + 1, 2 * h)); //v3
	mesh.addTexCoord(ofDefaultTexCoordType(1 * w + 1, 3 * h)); //v2

	mesh.addTexCoord(ofDefaultTexCoordType(3 * w, 2 * h - 1)); //v6
	mesh.addTexCoord(ofDefaultTexCoordType(4 * w, 1 * h + 1)); //v1
	mesh.addTexCoord(ofDefaultTexCoordType(4 * w, 2 * h - 1)); //v2
	mesh.addTexCoord(ofDefaultTexCoordType(3 * w, 2 * h - 1)); //v6
	mesh.addTexCoord(ofDefaultTexCoordType(4 * w, 1 * h + 1)); //v1
	mesh.addTexCoord(ofDefaultTexCoordType(3 * w, 1 * h + 1)); //v5

	mesh.addTexCoord(ofDefaultTexCoordType(3 * w, 2 * h - 1)); //v6
	mesh.addTexCoord(ofDefaultTexCoordType(3 * w, 1 * h + 1)); //v5
	mesh.addTexCoord(ofDefaultTexCoordType(2 * w, 1 * h + 1)); //v4
	mesh.addTexCoord(ofDefaultTexCoordType(3 * w, 2 * h - 1)); //v6
	mesh.addTexCoord(ofDefaultTexCoordType(2 * w, 2 * h - 1)); //v7
	mesh.addTexCoord(ofDefaultTexCoordType(2 * w, 1 * h + 1)); //v4

}

void Skybox::draw_mesh() {
	ofPushStyle();
	ofSetColor(255, 255, 255);
	image.bind();
	mesh.draw();
	image.unbind();
	ofPopStyle();
}