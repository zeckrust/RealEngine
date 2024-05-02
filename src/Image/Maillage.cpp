#pragma once

#include "Maillage.h"
#include <cmath>

Maillage::Maillage() {
	current_id = 0;
}

void Maillage::add_point(ofVec3f point, ofColor color) {
	points.push_back(Point(point.x, point.y, current_id, color));
	current_id++;
	if (points.size() > 2) {
		triangulation();
	}
}

void Maillage::draw() {
	if (points.size() > 2) {
		mesh.drawWireframe();
	}
}

Triangle Maillage::createSuperTriangle(void) {
	float xMin = points[0].x;
	float xMax = xMin;
	float yMin = points[0].y;
	float yMax = yMin;

	for (auto const& point : points) {
		xMin = std::min(xMin, point.x);
		xMax = std::max(xMax, point.x);
		yMin = std::min(yMin, point.y);
		yMax = std::min(yMax, point.y);
	}

	float dx = xMax - xMin;
	float dy = yMax - yMin;
	float dMax = std::max(dx, dy);
	float midx = (xMin + xMax) / 2;
	float midy = (yMin + yMax) / 2;

	Point p0 = Point(midx - 20 * dMax, midy - dMax, -1, ofColor(0));
	Point p1 = Point(midx, midy + 20 * dMax, -2, ofColor(0));
	Point p2 = Point(midx + 20 * dMax, midy - dMax, -3, ofColor(0));

	return Triangle(p0, p1, p2);
}

void Maillage::triangulation() {

	std::vector<Triangle> triangles;

	Triangle super_triangle = createSuperTriangle();
	
	triangles.push_back(Triangle(super_triangle.p0, super_triangle.p1, super_triangle.p2));

	for (auto const& pt : points) {
		std::vector<Edge> edges;
		std::vector<Triangle> tmps;
		for (auto const& tri : triangles) {
			float dist = pow(tri.circle.x - pt.x, 2) + pow(tri.circle.y - pt.y, 2);

			if ((dist - tri.circle.radius) <= 1e-4) {
				edges.push_back(tri.e0);
				edges.push_back(tri.e1);
				edges.push_back(tri.e2);
			}
			else {
				tmps.push_back(tri);
			}
		}

		std::vector<bool> remove(edges.size(), false);
		for (auto edge1 = edges.begin(); edge1 != edges.end(); edge1++) {
			for (auto edge2 = edges.begin(); edge2 != edges.end(); edge2++) {
				if (edge1 == edge2) {
					continue;
				}
				if (*edge1 == *edge2) {
					remove[std::distance(edges.begin(), edge1)] = true;
					remove[std::distance(edges.begin(), edge2)] = true;
				}
			}
		}

		int diff = 0;
		for (int i = 0; i < remove.size(); i++) {
			if (remove[i]) {
				edges.erase(edges.begin() + (i - diff));
				diff++;
			}
		}

		for (auto const& edge : edges) {
			tmps.push_back(Triangle(edge.p0, edge.p1, pt));
		}

		triangles = tmps;
	}

	for (int i = 0; i < triangles.size(); i++) {
		if (super_triangle == triangles[i]) {
			triangles.erase(triangles.begin() + i);
		}
	}

	updateMesh(triangles);
	
}

void Maillage::updateMesh(std::vector<Triangle> triangles) {
	mesh.clear();

	for (auto const& point : points) {
		mesh.addVertex(ofPoint(point.x, point.y, 0));
		mesh.addColor(point.color);
	}

	for (auto const& tri : triangles) {
		mesh.addTriangle(tri.p0.id, tri.p1.id, tri.p2.id);
	}
}
