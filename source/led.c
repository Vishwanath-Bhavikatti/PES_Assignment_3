/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
 * @Credits : Referred Embedded_Systems_Fundamentals by Dean, chapter 2
​ ​*​ ​@date​ :February 19, 2023
 * @file name : led.c
 * @file_description: It consists of MKL25Z4.h a default header file of the KL25Z board and
 *                    stdio.h for printf usage. Along with I have included led.h, delay.h and
 *                    touch.h whose function prototypes are being used in this file.
 * This file includes LED Initialization, Blinking individual LEDs and turning off LEDs and
 * initial LED pattern functions.
 *
*************************************************************************************************************************
*/

#include "MKL25Z4.h"
#include <stdio.h>
/* TODO: insert other include files here. */
#include "led.h"
#include "delay.h"
#include "touch.h"
#include "log.h"

/* TODO: insert other definitions and declarations here. */
#define RED_LED_PIN 18     //RED LED Port Pin number
#define GREEN_LED_PIN 19	//GREEN LED Port Pin number
#define BLUE_LED_PIN 1 		//BLUE LED Port Pin number
#define MASK(x) (1UL << (x))  // Masking bits
#define HUNDRED_MSEC_DELAY 600000        //100ms delay

void led_OFF();

volatile uint32_t touch_val = 0 ; // Initializing touch_value to 0


/*
 * @Function
 *     The led_blink_int() will basically initialize the led ports and pins
 *
 *     It turns clock for PORTS of LEDs and defines port bits as output
 */
void led_blink_init()
{
	//Enable clock to PORT B AND PORT D
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

    //select pin MUX mode to GPIO by setting the MUX field to PORTB_PCR18, PORTB_PCR_19 and PORTD_PCR_1 to 001
    //Make 3 pins GPIO
    PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(1);
    PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(1);
    PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;
    PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(1);

    //Define appropriate port bits to be outputs. We will do this by setting bits 18 and 19 in Port
    //B’s PDDR register and bit 1 in Port D’s PDDR:

    PTB->PDDR |= MASK(RED_LED_PIN) | MASK(GREEN_LED_PIN);
    PTD->PDDR |= MASK(BLUE_LED_PIN);

    led_OFF();

}

/*
 * @Function
 *     This function turns White LED ON
 *     PCOR:PORT clear Output register
 *     PSOR:PORT SET Output register
 *
 */
void led_WHITE_ON()
{
	//PCOR defines PORT clear Output register
	PTB->PCOR |= MASK(RED_LED_PIN) | MASK(GREEN_LED_PIN);
	PTD->PCOR |= MASK(BLUE_LED_PIN);

}
/*
 * @Function
 * 	  This function turns BLUE LED ON
 *
 */
void led_BLUE_ON()
{

	PTD->PCOR |= MASK(BLUE_LED_PIN);
	PTB->PSOR |= MASK(RED_LED_PIN);
	PTB->PSOR |= MASK(GREEN_LED_PIN);

}
/*
 * @Function
 *     This function turns RED LED ON
 *
 */
void led_RED_ON()
{
	PTB->PCOR |= MASK(RED_LED_PIN);
	PTB->PSOR |= MASK(GREEN_LED_PIN);
	PTD->PSOR |= MASK(BLUE_LED_PIN);
}
/*
 * @Function
 * This function turns GREEN LED ON
 *
 */
void led_GREEN_ON()
{
	PTB->PSOR |= MASK(RED_LED_PIN);
	PTB->PCOR |= MASK(GREEN_LED_PIN);
	PTD->PSOR |= MASK(BLUE_LED_PIN);
}
/*
 * @Function
 *     This function turns OFF LED
 *
 */
void led_OFF()
{
	PTB->PSOR |= MASK(RED_LED_PIN);
	PTB->PSOR |= MASK(GREEN_LED_PIN);
	PTD->PSOR |= MASK(BLUE_LED_PIN);
}
/*
 * @Function
 *    This function calls initial pattern of LED blinking White and Blue
 *
 */
void init_led_pattern()
{
	int loop = 2; // loop counter
	while(loop--)
	{
		LOG("Start Timer 500ms\n\r");
		LOG("Color changes to WHITE\n\r");


		//Turning ON white led for 500ms
		for(int i = 0;i < 5 ;i++)
		{
			led_WHITE_ON();
			delay(HUNDRED_MSEC_DELAY);
		}

		LOG("Start Timer 100ms\n\r");
		LOG("LEDs OFF\n\r");

		//Turning led off for 100ms
		led_OFF();
		delay(HUNDRED_MSEC_DELAY);

		LOG("Start Timer 500ms\n\r");
		LOG("Color changes to BLUE\n\r");

		//Turning ON Blue led for 500ms
		for(int i = 0;i < 5 ;i++)
		{
			led_BLUE_ON();
			delay(HUNDRED_MSEC_DELAY);
		}

		LOG("Start Timer 100ms\n\r");
		LOG("LEDs OFF\n\r");

		//Turning led off for 100ms
		led_OFF();
		delay(HUNDRED_MSEC_DELAY);
	}

}




