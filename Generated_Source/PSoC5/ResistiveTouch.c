/*******************************************************************************
* File Name: ResistiveTouch.c
* Version 2.0
*
* Description:
*  This file provides the API source code for the Resistive Touch component.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "ResistiveTouch.h"
#include "ResistiveTouch_xm.h"
#include "ResistiveTouch_xp.h"
#include "ResistiveTouch_ym.h"
#include "ResistiveTouch_yp.h"

uint8 ResistiveTouch_initVar = 0u;
static uint8 ResistiveTouch_measurementFlag = 0u;


/*******************************************************************************
* Function Name: ResistiveTouch_Init
********************************************************************************
*
* Summary:
*  Calls the Init() function of the ADC and AMux components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResistiveTouch_Init(void) 
{
    ResistiveTouch_AMux_Init();
    ResistiveTouch_ADC_Init();
}


/*******************************************************************************
* Function Name: ResistiveTouch_Start
********************************************************************************
*
* Summary:
*  Calls Init() if the component has not been initialized before. Calls Enable()
*  to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
* 
* Global variables:
*  ResistiveTouch_initVar - Indicates whether the component has been
*                             initialized.
*
*******************************************************************************/
void ResistiveTouch_Start(void)  
{
    if(ResistiveTouch_initVar == 0u)
    {    
        ResistiveTouch_Init();
        ResistiveTouch_initVar = 1u;
    }
    ResistiveTouch_Enable();
}


/*******************************************************************************
* Function Name: ResistiveTouch_Stop
********************************************************************************
*
* Summary:
*  Stops the ADC and AMux components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResistiveTouch_Stop(void)  
{
    ResistiveTouch_ADC_Stop();
    ResistiveTouch_AMux_Stop();
}


/*******************************************************************************
* Function Name: ResistiveTouch_Enable
********************************************************************************
*
* Summary:
*  Enables the ADC component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResistiveTouch_Enable(void)  
{
    ResistiveTouch_ADC_Enable();
}


/*******************************************************************************
* Function Name: ResistiveTouch_ActivateX
********************************************************************************
*
* Summary: 
*  Configures the pins to measure the Y-axis.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResistiveTouch_ActivateX(void) 
{
    /* Pins configuration to measure Y. */
    CyPins_SetPinDriveMode(ResistiveTouch_ym_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(ResistiveTouch_yp_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(ResistiveTouch_xp_0, PIN_DM_ALG_HIZ);
    CyPins_SetPinDriveMode(ResistiveTouch_xm_0, PIN_DM_ALG_HIZ);
    
    /* Switch AMux if channel 0 is not selected. */
    if(ResistiveTouch_AMux_GetChannel() != ResistiveTouch_AMUX_XP_CHAN)
    {
        ResistiveTouch_AMux_Next();
    }
}


/*******************************************************************************
* Function Name: ResistiveTouch_ActivateY
********************************************************************************
*
* Summary: 
*  Configures the pins to measure X-axis.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResistiveTouch_ActivateY(void) 
{
    /* Pins configuration to measure X. */
    CyPins_SetPinDriveMode(ResistiveTouch_xm_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(ResistiveTouch_xp_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(ResistiveTouch_yp_0, PIN_DM_ALG_HIZ);
    CyPins_SetPinDriveMode(ResistiveTouch_ym_0, PIN_DM_ALG_HIZ);
    
    /* Switch AMux if channel 1 is not selected. */
    if(ResistiveTouch_AMux_GetChannel() == ResistiveTouch_AMUX_XP_CHAN)
    {
        ResistiveTouch_AMux_Next();
    }
    /* Switch AMux to channel 1 if AMux is disconnected. */
    else if(ResistiveTouch_AMux_GetChannel() == ResistiveTouch_AMUX_NO_CHAN)
    {
        ResistiveTouch_AMux_Next();
        ResistiveTouch_AMux_Next();
    }
    else
    {
        /* Channel 1 is already selected. */
    }
}


/*******************************************************************************
* Function Name: ResistiveTouch_TouchDetect
********************************************************************************
*
* Summary:
*  Determines if the screen is touched.
*
* Parameters:
*  None
*
* Return:
*  uint8: The touch state.
*  0 - untouched
*  1 - touched
*
*******************************************************************************/
uint8 ResistiveTouch_TouchDetect(void) 
{
    /* Configure x+ pin to detect touch. */
    CyPins_SetPinDriveMode(ResistiveTouch_xp_0, PIN_DM_STRONG);

    /* Add delay for signal to stabilize. */
    CyDelayUs(5u);

    CyPins_SetPinDriveMode(ResistiveTouch_xp_0, PIN_DM_RES_UP);
    
    /* Switch AMux if channel 0 is not selected. */
    if(ResistiveTouch_AMux_GetChannel() != ResistiveTouch_AMUX_XP_CHAN)
    {
        ResistiveTouch_AMux_Next();
    }

    /* Configure x-, y+ and y- to detect touch. */
    CyPins_SetPinDriveMode(ResistiveTouch_xm_0, PIN_DM_ALG_HIZ);
    CyPins_SetPinDriveMode(ResistiveTouch_yp_0, PIN_DM_ALG_HIZ);
    CyPins_SetPinDriveMode(ResistiveTouch_ym_0, PIN_DM_STRONG);

    /* Add delay for signal to stabilize. The delay is dependant on whether
    * the measurement has been done before touch detect or not.
    */
    if (ResistiveTouch_measurementFlag == 0u)
    {
        CyDelayUs(20u);
    }
    else
    {
        ResistiveTouch_measurementFlag = 0u;
        CyDelayUs(8u);        
    }
    /* The screen is touched if the measured value is lower than the specified
    * threshold.
    */
    return ((ResistiveTouch_Measure() < ResistiveTouch_TOUCH_THRESHOLD) ? 1u : 0u);
}


/*******************************************************************************
* Function Name: ResistiveTouch_Measure
********************************************************************************
*
* Summary:
*  Returns the result of the ADC conversion. Does not return until ADC
*  conversion is complete.
*
* Parameters:
*  None
*
* Return:
*  int16: the result of the ADC conversion.
*
*******************************************************************************/
int16 ResistiveTouch_Measure(void) 
{       
    int16 result;

    /* Trigger the ADC conversion and wait for results (blocking). */
    ResistiveTouch_ADC_StartConvert();
    (void)ResistiveTouch_ADC_IsEndConversion(ResistiveTouch_ADC_WAIT_FOR_RESULT);
    result = ResistiveTouch_ADC_GetResult16();

    /* Assert a flag indicating that the measurement has been done. */
    ResistiveTouch_measurementFlag = 1u;
    return (result);
}


/* [] END OF FILE */
