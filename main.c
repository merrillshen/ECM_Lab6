// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "rc_servo.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void){
    LATDbits.LATD5=0;   //set initial output state
    TRISDbits.TRISD5=0;
    
    Interrupts_init();
    Timer0_init();

    int count = 0;
    unsigned int increasing = 1;        
    
    while(1){
		//write your code to call angle2PWM() to set the servo angle

        while (increasing == 1) {           
            angle2PWM(count);
            count += 1;
            __delay_ms(50);
            if (count == 90) {increasing=0;}
        }
        
        while (increasing == 0) {
            angle2PWM(count);
            count -= 1;
            __delay_ms(50);
            if (count == -90) {increasing=1;}
        }
    }
}
