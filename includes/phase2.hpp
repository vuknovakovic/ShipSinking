#include "game.hpp"

// extern bool anmiation;
extern bool orientation;


namespace phase2{
	void on_keyboard(unsigned char c, int x, int y);
	void mouse_function(int button, int state, int x, int y);
	void passive_motion(int x, int y);
	void on_timer(int val);
	void on_display();
}
