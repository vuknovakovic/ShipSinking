#include <vector>
#include <tuple>
#include <algorithm>

#include "ship.hpp"
#include "player.hpp"
// #include "display.hpp"

// extern int draw_at_x, draw_at_y;//from display.cpp


bool can_hit(int x, int y, std::vector<std::tuple<int, int>> aimed_cells){
	int tmp_x = 0, tmp_y = 0;
	// XXX Warning: ugly block of code incoming
	
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


bool player::aim_at(int x, int y, player opponent){
	if(!can_hit(x,y,aimed_cells))
		return false;
		
	opponent.aimed_at(x,y);
	return true;

}

void player::aimed_at(int x, int y){

	for(auto ship : ships){
		if(ship.hit(x,y)){
			if(!ship.alive){
				//TODO smisliti kako da obavestim protivnika da je unistio brod
			}
		}
	}
}

