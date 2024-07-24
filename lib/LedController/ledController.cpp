
#include "ledController.h"

void SetLedParam (struct LedParam *_Led, enum OperationMode _OpMode, int _tOn, int _tRep)
{
    _Led->Mode=_OpMode;
    _Led->tOn=_tOn;
    _Led->tRep=_tRep;
    _Led->Init=false;
}

void SetLedMode (struct LedParam *_Led, enum OperationMode _OpMode)
{
    if(_OpMode!=_Led->Mode)
    {
        _Led->Mode=_OpMode;
        _Led->MaxOperationStep=0;
    }
}

void GPIOController(struct LedParam *_LedParam, int _Broche)
{  
    if(_LedParam->Init==false)
    {
        _LedParam->Init=true;
        _LedParam->PreviousTime=millis();
        _LedParam->TimeLapse=0;
        _LedParam->Etat=_OFF;
    }
    else
    {
        if((millis()-_LedParam->PreviousTime)>_LedParam->TimeLapse)
        {
            _LedParam->PreviousTime=millis();

            switch (_LedParam->Mode)
            {
                case OFF:
                _LedParam->Etat=_OFF;
                _LedParam->TimeLapse=_LedParam->tRep;
                break;

                case ON:
                _LedParam->Etat=_ON;
                _LedParam->TimeLapse=_LedParam->tRep;
                break;

                case BLINK:
                _LedParam->Etat=!_LedParam->Etat;
                _LedParam->TimeLapse=_LedParam->tRep/2;
                break;

                case FLASH_ONE:
                if(_LedParam->MaxOperationStep==0)
                {
                    _LedParam->TimeLapse=(_LedParam->tRep-_LedParam->tOn);
                    _LedParam->MaxOperationStep=1;
                    _LedParam->Etat=_OFF; // Led OFF
                }
                else
                {
                    _LedParam->TimeLapse=_LedParam->tOn;
                    _LedParam->Etat=!_LedParam->Etat;
                    _LedParam->MaxOperationStep-=1;    
                }
                break;

                case FLASH_TWO:
                if(_LedParam->MaxOperationStep==0)
                {
                    _LedParam->TimeLapse=(_LedParam->tRep-(3*_LedParam->tOn));
                    _LedParam->MaxOperationStep=3;
                    _LedParam->Etat=_OFF; // Led OFF
                }
                else
                {
                    _LedParam->TimeLapse=_LedParam->tOn;
                    _LedParam->Etat=!_LedParam->Etat;
                    _LedParam->MaxOperationStep-=1;    
                }
                break;

                case FLASH_THREE:
                if(_LedParam->MaxOperationStep==0)
                {
                    _LedParam->TimeLapse=(_LedParam->tRep-(5*_LedParam->tOn));;
                    _LedParam->MaxOperationStep=5;
                    _LedParam->Etat=_OFF; // Led OFF
                }
                else
                {
                    _LedParam->TimeLapse=_LedParam->tOn;
                    _LedParam->Etat=!_LedParam->Etat;
                    _LedParam->MaxOperationStep-=1;
                }
                break;

                case FLASH_ONE_INV:
                if(_LedParam->MaxOperationStep==0)
                {
                    _LedParam->TimeLapse=(_LedParam->tRep-_LedParam->tOn);
                    _LedParam->MaxOperationStep=1;
                    _LedParam->Etat=_ON; // Led ON
                }
                else
                {
                    _LedParam->TimeLapse=_LedParam->tOn;
                    _LedParam->Etat=!_LedParam->Etat;
                    _LedParam->MaxOperationStep-=1;    
                }
                break;

                case FLASH_TWO_INV:
                if(_LedParam->MaxOperationStep==0)
                {
                    _LedParam->TimeLapse=(_LedParam->tRep-(3*_LedParam->tOn));
                    _LedParam->MaxOperationStep=3;
                    _LedParam->Etat=_ON; // Led ON
                }
                else
                {
                    _LedParam->TimeLapse=_LedParam->tOn;
                    _LedParam->Etat=!_LedParam->Etat;
                    _LedParam->MaxOperationStep-=1;    
                }
                break;

                case FLASH_THREE_INV:
                if(_LedParam->MaxOperationStep==0)
                {
                    _LedParam->TimeLapse=(_LedParam->tRep-(5*_LedParam->tOn));;
                    _LedParam->MaxOperationStep=5;
                    _LedParam->Etat=_ON; // Led ON
                }
                else
                {
                    _LedParam->TimeLapse=_LedParam->tOn;
                    _LedParam->Etat=!_LedParam->Etat;
                    _LedParam->MaxOperationStep-=1;
                }
                break;
                
                default:
                break;
            }        

            digitalWrite(_Broche, _LedParam->Etat);
        }
    }
}

