/*******************************************************************************
* File Name: ResistiveTouch_PM.c
* Version 2.0
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "ResistiveTouch.h"


/*******************************************************************************
* Function Name: ResistiveTouch_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the ADC configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResistiveTouch_SaveConfig(void) 
{
    ResistiveTouch_ADC_SaveConfig();   
}


/*******************************************************************************
* Function Name: ResistiveTouch_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the ADC configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void ResistiveTouch_RestoreConfig(void) 
{
    ResistiveTouch_ADC_RestoreConfig();  
}


/*******************************************************************************
* Function Name: ResistiveTouch_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResistiveTouch_Sleep(void) 
{
    ResistiveTouch_ADC_Sleep();
    ResistiveTouch_AMux_Stop();
}


/*******************************************************************************
* Function Name: ResistiveTouch_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResistiveTouch_Wakeup(void)  
{
    ResistiveTouch_ADC_Wakeup();
}


/* [] END OF FILE */
