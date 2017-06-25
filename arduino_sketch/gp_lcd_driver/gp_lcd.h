//==============================================================================================
//
//          GreenPAK4 static LCD driver
//
//==============================================================================================
//  Author:         abigsam@gmail.com (AR)
//  Project Name:   gp_lcd
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

#ifndef GP_LCD_H
#define GP_LCD_H

#include "Arduino.h"
#include <SPI.h>

enum gpLCDsigns {
    DISABLE_NUMBER_SIGN = 0u,
    ENABLE_MINUS,
    ENABLE_PLUS,
    DISABLE_LOWBAT,
    ENABLE_LOWBAT
};

enum gpLCDdigits {
    DISABLE_DIGIT = 0u,
    DISABLE_SEMICOLON,
    DISABLE_DECIMAL,
    ENABLE_DIGIT,
    ENABLE_SEMICOLON,
    ENABLE_DECIMAL
};

namespace gpLCDconstants {
    const uint8_t DIGITS_NUMBER = 5u;
    const uint8_t DIGIT_VALUE_MASK = 0xf;
    const uint8_t DISABLE_DIGIT_MASK = 0x0c;
    const uint8_t DECIMAL_POINT_MASK = 0x10;
    const uint8_t SEMICOLON_MASK = 0x20;
    //
    const uint8_t LOWBAT_SIGN_MASK = 0x20;      //Connected to "semicolon" bit
    const uint8_t LOWBAT_SIGN_POSITION = 4u;    //Position "Lowbat" sign
    const uint8_t MINUS_SIGN_MASK = 0x10;       //Connected to "decimal point" bit
    const uint8_t PLUS_SIGN_MASK = 0x30;        //Connected to "decimal point" and "semicolon" bits
    const uint8_t PLUS_SIGN_POSITION = 0u;      //Position sign
}

class gp_lcd {
    public:
        //Configure CSB pin, configure SPI module
        //gp_lcd(uint8_t csbPin);
        void begin(uint8_t csbPin);
        
        //Drive digits, semicolons & decimal points
        void setDigit(uint8_t value, uint8_t position, bool immediately = true);
        void configDigit(gpLCDdigits type, uint8_t position, bool immediately = true);
        
        //Drive special signs
        void setSigns(gpLCDsigns type, bool immediately = true);
        
        //Disable all signs
        void disableAll(bool immediately = true);
        
        //Flush all data to the driver
        void flush();
        
    //private: //Methods
        
    private: // Members
        uint8_t _csbPin;
        uint8_t _digitVal[gpLCDconstants::DIGITS_NUMBER]= {0};
        bool _digitEn[gpLCDconstants::DIGITS_NUMBER]= {false};
};

#endif
