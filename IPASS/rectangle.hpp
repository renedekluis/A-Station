//          Copyright René de Kluis 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file read_me.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "hwlib.hpp"


//This call is the library to draw a rectangle.
//In the private values are the foreground coler, background coler and radius.
//When rectangle is called you have to give the coördinate where the rectangle should start and the coördinate where it should end.
//And of course the foreground and background.
//After that you can draw the made rectangle on the screen by calling the function draw().

class rectangle : public hwlib::drawable {
private:  
	hwlib::location end;
	hwlib::color fg;
	hwlib::color bg;
   
public:
	rectangle( 
		hwlib::location start,
		hwlib::location end,
		hwlib::color fg = hwlib::black, 
		hwlib::color bg = hwlib::transparent
	);     
   void draw( hwlib::window & w );
   
}; 


