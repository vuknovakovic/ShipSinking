#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <GL/glut.h>

#include "../includes/phase1.hpp"
#include "../includes/phase2.hpp"
#include "../includes/ship.hpp"
#include "../includes/game.hpp"


namespace phase1{
	//indicator which player is setting ships
	int player_to_set = 1;

	int draw_at_x, draw_at_y;
	int size_to_draw = 1;
	int num_of_drawn_ships=0;

	bool orientation = HORIZ;
	std::string s = "IGRAC 1 POSTAVLJA BRODOVE";

	std::vector<ship> ships;//used for viewing of placed ships

	//ships used for displaying next ship that is going to be placed
	ship tmp1 = ship(1,0,0,orientation);
	ship tmp2 = ship(2,0,0,orientation);
	ship tmp3 = ship(3,0,0,orientation);
	ship tmp4 = ship(4,0,0,orientation);

	void on_keyboard(unsigned char c, int x, int y){
		(void) x;
		(void) y;
		switch(c){
			case 27:
				exit(0);
				break;
			case 'r'://rotate ship
				orientation = !orientation;
				glutPostRedisplay();
				break;
		return;
		}
	}

	void draw_ships(){
		switch(size_to_draw){
			case 1:
				tmp1.draw_at(draw_at_x, draw_at_y, orientation, true);
				break;
			case 2:
				tmp2.draw_at(draw_at_x, draw_at_y, orientation, true);
				break;
			case 3:
				tmp3.draw_at(draw_at_x, draw_at_y, orientation, true);
				break;
			case 4:
				tmp4.draw_at(draw_at_x, draw_at_y, orientation, true);
				break;
		}

		for(auto &ship:ships){
			ship.draw();
		}

	}

	void on_display(){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-11,11,-1,11,0,20);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		game::draw_debug_coords();

		//drawing field
		game::draw_left_field();
		game::draw_right_field();

		glDisable(GL_LIGHTING);

		//draw placed ships
		draw_ships();
		game::display_text(s);


		glEnable(GL_LIGHTING);

		glutSwapBuffers();

	}

	bool can_fit(int x, int y){
		if(orientation == HORIZ){
			if(x > 0 && x + size_to_draw > 11)
				return false;
			// horizontal orientation creates ship to the right of the given position, so on the left field we check for > -1
			else if(x < 0 && x + size_to_draw > 0)
				return false;

			for(int i=0;i<size_to_draw;++i){
				if(std::any_of(ships.begin(), ships.end(),
							[&](ship s){
								return s.has(x+i, y);
							}
							)
					)
					return false;
			}

		}
		else{
			if(y + size_to_draw > 11){
				return false;
			}
			for(int i=0;i<size_to_draw;++i){
				if(std::any_of(ships.begin(), ships.end(),
							[&](ship s){
								return s.has(x, y+i);
							}
							)
					)
					return false;
			}
		}

		return true;
	}

	void passive_motion(int x, int y){
		//screen to world coords
		float x_world = x*((11+11)/(float)width) - 11;
		float y_world = 11 - y*((11+1)/(float)height);

		if(!game::inside_field(x_world, y_world)){
			// std::cout << "Out of bounds!!" << std::endl;
			// set to -100 so that ship would not be displayed
			draw_at_x = draw_at_y = -100;
			return;
		}

		else{
			if(x_world < 0){ //left field
				float x_world_tmp = x_world + 0.5;//because field is moved 0.5 to the left

				draw_at_x = std::floor(x_world_tmp);
				draw_at_y = std::ceil(y_world);

			}
			else { //right_field
				float x_world_tmp = x_world - 0.5;//because field is moved 0.5 to the right

				draw_at_x = std::ceil(x_world_tmp);
				draw_at_y = std::ceil(y_world);

			}
		}

		if(!can_fit(draw_at_x, draw_at_y)){
			draw_at_x = draw_at_y = -100;
		}

		//player1 puts its ships on left field, so he cant have option to put them on right field, similar for player2
		else if(player_to_set == 1 && draw_at_x > 0)
			draw_at_x = draw_at_y = -100;
		else if(player_to_set == 2 && draw_at_x < 0)
			draw_at_x = draw_at_y = -100;
		glutPostRedisplay();
	}

	//mouse function trigerred on CLICK, places ships
	void mouse_function(int button, int state, int x, int y){
		(void)x, (void)y;

		//draw_at_x and draw_at_y are set in passive_motion
		if(draw_at_x == -100 && draw_at_y == -100)
			return;

		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if(player_to_set == 1){
				player1.add_ship(ship(size_to_draw, draw_at_x, draw_at_y, orientation));
				ships.push_back(ship(size_to_draw, draw_at_x, draw_at_y, orientation));

				//since we have to put 4 ships of size 1, 3 ships of size 2, 2 ships of size 3 and 1 ship of size 4,
				//this is valid because num_of_ships starts at 0
				if(num_of_drawn_ships + size_to_draw == 4){
					num_of_drawn_ships = -1;//set to -1 because its incremented at the end of IF statement so it will be 0 next time
					size_to_draw++;

					//size_to_draw == 5 means that this player has done setting its ships
					if(size_to_draw == 5){
						size_to_draw = 1;
						player_to_set = 2;
						s = "IGRAC 2 POSTAVLJA BRODOVE";
						ships.clear();//empty vector of ships to be displayed
					}
				}
			}

			else if(player_to_set == 2){
				player2.add_ship(ship(size_to_draw, draw_at_x, draw_at_y, orientation));
				ships.push_back(ship(size_to_draw, draw_at_x, draw_at_y, orientation));

				if(num_of_drawn_ships + size_to_draw == 4){//TODO check
					num_of_drawn_ships = -1;
					size_to_draw++;

					if(size_to_draw == 5){
						glutKeyboardFunc(phase2::on_keyboard);
						glutDisplayFunc(phase2::on_display);
						glutMouseFunc(phase2::mouse_function);
						glutPassiveMotionFunc(phase2::passive_motion);
						// glutTimerFunc(TIMER_INTERVAL, phase2::on_timer, WATER_ID);
						phase2::message_to_display="PLAYER 1 AIMS";

						// std::cout <<"kraj prve faze"<<std::endl;
						ships.clear();
					}
				}
			}
			num_of_drawn_ships++;

			//reset these so that recheck of coordinates and size is forced in passive motion
			//otherwise things like placing ship on top of last placed ship etc. are possible if mouse is not moved
			draw_at_x = draw_at_y = -100;

		}
			glutPostRedisplay();
	}



}

