
/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
​ ​*​ ​@date​ :Februrary 19, 2023
 * @file name : main.c
 * @file_description: This main file includes all the necessary supported header files and
 * 					  Implemented function headers. It calls all initialization functions for
 * 					  LED and Touch.
 * 					  It calls a infinite while loop to continuously run the program.
 *
*************************************************************************************************************************
*/

//Necessary Supported board specific header files
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/* TODO: insert other include files here. */
#include "led.h"
#include "delay.h"
#include "touch.h"
#include "touch_blink_pattern.h"
#include "log.h"

//start of main function

int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    #ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    	BOARD_InitDebugConsole();
	#endif

    // LEDs Initialization
    led_blink_init();
    //Touch Initialization
    Touch_Init();

    LOG("Christmas LED Pattern Blinking with Touch Pad Integration \n\r");


    //Initial LED pattern as given in problem statement
    init_led_pattern();

    //Infinite while loop calling Touch_blink_pattern to blink led based on touch input
    while(1){
    	touch_blink_pattern();
      }


    return 0 ;
}
