/*
Mogamad Saeed Solomon
SLMMOG032
EEE2046F Practical 4
*/

#include "stm32f0xx.h"
#include <lcd_stm32f0.c>

// functions used within the program
void initGPIO(void);
void fdelay(void);
void firstDisplay(void);
void secondDisplay(void);
void thirdDisplay(void);
void checkPB(void);
void display(void);

// QUESTION (b)
#define DELAY1 1000
#define DELAY2 1000

// QUESTION (d)
// global variables to hold LED outputs
uint8_t bitPattern1 = 0x00;         // 0b 0000 0000
uint8_t bitPattern2 = 0xFF;         // 0b 1111 1111
uint8_t bitPattern3 = 0xAA;         // 0b 1010 1010

// pr- processor commands of QUESTION (e)
#define TRUE 1
#define FALSE 0

// QUESTION (f)
typedef uint8_t flag_t;         // new variable type

// QUESTION (g)
// global variables to mark specific flag events in program
flag_t startFlag = FALSE;
flag_t firstFlag = FALSE;
flag_t secondFlag = FALSE;
flag_t thirdFlag = FALSE;

// QUESTION (m)
int main(void) {
    initGPIO();         // call our initializing unctions to prepare out stm board

   while (1) {     // loops forever
     
        checkPB();  // checks which switch
        display();     // calls the display depending on which button was pressed
    }
    return 0;   
}

//QUESTION (a)
 void initGPIO(void) {

    // activate clock for push buttons and LEDs
    RCC ->AHBENR |= (RCC_AHBENR_GPIOAEN) | (RCC_AHBENR_GPIOBEN);

    // enable pull up resistors 
    // set them to 01
    GPIOA -> PUPDR = 0x55;
  
    // initialize switches to input 00
    GPIOA -> MODER &= ~(GPIO_MODER_MODER0 |
                        GPIO_MODER_MODER1 |
                        GPIO_MODER_MODER2 |
                        GPIO_MODER_MODER3 );
    
    // initializes LEDs to output 01
    GPIOB -> MODER = 0x5555;        // sets to 0b 0001 0101 0101 0101

    // initialize LEDs to OFF
    GPIOB -> ODR = 0;
}   

void fdelay(void) {

    for (volatile int i=0; i<DELAY1; i++) {
        for (volatile int j=0; j<DELAY2; j++) {
            // do nothing
        }
    }
}

// QUESTION (h)
void firstDisplay(void) {

    // loops forever 
    while (1) {
        GPIOB -> ODR = bitPattern1;
        fdelay();        // delays for 1s before implementing next pattern

        GPIOB -> ODR = bitPattern2;
        fdelay();

        GPIOB -> ODR = bitPattern3;
        fdelay();
    }
}

// QUESTION (i)
void secondDisplay(void) {

    // loops forever
    while (1) {
    
        GPIOB -> ODR = 0b00000001;
        fdelay();
        GPIOB -> ODR = 0b00000010;
        fdelay();
        GPIOB -> ODR = 0b00000100;
        fdelay();
        GPIOB -> ODR = 0b00001000;
        fdelay();
        GPIOB -> ODR = 0b00010000;
        fdelay();
        GPIOB -> ODR = 0b00100000;
        fdelay();
        GPIOB -> ODR = 0b01000000;
        fdelay();
        GPIOB -> ODR = 0b10000000;
        fdelay();
    }
}

// QUESTION (j)
void thirdDisplay(void) {

    uint8_t k = 0;

    // loops forever
    while (1) {
        GPIOB -> ODR = k;             // displays binary value using LEDs
        fdelay();
        k ++;               // increment k

        // when our k reaches maximum number of 8 bit binary it resets k
        if (k == 255) {
            k = 0;
        }
    }
}

// QUESTION (k)
void checkPB(void) {

    // checks which switch was pressed
    if ((GPIOA -> IDR & GPIO_IDR_0) == 0) {
        // SW0
        startFlag = TRUE;
        firstFlag = FALSE;
        secondFlag = FALSE; 
        thirdFlag = FALSE;
    }
    else if ((GPIOA -> IDR & GPIO_IDR_1) == 0) {
        // SW1
        startFlag = TRUE; 
        firstFlag = TRUE; 
        secondFlag = FALSE; 
        thirdFlag = FALSE;
    }
    else if ((GPIOA -> IDR & GPIO_IDR_2) == 0) {
        // SW2
        startFlag = TRUE; 
        firstFlag = FALSE; 
        secondFlag = TRUE; 
        thirdFlag = FALSE;
    }
    else if ((GPIOA -> IDR & GPIO_IDR_3) == 0) {
        // SW3
        startFlag = TRUE; 
        firstFlag = FALSE; 
        secondFlag = FALSE; 
        thirdFlag = TRUE;
    }
}

// QUESTION (l)
void display(void) {

    if (startFlag == TRUE && firstFlag == FALSE && secondFlag == FALSE && thirdFlag == FALSE) 
        GPIOB -> ODR = 1;           // only turns on LED 0

    if (firstFlag == TRUE ) firstDisplay();

    if (secondFlag == TRUE) secondDisplay(); 

    if (thirdFlag == TRUE) thirdDisplay();
     
}