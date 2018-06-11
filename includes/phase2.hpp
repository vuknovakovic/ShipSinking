#ifndef __PHASE2__HPP
#define __PHASE2__HPP

#include "game.hpp"

// extern bool anmiation;
extern bool orientation;

namespace phase2{
	extern std::string message_to_display;
	extern std::vector<std::tuple<int,int>> aimed_cells;
	// extern int aimed_at_x, aimed_at_y;
	extern bool game_over;


	void on_keyboard(unsigned char c, int x, int y);
	void mouse_function(int button, int state, int x, int y);
	void passive_motion(int x, int y);
	void on_display();
}
#endif
