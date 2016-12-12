//          Copyright René de Kluis 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file read_me.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "hwlib.hpp"
#include "circle.hpp"



///constructor
circle::circle( 
		hwlib::location start, 
		int radius, 
		hwlib::color fg, 
		hwlib::color bg 
	): 
	hwlib::drawable{ start }, 
	radius{ radius }, 
	fg{ fg }, 
	bg{ bg }
{}     

void circle::draw( hwlib::window & w ){ 
	/// don't draw anything when the size would be 0
	if( radius < 1 ){
		return;       
	}
	
	/// http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
   
	int fx = 1 - radius;
	int ddFx = 1;
	int ddFy = -2 * radius;
	int x = 0;
	int y = radius;
	
	/// top and bottom
	w.write( start + hwlib::location( 0 , + radius ), fg );
	w.write( start + hwlib::location( 0 , - radius  ), fg );

	/// left and right 
	w.write( start + hwlib::location( + radius , 0  ), fg );
	w.write( start + hwlib::location( - radius , 0  ), fg );
		 
	if( bg != hwlib::transparent ){
   
		/// top and bottom
		w.write( start + hwlib::location( 0 , + radius  ), fg );
		w.write( start + hwlib::location( 0 , - radius  ), fg );

		/// left and right
		hwlib::line(  
				start - hwlib::location( radius, 0), 
				start + hwlib::location( radius, 0), 
				fg 
		).draw( w );
	} 
	
	while( x < y ){
	  
		/// calculate next outer circle point
		if( fx >= 0 ){
			y--;
			ddFy += 2;
			fx += ddFy;
		}
		x++;
		ddFx += 2;
		fx += ddFx;   
					
		w.write( start + hwlib::location( + x , + y  ), fg );
		w.write( start + hwlib::location( - x , + y  ), fg );
		w.write( start + hwlib::location( + x , - y  ), fg );
		w.write( start + hwlib::location( - x , - y  ), fg );
		w.write( start + hwlib::location( + y , + x  ), fg );
		w.write( start + hwlib::location( - y , + x  ), fg );
		w.write( start + hwlib::location( + y , - x  ), fg );
		w.write( start + hwlib::location( - y , - x  ), fg );
			
		if( bg != hwlib::transparent  ){
			hwlib::line( start + hwlib::location( -x ,  y ), start + hwlib::location(  x,  y  ), bg ).draw( w );
			hwlib::line( start + hwlib::location( -x , -y ), start + hwlib::location(  x , -y ), bg ).draw( w );
			hwlib::line( start + hwlib::location( -y ,  x ), start + hwlib::location(  y ,  x  ), bg ).draw( w );
			hwlib::line( start + hwlib::location( -y , -x  ), start + hwlib::location(  y , -x ), bg ).draw( w );
		}
	}
}   



