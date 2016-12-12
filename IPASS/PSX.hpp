///          Copyright René de Kluis 2016.
/// Distributed under the Boost Software License, Version 1.0.
///    (See accompanying file read_me.txt or copy at
///          http:///www.boost.org/LICENSE_1_0.txt)

#ifndef PSX_lib_h
#define PSX_lib_h

#include "hwlib.hpp"
#include <string>




namespace target = hwlib::target;


class PSX {
private:
	///PlayStation pins
	hwlib::spi_bus_bit_banged_sclk_mosi_miso ps_spi;
	target::pin_in & ps_data; 
	target::pin_out & ps_command; 
	target::pin_out & ps_select; 
	target::pin_out & ps_clock;
	
	/****************************************************/
   /*            Declare button variables              */
  /****************************************************/
	enum fourth_button_name{
	///4th byte
	Select = 	0x01,
	L3 = 		0x02,
	R3 = 		0x04,
	Start = 	0x08,
	Up = 		0x10,
	Right = 	0x20,
	Down = 		0x40,
	Left = 		0x80
	};

	enum fifth_button_name{
		///5th byte
		L2 = 		0x01,
		R2 = 		0x02,
		L1 = 		0x04,
		R1 = 		0x08,
		Triangle = 	0x10,
		O = 		0x20,
		X = 		0x40,
		Square = 	0x80
	};
	
	
public:

	///The returning 4th and 5th bytes from the PlayStation controller will be stored in the values fourth and fifth.
	///And the mode in the value mode.
	///These are made public, because I have to read them from the main.
	///with the function start_ps_control() the arduino will sent an array of bytes to the controller, 
	///and that will cause that the PlayStation controller sends the value of the mode and button values back.
	///print_button() is a function that will print the current pressed value of the PlayStation on the screen.
	byte fourth = 0xFF;
	byte fifth = 0xFF;
	byte mode = 0xFF;
	PSX(
	hwlib::spi_bus_bit_banged_sclk_mosi_miso & ps_spi, 
	target::pin_in & ps_data, 
	target::pin_out & ps_command, 
	target::pin_out & ps_select, 
	target::pin_out & ps_clock
	);
	
	void start_ps_control(void);
	void print_button();
	
};

#endif



