[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10080197&assignment_repo_type=AssignmentRepo)
# Course: Principle of Embedded Software - ECEN 5813 (Spring 2023)
# Assignment 3
## Author : Vishwanath Bhavikatti (vishwanathbhavikatti1310@gmail.com)
## Date : 2/22/2023

# Description: 
In this assignment I am doing bare-metal C executable program for ChristmasLights that runs on the KL25Z. 

## Compiler Used:
`gcc (with -WALL and -WERROR Flags enabled)`
## IDE and Development board
<br> IDE: MCUXpresso IDE 11.6.1
<br> Development Board: MKL25Z

## Implementation Details:
1)	At program startup, ChristmasLights will “test” the LED by blinking in the following pattern:
<br> WHITE for 500 msec, OFF for 100 msec, 
<br> BLUE for 500 msec, OFF for 100 msec,
<br> WHITE for 500 msec, OFF for 100 msec
<br> BLUE for 500 msec, OFF for 100 msec

2)	ChristmasLights will then enter an infinite loop where the LED will be flashed using the following pattern:
<br> RED ON for 500 msec, OFF for 500 msec, 
<br> GREEN ON for 1000 msec, OFF for 500 msec,
<br> RED ON for 2000 msec, OFF for 500 msec,
<br> GREEN ON for 3000 msec, OFF for 500 msec
<br> Go back to the top (e.g., RED ON for 500 msec…)

3)	During the infinite loop, when the LED is RED and GREEN, if the user touches the capacitive touch slider, the color will change as follows:
<br> `User touches	        Color`
<br> `Left side of slider	Red`
<br> `Right side of slider	Green`
<br> The blinking timing and sequence will be similar to earlier step 2) except that it will use only one color Red or Green depending on the slider touch. You can decide the end you consider as Left vs Right.
The ChristmasLights code should poll the touch slider at least once every 100 msec. If the LED is on when a touch is detected, the light color should change immediately.

4)	This code for now has one build targets, DEBUG. the DEBUG target will additionally cause the following debug output (via printf) to a serial console:
<br>	CHANGE LED TO RED, etc. for changes to the LED color
<br>	SLIDER VALUE 87 for changes to the slider value including showing the value read 
<br>	START TIMER 3000 for starting a delay 3000 msec delay. 


## Source Files Included:
<br>Logic Functions
<br> main.c
<br> led.c
<br> led.h
<br> touch.c
<br> touch.h
<br> delay.c
<br> delay.h
<br> touch_blink_pattern.c
<br> touch_blink_pattern.h

### Inbuilt Functions
<br> mtb.c
<br> semihost_hardfault.c

### Special Instructions while testing on KL25Z dev board.
<br> For my development board I checked the 100ms delay using stop watch and found it to be 600000 iterations in while loop inside delay function (Its approximated).
<br> In my case I am using exactly the same code for touch_sense initialisation and Touch_sense_LH function from Dean's git repo. https://github.com/alexander-g-dean/ESF/blob/master/NXP/Misc/Touch%20Sense/TSI/src/main.c
<br> Inside touch.c I am defining TOUCH_OFFSET as 550. I didnot edit this. However in my touch_blink.c file I defined TOUCH_SENSE_OFFSET_VALUE as 29 (for my board) and also defined TOUCH_SENSE_MID_VALUE as 275 (approximate value from repetative trial). 
## Name of the reviewer
Aamir Suhail Burhan
## Review Date:
2/21/2023
## Review Comments:
1. Comment: The macro defined for 100msec delay is called DELAY. Maybe it can be renamed to a more readable macro name like HUNDRED_MSEC_DELAY to make the code more readable.
    - Response: Yes, it makes complete sense. I implemented the change.
2. Comment:In touch_blink_pattern() function, while checking for right functionality it is better to keep a check for higher limit. As your touch_value is of unsigned integer type, if a negative value near -1 is used after calibration it can go to max value which is 0xFFFF.
    - Response: As I have defined one more touch offset value in addition to the code taken from Dean's git link so I think its not necessary atleast for this assignment.
