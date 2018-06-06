#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <vector>
#include <tuple>

#include "ship.hpp"

class player{
private:
	std::vector <ship> ships;
	std::vector <std::tuple<int,int>> aimed_cells;
	
public:
	bool aim_at(int x, int y, player);
	void aimed_at(int x, int y);
};
#endif
