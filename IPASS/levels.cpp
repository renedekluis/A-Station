//          Copyright René de Kluis 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file read_me.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "hwlib.hpp"
#include "levels.hpp"

 /// the following defines are the values how much the player should react on the buttons.
 /// to make the code more clear i've made the choice to decleare those values as defines, 
 /// so it will be easyer to read what is happening.


#define move_left  		 3
#define move_right  	-3
#define move_up  		 3
#define move_down 		-3
#define small_up 		 1
#define jump_length		 5


 /// contructor
levels::levels(hwlib::window & w):
	w(w)
{}

/// create level.
/// in this function there is only one level now,
/// but as you can see you can easily add new levels.
void levels::create_level(hwlib::window & w){
	switch(level){
		case 0:
			level_one(w);
			break;
	}
}


///here is defined what sould be in level one.
///as you can see there are 3 maps. 
/// when each map is build there is a loading screen.
/// in each map you need a ground where the player van stand on.
/// the map creation begins with clearing the whole screen, 
/// because there could be object from the previous map on the screen and those have to be deleted.
void levels::level_one(hwlib::window & w){
	hwlib::cout << "\n--------------------------------\nloading level 1, please wait.\n\n";
	display set_level_one(w);
	if(map < 0){		map = 0;	}
	else if(map > 2){	map = 2;	}
	switch(map){
		case 0:
			hwlib::cout << "\nloading map 0, please wait.\n";
			clear(w);
			set_level_one.create_ground(w);
			set_level_one.create_object(w, hwlib::location{123,0},hwlib::location{128,64});
			set_level_one.start_player(w);
			break;
		case 1:
			hwlib::cout << "\nloading map 1, please wait.\n";
			clear(w);
			set_level_one.create_ground(w);
			break;
		case 2:
			hwlib::cout << "\nloading map 2, please wait.\n";
			clear(w);
			set_level_one.create_ground(w);
			set_level_one.create_object(w, hwlib::location{0,0},hwlib::location{5,64});
			
		default:
			break;
	}
	
	hwlib::cout << "loading level 1, complete.\n--------------------------------\n";
}


 /// clear clears the screen.
 /// this is used for creating maps, first startup, and so on, 
 /// because then the whole screen needs an clear.
 /// in other cases i clear the objects by overwriting them with blancs.

void levels::clear(hwlib::window & w ){
	display clear_screen(w);
	clear_screen.clear(w);
}



 /// when the controller is off this function will be called.
 /// this will draw random circles on the screen.

void levels::screen_saver(hwlib::window & w){
	display SS(w);
	SS.clear(w);
	SS.graphics_random_circles(w);
	SS.clear(w);
}



 /// this will set the player move in save,
 /// so the old circle can be deleted by the next call of set_player.

void levels::set_variables(){
	levels::save_x = levels::move_x;
	levels::save_y = levels::move_y;
}


 /// this will draw the player on the new position, based on the button that is pressed on the PlayStation controller.
 /// if the player goes out of the map on the left or right side, the map on the right or left will be created.
 /// the other 2 if statements are there so the player can not fall through the ground 
 /// or (if the fysics don't work well) fly out of the screen at the top of the screen.

void levels::set_player(hwlib::window & w, int radius, int extra_x, int extra_y){
	display move_player(w);
	if(radius == 3){	move_player.set_dodge(w);	}
	else{				move_player.clear_dodge(w);	}
	
	set_variables();
	current_radius = radius;
	levels::move_x += extra_x; 
	levels::move_y += extra_y;
	
	if(move_x > 57){
		levels::move_x = levels::map--;
		level_one(w);
	}
	if(move_x < -69){
		levels::move_x = levels::map++;
		level_one(w);
	}
	if(move_y > 45){		levels::move_y =	45;			}
	if(move_y < ground){	levels::move_y = 	ground;		}
	
	move_player.set_move(levels::move_x, levels::move_y, levels::save_x, levels::save_y);
	move_player.move_player( w , radius );
}



 /// this function will look at the returning bytes from the controller and let the player react on that.
 /// i could not make the player jump or dodge only by pressing X or round in this time, 
 /// but i've managed to make a lot of key combinations happen.

