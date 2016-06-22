//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : Interrupts.c
// Author  : Frederic Chasse
// Date    : 2015-01-03
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This file declares all interrupt subroutines used.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : All priorities must be set and verified by the developper. All
//           priorities and subpriorities used are there as example. Also, note
//           that interrupt can be defined as iplnauto, iplnsrs and iplnsoft,
//           where n can be from 0 to 7. 7 is the highest priority, while 1 is
//           the lowest. A priority of 0 will disable the interrupt.
//           Subpriorities can go from (lowest to highest) 0 to 3.
//           SRS mode uses the shadow registers, soft uses the software
//           registers and auto is an automatic assignment.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include "..\headers\Interrupts.h"


/*******************************************************************************
 ***********************                               *************************
 ********************           TIMER INTERRUPTS          **********************
 ***********************                               *************************
 ******************************************************************************/

//=============================================
// Configure the Timer 1 interrupt handler
//=============================================
void __ISR(_TIMER_1_VECTOR, T1_INTERRUPT_PRIORITY) Timer1InterruptHandler(void)
{
  /*
   * DEVELOPPER CODE HERE
   */
  
  // Increment the number of overflows from this timer. Used primarily by Input Capture
  Timer.Var.nOverflows[0]++;
  
  mT1ClearIntFlag();
}

//=============================================
// Configure the Timer 2 interrupt handler
//=============================================
void __ISR(_TIMER_2_VECTOR, T2_INTERRUPT_PRIORITY) Timer2InterruptHandler(void)
{
  /*
   * DEVELOPPER CODE HERE
   */

  // Increment the number of overflows from this timer. Used primarily by Input Capture
  Timer.Var.nOverflows[1]++;

  mT2ClearIntFlag();
}

//=============================================
// Configure the Timer 3 interrupt handler
//=============================================
void __ISR(_TIMER_3_VECTOR, T3_INTERRUPT_PRIORITY) Timer3InterruptHandler(void)
{
  /*
   * DEVELOPPER CODE HERE
   */

  // Increment the number of overflows from this timer. Used primarily by Input Capture
  Timer.Var.nOverflows[2]++;

  mT3ClearIntFlag();
}

//=============================================
// Configure the Timer 4 interrupt handler
//=============================================
void __ISR(_TIMER_4_VECTOR, T4_INTERRUPT_PRIORITY) Timer4InterruptHandler(void)
{
  /*
   * DEVELOPPER CODE HERE
   */

  // Increment the number of overflows from this timer. Used primarily by Input Capture
  Timer.Var.nOverflows[3]++;

  mT4ClearIntFlag();
}

//=============================================
// Configure the Timer 5 interrupt handler
//=============================================
void __ISR(_TIMER_5_VECTOR, T5_INTERRUPT_PRIORITY) Timer5InterruptHandler(void)
{
  /*
   * DEVELOPPER CODE HERE
   */

  // Increment the number of overflows from this timer. Used primarily by Input Capture
  Timer.Var.nOverflows[4]++;

  mT5ClearIntFlag();
}


/*******************************************************************************
 ***********************                               *************************
 ********************           UART INTERRUPTS           **********************
 ***********************                               *************************
 *******************************************************************************/

//=============================================
// Configure the UART 1 interrupt handler
//=============================================

void __ISR(_UART_1_VECTOR, U1_INTERRUPT_PRIORITY) Uart1InterruptHandler(void)
{
  UINT8  i
        ,iMax   // Read/write max 8 bytes/interrupt
        ,data   // used in UartFifoWrite/Read functions
        ;

	// TX interrupt handling
  //===========================================================

  if ( INTGetEnable ( INT_SOURCE_UART_TX(UART1) ) )               // If TX interrupts enabled
  {
    if ( INTGetFlag ( INT_SOURCE_UART_TX(UART1) ) )               // If TX interrupt occured
    {
      if ( UARTTransmitterIsReady(UART1) && !Uart.Var.uartTxFifo[UART1].bufEmpty )  // If TX buffer is ready to receive data and the user's TX buffer is not empty
      {
        if (Uart.Var.uartTxFifo[UART1].lineBuffer.length < 8)     // Write max 8 bytes/interrupt
        {
          iMax = Uart.Var.uartTxFifo[UART1].lineBuffer.length;
        }
        else
        {
          iMax = 8;
        }

        for (i = 0; i < iMax; i++)
        {
          UartFifoRead((void *) &Uart.Var.uartTxFifo[UART1], &data);  // Copy from user
          U1TXREG = data;                                         // Put data in PIC32's TX buffer
        }
      }

      if (Uart.Var.uartTxFifo[UART1].bufEmpty)                    // If User's TX buffer is empty
      {
        Uart.DisableTxInterrupts(UART1);                          // Disable TX interrupts
      }

      INTClearFlag(INT_SOURCE_UART_TX(UART1));                    // Clear the TX interrupt Flag
    }
  }
  //===========================================================
  

	// RX interrupt handling
  //===========================================================
  if ( INTGetEnable ( INT_SOURCE_UART_RX(UART1) ) )               // If RX interrupts enabled
  {
    if ( INTGetFlag ( INT_SOURCE_UART_RX(UART1) ) )               // If RX interrupt occured
    {
      i = 0;
      iMax = 8;                                                   // Read max 8 bytes/interrupt
      while (   UARTReceivedDataIsAvailable(UART1)                // While RX data available
            && !Uart.Var.uartRxFifo[UART1].bufFull                // and user's RX buffer not full
            && (i < iMax)                                         // and under 8 bytes read
            )
      { // while ^
        data = UARTGetDataByte(UART1);                            // Get data for PIC32's RX FIFO buffer and copy it to user (next line)
        if ( UartFifoWrite((void *) &Uart.Var.uartRxFifo[UART1], &data) < 0 ) // If copy to user did not work
        {
          break;                                                  // Exit while loop
        }
        i++;
      } // end while

      if (!Uart.Var.uartRxFifo[UART1].bufEmpty)                   // If there is data in the user's RX buffer
      {
        Uart.Var.oIsRxDataAvailable[UART1] = 1;                   // Set according flag
      }

      INTClearFlag (INT_SOURCE_UART_RX(UART1) );                  // Clear the RX interrupt Flag

    }
	}
  //===========================================================
}
//=============================================

