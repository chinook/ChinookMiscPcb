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
// Variable definitions
//==============================================================================
#define CAN_NB_CHANNELS     2 // 2 CAN channels will be used
#define CAN_BUFFER_SIZE     8

BYTE Can1MessageFifoArea [ CAN_NB_CHANNELS     // Space used by CAN
                         * CAN_BUFFER_SIZE 
                         * CAN_TX_RX_MESSAGE_SIZE_BYTES 
                         ];

BYTE Can2MessageFifoArea [ CAN_NB_CHANNELS     // Space used by CAN
                         * CAN_BUFFER_SIZE 
                         * CAN_TX_RX_MESSAGE_SIZE_BYTES 
                         ];

#endif	/* __SETUP_H__ */