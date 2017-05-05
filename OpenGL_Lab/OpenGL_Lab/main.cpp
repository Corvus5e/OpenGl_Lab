
#include "GL\glut.h"

#include <math\my_function.h>
#include <io\console.h>
#include <io\vizualizer.h>

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
using namespace math;

void print_help();

int height = 600;
int width = 600;

MyFunction mf;

int main(int argc, char* argv[]){
	
	print_help();

	io::Console::readArgs(argc, argv);
	io::Vizualizer* v = io::Vizualizer::getInstance();
	v->init(argc, argv, width, height, "OpenGl Application");

	double mu = atof(io::Console::getParam("-mu").c_str());
	double m = atof(io::Console::getParam("-m").c_str());

	double radius_step = atof(io::Console::getParam("-v_step").c_str());
	double angle_step = atof(io::Console::getParam("-u_step").c_str());

	double radius_start = atof(io::Console::getParam("-v_start").c_str());
	double radius_end = atof(io::Console::getParam("-v_end").c_str());
	double angle_start = atof(io::Console::getParam("-u_start").c_str());
	double angle_end = atof(io::Console::getParam("-u_end").c_str());

	mf.mu(mu);
	mf.m(m);
	mf.compute_values(angle_start, angle_end, radius_start, radius_end, angle_step, radius_step);

	v->add_function(&mf);
	v->start();

	return 0;
}

void print_help(){

	 cout << " ==========  Help =========== " << endl << endl;
	 cout << "Controls : " << endl;
	 cout << "\t z -  zoom out" << endl;
	 cout << "\t x -  zoom in" << endl;
	 cout << "\t c -  change mode (gpu/cpu)" << endl;
	 cout << "Mouse to rotate scene" << endl << endl;

	 cout << "Launcher.bat contain parameters or function and drawing." << endl;
}