void levels::play(hwlib::window & w, byte controller_byte_left, byte controller_byte_right){
	set_variables();
	if((int)controller_byte_left != 0){

		switch((int)controller_byte_left){
			case commands_left::up:
			if(move_y < ground + 3){
				for(int i = 0; i < jump_length; i++){
					set_player(w, 5, 0 , move_up);
				}
			}
				break;
				
			case commands_left::up_right:
			if(move_y < ground + 3){
				for(int i = 0; i < jump_length; i++){
					set_player(w, 5, move_right, move_up);
				}
			}
				break;
				
			case commands_left::up_left:
			if(move_y < ground + 3){
				for(int i = 0; i < jump_length; i++){
					set_player(w, 5, move_left, move_up);
				}
			}
				break;
				
			case commands_left::down:
				switch(controller_byte_right){
					case commands_right::round:
						set_player(w, 3, 0, 0);
						break;
					case commands_right::X:
					if(move_y < ground + 3){
						for(int i = 0; i < jump_length; i++){
							set_player(w, 3, 0, small_up);
						}
					}
						break;
					default:
						set_player(w, 3, 0, 0);
						break;
				}
				break;
				
			case commands_left::down_right:
				switch((int)controller_byte_right){
					case commands_right::X:
					if(move_y < ground + 3){
						for(int i = 0; i < jump_length; i++){
							set_player(w, 3, move_right, small_up);
						}
					}
						break;
					default:
						set_player(w, 3, move_right, 0);
						break;
				}
				break;
				
			case commands_left::down_left:
				switch(controller_byte_right){
					case commands_right::X:
					if(move_y < ground + 3){
						for(int i = 0; i < jump_length; i++){
							set_player(w, 3, move_left, small_up);
						}
					}
						break;
					default:
						set_player(w, 3, move_left, 0);
						break;
				}
				break;
				
			case commands_left::left:
				switch(controller_byte_right){
					case commands_right::X:
					if(move_y < ground + 3){
						for(int i = 0; i < jump_length; i++){
							set_player(w, 5, move_left, move_up);
						}
					}
						break;
					case commands_right::round:
						set_player(w, 3, move_left, 0);
						break;
					default:
						set_player(w, 5, move_left, 0);
						break;
				}
				break;
				
			case commands_left::right:
				switch(controller_byte_right){
					case commands_right::X:
					if(move_y < ground + 3){
						for(int i = 0; i < jump_length; i++){
							set_player(w, 5, move_right, move_up);
						}
					}
						break;
					case commands_right::round:
						set_player(w, 3, move_right, 0);
						break;
					default:
						set_player(w, 5, move_right, 0);
						break;
				}
				break;
				
			default:
				break;
		}
	}
}



 ///this function is very importend for the game.
 ///the fysics will assure that the player won't fall through the ground and can not fly.
 ///if the player is in air, so if the player is higher then the ground,
 ///the code will tell play that the player is forbidden to jump again before he reaches the ground.
 ///i've chosen for this, because in the real world you can't jump again in the air as well.

void levels::physics_engine(hwlib::window & w){
	display physics(w);
	
	if(10 + move_y > ground){
		in_air = true;
		set_player(w, current_radius, 0, move_down);
	}
	else{
		in_air = false;
	}
}


 /// this function will set an npc on the screen that will hunt you down.
 /// if the computer is on the same position as you are, the computer "eats" you and the game will restart.

void levels::computer(hwlib::window & w){
	display move_computer(w);
	levels::computer_save_x = levels::computer_move_x;
	levels::computer_save_y = levels::computer_move_y;
	bool one = false;
	bool two = false;
	if(move_x > computer_move_x ){ 
		computer_move_x += 1;
	}
	else if(move_x < computer_move_x ){ 
		computer_move_x -= 1;
	}
	else{ 
		one = true;
	}
	
	if(move_y > computer_move_y ){ 
		computer_move_y += 1;
	}
	else if(move_y < computer_move_y ){ 
		computer_move_y -= 1;
	}
	else{ 
		two = true;
	}
	
	if(one == true && two == true){ 
		map = 1;
		level_one(w);
	}
	
	move_computer.set_npc_move(levels::computer_move_x, levels::computer_move_y, levels::computer_save_x, levels::computer_save_y);
	move_computer.move_npc( w );
}