//=============================================
// Configure the UART 2 interrupt handler
//=============================================

void __ISR(_UART_2_VECTOR, U2_INTERRUPT_PRIORITY) Uart2InterruptHandler(void)
{
  UINT8  i
        ,iMax   // Read/write max 8 bytes/interrupt
        ,data   // used in UartFifoWrite/Read functions
        ;

	// TX interrupt handling
  //===========================================================

  if ( INTGetEnable ( INT_SOURCE_UART_TX(UART2) ) )               // If TX interrupts enabled
  {
    if ( INTGetFlag ( INT_SOURCE_UART_TX(UART2) ) )               // If TX interrupt occured
    {
      if ( UARTTransmitterIsReady(UART2) && !Uart.Var.uartTxFifo[UART2].bufEmpty )  // If TX buffer is ready to receive data and the user's TX buffer is not empty
      {
        if (Uart.Var.uartTxFifo[UART2].lineBuffer.length < 8)     // Write max 8 bytes/interrupt
        {
          iMax = Uart.Var.uartTxFifo[UART2].lineBuffer.length;
        }
        else
        {
          iMax = 8;
        }

        for (i = 0; i < iMax; i++)
        {
          UartFifoRead((void *) &Uart.Var.uartTxFifo[UART2], &data);  // Copy from user
          U2TXREG = data;                                         // Put data in PIC32's TX buffer
        }
      }

      if (Uart.Var.uartTxFifo[UART2].bufEmpty)                    // If User's TX buffer is empty
      {
        Uart.DisableTxInterrupts(UART2);                          // Disable TX interrupts
      }

      INTClearFlag(INT_SOURCE_UART_TX(UART2));                    // Clear the TX interrupt Flag
    }
  }
  //===========================================================
  

	// RX interrupt handling
  //===========================================================
  if ( INTGetEnable ( INT_SOURCE_UART_RX(UART2) ) )               // If RX interrupts enabled
  {
    if ( INTGetFlag ( INT_SOURCE_UART_RX(UART2) ) )               // If RX interrupt occured
    {
      i = 0;
      iMax = 8;                                                   // Read max 8 bytes/interrupt
      while (   UARTReceivedDataIsAvailable(UART2)                // While RX data available
            && !Uart.Var.uartRxFifo[UART2].bufFull                // and user's RX buffer not full
            && (i < iMax)                                         // and under 8 bytes read
            )
      { // while ^
        data = UARTGetDataByte(UART2);                            // Get data for PIC32's RX FIFO buffer and copy it to user (next line)
        if ( UartFifoWrite((void *) &Uart.Var.uartRxFifo[UART2], &data) < 0 ) // If copy to user did not work
        {
          break;                                                  // Exit while loop
        }
        i++;
      } // end while

      if (!Uart.Var.uartRxFifo[UART2].bufEmpty)                   // If there is data in the user's RX buffer
      {
        Uart.Var.oIsRxDataAvailable[UART2] = 1;                   // Set according flag
      }

      INTClearFlag (INT_SOURCE_UART_RX(UART2) );                  // Clear the RX interrupt Flag

    }
	}
  //===========================================================
}
//=============================================

//=============================================
// Configure the UART 3 interrupt handler
//=============================================

//void __ISR(_UART_3_VECTOR, U3_INTERRUPT_PRIORITY) Uart3InterruptHandler(void)
//{
//  UINT8  i
//        ,iMax   // Read/write max 8 bytes/interrupt
//        ,data   // used in UartFifoWrite/Read functions
//        ;
//
//	// TX interrupt handling
//  //===========================================================
//
//  if ( INTGetEnable ( INT_SOURCE_UART_TX(UART3) ) )               // If TX interrupts enabled
//  {
//    if ( INTGetFlag ( INT_SOURCE_UART_TX(UART3) ) )               // If TX interrupt occured
//    {
//      if ( UARTTransmitterIsReady(UART3) && !Uart.Var.uartTxFifo[UART3].bufEmpty )  // If TX buffer is ready to receive data and the user's TX buffer is not empty
//      {
//        if (Uart.Var.uartTxFifo[UART3].lineBuffer.length < 8)     // Write max 8 bytes/interrupt
//        {
//          iMax = Uart.Var.uartTxFifo[UART3].lineBuffer.length;
//        }
//        else
//        {
//          iMax = 8;
//        }
//
//        for (i = 0; i < iMax; i++)
//        {
//          UartFifoRead((void *) &Uart.Var.uartTxFifo[UART3], &data);  // Copy from user
//          U3TXREG = data;                                         // Put data in PIC32's TX buffer
//        }
//      }
//
//      if (Uart.Var.uartTxFifo[UART3].bufEmpty)                    // If User's TX buffer is empty
//      {
//        Uart.DisableTxInterrupts(UART3);                          // Disable TX interrupts
//      }
//
//      INTClearFlag(INT_SOURCE_UART_TX(UART3));                    // Clear the TX interrupt Flag
//    }
//  }
//  //===========================================================
//  
//
//	// RX interrupt handling
//  //===========================================================
//  if ( INTGetEnable ( INT_SOURCE_UART_RX(UART3) ) )               // If RX interrupts enabled
//  {
//    if ( INTGetFlag ( INT_SOURCE_UART_RX(UART3) ) )               // If RX interrupt occured
//    {
//      i = 0;
//      iMax = 8;                                                   // Read max 8 bytes/interrupt
//      while (   UARTReceivedDataIsAvailable(UART3)                // While RX data available
//            && !Uart.Var.uartRxFifo[UART3].bufFull                // and user's RX buffer not full
//            && (i < iMax)                                         // and under 8 bytes read
//            )
//      { // while ^
//        data = UARTGetDataByte(UART3);                            // Get data for PIC32's RX FIFO buffer and copy it to user (next line)
//        if ( UartFifoWrite((void *) &Uart.Var.uartRxFifo[UART3], &data) < 0 ) // If copy to user did not work
//        {
//          break;                                                  // Exit while loop
//        }
//        i++;
//      } // end while
//
//      if (!Uart.Var.uartRxFifo[UART3].bufEmpty)                   // If there is data in the user's RX buffer
//      {
//        Uart.Var.oIsRxDataAvailable[UART3] = 1;                   // Set according flag
//      }
//
//      INTClearFlag (INT_SOURCE_UART_RX(UART3) );                  // Clear the RX interrupt Flag
//
//    }
//	}
//  //===========================================================
//}
//=============================================

