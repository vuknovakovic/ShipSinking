#ifndef __SHIP_HPP__
#define __SHIP_HPP__

#define VERT true
#define HORIZ false
#include <vector>
#include <tuple>

extern bool orientation;

class ship{

private:
	int size;
	std::vector<std::tuple<int, int>> fields;

	int num_of_hit_fields;
	std::vector<std::tuple<int, int>> hit_fields;

	int pos_x, pos_y;

	bool orientation;

	void create_ship_fields();

public:
	bool alive;

	ship(int size, int pos_x, int pos_y, bool orientation);
	int get_size(void);
	void update_status();
	void draw();
	bool has(int,int);
	void draw_at(int x, int y, bool orientation = ::orientation, bool set_color = true);
	void draw_hit_fields();
	bool hit(int, int);
};

#endif
