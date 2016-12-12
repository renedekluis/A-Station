//          Copyright René de Kluis 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file read_me.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "hwlib.hpp"
#include "rectangle.hpp"


rectangle::rectangle( 
		hwlib::location start, 
		hwlib::location end, 
		hwlib::color fg, 
		hwlib::color bg 
	): 
	hwlib::drawable( start ), 
	end( end ), 
	fg( fg ), 
	bg{ bg }
{}     

void rectangle::draw( hwlib::window & w ){ 
	//Begin and end coördinates are taken out of the locations.
	int start_x = start.x;
	int start_y = start.y;
	int end_x = end.x;
	int end_y = end.y;
	//start drawing at the begin of the x and y and continue untill the end of x and y.
	for(int i = start_x; i < end_x; i++){
		for(int j = start_y; j < end_y; j++){
		w.write(hwlib::location{i,j},fg);
		}
	}
	
}   