//=============================================
// Configure the UART 4 interrupt handler
//=============================================

void __ISR(_UART_4_VECTOR, U4_INTERRUPT_PRIORITY) Uart4InterruptHandler(void)
{
  UINT8  i
        ,iMax   // Read/write max 8 bytes/interrupt
        ,data   // used in UartFifoWrite/Read functions
        ;

	// TX interrupt handling
  //===========================================================

  if ( INTGetEnable ( INT_SOURCE_UART_TX(UART4) ) )               // If TX interrupts enabled
  {
    if ( INTGetFlag ( INT_SOURCE_UART_TX(UART4) ) )               // If TX interrupt occured
    {
      if ( UARTTransmitterIsReady(UART4) && !Uart.Var.uartTxFifo[UART4].bufEmpty )  // If TX buffer is ready to receive data and the user's TX buffer is not empty
      {
        if (Uart.Var.uartTxFifo[UART4].lineBuffer.length < 8)     // Write max 8 bytes/interrupt
        {
          iMax = Uart.Var.uartTxFifo[UART4].lineBuffer.length;
        }
        else
        {
          iMax = 8;
        }

        for (i = 0; i < iMax; i++)
        {
          UartFifoRead((void *) &Uart.Var.uartTxFifo[UART4], &data);  // Copy from user
          U4TXREG = data;                                         // Put data in PIC32's TX buffer
        }
      }

      if (Uart.Var.uartTxFifo[UART4].bufEmpty)                    // If User's TX buffer is empty
      {
        Uart.DisableTxInterrupts(UART4);                          // Disable TX interrupts
      }

      INTClearFlag(INT_SOURCE_UART_TX(UART4));                    // Clear the TX interrupt Flag
    }
  }
  //===========================================================
  

	// RX interrupt handling
  //===========================================================
  if ( INTGetEnable ( INT_SOURCE_UART_RX(UART4) ) )               // If RX interrupts enabled
  {
    if ( INTGetFlag ( INT_SOURCE_UART_RX(UART4) ) )               // If RX interrupt occured
    {
      i = 0;
      iMax = 8;                                                   // Read max 8 bytes/interrupt
      while (   UARTReceivedDataIsAvailable(UART4)                // While RX data available
            && !Uart.Var.uartRxFifo[UART4].bufFull                // and user's RX buffer not full
            && (i < iMax)                                         // and under 8 bytes read
            )
      { // while ^
        data = UARTGetDataByte(UART4);                            // Get data for PIC32's RX FIFO buffer and copy it to user (next line)
        if ( UartFifoWrite((void *) &Uart.Var.uartRxFifo[UART4], &data) < 0 ) // If copy to user did not work
        {
          break;                                                  // Exit while loop
        }
        i++;
      } // end while

      if (!Uart.Var.uartRxFifo[UART4].bufEmpty)                   // If there is data in the user's RX buffer
      {
        Uart.Var.oIsRxDataAvailable[UART4] = 1;                   // Set according flag
      }

      INTClearFlag (INT_SOURCE_UART_RX(UART4) );                  // Clear the RX interrupt Flag

    }
	}
  //===========================================================
}
//=============================================

//=============================================
// Configure the UART 5 interrupt handler
//=============================================

