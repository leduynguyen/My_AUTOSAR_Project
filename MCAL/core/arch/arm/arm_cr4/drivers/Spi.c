/*-------------------------------- Arctic Core ------------------------------
 * Copyright (C) 2013, ArcCore AB, Sweden, www.arccore.com.
 * Contact: <contact@arccore.com>
 *
 * You may ONLY use this file:
 * 1)if you have a valid commercial ArcCore license and then in accordance with
 * the terms contained in the written license agreement between you and ArcCore,
 * or alternatively
 * 2)if you follow the terms found in GNU General Public License version 2 as
 * published by the Free Software Foundation and appearing in the file
 * LICENSE.GPL included in the packaging of this file or here
 * <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>
 *-------------------------------- Arctic Core -----------------------------*/

/** @tagSettings DEFAULT_ARCHITECTURE=TMS570 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#define SPI_SOURCE

#include "Spi.h"
#include "Spi_Hw.h"
#include "isr.h"
#include "irq_types.h"

#define SPI_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"

const Spi_ConfigType* Spi_ConfigPtr_pt = NULL_PTR;
volatile Spi_StatusType Spi_DrvStatus = SPI_UNINIT;

#define SPI_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"

#if (SPI_HARDWAREUNIT0_ACTIVE == STD_ON)
ISR(Spi_IrqUnit0TxRxERR);
ISR(Spi_IrqUnit0TxRx);
#endif
#if (SPI_HARDWAREUNIT1_ACTIVE == STD_ON)
ISR(Spi_IrqUnit1TxRxERR);
ISR(Spi_IrqUnit1TxRx);
#endif
#if (SPI_HARDWAREUNIT2_ACTIVE == STD_ON)
ISR(Spi_IrqUnit2TxRxERR);
ISR(Spi_IrqUnit2TxRx);
#endif
#if (SPI_HARDWAREUNIT3_ACTIVE == STD_ON)
ISR(Spi_IrqUnit3TxRxERR);
ISR(Spi_IrqUnit3TxRx);
#endif
#if (SPI_HARDWAREUNIT4_ACTIVE == STD_ON)
ISR(Spi_IrqUnit4TxRxERR);
ISR(Spi_IrqUnit4TxRx);
#endif
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
#if ((SPI_HARDWAREUNIT1_ACTIVE == STD_ON) || (SPI_HARDWAREUNIT3_ACTIVE == STD_ON))
ISR(Dma_IsrBTC);
#endif
#endif /* defined(CFG_TMS570LS12X) */

#define SPI_START_SEC_CODE
#include "MemMap.h"

/* Requirements : AR_SPI_SR138, AR_SPI_SR169, AR_SPI_SR170, AR_SPI_SR171, AR_SPI_SR172, AR_SPI_SR174, AR_SPI_SR96,
 * AR_SPI_SR102, AR_SPI_SR114 */
FUNC(void, SPI_CODE) Spi_Init
(
   P2CONST(Spi_ConfigType, AUTOMATIC, SPI_PBCFG) ConfigPtr
)
{
   uint32 Index_loc;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
   if (Spi_DrvStatus != SPI_UNINIT)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_INIT, SPI_E_ALREADY_INITIALIZED);
   }
   else if (NULL_PTR == ConfigPtr)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_INIT, SPI_E_PARAM_POINTER);
   }
   else
