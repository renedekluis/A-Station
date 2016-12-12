//          Copyright René de Kluis 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file read_me.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "hwlib.hpp"

///This call is the library to draw a circle.
///In the private values are the foreground coler, background coler and radius.
///When circle is called you have to give the coördinate where it should be printed, the radius, foreground and background.
///After that you can draw the made circle on the screen by calling the function draw().
class circle : public hwlib::drawable {
private:   
	int radius;
	hwlib::color fg;
	hwlib::color bg;
   
public:
	circle( 
		hwlib::location start, 
		int radius, 
		hwlib::color fg = hwlib::black, 
		hwlib::color bg = hwlib::transparent
	);     
   void draw( hwlib::window & w );
   
}; 


