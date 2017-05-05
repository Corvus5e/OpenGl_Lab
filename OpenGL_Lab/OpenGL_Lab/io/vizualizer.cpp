
#include <io\vizualizer.h>
#include <GL\glut.h>

io::Vizualizer* global_vizualizer;

void global_draw(){

	io::Vizualizer::getInstance()->draw();
}

void global_reshape(GLsizei width, GLsizei height){

	io::Vizualizer::getInstance()->reshape(width, height);
}

void global_mouse(int button, int state, int x, int y){

	io::Vizualizer::getInstance()->mouse(button, state, x, y);
}

void global_motion(int x, int y){
	io::Vizualizer::getInstance()->motion(x, y);
}

void global_key(unsigned char key, int x, int y){
	io::Vizualizer::getInstance()->key(key, x, y);
}


/* 
 * Vizualizer 
*/

io::Vizualizer* io::Vizualizer::instance_ = 0;

io::Vizualizer::Vizualizer(){
	this->fi = 1.0;
	this->theta = 1.0;
	this->scale = 60.0;
	this->max_scale = 1000;
	this->lastX = 0.0;
	this->lastY = 0.0;
	this->rotation_speed = 0.0002;
	this->gpu_light = true; // 1 - OpenGL light ; 0 - cpu

	this->lamp.x = 0.0;
	this->lamp.y = 10.0;
	this->lamp.z = 4.0;
}

io::Vizualizer* io::Vizualizer::getInstance(){	

	if(!Vizualizer::instance_){
		Vizualizer::instance_ = new Vizualizer();
	}
	return Vizualizer::instance_;
}

void io::Vizualizer::init(int argc, char* argv[], int window_width, int window_height, char* title){

	glutInit(&argc, argv);
	glutInitWindowSize(window_width, window_height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(title);

	glutDisplayFunc(global_draw);
	glutReshapeFunc(global_reshape);
	glutMouseFunc(global_mouse);
	glutMotionFunc(global_motion);
	glutKeyboardFunc(global_key);
}

void io::Vizualizer::add_function(math::MyFunction* my_func){
	this->functions.push_back(my_func);
}

void io::Vizualizer::init_states(){

	glClearColor (0.0, 0.0, 0.0, 0.0);
						      // R    G    B    A
	GLfloat light_ambient[] = { 1.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse[] = { 0.0, 1.0, 0.0, 1.0};
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	
							   // x   y    z   mode  (0.0 - directional mode, 1.0 positional mode)
	GLfloat light_position[] = {this->lamp.x, this->lamp.y, this->lamp.z, 1.0};

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };


	//glShadeModel (GL_SMOOTH);

	// infinite viewpoint
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);	

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	//glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
}

void io::Vizualizer::start(){
	this->init_states();
	glutMainLoop();
}

