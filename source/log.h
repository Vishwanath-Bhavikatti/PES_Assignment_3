/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
 * @Credits : I took this snippet from Lecture slide "PES 10 KL25Z and GPIO pt2.pdf"
​ ​*​ ​@date​ :February 21, 2023
 * @file name : log.h
 * @file_description: This function basically does the operation of printf function only
 *                    in DEBUG mode.
 *
*************************************************************************************************************************
*/
#ifndef LOG_H_
#define LOG_H_

#include<stdio.h>

#ifdef DEBUG
#  define LOG printf
#else
#  define LOG(...)
#endif

#endif /* LOG_H_ */
