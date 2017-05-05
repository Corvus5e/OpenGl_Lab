
#ifndef IO_COLOR_H
#define IO_COLOR_H

namespace io {

	struct Color {
		double r;
		double g;
		double b;
		double a;

		Color(double r, double g, double b, double a = 1.0){
			this->r = r;
			this->g = g;
			this->b = b;
		}

		Color operator+(const Color& color){
			return Color(this->r + color.r, this->g + color.g, this->b + color.b, this->a + color.a);
		}

		Color operator*(const Color& color){
			return Color(this->r * color.r, this->g * color.g, this->b * color.b, this->a*color.a);
		}

		Color operator*(double k){
			return Color(this->r * k, this->g * k, this->b * k, this->a * k);
		}

		void normalize(double max){
			this->r /= max;
			this->g /= max;
			this->b /= max;
			this->a /= max;
		}
	};
}


#endif