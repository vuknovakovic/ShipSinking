#include <vector>
#include <tuple>

#include "ship.hpp"
#include "player.hpp"


bool can_hit(int x, int y, std::vector<std::tuple<int, int>> aimed_cells){
	for(auto cell : aimed_cells){
		int tmp_x, tmp_y;
		std::tie(tmp_x, tmp_y) = cell;
		if(tmp_x == x && tmp_y == y){
			return false;	
		}
	}

	return true;
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

