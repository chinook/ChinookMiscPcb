//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Project Template
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : Setup.h
// Author  : Frederic Chasse
// Date    : 2015-01-03
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This is the setup header for the system. It contains function
//           prototypes as well as macros and the public structure of
//           ChinookLib functions.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : For ChinookLib to be useable, it must be cloned on your hard
//           drive so the path
//               "..\..\..\ChinookLib\ChinookLib.X\headers\ChinookLib.h"
//           references an existing file.
//
//           Function names can and should be renamed by the user to improve the
//           readability of the code.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#ifndef __SETUP_H__
#define	__SETUP_H__

//%%%%%%%%%%%%%%%%%%%%%%%%%
// ChinookLib files
//%%%%%%%%%%%%%%%%%%%%%%%%%
#include "..\..\..\ChinookLib\ChinookLib.X\headers\ChinookLib.h"

//==============================================================================
// ChinookLib functions
//==============================================================================
struct sChinook Chinook;            // Contains all ChinookLib functions


//==============================================================================
// Skadi functions
//==============================================================================
//extern const size_t lengthSkadiCommandTable;
//extern sSkadiCommand_t skadiCommandTable[];

//==============================================================================
// State Machine public functions prototypes
//==============================================================================
void InitTimer        (void);
void InitPwm          (void);
void InitPorts        (void);
void InitCan          (void);
void InitSkadi        (void);
void InitSpi          (void);
void InitUart         (void);
void InitI2c          (void);
void InitWdt          (void);
void InitAdc          (void);
void InitInputCapture (void);
void StartInterrupts  (void);


//==============================================================================
// Macro definitions
//==============================================================================
#define INIT_TIMER          InitTimer()
#define INIT_PWM            InitPwm()
#define INIT_PORTS          InitPorts()
#define INIT_CAN            InitCan()
#define INIT_SPI            InitSpi()
#define INIT_UART           InitUart()
#define INIT_SKADI          InitSkadi()
#define INIT_I2C            InitI2c()
#define INIT_WDT            InitWdt()
#define INIT_ADC            InitAdc()
#define INIT_INPUT_CAPTURE  InitInputCapture()
#define START_INTERRUPTS    StartInterrupts()

//==============================================================================
// Define OUTPUT LED
//==============================================================================
#define LED_STATUS        LATFbits.LATF3
#define LED_CAN           LATBbits.LATB13
#define LED_ERROR         LATBbits.LATB15
#define LED_DEBG4         LATBbits.LATB12
#define LED_DEBG3         LATBbits.LATB11
#define LED_DEBG2         LATBbits.LATB10
#define LED_DEBG1         LATBbits.LATB9
#define LED_DEBG0         LATBbits.LATB8

/* Setup IO LED */
#define LED_DEBUG0_ON       Port.B.ClearBits(BIT_8)
#define LED_DEBUG1_ON       Port.B.ClearBits(BIT_9)
#define LED_DEBUG2_ON       Port.B.ClearBits(BIT_10)
#define LED_DEBUG3_ON       Port.B.ClearBits(BIT_11)
#define LED_DEBUG4_ON       Port.B.ClearBits(BIT_12)
#define LED_ERROR_ON        Port.B.ClearBits(BIT_15)
#define LED_CAN_ON          Port.B.ClearBits(BIT_13)
#define LED_STATUS_ON       Port.F.ClearBits(BIT_3)

#define LED_DEBUG0_OFF      Port.B.SetBits(BIT_8)
#define LED_DEBUG1_OFF      Port.B.SetBits(BIT_9)
#define LED_DEBUG2_OFF      Port.B.SetBits(BIT_10)
#define LED_DEBUG3_OFF      Port.B.SetBits(BIT_11)
#define LED_DEBUG4_OFF      Port.B.SetBits(BIT_12)
#define LED_ERROR_OFF       Port.B.SetBits(BIT_15)
#define LED_CAN_OFF         Port.B.SetBits(BIT_13)
#define LED_STATUS_OFF      Port.F.SetBits(BIT_3)

#define LED_DEBUG0_TOGGLE   Port.B.ToggleBits(BIT_8)
#define LED_DEBUG1_TOGGLE   Port.B.ToggleBits(BIT_9)
#define LED_DEBUG2_TOGGLE   Port.B.ToggleBits(BIT_10)
#define LED_DEBUG3_TOGGLE   Port.B.ToggleBits(BIT_11)
#define LED_DEBUG4_TOGGLE   Port.B.ToggleBits(BIT_12)
#define LED_ERROR_TOGGLE    Port.B.ToggleBits(BIT_15)
#define LED_CAN_TOGGLE      Port.B.ToggleBits(BIT_13)
#define LED_STATUS_TOGGLE   Port.F.ToggleBits(BIT_3)

#define LED_ALL_OFF()     { LED_DEBUG0_OFF    ; LED_DEBUG1_OFF    ; \
                            LED_DEBUG2_OFF    ; LED_DEBUG3_OFF    ; \
                            LED_DEBUG4_OFF    ; LED_ERROR_OFF     ; \
                            LED_CAN_OFF       ; LED_STATUS_OFF    ; }

#define LED_ALL_ON()      { LED_DEBUG0_ON     ; LED_DEBUG1_ON     ; \
                            LED_DEBUG2_ON     ; LED_DEBUG3_ON     ; \
                            LED_DEBUG4_ON     ; LED_ERROR_ON      ; \
                            LED_CAN_ON        ; LED_STATUS_ON     ; }

#define LED_ALL_TOGGLE()  { LED_DEBUG0_TOGGLE ; LED_DEBUG1_TOGGLE ; \
                            LED_DEBUG2_TOGGLE ; LED_DEBUG3_TOGGLE ; \
                            LED_DEBUG4_TOGGLE ; LED_ERROR_TOGGLE  ; \
                            LED_CAN_TOGGLE    ; LED_STATUS_TOGGLE ; }

//==============================================================================
// Define INPUT SWITCH
//==============================================================================
#define SW1               PORTEbits.RE5
#define SW2               PORTEbits.RE6
#define SW3               PORTEbits.RE7


/* Setup  IO switch */
#define READ_SW1    Port.E.ReadBits(BIT_5) >> 5
#define READ_SW2    Port.E.ReadBits(BIT_6) >> 6
#define READ_SW3    Port.E.ReadBits(BIT_7) >> 7


//==============================================================================
// Variable definitions
//==============================================================================
#define CAN_NB_CHANNELS     2 // 2 CAN channels will be used
#define CAN_BUFFER_SIZE     8

BYTE Can1MessageFifoArea [ CAN_NB_CHANNELS     // Space used by CAN
                         * CAN_BUFFER_SIZE 
                         * CAN_TX_RX_MESSAGE_SIZE_BYTES 
                         ];

#define HORN_FAN_BOARD_SID                0x80
#define HORN_FAN_DISCONNECT_SID           0x81

#endif	/* __SETUP_H__ */