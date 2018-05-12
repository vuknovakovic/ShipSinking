//callback functions
void on_display();
void on_keyboard(unsigned char c, int x, int y);
void mouse_function(int button, int state, int x, int y);
void passive_motion(int x, int y);
void on_reshape(int width, int height);

void init(int argc, char** argv);

void draw_field(float z);
void draw_left_field();
void draw_right_field();

void draw_debug_coords();


//macros
#define pi 3.141592653589793
#define eps 0.0001

// #define DEBUG -1 //macro for debuging,TODO will be deleted at the end
