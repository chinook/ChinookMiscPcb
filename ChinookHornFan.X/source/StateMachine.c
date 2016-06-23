//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : StateMachine.c
// Author  : Frederic Chasse
// Date    : 2015-02-25
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This is the C file for the state machine of the system.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : State names can and should be renamed by the user to improve the
//           readability of the code.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include "..\headers\StateMachine.h"


//==============================================================================
//	STATES OF STATE MACHINE
//==============================================================================

//===============================================================
// Name     : StateScheduler
// Purpose  : Decides which state is next depending on current
//            state and flags. Used as a function
//===============================================================
void StateScheduler(void)
{
  // Clear WDT
  //============================
  Wdt.Clear();
  //============================

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state == StateInit
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  if (pState == &StateInit)
  {
    if (INIT_2_ACQ)
    {
      pState = &StateAcq;       // First state
    }
    else if (INIT_2_TWO)
    {
      pState = &State2;       // Second state
    }
    else if (INIT_2_ERROR)
    {
      pState = &StateError;   // Error state
    }
    else
    {
      pState = &StateError;   // Go to Error state by default
    }
  }
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state == StateAcq
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  else if (pState == &StateAcq)
  {
    if (ACQ_2_ACQ)
    {
      pState = &StateAcq;       // First state
    }
    else if (ACQ_2_TWO)
    {
      pState = &State2;       // Second state
    }
    else if (ACQ_2_ERROR)
    {
      pState = &StateError;   // Error state
    }
    else
    {
      pState = &StateError;   // Go to Error state by default
    }
  }
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state == State2
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  else if (pState == &State2)
  {
    if (TWO_2_ACQ)
    {
      pState = &StateAcq;       // First state
    }
    else if (TWO_2_TWO)
    {
      pState = &State2;       // Second state
    }
    else if (TWO_2_ERROR)
    {
      pState = &StateError;   // Error state
    }
    else
    {
      pState = &StateError;   // Go to Error state by default
    }
  }
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state == StateError
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  else if (pState == &StateError)
  {
    if (ERROR_2_ACQ)
    {
      pState = &StateAcq;       // First state
    }
    else if (ERROR_2_TWO)
    {
      pState = &State2;       // Second state
    }
    else if (ERROR_2_ERROR)
    {
      pState = &StateError;   // Error state
    }
    else
    {
      pState = &StateError;   // Go to Error state by default
    }
  }
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state undetermined
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  else
  {
    pState = &StateError;   // Go to Error state by default
  }
  /*
   * DEVELOPPER CODE HERE
   */

}

//===============================================================
// Name     : StateInit
// Purpose  : Initialization of the system.
//===============================================================
void StateInit(void)
{

  INTDisableInterrupts();   // Disable all interrupts of the system.

  INIT_PORTS;
//  INIT_SPI;
  INIT_TIMER;
//  INIT_INPUT_CAPTURE;
  INIT_PWM;
//  INIT_ADC;
//  INIT_UART;
//  INIT_SKADI;
  INIT_CAN;
//  INIT_I2C;
//  INIT_WDT;
  START_INTERRUPTS;

}

//===============================================================
// Name     : State1
// Purpose  : TBD.
//===============================================================
void StateAcq(void)
{
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // FIRST PART OF STATE
  // Developper should add a small description of expected behavior
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // SECOND PART OF STATE
  // Developper should add a small description of expected behavior
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  /*
   * DEVELOPPER CODE HERE
   */
  sUartLineBuffer_t  uart1Data =  {
                                    .buffer = {0}
                                   ,.length =  0
                                  }
                    ,uart2Data =  {
                                    .buffer = {0}
                                   ,.length =  0
                                  }
                    ,uart3Data =  {
                                    .buffer = {0}
                                   ,.length =  0
                                  }
                    ,uart4Data =  {
                                    .buffer = {0}
                                   ,.length =  0
                                  }
                    ,uart5Data =  {
                                    .buffer = {0}
                                   ,.length =  0
                                  }
                    ,uart6Data =  {
                                    .buffer = {0}
                                   ,.length =  0
                                  }
                    ;
  
  INT32 err = 0;
  
//  Skadi.GetCmdMsg();    // Use if you do not use UART interrupts
  
  if (Uart.Var.oIsRxDataAvailable[UART1])                 // Check if RX interrupt occured
  {
      Skadi.GetCmdMsgFifo();                              // Use this line if you use UART interrupts and update the UART used
  }
  
  if (Uart.Var.oIsRxDataAvailable[UART2])                 // Check if RX interrupt occured
  {
    err = Uart.GetRxFifoBuffer(UART2, &uart2Data, FALSE); // put received data in uart2Data
    if (err >= 0)                                         // If no error occured
    {
      /* Do something */
      Uart.PutTxFifoBuffer(UART2, &uart2Data);            // Put data received in TX FIFO buffer
    }
  }
  
  if (Uart.Var.oIsRxDataAvailable[UART3])                 // Check if RX interrupt occured
  {
    err = Uart.GetRxFifoBuffer(UART3, &uart3Data, FALSE); // put received data in uart3Data
    if (err >= 0)                                         // If no error occured
    {
      /* Do something */
      Uart.PutTxFifoBuffer(UART3, &uart3Data);            // Put data received in TX FIFO buffer
    }
  }
  
  if (Uart.Var.oIsRxDataAvailable[UART4])                 // Check if RX interrupt occured
  {
    err = Uart.GetRxFifoBuffer(UART4, &uart4Data, FALSE); // put received data in uart4Data
    if (err >= 0)                                         // If no error occured
    {
      /* Do something */
      Uart.PutTxFifoBuffer(UART4, &uart4Data);            // Put data received in TX FIFO buffer
    }
  }
  
  if (Uart.Var.oIsRxDataAvailable[UART5])                 // Check if RX interrupt occured
  {
    err = Uart.GetRxFifoBuffer(UART5, &uart5Data, FALSE); // put received data in uart5Data
    if (err >= 0)                                         // If no error occured
    {
      /* Do something */
      Uart.PutTxFifoBuffer(UART5, &uart5Data);            // Put data received in TX FIFO buffer
    }
  }
  
  if (Uart.Var.oIsRxDataAvailable[UART6])                 // Check if RX interrupt occured
  {
    err = Uart.GetRxFifoBuffer(UART6, &uart6Data, FALSE); // put received data in uart6Data
    if (err >= 0)                                         // If no error occured
    {
      /* Do something */
      Uart.PutTxFifoBuffer(UART6, &uart6Data);            // Put data received in TX FIFO buffer
    }
  }

}

//===============================================================
// Name     : State2
// Purpose  : TBD.
//===============================================================
void State2(void)
{
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // FIRST PART OF STATE
  // Developper should add a small description of expected behavior
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // SECOND PART OF STATE
  // Developper should add a small description of expected behavior
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  /*
   * DEVELOPPER CODE HERE
   */

}

//===============================================================
// Name     : StateError
// Purpose  : Error state of the system. Used to assess and
//            correct errors in the system.
//===============================================================
void StateError(void)
{
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // VARIABLE DECLARATIONS
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // FIRST PART OF STATE
  // Developper should add a small description of expected behavior
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  /*
   * DEVELOPPER CODE HERE
   */

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // SECOND PART OF STATE
  // Developper should add a small description of expected behavior
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  /*
   * DEVELOPPER CODE HERE
   */

}