void __ISR(_UART_5_VECTOR, U5_INTERRUPT_PRIORITY) Uart5InterruptHandler(void)
{
  UINT8  i
        ,iMax   // Read/write max 8 bytes/interrupt
        ,data   // used in UartFifoWrite/Read functions
        ;

	// TX interrupt handling
  //===========================================================

  if ( INTGetEnable ( INT_SOURCE_UART_TX(UART5) ) )               // If TX interrupts enabled
  {
    if ( INTGetFlag ( INT_SOURCE_UART_TX(UART5) ) )               // If TX interrupt occured
    {
      if ( UARTTransmitterIsReady(UART5) && !Uart.Var.uartTxFifo[UART5].bufEmpty )  // If TX buffer is ready to receive data and the user's TX buffer is not empty
      {
        if (Uart.Var.uartTxFifo[UART5].lineBuffer.length < 8)     // Write max 8 bytes/interrupt
        {
          iMax = Uart.Var.uartTxFifo[UART5].lineBuffer.length;
        }
        else
        {
          iMax = 8;
        }

        for (i = 0; i < iMax; i++)
        {
          UartFifoRead((void *) &Uart.Var.uartTxFifo[UART5], &data);  // Copy from user
          U5TXREG = data;                                         // Put data in PIC32's TX buffer
        }
      }

      if (Uart.Var.uartTxFifo[UART5].bufEmpty)                    // If User's TX buffer is empty
      {
        Uart.DisableTxInterrupts(UART5);                          // Disable TX interrupts
      }

      INTClearFlag(INT_SOURCE_UART_TX(UART5));                    // Clear the TX interrupt Flag
    }
  }
  //===========================================================
  

	// RX interrupt handling
  //===========================================================
  if ( INTGetEnable ( INT_SOURCE_UART_RX(UART5) ) )               // If RX interrupts enabled
  {
    if ( INTGetFlag ( INT_SOURCE_UART_RX(UART5) ) )               // If RX interrupt occured
    {
      i = 0;
      iMax = 8;                                                   // Read max 8 bytes/interrupt
      while (   UARTReceivedDataIsAvailable(UART5)                // While RX data available
            && !Uart.Var.uartRxFifo[UART5].bufFull                // and user's RX buffer not full
            && (i < iMax)                                         // and under 8 bytes read
            )
      { // while ^
        data = UARTGetDataByte(UART5);                            // Get data for PIC32's RX FIFO buffer and copy it to user (next line)
        if ( UartFifoWrite((void *) &Uart.Var.uartRxFifo[UART5], &data) < 0 ) // If copy to user did not work
        {
          break;                                                  // Exit while loop
        }
        i++;
      } // end while

      if (!Uart.Var.uartRxFifo[UART5].bufEmpty)                   // If there is data in the user's RX buffer
      {
        Uart.Var.oIsRxDataAvailable[UART5] = 1;                   // Set according flag
      }

      INTClearFlag (INT_SOURCE_UART_RX(UART5) );                  // Clear the RX interrupt Flag

    }
	}
  //===========================================================
}
//=============================================

//=============================================
// Configure the UART 6 interrupt handler
//=============================================

void __ISR(_UART_6_VECTOR, U6_INTERRUPT_PRIORITY) Uart6InterruptHandler(void)
{
  UINT8  i
        ,iMax   // Read/write max 8 bytes/interrupt
        ,data   // used in UartFifoWrite/Read functions
        ;

	// TX interrupt handling
  //===========================================================

  if ( INTGetEnable ( INT_SOURCE_UART_TX(UART6) ) )               // If TX interrupts enabled
  {
    if ( INTGetFlag ( INT_SOURCE_UART_TX(UART6) ) )               // If TX interrupt occured
    {
      if ( UARTTransmitterIsReady(UART6) && !Uart.Var.uartTxFifo[UART6].bufEmpty )  // If TX buffer is ready to receive data and the user's TX buffer is not empty
      {
        if (Uart.Var.uartTxFifo[UART6].lineBuffer.length < 8)     // Write max 8 bytes/interrupt
        {
          iMax = Uart.Var.uartTxFifo[UART6].lineBuffer.length;
        }
        else
        {
          iMax = 8;
        }

        for (i = 0; i < iMax; i++)
        {
          UartFifoRead((void *) &Uart.Var.uartTxFifo[UART6], &data);  // Copy from user
          U6TXREG = data;                                         // Put data in PIC32's TX buffer
        }
      }

      if (Uart.Var.uartTxFifo[UART6].bufEmpty)                    // If User's TX buffer is empty
      {
        Uart.DisableTxInterrupts(UART6);                          // Disable TX interrupts
      }

      INTClearFlag(INT_SOURCE_UART_TX(UART6));                    // Clear the TX interrupt Flag
    }
  }
  //===========================================================
  

	// RX interrupt handling
  //===========================================================
  if ( INTGetEnable ( INT_SOURCE_UART_RX(UART6) ) )               // If RX interrupts enabled
  {
    if ( INTGetFlag ( INT_SOURCE_UART_RX(UART6) ) )               // If RX interrupt occured
    {
      i = 0;
      iMax = 8;                                                   // Read max 8 bytes/interrupt
      while (   UARTReceivedDataIsAvailable(UART6)                // While RX data available
            && !Uart.Var.uartRxFifo[UART6].bufFull                // and user's RX buffer not full
            && (i < iMax)                                         // and under 8 bytes read
            )
      { // while ^
        data = UARTGetDataByte(UART6);                            // Get data for PIC32's RX FIFO buffer and copy it to user (next line)
        if ( UartFifoWrite((void *) &Uart.Var.uartRxFifo[UART6], &data) < 0 ) // If copy to user did not work
        {
          break;                                                  // Exit while loop
        }
        i++;
      } // end while

      if (!Uart.Var.uartRxFifo[UART6].bufEmpty)                   // If there is data in the user's RX buffer
      {
        Uart.Var.oIsRxDataAvailable[UART6] = 1;                   // Set according flag
      }

      INTClearFlag (INT_SOURCE_UART_RX(UART6) );                  // Clear the RX interrupt Flag

    }
	}
  //===========================================================
}
//=============================================


/*******************************************************************************
 ***********************                               *************************
 ********************           ADC INTERRUPT             **********************
 ***********************                               *************************
 *******************************************************************************/

//=============================================
// Configure the ADC interrupt handler
//=============================================
void __ISR(_ADC_VECTOR, ADC_INTERRUPT_PRIO) AdcInterruptHandler(void)
{
  Adc.Read();               // Read the enabled channels and puts them in Adc.Var.adcReadValues[]
  INTClearFlag(INT_AD1);    // Clear the ADC conversion done interrupt Flag
}
//=============================================