#endif
   {
      /* Store configuration pointer */
      Spi_ConfigPtr_pt = ConfigPtr;
      /* Initialize driver status */
      Spi_DrvStatus = SPI_IDLE;

      /* Initialize all DLC's status */
      for (Index_loc = 0U; Index_loc < Spi_ConfigPtr_pt->Spi_MaxDlcs; Index_loc++)
      {
         Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_DlcResult[Index_loc] = SPI_DLC_OK;
      }
      /* Initialize all Jobs status */
      for (Index_loc = 0U; Index_loc < Spi_ConfigPtr_pt->Spi_MaxJobs; Index_loc++)
      {
         Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_JobResult[Index_loc] = SPI_JOB_OK;
      }
      /* Initialize all Sequences status */
      for (Index_loc = 0U; Index_loc < Spi_ConfigPtr_pt->Spi_MaxSequences; Index_loc++)
      {
         Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_SeqResult[Index_loc] = SPI_SEQ_OK;
      }
      Spi_HwInit();
#if (SPI_HARDWAREUNIT0_ACTIVE == STD_ON)
    ISR_INSTALL_ISR2("SPI1Level0", Spi_IrqUnit0TxRxERR, SPI1_LVL0_INT, 2, 0);
    ISR_INSTALL_ISR2("SPI1Level1", Spi_IrqUnit0TxRx, SPI1_LVL1_INT, 2, 0);
#endif

#if (SPI_HARDWAREUNIT1_ACTIVE == STD_ON)
    ISR_INSTALL_ISR2("SPI2Level0", Spi_IrqUnit1TxRxERR, SPI2_LVL0_INT, 2, 0);
    ISR_INSTALL_ISR2("SPI2Level1", Spi_IrqUnit1TxRx, SPI2_LVL1_INT, 2, 0);
#endif

#if (SPI_HARDWAREUNIT2_ACTIVE == STD_ON)
    ISR_INSTALL_ISR2("SPI3Level0", Spi_IrqUnit2TxRxERR, SPI3_LVL0_INT, 2, 0);
    ISR_INSTALL_ISR2("SPI3Level1", Spi_IrqUnit2TxRx, SPI3_LVL1_INT, 2, 0);
#endif

#if (SPI_HARDWAREUNIT3_ACTIVE == STD_ON)
    ISR_INSTALL_ISR2("SPI4Level0", Spi_IrqUnit3TxRxERR, SPI4_LVL0_INT, 2, 0);
    ISR_INSTALL_ISR2("SPI4Level1", Spi_IrqUnit3TxRx, SPI4_LVL1_INT, 2, 0);
#endif

#if (SPI_HARDWAREUNIT4_ACTIVE == STD_ON)
    ISR_INSTALL_ISR2("SPI5Level0", Spi_IrqUnit4TxRxERR, SPI5_LVL0_INT, 2, 0);
    ISR_INSTALL_ISR2("SPI5Level1", Spi_IrqUnit4TxRx, SPI5_LVL1_INT, 2, 0);
#endif

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
#if ((SPI_HARDWAREUNIT1_ACTIVE == STD_ON) || (SPI_HARDWAREUNIT3_ACTIVE == STD_ON))
    ISR_INSTALL_ISR2("SpiDmaBtc", Dma_IsrBTC, SPI_DMABTC_INT, 2, 0);
#endif
#endif /* defined(CFG_TMS570LS12X) */
   }
}

/* Requirements : AR_SPI_SR176, AR_SPI_SR177, AR_SPI_SR178, AR_SPI_SR179, AR_SPI_SR180, AR_SPI_SR181, AR_SPI_SR182,
 * AR_SPI_SR183, AR_SPI_SR184, AR_SPI_SR93, AR_SPI_SR102, AR_SPI_SR112, AR_SPI_SR113 */
FUNC(Std_ReturnType, SPI_CODE) Spi_DeInit(void)
{
   Std_ReturnType deinit_return = E_NOT_OK;
   uint32 Index_loc;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
   if (Spi_DrvStatus  == SPI_UNINIT)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_DEINIT, SPI_E_UNINIT);
   }
   else
#endif
   {
      if (Spi_DrvStatus  == SPI_BUSY)
      {
         /* Do nothing */
      }
      else
      {
         Spi_DrvStatus  = SPI_UNINIT;
         for (Index_loc = 0U; Index_loc < Spi_ConfigPtr_pt->Spi_MaxDlcs; Index_loc++)
         {
            Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_DlcResult[Index_loc] = SPI_DLC_OK ;
         }
         for (Index_loc = 0U; Index_loc < Spi_ConfigPtr_pt->Spi_MaxJobs; Index_loc++)
         {
            Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_JobResult[Index_loc] = SPI_JOB_OK;
         }
         for (Index_loc = 0U; Index_loc < Spi_ConfigPtr_pt->Spi_MaxSequences; Index_loc++)
         {
            Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_SeqResult[Index_loc] = SPI_SEQ_OK;
         }
         Spi_HwDeInit();

         deinit_return = E_OK;
      }
   }
   return(deinit_return);
}

