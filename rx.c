/* Example of code that is compiled to run from RAM, pushed to RAM, then run from there. */

#include "ch32fun.h"
#include "isler.h"
#include <stdio.h>

#define LED               PA9
#define LL_TX_POWER_0_DBM 0x12

void blink(int n) {
	for(int i = n-1; i >= 0; i--) {
		funDigitalWrite( LED, FUN_LOW ); // Turn on LED
		Delay_Ms(33);
		funDigitalWrite( LED, FUN_HIGH ); // Turn off LED
		if(i) Delay_Ms(33);
	}
}

int main()
{
	SystemInit();

	funGpioInitAll();
	funPinMode( LED, GPIO_CFGLR_OUT_2Mhz_PP );

	BLECoreInit(LL_TX_POWER_0_DBM);
	uint8_t frame_info[] = {0xff, 0x10}; // PDU, len

	blink(5);
	printf("~ ch570 rx !\n");

	Frame_RX(frame_info, 37);
	while(1);
}
