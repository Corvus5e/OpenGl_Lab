
#include "derivative.h"

using namespace math;

Derivative::Derivative(Function* func){
	this->func_ = func;
};

DerivativeValue Derivative::value(double angle, double radius){

	double delta = 0.001;
	Point p = this->func_->value(angle, radius);
	Point p_u = this->func_->value(angle + delta, radius);
	Point p_v = this->func_->value(angle, radius + delta);

	DerivativeValue d;
	d.d_angle = Vector( (p_u.x - p.x)/delta, (p_u.y - p.y)/delta, (p_u.z - p.z)/delta);
	d.d_radius = Vector((p_v.x - p.x)/delta, (p_v.y - p.y)/delta, (p_v.z - p.z)/delta);

	return d;
}