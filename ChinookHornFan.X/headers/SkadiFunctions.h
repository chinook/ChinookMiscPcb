//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : HeaderTemplate.h
// Author  : Frederic Chasse
// Date    : 2015-01-03
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This header file gathers the functions used for Skadi.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : Function names can and should be renamed by the user to improve the
//           readability of the code.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#ifndef __SKADI_FUNCTIONS__
#define	__SKADI_FUNCTIONS__

#include "Setup.h"


//==============================================================================
// Public functions prototypes
//==============================================================================

/**************************************************************
 * Function name  : LedDebug
 * Purpose        : Toggle LED_DEBUG.
 * Arguments      : None.
 * Returns        : None.
 *************************************************************/
void LedDebug();

/**************************************************************
 * Function name  : LedCan
 * Purpose        : Toggle LED_CAN.
 * Arguments      : None.
 * Returns        : None.
 *************************************************************/
void LedCan();

/**************************************************************
 * Function name  : ReInitSystem
 * Purpose        : Redo StateInit().
 * Arguments      : None.
 * Returns        : None.
 *************************************************************/
void ReInitSystem();


//==============================================================================
// Macro definitions
//==============================================================================


//==============================================================================
// Variable declarations
//==============================================================================
//
///***********************************
// * Table of functions used in Skadi
// **********************************/
//sSkadiCommand_t skadiCommandTable[] =
//{
//   {"LedDebug"    , LedDebug    , 1, "Usage : flash Led DEBUG"}   // 1 argument
//  ,{"LedCan"      , LedCan      , 1, "Usage : flash Led CAN"}     // 1 argument
//  ,{"ReInitSystem", ReInitSystem, 0, "Redo StateInit()"}          // 0 argument
//};
//
///***************************************************
// * Length of the table of functions used in Skadi
// **************************************************/
//const size_t lengthSkadiCommandTable = 3;


#endif	/* __SKADI_FUNCTIONS__ */

