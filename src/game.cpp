#include <vector>
#include <GL/gl.h>
#include <cmath>
#include <GL/glut.h>

#include "../includes/game.hpp"
#include "../includes/ship.hpp"
#include "../includes/player.hpp"
#include "../includes/phase1.hpp"

int width = 600, height = 1000;
int water_paramater = 0;
player player1, player2;

namespace game{

	void init(){

		// glutInit(&argc, argv);
    	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    	glEnable(GL_DEPTH_TEST);
    	glEnable(GL_NORMALIZE);

    	//creating window
		width=600;
		height=1000;
    	glutInitWindowSize(height, width);
    	glutInitWindowPosition(100, 100);
    	glutCreateWindow("potapanje_brodica");

    	//GLUT callback functions binding
    	glutKeyboardFunc(phase1::on_keyboard);
    	glutReshapeFunc(on_reshape);
    	glutDisplayFunc(phase1::on_display);
		glutMouseFunc(phase1::mouse_function);
		glutPassiveMotionFunc(phase1::passive_motion);
		glutTimerFunc(TIMER_INTERVAL, phase1::on_timer, WATER_ID);

		//OpenGL init
		glLoadIdentity();
		gluPerspective(60, (float)width/height, 1, 40);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

	}	
	
	bool inside_field(float x, float y){
		return 	!(x < -10.5 || x > 10.5 || y < 0 || y > 10	|| abs(x) < 0.5);
	}

	void draw_right_field(){
		draw_field(0.5);
	}
	void draw_left_field(){
		draw_field(-10.5);
	}
	
	//funtcion for water wave efect
	float function(float u, float v){
	
		return 5*std::sin((- water_paramater + u*u + v*v) / 150);
	}
	
	void set_vertex_and_normal(float u, float v){
	
	    float diff_u, diff_v;
		float x = u, y =v;//tmp values
		//multiplication changes wave efect, this looks nice for now
		u = 4 * u;
		v = 4 * v;
	
		//calculating aprox. diferential of function
	    diff_u = (function(u + 1, v) - function(u - 1, v));
	    diff_v = (function(u, v + 1) - function(u, v - 1));
	
		//set normal
	    glNormal3f(sin(-diff_u), std::sin(-diff_v),1);
	
		// set blue color and set vertex
		glColor3f(0,0,1);
	    glVertex3f(x, y, 0);
	}
	
	void set_light(){
	
		//light properities
		GLfloat light_position[] = { 1, 1, 1, 0 };
		GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
		GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
		GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };
	
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	
	}
	
	void draw_water(){
		glColor3f(0,0,1);
		for (float u = 0; u < 10; u++) {
			glBegin(GL_TRIANGLE_STRIP);
			for (float v = 0; v <= 10; v++) {
				set_vertex_and_normal(u, v);
				set_vertex_and_normal(u + 1, v);
			}
			glEnd();
		}
	}
	
	void draw_field(float x){
	
		glPushMatrix();
	
			glTranslatef(x,0,0);
			
			set_light();
			
			glEnable(GL_COLOR_MATERIAL);
			draw_water();
	
			// drawing field
			glDisable(GL_LIGHTING);
			glColor3f(1,1,1);
			glBegin(GL_LINES);
			for(int i=0;i<=10;i++) {
				glVertex3f(i,0,0);
				glVertex3f(i,10,0);
				glVertex3f(0,i,0);
				glVertex3f(10,i,0);
			}
			glEnd();
			glDisable(GL_COLOR_MATERIAL);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	
	}
	
	void draw_debug_coords(){
	
		glDisable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1,0,0);
		glBegin(GL_LINE_STRIP);
			glVertex3f(0,0,0);
			glVertex3f(100,0,0);
		glEnd();
		glColor3f(0,1,0);
		glBegin(GL_LINE_STRIP);
			glVertex3f(0,0,0);
			glVertex3f(0,100,0);
		glEnd();
		glColor3f(0,0,1);
		glBegin(GL_LINE_STRIP);
			glVertex3f(0,0,0);
			glVertex3f(0,0,100);
		glEnd();
		glDisable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
	}
	

	void on_reshape(int w, int h){
		width=w;
		height=h;
	
	
		glViewport(0,0,width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	
		gluPerspective(60, (float)width/height, 1, 40);
	
		glMatrixMode(GL_MODELVIEW);
	}
}

