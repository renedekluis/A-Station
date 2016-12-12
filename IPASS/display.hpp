//          Copyright René de Kluis 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file read_me.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "hwlib.hpp"
#include "circle.hpp"
#include "rectangle.hpp"


 /// this class is used to print items on the screen.
 /// i've chosen to make this a different class then the levels class,
 /// because the levels class would become really big otherways.


class display{
private:
	int start_x  = 70;
	int start_y = 12;
	int move_x = 0;
	int move_y = 0;
	int save_x = 0;
	int save_y = 0;
	int computer_move_x = 0;
	int computer_move_y = 0;
	int computer_save_x = 0;
	int computer_save_y = 0;
	bool need_clear = false;
	hwlib::window & w;
	byte direction;
	hwlib::location start = {0,0};
	hwlib::location end = {128,10};
	
	
public:

	
	/// the functions here are roughly the same as in the levels class, 
	/// but with a bit more information to draw it correctly on the display.
	/// I will explain the most in the .cpp file.

	display(hwlib::window & w);
	
	int rand();
	unsigned int random_in_range( unsigned int min, unsigned int max );
	void clear(hwlib::window & w );
	void graphics_random_circles( hwlib::window & w );
	void create_ground(hwlib::window & w);
	void create_object(hwlib::window & w, hwlib::location start_coordinate,hwlib::location end_coordinate);
	void set_move(int h, int i, int j, int k);
	void clear_dodge(hwlib::window & w);
	void set_dodge(hwlib::window & w);
	void move_player(hwlib::window & w, int player_radius);
	void start_player(hwlib::window & w);
	void move_npc(hwlib::window & w);
	void set_npc_move(int h, int i, int j, int k );
};