/*******************************************************************************
 ***********************                               *************************
 ********************      INPUT CAPTURE INTERRUPTS       **********************
 ***********************                               *************************
 ******************************************************************************/

//================================================
// Configure the InputCapture 1 interrupt handler
//================================================
void __ISR(_INPUT_CAPTURE_1_VECTOR, IC1_INT_PRIORITY) InputCapture1InterruptHandler(void)
{
  /*
   * DEVELOPPER CODE HERE
   */

  // Get the timer used by this Input Capture
  TimerNum_t numTimer = InputCapture.Var.timerUsed[IC1];

  // Wait for capture data to be ready
  while(!(InputCapture.IsCaptureReady(IC1)));

  // Update values of timer overflows
  InputCapture.Var.previousTimerOverflows[IC1] = InputCapture.Var.currentTimerOverflows[IC1];
  InputCapture.Var.currentTimerOverflows[IC1]  = Timer.ReadOverflows(numTimer);

  // Store the timer value of the capture event
  InputCapture.Var.previousCaptureCountValue[IC1] = InputCapture.Var.currentCaptureCountValue[IC1];
  InputCapture.Var.currentCaptureCountValue [IC1] = InputCapture.ReadCapture(IC1);

//  oCapture = 1;   // Flag that tells that a new Capture event occured

  // Clear the interrupt flag
  INTClearFlag(INT_IC1);
}
//================================================

//================================================
// Configure the InputCapture 2 interrupt handler
//================================================
void __ISR(_INPUT_CAPTURE_2_VECTOR, IC2_INT_PRIORITY) InputCapture2InterruptHandler(void)
{
  /*
   * DEVELOPPER CODE HERE
   */

  // Get the timer used by this Input Capture
  TimerNum_t numTimer = InputCapture.Var.timerUsed[IC2];

  // Wait for capture data to be ready
  while(!(InputCapture.IsCaptureReady(IC2)));

  // Update values of timer overflows
  InputCapture.Var.previousTimerOverflows[IC2] = InputCapture.Var.currentTimerOverflows[IC2];
  InputCapture.Var.currentTimerOverflows[IC2]  = Timer.ReadOverflows(numTimer);

  // Store the timer value of the capture event
  InputCapture.Var.previousCaptureCountValue[IC2] = InputCapture.Var.currentCaptureCountValue[IC2];
  InputCapture.Var.currentCaptureCountValue [IC2] = InputCapture.ReadCapture(IC2);

//  oCapture = 1;   // Flag that tells that a new Capture event occured

  // Clear the interrupt flag
  INTClearFlag(INT_IC2);
}
//================================================

//================================================
// Configure the InputCapture 3 interrupt handler
//================================================
void __ISR(_INPUT_CAPTURE_3_VECTOR, IC3_INT_PRIORITY) InputCapture3InterruptHandler(void)
{
  /*
   * DEVELOPPER CODE HERE
   */

  // Get the timer used by this Input Capture
  TimerNum_t numTimer = InputCapture.Var.timerUsed[IC3];

  // Wait for capture data to be ready
  while(!(InputCapture.IsCaptureReady(IC3)));

  // Update values of timer overflows
  InputCapture.Var.previousTimerOverflows[IC3] = InputCapture.Var.currentTimerOverflows[IC3];
  InputCapture.Var.currentTimerOverflows[IC3]  = Timer.ReadOverflows(numTimer);

  // Store the timer value of the capture event
  InputCapture.Var.previousCaptureCountValue[IC3] = InputCapture.Var.currentCaptureCountValue[IC3];
  InputCapture.Var.currentCaptureCountValue [IC3] = InputCapture.ReadCapture(IC3);

//  oCapture = 1;   // Flag that tells that a new Capture event occured

  // Clear the interrupt flag
  INTClearFlag(INT_IC3);
}
//================================================

//================================================
// Configure the InputCapture 4 interrupt handler
//================================================
void __ISR(_INPUT_CAPTURE_4_VECTOR, IC4_INT_PRIORITY) InputCapture4InterruptHandler(void)
{
  /*
   * DEVELOPPER CODE HERE
   */

  // Get the timer used by this Input Capture
  TimerNum_t numTimer = InputCapture.Var.timerUsed[IC4];

  // Wait for capture data to be ready
  while(!(InputCapture.IsCaptureReady(IC4)));

  // Update values of timer overflows
  InputCapture.Var.previousTimerOverflows[IC4] = InputCapture.Var.currentTimerOverflows[IC4];
  InputCapture.Var.currentTimerOverflows[IC4]  = Timer.ReadOverflows(numTimer);

  // Store the timer value of the capture event
  InputCapture.Var.previousCaptureCountValue[IC4] = InputCapture.Var.currentCaptureCountValue[IC4];
  InputCapture.Var.currentCaptureCountValue [IC4] = InputCapture.ReadCapture(IC4);

//  oCapture = 1;   // Flag that tells that a new Capture event occured

  // Clear the interrupt flag
  INTClearFlag(INT_IC4);
}
//================================================

