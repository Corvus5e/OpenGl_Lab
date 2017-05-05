
#ifndef MATH_FUNCTION_H
#define MATH_FUNCTION_H

#include <math\point.hpp>
#include <math\vector.hpp>

#include <vector>

namespace math {

	typedef struct {

		Vector d_angle;
		Vector d_radius;		

	} DerivativeValue;

	class Function {

	protected:
		
		std::vector<std::vector<math::Point>> points_;
		std::vector<std::vector<math::Vector>> normals_;

	public:

		virtual Point value(double angle, double radius) = 0;

		virtual Vector normal(double angle, double radius) = 0;

		virtual void compute_values(double angle_start, double angle_end, double radius_start, double radius_end, double angle_step, double radius_step) = 0;

		virtual std::vector<std::vector<math::Point>>& points() = 0;

		virtual std::vector<std::vector<math::Vector>>& normals() = 0;

	};

}

#endif