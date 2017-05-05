
#ifndef MY_FUNCTION_H
#define MY_FUNCTION_H

#include <math\function.h>
#include <math\vector.hpp>
#include <vector>

#define PI 3.14159265358979323846

namespace math {

	// Сотовая коническая поверхность. Англ. перевод - ???
	// Аналитические поверхности - Кривошапко - 2006 - стр. 354

	class MyFunction : public Function {
	
	private:
		double mu_;
		double m_;

		double theta(double u);
		double S(double u);
	
	public :
		
		MyFunction();

		MyFunction(double mu, double m);

		Point value(double angle, double radius);

		Vector normal(double angle, double radius);

		void compute_values(double angle_start, double angle_end, double radius_start, double radius_end, double angle_step, double radius_step);

		std::vector<std::vector<math::Point>>& points();

		std::vector<std::vector<math::Vector>>& normals();

		double mu();

		double m();

		void mu(double mu);

		void m(double m);
	
		virtual ~MyFunction();
	};

}
#endif