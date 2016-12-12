//          Copyright René de Kluis 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file read_me.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "hwlib.hpp"
#include "display.hpp"


 /// in this class is almost everything of the game defined.
 /// well, in the .cpp are the definitions, here are the declarations,
 /// but you know what i mean.
 /// there are a lot of private values:
 /// move values for the player,
 /// saved values of the player (for faster clearing),
 /// move values for the npc (non-playing character),
 /// saved values of the npc (again for faster clearing),
 /// on what level the ground should be,
 /// the radius of the player,
 /// and a boolean to check if the player is in the air or not. (this will be explained with the fysics funtion)
 /// 
 /// Also there are two enumerations with the button values, the first enumeration is for the buttons what return on the fourth bye
 /// and the second enumeration is for the button values that return on the fifth byte.


class levels{
private:
	hwlib::window & w;
	byte direction;
	int move_x = 0;
	int move_y = 0;
	int save_x = 0;
	int save_y = 0;
	int computer_move_x = 20;
	int computer_move_y = 20;
	int computer_save_x = 0;
	int computer_save_y = 0;
	int ground = 1;
	int current_radius = 5;
	bool in_air = false;
	int map = 1;
	int level = 0;
	hwlib::location object1_start = hwlib::location{10,0};
	hwlib::location object1_end = hwlib::location{40,30};
	enum commands_left{
		up 			= 0x10, 
		right		= 0x20, 
		down		= 0x40, 
		left 		= 0x80, 
		down_left 	= 0xC0, 
		down_right 	= 0x60, 
		up_left 	= 0x90, 
		up_right 	= 0x30
	};
	enum commands_right{
		triangle 	= 0x10, 
		round 		= 0x20, 
		X 			= 0x40, 
		square 		= 0x80, 
		X_round 	= 0x60
	};
	
	
public:
	 /// the following function are all for making the game. create level will set a level, 
	 /// but in a level there are maps, so there is a function for level one.
	 /// In that function there is declared what that level should have.
	 /// one of those things is that level one has three maps, 
	 /// so in there is decleared what should be created in those maps.
	 /// the play function looks what button is pressed and let the player react on that.
	 /// function fysics is a function where is defined that a player can not fly and therefor fall down to the ground.
	 /// 
	 /// I will explain more in the .cpp file.
	 /// the value hwlib::window is a reference to the display screen.
	 /// you have to give this value to almost all function so the function can print items on the correct screen.
	 
	 ///constructor
	levels(hwlib::window & w);
	///screen saver
	void screen_saver(hwlib::window & w);
	///creates level one
	void level_one(hwlib::window & w);
	///clear screen
	void clear(hwlib::window & w );
	///constant checking for movement of player
	void play(hwlib::window & w, byte controller_byte_left, byte controller_byte_right);
	///set the player variables in display
	void set_variables();
	///makes the player fall down
	void physics_engine(hwlib::window & w);
	///set the play on the correct value
	void set_player(hwlib::window & w, int radius, int extra_x, int extra_y);
	///create maps in a level
	void create_level(hwlib::window & w);
	///set an object in the map
	void set_object(hwlib::window & w, hwlib::location k, hwlib::location j);
	///movement of the npc
	void computer(hwlib::window & w);
};