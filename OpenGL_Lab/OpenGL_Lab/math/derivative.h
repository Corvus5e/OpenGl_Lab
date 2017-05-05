
#ifndef MATH_DERIVATIVE_H
#define MATH_DERIVATIVE_H

#include <math\function.h>
#include <math\vector.hpp>

namespace math {

	class Derivative {

		Function* func_;

	public :

		Derivative(Function* function);
		DerivativeValue value(double angle, double radius);

	};
}


#endif