//==============================================================================================
//
//          GreenPAK4 static LCD driver
//
//==============================================================================================
//  Author:         abigsam@gmail.com (AR)
//  Project Name:   gp_lcd_static_driver
//  GitHub:         https://github.com/abigsam/gp_lcd_static_driver
//  CircuitMaker:   https://workspace.circuitmaker.com/Projects/Details/Andrey-Rachek/gplcdstaticdriver
//==============================================================================================
//  Description:
//  ===
//  Driver for static 7-segment 4.5 digits LCD with GreenPAK4. Driver connected via SPI to the
//  Arduino. SPI connected as foloows:
//  SCK	     --> digital pin 13
//  MOSI     --> digital pin 11
//  CSB(SS)	 --> digital pin 7
//  
//  For driving LCD used 5 GreenPAK4-s (GP) connected in chain. Each GP control one digit plus 
//  decimal point % semicolon (if implemented).
//  Each GP contain 8 bits for control LCD digit (write via SPI LSB first):
//  * bit 7: not used;
//  * bit 6: not used;
//  * bit 5: if it '1' semicolon is enabled (if implemented);
//  * bit 4: if it '1' decimal point is enabled (if implemented);
//  * bit 3-0: digit from 0...9; if it eq. or more than 12 all segments are disabled.
//  In CircuitMaker project LCD used ITH-E0811GRNPITH-E0811GRNP, datasheet see in CircuitMaker
//  project attachments. For this LCD each GP drive:
//  * GP5 (send first): drive first (from right) digit; bit 4 drive MINUS sign, bit 5 drive
//    PLUS sign;
//  * GP4: drive second digit; bit 4 drive decimal point; semicolon is not implemented;
//  * GP3: drive third digit; bit 4 drive decimal point; bit 5 drive semicolon;
//  * GP2: drive fourth digit; bit 4 drive decimal point; bit 5 drive semicolon;
//  * GP1: drive fifth digit (can display only "1"); bit 4 drive decimal point; bit 5 drive
//    "Low Battery" sign.
// 
//  This software using as folows:
//  
// 
//
//==============================================================================================
// Reision history:
// ===
// 12.06.2017   v0.0.01 [AR]    -- File created
// 
// 
// 
//==============================================================================================
// TODO:
// ===
// 
// 
// 
// 
// 
//==============================================================================================



#include <SPI.h>
#include "gp_lcd.h"

//const int chipSelectPin = 7;
//const byte DISABLE_DIGIT = 0x0c;

gp_lcd LCD;//(7);
int cnt = 0;
const int DELAY_MS = 100;

//
void setup() {
  LCD.begin(7);
  LCD.disableAll();
}

//
void loop() {
  for (uint8_t i = 0; i < gpLCDconstants::DIGITS_NUMBER; ++i) {
      LCD.configDigit(ENABLE_DECIMAL, i);
      delay(DELAY_MS);
      LCD.configDigit(ENABLE_SEMICOLON, i);
      delay(DELAY_MS);
  }
  //delay(500);
  LCD.setSigns(ENABLE_MINUS);
  delay(DELAY_MS);
  LCD.setSigns(ENABLE_PLUS);
  delay(DELAY_MS);
  LCD.setSigns(ENABLE_LOWBAT);
  delay(DELAY_MS);
  //
  for (uint8_t i = 0; i < gpLCDconstants::DIGITS_NUMBER; ++i) {
      LCD.configDigit(ENABLE_DIGIT, i, false);
      LCD.setDigit(cnt, i);
      //if (cnt < 9) ++cnt;
      //else cnt = 0u;
      delay(DELAY_MS);
  }

  if (cnt < 9) ++cnt;
  else cnt = 0u;
  
  delay(2000);
  
  for (uint8_t i = 0; i < gpLCDconstants::DIGITS_NUMBER; ++i) {
      LCD.configDigit(DISABLE_DECIMAL, i);
      delay(DELAY_MS);
      LCD.configDigit(DISABLE_SEMICOLON, i);
      delay(DELAY_MS);
  }
  //delay(500);
  LCD.setSigns(DISABLE_NUMBER_SIGN);
  delay(DELAY_MS);
  LCD.setSigns(DISABLE_LOWBAT);
  delay(DELAY_MS);
  //
  for (uint8_t i = 0; i < gpLCDconstants::DIGITS_NUMBER; ++i) {
      LCD.configDigit(DISABLE_DIGIT, i);
      delay(DELAY_MS);
  }
}

