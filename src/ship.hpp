#define VERT true
#define HORIZ false


class ship{

private:
	int size;
	int num_of_hit_fields;
	bool alive;
	int pos_x, pos_y;
	bool orientation;

	void update_status();
public:
	ship(int size, int pos_x, int pos_y, bool orientation);
	int get_size(void);
	bool get_status(void);
	void draw();
	void draw_at(int x, int y);
};
