
#include "my_function.h"
#include "derivative.h"

math::MyFunction::MyFunction(){
	this->mu_ = 0.08;
	this->m_ = 5.2;
}

math::MyFunction::MyFunction(double mu, double m) : mu_(mu), m_(m){
}

math::Point math::MyFunction::value(double u, double v){

	Point p(0,0,0);

	p.x = v * sin(theta(u)) * cos(u);
	p.y = v * sin(theta(u)) * sin(u);
	p.z = v * cos(theta(u));

	return p;
}

math::Vector math::MyFunction::normal(double u, double v){

	Derivative der(this);
	DerivativeValue dv = der.value(u, v);

	// cross product
	Vector cp = Vector::cross_product(dv.d_radius, dv.d_angle );	
	cp.normalize();

	return cp;
}

std::vector<std::vector<math::Point>>& math::MyFunction::points(){
	return this->points_;
}

std::vector<std::vector<math::Vector>>& math::MyFunction::normals(){
	return this->normals_;
}

void math::MyFunction::compute_values(double angle_start, double angle_end, double radius_start, double radius_end, double angle_step, double radius_step){

	this->points_.clear();
	this->points_.resize(0);
	this->normals_.clear();
	this->normals_.resize(0);

	int angle_size = (angle_end - angle_start) / angle_step + 1;
	int radius_size = (radius_end - radius_start) / radius_step + 1;

	points_.resize(radius_size);
	normals_.resize(radius_size);
	for(int i = 0; i < points_.size(); i++){
		points_[i].resize(angle_size);
		normals_[i].resize(angle_size);
		for(int j = 0; j < points_[i].size(); j++){			
			points_[i][j] = this->value(j*angle_step + angle_start, i*radius_step + radius_start);
			normals_[i][j] = this->normal(j*angle_step + angle_start, i*radius_step + radius_start);
		}
	}
}

double math::MyFunction::S(double u){
	return ( 1 + this->mu_ * sin(this->m_ * u) );
}

double math::MyFunction::theta(double u){
	return ( PI / 2.0 * this->S(u) );
}

void math::MyFunction::m(double m){
	this->m_ = m;
}

void math::MyFunction::mu(double mu){
	this->mu_ = mu;
}

double math::MyFunction::m(){
	return this->m_;
}

double math::MyFunction::mu(){
	return this->mu_;
}

math::MyFunction::~MyFunction(){

}