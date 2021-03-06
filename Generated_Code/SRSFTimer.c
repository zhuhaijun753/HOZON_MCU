/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : SRSFTimer.c
**     Project     : mcu_app
**     Processor   : S32K144_100
**     Component   : ftm
**     Version     : Component SDK_S32K144_04, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32K144_04
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-01-13, 14:36, # CodeGen: 0
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     All Rights Reserved.
**     
**     THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
**     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
**     OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
**     IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
**     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**     SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
**     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
**     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
**     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
**     THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file SRSFTimer.c
** @version 01.00
*/
/*!
**  @addtogroup SRSFTimer_module SRSFTimer module documentation
**  @{
*/

/* Module SRSFTimer.
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 8.4, external symbol defined without a prior
 * declaration.
 * The symbols are declared in the driver header as external; the header is not included
 * by this file.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External variable could be made static.
 * The external variable will be used in other source files in application code.
 */

#include "SRSFTimer.h"


/* Callbacks declaration */
/* Channels configuration structure for SRSFTimer input capture */
  ftm_input_ch_param_t SRSFTimer_InputCaptureChannelConfig[1] =
{
    {
     4U, /* Channel id */
     FTM_SIGNAL_MEASUREMENT, /* Input capture operation mode */
     FTM_RISING_EDGE, /* Edge alignment mode */
     FTM_PERIOD_ON_MEASUREMENT, /* Signal measurement operation type */
     0U, /* Filter value */
     false, /* Filter state (enabled/disabled) */
     true,
     NULL,
     NULL
    }
};
/* Input capture configuration for SRSFTimer */
 ftm_input_param_t SRSFTimer_InputCaptureConfig =
{
     1U, /* Number of channels */
     65535U, /* Max count value */
     SRSFTimer_InputCaptureChannelConfig /* Channels configuration */
};
/* Timer mode configuration for SRSFTimer */
/* Global configuration of SRSFTimer */
ftm_user_config_t  SRSFTimer_InitConfig =
{
    {
        false,   /* Software trigger state */
        false,  /* Hardware trigger 1 state */
        false,  /* Hardware trigger 2 state */
        false,  /* Hardware trigger 3 state */
        false, /* Max loading point state */
        false, /* Min loading point state */
        FTM_SYSTEM_CLOCK, /* Update mode for INVCTRL register */
        FTM_SYSTEM_CLOCK, /* Update mode for SWOCTRL register */
        FTM_SYSTEM_CLOCK, /* Update mode for OUTMASK register */
        FTM_SYSTEM_CLOCK, /* Update mode for CNTIN register */
        false, /* Automatic clear of the trigger*/
        FTM_UPDATE_NOW, /* Synchronization point */
    },
     FTM_MODE_INPUT_CAPTURE, /*!< Mode of operation for FTM */
     FTM_CLOCK_DIVID_BY_32, /* FTM clock prescaler */
     FTM_CLOCK_SOURCE_EXTERNALCLK,   /* FTM clock source */
     FTM_BDM_MODE_11, /* FTM debug mode */
     false, /* Interrupt state */
     false /* Initialization trigger */
};

/* END SRSFTimer. */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the Freescale S32K series of microcontrollers.
**
** ###################################################################
*/