//================================================
// Configure the InputCapture 5 interrupt handler
//================================================
void __ISR(_INPUT_CAPTURE_5_VECTOR, IC5_INT_PRIORITY) InputCapture5InterruptHandler(void)
{
  /*
   * DEVELOPPER CODE HERE
   */

  // Get the timer used by this Input Capture
  TimerNum_t numTimer = InputCapture.Var.timerUsed[IC5];

  // Wait for capture data to be ready
  while(!(InputCapture.IsCaptureReady(IC5)));

  // Update values of timer overflows
  InputCapture.Var.previousTimerOverflows[IC5] = InputCapture.Var.currentTimerOverflows[IC5];
  InputCapture.Var.currentTimerOverflows[IC5]  = Timer.ReadOverflows(numTimer);

  // Store the timer value of the capture event
  InputCapture.Var.previousCaptureCountValue[IC5] = InputCapture.Var.currentCaptureCountValue[IC5];
  InputCapture.Var.currentCaptureCountValue [IC5] = InputCapture.ReadCapture(IC5);

//  oCapture5 = 1;   // Flag that tells that a new Capture event occured

  // Clear the interrupt flag
  INTClearFlag(INT_IC5);
}
//================================================


/*******************************************************************************
 ***********************                               *************************
 ********************           CAN INTERRUPTS            **********************
 ***********************                               *************************
 ******************************************************************************/

