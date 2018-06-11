#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>

#include "../includes/game.hpp"
#include "../includes/phase2.hpp"


int hit_at_x, hit_at_y;
int aimed_at_x, aimed_at_y;
int aimed_from;

extern player player1, player2;
int player_on_move = 1;
bool animation;
extern double animation_param;

std::vector<std::tuple<int,int>> aimed_cells;


namespace phase2{
	std::string message_to_display = "";

	void on_keyboard(unsigned char c, int x, int y){
		(void)x, (void)y;
		switch(c){
			case 27:
				exit(0);
		}

	}

	void mouse_function(int button, int state, int x, int y){
		(void)x, (void)y;
		bool hit = false;
		//hit_at_x and hit_at_y are set in passive_motion
		if(hit_at_x == -100 && hit_at_y == -100)
			return;

		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if(player_on_move == 1){
				if(hit_at_x < 0)
					return;

				hit = player1.aim_at(hit_at_x, hit_at_y, player2);
				if(!hit){
					player_on_move = 2;
					phase2::message_to_display = "PLAYER 2 AIMS";
				}

				//phase2:message_to_display is updated in player.aim_at method, so using that to check wheter the cell has been aimed
				//is faster than iterating through vector
				if(phase2::message_to_display == "CELL ALLREADY AIMED, AIM AGAIN") 
					return;

				animation = !animation;

				glutTimerFunc(TIMER_INTERVAL, game::on_timer, ANIMATION_ID);
				phase2::message_to_display = "PLAYER 1 AIMS";
				
				aimed_at_x = hit_at_x;
				aimed_at_y = hit_at_y;
				
				aimed_from = -11;

				if(!animation)
					aimed_cells.push_back(std::make_tuple(hit_at_x,hit_at_y));


			}

			else if(player_on_move == 2){
				if(hit_at_x > 0)
					return;
				hit = player2.aim_at(hit_at_x, hit_at_y, player1);

				if(!hit){
					player_on_move = 1;
					phase2::message_to_display = "PLAYER 1 AIMS";
				}

				if(phase2::message_to_display == "CELL ALLREADY AIMED, AIM AGAIN") 
					return;

				animation = !animation;
				glutTimerFunc(TIMER_INTERVAL, game::on_timer, ANIMATION_ID);
				phase2::message_to_display = "PLAYER 2 AIMS";

				aimed_at_x = hit_at_x;
				aimed_at_y = hit_at_y;


				aimed_from = 11;
				if(animation_param == 0)
					aimed_cells.push_back(std::make_tuple(hit_at_x,hit_at_y));
			}


		}
			glutPostRedisplay();
	}
	void passive_motion(int x, int y){
		//screen to world coords
		float x_world = x*((11+11)/(float)width) - 11;
		float y_world = 11 - y*((11+1)/(float)height);

		if(!game::inside_field(x_world, y_world)){
			// std::cout << "Out of bounds!!" << std::endl;
			// set to -100 so that ship would not be displayed
			hit_at_x = hit_at_y = -100;
			return;
		}

		else{
			if(x_world < 0){ //left field
				float x_world_tmp = x_world + 0.5;//because field is moved 0.5 to the left

				hit_at_x = std::floor(x_world_tmp);
				hit_at_y = std::ceil(y_world);

			}
			else { //right_field
				float x_world_tmp = x_world - 0.5;//because field is moved 0.5 to the right

				hit_at_x = std::ceil(x_world_tmp);
				hit_at_y = std::ceil(y_world);

			}
		}

		glutPostRedisplay();
	}

	void draw_bullet(std::tuple<int, int> from, std::tuple<int,int> to){
		int x_from, y_from;
		int x_to, y_to;

		std::tie(x_from, y_from) = from;
		std::tie(x_to, y_to) = to;
		float diff_x = x_to - x_from;
		float diff_y = y_to - y_from;

		glPushMatrix();

			GLfloat material_ambient[] = { 0, 0.5, 0.5, 1 };
			GLfloat material_diffuse[] = { 0, 0.3, 0.3, 1 };
			GLfloat material_specular[] = { 1, 1, 1, 1 };
			GLfloat shine = 10;

			glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
			glMaterialf(GL_FRONT, GL_SHININESS, shine);

			glTranslatef(x_from + animation_param*diff_x,
					y_from + animation_param*diff_y,
					2 - 2*animation_param);

			glutSolidSphere(0.2,10,10);
		glPopMatrix();

	}
	void draw_aimed_cells(){
		float x,y;
		for(auto &cell : aimed_cells){
			std::tie(x,y) = cell;
				glPushMatrix();
					glTranslatef(x,y-0.5,0.05);
					glScalef(1,1,0.1);
					glutSolidCube(1);
				glPopMatrix();
		}

	}
	void on_display(){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

	#ifdef DEBUG
		float x =r* sin(theta)*sin(fi);
		float y =r* cos(theta);
		float z =r* sin(theta)*cos(fi);
		gluLookAt(x ,y ,z,
				0,0,0,
				0,1,0);

	#endif

	#ifndef DEBUG
		if(animation){
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(60, (float)width/height, 1, 40);
			gluLookAt(	0 ,-7 ,10,
						0,0,0,
						0,1,0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

		else{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-11,11,-1,11,0,20);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
	#endif

		game::draw_debug_coords();

		//drawing field
		game::draw_left_field();
		game::draw_right_field();

		draw_aimed_cells();
		game::display_text(phase2::message_to_display);

		// glDisable(GL_LIGHTING);

		player1.draw_hit_ships();
		player2.draw_hit_ships();

		draw_bullet(std::make_tuple(aimed_from,0), std::make_tuple(aimed_at_x, aimed_at_y));


		glEnable(GL_LIGHTING);

		glutSwapBuffers();

		}
}

