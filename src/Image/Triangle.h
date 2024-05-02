#pragma once

#include "ofMain.h"

struct Point {
	float x, y;
	size_t id;
	ofColor color;
	Point(size_t p_id) : x{ 0 }, y{ 0 }, id{ p_id } {}
	Point(float p_x, float p_y, size_t p_id, ofColor p_color) : x{ p_x }, y{ p_y }, id{ p_id }, color{ p_color } {}

	bool operator==(const Point& other) const { return (other.x == x && other.y == y); }
	bool operator!=(const Point& other) const { return !operator==(other); }
};

struct Edge {
	Point p0, p1;
	Edge(Point const& pt0, Point const& pt1) : p0{ pt0 }, p1{ pt1 } {}

	bool operator==(const Edge& other) const { return (other.p0 == p0 && other.p1 == p1) || (other.p0 == p1 && other.p1 == p0); }
};

struct Circle {
	int x, y;
	double radius;
	Circle() = default;
};

class Triangle {
	public:
		Triangle(const Point& pt0, const Point& pt1, const Point& pt2);
		bool in_triangle(glm::vec3 pt);
		bool operator==(const Triangle& other);

		Point p0, p1, p2;
		Edge e0, e1, e2;
		Circle circle;
};