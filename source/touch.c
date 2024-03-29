/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
 * @Credits : https://github.com/alexander-g-dean/ESF/blob/master/NXP/Misc/Touch%20Sense/TSI/src/main.c
​ ​*​ ​@date​ :February 19, 2023
 * @file name : touch.c
 * @file_description: It consists of MKL25Z4.h a default header file of the KL25Z board.
 *                     Along with I have included delay.h and touch.h whose function prototypes are being used in this file.
 * 					   This file includes Touch Initialization and Touch_scan_LH value function
 * 					   which initializes TSI module and scans touch value
 *
*************************************************************************************************************************
*/
#include "touch.h"
#include "delay.h"
#include "MKL25Z4.h"
#define TOUCH_OFFSET 550  // offset value to be subtracted
#define TOUCH_DATA (TSI0->DATA & 0xFFFF)//macro for extracting the count from data register

/*
 * @Function
 *     This function initializes TSI module
 */
void Touch_Init()
{
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK; // enabling the clock


	TSI0->GENCS = TSI_GENCS_MODE(0u) | //operating in non-noise mode
				  TSI_GENCS_REFCHRG(0u) | //reference oscillator charge and discharge value 500nA
				  TSI_GENCS_DVOLT(0u) | //oscillator voltage rails set to default
				  TSI_GENCS_EXTCHRG(0u) | //electrode oscillator charge and discharge value 500nA
				  TSI_GENCS_PS(0u) |  // frequency clock divided by one
				  TSI_GENCS_NSCN(31u) | //scanning the electrode 32 times
				  TSI_GENCS_TSIEN_MASK | //enabling the TSI module
				  TSI_GENCS_EOSF_MASK; // writing one to clear the end of scan flag

}
/*
 * @Function
 *     This function scans the touch sense and returns sense value as an integer
 *     return: integer scan value
 */
int Touch_Scan_LH(void)
{
	unsigned int scan = 0;
	TSI0->DATA = 	TSI_DATA_TSICH(10u);
	TSI0->DATA |= TSI_DATA_SWTS_MASK; //software trigger to start the scan
	while (!(TSI0->GENCS & TSI_GENCS_EOSF_MASK )) // waiting for the scan to complete 32 times
	;
	scan = TOUCH_DATA;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK ; //writing one to clear the end of scan flag

	return scan- TOUCH_OFFSET;
}

