
#ifndef POINT_H
#define POINT_H

#include <cmath>

namespace math {

	struct Point {
		double x;
		double y;
		double z;

		Point() {
			x = 0.0;
			y = 0.0;
			z = 0.0;
		}

		Point(double x, double y, double z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		double static distance(Point& p1, Point p2){
			return sqrt( pow((p2.x - p1.x), 2.0) + pow((p2.y - p1.y), 2.0) + pow((p2.z - p1.z), 2.0));
		}
	};
}

#endif