/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
 * @Credits : Referred Embedded_Systems_Fundamentals by Dean, chapter 2
​ ​*​ ​@date​ :February 19, 2023
 * @file name : led.h
 * @file_description:
 * 		This file includes LED Initialization, Blinking individual LEDs and turning off LEDs and
 * 		initial LED pattern function prototypes.
 *
*************************************************************************************************************************
*/
#ifndef LED_H_
#define LED_H_

void led_blink_init();
void led_WHITE_ON();
void led_BLUE_ON();
void led_GREEN_ON();
void led_RED_ON();
void led_OFF();
void init_led_pattern();

#endif /* LED_H_ */
