#ifndef __PHASE1__HPP
#define __PHASE1__HPP
#include "game.hpp"

extern bool animation;
extern bool orientation;


namespace phase1{
	void on_keyboard(unsigned char c, int x, int y);
	void mouse_function(int button, int state, int x, int y);
	void passive_motion(int x, int y);
	void on_timer(int val);
	void on_display();
}
#endif
