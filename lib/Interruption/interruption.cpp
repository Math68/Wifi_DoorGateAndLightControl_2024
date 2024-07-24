#include "interruption.h"

ISR_Events ISR_Event;

void IRAM_ATTR ISR_DoorG1Moved(){
    ISR_Event=DOORG1DEBOUNCE;
}

void IRAM_ATTR ISR_DoorG2Moved(){
    ISR_Event=DOORG2DEBOUNCE;
}

void IRAM_ATTR ISR_DayStateChanged(){
    ISR_Event=DAYSTATECHANGED;
}

void IRAM_ATTR ISR_GateMoved(){
    ISR_Event=GATEDEBOUNCE;
}
