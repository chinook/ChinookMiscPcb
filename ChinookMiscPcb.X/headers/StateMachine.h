//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : StateMachine.h
// Author  : Frederic Chasse
// Date    : 2015-02-25
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This is the header file for the state machine of the system.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : State names can and should be renamed by the user to improve the
//           readability of the code.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#ifndef __STATE_MACHINE_H__
#define	__STATE_MACHINE_H__

#include "Setup.h"
#include "StateFunctions.h"


//==============================================================================
// State Machine public function prototypes
//==============================================================================
void StateInit      (void);   // Initialization state of the system
void StateAcq       (void);   // First state. User can rename it as needed
void State2         (void);   // Second state. User can rename it as needed
void StateError     (void);   // Error state. User should assess and corret errors in this state
void StateScheduler (void);   // State Scheduler. Decides which state is next
                              // depending on current state and flags. Used as a function


//==============================================================================
// Macro definitions
//==============================================================================

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// State scheduler flags
// The state scheduler is at the end of each state and
// decides which state is next. Following flags
// are used in this decision. The names used can and
// should be renamed to improve readability. Also, the
// conditions tested in the defines should be changed
// to proper tests
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#define INIT_2_ACQ     breakFlag                // StateInit to StateAcq
#define INIT_2_ERROR   errorFlag                // StateInit to StateError
#define INIT_2_TWO    !breakFlag                // StateInit to State2

#define ACQ_2_TWO     !breakFlag                // StateAcq to State2
#define ACQ_2_ACQ      breakFlag                // StateAcq to StateAcq
#define ACQ_2_ERROR   !breakFlag && errorFlag   // StateAcq to StateError

#define TWO_2_ACQ      breakFlag                // State2 to StateAcq
#define TWO_2_TWO     !breakFlag                // State2 to State2
#define TWO_2_ERROR    breakFlag && errorFlag   // State2 to StateError

#define ERROR_2_ACQ   !errorFlag && breakFlag   // StateError to StateAcq
#define ERROR_2_TWO   !errorFlag && !breakFlag  // StateError to State2
#define ERROR_2_ERROR  errorFlag                // StateError to StateError
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//==============================================================================
// Variable declarations
//==============================================================================
void (*pState)(void);       // State pointer, used to navigate between states
volatile  INT8  breakFlag   // Flag indicating if the emergency break has been pressed
               ,errorFlag   // Flag indicating an error
               ;

// Typedef for mapping the steering wheel switches and the buttons on the board
// All the buttons used : 3 on the steering wheel, 3 on the board
typedef union
{
  struct
  {
    UINT8  steerWheelSw1  : 1
          ,steerWheelSw3  : 1
          ,steerWheelSw10 : 1
          ,boardSw1       : 1
          ,boardSw2       : 1
          ,boardSw3       : 1
          ,               : 2
          ;
  } bits;

  UINT8 byte;

} Buttons_t;

typedef union
{
  struct
  {
    UINT8  steerWheelSw1  : 1
          ,steerWheelSw3  : 1
          ,steerWheelSw10 : 1
          ,boardSw1       : 1
          ,boardSw2       : 1
          ,boardSw3       : 1
          ,               : 2
          ;
  } bits;

  UINT8 byte;

} Chng_t;

typedef struct sButtonStates
{
  Buttons_t buttons;
  Chng_t    chng;
} sButtonStates_t;

#endif	/* __STATE_MACHINE_H__ */

