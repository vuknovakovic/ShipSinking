#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

#include <GL/gl.h>
#include <GL/glut.h>

#include "../includes/ship.hpp"

extern bool orientation;


ship::ship(int size, int pos_x, int pos_y, bool orientation):
	size{size}, num_of_hit_fields{0}, pos_x{pos_x}, pos_y{pos_y}, orientation{orientation}, alive{true}
{
	create_ship_fields();
}

void ship::create_ship_fields(){
	if(orientation == HORIZ){
		for(int i=0;i<size;++i)
			this->fields.push_back(std::make_tuple(pos_x+i, pos_y));
	}
	else{
		for(int i=0;i<size;++i)
			this->fields.push_back(std::make_tuple(pos_x, pos_y+i));
	}
	

}
bool ship::has(int x,int y){
	int tmp_x, tmp_y;
	return std::any_of(fields.begin(), fields.end(),
			[&](std::tuple<int,int> tmp){
				std::tie(tmp_x, tmp_y) = tmp;
				return tmp_x == x && tmp_y == y;
			});
}

int ship::get_size(void){
	return this->size;
}
void ship::update_status(){
	if(num_of_hit_fields == size){
		alive=false;
	}
}

void ship::draw(){

	glColor3f(1,0,0);
	this->draw_at(this->pos_x, this->pos_y,this->orientation,false);
	//drawing hit fields
	for(auto cell : hit_fields){
		float x, y;
		std::tie(x,y) = cell;
		y-=0.5;
		glPushMatrix();
			glColor3f(1,1,0);
			glTranslatef(x,y,0.35);
			glutSolidSphere(0.7,20,20);
		glPopMatrix();
	}

}

void ship::draw_at(	int x, int y,
					bool orientation,
					bool set_color){	

	float scale_x, scale_y;
	float trans_x, trans_y;

	if(orientation == HORIZ){
		scale_x = this->size;
		trans_x = x + 0.5*(1-this->size%2) + 1*(this->size>2);
		//NOTE
		//+0.5*(1-this->size) + 1*(size>2) because of the way OpenGL draws cube.
		//Since it draws it symetrical to given point, this part is necessary so that cube would fit nicely in cell, 
		//otherwise it is shifted for 0.5 on x axis, or, if size > 2, shifted for one cell

		scale_y = 1;
		trans_y = y - 0.5;
	}
	else{
		scale_x = 1;
		trans_x = x;
			
		scale_y = this->size;
		trans_y = y - 0.5*(this->size%2) + 1*(this->size>2);
		//same NOTE as above, just for y axis
	}
	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();
		if(set_color){
			glColor3f(0,1,0);
		}
		glTranslatef(trans_x, trans_y, 0.25);//.25 on z so ship would not fall trough field
		glScalef(scale_x, scale_y, 0.5);//.5 on z so it would be lower
		glutSolidCube(1);
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
}

bool ship::hit(int x, int y){

	for(auto it = this->fields.begin(); it != this->fields.end(); ){
		auto cell = *it;

		int tmp_x, tmp_y;
		std::tie(tmp_x, tmp_y) = cell;

		if(x == tmp_x && y == tmp_y){
			hit_fields.push_back(cell);
			it = fields.erase(it);

			num_of_hit_fields++;

			update_status();

			return true;
		}
		else ++it;
	}
	return false;
}


void ship::draw_hit_fields(){

	//drawing hit fields
	
	if(!alive){
		glColor3f(1,0,0);
		draw_at(pos_x, pos_y, orientation, false);
		return;
	}
	
	for(auto cell : hit_fields){
		float x, y;
		std::tie(x,y) = cell;
		y-=0.5;
		glDisable(GL_LIGHTING);
		glPushMatrix();
			glColor3f(1,1,0);
			glTranslatef(x,y,0.35);
			glutSolidSphere(0.7,20,20);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}

}
