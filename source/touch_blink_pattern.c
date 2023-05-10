/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
 * @file name : touch_blink.c
 * @date : February 19, 2023
 * @file_description: It consists of MKL25Z4.h a default header file of the KL25Z board and
 * 					  stdio.h header file used for printf function.
 *                     Along with I have included delay.h,led.h and touch.h whose function prototypes are being used in this file.
 * 					   This file includes Touch Initialization and Touch_scan_LH value function
 * 					   which initializes TSI module and scans touch value
 *
*************************************************************************************************************************
*/



#include "MKL25Z4.h"
#include <stdio.h>
#include "delay.h"
#include "led.h"
#include "touch.h"
#include "log.h"


#define TOUCH_SENSE_OFFSET_VAL 29 // Touch offset of my board
#define TOUCH_SENSE_MID_VAL 275  // Touch sense middle value approximately taken
#define HUNDRED_MSEC_DELAY 600000 //100ms delay approximately taken with the help of stop watch
volatile uint32_t touch_value = 0 ; // initializing touch value to zero

// enumerating data for 3 states of touch pattern
enum state
{
	no_touch,
	left_touch,
	right_touch
}CurrentState;

// defining flags for touch condition
int left_touch_flag = 0;
int right_touch_flag = 0;

/*
 * @Function
 *     This function checks for the touch sensed value for every 100ms and blinks LEDs based
 *     on input touch value.
 *     Synchronization of checking touch sense for every 100 ms and blinking LED is done
 *     based on Polling method.
 */
