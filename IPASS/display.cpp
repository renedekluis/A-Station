//          Copyright René de Kluis 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file read_me.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "hwlib.hpp"
#include "display.hpp"


 /// contructor
 /// used to make the object display

display::display(hwlib::window & w):
	w(w)
{}


 /// the rand function is used to make a random value.
 /// this is used in the random circles screen saver.

int display::rand(){
	static int n = 0;
	n = n * 214013L + 2531011L; 
	return ( n >> 16) & 0x7fff; 
}


 /// random_in_range is used for, well, the name says is,
 ///get a random value between two integers.

unsigned int display::random_in_range( unsigned int min, unsigned int max ){
	unsigned int x = rand();
	x = x % ( max - min + 1 ); 
	return min + x;
}



 /// clears the whole screen

void display::clear(hwlib::window & w ){
	w.clear();
}


 /// this is the screen saver.
 ///this will be called if the PlayStation controller is turned off.
 /// for this to work i've decleard a random int x, y and radius,
 /// made with the random function what i've explained above.

void display::graphics_random_circles( hwlib::window & w ){
	int x  = random_in_range( 10, w.size.x - 10 );
	int y = random_in_range( 10, w.size.y - 10 );
	int s  = random_in_range( 4, w.size.y / 4 );
	auto moving_circle = hwlib::circle( 
		hwlib::location{  x,  y },
		s,
		w.foreground 
	);
	moving_circle.draw( w );
}


 ///this function is to let the player move.
 /// i've chosen not to clear the screen everytime the player move.
 /// but if the player moves to remove the old position of the player.
 /// in this way the system only had to re-draw a small part instead of the whole screen.
 /// this made the program run faster.
 /// 
 /// also, if the player does not move, the function won't do anything, 
 /// because 
 /// 1) it isn't nessasery 
 /// 2) makes the program run faster instead always re-drawing

void display::move_player(hwlib::window & w, int player_radius){
	int x  = display::start_x;
	int y = display::start_y;
	int s  = player_radius;

	if(save_x != move_x || save_y != move_y)
	{
		if(need_clear == false){
			auto clear_dodge = circle(
				hwlib::location{ x + save_x, y + save_y},
				3,
				hwlib::green
			);
			clear_dodge.draw(w);
			
			auto clear_player = circle(
				hwlib::location{  x + save_x,  y + save_y},
				s,
				hwlib::green 
			);
			clear_player.draw(w);
			
			auto moving_circle = circle( 
				hwlib::location{  x + move_x,  y + move_y},
				s,
				w.foreground 
			);
			moving_circle.draw( w );
			save_x = move_x;
			save_y = move_y;
		}
		else{
			auto clear_player = circle(
				hwlib::location{  x + save_x,  y + save_y},
				5,
				hwlib::green 
			);
			clear_player.draw(w);
			
			auto clear_dodge = circle(
				hwlib::location{  x + save_x,  y + save_y},
				s,
				hwlib::green 
			);
			clear_dodge.draw(w);
			
			auto  player_dodge = circle(
				hwlib::location{ x + move_x, y + move_y},
				s,
				w.foreground
			);
			player_dodge.draw(w);
		}
	}
}


 ///this function will draw the player at the starting position.
 ///this is because the previous function doesn't draw the player in the first instance,
 ///because the player hasn't moved yet.

void display::start_player(hwlib::window & w){
	auto set_player = circle( 
			hwlib::location{ display::start_x,  start_y},
			5,
			w.foreground 
		);
		set_player.draw( w );
}



 /// create_ground will create the floor on the bottum of the screen.

void display::create_ground(hwlib::window & w){
	
	rectangle ground(
		hwlib::location{0, 0},
		hwlib::location{128, 5},
		w.foreground 
	);
	ground.draw(w);
	
}


 ///create_object will create a rectangle of choice as an object in the game.
 ///the object is not decleared in the fysics yet, so the player will, for now,
 /// move through the object unfortunally.

void display::create_object(hwlib::window & w, hwlib::location start_coordinate,hwlib::location end_coordinate){
	rectangle object(
		start_coordinate,
		end_coordinate,
		w.foreground 
	);
	object.draw(w);
	hwlib::wait_ms(100);
}


 ///sets the correct current values in the display.hpp,
 ///so the player moves correctly.

void display::set_move(int h, int i, int j, int k ){
	display::move_x = h;
	display::move_y = i;
	display::save_x = j;
	display::save_y = k;
	
}


 /// if the player is not dodged, this function will be called, 
 /// so the player will be drawn with a radius of 5. (normal)

void display::clear_dodge(hwlib::window & w){
	display::need_clear = false;
}


 ///if the player is not dodged, this function will be called, 
 ///so the player will be drawn with a radius of 3. (dodged)

void display::set_dodge(hwlib::window & w){
	display::need_clear = true;
}



 /// this function is almost the same as the set_move function,
 /// only this is for the npc that chases you.

void display::set_npc_move(int h, int i, int j, int k ){
	display::computer_move_x = h;
	display::computer_move_y = i;
	display::computer_save_x = j;
	display::computer_save_y = k;
	
}



 ///this is the same as move player, 
 ///except that the npc can not be in a dodged state, 
 ///so that part ( and the booleans to clear and set dodged) are removed.
 
void display::move_npc(hwlib::window & w){
	int x  = display::start_x;
	int y  = display::start_y;
	int s  = 5;
	
	auto clear_player = circle(
		hwlib::location{  x + computer_save_x,  y + computer_save_y},
		s,
		hwlib::green 
	);
	clear_player.draw(w);
	
	auto moving_circle = circle( 
		hwlib::location{  x + computer_move_x,  y + computer_move_y},
		s,
		w.foreground 
	);
	moving_circle.draw( w );
	computer_save_x = computer_move_x;
	computer_save_y = computer_move_y;
}