/* Requirements : AR_SPI_SR134, AR_SPI_SR137, AR_SPI_SR138, AR_SPI_SR139, AR_SPI_SR230, AR_SPI_SR232, AR_SPI_SR233 */
FUNC(Spi_StatusType, SPI_CODE) Spi_GetStatus(void)
{
#if (STD_ON == SPI_DEV_ERROR_DETECT)
   if (Spi_DrvStatus  == SPI_UNINIT)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETSTATUS_SERVICE_ID, SPI_E_UNINIT);
   }
#endif
   Spi_StatusType DrvStatusLoc = SPI_UNINIT;
   DrvStatusLoc = Spi_DrvStatus;
   return(DrvStatusLoc);
}

/* Requirements : AR_SPI_SR143, AR_SPI_SR145, AR_SPI_SR234, AR_SPI_SR236, AR_SPI_SR237, AR_SPI_SR89, AR_SPI_SR93,
 * AR_SPI_SR102, AR_SPI_SR106, AR_SPI_SR107, AR_SPI_SR112, AR_SPI_SR113 */
FUNC(Spi_JobResultType, SPI_CODE) Spi_GetJobResult
(
   Spi_JobType Job
)
{
   Spi_JobResultType get_job_result_return = SPI_JOB_FAILED;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
   if (Spi_DrvStatus  == SPI_UNINIT)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_GET_JOB_RESULT, SPI_E_UNINIT);
   }
   else if (Job >= Spi_ConfigPtr_pt->Spi_MaxJobs)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_GET_JOB_RESULT, SPI_E_PARAM_JOB);
   }
   else
#endif
   {
      get_job_result_return = Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_JobResult[Job];
   }
   return(get_job_result_return);
}

#if (SPI_HW_STATUS_API == STD_ON)
/* SourceId : SPI_SourceId_008 */
/* Requirements : AR_SPI_SR135, AR_SPI_SR140, AR_SPI_SR141, AR_SPI_SR92, AR_SPI_SR93, AR_SPI_SR102, AR_SPI_SR110,
 * AR_SPI_SR111, AR_SPI_SR112, AR_SPI_SR262, AR_SPI_SR263, AR_SPI_SR264, AR_SPI_SR265, AR_SPI_SR267 */
FUNC(Spi_StatusType, SPI_CODE) Spi_GetHWUnitStatus
(
   Spi_HWUnitType HWUnit
)
{
   Spi_StatusType get_hw_unit_status_return = SPI_UNINIT;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
   if (Spi_DrvStatus  == SPI_UNINIT)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_GET_UNIT_STATUS, SPI_E_UNINIT);
   }
   else if (HWUnit >= Spi_ConfigPtr_pt->Spi_MaxDlcs)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_GET_UNIT_STATUS, SPI_E_PARAM_UNIT);
   }
   else
#endif
   {
      switch(Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_DlcResult[HWUnit])
      {
         case SPI_DLC_PENDING:
            /* need to fall through here, both results are mapped to SPI_BUSY  */
         case SPI_DLC_FAILED:
            get_hw_unit_status_return = SPI_BUSY;
            break;
         case SPI_DLC_OK:
            get_hw_unit_status_return = SPI_IDLE;
            break;
         default:
            break;
      }
   }
   return(get_hw_unit_status_return);
}
#endif

/* Requirements : AR_SPI_SR146, AR_SPI_SR148, AR_SPI_SR150, AR_SPI_SR151, AR_SPI_SR152, AR_SPI_SR239, AR_SPI_SR90,
 * AR_SPI_SR93, AR_SPI_SR102, AR_SPI_SR106, AR_SPI_SR107, AR_SPI_SR112, AR_SPI_SR113, AR_SPI_SR240, AR_SPI_SR241,
 * AR_SPI_SR242 */
