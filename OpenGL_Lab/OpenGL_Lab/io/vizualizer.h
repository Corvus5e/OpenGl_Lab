
#ifndef IO_VIZUALIZER_H
#define IO_VIZUALIZER_H

#include <math\function.h>
#include <math\point.hpp>
#include <math\my_function.h>
#include <io\color.hpp>

#include <iostream>

namespace io {

	class Vizualizer {

		static Vizualizer* instance_;

		double fi;
		double theta;
		double scale;

		math::Point lamp;

		double max_scale;

		double lastX;
		double lastY;
		double rotation_speed;

		std::vector<math::Function*> functions;

		float light_position[4];

		bool gpu_light;

		Vizualizer();

		void init_states();

		void cpu_init_states();

		Color compute_color(math::Point vertex, math::Vector normal);

	public :

		static Vizualizer* getInstance();

		void init(int argc, char* argv[], int window_width, int window_height, char* title);

		void add_function(math::MyFunction* my_func);

		void start();

		void draw();

		void reshape(int width, int heigth);

		void mouse(int button, int state, int x, int y);

		void motion(int x, int y);

		void key(unsigned char key, int x, int y);

	};

}

#endif