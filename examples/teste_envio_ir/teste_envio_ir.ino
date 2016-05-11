/*
 * IRremote: IRsendRawDemo - demonstrates sending IR codes with sendRaw
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 *
 * IRsendRawDemo - added by AnalysIR (via www.AnalysIR.com), 24 August 2015
 *
 * This example shows how to send a RAW signal using the IRremote library.
 * The example signal is actually a 32 bit NEC signal.
 * Remote Control button: LGTV Power On/Off. 
 * Hex Value: 0x20DF10EF, 32 bits
 * 
 * It is more efficient to use the sendNEC function to send NEC signals. 
 * Use of sendRaw here, serves only as an example of using the function.
 * 
 */


#include <IRremote.h>

IRsend irsend;

void setup()
{

}

void loop() {
  int khz = 38; // 38kHz carrier frequency for the NEC protocol

unsigned int  rawData2[115] = {5050,2050, 450,1700, 450,600, 450,650, 400,650, 450,1700, 400,650, 450,650, 400,650, 400,650, 450,1700, 450,600, 450,1700, 450,1700, 400,650, 450,1700, 400,1750, 400,1700, 450,1700, 450,1700, 400,650, 450,1700, 400,650, 450,650, 400,650, 400,650, 450,650, 400,650, 450,1700, 400,1700, 450,650, 400,650, 450,650, 400,650, 400,650, 450,1700, 400,650, 450,650, 400,650, 450,600, 450,650, 400,650, 450,600, 450,650, 400,650, 450,650, 400,650, 400,650, 450,650, 400,650, 450,1700, 400,1700, 450,1700, 450,1700, 400,650, 450,650, 400,650, 400};  // UNKNOWN 8F414434
unsigned int  rawData3[115] = {5050,2100, 400,1700, 450,650, 400,650, 450,650, 400,1700, 450,650, 400,650, 450,600, 450,650, 400,1700, 450,650, 400,1750, 400,1700, 450,650, 400,1700, 450,1700, 450,1700, 400,1700, 450,1700, 450,650, 400,1700, 450,650, 400,650, 450,600, 450,650, 400,650, 450,600, 450,1700, 450,1700, 400,650, 450,650, 400,650, 400,650, 450,650, 400,1700, 450,650, 400,650, 450,600, 450,650, 400,650, 450,650, 400,650, 450,600, 450,650, 400,650, 450,600, 450,650, 400,650, 450,600, 450,1700, 450,1700, 400,1750, 400,1700, 450,650, 400,650, 450,600, 450};  // UNKNOWN 8F414434
unsigned int  rawData4[115] = {5100,2050, 400,1750, 400,650, 450,600, 450,650, 400,1700, 450,650, 400,650, 450,600, 450,650, 400,1750, 400,650, 400,1750, 400,1700, 450,650, 400,1700, 450,1700, 450,1700, 400,1750, 400,1700, 450,650, 400,1700, 450,650, 400,650, 450,600, 450,650, 400,650, 450,650, 400,1700, 450,1700, 450,600, 450,650, 400,650, 450,600, 450,650, 400,1700, 450,650, 400,650, 450,650, 400,650, 450,600, 450,650, 400,650, 450,600, 450,650, 400,650, 450,600, 450,650, 400,650, 450,600, 450,1700, 450,1700, 400,1750, 400,1700, 450,650, 400,650, 450,600, 450};

  irsend.sendRaw(rawData2, sizeof(rawData2) / sizeof(rawData2[0]), khz); //Note the approach used to automatically calculate the size of the array.
  delay(2000);
  irsend.sendRaw(rawData3, sizeof(rawData3) / sizeof(rawData3[0]), khz);
  delay(2000);
  irsend.sendRaw(rawData4, sizeof(rawData4) / sizeof(rawData4[0]), khz);
 delay(2000);

}