FUNC(Spi_SeqResultType, SPI_CODE) Spi_GetSequenceResult
(
   Spi_SequenceType Seq
)
{
   Spi_SeqResultType get_sequence_result_return = SPI_SEQ_FAILED;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
   if (Spi_DrvStatus  == SPI_UNINIT)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_GET_SEQ_RESULT, SPI_E_UNINIT);
   }
   else if (Seq >= Spi_ConfigPtr_pt->Spi_MaxSequences)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_GET_SEQ_RESULT, SPI_E_PARAM_SEQ);
   }
   else
#endif
   {
      get_sequence_result_return = Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_SeqResult[Seq];
   }

   return(get_sequence_result_return);
}

#if (SPI_VERSION_INFO_API == STD_ON)
/* SourceId : SPI_SourceId_010 */
/* Requirements : AR_SPI_SR102, AR_SPI_SR244, AR_SPI_SR245, AR_SPI_SR246, AR_SPI_SR247, AR_SPI_SR249, AR_SPI_SR250
 * AR_SPI_SR251 */
FUNC(void, SPI_CODE) Spi_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, SPI_APPL_DATA) VersioninfoPtr
)
{

#if (STD_ON == SPI_DEV_ERROR_DETECT)
   if (VersioninfoPtr == NULL_PTR)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_GETVERSION_INFO, SPI_E_PARAM_POINTER);
   }
   else
#endif
   {
      VersioninfoPtr->vendorID         = (uint16)( SPI_VENDOR_ID);
      VersioninfoPtr->moduleID         = (uint16)( SPI_MODULE_ID );
      VersioninfoPtr->sw_major_version = (uint8)( SPI_SW_MAJOR_VERSION);
      VersioninfoPtr->sw_minor_version = (uint8)( SPI_SW_MINOR_VERSION);
      VersioninfoPtr->sw_patch_version = (uint8)( SPI_SW_PATCH_VERSION);
   }
}
#endif

#if ((SPI_CHANNELBUFFERS == SPI_IB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))
/* Requirements : AR_SPI_SR88, AR_SPI_SR102, AR_SPI_SR105, AR_SPI_SR112, AR_SPI_SR113 */
FUNC(Std_ReturnType, SPI_CODE) Spi_WriteIB
(
   Spi_ChannelType Channel,
   P2CONST(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) DataBufferPtr
)
{
   Std_ReturnType write_ib_return = E_NOT_OK;

   uint16_least Index_loc;
   uint16_least Len_loc;
   uint16_least TxDefData_loc;
   uint16_least DataMode_loc;
   P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR_NOINIT) TxPtr_p;   /* pointer channel Tx data */


#if (STD_ON == SPI_DEV_ERROR_DETECT)
   if (Spi_DrvStatus  == SPI_UNINIT)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_WRITE_IB, SPI_E_UNINIT);
   }
   else if (  (Channel >= Spi_ConfigPtr_pt->Spi_MaxChannels)
           || (Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_ChannelBuf != SPI_IB))
   {
      /* channel must be valid */
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_WRITE_IB, SPI_E_PARAM_CHANNEL);
   }
   else
#endif
   {
      DataMode_loc  = Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_DataWidth;
      Len_loc       = Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_BufLength;
      TxDefData_loc = Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_DefaultTxData;
      TxPtr_p       = Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_Descriptor->Spi_Tx_pt;

      /* setup Rx and Tx length, the DLC module uses the generated lengths */
      Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_Descriptor->Spi_TxRxLength =
        Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_BufLength;
      if(DataBufferPtr == NULL_PTR)
      {
         if(TxPtr_p == NULL_PTR)
         {
            /* Do nothing */
         }
         else
         {
            /* copy default value */
            for(Index_loc=0U; Index_loc < Len_loc; Index_loc++)
            {
               if(DataMode_loc == 8U)
               {
                  *(TxPtr_p+Index_loc) = (uint8)TxDefData_loc;
               }
               else
               {
                  *(TxPtr_p+Index_loc) = (uint16)TxDefData_loc;
               }
            }
            write_ib_return = E_OK;
         }
      }
      else
      {
         /* only 8bit data buffers are handled, so the length has to be adjusted */
         if(DataMode_loc == 16U)
         {
            /* the length is automatically adjusted by the generation tool, adjust to 8bit length */
            Len_loc = Len_loc << 1U;
         }
         else
         {
            /* no action */
         }
         /* copy data to internal buffer */
         for(Index_loc=0U; Index_loc < Len_loc; Index_loc++)
         {
            *(Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_Descriptor->Spi_Tx_pt + Index_loc) =
                  *(DataBufferPtr + Index_loc);
         }

         write_ib_return = E_OK;
      }
   }
   return(write_ib_return);
}
#endif

