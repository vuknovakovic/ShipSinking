#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>

#include <GL/gl.h>
#include <GL/glut.h>

#include "../includes/ship.hpp"
#include "../includes/player.hpp"
#include "../includes/phase2.hpp"
// #include "../includes/display.hpp"

// extern int draw_at_x, draw_at_y;//from display.cpp


bool can_hit(int x, int y, std::vector<std::tuple<int, int>> aimed_cells){
	int tmp_x = 0, tmp_y = 0;
	
	return !(std::any_of(aimed_cells.begin(), aimed_cells.end(),
						[&](std::tuple<int,int> tmp){
							std::tie(tmp_x, tmp_y) = tmp;
							return (tmp_x == x && tmp_y == y);
							}
						)
			);
}


void player::add_ship(const ship& s){
	ships.push_back(s);
}


bool player::aim_at(int x, int y, player &opponent){
	// std::cout << "gadjao sam " << x << " " << y;
	if(!can_hit(x,y,aimed_cells)){
		//TODO notify to aim again
		phase2::message_to_display = "CELL ALLREADY AIMED, AIM AGAIN";
		// std::cout << "\nne mogu da gadjam" << std::endl;
		return true;
	}
	aimed_cells.push_back(std::make_tuple(x,y));
		
	return opponent.aimed_at(x,y);

}

bool player::aimed_at(int x, int y){
	// std::cout << "gadjan sam na "<< x << " " << y;

	// return std::any_of(ships.begin(),ships.end(),
			// [&](ship& s){
				// bool hit = s.hit(x,y);
				// if(hit && !s.alive){
					// TODO notify
				// }
				// return hit;
			// }
			// );


//
	for(auto &ship : ships){
		if(ship.hit(x,y)){
			if(!ship.alive){
				// TODO smisliti kako da obavestim protivnika da je unistio brod
				phase2::message_to_display = "SHIP DESTROYED";
				num_of_lost_ships++;
				if(num_of_lost_ships == 10){
					phase2::message_to_display = "GAME OVER";
				}
				// std:: cout << " i pogodjen sam" << std::endl;
			}
			return true;
		}
	}
	return false;
}

void player::draw_aimed_fields(){
	float x, y;
	for(auto &cell : aimed_cells){
		std::tie(x,y) = cell;
			glBegin(GL_POLYGON);
				glColor3f(1,1,1);
				glVertex3f(x-0.5,y,0);
				glVertex3f(x+0.5,y,0);
				glVertex3f(x-0.5,y-1,0);
				glVertex3f(x+0.5,y-1,0);
			glEnd();
	}

}

void player::draw_hit_ships(){
	for(auto &s : ships){
		s.draw_hit_fields();
	}
}
