#include "BezierPlane.h"
#include <cmath>

BezierPlane::BezierPlane(ofVec3f p1, ofVec3f p2, ofVec3f p3, ofVec3f p4, int s_width, ofColor s_color, ofColor f_color) : SceneObject() {
	
	resolution = 30;
	stroke_width = s_width;
	stroke_color = s_color;
	fill_color = f_color;

	ctrl_pts.push_back(p1);
	ctrl_pts.push_back(p2);
	ctrl_pts.push_back(p3);
	ctrl_pts.push_back(p4);

	for (int i = 0; i < 4; i++) {
		input.push_back(std::vector<ofVec3f>());
		for (int j = 0; j < 4; j++) {
			input[i].push_back(ofVec3f());
		}
	}

	generate_ctrl_pts();
	setup_mesh();

}

double factorial(double n) {
	if (n == 0 || n == 1) {
		return 1;
	}
	return n * factorial(n - 1);
}

double combination(double n, double i) {
	return factorial(n) / (factorial(i) * factorial(n - i));
}

double bernstein(double n, double i, double u) {
	return combination(n, i) * pow(u, i) * pow(1 - u, n - i);
}

ofVec3f BezierPlane::curve_pts_position(double u, double v) {

	ofVec3f sum = ofVec3f(0, 0, 0);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			sum += (bernstein(4, i, u) * bernstein(4, j, v) * input[i][j]);
		}
	}
	return sum;
}

void BezierPlane::generate_ctrl_pts() {
	int index = 0;
	for (int i = 0; i < 4; i++) {
		input.at(i).at(i).set(ctrl_pts.at(i));
		for (int j = 1; j < (i+1); j++) {
			input.at(i).at(i-j).set(ofVec3f(input[i-1][i-j].x, input[i][i-j+1].y, (input[i - 1][i - j].z + input[i][i - j + 1].z) / 2));
			input.at(i-j).at(i).set(ofVec3f(input[i-j+1][i].x, input[i-j][i-1].y, (input[i - j + 1][i].z + input[i - j][i - 1].z)/2));
		}
	}


}

void BezierPlane::setup_mesh(void) {
	//mesh = ofMesh::plane(width, height, resolution, resolution, OF_PRIMITIVE_TRIANGLES);
	for (double u = 0; u < resolution; u++) {
		for (double v = 0; v < resolution; v++) {
			mesh.addVertex(curve_pts_position(double(u/resolution), double(v/resolution)));
			mesh.addColor(fill_color);
			wire_mesh.addVertex(curve_pts_position(double(u / resolution), double(v / resolution)));
			wire_mesh.addColor(stroke_color);
		}
	}

	for (int i = 0; i < resolution-1; i++) {
		for (int j = 0; j < resolution-1; j++) {
			mesh.addTriangle((i * resolution) + j, (i * resolution) + j + 1, ((i + 1) * resolution) + j);
			mesh.addTriangle((i * resolution) + j + 1, ((i + 1) * resolution) + j, ((i + 1) * resolution) + j + 1);
			wire_mesh.addTriangle((i * resolution) + j, (i * resolution) + j + 1, ((i + 1) * resolution) + j);
			wire_mesh.addTriangle((i * resolution) + j + 1, ((i + 1) * resolution) + j, ((i + 1) * resolution) + j + 1);
		}
	}
}

void BezierPlane::draw(void) {
	mesh.draw();
	wire_mesh.drawWireframe();

	if (selected) {
		ofSetColor(255, 0, 0);
		ofSpherePrimitive sphere;
		sphere.set(8.0f, 100);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				sphere.setPosition(input[i][j]);
				sphere.draw();
			}
		}
	}
}

