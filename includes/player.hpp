#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <vector>
#include <tuple>

#include "ship.hpp"

class player{
private:
	std::vector <ship> ships;
	std::vector <std::tuple<int,int>> aimed_cells;
	int num_of_lost_ships = 0;
	
public:
	bool aim_at(int x, int y, player&);
	bool aimed_at(int x, int y);
	void add_ship(const ship& s);
	void draw_aimed_fields();
	void draw_hit_ships();
};
#endif
