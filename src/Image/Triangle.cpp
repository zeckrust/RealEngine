#include "Triangle.h"
#include <cmath>

Triangle::Triangle(const Point& pt0, const Point& pt1, const Point& pt2) :
	p0{ pt0 }, p1{ pt1 }, p2{ pt2 }, e0{ pt0, pt1 }, e1{ pt1, pt2 }, e2{ pt2, pt0 },
	circle{}
{
	int ax = p1.x - p0.x;
	int ay = p1.y - p0.y;
	int bx = p2.x - p0.x;
	int by = p2.y - p0.y;

	double m = pow(p1.x, 2) - pow(p0.x, 2) + pow(p1.y, 2) - pow(p0.y, 2);
	double u = pow(p2.x, 2) - pow(p0.x, 2) + pow(p2.y, 2) - pow(p0.y, 2);
	double s = 1. / (2. * (ax * by - ay * bx));

	circle.x = ((p2.y - p0.y) * m + (p0.y - p1.y) * u) * s;
	circle.y = ((p0.x - p2.x) * m + (p1.x - p0.x) * u) * s;

	double dx = p0.x - circle.x;
	double dy = p0.y - circle.y;
	circle.radius = pow(dx, 2) + pow(dy, 2);
}

bool Triangle::operator==(const Triangle& other) {
	return	(other.p0 == p0 || other.p1 == p0 || other.p2 == p0) ||
			(other.p0 == p1 || other.p1 == p1 || other.p2 == p1) ||
			(other.p0 == p2 || other.p1 == p2 || other.p2 == p2);
}