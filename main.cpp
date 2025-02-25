#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "f73-rncontrol-lib/uart.h"
#include "f73-rncontrol-lib/adc.h"
#include "f73-rncontrol-lib/button.h"
#include "f73-rncontrol-lib/led.h"
#include "f73-rncontrol-lib/counter.h"

#include "can.h"



int main()
{
	// init LED
	ledInit();

	// init Buttons
	buttonInit();

	//init UART 
	uartInit(9600,8,'N',1);

	//CAN init
	can_init(BITRATE_500_KBPS);      // CAN init 500 kbit/s

	can_t resvmsg;          // Message-Objekt auf dem Stack anlegen
   	can_t sendmsg;          // Message-Objekt auf dem Stack anlegen
    sendmsg.id = 0x0F;          // ID setzen, hier: dec
    sendmsg.flags.rtr = 0;      // Remote-Transmission-Request -> aus
    sendmsg.length = 1;         // Länge der Nachricht: 1 Byte
    sendmsg.data[0]=0xff;       // Datenbyte 0 füllen
	
	
	printf("\r\nCAN Send Receive Test\r\n");
	printf("\r\nButton 1 : CAN-Nachricht senden\r\n");
	ledSet(1); // Lebenszeichen

	while (1)
	{
		if(buttonRead()==1)
		{	
			sendmsg.data[0]=0x01;
			can_send_message(&sendmsg);        // CAN-Nachricht versenden
			ledToggle(2); //LED 2 toggeln
		}
		
		if(can_check_message()) // Prüfe, ob Nachricht empfangen wurde.
		{
	
			ledToggle(3);
			can_get_message(&resvmsg);
			printf("CAN_Message mit der ID 0x%x DLC 0x%x Data: ", resvmsg.id,resvmsg.length);	// Zeichenkette erzeugen und in dn Zwischenspeicher schreiben
			
			for(uint8_t i=0;i<resvmsg.length;i++)
			{
			printf("0x%x ", resvmsg.data[i]);
			
			}
			printf("empfangen \n\r ");	// Zeichenkette erzeugen und in dn Zwischenspeicher schreiben
			
	    }

	}
	return 0;
}