#if ((SPI_CHANNELBUFFERS == SPI_IB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))
/* Requirements : AR_SPI_SR88, AR_SPI_SR102, AR_SPI_SR105, AR_SPI_SR112, AR_SPI_SR113 */
FUNC(Std_ReturnType, SPI_CODE) Spi_ReadIB
(
    Spi_ChannelType Channel,
    P2VAR(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) DataBufferPtr
)
{
   Std_ReturnType read_ib_return = E_NOT_OK;

   uint16_least Index_loc;
   uint16_least Len_loc;
   P2VAR(Spi_DataType, AUTOMATIC, SPI_VAR_NOINIT) RxPtr_p;   /* pointer channel Rx data */

#if (STD_ON == SPI_DEV_ERROR_DETECT)
   if (Spi_DrvStatus  == SPI_UNINIT)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_READ_IB, SPI_E_UNINIT);
   }
   else if (  (Channel >= Spi_ConfigPtr_pt->Spi_MaxChannels)
           || (Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_ChannelBuf != SPI_IB))
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_READ_IB, SPI_E_PARAM_CHANNEL);
   }
   else
#endif
   {
      if(Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_DataWidth == 8U)
      {
         Len_loc = Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_BufLength;
      }
      else
      {
         /* the length is automatically adjusted by the generation tool, adjust to 8bit length */
         Len_loc = (Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_BufLength << 1U);
      }
      RxPtr_p = Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_Descriptor->Spi_Rx_pt;
      /* setup Rx and Tx length, the DLC module uses the generated lengths */
      Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_Descriptor->Spi_TxRxLength =
        Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_BufLength;

      if(DataBufferPtr == NULL_PTR)
      {
         /* no data available */
         read_ib_return = E_OK;
      }
      else
      {
         if(RxPtr_p == NULL_PTR)
         {
            /* Do nothing */
         }
         else
         {
            for(Index_loc=0U; Index_loc < Len_loc; Index_loc++)
            {
               *(DataBufferPtr + Index_loc) = *(RxPtr_p + Index_loc);
            }
            read_ib_return = E_OK;
         }

      }
   }
   return(read_ib_return);
}
#endif

#if ((SPI_CHANNELBUFFERS == SPI_EB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))
/* Requirements : AR_SPI_SR42, AR_SPI_SR43, AR_SPI_SR220, AR_SPI_SR222, AR_SPI_SR223, AR_SPI_SR224, AR_SPI_SR225
 * AR_SPI_SR226, AR_SPI_SR227, AR_SPI_SR229, AR_SPI_SR88, AR_SPI_SR91, AR_SPI_SR93, AR_SPI_SR102, AR_SPI_SR105,
 * AR_SPI_SR108, AR_SPI_SR109, AR_SPI_SR112, AR_SPI_SR113 */
FUNC(Std_ReturnType, SPI_CODE) Spi_SetupEB
(
    Spi_ChannelType Channel,
    P2CONST(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) SrcDataBufferPtr,
    P2VAR(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) DesDataBufferPtr,
    Spi_NumberOfDataType Length
)
{
   Std_ReturnType setup_eb_return = E_NOT_OK;
   Spi_NumberOfDataType LengthEB_t;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
   if (Spi_DrvStatus  == SPI_UNINIT)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SETUP_EB, SPI_E_UNINIT);
   }
   else if (  (Channel >= Spi_ConfigPtr_pt->Spi_MaxChannels)
        || (Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_ChannelBuf != SPI_EB))
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SETUP_EB, SPI_E_PARAM_CHANNEL);
   }
   else
