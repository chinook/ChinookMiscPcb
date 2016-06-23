//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : main.c
// Author  : Frederic Chasse
// Date    : 2015-01-03
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This is the main C file of the template project used by all
//           developpers of Chinook. It uses ChinookLib, which is another
//           repository on Github.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : For ChinookLib to be useable, it must be cloned on your hard
//           drive so the path
//               "..\..\..\ChinookLib\ChinookLib.X\headers\ChinookLib.h"
//           references an existing file.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#include "..\headers\Setup.h"
#include "..\headers\SkadiFunctions.h"
#include "..\headers\Interrupts.h"
#include "..\headers\StateMachine.h"
#include "..\headers\HardwareProfile.h"


//==============================================================================
// FUNCTION PROTOTYPES
//==============================================================================


//==============================================================================
// VARIABLE DECLARATIONS
//==============================================================================


//==============================================================================
// MAIN CODE
//==============================================================================
void main(void)
{

//==============================================================================
// Following memcopies are used to be able to use the form 
// Chinook.LibraryX.FunctionX in case the developper wants to see the available
// functions.
// IMPORTANT NOTE : the variables structures (example : Adc.Var...) WON'T be
//                  updated. Only use Chinook.Lib.Function format for the
//                  functions.
//==============================================================================
  memcpy( &Chinook.Port  , &Port  , sizeof ( struct sChinookPort  ) );
  memcpy( &Chinook.Uart  , &Uart  , sizeof ( struct sChinookUart  ) );
  memcpy( &Chinook.Pwm   , &Pwm   , sizeof ( struct sChinookPwm   ) );
  memcpy( &Chinook.Timer , &Timer , sizeof ( struct sChinookTimer ) );
  memcpy( &Chinook.Spi   , &Port  , sizeof ( struct sChinookSpi   ) );
  memcpy( &Chinook.Wdt   , &Wdt   , sizeof ( struct sChinookWdt   ) );
  memcpy( &Chinook.Adc   , &Adc   , sizeof ( struct sChinookAdc   ) );
  memcpy( &Chinook.Can   , &Can   , sizeof ( struct sChinookCan   ) );
  memcpy( &Chinook.I2c   , &I2c   , sizeof ( struct sChinookI2c   ) );
  memcpy( &Chinook.Skadi , &Skadi , sizeof ( struct sChinookSkadi ) );
  memcpy( &Chinook.InputCapture , &InputCapture , sizeof ( struct sChinookInputCapture ) );
//==============================================================================


//==============================================================================
// The next line disables the JTAG for the PIC. If the JTAG is enabled, pins
// RB10-13 can't be used as I/Os. If you want to use the JTAG, comment or
// remove this line.
//==============================================================================
  DDPCONbits.JTAGEN = 0;
//==============================================================================


//==============================================================================
// Configure the device for maximum performance but do not change the PBDIV
// Given the options, this function will change the flash wait states, RAM
// wait state and enable prefetch cache but will not change the PBDIV.
// The PBDIV value is already set via the pragma FPBDIV option in HardwareProfile.h.
//==============================================================================
  SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
//==============================================================================


// State machine init
//=================================================================
//  if (Wdt.ReadEvent())    // If a system reset has occured
//  {
//    Wdt.Disable();        // Disable WDT and
//    Wdt.ClearEvent();     // the WDT event bit
//    pState = &StateError; // Go to StateError
//  }
//  else
//  {
//    pState = &StateInit;  // Else, initialize the system as usual
//  }
//=================================================================
  
  StateInit();
  
	while(1)  //infinite loop
	{
    if (!SW1)
    {
      Pwm.SetDutyCycle(PWM_3, 250);
      while (!SW1);
      Pwm.SetDutyCycle(PWM_3, 10);
    }
//    else
//    {
//      Pwm.SetDutyCycle(PWM_3, 10);
//      while(SW1);
//    }
    
    if (!SW3)
    {
//      Port.D.SetBits(BIT_3);
//      Timer.DelayMs(100);
      Port.D.ClearBits(BIT_3);
      Timer.DelayMs(50);
      Port.D.SetBits(BIT_3);
//      Timer.DelayMs(100);
//      Port.D.ClearBits(BIT_3);
//      Timer.DelayMs(100);
      
      while (!SW3);
    }
//    else
//    {
//      Port.D.ClearBits(BIT_3);
//    }
    
//  // State machine entry & exit point
//  //===========================================================
//		(*pState)();          // jump to next state
//  //===========================================================
//
//  // State scheduler
//  //===========================================================
//    StateScheduler();     // Decides which state will be next
//	//===========================================================
    
	}
} //END MAIN CODE