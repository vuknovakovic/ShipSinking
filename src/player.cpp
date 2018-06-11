#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>

#include <GL/gl.h>
#include <GL/glut.h>

#include "../includes/ship.hpp"
#include "../includes/player.hpp"
#include "../includes/phase2.hpp"


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
	if(!can_hit(x,y,aimed_cells)){
		phase2::message_to_display = "CELL ALLREADY AIMED, AIM AGAIN";
		return true;
	}
	aimed_cells.push_back(std::make_tuple(x,y));
		
	return opponent.aimed_at(x,y);

}

bool player::aimed_at(int x, int y){

	for(auto &ship : ships){
		if(ship.hit(x,y)){
			if(!ship.alive){
				phase2::message_to_display = "SHIP DESTROYED";
				num_of_lost_ships++;

				if(num_of_lost_ships == 10){
					phase2::message_to_display = "GAME OVER";
					phase2::game_over=true;
				}
			}
			return true;
		}
	}
	return false;
}


void player::draw_hit_ships(){
	for(auto &s : ships){
		s.draw_hit_fields();
	}
}