#endif
   {
      /* check for frame mode if the length is aligned */
      if(Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_DataWidth == 8U)
      {
         LengthEB_t = Length;
      }
      else
      {
#if (STD_ON == SPI_DEV_ERROR_DETECT)
         /* length must be even aligned in 16 or 32 bit mode */
         if(((Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_DataWidth == 32U) && ((Length % 4U) != 0U)) ||
            ((Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_DataWidth == 16U) && ((Length & 1U) == 1U)))
         {
            Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SETUP_EB, SPI_E_PARAM_LENGTH);
            return (setup_eb_return);
         }
         else
#endif
         {
            LengthEB_t = (Length >> 1U);
            /* buffers must be even aligned in 16 bit mode */
#if (STD_ON == SPI_DEV_ERROR_DETECT)
            {
               if(  (((uint32)SrcDataBufferPtr  & 1U) == 1U)
                 || (((uint32)DesDataBufferPtr & 1U) == 1U)  )
               {
                  Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SETUP_EB, SPI_E_PARAM_POINTER);
                  return (setup_eb_return);
               }
            }
#endif
         }
      }
      /* now check length */
#if (STD_ON == SPI_DEV_ERROR_DETECT)
      if ((Length == 0U) || (Length > Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_BufLength))
      {
         Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SETUP_EB, SPI_E_PARAM_LENGTH);
         setup_eb_return = E_NOT_OK;
      }
      else
#endif
      {
         Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_Descriptor->Spi_Tx_pt =
             (P2VAR(Spi_DataType, AUTOMATIC, SPI_APPL_DATA))SrcDataBufferPtr;
         Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_Descriptor->Spi_Rx_pt = DesDataBufferPtr;
         Spi_ConfigPtr_pt->Spi_ChannelCfg[Channel].Spi_Descriptor->Spi_TxRxLength = LengthEB_t;

         setup_eb_return = E_OK;
      }
   }
   return(setup_eb_return);
}
#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
/* Requirements : AR_SPI_SR22, AR_SPI_SR50, AR_SPI_SR51, AR_SPI_SR74, AR_SPI_SR194, AR_SPI_SR195, AR_SPI_SR196
 * AR_SPI_SR197, AR_SPI_SR198, AR_SPI_SR199, AR_SPI_SR200, AR_SPI_SR201, AR_SPI_SR202, AR_SPI_SR203, AR_SPI_SR204
 * AR_SPI_SR205, AR_SPI_SR206, AR_SPI_SR207, AR_SPI_SR209, AR_SPI_SR210, AR_SPI_SR90, AR_SPI_SR93, AR_SPI_SR94,
 * AR_SPI_SR102, AR_SPI_SR106, AR_SPI_SR112, AR_SPI_SR113 */
FUNC(Std_ReturnType, SPI_CODE) Spi_AsyncTransmit
(
    Spi_SequenceType Sequence
)
{
   Spi_HwEventType HwEv_loc;
   Std_ReturnType  Ret_loc = E_NOT_OK;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
   if (Spi_DrvStatus  == SPI_UNINIT)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_ASYNC_TRANSMIT, SPI_E_UNINIT);
   }
   else if(Sequence >= Spi_ConfigPtr_pt->Spi_MaxSequences)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_ASYNC_TRANSMIT, SPI_E_PARAM_SEQ);
   }
   else if(Spi_GetSequenceResult(Sequence) == SPI_SEQ_PENDING)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_ASYNC_TRANSMIT, SPI_E_SEQ_PENDING);
   }
   else
