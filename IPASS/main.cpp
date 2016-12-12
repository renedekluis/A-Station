///          Copyright René de Kluis 2016.
/// Distributed under the Boost Software License, Version 1.0.
///    (See accompanying file read_me.txt or copy at
///          http:///www.boost.org/LICENSE_1_0.txt)


#include "hwlib.hpp"
#include "PSX.hpp"
#include "led_control.hpp"
#include "levels.hpp"


int main( void ){	
	
	/// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	

	
	   /****************************************************/
	  /*                   Pin setup                      */
	 /****************************************************/

	///include the namespace target from hwlib
	namespace target = hwlib::target;
	hwlib::wait_ms(1000);
	hwlib::cout << "\n------------------------------\n    A-STATION STARTING UP.\n------------------------------\n";
	///pin setup for the Playstation 2 controller.
	///purple
	auto ps_data = target::pin_in(target::pins::d8); 				
	///gray
	auto ps_command = target::pin_out(target::pins::d9); 			
	///gray
	auto ps_select = target::pin_out(target::pins::d10); 			
	///purple
	auto ps_clock = target::pin_out(target::pins::d11); 			
	
	///pin setup for the leds what have to be turned on 
	///based on the 4th returning byte of the PlayStation controller.
	///brouwn
	auto fourth_byte_cmd   = target::pin_out( target::pins::d2 );	 
	///yellow
	auto fourth_byte_sel = target::pin_out( target::pins::d3 );		
	///yellow
	auto fourth_byte_clock = target::pin_out( target::pins::d4 );	
	
	///pin setup for the leds what have to be turned on 
	///based on the 4th returning byte of the PlayStation controller.
	///brouwn
	auto fifth_byte_cmd   = target::pin_out( target::pins::d5 ); 	
	///yellow
	auto fifth_byte_sel = target::pin_out( target::pins::d6 );		
	///yellow
	auto fifth_byte_clock = target::pin_out( target::pins::d7);		
	
	///enable reset for shift registers.
	auto reset = target::pin_out(target::pins::d1);
	
	///pin setup for the OLED Display
	auto scl = target::pin_oc{ target::pins::scl };
	auto sda = target::pin_oc{ target::pins::sda };
	
	///set i2c bus
	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda{ scl,sda };
	
	///set display
	auto display_frame = hwlib::glcd_oled{ i2c_bus, 0x3c };
	
	
	
	
	      /****************************************************/
	    /*                   SPI setup                      */
	  /****************************************************/
	
	
	hwlib::wait_ms(100);
	auto fourth_byte_spi  = hwlib::spi_bus_bit_banged_sclk_mosi_miso( fourth_byte_clock, fourth_byte_cmd, hwlib::pin_in_dummy );
	hwlib::wait_ms(100);
	auto fifth_byte_spi  = hwlib::spi_bus_bit_banged_sclk_mosi_miso( fifth_byte_clock, fifth_byte_cmd, hwlib::pin_in_dummy );
	hwlib::wait_ms(100);
	auto ps_spi = hwlib::spi_bus_bit_banged_sclk_mosi_miso(ps_clock, ps_command, ps_data, false, false);
	hwlib::wait_ms(100);
	
	
		  /****************************************************/
	    /*               creating objects                   */
	  /****************************************************/
	led_control fourth_byte(
		fourth_byte_spi, 
		fourth_byte_sel,
		reset
	);
	
	led_control fifth_byte(
		fifth_byte_spi, 
		fifth_byte_sel,
		reset
	);

	
	PSX controller(
	ps_spi, 
	ps_data, 
	ps_command, 
	ps_select, 
	ps_clock
	);
	
	levels frame(display_frame);
	
	///check one time for the button state to check if the controller is turned on.
	controller.start_ps_control();
	///if everything is ready, print "welcome"
	///so the player knows A-Station is ready to use.
	hwlib::cout << "\n------------------------------\n          WELCOME!\n------------------------------\n";
	frame.clear(display_frame);
	frame.create_level(display_frame);
	while(1){
		controller.start_ps_control();
		if((int)controller.mode == 0x73){
			hwlib::cout << "\nController state : ON\n";
		}
		else{
			hwlib::cout << "\nController state : OFF\n";
		}
		while((int)controller.mode == 0x73){
			///check the button value and PlayStation controller mode.
			controller.start_ps_control();
			///print button value of controller.
			controller.print_button();
			
			///print the button value on the leds.
			fourth_byte.write_byte(controller.fourth);
			fifth_byte.write_byte(controller.fifth);
			
			///set computer
			frame.computer(display_frame);
			///set player
			frame.play( display_frame, controller.fourth, controller.fifth);
			///set physics
			frame.physics_engine(display_frame);
			
		}
		///if the controller is turned of the screen saver starts.
		hwlib::cout << "Please turn on your controller";
		for(int i = 0; i < 5; i++){
			frame.screen_saver(display_frame);
			controller.start_ps_control();
			hwlib::cout << ".";
		}
		///if the controller is turned on again,
		///rebuild the level.
		if((int)controller.mode == 0x73){
			frame.clear(display_frame);
			frame.level_one(display_frame);
		}
	}
	
	
}

	
	
