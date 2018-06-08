#include "game.hpp"

#include <GL/glut.h>

int main(int argc, char**argv){
	
	glutInit(&argc, argv);
	game::init();
	glutMainLoop();

	return 0;
}
