/*******************************************************************************
* File Name: Y_MINUS.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Y_MINUS_H) /* Pins Y_MINUS_H */
#define CY_PINS_Y_MINUS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Y_MINUS_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Y_MINUS__PORT == 15 && ((Y_MINUS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Y_MINUS_Write(uint8 value);
void    Y_MINUS_SetDriveMode(uint8 mode);
uint8   Y_MINUS_ReadDataReg(void);
uint8   Y_MINUS_Read(void);
void    Y_MINUS_SetInterruptMode(uint16 position, uint16 mode);
uint8   Y_MINUS_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Y_MINUS_SetDriveMode() function.
     *  @{
     */
        #define Y_MINUS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Y_MINUS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Y_MINUS_DM_RES_UP          PIN_DM_RES_UP
        #define Y_MINUS_DM_RES_DWN         PIN_DM_RES_DWN
        #define Y_MINUS_DM_OD_LO           PIN_DM_OD_LO
        #define Y_MINUS_DM_OD_HI           PIN_DM_OD_HI
        #define Y_MINUS_DM_STRONG          PIN_DM_STRONG
        #define Y_MINUS_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Y_MINUS_MASK               Y_MINUS__MASK
#define Y_MINUS_SHIFT              Y_MINUS__SHIFT
#define Y_MINUS_WIDTH              1u

/* Interrupt constants */
#if defined(Y_MINUS__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Y_MINUS_SetInterruptMode() function.
     *  @{
     */
        #define Y_MINUS_INTR_NONE      (uint16)(0x0000u)
        #define Y_MINUS_INTR_RISING    (uint16)(0x0001u)
        #define Y_MINUS_INTR_FALLING   (uint16)(0x0002u)
        #define Y_MINUS_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Y_MINUS_INTR_MASK      (0x01u) 
#endif /* (Y_MINUS__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Y_MINUS_PS                     (* (reg8 *) Y_MINUS__PS)
/* Data Register */
#define Y_MINUS_DR                     (* (reg8 *) Y_MINUS__DR)
/* Port Number */
#define Y_MINUS_PRT_NUM                (* (reg8 *) Y_MINUS__PRT) 
/* Connect to Analog Globals */                                                  
#define Y_MINUS_AG                     (* (reg8 *) Y_MINUS__AG)                       
/* Analog MUX bux enable */
#define Y_MINUS_AMUX                   (* (reg8 *) Y_MINUS__AMUX) 
/* Bidirectional Enable */                                                        
#define Y_MINUS_BIE                    (* (reg8 *) Y_MINUS__BIE)
/* Bit-mask for Aliased Register Access */
#define Y_MINUS_BIT_MASK               (* (reg8 *) Y_MINUS__BIT_MASK)
/* Bypass Enable */
#define Y_MINUS_BYP                    (* (reg8 *) Y_MINUS__BYP)
/* Port wide control signals */                                                   
#define Y_MINUS_CTL                    (* (reg8 *) Y_MINUS__CTL)
/* Drive Modes */
#define Y_MINUS_DM0                    (* (reg8 *) Y_MINUS__DM0) 
#define Y_MINUS_DM1                    (* (reg8 *) Y_MINUS__DM1)
#define Y_MINUS_DM2                    (* (reg8 *) Y_MINUS__DM2) 
/* Input Buffer Disable Override */
#define Y_MINUS_INP_DIS                (* (reg8 *) Y_MINUS__INP_DIS)
/* LCD Common or Segment Drive */
#define Y_MINUS_LCD_COM_SEG            (* (reg8 *) Y_MINUS__LCD_COM_SEG)
/* Enable Segment LCD */
#define Y_MINUS_LCD_EN                 (* (reg8 *) Y_MINUS__LCD_EN)
/* Slew Rate Control */
#define Y_MINUS_SLW                    (* (reg8 *) Y_MINUS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Y_MINUS_PRTDSI__CAPS_SEL       (* (reg8 *) Y_MINUS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Y_MINUS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Y_MINUS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Y_MINUS_PRTDSI__OE_SEL0        (* (reg8 *) Y_MINUS__PRTDSI__OE_SEL0) 
#define Y_MINUS_PRTDSI__OE_SEL1        (* (reg8 *) Y_MINUS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Y_MINUS_PRTDSI__OUT_SEL0       (* (reg8 *) Y_MINUS__PRTDSI__OUT_SEL0) 
#define Y_MINUS_PRTDSI__OUT_SEL1       (* (reg8 *) Y_MINUS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Y_MINUS_PRTDSI__SYNC_OUT       (* (reg8 *) Y_MINUS__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Y_MINUS__SIO_CFG)
    #define Y_MINUS_SIO_HYST_EN        (* (reg8 *) Y_MINUS__SIO_HYST_EN)
    #define Y_MINUS_SIO_REG_HIFREQ     (* (reg8 *) Y_MINUS__SIO_REG_HIFREQ)
    #define Y_MINUS_SIO_CFG            (* (reg8 *) Y_MINUS__SIO_CFG)
    #define Y_MINUS_SIO_DIFF           (* (reg8 *) Y_MINUS__SIO_DIFF)
#endif /* (Y_MINUS__SIO_CFG) */

/* Interrupt Registers */
#if defined(Y_MINUS__INTSTAT)
    #define Y_MINUS_INTSTAT            (* (reg8 *) Y_MINUS__INTSTAT)
    #define Y_MINUS_SNAP               (* (reg8 *) Y_MINUS__SNAP)
    
	#define Y_MINUS_0_INTTYPE_REG 		(* (reg8 *) Y_MINUS__0__INTTYPE)
#endif /* (Y_MINUS__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Y_MINUS_H */


/* [] END OF FILE */
