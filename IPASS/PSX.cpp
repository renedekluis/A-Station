///          Copyright René de Kluis 2016.
/// Distributed under the Boost Software License, Version 1.0.
///    (See accompanying file read_me.txt or copy at
///          http:///www.boost.org/LICENSE_1_0.txt)

#include "hwlib.hpp"
#include "PSX.hpp"
#include "led_control.hpp"





    /****************************************************/
   /*            byte array with commands              */
  /*     for sending to the Playstation Controller.   */
 /****************************************************/
byte read_data[] = {0x01,0x42,0x00,0x00,0x00};
byte return_data[5];


///Setup spi connection with the clock command and data pin.
///Last 2 booleans are both false, the first booleans is to check if the spi has to work with the Most Significant Bit first or Least Significant Bit first.
///Here we need Last Significant Bit first, so that boolean is false.
///The second boolean is to check if the spi has to work with an active high clock or an active low. 
///In my case I need a active high clock so the boolean has to be false.

PSX::PSX(
	hwlib::spi_bus_bit_banged_sclk_mosi_miso & ps_spi, 
	target::pin_in & ps_data, 
	target::pin_out & ps_command, 
	target::pin_out & ps_select, 
	target::pin_out & ps_clock
	):
	ps_spi(ps_spi),
	ps_data(ps_data),
	ps_command(ps_command), 
	ps_select(ps_select),
	ps_clock(ps_clock)
{
}

///this following function will communicate with the PlayStation controller.
///the read_data byte array will be send to the controller.
///on the second byte there will come the current mode of the controller.
///and on the fourth and fifth will be the button that is pressed (if there is one pressed).
void PSX::start_ps_control(){
	hwlib::wait_ms(10);
	ps_spi.write_and_read(ps_select, 5 , read_data, return_data );
	
	mode = return_data[1];
	fourth = 0xFF - return_data[3];
	fifth = 0xFF - return_data[4];
}
///This function will print the current button value in the command screen.
///For an embedded system is can be ereased, but it is very usefull for debugging.
///as said earlier, half of the button values will be returned on the fourth byte and the other half on the fift.
///So I've made two switch cases to make the arduino print the correct current value of the buttons.
void PSX::print_button(){
	switch(fourth){
		case PSX::fourth_button_name::Select:
			hwlib::cout << "Select\n";
			break;
		case PSX::fourth_button_name::L3:
			hwlib::cout << "L3\n";
			break;
		case PSX::fourth_button_name::R3:
			hwlib::cout << "R3\n";
			break;
		case PSX::fourth_button_name::Start:
			hwlib::cout << "Start\n";
			break;
		case PSX::fourth_button_name::Up:
			hwlib::cout << "Up\n";
			break;
		case PSX::fourth_button_name::Right:
			hwlib::cout << "Right\n";
			break;
		case PSX::fourth_button_name::Down:
			hwlib::cout << "Down\n";
			break;
		case PSX::fourth_button_name::Left:
			hwlib::cout << "Left\n";
			break;
			
		default:
			break;
	}
	
	switch(fifth){
		case PSX::fifth_button_name::L2:
			hwlib::cout << "L2\n";
			break;
		case PSX::fifth_button_name::R2:
			hwlib::cout << "R2\n";
			break;
		case PSX::fifth_button_name::L1:
			hwlib::cout << "L1\n";
			break;
		case PSX::fifth_button_name::R1:
			hwlib::cout << "R1\n";
			break;
		case PSX::fifth_button_name::Triangle:
			hwlib::cout << "Triangle\n";
			break;
		case PSX::fifth_button_name::O:
			hwlib::cout << "O\n";
			break;
		case PSX::fifth_button_name::X:
			hwlib::cout << "X\n";
			break;
		case PSX::fifth_button_name::Square:
			hwlib::cout << "Square\n";
			break;
			
		default:
			break;
	}
	
}

