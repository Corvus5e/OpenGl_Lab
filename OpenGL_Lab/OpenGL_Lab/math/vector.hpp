

#ifndef IO_VECTOR_H
#define IO_VECTOR_H

#include <math\point.hpp>
#include <math.h>


namespace math {

	struct Vector {

		double x;
		double y;
		double z;	

		Vector(){
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		Vector(double x, double y, double z){
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector(math::Point& start, math::Point& end){
			x = end.x - start.x;
			y = end.y - start.y;
			z = end.z - start.z;
		}
		
		Vector operator+(const Vector& v){
			return Vector(this->x+v.x, this->y+v.y, this->z+v.z);
		}

		static double scalar_product(const Vector& v1, const Vector& v2) {
			return (v1.x * v2.x + 
						v1.y * v2.y + 
							v1.z * v2.z);
		}

		static Vector cross_product(const Vector& v, const Vector& w){
			return Vector(v.y*w.z - w.y*v.z, w.x*v.z - v.x*w.z, v.x*w.y - w.x*v.y);
		}

		double length(){
			return std::sqrt( x*x  + y*y + z*z);
		}

		void normalize(){
			double len = this->length();
			if(len > 0.0){
				this->x /= len;
				this->y /= len;
				this->z /= len;
			}
		}
	};

}


#endif