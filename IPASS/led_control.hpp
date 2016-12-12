//          Copyright René de Kluis 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file read_me.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#include "hwlib.hpp"

#ifndef led_control_h
#define led_control_h


 /// this class will control what led light will turn on.
 /// in the read and write function the returning byte value 
 /// of the controller will be shifted through the HC595 register so the correct light will turn on.

namespace target = hwlib::target;
class led_control{
private:
	hwlib::spi_bus_bit_banged_sclk_mosi_miso spi;
	target::pin_out & select; 
	target::pin_out & reset;
	
public:
	led_control(
		hwlib::spi_bus_bit_banged_sclk_mosi_miso & spi, 
		target::pin_out & select,
		target::pin_out & reset
	);
	
	void write_byte(byte command);
	
};



#endif