#endif
   {
      /* check jobs of this sequence, if they are in service */
      HwEv_loc.Event_u8   = SPI_HW_EV_SEQ_START;
      HwEv_loc.Guard_u8   = SPI_HW_ASYNC;
      HwEv_loc.TaskID_u8  = Sequence;
      HwEv_loc.NrOfJobs_u8 = 0U;

      Ret_loc = Spi_HwSetEvent(&HwEv_loc);

#if (STD_ON == SPI_DEV_ERROR_DETECT)
      if(Ret_loc == E_NOT_OK)
      {
         Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_ASYNC_TRANSMIT, SPI_E_SEQ_PENDING);
      }
#endif
   }
   return(Ret_loc);
}
#endif

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0)  || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
/* Requirements : AR_SPI_SR22, AR_SPI_SR74, AR_SPI_SR90, AR_SPI_SR95, AR_SPI_SR102, AR_SPI_SR106, AR_SPI_SR112,
 * AR_SPI_SR113, AR_SPI_SR252 */
FUNC(Std_ReturnType, SPI_CODE) Spi_SyncTransmit
(
    Spi_SequenceType Sequence
)
{
   Spi_HwEventType HwEv_loc;
   Std_ReturnType  Ret_loc = E_NOT_OK;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
   if (Spi_DrvStatus  == SPI_UNINIT)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SYNC_TRANSMIT, SPI_E_UNINIT);
   }
   else if(Sequence >= Spi_ConfigPtr_pt->Spi_MaxSequences)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SYNC_TRANSMIT, SPI_E_PARAM_SEQ);
   }
   else if(Spi_GetSequenceResult(Sequence) == SPI_SEQ_PENDING)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SYNC_TRANSMIT, SPI_E_SEQ_IN_PROCESS);
   }
   else
#endif
   {
      /* check jobs of this sequence, if they are in service */
      HwEv_loc.Event_u8  = SPI_HW_EV_SEQ_START;
      HwEv_loc.Guard_u8  = SPI_HW_SYNC;
      HwEv_loc.TaskID_u8 = Sequence;
      Ret_loc = Spi_HwSetEvent(&HwEv_loc);

#if (STD_ON == SPI_DEV_ERROR_DETECT)
      if(Ret_loc == E_NOT_OK)
      {
         Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SYNC_TRANSMIT, SPI_E_SEQ_IN_PROCESS);
      }
#endif
      while(Spi_GetSequenceResult(Sequence) == SPI_SEQ_PENDING)
      {
         Spi_HwProcessState(Spi_ConfigPtr_pt->Spi_SeqCfg[Sequence].Spi_JobList[0U]);
      }
   }

   return(Ret_loc);
}
#endif
#endif /* defined(CFG_TMS570LS12X) */

#if (SPI_CANCEL_API == STD_ON)
/* SourceId : SPI_SourceId_016 */
/* Requirements : AR_SPI_SR90, AR_SPI_SR93, AR_SPI_SR102, AR_SPI_SR106, AR_SPI_SR112, AR_SPI_SR268, AR_SPI_SR269,
 * AR_SPI_SR270 */
FUNC(void, SPI_CODE) Spi_Cancel
(
   Spi_SequenceType Sequence
)
{
   Spi_HwEventType HwEv_loc;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
   if (Spi_DrvStatus  == SPI_UNINIT)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_CANCEL, SPI_E_UNINIT);
   }
   else if(Sequence >= Spi_ConfigPtr_pt->Spi_MaxSequences)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_CANCEL, SPI_E_PARAM_SEQ);
   }
   else
#endif
   {
      HwEv_loc.Guard_u8 = 0U;
      HwEv_loc.NrOfJobs_u8 = 0U;
      HwEv_loc.Event_u8 = SPI_HW_EV_CANCEL;
      HwEv_loc.TaskID_u8 = Sequence;
      Spi_HwSetEvent(&HwEv_loc);
   }
}
#endif

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
/* SourceId : SPI_SourceId_017 */
/* Requirements : AR_SPI_SR274, AR_SPI_SR275, AR_SPI_SR276, AR_SPI_SR277, AR_SPI_SR280, AR_SPI_SR282 */
FUNC(Std_ReturnType, SPI_CODE) Spi_SetAsyncMode
(
   Spi_AsyncModeType Mode
)
{
#if (STD_ON == SPI_DEV_ERROR_DETECT)
   if (Spi_DrvStatus  == SPI_UNINIT)
   {
      Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SETASYNCMODE_SERVICE_ID, SPI_E_UNINIT);
   }
   return E_NOT_OK;
