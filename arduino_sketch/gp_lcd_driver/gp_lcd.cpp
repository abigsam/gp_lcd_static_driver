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

#include "gp_lcd.h"

using namespace gpLCDconstants;

//Constructor
//gp_lcd::gp_lcd(uint8_t csbPin):
//     _csbPin(csbPin)
//{
//    //SPI.begin();
//    //SPI.setBitOrder(LSBFIRST);
//    //pinMode(_csbPin, OUTPUT);
//    //digitalWrite(_csbPin, HIGH);
//}

//
void gp_lcd::begin(uint8_t csbPin) {
    _csbPin = csbPin;
    SPI.begin();
    SPI.setBitOrder(LSBFIRST);
    pinMode(_csbPin, OUTPUT);
    digitalWrite(_csbPin, HIGH);
}

//Flush all configured digits
void gp_lcd::flush() {
    digitalWrite(_csbPin, LOW);
    for (uint8_t i = 0u; i < DIGITS_NUMBER; ++i) {
        if (_digitEn[i])
            SPI.transfer(_digitVal[i]);
        else
            SPI.transfer((~DIGIT_VALUE_MASK & _digitVal[i]) | DISABLE_DIGIT_MASK);
    }
    digitalWrite(_csbPin, HIGH);
}

//
void gp_lcd::setDigit(uint8_t value, uint8_t position, bool immediately) {
    uint8_t temp = 0u;
    if (position < DIGITS_NUMBER) {
        temp = _digitVal[position] & ~DIGIT_VALUE_MASK;
        _digitVal[position] = temp | (value & DIGIT_VALUE_MASK);
    }
    if (immediately) {
        flush();
    }
}

//
void gp_lcd::configDigit(gpLCDdigits type, uint8_t position, bool immediately) {
    if (position < DIGITS_NUMBER) {
        if (DISABLE_DIGIT == type || ENABLE_DIGIT == type)
            _digitEn[position] = (ENABLE_DIGIT == type) ? true : false;
        else if (DISABLE_SEMICOLON == type) {
            if (position != LOWBAT_SIGN_POSITION && position != PLUS_SIGN_POSITION) {
                _digitVal[position] &= ~SEMICOLON_MASK;
            }
        }
        else if (ENABLE_SEMICOLON == type) {
            if (position != LOWBAT_SIGN_POSITION && position != PLUS_SIGN_POSITION) {
                _digitVal[position] |= SEMICOLON_MASK;
            }
        }
        else if (DISABLE_DECIMAL == type) {
            if (position != PLUS_SIGN_POSITION) {
                _digitVal[position] &= ~DECIMAL_POINT_MASK;
            }
        }
        else if (ENABLE_DECIMAL == type) {
            if (position != PLUS_SIGN_POSITION) {
                _digitVal[position] |= DECIMAL_POINT_MASK;
            }
        }
    }
    if (immediately) {
        flush();
    }
}

//
void gp_lcd::setSigns(gpLCDsigns type, bool immediately) {
    if (DISABLE_NUMBER_SIGN == type)
        { _digitVal[PLUS_SIGN_POSITION] &= ~PLUS_SIGN_MASK; }
    else if (ENABLE_MINUS == type) {
        _digitVal[PLUS_SIGN_POSITION] &= ~PLUS_SIGN_MASK;
        _digitVal[PLUS_SIGN_POSITION] = MINUS_SIGN_MASK;
    }
    else if (ENABLE_PLUS == type)
        { _digitVal[PLUS_SIGN_POSITION] |= PLUS_SIGN_MASK; }
    else if (DISABLE_LOWBAT == type)
        { _digitVal[LOWBAT_SIGN_POSITION] &= ~LOWBAT_SIGN_MASK; }
    else if (ENABLE_LOWBAT == type)
        { _digitVal[LOWBAT_SIGN_POSITION] |= LOWBAT_SIGN_MASK; }
    if (immediately) {
        flush();
    }
}

//
void gp_lcd::disableAll(bool immediately) {
    for (uint8_t i = 0u; i < DIGITS_NUMBER; ++i) {
        _digitEn[i] = false;
        _digitVal[i] &= ~(DECIMAL_POINT_MASK | SEMICOLON_MASK);
    }
    if (immediately) {
        flush();
    }
}
