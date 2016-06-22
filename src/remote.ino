#include <IRremoteESP8266.h>

IRsend irsend(D1); //an IR emitter led is connected to GPIO pin 4

void remote_setup(){
  irsend.begin();
}


int khz = 38; // 38kHz carrier frequency for the NEC protocol
unsigned int  rawData2[359] = {5112, 2080, 436, 1720, 436, 644, 436, 644, 436, 640, 440, 1716, 440, 644, 432, 644, 432, 644, 436, 644, 436, 1716, 444, 640, 436, 1716, 440, 1720, 440, 640, 436, 1716, 444, 1716, 436, 1720, 440, 1716, 440, 1716, 440, 640, 440, 1720, 436, 640, 440, 640, 432, 648, 432, 644, 436, 640, 440, 640, 440, 1716, 440, 1716, 436, 648, 432, 644, 436, 640, 440, 640, 436, 644, 436, 1716, 440, 644, 432, 644, 436, 644, 436, 640, 440, 640, 436, 644, 436, 644, 432, 648, 432, 640, 436, 644, 436, 644, 436, 640, 440, 640, 436, 644, 436, 1716, 440, 1720, 436, 1716, 444, 1716, 436, 648, 432, 640, 440, 640, 436, 29312, 5108, 2076, 440, 1720, 440, 640, 436, 644, 436, 640, 436, 1720, 440, 640, 436, 644, 436, 640, 440, 640, 432, 1724, 436, 640, 440, 1716, 440, 1720, 440, 640, 432, 1720, 440, 1720, 436, 1720, 440, 1716, 440, 1716, 440, 640, 436, 1724, 436, 640, 440, 640, 436, 644, 432, 648, 432, 640, 440, 640, 436, 1720, 440, 1716, 440, 640, 436, 644, 436, 640, 440, 640, 440, 640, 440, 640, 432, 644, 436, 640, 436, 644, 436, 644, 436, 640, 440, 1716, 440, 1716, 436, 644, 436, 644, 436, 1716, 444, 640, 436, 1716, 440, 644, 432, 648, 432, 640, 440, 640, 436, 644, 436, 644, 436, 640, 440, 640, 432, 648, 432, 1720, 440, 640, 436, 644, 436, 644, 436, 640, 440, 1716, 436, 644, 436, 640, 440, 640, 436, 644, 436, 644, 432, 644, 436, 644, 432, 644, 436, 644, 436, 640, 440, 640, 440, 640, 432, 648, 432, 644, 436, 644, 432, 644, 436, 640, 440, 640, 440, 640, 436, 644, 436, 1716, 440, 1720, 436, 1720, 436, 644, 436, 640, 440, 640, 432, 648, 432, 1720, 440, 1720, 436, 644, 436, 1716, 436, 648, 432, 1720, 440, 640, 436, 644, 436, 640, 440, 640, 440, 640, 432, 648, 432, 644, 436, 640, 440, 640, 440, 640, 436, 640, 436, 644, 432, 648, 432, 644, 436, 1716, 440, 644, 436, 644, 436, 640, 436, 644, 436, 644, 432, 644, 436, 640, 440, 1716, 440, 644, 436, 640, 436};  // UNKNOWN 8F414434


void remote_sendCommand(byte temp, byte fan)
{
	/*
	00 10001000        17
	01 01011011        218
	02 11101000        23
	03 00011000        24
	04 00000000        0
	05 11001010        83
	06 00000000        0
	07 10000100        33
	08 00000000        0
	09 00000000        0
	10 0TTTTTTT        0  <- Temp
	11 T1101FFF        22 <- Fan
	12 FFFFF000        0
	13 00000100        32
	14 CCCCCCCC        0  <- Checksum
	*/
	byte adjustedTemp = temp - 9;
	byte header[7] = { 17, 218, 23, 24, 4, 0, 30 };
	byte body[15] = { 17, 218, 23, 24, 0, 83, 0, 33, 0, 0, 0, 22, 0, 32, 0 };

	// Temp
	bitWrite(body[10], 1, bitRead(adjustedTemp, 0));
	bitWrite(body[10], 2, bitRead(adjustedTemp, 1));
	bitWrite(body[10], 3, bitRead(adjustedTemp, 2));
	bitWrite(body[10], 4, bitRead(adjustedTemp, 3));
	bitWrite(body[10], 5, bitRead(adjustedTemp, 4));
	bitWrite(body[10], 6, bitRead(adjustedTemp, 5));
	bitWrite(body[10], 7, bitRead(adjustedTemp, 6));
	bitWrite(body[11], 0, bitRead(adjustedTemp, 7));

	// Fan
	bitWrite(body[11], 5, bitRead(fan, 0));
	bitWrite(body[11], 6, bitRead(fan, 1));
	bitWrite(body[11], 7, bitRead(fan, 2));
	bitWrite(body[12], 0, bitRead(fan, 3));
	bitWrite(body[12], 1, bitRead(fan, 4));
	bitWrite(body[12], 2, bitRead(fan, 5));
	bitWrite(body[12], 3, bitRead(fan, 6));
	bitWrite(body[12], 4, bitRead(fan, 7));

	// Checksum
	for (int i = 0; i < 14; i++)
	{
		body[14] += body[i];
	}

	int currentCommandPosition = 0;
	unsigned int irCommand[359];

	// HEADER
	irCommand[currentCommandPosition++] = 5108;
	irCommand[currentCommandPosition++] = 2080;
	irCommand[currentCommandPosition++] = 440;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (bitRead(header[i], j))
			{
				irCommand[currentCommandPosition++] = 1720;
			}
			else
			{
				irCommand[currentCommandPosition++] = 640;
			}

			irCommand[currentCommandPosition++] = 440;
		}
	}

	// PAUSE
	irCommand[currentCommandPosition++] = 29000;

	// BODY
	irCommand[currentCommandPosition++] = 5108;
	irCommand[currentCommandPosition++] = 2080;
	irCommand[currentCommandPosition++] = 440;

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (bitRead(body[i], j))
			{
				irCommand[currentCommandPosition++] = 1720;
			}
			else
			{
				irCommand[currentCommandPosition++] = 640;
			}

			irCommand[currentCommandPosition++] = 440;
		}
	}
  irsend.sendRaw(irCommand,sizeof(irCommand) / sizeof(irCommand[0]), khz);
}
