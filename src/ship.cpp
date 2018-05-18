#include <iostream>
#include <algorithm>
#include <vector>

#include <GL/gl.h>
#include <GL/glut.h>

#include "ship.hpp"

extern bool orientation;

ship::ship(int size, float pos_x, float pos_y, bool orientation):
	size{size}, num_of_hit_fields{0}, alive{true}, pos_x{pos_x}, pos_y{pos_y}, orientation{orientation}
{}

int ship::get_size(void){
	return this->size;
}
bool ship::get_status(void){
	return this->alive;
}
void ship::update_status(){
	if(num_of_hit_fields == size){
		alive=false;
	}
}

//TODO dodati  ovicavanje
void ship::draw(){
	float scale_x, scale_y;
	float trans_x, trans_y;

	if(this->orientation == HORIZ){
		scale_x = this->size;
		trans_y = this->pos_y- 0.5;
		scale_y = 1;
		trans_x = this->pos_x - 0.5*(1-this->size%2);//size%2 iz used so that ship would fit the field nicely, otherwise its half left half right
	}
	else{
		scale_y = this->size;
		trans_x = this->pos_x;
		scale_x = 1;
		trans_y = this->pos_y- 0.5*(this->size%2);//same as above 
	}

	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(trans_x, trans_y, 0.25);
		glScalef(scale_x, scale_y, 0.5);
		glutSolidCube(1);
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
}

void ship::draw_at(int x, int y){//used for drawing ship at specific coords, for placing
	float scale_x, scale_y;
	float trans_x, trans_y;

	if(::orientation == HORIZ){
		scale_x = this->size;
		trans_y = y- 0.5;
		scale_y = 1;
		trans_x = x - 0.5*(1-this->size%2);
	}
	else{
		scale_y = this->size;
		trans_x = x;
		scale_x = 1;
		trans_y = y- 0.5*(this->size%2);
	}
	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();
		glColor3f(0,1,0);
		glTranslatef(trans_x, trans_y, 0.25);
		glScalef(scale_x, scale_y, 0.5);
		glutSolidCube(1);
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
}