void io::Vizualizer::draw(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	GLdouble eyeX = scale * sin(theta) * cos(fi);
	GLdouble eyeY = scale * sin(theta) * sin(fi);
	GLdouble eyeZ = scale * cos(theta);

	if(sin(theta) > 0)
		gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, 0, 1);
	else 
		gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, 0, -1);

							  // x   y    z   mode  (0.0 - directional mode, 1.0 positional mode)
	GLfloat light_position[] = {this->lamp.x, this->lamp.y, this->lamp.z, 1.0};
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);

	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLES);

	for(int i = 0; i < functions.size(); i++){

		std::vector<std::vector<math::Point>>& points = functions[i]->points();
		std::vector<std::vector<math::Vector>>& normals = functions[i]->normals();

		for(int v = 0; v < points.size() - 1; v++){
			for(int u = 0; u < points[v].size() - 1; u++){
				
				if(this->gpu_light){
					// 0
					glNormal3d(normals[v][u].x, normals[v][u].y, normals[v][u].z);
					glVertex3d(points[v][u].x, points[v][u].y, points[v][u].z);
					// 1
					glNormal3d(normals[v][u + 1].x, normals[v][u + 1].y, normals[v][u + 1].z);
					glVertex3d(points[v][u + 1].x, points[v][u + 1].y, points[v][u + 1].z);
					// 2
					glNormal3d(normals[v + 1][u].x, normals[v + 1][u].y, normals[v + 1][u].z);
					glVertex3d(points[v + 1][u].x, points[v + 1][u].y, points[v + 1][u].z);

					// 1					
					glNormal3d(normals[v][u + 1].x, normals[v][u + 1].y, normals[v][u + 1].z);
					glVertex3d(points[v][u + 1].x, points[v][u + 1].y, points[v][u + 1].z);
					// 2
					glNormal3d(normals[v + 1][u].x, normals[v + 1][u].y, normals[v + 1][u].z);
					glVertex3d(points[v + 1][u].x, points[v + 1][u].y, points[v + 1][u].z);
					// 3
					glNormal3d(normals[v + 1][u + 1].x, normals[v + 1][u + 1].y, normals[v + 1][u + 1].z);
					glVertex3d(points[v + 1][u + 1].x, points[v + 1][u + 1].y, points[v + 1][u + 1].z);
				}

				else {

					Color c_0 = this->compute_color(points[v][u], normals[v][u]);
					Color c_1 = this->compute_color(points[v][u+1], normals[v][u+1]);
					Color c_2 = this->compute_color(points[v+1][u], normals[v+1][u]);
					Color c_3 = this->compute_color(points[v+1][u+1], normals[v+1][u+1]);

					// 0
					glColor3d(c_0.r, c_0.g, c_0.b);
					glVertex3d(points[v][u].x, points[v][u].y, points[v][u].z);
					// 1
					glColor3d(c_1.r, c_1.g, c_1.b);
					glVertex3d(points[v][u + 1].x, points[v][u + 1].y, points[v][u + 1].z);
					// 2
					glColor3d(c_2.r, c_2.g, c_2.b);
					glVertex3d(points[v + 1][u].x, points[v + 1][u].y, points[v + 1][u].z);

					// 1					
					glColor3d(c_1.r, c_1.g, c_1.b);
					glVertex3d(points[v][u + 1].x, points[v][u + 1].y, points[v][u + 1].z);
					// 2
					glColor3d(c_2.r, c_2.g, c_2.b);
					glVertex3d(points[v + 1][u].x, points[v + 1][u].y, points[v + 1][u].z);
					// 3
					glColor3d(c_3.r, c_3.g, c_3.b);
					glVertex3d(points[v + 1][u + 1].x, points[v + 1][u + 1].y, points[v + 1][u + 1].z);
				}
			}
		}
	}

	glEnd();


	#pragma region Axes

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);	
	glVertex3d(10, 0, 0);	
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);	
	glVertex3d(0, 10, 0);	
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);	
	glVertex3d(0, 0, 10);	
	glEnd();

	#pragma endregion

	glutSwapBuffers();
}

void io::Vizualizer::reshape(int width, int height){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();			
	glViewport(0, 0, width, height);
	gluPerspective(45.0f, width/height, 0.1f, max_scale);		
	glMatrixMode(GL_MODELVIEW);	
}

void io::Vizualizer::mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON :
			if(state == GLUT_DOWN){
				lastX = x;
				lastY = y;				
			}
		break;
	}
}

void io::Vizualizer::motion(int x, int y){

	fi -= rotation_speed*(x - lastX)*scale;
	theta -= rotation_speed*(y - lastY)*scale;

	lastX = x;
	lastY = y;

	global_draw(); // instead render loop
}

void io::Vizualizer::key(unsigned char key, int x, int y){

	double step = scale / 10;
	if( (key == 'z') && (scale + step < max_scale) ){
		scale += step;
	}
	if( (key == 'x') && (scale - step > 0.1) )
		scale -= step;

	if(key == 'c') {
		if(this->gpu_light){
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT1);
			this->gpu_light = false;
		}
		else{
			this->gpu_light = true;
			init_states();
		}		
	}
	global_draw();
}

io::Color io::Vizualizer::compute_color(math::Point vertex, math::Vector normal){

	io::Color c(0, 0, 0);


	io::Color light_ambient(1.0, 0.0, 0.0, 1.0);
	io::Color light_diffuse( 0.0, 1.0, 0.0, 1.0);
	io::Color light_specular( 1.0, 1.0, 1.0, 1.0 );	

	io::Color material_ambient(1.0, 1.0, 1.0, 1.0);
	io::Color material_diffuse(1.0,1.0,1.0,1.0);
	io::Color material_specular(1.0,1.0,1.0,1.0);


	GLdouble eyeX = scale * sin(theta) * cos(fi);
	GLdouble eyeY = scale * sin(theta) * sin(fi);
	GLdouble eyeZ = scale * cos(theta);

	math::Point light_position = this->lamp; 	
	double mat_shininess = 10.0;

	math::Vector l(vertex, light_position);	
	math::Vector s = l + math::Vector(0,0,1);
	//math::Vector s = l + math::Vector(eyeX, eyeY, eyeZ);
	s.normalize();

	double sp_ln = math::Vector::scalar_product(l, normal);
	
	io::Color spec_summand(0,0,0);

	if(sp_ln != 0.0)
		spec_summand = light_specular*material_specular*std::max(math::Vector::scalar_product(s, normal), 0.0) * mat_shininess;

	c = c + light_ambient*material_ambient + light_diffuse * material_diffuse * std::max(0.0, sp_ln)  + spec_summand;

	c.normalize(1 + std::max(0.0, sp_ln) +  mat_shininess );

	return c;
}