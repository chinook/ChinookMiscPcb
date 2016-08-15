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
// Purpose : This is a template header file that every developper should use as
//           a starter when developping code.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : Function names can and should be renamed by the user to improve the
//           readability of the code.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#ifndef __HEADER_TEMPLATE_H__
#define	__HEADER_TEMPLATE_H__

#include "Setup.h"


//==============================================================================
// Public functions prototypes
//==============================================================================

/**************************************************************
 * Function name  : TemplateFunction
 * Purpose        : Give a template for developpers to start from.
 * Arguments      : None.
 * Returns        : 0 on success, -1 on failure.
 *************************************************************/
static inline INT8 TemplateFunction (void);


//==============================================================================
// Macro definitions
//==============================================================================

#define TEMPLATE_MACRO_1    1
#define TEMPLATE_MACRO_2    2


//==============================================================================
// Variable declarations
//==============================================================================

/***********************************
 * Template structure
 **********************************/
typedef struct sTemplate
{
  UINT16  variableName;
  UINT8   secondVariable;
  float   thirdVariable;
  double  fourthVariable;
} sTemplate;

/***********************************
 * Template global variable
 **********************************/
INT32 globalVariable = -10;

/***********************************
 * Global struct
 **********************************/
//sTemplate templateStruct;
//  {
//     .variableName    = 12
//    ,.secondVariable  = 0xFF
//    ,.thirdVariable   = 0.0f
//    ,.fourthVariable  = 0.0f
//  }


#endif	/* __HEADER_TEMPLATE_H__ */