3. Comment:Goto statements to exit from a switch case would generally not be recommended. Using only break statements would be a better way to control the flow of the program.
    - Response: I agree with the reviewer and I used other logic.
4. Comment:Once a touch is detected, the code does not continue with the specified timing pattern based on touch input. It rather restarts the pattern based on your touch input. You will need to change your logic for this.
    - Response: I appreciate reviewer here, as my understanding was wrong. Done the changes for recently pushed code.
5. Comment:The pattern should display red or green after a touch is detected with the specified timing pattern. The code written displays red for 500ms, 2000ms and green for 1000ms, 3000ms. It should rather display red for 500, 1000,2000 and 3000 provided that there is a red touch detected.
    - Response: I got confused actually and based on reviewer comment I changed it.
6. Comment:Code elegance can be improved in the touch_blink_pattern.c file to make it more readable.
    - Response: I tried to do my best withing the given time.


## Extra Credit:
#### Question 1: Starting address of main() and totaly bytes of memory used by delay() function.
<br> Starting Address of main() function : `0000225E` in Hexadecimal
<br> Number of Bytes taken by Delay function: `30 ` Bytes starting from Address `00002240` hex to `0000225C` hex.
<br> How to view this address :
<br> Windows --> Show view --> other --> DEBUG --> Disassembly



#### Question 2: Disassembly of delay() Function:

<br>          `delay:`             //This line defines a function named "delay". It is start of delay subroutine
<br> //This instruction saves the values of register r7 (the frame pointer) and the link register lr on the stack. This is done to preserve their values across function calls.
<br> `00002240:   push    {r7, lr}`  
<br> //This instruction decrements the stack pointer (sp) by 8 bytes. This is done to allocate space on the stack for local variables.
<br> `00002242:   sub     sp, #8 `
<br> //This instruction sets the base pointer (r7) to the current value of the stack pointer (sp). This establishes a new stack frame for the function.
<br> `00002244:   add     r7, sp, #0`
<br> //This instruction stores the first argument passed to the function in register r0 at an offset of 4 bytes from the base pointer (r7).
<br> `00002246:   str     r0, [r7, #4]`
<br> //This line indicates the start of a loop that decrements the "iteration" variable until it reaches zero.
<br> `21        	while(iteration--)`
<br> //This is a no-op instruction that does nothing.
<br> `00002248:   nop     ; (mov r8, r8)`
<br> //This instruction loads the value of the "iteration" variable from memory into register r3.
<br> `0000224a:   ldr     r3, [r7, #4]`
<br> //This instruction subtracts 1 from the value in r3 and stores the result in r2.
<br> `0000224c:   subs    r2, r3, #1`
<br> //This instruction stores the updated value of the "iteration" variable in memory at an offset of 4 bytes from the base pointer.
<br> `0000224e:   str     r2, [r7, #4]`
<br> //This instruction compares the value in r3 to zero.
<br> `00002250:   cmp     r3, #0`
<br> //If the value in r3 is not equal to zero, this instruction jumps back to the start of the loop (at address 0000224a).
<br> `00002252:   bne.n   0x224a <delay+10>`
<br> `23        }` // End of the while loop.
<br> // Two no-op instructions that do nothing.
<br>` 00002254:   nop     ; (mov r8, r8)`
<br> `00002256:   nop     ; (mov r8, r8)`
<br> //This instruction restores the stack pointer to its original value by setting it to the value of the base pointer (r7).
<br> `00002258:   mov     sp, r7`
<br> //This instruction increments the stack pointer by 8 bytes to deallocate the space used by local variables.
<br> `0000225a:   add     sp, #8`
<br> //This instruction restores the values of the frame pointer (r7) and the program counter (pc) from the stack, effectively returning control to the calling function.
<br> `0000225c:   pop     {r7, pc}`
