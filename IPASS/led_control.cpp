//          Copyright René de Kluis 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file read_me.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#include "hwlib.hpp"
#include "led_control.hpp"
#include <vector>

///pin setup for the led control.
namespace target = hwlib::target;
using namespace std;

///constructor
led_control::led_control(
	hwlib::spi_bus_bit_banged_sclk_mosi_miso & spi, 
	target::pin_out & select, target::pin_out & reset
	):
	spi(spi),
	select(select),
	reset(reset)
	{}

///this function will send the returning 4th and 5th byte to the controller
///the spi's function write_and_read() will correctly shift it 
///through the register so the correct led will turn on.
void led_control::write_byte(byte command){
	reset.set(0);
	reset.set(1);
	byte* send = (byte*)&command;
	byte dummy[1] = {0xFF};
	
	spi.write_and_read(select, 1 , send, dummy);
}
