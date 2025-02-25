#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "f73-rncontrol-lib/uart.h"
#include "f73-rncontrol-lib/adc.h"
#include "f73-rncontrol-lib/button.h"
#include "f73-rncontrol-lib/led.h"
#include "f73-rncontrol-lib/counter.h"

#include "can.h"
#include "rfid.h"

// UID S50 Mifare 1K Chip auslesen
uint8_t mfrc522_get_card_serial(uint8_t *serial_out)
{

	uint8_t status;
	uint8_t i;
	uint8_t serNumCheck = 0;
	uint32_t unLen;

	mfrc522_write(BitFramingReg, 0x00); // TxLastBists = BitFramingReg[2..0]

	serial_out[0] = PICC_ANTICOLL;
	serial_out[1] = 0x20;
	status = mfrc522_to_card(Transceive_CMD, serial_out, 2, serial_out, &unLen);

	if (status == CARD_FOUND)
	{
		// Check card serial number
		for (i = 0; i < 4; i++)
		{
			serNumCheck ^= serial_out[i];
		}
		if (serNumCheck != serial_out[i])
		{
			status = ERROR;
		}
	}
	return status;
}

int main()
{
	// init LED
	ledInit();

	// init Buttons
	buttonInit();

	// init UART
	uartInit(9600, 8, 'N', 1);

	// CAN init
	can_init(BITRATE_500_KBPS); // CAN init 500 kbit/s

	can_t resvmsg;			// Message-Objekt auf dem Stack anlegen
	can_t sendmsg;			// Message-Objekt auf dem Stack anlegen
	sendmsg.id = 0x0F;		// ID setzen, hier: dec
	sendmsg.flags.rtr = 0;	// Remote-Transmission-Request -> aus
	sendmsg.length = 1;		// Länge der Nachricht: 1 Byte
	sendmsg.data[0] = 0xff; // Datenbyte 0 füllen

	// RFID init
	mfrc522_init(); // RC522 initialisieren

	uint8_t status = 0;	  // Statusbyte RFID Reader
	uint8_t str[MAX_LEN]; // Datenarray für ein Sektor (16 Byte)  (MIFARE S50)

	printf("\r\nCAN Send Receive and RFID Test\r\n");
	printf("\r\nButton 1 : CAN-Nachricht senden\r\n");
	ledSet(1); // Lebenszeichen

	status = mfrc522_read(VersionReg); // Prüfen, ob Reader erreichbar und auslesen der Version 1.0 oder 2.0
	if (status == 0x92)				   // Prüfen, ob Reader gefunden Versionsnummer 0x92
	{
		printf("Version: 0x%x   READER FOUND", status); // Zeichenkette erzeugen und in dn Zwischenspeicher schreiben
		// Versionsnummer ausgeben
	}
	else // sonst Fehlermeldung ausgeben
	{
		printf("Version: 0x%x   READER NOT FOUND", status); // Zeichenkette erzeugen und in dn Zwischenspeicher schreiben
															// Versionsnummer ausgeben
	}
	printf("\n\r"); // Neue Zeile

	while (1)
	{
		if (buttonRead() == 1)
		{
			sendmsg.data[0] = 0x01;
			can_send_message(&sendmsg); // CAN-Nachricht versenden
			ledToggle(2);				// LED 2 toggeln
		}

		if (can_check_message()) // Prüfe, ob Nachricht empfangen wurde.
		{

			ledToggle(3);
			can_get_message(&resvmsg);
			printf("CAN_Message mit der ID 0x%x DLC 0x%x Data: ", resvmsg.id, resvmsg.length); // Zeichenkette erzeugen und in dn Zwischenspeicher schreiben

			for (uint8_t i = 0; i < resvmsg.length; i++)
			{
				printf("0x%x ", resvmsg.data[i]);
			}
			printf("empfangen \n\r "); // Zeichenkette erzeugen und in dn Zwischenspeicher schreiben
		}

		status = mfrc522_request(PICC_REQALL, str); // Prüfe, ob ein Tag in der nähe ist

		if (status == CARD_FOUND)
		{
			printf("CARD FOUND  \n\r  ");

			if (str[0] == 0x04)
			{
				printf("Mifare_One_S50 FOUND   ");
				printf("TagType: 0x%x%x ", str[0], str[1]); // Versionsnummer ausgeben
				uint8_t UID_Status = mfrc522_get_card_serial(str);
				printf("UID: 0x%x%x%x%x \n\r \n\r ", str[0], str[1], str[2], str[3]); // UID Seriennummer ausgeben
			}
		}
		_delay_ms(50);
	}
	return 0;
}