void touch_blink_pattern()
{

	// Print statements in DEBUG, This print will no occur in first call as Current State is not updated
	if(CurrentState == no_touch)
	{
		LOG("Start Timer 500ms\n\r");
		LOG("Color changes to RED\n\r");
	}
	else if(CurrentState == left_touch)
	{
		LOG("Start Timer 500ms\n\r");
		LOG("Color changes to RED\n\r");

	}
	else if(CurrentState == right_touch)
	{
		LOG("Start Timer 500ms\n\r");
		LOG("Color changes to GREEN\n\r");
	}
	//RED LED ON for 500ms if no touch input comes in between
	for(int i=0;i<5;i++)
	{
		touch_value = Touch_Scan_LH();//reading touch sense for every 100ms
		// Condition for no touch sense case
		if(touch_value < TOUCH_SENSE_OFFSET_VAL && (left_touch_flag == 0 && right_touch_flag == 0))
		{
			CurrentState = no_touch;
		}
		// condition to check if touch sense occured on left side of my board
		else if((touch_value > TOUCH_SENSE_OFFSET_VAL) && (touch_value < TOUCH_SENSE_MID_VAL))
		{
			CurrentState = left_touch;
			left_touch_flag = 1; // turning flag high when left touch is done

			LOG("Color changes to RED -- Slider Value:%d \n\r",touch_value);

		}
			// condition to check if touch sense occured on right side of my board
		else if(touch_value > TOUCH_SENSE_MID_VAL)
		{
			CurrentState = right_touch;
			right_touch_flag = 1; // turning flag high when right touch is done

			LOG("Color changes to GREEN -- Slider Value:%d \n\r",touch_value);

		}
		//switch case to check for the Current state of the touch and turn LEDs accordingly
		switch(CurrentState)
		{
			case no_touch:
				led_RED_ON();
				delay(HUNDRED_MSEC_DELAY);
				break;
			case left_touch:
				led_RED_ON();
				delay(HUNDRED_MSEC_DELAY);
				break;
			case right_touch:
				led_GREEN_ON();
				delay(HUNDRED_MSEC_DELAY);
				break;
			default:
				break;
		}
	}

	LOG("Start Timer 500ms\n\r");
	LOG("LEDs OFF\n\r");

	//LED OFF for 500ms if no touch input comes in between
		for(int i=0;i<5;i++)
		{
			touch_value = Touch_Scan_LH();//reading touch sense for every 100ms
			// Condition for no touch sense case
			if(touch_value < TOUCH_SENSE_OFFSET_VAL && (left_touch_flag == 0 && right_touch_flag == 0))
			{
				CurrentState = no_touch;
			}
			// condition to check if touch sense occured on left side of my board
			else if((touch_value > TOUCH_SENSE_OFFSET_VAL) && (touch_value < TOUCH_SENSE_MID_VAL))
			{
				CurrentState = left_touch;
				left_touch_flag = 1; // turning flag high when left touch is done

				LOG("Color changes to RED -- Slider Value:%d \n\r",touch_value);

			}
			// condition to check if touch sense occured on right side of my board
			else if(touch_value > TOUCH_SENSE_MID_VAL)
			{
				CurrentState = right_touch;
				right_touch_flag = 1; // turning flag high when right touch is done

				LOG("Color changes to GREEN -- Slider Value:%d \n\r",touch_value);

			}

			led_OFF();
			delay(HUNDRED_MSEC_DELAY);
		}
// Print statements in DEBUG
	if(CurrentState == no_touch)
	{

		LOG("Start Timer 1000ms\n\r");
		LOG("Color changes to GREEN\n\r");

	}
	else if(CurrentState == left_touch)
	{

		LOG("Start Timer 1000ms\n\r");
		LOG("Color changes to RED\n\r");

	}
	else if(CurrentState == right_touch)
	{

		LOG("Start Timer 1000ms\n\r");
		LOG("Color changes to GREEN\n\r");

	}

	//RED LED ON for 1000ms if no touch input comes in between
	for(int i=0;i<10;i++)
	{
		touch_value = Touch_Scan_LH();//reading touch sense for every 100ms
		// Condition for no touch sense case
		if(touch_value < TOUCH_SENSE_OFFSET_VAL && (left_touch_flag == 0 && right_touch_flag == 0))
		{
			CurrentState = no_touch;
		}
		// condition to check if touch sense occured on left side of my board
		else if((touch_value > TOUCH_SENSE_OFFSET_VAL) && (touch_value < TOUCH_SENSE_MID_VAL))
		{
			CurrentState = left_touch;
			left_touch_flag = 1; // turning flag high when left touch is done

			LOG("Color changes to RED -- Slider Value:%d \n\r",touch_value);

		}
		// condition to check if touch sense occured on right side of my board
		else if(touch_value > TOUCH_SENSE_MID_VAL)
		{
			CurrentState = right_touch;
			right_touch_flag = 1; // turning flag high when right touch is done

			LOG("Color changes to GREEN -- Slider Value:%d \n\r",touch_value);

		}
		//switch case to check for the Current state of the touch and turn LEDs accordingly
		switch(CurrentState)
		{
			case no_touch:
			led_GREEN_ON();
			delay(HUNDRED_MSEC_DELAY);
			break;
			case left_touch:
				led_RED_ON();
				delay(HUNDRED_MSEC_DELAY);
				break;
			case right_touch:
				led_GREEN_ON();
				delay(HUNDRED_MSEC_DELAY);
				break;
			default:
				break;
		}
	}

	LOG("Start Timer 500ms\n\r");
	LOG("LEDs OFF\n\r");

	//LED OFF for 500ms if no touch input comes in between
		for(int i=0;i<5;i++)
		{
			touch_value = Touch_Scan_LH();//reading touch sense for every 100ms
			// Condition for no touch sense case
			if(touch_value < TOUCH_SENSE_OFFSET_VAL && (left_touch_flag == 0 && right_touch_flag == 0))
			{
				CurrentState = no_touch;
			}
			// condition to check if touch sense occured on left side of my board
			else if((touch_value > TOUCH_SENSE_OFFSET_VAL) && (touch_value < TOUCH_SENSE_MID_VAL))
			{
				CurrentState = left_touch;
				left_touch_flag = 1; // turning flag high when left touch is done

				LOG("Color changes to RED -- Slider Value:%d \n\r",touch_value);

			}
			// condition to check if touch sense occured on right side of my board
			else if(touch_value > TOUCH_SENSE_MID_VAL)
			{
				CurrentState = right_touch;
				right_touch_flag = 1; // turning flag high when right touch is done

				LOG("Color changes to GREEN -- Slider Value:%d \n\r",touch_value);

			}

			led_OFF();
			delay(HUNDRED_MSEC_DELAY);
		}

// Print statements in DEBUG
	if(CurrentState == no_touch)
	{

		LOG("Start Timer 2000ms\n\r");
		LOG("Color changes to RED\n\r");

		}
	else if(CurrentState == left_touch)
	{

		LOG("Start Timer 2000ms\n\r");
		LOG("Color changes to RED\n\r");

	}
	else if(CurrentState == right_touch)
	{

		LOG("Start Timer 2000ms\n\r");
		LOG("Color changes to GREEN\n\r");

	}
	//RED LED ON for 2000ms if no touch input comes in between
	for(int i=0;i<20;i++)
	{
		touch_value = Touch_Scan_LH();//reading touch sense for every 100ms
		// Condition for no touch sense case
		if(touch_value < TOUCH_SENSE_OFFSET_VAL && (left_touch_flag == 0 && right_touch_flag == 0))
		{
			CurrentState = no_touch;
		}
		// condition to check if touch sense occured on left side of my board
		else if((touch_value > TOUCH_SENSE_OFFSET_VAL) && (touch_value < TOUCH_SENSE_MID_VAL))
		{
			CurrentState = left_touch;
			left_touch_flag = 1; // turning flag high when left touch is done

			LOG("Color changes to RED -- Slider Value:%d \n\r",touch_value);

		}
		// condition to check if touch sense occured on right side of my board
		else if(touch_value > TOUCH_SENSE_MID_VAL)
		{
			CurrentState = right_touch;
			right_touch_flag = 1; // turning flag high when right touch is done

			LOG("Color changes to GREEN -- Slider Value:%d \n\r",touch_value);

		}
		//switch case to check for the Current state of the touch and turn LEDs accordingly
		switch(CurrentState)
		{
			case no_touch:
				led_RED_ON();
				delay(HUNDRED_MSEC_DELAY);
				break;
			case left_touch:
				led_RED_ON();
				delay(HUNDRED_MSEC_DELAY);
				break;
			case right_touch:
				led_GREEN_ON();
				delay(HUNDRED_MSEC_DELAY);
				break;
			default:
				break;
		}
	}


	LOG("Start Timer 500ms\n\r");
	LOG("LEDs OFF\n\r");

	//LED OFF for 500ms if no touch input comes in between
	for(int i=0;i<5;i++)
	{
		touch_value = Touch_Scan_LH();//reading touch sense for every 100ms
		// Condition for no touch sense case
		if(touch_value < TOUCH_SENSE_OFFSET_VAL && (left_touch_flag == 0 && right_touch_flag == 0))
		{
			CurrentState = no_touch;
		}
		// condition to check if touch sense occured on left side of my board
		else if((touch_value > TOUCH_SENSE_OFFSET_VAL) && (touch_value < TOUCH_SENSE_MID_VAL))
		{
			CurrentState = left_touch;
			left_touch_flag = 1; // turning flag high when left touch is done

			LOG("Color changes to RED -- Slider Value:%d \n\r",touch_value);

		}
		// condition to check if touch sense occured on right side of my board
		else if(touch_value > TOUCH_SENSE_MID_VAL)
		{
			CurrentState = right_touch;
			right_touch_flag = 1; // turning flag high when right touch is done

			LOG("Color changes to GREEN -- Slider Value:%d \n\r",touch_value);

		}

		led_OFF();
		delay(HUNDRED_MSEC_DELAY);
	}
// Print statements in DEBUG
	if(CurrentState == no_touch)
	{

		LOG("Start Timer 3000ms\n\r");
		LOG("Color changes to GREEN\n\r");

	}
	else if(CurrentState == left_touch)
	{

		LOG("Start Timer 3000ms\n\r");
		LOG("Color changes to RED\n\r");

	}
	else if(CurrentState == right_touch)
	{

		LOG("Start Timer 3000ms\n\r");
		LOG("Color changes to GREEN\n\r");

	}
	//GREEN LED ON for 3000ms if no touch input comes in between
	for(int i=0;i<30;i++)
	{
		touch_value = Touch_Scan_LH();//reading touch sense for every 100ms
		// Condition for no touch sense case
		if(touch_value < TOUCH_SENSE_OFFSET_VAL && (left_touch_flag == 0 && right_touch_flag == 0))
		{
		    CurrentState = no_touch;
		}
		// condition to check if touch sense occured on left side of my board
		else if((touch_value > TOUCH_SENSE_OFFSET_VAL) && (touch_value < TOUCH_SENSE_MID_VAL))
		{
		    CurrentState = left_touch;
		    left_touch_flag = 1; // turning flag high when left touch is done

		    LOG("Color changes to RED -- Slider Value:%d \n\r",touch_value);

		}
		// condition to check if touch sense occured on right side of my board
		else if(touch_value > TOUCH_SENSE_MID_VAL)
		{
		    CurrentState = right_touch;
		    right_touch_flag = 1; // turning flag high when right touch is done

		    LOG("Color changes to GREEN -- Slider Value:%d \n\r",touch_value);

		}
		//switch case to check for the Current state of the touch and turn LEDs accordingly
		switch(CurrentState)
		{
			case no_touch:
				led_GREEN_ON();
				delay(HUNDRED_MSEC_DELAY);
				break;
			case left_touch:
				led_RED_ON();
				delay(HUNDRED_MSEC_DELAY);
				break;
			case right_touch:
				led_GREEN_ON();
				delay(HUNDRED_MSEC_DELAY);
				break;
			default:
				break;
		}
	}

	LOG("Start Timer 500ms\n\r");
	LOG("LEDs OFF\n\r");

	//LED OFF for 500ms if no touch input comes in between
		for(int i=0;i<5;i++)
		{
			touch_value = Touch_Scan_LH();//reading touch sense for every 100ms
			// Condition for no touch sense case
			if(touch_value < TOUCH_SENSE_OFFSET_VAL && (left_touch_flag == 0 && right_touch_flag == 0))
			{
			    CurrentState = no_touch;
			}
			// condition to check if touch sense occured on left side of my board
			else if((touch_value > TOUCH_SENSE_OFFSET_VAL) && (touch_value < TOUCH_SENSE_MID_VAL))
			{
			    CurrentState = left_touch;
			    left_touch_flag = 1; // turning flag high when left touch is done

			    LOG("Color changes to RED -- Slider Value:%d \n\r",touch_value);

			}
			// condition to check if touch sense occured on right side of my board
			else if(touch_value > TOUCH_SENSE_MID_VAL)
			{
			    CurrentState = right_touch;
			    right_touch_flag = 1; // turning flag high when right touch is done

			    LOG("Color changes to GREEN -- Slider Value:%d \n\r",touch_value);

			}

			led_OFF();
			delay(HUNDRED_MSEC_DELAY);
		}

}
