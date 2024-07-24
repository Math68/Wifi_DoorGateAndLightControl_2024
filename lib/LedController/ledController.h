#pragma once

// Led Controller
//
// Independent fonction wich control a LED
// There it will be possible to have nine modes
// OFF, ON, BLINK, FLASH 1,2,3 and the flashing inverse
//
//           _                     _ _     _ _     _ _
//            !                   !   !   !   !   !   !
//            !_ _ _ _ _ _ _ _ _ _!   !_ _!   !_ _!   !_ _
// Operation              0         5   4   3   2   1 
// 
// MaxOperationStep = 0 + 5
// Time laps @0 = trep - (5 x ton)
// Time laps @5, @4, @3, @2, @1 = ton 
//
//
// See below how to use it!!!
//  
// #define GPIO XX
//
// struct LedParam LedRed, *PLedRed=&LedRed;
//
// void setup()
// {
//      pinMode(GPIO, OUTPUT);
//      SetLedParam(PLedRed, FLASH_THREE, 150, 2000);   // Led will flashing three time, flashing as dead time will be 150ms and will repeat all 2s. 
// }
//
// void loop()
// {
//      GPIOController(PLedRed, GPIO);
// }
//

#include <Arduino.h>

#define _ON 0
#define _OFF 1

enum OperationMode {OFF, ON, BLINK, FLASH_ONE, FLASH_TWO, FLASH_THREE, FLASH_ONE_INV, FLASH_TWO_INV, FLASH_THREE_INV};

struct LedParam{
    enum OperationMode Mode;       // Operating mode or RunMode

    char MaxOperationStep;  // Number of operation step 
    bool Init;
    bool Etat;              // Output Stata
    int tOn;                // On Time in ms
    int tRep;               // Repetition Time in ms

    long TimeLapse;
    long PreviousTime;
};

void SetLedParam (struct LedParam *_Led, enum OperationMode _OpMode, int _tOn, int _tRep);
void SetLedMode (struct LedParam *_Led, enum OperationMode _OpMode);
void GPIOController(struct LedParam *_LedParam, int _Broche);