//================================================
// Configure the CAN1 interrupt handler
//================================================
void __ISR(_CAN_1_VECTOR, CAN1_INT_PRIORITY) Can1InterruptHandler(void)
{
    // Check if the source of the interrupt is RX_EVENT. This is redundant since
    // only this event is enabled in this example but this shows one scheme for
    // handling events
    if ((CANGetModuleEvent(CAN1) & CAN_RX_EVENT) != 0) {

        // Within this, you can check which channel caused the event by using
        // the CANGetModuleEvent() function which returns a code representing
        // the highest priority pending event.
        if (CANGetPendingEventCode(CAN1) == CAN_CHANNEL1_EVENT) {

            // This means that channel 1 caused the event.
            // The CAN_RX_CHANNEL_NOT_EMPTY event is persistent. You could either
            // read the channel in the ISR to clear the event condition or as done
            // here, disable the event source, and set an application flag to
            // indicate that a message has been received. The event can be
            // enabled by the application when it has processed one message.
            // Note that leaving the event enabled would cause the CPU to keep
            // executing the ISR since the CAN_RX_CHANNEL_NOT_EMPTY event is
            // persistent (unless the not empty condition is cleared.)
            CANEnableChannelEvent(CAN1, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);    
            
            //Do shit
            
            CANUpdateChannel(CAN1, CAN_CHANNEL1);
            CANEnableChannelEvent(CAN1, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
            
        }
    }

    // The CAN1 Interrupt flag is  cleared at the end of the interrupt routine.
    // This is because the event source that could have caused this interrupt to
    // occur (CAN_RX_CHANNEL_NOT_EMPTY) is disabled. Attempting to clear the
    // CAN1 interrupt flag when the the CAN_RX_CHANNEL_NOT_EMPTY interrupt is
    // enabled will not have any effect because the base event is still present.
    INTClearFlag(INT_CAN1);
}


//================================================
// Configure the CAN2 interrupt handler
//================================================
void __ISR(_CAN_2_VECTOR, CAN2_INT_PRIORITY) Can2InterruptHandler(void)
{
    // Check if the source of the interrupt is RX_EVENT. This is redundant since
    // only this event is enabled in this example but this shows one scheme for
    // handling events
    if ((CANGetModuleEvent(CAN2) & CAN_RX_EVENT) != 0) {

        // Within this, you can check which channel caused the event by using
        // the CANGetModuleEvent() function which returns a code representing
        // the highest priority pending event.
        if (CANGetPendingEventCode(CAN2) == CAN_CHANNEL1_EVENT) {

            // This means that channel 1 caused the event.
            // The CAN_RX_CHANNEL_NOT_EMPTY event is persistent. You could either
            // read the channel in the ISR to clear the event condition or as done
            // here, disable the event source, and set an application flag to
            // indicate that a message has been received. The event can be
            // enabled by the application when it has processed one message.
            // Note that leaving the event enabled would cause the CPU to keep
            // executing the ISR since the CAN_RX_CHANNEL_NOT_EMPTY event is
            // persistent (unless the not empty condition is cleared.)
            CANEnableChannelEvent(CAN2, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);           
        }
    }

    // The CAN1 Interrupt flag is  cleared at the end of the interrupt routine.
    // This is because the event source that could have caused this interrupt to
    // occur (CAN_RX_CHANNEL_NOT_EMPTY) is disabled. Attempting to clear the
    // CAN1 interrupt flag when the the CAN_RX_CHANNEL_NOT_EMPTY interrupt is
    // enabled will not have any effect because the base event is still present.
    INTClearFlag(INT_CAN2);
}


/*******************************************************************************
 ***********************                               *************************
 ********************           I2C INTERRUPTS            **********************
 ***********************                               *************************
 *******************************************************************************/

//=============================================
// Configure the I2C4 interrupt handler
//=============================================
void __ISR(_I2C_4_VECTOR, I2C4_INT_PRIORITY) I2c4InterruptHandler(void)
{
//  if (INTGetFlag(INT_I2C4S))  // Slave interrupt
//  {
//    INTClearFlag(INT_I2C4S);
//  }
  
//  if (INTGetFlag(INT_I2C4B))  //Bus Collision interrupt
//  {
//    INTClearFlag(INT_I2C4B);
//  }
  
  sI2cCmdBuffer_t masterData;   // Used for keeping track of the current state
  
  if (INTGetFlag(INT_I2C4M))  // Master interrupt
  {
    INTClearFlag(INT_I2C4M);

    if (I2c.Var.oReadDataInNextInterrupt[I2C4])     // If a read was started last interrupt
    {
      masterData.data  = I2C4RCV;                   // Read from I2C buffer
      masterData.state = I2C_MASTER_RECEIVE_DATA;   // Dummy write
      I2cFifoWrite((void *) &I2c.Var.i2cUserFifo[I2C4], &masterData);   // Copy to user
      I2c.Var.oRxDataAvailable[I2C4] = 1;
      I2c.Var.oReadDataInNextInterrupt[I2C4] = 0;
    }
    
    if (I2c.Var.oI2cWriteIsRunning[I2C4])   // Writing procedure
    {
      I2cFifoRead((void *) &I2c.Var.i2cWriteQueue[I2C4], &masterData);  // Get current state
      switch (masterData.state)
      {
      //======================================================  
        case I2C_MASTER_RECEIVE_DATA : 
          I2C4CONbits.RCEN = 1;                         // Receive byte sequence
          I2c.Var.oReadDataInNextInterrupt[I2C4] = 1;   // Flag for the next interrupt to read the RX buffer
          break;
      //====================================================== 

      //======================================================  
        case I2C_MASTER_START_CONDITION : 
          I2C4CONbits.SEN = 1;                          // Start condition sequence
          break;
      //====================================================== 

      //======================================================  
        case I2C_MASTER_STOP_CONDITION : 
          I2C4CONbits.PEN = 1;                          // Stop condition sequence
          
          if (I2c.Var.oPoolSlaveAcknowledge[I2C4])      // If the user wanted to poll
          {
            if (!I2c.Var.oSecondStopAfterPooling[I2C4]) // If this is the first stop after writing all the data
            {                                           // Add the next three states required for polling
              masterData.state = I2C_MASTER_START_CONDITION;
              I2cFifoWrite((void *) &I2c.Var.i2cWriteQueue[I2C4], &masterData);
              
              masterData.state = I2C_MASTER_TRANSMIT_DATA;
              I2cFifoWrite((void *) &I2c.Var.i2cWriteQueue[I2C4], &masterData);
              
              masterData.state = I2C_MASTER_STOP_CONDITION;
              I2cFifoWrite((void *) &I2c.Var.i2cWriteQueue[I2C4], &masterData);
              
              I2c.Var.oSecondStopAfterPooling[I2C4] = 1;
            }
            else                                        // If the first stop has passed
            {
              if (!I2CByteWasAcknowledged(I2C4))        // If slave sent NACK
              {                                         // Redo the 3 states for the polling
                masterData.state = I2C_MASTER_START_CONDITION;
                I2cFifoWrite((void *) &I2c.Var.i2cWriteQueue[I2C4], &masterData);

                masterData.state = I2C_MASTER_TRANSMIT_DATA;
                I2cFifoWrite((void *) &I2c.Var.i2cWriteQueue[I2C4], &masterData);

                masterData.state = I2C_MASTER_STOP_CONDITION;
                I2cFifoWrite((void *) &I2c.Var.i2cWriteQueue[I2C4], &masterData);
              }
              else                                      // If slave sent ACK
              {                                         // End the communication with the slave
                masterData.state = I2C_MASTER_DONE;
                I2cFifoWrite((void *) &I2c.Var.i2cWriteQueue[I2C4], &masterData);
                I2c.Var.oSecondStopAfterPooling[I2C4] = 0;
              }
            }
          }
          break;
      //====================================================== 

      //======================================================    
        case I2C_MASTER_TRANSMIT_DATA : 
          I2C4TRN = masterData.data;      // Put data in TX buffer
          break;
      //====================================================== 

      //======================================================  
        case I2C_MASTER_DONE : 
          if (I2c.Var.i2cWriteQueue[I2C4].bufEmpty)     // If there is nothing more to send
          {
            I2c.Var.oI2cWriteIsRunning[I2C4] = 0;       // Turn off writing process
          }
          else                                          // If there is still data in the WriteQueue
          {
            INTSetFlag(INT_I2C4M);                      // Start another writing process
          }
          break;
      //====================================================== 

      //======================================================  
        case I2C_MASTER_REPEAT_START : 
          I2C4CONbits.RSEN = 1;   //repeated start condition sequence
          break;
      //====================================================== 

      //======================================================  
        case I2C_MASTER_SLAVE_SENT_STOP :   // Not used
//          LED_ERROR_ON;
          break;
      //====================================================== 

      //======================================================  
        case I2C_MASTER_SEND_ACK : 
          I2C4CONbits.ACKDT = 0;  //ACK
          I2C4CONbits.ACKEN = 1;  //Send ACK sequence
          break;
      //====================================================== 

      //======================================================  
        case I2C_MASTER_SEND_NACK : 
          I2C4CONbits.ACKDT = 1;  //NACK
          I2C4CONbits.ACKEN = 1;  //Send NACK sequence
          break;
      //====================================================== 

      //======================================================  
        case I2C_CMD_ERROR :      // Not used
//          LED_ERROR_ON;
          break;
      //====================================================== 

      //======================================================  
        default : 
          break;
      //======================================================  
      } // end switch (master.state)
    } // end if (writing sequence)
    
    

    if (I2c.Var.oI2cReadIsRunning[I2C4])    // Reading procedure
    {
      I2cFifoRead((void *) &I2c.Var.i2cReadQueue[I2C4], &masterData);   // Get current state
      switch (masterData.state)
      {
      //======================================================  
        case I2C_MASTER_RECEIVE_DATA : 
          I2C4CONbits.RCEN = 1;             // Receive byte sequence
          I2c.Var.oReadDataInNextInterrupt[I2C4] = 1;
          break;
      //====================================================== 

      //======================================================  
        case I2C_MASTER_START_CONDITION : 
          I2C4CONbits.SEN = 1;              // Start condition sequence
          break;
      //====================================================== 

      //======================================================  
        case I2C_MASTER_REPEAT_START : 
          I2C4CONbits.RSEN = 1;             // Repeated start condition sequence
          break;
      //====================================================== 

      //======================================================  
        case I2C_MASTER_STOP_CONDITION : 
          I2C4CONbits.PEN = 1;              // Stop condition
          break;
      //====================================================== 

      //======================================================    
        case I2C_MASTER_TRANSMIT_DATA : 
          I2C4TRN = masterData.data;        // Put data in TX buffer
          break;
      //====================================================== 

      //======================================================  
        case I2C_MASTER_DONE : 
          if (I2c.Var.i2cReadQueue[I2C4].bufEmpty)    // If there is nothing more to send
          {
            I2c.Var.oI2cReadIsRunning[I2C4] = 0;      // Turn off reading process
          }
          else                                        // If there is still data in the ReadQueue
          {
            INTSetFlag(INT_I2C4M);                    // Start another reading process
          }
          break;
      //====================================================== 

      //======================================================  
        case I2C_MASTER_SLAVE_SENT_STOP :   // Not used
//          LED_ERROR_ON;
          break;
      //====================================================== 

      //======================================================  
        case I2C_MASTER_SEND_ACK : 
          I2C4CONbits.ACKDT = 0;  // ACK
          I2C4CONbits.ACKEN = 1;  // Send ACK sequence
          break;
      //====================================================== 

      //======================================================  
        case I2C_MASTER_SEND_NACK : 
          I2C4CONbits.ACKDT = 1;  // NACK
          I2C4CONbits.ACKEN = 1;  // Send NACK sequence
          break;
      //====================================================== 

      //======================================================  
        case I2C_CMD_ERROR :      // Not used
//          LED_ERROR_ON;
          break;
      //======================================================

      //======================================================  
        default : 
          break;
      //======================================================  
      } // end switch (master.state)
    } // end if (read sequence)
  }  // end if (master interrupt)
}   // end interrupt
//=============================================


/*******************************************************************************
 ***********************                               *************************
 ********************           SPI INTERRUPTS            **********************
 ***********************                               *************************
 *******************************************************************************/


//=============================================
// Configure the SPI 3 interrupt handler
//=============================================

//void __ISR(_SPI_3_VECTOR, S3_INTERRUPT_PRIORITY) Spi3InterruptHandler(void)
//{
//  UINT8  i
//        ,iMax   // Read/write max 8 bytes/interrupt
//        ,data   // used in SpiFifoWrite/Read functions
//        ;
//
//	// TX interrupt handling
//  //===========================================================
//
//  if ( INTGetEnable ( INT_SOURCE_SPI_TX(SPI3) ) )               // If TX interrupts enabled
//  {
//    if ( INTGetFlag ( INT_SOURCE_SPI_TX(SPI3) ) )               // If TX interrupt occured
//    {
//      if ( SpiChnTxBuffEmpty(SPI_CHANNEL3) && !Spi.Var.spiTxFifo[SPI3].bufEmpty )  // If TX buffer is ready to receive data and the user's TX buffer is not empty
//      {
//        if (Spi.Var.spiTxFifo[SPI3].lineBuffer.length < Spi.Var.spiTxFifo[SPI3].maxWordsPerInt)     // Write max 8 bytes/interrupt
//        {
//          iMax = Spi.Var.spiTxFifo[SPI3].lineBuffer.length;
//        }
//        else
//        {
//          iMax = Spi.Var.spiTxFifo[SPI3].maxWordsPerInt;
//        }
//
//        for (i = 0; i < iMax; i++)
//        {
//          SpiFifoRead((void *) &Spi.Var.spiTxFifo[SPI3], &data);  // Copy from user
//          SPI3BUF = data;                                         // Put data in PIC32's TX buffer
//        }
//      }
//
//      if (Spi.Var.spiTxFifo[SPI3].bufEmpty)                    // If User's TX buffer is empty
//      {
//        Spi.DisableTxInterrupts(SPI3);                          // Disable TX interrupts
//      }
//
//      INTClearFlag(INT_SOURCE_SPI_TX(SPI3));                    // Clear the TX interrupt Flag
//    }
//  }
//  //===========================================================
//  
//
//	// RX interrupt handling
//  //===========================================================
//  if ( INTGetEnable ( INT_SOURCE_SPI_RX(SPI3) ) )               // If RX interrupts enabled
//  {
//    if ( INTGetFlag ( INT_SOURCE_SPI_RX(SPI3) ) )               // If RX interrupt occured
//    {
//      i = 0;
//      iMax = Spi.Var.spiRxFifo[SPI3].maxWordsPerInt;            // Read max 8 bytes/interrupt
//      while (   SpiChnDataRdy(SPI_CHANNEL3)                // While RX data available
//            && !Spi.Var.spiRxFifo[UART3].bufFull                // and user's RX buffer not full
//            && (i < iMax)                                         // and under 8 bytes read
//            )
//      { // while ^
//        data = SpiChnGetC(SPI_CHANNEL3);                            // Get data for PIC32's RX FIFO buffer and copy it to user (next line)
//        if ( SpiFifoWrite((void *) &Spi.Var.spiRxFifo[SPI3], &data) < 0 ) // If copy to user did not work
//        {
//          break;                                                  // Exit while loop
//        }
//        i++;
//      } // end while
//
//      if (!Spi.Var.spiRxFifo[SPI3].bufEmpty)                   // If there is data in the user's RX buffer
//      {
//        Spi.Var.oIsRxDataAvailable[SPI3] = 1;                   // Set according flag
//      }
//
//      INTClearFlag (INT_SOURCE_SPI_RX(SPI3) );                  // Clear the RX interrupt Flag
//
//    }
//	}
//  //===========================================================
//}
////=============================================