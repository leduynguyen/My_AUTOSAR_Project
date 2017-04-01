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

#ifndef SPI_HW_H
#define SPI_HW_H

/* event definitions of the spi job statemachine */
typedef enum
{
    SPI_HW_EV_INIT = 0U,
    SPI_HW_EV_SEQ_START = 1U,
    SPI_HW_EV_JOB_START = 2U,
    SPI_HW_EV_JOB_FINISHED = 3U,
    SPI_HW_EV_CANCEL = 4U,
    SPI_HW_EV_FAILED = 5U,
    SPI_HW_EV_CONSUMED = 6U
} Spi_HwEventDefType;

typedef enum
{
    SPI_HW_UNDEF = 0U,
    SPI_HW_SYNC  = 1U,
    SPI_HW_ASYNC = 2U
} Spi_HwModeType;

/* forward declarations of structure types */
typedef struct Spi_JobSortedType_fd Spi_JobSortedType;
typedef struct Spi_HwEventType_fd   Spi_HwEventType;

/* event object definitions of the spi job state machine */
struct Spi_JobSortedType_fd
{
    P2VAR(Spi_JobSortedType, AUTOMATIC, SPI_VAR_NOINIT) JobNext_pt;   /* pointer to next job of a sequence */
    uint8  JobID_u8   ;   /* used to access job structure */
    uint8  SeqID_u8   ;   /* marks the job assigned to this sequence */
    uint8  JobStatus_u8 ; /* job internal status in the sorted priority queue */
};

/* event object definitions of the spi job state machine */
struct Spi_HwEventType_fd
{
    P2VAR(Spi_HwEventType, AUTOMATIC, SPI_VAR_NOINIT) SeqPrev_pt;
    P2VAR(Spi_HwEventType, AUTOMATIC, SPI_VAR_NOINIT) SeqNext_pt;
    volatile uint8 Event_u8;
    uint8  Guard_u8 ;
    uint8  TaskID_u8  ;   /* kind of job, sequence to execute, can be used for both */
    uint8  NrOfJobs_u8;   /* number of jobs, sequences */
};

typedef struct {
    uint8 SeqIdAkt_u8;  /* Id of the sequence, current being processed  */
    uint8 SeqIdPend_u8; /* Id of the sequence, pending                  */
    uint8 SeqIdRep_u8;  /* Id of the sequence, reported by job complete */
    uint8 SeqNrPend_u8; /* number of queued sequences */
} Spi_HwInstType ;

extern uint8 Spi_JobPrioConvTbl_at[];
extern Spi_JobSortedType Spi_JobsSorted_at[];
extern Spi_HwEventType Spi_HwSeqEvent_at[];

FUNC(Std_ReturnType, SPI_CODE) Spi_HwSetEvent
(
    P2CONST(Spi_HwEventType, AUTOMATIC, SPI_VAR)Hw_Event_pt
);
FUNC(void, SPI_CODE) Spi_HwInit(void);
FUNC(void, SPI_CODE) Spi_HwDeInit(void) ;
FUNC(void, SPI_CODE) Spi_HwProcessState(uint16_least HW_Inst_Nr_u8);
FUNC(void, SPI_CODE) Spi_HwJobComplete(uint16_least Job_u16, uint16_least DLC_u16) ;

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
FUNC(void, SPI_CODE) Spi_HwSetMode(Spi_AsyncModeType Mode);
#endif

#endif /* SPI_HW_H */
