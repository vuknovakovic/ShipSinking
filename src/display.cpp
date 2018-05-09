#include <iostream>
#include <cmath>

#include <GL/gl.h>
#include <GL/glut.h>

//callback functions
void on_display();
void on_keyboard(unsigned char c, int x, int y);
void mouse_function(int button, int state, int x, int y);
void on_reshape(int width, int height);

void init(int argc, char** argv);

void draw_field(float z);
void draw_left_field();
void draw_right_field();

void draw_debug_coords();


//global variables
bool animation = true;
int width, height;

//macros
#define pi 3.141592653589793
#define eps 0.0001

// #define DEBUG -1 //macro for debuging,TODO will be deleted at the end



static float r=12;

int main(int argc, char** argv){

    //GLUT init
	init(argc, argv);

    glutMainLoop();

	return 0;
}
void init(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    //creating window
	width=600;
	height=1000;
    glutInitWindowSize(height, width);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    //GLUT callback functions binding
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
	glutMouseFunc(mouse_function);

	//OpenGL init
	glLoadIdentity();
	gluPerspective(60, (float)width/height, 1, 40);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

//helper function 
bool inside_field(float x, float y){
	return 	!(x < -10.5 || x > 10.5 ||y < 0 || y > 10	|| abs(x) < 0.5);
}

//mouse function trigerred on CLICK
void mouse_function(int button, int state, int x, int y){

	//world coords
	float x_world = x*((11+11)/(float)width) - 11;
	float y_world = 11 - y*((11+1)/(float)height);

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(!inside_field(x_world, y_world)){
			std::cout << "Out of bounds!!" << std::endl;
		}
		if(x_world < 0){ //left field
			float x_world_tmp = x_world + 0.5;

			int hit_cell_x = x_world_tmp;
			int hit_cell_y = y_world;
			
			std::cout << hit_cell_x << " " << hit_cell_y << " " <<std::endl;
		}
		else { //right_field
			float x_world_tmp = x_world - 0.5;
			
			int hit_cell_x = x_world_tmp;
			int hit_cell_y = y_world;
			
			std::cout << hit_cell_x << " " << hit_cell_y << " " <<std::endl;
		
		}
		std::cout << x_world << " " << y_world << " " <<std::endl;
	}

}

void on_display(){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

#ifdef DEBUG
	float x =r* cos(theta)*cos(fi);
	float y =r* cos(theta)*sin(fi);
	float z =r* sin(theta);
	gluLookAt(x ,y ,z,
			0,0,0,
			0,1,0);
	glRotatef(90, 0,0,1);

#endif

#ifndef DEBUG
	if(animation){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, (float)width/height, 1, 40);
		gluLookAt(0 ,-7 ,10,
			  0,0,0,
			  0,1,0);
		glMatrixMode(GL_MODELVIEW);
	}
	
	else{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-11,11,-1,11,0,20);
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
#endif

	draw_debug_coords();

	//drawing left field
	draw_left_field();

	//drawing right field
	draw_right_field();


	glutSwapBuffers();
}

void draw_right_field(){
	draw_field(0.5);
}
void draw_left_field(){
	draw_field(-10.5);
}

void draw_field(float x){

	glPushMatrix();
	
		glTranslatef(x,0,0);

		// drawing "water"TODO: add normals to get wave efect
		glColor3f(0,0,1);
		glBegin(GL_POLYGON);
			glVertex3f(0,0,0);
			glVertex3f(10,0,0);
			glVertex3f(10,10,0);
			glVertex3f(0,10,0);
		glEnd();

		// drawing field
		glColor3f(1,1,1);
		glBegin(GL_LINES);
		for(int i=0;i<=10;i++) {
			glVertex3f(i,0,0);
			glVertex3f(i,10,0);
			glVertex3f(0,i,0);
			glVertex3f(10,i,0);
		};
		glEnd();
	glPopMatrix();

}

void draw_debug_coords(){

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
}


void on_keyboard(unsigned char c, int x, int y){
	(void) x;
	(void) y;
	switch(c){
		case 27:
			exit(0);
			break;
		case 't'://TODO delete this, this should be done automatically when needed
			animation = !animation;
			glutPostRedisplay();
		}
	return;
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
