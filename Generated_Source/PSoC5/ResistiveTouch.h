/*******************************************************************************
* File Name: ResistiveTouch.h
* Version 2.0
*
* Description:
*  This file provides the constants and parameter values for the ResistiveTouch
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_RESISTIVE_TOUCH_ResistiveTouch_H)
#define CY_RESISTIVE_TOUCH_ResistiveTouch_H

#include "cytypes.h"
#include "ResistiveTouch_ADC.h"
#include "ResistiveTouch_AMux.h"


/***************************************
*        Function Prototypes
****************************************/

void ResistiveTouch_Start(void) ;
void ResistiveTouch_Stop(void) ;
void ResistiveTouch_Init(void) ; 
void ResistiveTouch_Enable(void) ;
void ResistiveTouch_ActivateX(void) ;
void ResistiveTouch_ActivateY(void);
int16 ResistiveTouch_Measure(void) ;
uint8 ResistiveTouch_TouchDetect(void) ;

void ResistiveTouch_SaveConfig(void) ;
void ResistiveTouch_RestoreConfig(void) ;
void ResistiveTouch_Sleep(void) ; 
void ResistiveTouch_Wakeup(void) ; 

/* Macros for emWinGraphics Library */
#define CYTOUCH_START()         ResistiveTouch_Start() 
#define CYTOUCH_STOP()          ResistiveTouch_Stop()
#define CYTOUCH_MEASURE()       ResistiveTouch_Measure()
#define CYTOUCH_ACTIVATE_X()    ResistiveTouch_ActivateX()
#define CYTOUCH_ACTIVATE_Y()    ResistiveTouch_ActivateY()
#define CYTOUCH_TOUCHED()       ResistiveTouch_TouchDetect()


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 ResistiveTouch_initVar;


/***************************************
*       Constants
***************************************/

/* AMUX channel definitions */
#define ResistiveTouch_AMUX_XP_CHAN   (0)
#define ResistiveTouch_AMUX_YP_CHAN   (1)
#define ResistiveTouch_AMUX_NO_CHAN   (-1)

/* The screen is touched if the measured value is lower than the specified
* threshold.
*/
#define ResistiveTouch_TOUCH_THRESHOLD        (0x778)


#endif /* CY_RESIST_TOUCH_ResistiveTouch_H */


/* [] END OF FILE */