#endif
   Std_ReturnType set_async_mode_return = E_OK;

   if(Mode == SPI_INTERRUPT_MODE)
   {
      if(Spi_DrvStatus  == SPI_IDLE)
      {
         Spi_HwSetMode(Mode);
      }
      else
      {
         set_async_mode_return = E_NOT_OK;
      }
   }
   else
   {
      /* set new mode */
      Spi_HwSetMode(Mode);
   }

   return(set_async_mode_return);
}
#endif

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
/* SourceId : SPI_SourceId_018 */
/* Requirements : AR_SPI_SR283 */
FUNC(void, SPI_CODE) Spi_MainFunction_Handling(void)
{

}
#endif

#if (SPI_ENABLE_LOOPBACK_MODE_API == STD_ON)
/* SourceId : SPI_SourceId_071 */
/* Requirements : AR_SPI_SR322 */
FUNC(Std_ReturnType, SPI_CODE)  Spi_EnableLoopbackMode
(
   Spi_HWUnitType HWUnit,
   Spi_LoopbackModeType LBMode
)
{
   Std_ReturnType enable_loopback_mode_return = E_NOT_OK;

   /* Check if Spi driver already initialized*/
   if (Spi_DrvStatus != SPI_UNINIT)
   {
      /* Check requested HW Unit validity */
      if (HWUnit < Spi_ConfigPtr_pt->Spi_MaxDlcs)
      {
         Spi_DlcEnableLpbk(HWUnit, LBMode);

         enable_loopback_mode_return = E_OK;
      }
   }

   return(enable_loopback_mode_return);
}
#endif


#if (SPI_DISABLE_LOOPBACK_MODE_API == STD_ON)
/* Requirements : AR_SPI_SR322 */
FUNC(Std_ReturnType, SPI_CODE)  Spi_DisableLoopbackMode
(
   Spi_HWUnitType HWUnit
)
{
   Std_ReturnType disable_loopback_mode_return = E_NOT_OK;

   if (HWUnit < Spi_ConfigPtr_pt->Spi_MaxDlcs)
   {
      Spi_DlcDisableLpbk(HWUnit);

      disable_loopback_mode_return = E_OK;
   }

   return(disable_loopback_mode_return);
}
#endif

#if (SPI_REGISTER_READBACK_API == STD_ON)
/* Requirements : AR_SPI_SRXXX */
FUNC(Std_ReturnType, SPI_CODE) Spi_RegisterReadback
(
    P2VAR(Spi_RegisterReadbackType, AUTOMATIC, SPI_APPL_DATA) RegisterReadbackPtr,
    Spi_HWUnitType HWUnit
)
{
   Std_ReturnType register_readback_return = E_NOT_OK;

   if(NULL_PTR == RegisterReadbackPtr)
   {
      /* Do nothing. Incorrect pointer. */
   }
   else if(HWUnit >= Spi_ConfigPtr_pt->Spi_MaxDlcs)
   {
      /* Do nothing. Incorrect HW Unit. */
   }
   else
   {
      RegisterReadbackPtr->Spi_GCR0 = Spi_DlcRegisterRdbk(SPI_GCR0_RB, HWUnit);
      RegisterReadbackPtr->Spi_GCR1 = Spi_DlcRegisterRdbk(SPI_GCR1_RB, HWUnit);
      RegisterReadbackPtr->Spi_DEF  = Spi_DlcRegisterRdbk(SPI_DEF_RB, HWUnit);
      RegisterReadbackPtr->Spi_EN   = Spi_DlcRegisterRdbk(SPI_EN_RB, HWUnit);

      register_readback_return = E_OK;
   }

   return(register_readback_return);
}
#endif

#define SPI_STOP_SEC_CODE
#include "MemMap.h"
