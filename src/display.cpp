#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

void on_display();
void on_keyboard(unsigned char c, int x, int y);
void mouse_function(int button, int state, int x, int y);
void on_reshape(int width, int height);
void init(int argc, char** argv);
int width, height;


#define pi 3.141592653589793
#define eps 0.0001
/** #define DEBUG -1 */

float fi=0;
float theta=0;
float delta_fi=pi/90;
float delta_theta=pi/90;
float left_fi=0;
float right_fi=2*pi;
float left_theta=-pi/2;
float right_theta=pi/2;
float hrs = 0;


void inc_angle(float *angle, float angle_inc, float angle_b);
void dec_angle(float *angle, float angle_dec, float angle_b);

void draw_field(float z);
void draw_left_field();
void draw_right_field();

void draw_cords();


//light
float light_ambient[]={0.3,0.3,0.3,1};
float light_diffuse[]={0.6,0.6,0.6,1};
float light_specular[]={0.9,0.9,0.9,1};
float light_position[]={0,0,0,1};

//material;
float material_ambient[]={0.3,0.3,0.3,1};
float material_diffuse[]={0.6,0.6,0.6,1};
float material_specular[]={0.9,0.9,0.9,1};
float shininess = 20;

static float r=12;

int main(int argc, char** argv){
		
    /* Inicijalizuje se GLUT. */
	init(argc, argv);
    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

	return 0;
}
void init(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    /* Kreira se prozor. */
	width=600;
	height=1000;
    glutInitWindowSize(height, width);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
	glutMouseFunc(mouse_function);

	// glEnable(GL_LIGHTING);

//	* Postavljaju se svojstva prvog svetla
	// glEnable(GL_LIGHT0);

	// glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	// glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	// glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	// glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    /*** Postavljaju se svojstva materijala */ 
    /** glMaterialfv(GL_FRONT, GL_AMBIENT,material_ambient); */
    /** glMaterialfv(GL_FRONT, GL_DIFFUSE,material_diffuse); */
    /** glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular); */
    /** glMaterialf(GL_FRONT, GL_SHININESS, shininess); */

    /* Obavlja se OpenGL inicijalizacija. */
	glLoadIdentity();
	gluPerspective(60, (float)width/height, 1, 40);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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

	printf("%g %g %g\n", x, y, z);
#endif

#ifndef DEBUG// ako je animacija ond ide ovaj pogled
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)width/height, 1, 40);
	gluLookAt(0 ,-7 ,-10,
	  	0,0,0,
	  	0,1,0);
	glMatrixMode(GL_MODELVIEW);
	//inace radi ovo
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// float zoom=width/height;
	// glOrtho(0*zoom, 40*zoom, -10*zoom, 20*zoom,0, 100);//TODO predtsvaiti sve ovo preko width i height
	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
	// glRotatef(90, 1,0,0);
	// glRotatef(270, 0,1,0);
	// glTranslatef(-10*zoom, 0*zoom, -25*zoom);
#endif
			
	
	draw_cords();

	//drawing left field
	draw_left_field();

	//drawing right field
	draw_right_field();
	


	glutSwapBuffers();
}

void draw_left_field(){
	draw_field(0.5);
}
void draw_right_field(){
	draw_field(-10.5);
}

void draw_field(float x){
//
	// drawing "water"TODO: add normals and stuff to get wave efect and whoosh stuff
	glPushMatrix();
//
//
	// material_ambient[0]=0;
	// material_diffuse[0]=0;
	// material_specular[0]=0;
//
	// material_ambient[1]=0;
	// material_diffuse[1]=0;
	// material_specular[1]=0;
//
	// material_ambient[2]=1;
	// material_diffuse[2]=1;
	// material_specular[2]=1;
//
    // glMaterialfv(GL_FRONT, GL_AMBIENT,material_ambient);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE,material_diffuse);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
//
	glTranslatef(x,0,0);
	glColor3f(0,0,1);//water, TODO whoosh stuff
	glBegin(GL_POLYGON);
		glVertex3f(0,0,0);
		glVertex3f(10,0,0);
		glVertex3f(10,10,0);
		glVertex3f(0,10,0);
	glEnd();
//
	// drawing fields
	// glDisable(GL_LIGHT0);//disable lights so that white color would be applied properly
//
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

	// glEnable(GL_LIGHT0);
}

void draw_cords(){
	
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
		case 'a':
			dec_angle(&fi, delta_fi, left_fi);
			glutPostRedisplay();
			break;
		case 'w':
			inc_angle(&theta, delta_theta, right_theta);
			glutPostRedisplay();
			break;
	   	case 'd':
		  inc_angle(&fi, delta_fi, right_fi);
		  glutPostRedisplay();
		  break;
	  
		case 's':
			dec_angle(&theta, delta_theta, left_theta);
			glutPostRedisplay();
			break;
		}
	return;
}
void on_reshape(int w, int h){
	width=w;
	height=h;
	glViewport(0,0,width, height);
	/** glMatrixMode(GL_PROJECTION); */
	/** glLoadIdentity(); */
	/** gluPerspective(60, (float)width/height, 1, 40); */
	
	glMatrixMode(GL_MODELVIEW);
}

void inc_angle(float *angle, float angle_inc, float angle_b){
	float tmp = *angle+angle_inc;
	if(tmp>angle_b)
		return;
	*angle+=angle_inc;
}
void dec_angle(float *angle, float angle_dec, float angle_b){
	float tmp = *angle-angle_dec;
	if(tmp<angle_b)
		return;
	*angle-=angle_dec;
}
void mouse_function(int button, int state, int x, int y){
	(void) button;
	if(state == GLUT_DOWN){
		printf("%d %d\n", x, y);
	}

}
