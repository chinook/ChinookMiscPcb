//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : SourceTemplate.c
// Author  : Frederic Chasse
// Date    : 2015-01-03
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This C file gathers the functions used for Skadi.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : Function names can and should be renamed by the user to improve the
//           readability of the code. User must set the functions here and adjust
//           the structure skadiCommandTable located in Setup.c.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include "..\headers\SkadiFunctions.h"


//==============================================================================
// Private functions prototypes
//==============================================================================


//==============================================================================
// Variable definitions
//==============================================================================


//==============================================================================
// Functions
//==============================================================================

/**************************************************************
 * Function name  : LedDebug
 * Purpose        : Toggle LedDebug depending on the arguments
 * Arguments      : Received from Skadi functions
 * Returns        : None.
 *************************************************************/
void LedDebug(sSkadi_t *skadi, sSkadiArgs_t args)
{
  UINT8 errorMsg[] = {"Cette led n'existe pas!\r\n"};

  int led = atoi(args.elements[0]);   // Convert argument to int

  if (led == 1)
  {
#ifdef __32MX795F512L__
    Port.A.ToggleBits(BIT_3);
#elif defined __32MX795F512H__
    Port.B.ToggleBits(BIT_12);
#endif
  }
  else
  {
    Uart.SendDataBuffer(UART1, errorMsg, sizeof(errorMsg));
  }
}


/**************************************************************
 * Function name  : LedCan
 * Purpose        : Toggle LedCan depending on the arguments
 * Arguments      : Received from Skadi functions
 * Returns        : None.
 *************************************************************/
void LedCan(sSkadi_t *skadi, sSkadiArgs_t args)
{
  UINT8 errorMsg[] = {"Cette led n'existe pas!\r\n"};

  int led = atoi(args.elements[0]);   // Convert argument to int

  if (led == 2)
  {
#ifdef __32MX795F512L__
    Port.C.ToggleBits(BIT_1);
#elif defined __32MX795F512H__
    Port.B.ToggleBits(BIT_13);
#endif
  }
  else
  {
    Uart.SendDataBuffer(UART1, errorMsg, sizeof(errorMsg));
  }
}


/**************************************************************
 * Function name  : ReInitSystem
 * Purpose        : Redo StateInit()
 * Arguments      : Received from Skadi functions
 * Returns        : None.
 *************************************************************/
void ReInitSystem(sSkadi_t *skadi, sSkadiArgs_t args)
{
  StateInit();
}