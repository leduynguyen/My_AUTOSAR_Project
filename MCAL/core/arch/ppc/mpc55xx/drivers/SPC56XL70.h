/******************************************************************************\
 PARTID/PROJECT : MPC5643L / Leopard
 FILE           : mpc5643l.h
 FILE VERSION   : 3.01
 
 DESCRIPTION    : The content of this file provides register and other 
                  definitions for the above part and/or project.
 
 COPYRIGHT      : (c) 2009-2012, Freescale Semiconductor 

 RELEASE DATE   : Nov 05th, 2012
 
 AUTHOR         : Generated from the IP-XACT database
 DB VERSION     : 00.00.02.04 
 PARAMS VERSION : 0.00
 CREATION DATE  : Wed Oct 24 18:46:02 CEST 2012

   >>>>  NOTE! this file is auto-generated please do not edit it!  <<<< 

\******************************************************************************/

/******************************************************************************\

  FREESCALE SEMICONDUCTOR SOFTWARE LICENSE AGREEMENT                        
                                                                            
  This is a legal agreement between you (either as an individual or as an   
  authorized representative of your employer) and Freescale Semiconductor,  
  Inc. ("Freescale"). It concerns your rights to use this file and any      
  accompanying written materials (the "Software"). In consideration for     
  Freescale allowing you to access the Software, you are agreeing to be     
  bound by the terms of this Agreement. If you do not agree to all of the   
  terms of this Agreement, do not download the Software. If you change your 
  mind later, stop using the Software and delete all copies of the Software 
  in your possession or control. Any copies of the Software that you have   
  already distributed, where permitted, and do not destroy will continue to 
  be governed by this Agreement. Your prior use will also continue to be    
  governed by this Agreement.                                               
                                                                            
  LICENSE GRANT.  Freescale grants to you, free of charge, the non-         
  exclusive, non-transferable right (1) to use the Software, (2) to         
  reproduce the Software, (3) to prepare derivative works of the Software,  
  (4) to distribute the Software and derivative works thereof in source     
  (human-readable) form and object (machine-readable) form, and (5) to      
  sublicense to others the right to use the distributed Software. If you    
  violate any of the terms or restrictions of this Agreement, Freescale may 
  immediately terminate this Agreement, and require that you stop using and 
  delete all copies of the Software in your possession or control.          
                                                                            
  COPYRIGHT.  The Software is licensed to you, not sold. Freescale owns the 
  Software, and United States copyright laws and international treaty       
  provisions protect the Software. Therefore, you must treat the Software   
  like any other copyrighted material (e.g. a book or musical recording).   
  You may not use or copy the Software for any other purpose than what is   
  described in this Agreement. Except as expressly provided herein,         
  Freescale does not grant to you any express or implied rights under any   
  Freescale or third-party patents, copyrights, trademarks, or trade        
  secrets. Additionally, you must reproduce and apply any copyright or other
  proprietary rights notices included on or embedded in the Software to any 
  copies or derivative works made thereof, in whole or in part, if any.     
                                                                            
  SUPPORT.  Freescale is NOT obligated to provide any support, upgrades or  
  new releases of the Software. If you wish, you may contact Freescale and  
  report problems and provide suggestions regarding the Software. Freescale 
  has no obligation whatsoever to respond in any way to such a problem      
  report or suggestion. Freescale may make changes to the Software at any   
  time, without any obligation to notify or provide updated versions of the 
  Software to you.                                                          
                                                                            
  NO WARRANTY.  TO THE MAXIMUM EXTENT PERMITTED BY LAW, FREESCALE EXPRESSLY 
  DISCLAIMS ANY WARRANTY FOR THE SOFTWARE. THE SOFTWARE IS PROVIDED "AS IS",
  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,       
  WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
  A PARTICULAR PURPOSE, OR NON-INFRINGEMENT. YOU ASSUME THE ENTIRE RISK     
  ARISING OUT OF THE USE OR PERFORMANCE OF THE SOFTWARE, OR ANY SYSTEMS YOU 
  DESIGN USING THE SOFTWARE (IF ANY). NOTHING IN THIS AGREEMENT MAY BE      
  CONSTRUED AS A WARRANTY OR REPRESENTATION BY FREESCALE THAT THE SOFTWARE  
  OR ANY DERIVATIVE WORK DEVELOPED WITH OR INCORPORATING THE SOFTWARE WILL  
  BE FREE FROM INFRINGEMENT OF THE INTELLECTUAL PROPERTY RIGHTS OF THIRD    
  PARTIES.                                                                  
                                                                            
  INDEMNITY.  You agree to fully defend and indemnify Freescale from any and
  all claims, liabilities, and costs (including reasonable attorney's fees) 
  related to (1) your use (including your sublicensee's use, if permitted)  
  of the Software or (2) your violation of the terms and conditions of this 
  Agreement.                                                                
                                                                            
  LIMITATION OF LIABILITY.  IN NO EVENT WILL FREESCALE BE LIABLE, WHETHER IN
  CONTRACT, TORT, OR OTHERWISE, FOR ANY INCIDENTAL, SPECIAL, INDIRECT,      
  CONSEQUENTIAL OR PUNITIVE DAMAGES, INCLUDING, BUT NOT LIMITED TO, DAMAGES 
  FOR ANY LOSS OF USE, LOSS OF TIME, INCONVENIENCE, COMMERCIAL LOSS, OR LOST
  PROFITS, SAVINGS, OR REVENUES TO THE FULL EXTENT SUCH MAY BE DISCLAIMED BY
  LAW.                                                                      
                                                                            
  COMPLIANCE WITH LAWS; EXPORT RESTRICTIONS.  You must use the Software in  
  accordance with all applicable U.S. laws, regulations and statutes. You   
  agree that neither you nor your licensees (if any) intend to or will,     
  directly or indirectly, export or transmit the Software to any country in 
  violation of U.S. export restrictions.                                    
                                                                            
  GOVERNMENT USE.  Use of the Software and any corresponding documentation, 
  if any, is provided with RESTRICTED RIGHTS. Use, duplication or disclosure
  by the Government is subject to restrictions as set forth in subparagraph 
  (c)(1)(ii) of The Rights in Technical Data and Computer Software clause at
  DFARS 252.227-7013 or subparagraphs (c)(l) and (2) of the Commercial      
  Computer Software--Restricted Rights at 48 CFR 52.227-19, as applicable.  
  Manufacturer is Freescale Semiconductor, Inc., 6501 William Cannon Drive  
  West, Austin, TX, 78735.                                                  
                                                                            
  HIGH RISK ACTIVITIES.  You acknowledge that the Software is not fault     
  tolerant and is not designed, manufactured or intended by Freescale for   
  incorporation into products intended for use or resale in on-line control 
  equipment in hazardous, dangerous to life or potentially life-threatening 
  environments requiring fail-safe performance, such as in the operation of 
  nuclear facilities, aircraft navigation or communication systems, air     
  traffic control, direct life support machines or weapons systems, in which
  the failure of products could lead directly to death, personal injury or  
  severe physical or environmental damage ("High Risk Activities"). You     
  specifically represent and warrant that you will not use the Software or  
  any derivative work of the Software for High Risk Activities.             
                                                                            
  CHOICE OF LAW; VENUE; LIMITATIONS.  You agree that the statutes and laws  
  of the United States and the State of Texas, USA, without regard to       
  conflicts of laws principles, will apply to all matters relating to this  
  Agreement or the Software, and you agree that any litigation will be      
  subject to the exclusive jurisdiction of the state or federal courts in   
  Texas, USA. You agree that regardless of any statute or law to the        
  contrary, any claim or cause of action arising out of or related to this  
  Agreement or the Software must be filed within one (1) year after such    
  claim or cause of action arose or be forever barred.                      
                                                                            
  PRODUCT LABELING.  You are not authorized to use any Freescale trademarks,
  brand names, or logos.                                                   
                                                                           
  ENTIRE AGREEMENT.  This Agreement constitutes the entire agreement between
  you and Freescale regarding the subject matter of this Agreement, and     
  supersedes all prior communications, negotiations, understandings,        
  agreements or representations, either written or oral, if any. This       
  Agreement may only be amended in written form, executed by you and        
  Freescale.                                                                
                                                                            
  SEVERABILITY.  If any provision of this Agreement is held for any reason  
  to be invalid or unenforceable, then the remaining provisions of this     
  Agreement will be unimpaired and, unless a modification or replacement of 
  the invalid or unenforceable provision is further held to deprive you or  
  Freescale of a material benefit, in which case the Agreement will         
  immediately terminate, the invalid or unenforceable provision will be     
  replaced with a provision that is valid and enforceable and that comes    
  closest to the intention underlying the invalid or unenforceable          
  provision.                                                                
                                                                            
  NO WAIVER.  The waiver by Freescale of any breach of any provision of this
  Agreement will not operate or be construed as a waiver of any other or a  
  subsequent breach of the same or a different provision.                   
                                                                            
\******************************************************************************/


/****************************************************************************\
 * Example instantiation and use:            
 *                                           
 *  <MODULE>.<REGISTER>.B.<BIT> = 1;         
 *  <MODULE>.<REGISTER>.R       = 0x10000000;
 *                                           
\****************************************************************************/


/*** !!!!!!!!!!! IMPORTANT NOTE ABOUT THE CONTENT OF THIS FILE !!!!!!!!!!! ***\

  For some IP blocks in this file the register descriptions are written generic
  because they are not (yet) taking into account a particular parameterization
  done for a specific SoC. This means for some of the modules there might be
  a register defined or a field defined that does not exist on this particular
  SoC. We are in the process of capturing the dependencies between the SoC set
  of parameters and a particular IP instance.

  This is especially true for some highly parameterizable modules, like the
  MagicCarpet, the SIUL, the MAX, the PBRIDGE, etc.

\*** !!!!!!!!!!! IMPORTANT NOTE ABOUT THE CONTENT OF THIS FILE !!!!!!!!!!! ***/

/******************************************************************************\

 *** FILE HISTORY AND KNOWN ISSUES 

   MJR 24-Oct-2012:  
    * Major update in a new version 3.0, which tries to fix all known issues
      but also migrates to the new database reg_db, which allows a better and
      more detailed parameterization approach. Details see below.
    * global changes done:
      - removed compatibility entries to Pictus and for deprecated register and 
        field names 
      - added BASE_ADDRESS defines for usage by register protection macros
      - added crazy cast to fool the MISRA tool checker on the IP base entries
    * other modifications (high level)
      - STCU: added information about registers that need/should be accessed 
              for safety checks (as the one described in the SAG); all other 
              registers are declared as reserved and should not be accessed.
      - SWG: SGENDIG renamed to SWG to follow the RM
      - XBAR: MAX renamed to XBAR to follow the RM, parameterized to show only 
              valid masters and slaves (Note: HPE field not checked)
      - DMA_CH_MUX: renamed to DMAMUX, added parameterization, have 33 channels
      - eDMA: SPP_DMA2 renamed to eDMA, to align with RM; also modified most 
              register and field names accordingly. Had to change some field 
              names to have unique names; also improved some for better usability 
              (see SERQ register as an example). The MLOFF(NO/YES), and ELINK(NO/YES)
              variants for some TCD registers are not implemented.
      - FLASH: renamed from CFLASH to FLASH, 
               added parameterization, added EA field in UT0, names aligned to RM
      - CFLASH_SHADOW: removed useless description of DCF records
      - OSC: added parameterization, field OSCDIV is reserved now
      - ME: improved parameterization, aligned with RM (fields S_LIN_FLEXx changed to S_LINFLEXx)
      - DSPI: improved parameterization (mostly disable DSI registers, 4 CTAR registers)
      - SSCM: added parameterization, corrected size of KEY field in DPMKEY, added fields for UOPS
      - RGM: improved parameterization
      - CGM: improved parameterization
      - PCU: improved parameterization
      - mcPWM: improved parameterization (now capture A,B are correctly removed, 
               size of CVALxCYC corrected, FFULL+GSTR added)
      - LINFLEX: names and fields adapted to RM (docs team used these old names, 
                 although these were marked before as deprecated)
      - SWG: improved parameterization, fixed name of STAT register
      - FLEXRAY: improved parameterization, adapted some field names to RM value, 
                 correctly modeled the NMVP registers as byte regs
      - eTIMER: added instance specific parameterization, 
                renamed to eTIMER to be compliant to RM
      - ADC: added parameterization, exact channel assignment and usage (e.g. ch9 is for 
             factory test only) not yet covered, added WLSIDE1 variants
      - CTU: improved parameterization; aligned most names with RM, this is not done when 
             these names did already result in a conflict AND will be changed for 
             C55 designs (i.e. Panther) - in this case the C55 name is used already.
      - SPP_MCM: module name changed to ECSM to match the RM
      - FCCU: added parameterization, reflecting actually implemented CF/NCF
      - INTC: added parameterization, aligned most names with RM (when it makes sense, 
              do not add the useless PRC0 suffix), still a rough estimation
      - PMUCTRL: corrected available registers/bitfields
      - SIUL: improved parameterization;
         . however the Pad Control information is still a close approximation, 
              indiviual PAD registers are still not enabled.
         . the GPIO data registers are correct according to the SoC parameterization, 
              but do not match the RM (in the RM are less)
         . modeled the PGPDI and PGPDO registers as array of 16 bit registers, 
              which matches the use model of these registers (but no the RM)
      - INTC: improved parameterization; did not add the _PRC0 suffix to some field names 
              (does not make sense since there is only a single processor anyway)

   MJR 14-Mar-2011 - 17-Jun-2011:
    * Reviewed register list of the RGM and modified to fully match the actual
      parameterization done in RTL. Now all fields reflect the reality.
      Affected registers are: DERD, FEAR, DEAR (disappeared), FBRE
    * Reviewed PBRIDGE registers and adapted to parameterization; since there
      is no support for buffered writes, the BW and MBW fields disappear.
      Also aligned register map with implemented masters and slaves.
    * Reviewed the Crossbar MAX registers and aligned with implemented masters
      and slaves. Added RO field, HPE needs to be reviewed against RTL, still.
    * FlexCAN: added RXFIFO structure, adjusted MSG buffer accordingly.

   MJR 03-Mar-2011 - 14-Mar-2011:
    * reviewed the MCM registers and replaced generic versions of the registers
      with the actually implemented ones. 
      Fixed: added PLAMC, added PLAMS, fixed MUDCR, removed MWCR, MIR, 
             renamed PFEDR to PFEDRL and PREDR to PREDRL to match docu
      (#define based only) Fixed some of the related default values
    * adapted the ADC to be a close approximation of the actual, parameterized
      ADC. We now take all parameters into account and the registers seem to 
      match, but there are still some discrepancies in the bit fields.
    * reviewed the ME registers and corrected the most obvious issues in the
      definition: added the missing <mode>_MC register and bits for the TEST
                  mode, and removed non-existing peripheral control registers.
                  Also removed then non-existing STANDBY0_MC registers.
      For the #define based header file, fixed wrong default values and ro/rw
      settings for some of the bit fields.
    * reviewed the SEMA4 register set. There is one issue with the RSTGT and
      the RSTNTF registers; there is an overlay of read-only and write-only
      registers which are not properly handled by the IP-XACT generators.
      This results in a 23 bit wide structure for a 16 bit register.
    * reviewed the INTC register set. Removed registers and fields related to
      the second processor, since this is not enabled in LSM mode.
    * reviewed the PBRIDGE register set. Aligned it with the currently defined
      parameterization used in Leopard.
    * reviewed the eDMA setup. Cleaned up the very generic setup and aligned
      it with the parameterization used for Leopard. The definition of the TCD
      need to have a second review, there is some not-so-consistent setup for
      some of the fields here.
    * Added the READ_FROM_TFLASH macro and related definitions. These are used
      from the #define based header file used for verification purposes, so
      make sure to have appropriate setup functionality available.
    * reviewed the mcTIMER setup, removed some non-existing registers according
      to the parameterization, added new field to DREQ registers.

   MJR 04-Feb-2011:
    * (#define based only) Modified the default values for SIUL_MIDR1 and 
                           SSCM_MEMCONFIG to match cut-3 values
    * (#define based only) Fixed default value for OSC_CTL

   MJR 02-Dec-2010:
   Changes between the last version for the cut-1 device and this version:

    * Added entries for the DCF clients to the Shadow Flash Area
    * Fixed field sizes for the block selections in the Flash controller
    * Modified WKPU, now have the correctly parameterized block instead generic
    * Complete rehaul of the SSCM register structure, specific special test regs
    * Fixed some fields in the ME structure, remove of non-existing MC_STANDBY
    * Parameterized PLL, now PLL_ON bit is gone (parameter dependent)
    * Complete rehaul of the RGM, not have an exact match with parameterization
    * Fixed CDATA field in ADC
    * Corrected number of FIFO's in LINFlex
    * CRC modules allows now one more polynom, adjusted field size of POLYG
    * Some FCCU registers have been renamed to use a consistent naming scheme
      that avoid naming collisions in the #define based header
    * Field corrections in the Sine Wave Generator block
    * Added entries for the PFlash Controller
    * Fixed MPROT register in the PBRIGDE
    * Reflected the DSI functionality in the DSPI, corrected parameterization
    * Fixed SMBA in FlexRay
    * Many other minor fixes

 *** KNOWN ISSUES 

    * Register map of SIUL and INTC is still generic, parameterization is not
      fully applied (specific register details are not yet modeled). 
    * Due to usage of unnamed structs and #defines for compatibility reasons 
      this file is not fully MISRA-C compliant.

\******************************************************************************/

#ifndef _leopard_H_  /* prevents multiple inclusions of this file */ 
#define _leopard_H_

#include "typedefs.h"

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef __MWERKS__
#pragma push
#pragma ANSI_strict off
#endif

// #define USE_FIELD_ALIASES_LINFLEX
/****************************************************************/
/*                                                              */
/* Global definitions and aliases */
/*                                                              */
/****************************************************************/
 
/*
   Platform blocks that are only accessible by the second core (core 1) when
    the device is in DPM mode. The block definition is equivalent to the one
    for the first core (core 0) and reuses the related block structure.

   NOTE: the <block_name>_1 defines are the preferred method for programming
 */
#define  PBRIDGE_1     (*(volatile PBRIDGE_tag*)  0x8FF00000UL)
#define  XBAR_1        (*(volatile XBAR_tag*)     0x8FF04000UL)
#define  MPU_1         (*(volatile MPU_tag*)      0x8FF10000UL)
#define  SEMA4_1       (*(volatile SEMA4_tag*)    0x8FF24000UL)
#define  SWT_1         (*(volatile SWT_tag*)      0x8FF38000UL)
#define  STM_1         (*(volatile STM_tag*)      0x8FF3C000UL)
#define  ECSM_1        (*(volatile ECSM_tag*)     0x8FF40000UL)
#define  eDMA_1        (*(volatile eDMA_tag*)     0x8FF44000UL)
#define  INTC_1        (*(volatile INTC_tag*)     0x8FF48000UL)  

/*
   Platform blocks that are only accessible by the second core (core 1) when
    the device is in DPM mode. The block definition is equivalent to the one
    for the first core (core 0) and reuses the related block structure.

   NOTE: the <block_name>_DPM defines are deprecated, use <block_name>_1 for
         programming the corresponding blocks for new code instead.
 */
#define  PBRIDGE_DPM   PBRIDGE_1
#define  XBAR_DPM      XBAR_1
#define  MPU_DPM       MPU_1
#define  SEMA4_DPM     SEMA4_1
#define  SWT_DPM       SWT_1
#define  STM_DPM       STM_1
#define  ECSM_DPM      ECSM_1
#define  eDMA_DPM      eDMA_1
#define  INTC_DPM      INTC_1

#define INTC_BASEADDRESS 0xFFF48000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define INTC  (*(volatile struct INTC_tag*)     0xFFF48000UL)


/****************************************************************/
/*                                                              */
/* Module: CFLASH_SHADOW  */
/*                                                              */
/****************************************************************/


   /* Register layout for all registers NVPWD ... */

   typedef union {   /* NVPWD0-1 - Non Volatile Private Censorship PassWorD Register */
      vuint32_t R;
      struct {
         vuint32_t  PWD:32;            /* PassWorD */
      } B;
   } CFLASH_SHADOW_NVPWD_32B_tag;


   /* Register layout for all registers NVSCI ... */

   typedef union {   /* NVSCI - Non Volatile System Censoring Information Register */
      vuint32_t R;
      struct {
         vuint32_t  SC:16;             /* Serial Censorship Control Word */
         vuint32_t  CW:16;             /* Censorship Control Word */
      } B;
   } CFLASH_SHADOW_NVSCI_32B_tag;

   typedef union {   /* Non Volatile LML Default Value */
      vuint32_t R;
   } CFLASH_SHADOW_NVLML_32B_tag;

   typedef union {   /* Non Volatile HBL Default Value */
      vuint32_t R;
   } CFLASH_SHADOW_NVHBL_32B_tag;

   typedef union {   /* Non Volatile SLL Default Value */
      vuint32_t R;
   } CFLASH_SHADOW_NVSLL_32B_tag;


   /* Register layout for all registers NVBIU ... */

   typedef union {   /* Non Volatile Bus Interface Unit Register */
      vuint32_t R;
      struct {
         vuint32_t  BI:32;             /* Bus interface Unit */
      } B;
   } CFLASH_SHADOW_NVBIU_32B_tag;

   typedef union {   /* NVUSRO - Non Volatile USeR Options Register */
      vuint32_t R;
      struct {
         vuint32_t  UO:32;             /* User Options */
      } B;
   } CFLASH_SHADOW_NVUSRO_32B_tag;


   typedef struct CFLASH_SHADOW_BIU_DEFAULTS_struct_tag {

                             /* Non Volatile Bus Interface Unit Register */
      CFLASH_SHADOW_NVBIU_32B_tag NVBIU;   /* relative offset: 0x0000 */
      int8_t CFLASH_SHADOW_BIU_DEFAULTS_reserved_0004[4];

   } CFLASH_SHADOW_BIU_DEFAULTS_tag;



   typedef struct CFLASH_SHADOW_struct_tag {

      int8_t CFLASH_SHADOW_reserved_0000[15832];
      union {
         /* NVPWD0-1 - Non Volatile Private Censorship PassWorD Register */
         CFLASH_SHADOW_NVPWD_32B_tag NVPWD[2];  /* offset: 0x3DD8  (0x0004 x 2) */

         struct {
           /* NVPWD0-1 - Non Volatile Private Censorship PassWorD Register */
            CFLASH_SHADOW_NVPWD_32B_tag NVPWD0;  /* offset: 0x3DD8 size: 32 bit */
            CFLASH_SHADOW_NVPWD_32B_tag NVPWD1;  /* offset: 0x3DDC size: 32 bit */
         };

      };
      union {
           /* NVSCI - Non Volatile System Censoring Information Register */
         CFLASH_SHADOW_NVSCI_32B_tag NVSCI[2];  /* offset: 0x3DE0  (0x0004 x 2) */

         struct {
           /* NVSCI - Non Volatile System Censoring Information Register */
            CFLASH_SHADOW_NVSCI_32B_tag NVSCI0;  /* offset: 0x3DE0 size: 32 bit */
            CFLASH_SHADOW_NVSCI_32B_tag NVSCI1;  /* offset: 0x3DE4 size: 32 bit */
         };

      };
                                       /* Non Volatile LML Default Value */
      CFLASH_SHADOW_NVLML_32B_tag NVLML;   /* offset: 0x3DE8 size: 32 bit */
      int8_t CFLASH_SHADOW_reserved_3DEC[4];
                                       /* Non Volatile HBL Default Value */
      CFLASH_SHADOW_NVHBL_32B_tag NVHBL;   /* offset: 0x3DF0 size: 32 bit */
      int8_t CFLASH_SHADOW_reserved_3DF4[4];
                                       /* Non Volatile SLL Default Value */
      CFLASH_SHADOW_NVSLL_32B_tag NVSLL;   /* offset: 0x3DF8 size: 32 bit */
      int8_t CFLASH_SHADOW_reserved_3DFC[4];
      union {
                                           /*  Register set BIU_DEFAULTS */
         CFLASH_SHADOW_BIU_DEFAULTS_tag BIU_DEFAULTS[3];  /* offset: 0x3E00  (0x0008 x 3) */

         struct {
                             /* Non Volatile Bus Interface Unit Register */
            CFLASH_SHADOW_NVBIU_32B_tag NVBIU2;  /* offset: 0x3E00 size: 32 bit */
            int8_t CFLASH_SHADOW_reserved_3E04_I1[4];
            CFLASH_SHADOW_NVBIU_32B_tag NVBIU3;  /* offset: 0x3E08 size: 32 bit */
            int8_t CFLASH_SHADOW_reserved_3E0C_I1[4];
            CFLASH_SHADOW_NVBIU_32B_tag NVBIU4;  /* offset: 0x3E10 size: 32 bit */
            int8_t CFLASH_SHADOW_reserved_3E14_E1[4];
         };

      };
                          /* NVUSRO - Non Volatile USeR Options Register */
      CFLASH_SHADOW_NVUSRO_32B_tag NVUSRO;  /* offset: 0x3E18 size: 32 bit */
      int8_t CFLASH_SHADOW_reserved_3E1C[484];

   } CFLASH_SHADOW_tag;


#define CFLASH_SHADOW_BASEADDRESS 0x00F00000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define CFLASH_SHADOW (*(volatile CFLASH_SHADOW_tag *)(volatile void*) ((vuint8_t*)0UL + 0x00F00000UL))



/****************************************************************/
/*                                                              */
/* Module: FLASH  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Module Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t:5;
         vuint32_t  SIZE:3;            /* Array Space Size */
         vuint32_t:1;
         vuint32_t  LAS:3;             /* Low Address Space */
         vuint32_t:3;
         vuint32_t  MAS:1;             /* Mid Address Space Configuration */
         vuint32_t  EER:1;             /* ECC Event Error */
         vuint32_t  RWE:1;             /* Read-while-Write Event Error */
         vuint32_t  SBC:1;             /* Single Bit Correction */
         vuint32_t:1;
         vuint32_t  PEAS:1;            /* Program/Erase Access Space */
         vuint32_t  DONE:1;            /* modify operation DONE */
         vuint32_t  PEG:1;             /* Program/Erase Good */
         vuint32_t:4;
         vuint32_t  PGM:1;             /* Program Bit */
         vuint32_t  PSUS:1;            /* Program Suspend */
         vuint32_t  ERS:1;             /* Erase Bit */
         vuint32_t  ESUS:1;            /* Erase Suspend */
         vuint32_t  EHV:1;             /* Enable High Voltage */
      } B;
   } FLASH_MCR_32B_tag;

   typedef union {   /* LML - Low/Mid Address Space Block Locking Register */
      vuint32_t R;
      struct {
         vuint32_t  LME:1;             /* Low/Mid Address Space Block Enable */
         vuint32_t:10;
         vuint32_t  SLOCK:1;           /* Shadow Address Space Block Lock */
         vuint32_t:2;
         vuint32_t  MLOCK:2;           /* Mid Address Space Block Lock */
         vuint32_t:6;
         vuint32_t  LLOCK:10;          /* Low Address Space Block Lock */
      } B;
   } FLASH_LML_32B_tag;

   typedef union {   /* HBL - High Address Space Block Locking Register */
      vuint32_t R;
      struct {
         vuint32_t  HBE:1;             /* High Address Space Block Enable */
         vuint32_t:25;
         vuint32_t  HLOCK:6;           /* High Address Space Block Lock */
      } B;
   } FLASH_HBL_32B_tag;

   typedef union {   /* SLL - Secondary Low/Mid Address Space Block Locking Register */
      vuint32_t R;
      struct {
         vuint32_t  SLE:1;             /* Secondary Low/Mid Address Space Block Enable */
         vuint32_t:10;
         vuint32_t  SSLOCK:1;          /* Secondary Shadow Address Space Block Lock */
         vuint32_t:2;
         vuint32_t  SMLOCK:2;          /* Secondary Mid Address Space Block Lock */
         vuint32_t:6;
         vuint32_t  SLLOCK:10;         /* Secondary Low Address Space Block Lock */
      } B;
   } FLASH_SLL_32B_tag;

   typedef union {   /* LMS - Low/Mid Address Space Block Select Register */
      vuint32_t R;
      struct {
         vuint32_t:14;
         vuint32_t  MSEL:2;            /* Mid Address Space Block Select */
         vuint32_t:6;
         vuint32_t  LSEL:10;           /* Low Address Space Block Select */
      } B;
   } FLASH_LMS_32B_tag;

   typedef union {   /* HBS - High Address Space Block Select Register */
      vuint32_t R;
      struct {
         vuint32_t:26;
         vuint32_t  HSEL:6;            /* High Address Space Block Select */
      } B;
   } FLASH_HBS_32B_tag;

   typedef union {   /* ADR - Address Register */
      vuint32_t R;
      struct {
         vuint32_t  SAD:1;             /* Shadow Address */
         vuint32_t:10;
         vuint32_t  ADDR:18;           /* Address */
         vuint32_t:3;
      } B;
   } FLASH_ADR_32B_tag;

   typedef union {   /* Platform Flash Configuration Register 0 */
      vuint32_t R;
      struct {
         vuint32_t:2;
         vuint32_t  B02_APC:3;         /* Bank0+2 Address Pipelining Control */
         vuint32_t:3;
         vuint32_t  B02_WWSC:2;        /* Bank0+2 Write Wait State Control */
         vuint32_t:2;
         vuint32_t  B02_RWSC:3;        /* Bank0+2 Read Wait State Control */
         vuint32_t:2;
         vuint32_t  B02_P1_BCFG:2;     /* Bank0+2 Port 1 Page Buffer Configuration */
         vuint32_t  B02_P1_DPFE:1;     /* Bank0+2 Port 1 Data Prefetch Enable */
         vuint32_t  B02_P1_IPFE:1;     /* Bank0+2 Port 1 Inst Prefetch Enable */
         vuint32_t  B02_P1_PFLM:2;     /* Bank0+2 Port 1 Prefetch Limit */
         vuint32_t  B02_P1_BFE:1;      /* Bank0+2 Port 1 Buffer Enable */
         vuint32_t:1;
         vuint32_t  B02_P0_BCFG:2;     /* Bank0+2 Port 0 Page Buffer Configuration */
         vuint32_t  B02_P0_DPFE:1;     /* Bank0+2 Port 0 Data Prefetch Enable */
         vuint32_t  B02_P0_IPFE:1;     /* Bank0+2 Port 0 Inst Prefetch Enable */
         vuint32_t  B02_P0_PFLM:2;     /* Bank0+2 Port 0 Prefetch Limit */
         vuint32_t  B02_P0_BFE:1;      /* Bank0+2 Port 0 Buffer Enable */
      } B;
   } FLASH_PFCR0_32B_tag;

   typedef union {   /* Bus Interface Unit Register 0 */
      vuint32_t R;
   } FLASH_BIU0_32B_tag;

   typedef union {   /* Platform Flash Access Protection Register */
      vuint32_t R;
      struct {
         vuint32_t:6;
         vuint32_t  ARBM:2;            /* Arbitration Mode */
         vuint32_t:1;
         vuint32_t  M6PFD:1;           /* Master x Prefetch Disable */
         vuint32_t  M5PFD:1;           /* Master x Prefetch Disable */
         vuint32_t:1;
         vuint32_t  M3PFD:1;           /* Master x Prefetch Disable */
         vuint32_t  M2PFD:1;           /* Master x Prefetch Disable */
         vuint32_t  M1PFD:1;           /* Master x Prefetch Disable */
         vuint32_t  M0PFD:1;           /* Master x Prefetch Disable */
         vuint32_t:2;
         vuint32_t  M6AP:2;            /* Master 6 Access Protection */
         vuint32_t  M5AP:2;            /* Master 5 Access Protection */
         vuint32_t:2;
         vuint32_t  M3AP:2;            /* Master 3 Access Protection */
         vuint32_t  M2AP:2;            /* Master 2 Access Protection */
         vuint32_t  M1AP:2;            /* Master 1 Access Protection */
         vuint32_t  M0AP:2;            /* Master 0 Access Protection */
      } B;
   } FLASH_PFAPR_32B_tag;

   typedef union {   /* Bus Interface Unit Register 2 */
      vuint32_t R;
   } FLASH_BIU2_32B_tag;

   typedef union {   /* UT0 - User Test Register */
      vuint32_t R;
      struct {
         vuint32_t  UTE:1;             /* User Test Enable */
         vuint32_t  SBCE:1;            /* Single Bit Correction Enable */
         vuint32_t:6;
         vuint32_t  DSI:8;             /* Data Syndrome Input */
         vuint32_t:8;
         vuint32_t  EA:1;              /* ECC Algorith 1=modified Hsiao/0=modified Hamming */
         vuint32_t:1;
         vuint32_t  MRE:1;             /* Margin Read Enable */
         vuint32_t  MRV:1;             /* Margin Read Value */
         vuint32_t  EIE:1;             /* ECC Data Input Enable */
         vuint32_t  AIS:1;             /* Array Integrity Sequence */
         vuint32_t  AIE:1;             /* Array Integrity Enable */
         vuint32_t  AID:1;             /* Array Integrity Done */
      } B;
   } FLASH_UT0_32B_tag;

   typedef union {   /* UT1 - User Test Register */
      vuint32_t R;
   } FLASH_UT1_32B_tag;

   typedef union {   /* UT2 - User Test Register */
      vuint32_t R;
   } FLASH_UT2_32B_tag;


   /* Register layout for all registers UM ... */

   typedef union {   /* UM - User Multiple Input Signature Register */
      vuint32_t R;
      struct {
         vuint32_t  MISR:32;           /* Multiple Input Signature */
      } B;
   } FLASH_UM_32B_tag;

   typedef union {   /* UM - User Multiple Input Signature Register */
      vuint32_t R;
      struct {
         vuint32_t:15;
         vuint32_t  MISR_UMn:17;       /* Multiple Input Signature */
      } B;
   } FLASH_UM4_32B_tag;


   typedef struct FLASH_struct_tag {

                                        /* Module Configuration Register */
      FLASH_MCR_32B_tag MCR;               /* offset: 0x0000 size: 32 bit */
                   /* LML - Low/Mid Address Space Block Locking Register */
      FLASH_LML_32B_tag LML;               /* offset: 0x0004 size: 32 bit */
                      /* HBL - High Address Space Block Locking Register */
      FLASH_HBL_32B_tag HBL;               /* offset: 0x0008 size: 32 bit */
         /* SLL - Secondary Low/Mid Address Space Block Locking Register */
      FLASH_SLL_32B_tag SLL;               /* offset: 0x000C size: 32 bit */
                    /* LMS - Low/Mid Address Space Block Select Register */
      FLASH_LMS_32B_tag LMS;               /* offset: 0x0010 size: 32 bit */
                       /* HBS - High Address Space Block Select Register */
      FLASH_HBS_32B_tag HBS;               /* offset: 0x0014 size: 32 bit */
                                               /* ADR - Address Register */
      FLASH_ADR_32B_tag ADR;               /* offset: 0x0018 size: 32 bit */
      union {
                              /* Platform Flash Configuration Register 0 */
         FLASH_PFCR0_32B_tag PFCR0;        /* offset: 0x001C size: 32 bit */

                                        /* Bus Interface Unit Register 0 */
         FLASH_BIU0_32B_tag BIU0;          /* offset: 0x001C size: 32 bit */

      };
      int8_t FLASH_reserved_0020[4];
      union {
                            /* Platform Flash Access Protection Register */
         FLASH_PFAPR_32B_tag PFAPR;        /* offset: 0x0024 size: 32 bit */

                                        /* Bus Interface Unit Register 2 */
         FLASH_BIU2_32B_tag BIU2;          /* offset: 0x0024 size: 32 bit */

      };
      int8_t FLASH_reserved_0028[20];
                                             /* UT0 - User Test Register */
      FLASH_UT0_32B_tag UT0;               /* offset: 0x003C size: 32 bit */
                                             /* UT1 - User Test Register */
      FLASH_UT1_32B_tag UT1;               /* offset: 0x0040 size: 32 bit */
                                             /* UT2 - User Test Register */
      FLASH_UT2_32B_tag UT2;               /* offset: 0x0044 size: 32 bit */
      union {
                          /* UM - User Multiple Input Signature Register */
         FLASH_UM_32B_tag UM[5];           /* offset: 0x0048  (0x0004 x 5) */

         struct {
                          /* UM - User Multiple Input Signature Register */
            FLASH_UM_32B_tag UM0;          /* offset: 0x0048 size: 32 bit */
            FLASH_UM_32B_tag UM1;          /* offset: 0x004C size: 32 bit */
            FLASH_UM_32B_tag UM2;          /* offset: 0x0050 size: 32 bit */
            FLASH_UM_32B_tag UM3;          /* offset: 0x0054 size: 32 bit */
            FLASH_UM_32B_tag UM4;          /* offset: 0x0058 size: 32 bit */
         };

         struct {
            int8_t FLASH_reserved_0048_I2[16];
                          /* UM - User Multiple Input Signature Register */
            FLASH_UM4_32B_tag UM4_;         /* offset: 0x0058 size: 32 bit */
         };

      };
      int8_t FLASH_reserved_005C[16292];

   } FLASH_tag;


#define FLASH_BASEADDRESS 0xC3F88000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define FLASH (*(volatile FLASH_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3F88000UL))



/****************************************************************/
/*                                                              */
/* Module: SIUL  */
/*                                                              */
/****************************************************************/

   typedef union {   /* MCU ID Register #1 */
      vuint32_t R;
      struct {
         vuint32_t  PARTNUM:16;        /* MCU Part Number */
         vuint32_t  CSP:1;             /* CSP Package */
         vuint32_t  PKG:5;             /* Package Settings */
         vuint32_t:2;
         vuint32_t  MAJOR_MASK:4;      /* Major Mask Revision */
         vuint32_t  MINOR_MASK:4;      /* Minor Mask Revision */
      } B;
   } SIUL_MIDR1_32B_tag;

   typedef union {   /* MCU ID Register #2 */
      vuint32_t R;
      struct {
         vuint32_t  SF:1;              /* Manufacturer */
         vuint32_t  FLASH_SIZE_1:4;    /* Coarse Flash Memory Size */
         vuint32_t  FLASH_SIZE_2:4;    /* Fine Flash Memory Size */
         vuint32_t:7;
         vuint32_t  PARTNUM2:8;        /* MCU Part Number */
         vuint32_t:7;
         vuint32_t  FR:1;              /* Flexray Present */
      } B;
   } SIUL_MIDR2_32B_tag;

   typedef union {   /* Interrupt Status Flag Register */
      vuint32_t R;
      struct {
         vuint32_t  EIF31:1;           /* External Interrupt #31 Status Flag */
         vuint32_t  EIF30:1;           /* External Interrupt #30 Status Flag */
         vuint32_t  EIF29:1;           /* External Interrupt #29 Status Flag */
         vuint32_t  EIF28:1;           /* External Interrupt #28 Status Flag */
         vuint32_t  EIF27:1;           /* External Interrupt #27 Status Flag */
         vuint32_t  EIF26:1;           /* External Interrupt #26 Status Flag */
         vuint32_t  EIF25:1;           /* External Interrupt #25 Status Flag */
         vuint32_t  EIF24:1;           /* External Interrupt #24 Status Flag */
         vuint32_t  EIF23:1;           /* External Interrupt #23 Status Flag */
         vuint32_t  EIF22:1;           /* External Interrupt #22 Status Flag */
         vuint32_t  EIF21:1;           /* External Interrupt #21 Status Flag */
         vuint32_t  EIF20:1;           /* External Interrupt #20 Status Flag */
         vuint32_t  EIF19:1;           /* External Interrupt #19 Status Flag */
         vuint32_t  EIF18:1;           /* External Interrupt #18 Status Flag */
         vuint32_t  EIF17:1;           /* External Interrupt #17 Status Flag */
         vuint32_t  EIF16:1;           /* External Interrupt #16 Status Flag */
         vuint32_t  EIF15:1;           /* External Interrupt #15 Status Flag */
         vuint32_t  EIF14:1;           /* External Interrupt #14 Status Flag */
         vuint32_t  EIF13:1;           /* External Interrupt #13 Status Flag */
         vuint32_t  EIF12:1;           /* External Interrupt #12 Status Flag */
         vuint32_t  EIF11:1;           /* External Interrupt #11 Status Flag */
         vuint32_t  EIF10:1;           /* External Interrupt #10 Status Flag */
         vuint32_t  EIF9:1;            /* External Interrupt #9 Status Flag */
         vuint32_t  EIF8:1;            /* External Interrupt #8 Status Flag */
         vuint32_t  EIF7:1;            /* External Interrupt #7 Status Flag */
         vuint32_t  EIF6:1;            /* External Interrupt #6 Status Flag */
         vuint32_t  EIF5:1;            /* External Interrupt #5 Status Flag */
         vuint32_t  EIF4:1;            /* External Interrupt #4 Status Flag */
         vuint32_t  EIF3:1;            /* External Interrupt #3 Status Flag */
         vuint32_t  EIF2:1;            /* External Interrupt #2 Status Flag */
         vuint32_t  EIF1:1;            /* External Interrupt #1 Status Flag */
         vuint32_t  EIF0:1;            /* External Interrupt #0 Status Flag */
      } B;
   } SIUL_ISR_32B_tag;

   typedef union {   /* Interrupt Request Enable Register */
      vuint32_t R;
      struct {
         vuint32_t  EIRE31:1;          /* External Interrupt #31 Request Enable */
         vuint32_t  EIRE30:1;          /* External Interrupt #30 Request Enable */
         vuint32_t  EIRE29:1;          /* External Interrupt #29 Request Enable */
         vuint32_t  EIRE28:1;          /* External Interrupt #28 Request Enable */
         vuint32_t  EIRE27:1;          /* External Interrupt #27 Request Enable */
         vuint32_t  EIRE26:1;          /* External Interrupt #26 Request Enable */
         vuint32_t  EIRE25:1;          /* External Interrupt #25 Request Enable */
         vuint32_t  EIRE24:1;          /* External Interrupt #24 Request Enable */
         vuint32_t  EIRE23:1;          /* External Interrupt #23 Request Enable */
         vuint32_t  EIRE22:1;          /* External Interrupt #22 Request Enable */
         vuint32_t  EIRE21:1;          /* External Interrupt #21 Request Enable */
         vuint32_t  EIRE20:1;          /* External Interrupt #20 Request Enable */
         vuint32_t  EIRE19:1;          /* External Interrupt #19 Request Enable */
         vuint32_t  EIRE18:1;          /* External Interrupt #18 Request Enable */
         vuint32_t  EIRE17:1;          /* External Interrupt #17 Request Enable */
         vuint32_t  EIRE16:1;          /* External Interrupt #16 Request Enable */
         vuint32_t  EIRE15:1;          /* External Interrupt #15 Request Enable */
         vuint32_t  EIRE14:1;          /* External Interrupt #14 Request Enable */
         vuint32_t  EIRE13:1;          /* External Interrupt #13 Request Enable */
         vuint32_t  EIRE12:1;          /* External Interrupt #12 Request Enable */
         vuint32_t  EIRE11:1;          /* External Interrupt #11 Request Enable */
         vuint32_t  EIRE10:1;          /* External Interrupt #10 Request Enable */
         vuint32_t  EIRE9:1;           /* External Interrupt #9 Request Enable */
         vuint32_t  EIRE8:1;           /* External Interrupt #8 Request Enable */
         vuint32_t  EIRE7:1;           /* External Interrupt #7 Request Enable */
         vuint32_t  EIRE6:1;           /* External Interrupt #6 Request Enable */
         vuint32_t  EIRE5:1;           /* External Interrupt #5 Request Enable */
         vuint32_t  EIRE4:1;           /* External Interrupt #4 Request Enable */
         vuint32_t  EIRE3:1;           /* External Interrupt #3 Request Enable */
         vuint32_t  EIRE2:1;           /* External Interrupt #2 Request Enable */
         vuint32_t  EIRE1:1;           /* External Interrupt #1 Request Enable */
         vuint32_t  EIRE0:1;           /* External Interrupt #0 Request Enable */
      } B;
   } SIUL_IRER_32B_tag;

   typedef union {   /* Interrupt Rising Edge Event Enable Register */
      vuint32_t R;
      struct {
         vuint32_t  IREE31:1;          /* Enable rising-edge events for interrupt #31 */
         vuint32_t  IREE30:1;          /* Enable rising-edge events for interrupt #30 */
         vuint32_t  IREE29:1;          /* Enable rising-edge events for interrupt #29 */
         vuint32_t  IREE28:1;          /* Enable rising-edge events for interrupt #28 */
         vuint32_t  IREE27:1;          /* Enable rising-edge events for interrupt #27 */
         vuint32_t  IREE26:1;          /* Enable rising-edge events for interrupt #26 */
         vuint32_t  IREE25:1;          /* Enable rising-edge events for interrupt #25 */
         vuint32_t  IREE24:1;          /* Enable rising-edge events for interrupt #24 */
         vuint32_t  IREE23:1;          /* Enable rising-edge events for interrupt #23 */
         vuint32_t  IREE22:1;          /* Enable rising-edge events for interrupt #22 */
         vuint32_t  IREE21:1;          /* Enable rising-edge events for interrupt #21 */
         vuint32_t  IREE20:1;          /* Enable rising-edge events for interrupt #20 */
         vuint32_t  IREE19:1;          /* Enable rising-edge events for interrupt #19 */
         vuint32_t  IREE18:1;          /* Enable rising-edge events for interrupt #18 */
         vuint32_t  IREE17:1;          /* Enable rising-edge events for interrupt #17 */
         vuint32_t  IREE16:1;          /* Enable rising-edge events for interrupt #16 */
         vuint32_t  IREE15:1;          /* Enable rising-edge events for interrupt #15 */
         vuint32_t  IREE14:1;          /* Enable rising-edge events for interrupt #14 */
         vuint32_t  IREE13:1;          /* Enable rising-edge events for interrupt #13 */
         vuint32_t  IREE12:1;          /* Enable rising-edge events for interrupt #12 */
         vuint32_t  IREE11:1;          /* Enable rising-edge events for interrupt #11 */
         vuint32_t  IREE10:1;          /* Enable rising-edge events for interrupt #10 */
         vuint32_t  IREE9:1;           /* Enable rising-edge events for interrupt #9 */
         vuint32_t  IREE8:1;           /* Enable rising-edge events for interrupt #8 */
         vuint32_t  IREE7:1;           /* Enable rising-edge events for interrupt #7 */
         vuint32_t  IREE6:1;           /* Enable rising-edge events for interrupt #6 */
         vuint32_t  IREE5:1;           /* Enable rising-edge events for interrupt #5 */
         vuint32_t  IREE4:1;           /* Enable rising-edge events for interrupt #4 */
         vuint32_t  IREE3:1;           /* Enable rising-edge events for interrupt #3 */
         vuint32_t  IREE2:1;           /* Enable rising-edge events for interrupt #2 */
         vuint32_t  IREE1:1;           /* Enable rising-edge events for interrupt #1 */
         vuint32_t  IREE0:1;           /* Enable rising-edge events for interrupt #0 */
      } B;
   } SIUL_IREER_32B_tag;

   typedef union {   /* Interrupt Falling-Edge Event Enable Register */
      vuint32_t R;
      struct {
         vuint32_t  IFEE31:1;          /* Enable falling-edge events for interrupt #31 */
         vuint32_t  IFEE30:1;          /* Enable falling-edge events for interrupt #30 */
         vuint32_t  IFEE29:1;          /* Enable falling-edge events for interrupt #29 */
         vuint32_t  IFEE28:1;          /* Enable falling-edge events for interrupt #28 */
         vuint32_t  IFEE27:1;          /* Enable falling-edge events for interrupt #27 */
         vuint32_t  IFEE26:1;          /* Enable falling-edge events for interrupt #26 */
         vuint32_t  IFEE25:1;          /* Enable falling-edge events for interrupt #25 */
         vuint32_t  IFEE24:1;          /* Enable falling-edge events for interrupt #24 */
         vuint32_t  IFEE23:1;          /* Enable falling-edge events for interrupt #23 */
         vuint32_t  IFEE22:1;          /* Enable falling-edge events for interrupt #22 */
         vuint32_t  IFEE21:1;          /* Enable falling-edge events for interrupt #21 */
         vuint32_t  IFEE20:1;          /* Enable falling-edge events for interrupt #20 */
         vuint32_t  IFEE19:1;          /* Enable falling-edge events for interrupt #19 */
         vuint32_t  IFEE18:1;          /* Enable falling-edge events for interrupt #18 */
         vuint32_t  IFEE17:1;          /* Enable falling-edge events for interrupt #17 */
         vuint32_t  IFEE16:1;          /* Enable falling-edge events for interrupt #16 */
         vuint32_t  IFEE15:1;          /* Enable falling-edge events for interrupt #15 */
         vuint32_t  IFEE14:1;          /* Enable falling-edge events for interrupt #14 */
         vuint32_t  IFEE13:1;          /* Enable falling-edge events for interrupt #13 */
         vuint32_t  IFEE12:1;          /* Enable falling-edge events for interrupt #12 */
         vuint32_t  IFEE11:1;          /* Enable falling-edge events for interrupt #11 */
         vuint32_t  IFEE10:1;          /* Enable falling-edge events for interrupt #10 */
         vuint32_t  IFEE9:1;           /* Enable falling-edge events for interrupt #9 */
         vuint32_t  IFEE8:1;           /* Enable falling-edge events for interrupt #8 */
         vuint32_t  IFEE7:1;           /* Enable falling-edge events for interrupt #7 */
         vuint32_t  IFEE6:1;           /* Enable falling-edge events for interrupt #6 */
         vuint32_t  IFEE5:1;           /* Enable falling-edge events for interrupt #5 */
         vuint32_t  IFEE4:1;           /* Enable falling-edge events for interrupt #4 */
         vuint32_t  IFEE3:1;           /* Enable falling-edge events for interrupt #3 */
         vuint32_t  IFEE2:1;           /* Enable falling-edge events for interrupt #2 */
         vuint32_t  IFEE1:1;           /* Enable falling-edge events for interrupt #1 */
         vuint32_t  IFEE0:1;           /* Enable falling-edge events for interrupt #0 */
      } B;
   } SIUL_IFEER_32B_tag;

   typedef union {   /* Interrupt Filter Enable Register */
      vuint32_t R;
      struct {
         vuint32_t  IFE31:1;           /* Enable Digital Glitch Filter for interrupt #31 */
         vuint32_t  IFE30:1;           /* Enable Digital Glitch Filter for interrupt #30 */
         vuint32_t  IFE29:1;           /* Enable Digital Glitch Filter for interrupt #29 */
         vuint32_t  IFE28:1;           /* Enable Digital Glitch Filter for interrupt #28 */
         vuint32_t  IFE27:1;           /* Enable Digital Glitch Filter for interrupt #27 */
         vuint32_t  IFE26:1;           /* Enable Digital Glitch Filter for interrupt #26 */
         vuint32_t  IFE25:1;           /* Enable Digital Glitch Filter for interrupt #25 */
         vuint32_t  IFE24:1;           /* Enable Digital Glitch Filter for interrupt #24 */
         vuint32_t  IFE23:1;           /* Enable Digital Glitch Filter for interrupt #23 */
         vuint32_t  IFE22:1;           /* Enable Digital Glitch Filter for interrupt #22 */
         vuint32_t  IFE21:1;           /* Enable Digital Glitch Filter for interrupt #21 */
         vuint32_t  IFE20:1;           /* Enable Digital Glitch Filter for interrupt #20 */
         vuint32_t  IFE19:1;           /* Enable Digital Glitch Filter for interrupt #19 */
         vuint32_t  IFE18:1;           /* Enable Digital Glitch Filter for interrupt #18 */
         vuint32_t  IFE17:1;           /* Enable Digital Glitch Filter for interrupt #17 */
         vuint32_t  IFE16:1;           /* Enable Digital Glitch Filter for interrupt #16 */
         vuint32_t  IFE15:1;           /* Enable Digital Glitch Filter for interrupt #15 */
         vuint32_t  IFE14:1;           /* Enable Digital Glitch Filter for interrupt #14 */
         vuint32_t  IFE13:1;           /* Enable Digital Glitch Filter for interrupt #13 */
         vuint32_t  IFE12:1;           /* Enable Digital Glitch Filter for interrupt #12 */
         vuint32_t  IFE11:1;           /* Enable Digital Glitch Filter for interrupt #11 */
         vuint32_t  IFE10:1;           /* Enable Digital Glitch Filter for interrupt #10 */
         vuint32_t  IFE9:1;            /* Enable Digital Glitch Filter for interrupt #9 */
         vuint32_t  IFE8:1;            /* Enable Digital Glitch Filter for interrupt #8 */
         vuint32_t  IFE7:1;            /* Enable Digital Glitch Filter for interrupt #7 */
         vuint32_t  IFE6:1;            /* Enable Digital Glitch Filter for interrupt #6 */
         vuint32_t  IFE5:1;            /* Enable Digital Glitch Filter for interrupt #5 */
         vuint32_t  IFE4:1;            /* Enable Digital Glitch Filter for interrupt #4 */
         vuint32_t  IFE3:1;            /* Enable Digital Glitch Filter for interrupt #3 */
         vuint32_t  IFE2:1;            /* Enable Digital Glitch Filter for interrupt #2 */
         vuint32_t  IFE1:1;            /* Enable Digital Glitch Filter for interrupt #1 */
         vuint32_t  IFE0:1;            /* Enable Digital Glitch Filter for interrupt #0 */
      } B;
   } SIUL_IFER_32B_tag;


   /* Register layout for all registers PCR ... */

   typedef union {   /* Pad Configuration Register */
      vuint16_t R;
      struct {
         vuint16_t:1;
         vuint16_t  SMC:1;             /* Safe Mode Control */
         vuint16_t  APC:1;             /* Analog Pad Control */
         vuint16_t:1;
         vuint16_t  PA:2;              /* Pad Output Assignment */
         vuint16_t  OBE:1;             /* Output Buffer Enable */
         vuint16_t  IBE:1;             /* Input Buffer Enable */
         vuint16_t:2;
         vuint16_t  ODE:1;             /* Open Drain Enable */
         vuint16_t:2;
         vuint16_t  SRC:1;             /* Slew Rate Control (0=slow,1=fast) */
         vuint16_t  WPE:1;             /* Weak Pull Enable */
         vuint16_t  WPS:1;             /* Weak Pull Select */
      } B;
   } SIUL_PCR_16B_tag;


   /* Register layout for all registers PSMI ... */

   typedef union {   /* Pad Selection for Multiplexed Inputs (combined 32 bit version) */
      vuint32_t R;
      struct {
         vuint32_t:4;
         vuint32_t  PADSEL0:4;         /* Source Signal Select */
         vuint32_t:4;
         vuint32_t  PADSEL1:4;         /* Source Signal Select */
         vuint32_t:4;
         vuint32_t  PADSEL2:4;         /* Source Signal Select */
         vuint32_t:4;
         vuint32_t  PADSEL3:4;         /* Source Signal Select */
      } B;
   } SIUL_PSMI_32B_tag;


   /* Register layout for all registers PSMI ... */

   typedef union {   /* Pad Selection for Multiplexed Inputs */
      vuint8_t R;
      struct {
         vuint8_t:4;
         vuint8_t   PADSEL:4;          /* Source Signal Select */
      } B;
   } SIUL_PSMI_8B_tag;


   /* Register layout for all registers GPDO ... */

   typedef union {   /* GPIO Pad Data Output Register (combined 32 bit version) */
      vuint32_t R;
      struct {
         vuint32_t:7;
         vuint32_t  PDO0:1;            /* Pad Data Out */
         vuint32_t:7;
         vuint32_t  PDO1:1;            /* Pad Data Out */
         vuint32_t:7;
         vuint32_t  PDO2:1;            /* Pad Data Out */
         vuint32_t:7;
         vuint32_t  PDO3:1;            /* Pad Data Out */
      } B;
   } SIUL_GPDO_32B_tag;


   /* Register layout for all registers GPDO ... */

   typedef union {   /* GPIO Pad Data Output Register */
      vuint8_t R;
      struct {
         vuint8_t:7;
         vuint8_t   PDO:1;             /* Pad Data Out */
      } B;
   } SIUL_GPDO_8B_tag;


   /* Register layout for all registers GPDI ... */

   typedef union {   /* GPIO Pad Data Input Register */
      vuint8_t R;
      struct {
         vuint8_t:7;
         vuint8_t   PDI:1;             /* Pad Data In */
      } B;
   } SIUL_GPDI_8B_tag;


   /* Register layout for all registers GPDI ... */

   typedef union {   /* GPIO Pad Data Input Register (combined 32 bit version) */
      vuint32_t R;
      struct {
         vuint32_t:7;
         vuint32_t  PDI0:1;            /* Pad Data In */
         vuint32_t:7;
         vuint32_t  PDI1:1;            /* Pad Data In */
         vuint32_t:7;
         vuint32_t  PDI2:1;            /* Pad Data In */
         vuint32_t:7;
         vuint32_t  PDI3:1;            /* Pad Data In */
      } B;
   } SIUL_GPDI_32B_tag;


   /* Register layout for all registers PGPDO ... */

   typedef union {   /* Parallel GPIO Pad Data Out Register */
      vuint16_t R;
   } SIUL_PGPDO_16B_tag;


   /* Register layout for all registers PGPDI ... */

   typedef union {   /* Parallel GPIO Pad Data In Register */
      vuint16_t R;
   } SIUL_PGPDI_16B_tag;


   /* Register layout for all registers MPGPDO ... */

   typedef union {   /* Masked Parallel GPIO Pad Data Out Register */
      vuint32_t R;
      struct {
         vuint32_t  MASK:16;           /* Mask Field */
         vuint32_t  MPPDO:16;          /* Masked Parallel Pad Data Out */
      } B;
   } SIUL_MPGPDO_32B_tag;


   /* Register layout for all registers IFMCR ... */

   typedef union {   /* Interrupt Filter Maximum Counter Register */
      vuint32_t R;
      struct {
         vuint32_t:28;
         vuint32_t  MAXCNT:4;          /* Maximum Interrupt Filter Counter setting */
      } B;
   } SIUL_IFMCR_32B_tag;

   typedef union {   /* Interrupt Filter Clock Prescaler Register */
      vuint32_t R;
      struct {
         vuint32_t:28;
         vuint32_t  IFCP:4;            /* Interrupt Filter Clock Prescaler setting */
      } B;
   } SIUL_IFCPR_32B_tag;


   typedef struct SIUL_struct_tag {

      int8_t SIUL_reserved_0000[4];
                                                   /* MCU ID Register #1 */
      SIUL_MIDR1_32B_tag MIDR;            /* offset: 0x0004 size: 32 bit */ /* Renamed from MIDR1 to simplify code reuse */
                                                   /* MCU ID Register #2 */
      SIUL_MIDR2_32B_tag MIDR2;            /* offset: 0x0008 size: 32 bit */
      int8_t SIUL_reserved_000C[8];
                                       /* Interrupt Status Flag Register */
      SIUL_ISR_32B_tag ISR;                /* offset: 0x0014 size: 32 bit */
                                    /* Interrupt Request Enable Register */
      SIUL_IRER_32B_tag IRER;              /* offset: 0x0018 size: 32 bit */
      int8_t SIUL_reserved_001C[12];
                          /* Interrupt Rising Edge Event Enable Register */
      SIUL_IREER_32B_tag IREER;            /* offset: 0x0028 size: 32 bit */
                         /* Interrupt Falling-Edge Event Enable Register */
      SIUL_IFEER_32B_tag IFEER;            /* offset: 0x002C size: 32 bit */
                                     /* Interrupt Filter Enable Register */
      SIUL_IFER_32B_tag IFER;              /* offset: 0x0030 size: 32 bit */
      int8_t SIUL_reserved_0034[12];
      union {
                                           /* Pad Configuration Register */
         SIUL_PCR_16B_tag PCR[133];        /* offset: 0x0040  (0x0002 x 133) */

         struct {
                                           /* Pad Configuration Register */
            SIUL_PCR_16B_tag PCR0;         /* offset: 0x0040 size: 16 bit */
            SIUL_PCR_16B_tag PCR1;         /* offset: 0x0042 size: 16 bit */
            SIUL_PCR_16B_tag PCR2;         /* offset: 0x0044 size: 16 bit */
            SIUL_PCR_16B_tag PCR3;         /* offset: 0x0046 size: 16 bit */
            SIUL_PCR_16B_tag PCR4;         /* offset: 0x0048 size: 16 bit */
            SIUL_PCR_16B_tag PCR5;         /* offset: 0x004A size: 16 bit */
            SIUL_PCR_16B_tag PCR6;         /* offset: 0x004C size: 16 bit */
            SIUL_PCR_16B_tag PCR7;         /* offset: 0x004E size: 16 bit */
            SIUL_PCR_16B_tag PCR8;         /* offset: 0x0050 size: 16 bit */
            SIUL_PCR_16B_tag PCR9;         /* offset: 0x0052 size: 16 bit */
            SIUL_PCR_16B_tag PCR10;        /* offset: 0x0054 size: 16 bit */
            SIUL_PCR_16B_tag PCR11;        /* offset: 0x0056 size: 16 bit */
            SIUL_PCR_16B_tag PCR12;        /* offset: 0x0058 size: 16 bit */
            SIUL_PCR_16B_tag PCR13;        /* offset: 0x005A size: 16 bit */
            SIUL_PCR_16B_tag PCR14;        /* offset: 0x005C size: 16 bit */
            SIUL_PCR_16B_tag PCR15;        /* offset: 0x005E size: 16 bit */
            SIUL_PCR_16B_tag PCR16;        /* offset: 0x0060 size: 16 bit */
            SIUL_PCR_16B_tag PCR17;        /* offset: 0x0062 size: 16 bit */
            SIUL_PCR_16B_tag PCR18;        /* offset: 0x0064 size: 16 bit */
            SIUL_PCR_16B_tag PCR19;        /* offset: 0x0066 size: 16 bit */
            SIUL_PCR_16B_tag PCR20;        /* offset: 0x0068 size: 16 bit */
            SIUL_PCR_16B_tag PCR21;        /* offset: 0x006A size: 16 bit */
            SIUL_PCR_16B_tag PCR22;        /* offset: 0x006C size: 16 bit */
            SIUL_PCR_16B_tag PCR23;        /* offset: 0x006E size: 16 bit */
            SIUL_PCR_16B_tag PCR24;        /* offset: 0x0070 size: 16 bit */
            SIUL_PCR_16B_tag PCR25;        /* offset: 0x0072 size: 16 bit */
            SIUL_PCR_16B_tag PCR26;        /* offset: 0x0074 size: 16 bit */
            SIUL_PCR_16B_tag PCR27;        /* offset: 0x0076 size: 16 bit */
            SIUL_PCR_16B_tag PCR28;        /* offset: 0x0078 size: 16 bit */
            SIUL_PCR_16B_tag PCR29;        /* offset: 0x007A size: 16 bit */
            SIUL_PCR_16B_tag PCR30;        /* offset: 0x007C size: 16 bit */
            SIUL_PCR_16B_tag PCR31;        /* offset: 0x007E size: 16 bit */
            SIUL_PCR_16B_tag PCR32;        /* offset: 0x0080 size: 16 bit */
            SIUL_PCR_16B_tag PCR33;        /* offset: 0x0082 size: 16 bit */
            SIUL_PCR_16B_tag PCR34;        /* offset: 0x0084 size: 16 bit */
            SIUL_PCR_16B_tag PCR35;        /* offset: 0x0086 size: 16 bit */
            SIUL_PCR_16B_tag PCR36;        /* offset: 0x0088 size: 16 bit */
            SIUL_PCR_16B_tag PCR37;        /* offset: 0x008A size: 16 bit */
            SIUL_PCR_16B_tag PCR38;        /* offset: 0x008C size: 16 bit */
            SIUL_PCR_16B_tag PCR39;        /* offset: 0x008E size: 16 bit */
            SIUL_PCR_16B_tag PCR40;        /* offset: 0x0090 size: 16 bit */
            SIUL_PCR_16B_tag PCR41;        /* offset: 0x0092 size: 16 bit */
            SIUL_PCR_16B_tag PCR42;        /* offset: 0x0094 size: 16 bit */
            SIUL_PCR_16B_tag PCR43;        /* offset: 0x0096 size: 16 bit */
            SIUL_PCR_16B_tag PCR44;        /* offset: 0x0098 size: 16 bit */
            SIUL_PCR_16B_tag PCR45;        /* offset: 0x009A size: 16 bit */
            SIUL_PCR_16B_tag PCR46;        /* offset: 0x009C size: 16 bit */
            SIUL_PCR_16B_tag PCR47;        /* offset: 0x009E size: 16 bit */
            SIUL_PCR_16B_tag PCR48;        /* offset: 0x00A0 size: 16 bit */
            SIUL_PCR_16B_tag PCR49;        /* offset: 0x00A2 size: 16 bit */
            SIUL_PCR_16B_tag PCR50;        /* offset: 0x00A4 size: 16 bit */
            SIUL_PCR_16B_tag PCR51;        /* offset: 0x00A6 size: 16 bit */
            SIUL_PCR_16B_tag PCR52;        /* offset: 0x00A8 size: 16 bit */
            SIUL_PCR_16B_tag PCR53;        /* offset: 0x00AA size: 16 bit */
            SIUL_PCR_16B_tag PCR54;        /* offset: 0x00AC size: 16 bit */
            SIUL_PCR_16B_tag PCR55;        /* offset: 0x00AE size: 16 bit */
            SIUL_PCR_16B_tag PCR56;        /* offset: 0x00B0 size: 16 bit */
            SIUL_PCR_16B_tag PCR57;        /* offset: 0x00B2 size: 16 bit */
            SIUL_PCR_16B_tag PCR58;        /* offset: 0x00B4 size: 16 bit */
            SIUL_PCR_16B_tag PCR59;        /* offset: 0x00B6 size: 16 bit */
            SIUL_PCR_16B_tag PCR60;        /* offset: 0x00B8 size: 16 bit */
            SIUL_PCR_16B_tag PCR61;        /* offset: 0x00BA size: 16 bit */
            SIUL_PCR_16B_tag PCR62;        /* offset: 0x00BC size: 16 bit */
            SIUL_PCR_16B_tag PCR63;        /* offset: 0x00BE size: 16 bit */
            SIUL_PCR_16B_tag PCR64;        /* offset: 0x00C0 size: 16 bit */
            SIUL_PCR_16B_tag PCR65;        /* offset: 0x00C2 size: 16 bit */
            SIUL_PCR_16B_tag PCR66;        /* offset: 0x00C4 size: 16 bit */
            SIUL_PCR_16B_tag PCR67;        /* offset: 0x00C6 size: 16 bit */
            SIUL_PCR_16B_tag PCR68;        /* offset: 0x00C8 size: 16 bit */
            SIUL_PCR_16B_tag PCR69;        /* offset: 0x00CA size: 16 bit */
            SIUL_PCR_16B_tag PCR70;        /* offset: 0x00CC size: 16 bit */
            SIUL_PCR_16B_tag PCR71;        /* offset: 0x00CE size: 16 bit */
            SIUL_PCR_16B_tag PCR72;        /* offset: 0x00D0 size: 16 bit */
            SIUL_PCR_16B_tag PCR73;        /* offset: 0x00D2 size: 16 bit */
            SIUL_PCR_16B_tag PCR74;        /* offset: 0x00D4 size: 16 bit */
            SIUL_PCR_16B_tag PCR75;        /* offset: 0x00D6 size: 16 bit */
            SIUL_PCR_16B_tag PCR76;        /* offset: 0x00D8 size: 16 bit */
            SIUL_PCR_16B_tag PCR77;        /* offset: 0x00DA size: 16 bit */
            SIUL_PCR_16B_tag PCR78;        /* offset: 0x00DC size: 16 bit */
            SIUL_PCR_16B_tag PCR79;        /* offset: 0x00DE size: 16 bit */
            SIUL_PCR_16B_tag PCR80;        /* offset: 0x00E0 size: 16 bit */
            SIUL_PCR_16B_tag PCR81;        /* offset: 0x00E2 size: 16 bit */
            SIUL_PCR_16B_tag PCR82;        /* offset: 0x00E4 size: 16 bit */
            SIUL_PCR_16B_tag PCR83;        /* offset: 0x00E6 size: 16 bit */
            SIUL_PCR_16B_tag PCR84;        /* offset: 0x00E8 size: 16 bit */
            SIUL_PCR_16B_tag PCR85;        /* offset: 0x00EA size: 16 bit */
            SIUL_PCR_16B_tag PCR86;        /* offset: 0x00EC size: 16 bit */
            SIUL_PCR_16B_tag PCR87;        /* offset: 0x00EE size: 16 bit */
            SIUL_PCR_16B_tag PCR88;        /* offset: 0x00F0 size: 16 bit */
            SIUL_PCR_16B_tag PCR89;        /* offset: 0x00F2 size: 16 bit */
            SIUL_PCR_16B_tag PCR90;        /* offset: 0x00F4 size: 16 bit */
            SIUL_PCR_16B_tag PCR91;        /* offset: 0x00F6 size: 16 bit */
            SIUL_PCR_16B_tag PCR92;        /* offset: 0x00F8 size: 16 bit */
            SIUL_PCR_16B_tag PCR93;        /* offset: 0x00FA size: 16 bit */
            SIUL_PCR_16B_tag PCR94;        /* offset: 0x00FC size: 16 bit */
            SIUL_PCR_16B_tag PCR95;        /* offset: 0x00FE size: 16 bit */
            SIUL_PCR_16B_tag PCR96;        /* offset: 0x0100 size: 16 bit */
            SIUL_PCR_16B_tag PCR97;        /* offset: 0x0102 size: 16 bit */
            SIUL_PCR_16B_tag PCR98;        /* offset: 0x0104 size: 16 bit */
            SIUL_PCR_16B_tag PCR99;        /* offset: 0x0106 size: 16 bit */
            SIUL_PCR_16B_tag PCR100;       /* offset: 0x0108 size: 16 bit */
            SIUL_PCR_16B_tag PCR101;       /* offset: 0x010A size: 16 bit */
            SIUL_PCR_16B_tag PCR102;       /* offset: 0x010C size: 16 bit */
            SIUL_PCR_16B_tag PCR103;       /* offset: 0x010E size: 16 bit */
            SIUL_PCR_16B_tag PCR104;       /* offset: 0x0110 size: 16 bit */
            SIUL_PCR_16B_tag PCR105;       /* offset: 0x0112 size: 16 bit */
            SIUL_PCR_16B_tag PCR106;       /* offset: 0x0114 size: 16 bit */
            SIUL_PCR_16B_tag PCR107;       /* offset: 0x0116 size: 16 bit */
            SIUL_PCR_16B_tag PCR108;       /* offset: 0x0118 size: 16 bit */
            SIUL_PCR_16B_tag PCR109;       /* offset: 0x011A size: 16 bit */
            SIUL_PCR_16B_tag PCR110;       /* offset: 0x011C size: 16 bit */
            SIUL_PCR_16B_tag PCR111;       /* offset: 0x011E size: 16 bit */
            SIUL_PCR_16B_tag PCR112;       /* offset: 0x0120 size: 16 bit */
            SIUL_PCR_16B_tag PCR113;       /* offset: 0x0122 size: 16 bit */
            SIUL_PCR_16B_tag PCR114;       /* offset: 0x0124 size: 16 bit */
            SIUL_PCR_16B_tag PCR115;       /* offset: 0x0126 size: 16 bit */
            SIUL_PCR_16B_tag PCR116;       /* offset: 0x0128 size: 16 bit */
            SIUL_PCR_16B_tag PCR117;       /* offset: 0x012A size: 16 bit */
            SIUL_PCR_16B_tag PCR118;       /* offset: 0x012C size: 16 bit */
            SIUL_PCR_16B_tag PCR119;       /* offset: 0x012E size: 16 bit */
            SIUL_PCR_16B_tag PCR120;       /* offset: 0x0130 size: 16 bit */
            SIUL_PCR_16B_tag PCR121;       /* offset: 0x0132 size: 16 bit */
            SIUL_PCR_16B_tag PCR122;       /* offset: 0x0134 size: 16 bit */
            SIUL_PCR_16B_tag PCR123;       /* offset: 0x0136 size: 16 bit */
            SIUL_PCR_16B_tag PCR124;       /* offset: 0x0138 size: 16 bit */
            SIUL_PCR_16B_tag PCR125;       /* offset: 0x013A size: 16 bit */
            SIUL_PCR_16B_tag PCR126;       /* offset: 0x013C size: 16 bit */
            SIUL_PCR_16B_tag PCR127;       /* offset: 0x013E size: 16 bit */
            SIUL_PCR_16B_tag PCR128;       /* offset: 0x0140 size: 16 bit */
            SIUL_PCR_16B_tag PCR129;       /* offset: 0x0142 size: 16 bit */
            SIUL_PCR_16B_tag PCR130;       /* offset: 0x0144 size: 16 bit */
            SIUL_PCR_16B_tag PCR131;       /* offset: 0x0146 size: 16 bit */
            SIUL_PCR_16B_tag PCR132;       /* offset: 0x0148 size: 16 bit */
         };

      };
      int8_t SIUL_reserved_014A[950];
      union {
       /* Pad Selection for Multiplexed Inputs (combined 32 bit version) */
         SIUL_PSMI_32B_tag PSMI_32B[11];       /* offset: 0x0500  (0x0004 x 11) */

                                 /* Pad Selection for Multiplexed Inputs */
         SIUL_PSMI_8B_tag PSMI[44];        /* offset: 0x0500  (0x0001 x 44) */

         struct {
           /* Pad Selection for Multiplexed Inputs (combined 32 bit version) */
            SIUL_PSMI_32B_tag PSMI0_3;     /* offset: 0x0500 size: 32 bit */
            SIUL_PSMI_32B_tag PSMI4_7;     /* offset: 0x0504 size: 32 bit */
            SIUL_PSMI_32B_tag PSMI8_11;    /* offset: 0x0508 size: 32 bit */
            SIUL_PSMI_32B_tag PSMI12_15;   /* offset: 0x050C size: 32 bit */
            SIUL_PSMI_32B_tag PSMI16_19;   /* offset: 0x0510 size: 32 bit */
            SIUL_PSMI_32B_tag PSMI20_23;   /* offset: 0x0514 size: 32 bit */
            SIUL_PSMI_32B_tag PSMI24_27;   /* offset: 0x0518 size: 32 bit */
            SIUL_PSMI_32B_tag PSMI28_31;   /* offset: 0x051C size: 32 bit */
            SIUL_PSMI_32B_tag PSMI32_35;   /* offset: 0x0520 size: 32 bit */
            SIUL_PSMI_32B_tag PSMI36_39;   /* offset: 0x0524 size: 32 bit */
            SIUL_PSMI_32B_tag PSMI40_43;   /* offset: 0x0528 size: 32 bit */
         };

         struct {
                                 /* Pad Selection for Multiplexed Inputs */
            SIUL_PSMI_8B_tag PSMI0;        /* offset: 0x0500 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI1;        /* offset: 0x0501 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI2;        /* offset: 0x0502 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI3;        /* offset: 0x0503 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI4;        /* offset: 0x0504 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI5;        /* offset: 0x0505 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI6;        /* offset: 0x0506 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI7;        /* offset: 0x0507 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI8;        /* offset: 0x0508 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI9;        /* offset: 0x0509 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI10;       /* offset: 0x050A size: 8 bit */
            SIUL_PSMI_8B_tag PSMI11;       /* offset: 0x050B size: 8 bit */
            SIUL_PSMI_8B_tag PSMI12;       /* offset: 0x050C size: 8 bit */
            SIUL_PSMI_8B_tag PSMI13;       /* offset: 0x050D size: 8 bit */
            SIUL_PSMI_8B_tag PSMI14;       /* offset: 0x050E size: 8 bit */
            SIUL_PSMI_8B_tag PSMI15;       /* offset: 0x050F size: 8 bit */
            SIUL_PSMI_8B_tag PSMI16;       /* offset: 0x0510 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI17;       /* offset: 0x0511 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI18;       /* offset: 0x0512 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI19;       /* offset: 0x0513 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI20;       /* offset: 0x0514 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI21;       /* offset: 0x0515 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI22;       /* offset: 0x0516 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI23;       /* offset: 0x0517 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI24;       /* offset: 0x0518 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI25;       /* offset: 0x0519 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI26;       /* offset: 0x051A size: 8 bit */
            SIUL_PSMI_8B_tag PSMI27;       /* offset: 0x051B size: 8 bit */
            SIUL_PSMI_8B_tag PSMI28;       /* offset: 0x051C size: 8 bit */
            SIUL_PSMI_8B_tag PSMI29;       /* offset: 0x051D size: 8 bit */
            SIUL_PSMI_8B_tag PSMI30;       /* offset: 0x051E size: 8 bit */
            SIUL_PSMI_8B_tag PSMI31;       /* offset: 0x051F size: 8 bit */
            SIUL_PSMI_8B_tag PSMI32;       /* offset: 0x0520 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI33;       /* offset: 0x0521 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI34;       /* offset: 0x0522 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI35;       /* offset: 0x0523 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI36;       /* offset: 0x0524 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI37;       /* offset: 0x0525 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI38;       /* offset: 0x0526 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI39;       /* offset: 0x0527 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI40;       /* offset: 0x0528 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI41;       /* offset: 0x0529 size: 8 bit */
            SIUL_PSMI_8B_tag PSMI42;       /* offset: 0x052A size: 8 bit */
            SIUL_PSMI_8B_tag PSMI43;       /* offset: 0x052B size: 8 bit */
         };

      };
      int8_t SIUL_reserved_052C[212];
      union {
              /* GPIO Pad Data Output Register (combined 32 bit version) */
         SIUL_GPDO_32B_tag GPDO_32B[34];   /* offset: 0x0600  (0x0004 x 34) */

         struct {
                                        /* GPIO Pad Data Output Register */
            SIUL_GPDO_8B_tag GPDO[133];    /* offset: 0x0600  (0x0001 x 133) */
            int8_t SIUL_reserved_0685_E1[3];
         };

         struct {
              /* GPIO Pad Data Output Register (combined 32 bit version) */
            SIUL_GPDO_32B_tag GPDO0_3;     /* offset: 0x0600 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO4_7;     /* offset: 0x0604 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO8_11;    /* offset: 0x0608 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO12_15;   /* offset: 0x060C size: 32 bit */
            SIUL_GPDO_32B_tag GPDO16_19;   /* offset: 0x0610 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO20_23;   /* offset: 0x0614 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO24_27;   /* offset: 0x0618 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO28_31;   /* offset: 0x061C size: 32 bit */
            SIUL_GPDO_32B_tag GPDO32_35;   /* offset: 0x0620 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO36_39;   /* offset: 0x0624 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO40_43;   /* offset: 0x0628 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO44_47;   /* offset: 0x062C size: 32 bit */
            SIUL_GPDO_32B_tag GPDO48_51;   /* offset: 0x0630 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO52_55;   /* offset: 0x0634 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO56_59;   /* offset: 0x0638 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO60_63;   /* offset: 0x063C size: 32 bit */
            SIUL_GPDO_32B_tag GPDO64_67;   /* offset: 0x0640 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO68_71;   /* offset: 0x0644 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO72_75;   /* offset: 0x0648 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO76_79;   /* offset: 0x064C size: 32 bit */
            SIUL_GPDO_32B_tag GPDO80_83;   /* offset: 0x0650 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO84_87;   /* offset: 0x0654 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO88_91;   /* offset: 0x0658 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO92_95;   /* offset: 0x065C size: 32 bit */
            SIUL_GPDO_32B_tag GPDO96_99;   /* offset: 0x0660 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO100_103;  /* offset: 0x0664 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO104_107;  /* offset: 0x0668 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO108_111;  /* offset: 0x066C size: 32 bit */
            SIUL_GPDO_32B_tag GPDO112_115;  /* offset: 0x0670 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO116_119;  /* offset: 0x0674 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO120_123;  /* offset: 0x0678 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO124_127;  /* offset: 0x067C size: 32 bit */
            SIUL_GPDO_32B_tag GPDO128_131;  /* offset: 0x0680 size: 32 bit */
            SIUL_GPDO_32B_tag GPDO132_135;  /* offset: 0x0684 size: 32 bit */
         };

         struct {
                                        /* GPIO Pad Data Output Register */
            SIUL_GPDO_8B_tag GPDO0;        /* offset: 0x0600 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO1;        /* offset: 0x0601 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO2;        /* offset: 0x0602 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO3;        /* offset: 0x0603 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO4;        /* offset: 0x0604 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO5;        /* offset: 0x0605 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO6;        /* offset: 0x0606 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO7;        /* offset: 0x0607 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO8;        /* offset: 0x0608 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO9;        /* offset: 0x0609 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO10;       /* offset: 0x060A size: 8 bit */
            SIUL_GPDO_8B_tag GPDO11;       /* offset: 0x060B size: 8 bit */
            SIUL_GPDO_8B_tag GPDO12;       /* offset: 0x060C size: 8 bit */
            SIUL_GPDO_8B_tag GPDO13;       /* offset: 0x060D size: 8 bit */
            SIUL_GPDO_8B_tag GPDO14;       /* offset: 0x060E size: 8 bit */
            SIUL_GPDO_8B_tag GPDO15;       /* offset: 0x060F size: 8 bit */
            SIUL_GPDO_8B_tag GPDO16;       /* offset: 0x0610 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO17;       /* offset: 0x0611 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO18;       /* offset: 0x0612 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO19;       /* offset: 0x0613 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO20;       /* offset: 0x0614 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO21;       /* offset: 0x0615 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO22;       /* offset: 0x0616 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO23;       /* offset: 0x0617 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO24;       /* offset: 0x0618 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO25;       /* offset: 0x0619 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO26;       /* offset: 0x061A size: 8 bit */
            SIUL_GPDO_8B_tag GPDO27;       /* offset: 0x061B size: 8 bit */
            SIUL_GPDO_8B_tag GPDO28;       /* offset: 0x061C size: 8 bit */
            SIUL_GPDO_8B_tag GPDO29;       /* offset: 0x061D size: 8 bit */
            SIUL_GPDO_8B_tag GPDO30;       /* offset: 0x061E size: 8 bit */
            SIUL_GPDO_8B_tag GPDO31;       /* offset: 0x061F size: 8 bit */
            SIUL_GPDO_8B_tag GPDO32;       /* offset: 0x0620 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO33;       /* offset: 0x0621 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO34;       /* offset: 0x0622 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO35;       /* offset: 0x0623 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO36;       /* offset: 0x0624 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO37;       /* offset: 0x0625 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO38;       /* offset: 0x0626 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO39;       /* offset: 0x0627 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO40;       /* offset: 0x0628 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO41;       /* offset: 0x0629 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO42;       /* offset: 0x062A size: 8 bit */
            SIUL_GPDO_8B_tag GPDO43;       /* offset: 0x062B size: 8 bit */
            SIUL_GPDO_8B_tag GPDO44;       /* offset: 0x062C size: 8 bit */
            SIUL_GPDO_8B_tag GPDO45;       /* offset: 0x062D size: 8 bit */
            SIUL_GPDO_8B_tag GPDO46;       /* offset: 0x062E size: 8 bit */
            SIUL_GPDO_8B_tag GPDO47;       /* offset: 0x062F size: 8 bit */
            SIUL_GPDO_8B_tag GPDO48;       /* offset: 0x0630 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO49;       /* offset: 0x0631 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO50;       /* offset: 0x0632 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO51;       /* offset: 0x0633 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO52;       /* offset: 0x0634 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO53;       /* offset: 0x0635 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO54;       /* offset: 0x0636 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO55;       /* offset: 0x0637 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO56;       /* offset: 0x0638 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO57;       /* offset: 0x0639 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO58;       /* offset: 0x063A size: 8 bit */
            SIUL_GPDO_8B_tag GPDO59;       /* offset: 0x063B size: 8 bit */
            SIUL_GPDO_8B_tag GPDO60;       /* offset: 0x063C size: 8 bit */
            SIUL_GPDO_8B_tag GPDO61;       /* offset: 0x063D size: 8 bit */
            SIUL_GPDO_8B_tag GPDO62;       /* offset: 0x063E size: 8 bit */
            SIUL_GPDO_8B_tag GPDO63;       /* offset: 0x063F size: 8 bit */
            SIUL_GPDO_8B_tag GPDO64;       /* offset: 0x0640 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO65;       /* offset: 0x0641 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO66;       /* offset: 0x0642 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO67;       /* offset: 0x0643 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO68;       /* offset: 0x0644 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO69;       /* offset: 0x0645 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO70;       /* offset: 0x0646 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO71;       /* offset: 0x0647 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO72;       /* offset: 0x0648 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO73;       /* offset: 0x0649 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO74;       /* offset: 0x064A size: 8 bit */
            SIUL_GPDO_8B_tag GPDO75;       /* offset: 0x064B size: 8 bit */
            SIUL_GPDO_8B_tag GPDO76;       /* offset: 0x064C size: 8 bit */
            SIUL_GPDO_8B_tag GPDO77;       /* offset: 0x064D size: 8 bit */
            SIUL_GPDO_8B_tag GPDO78;       /* offset: 0x064E size: 8 bit */
            SIUL_GPDO_8B_tag GPDO79;       /* offset: 0x064F size: 8 bit */
            SIUL_GPDO_8B_tag GPDO80;       /* offset: 0x0650 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO81;       /* offset: 0x0651 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO82;       /* offset: 0x0652 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO83;       /* offset: 0x0653 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO84;       /* offset: 0x0654 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO85;       /* offset: 0x0655 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO86;       /* offset: 0x0656 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO87;       /* offset: 0x0657 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO88;       /* offset: 0x0658 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO89;       /* offset: 0x0659 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO90;       /* offset: 0x065A size: 8 bit */
            SIUL_GPDO_8B_tag GPDO91;       /* offset: 0x065B size: 8 bit */
            SIUL_GPDO_8B_tag GPDO92;       /* offset: 0x065C size: 8 bit */
            SIUL_GPDO_8B_tag GPDO93;       /* offset: 0x065D size: 8 bit */
            SIUL_GPDO_8B_tag GPDO94;       /* offset: 0x065E size: 8 bit */
            SIUL_GPDO_8B_tag GPDO95;       /* offset: 0x065F size: 8 bit */
            SIUL_GPDO_8B_tag GPDO96;       /* offset: 0x0660 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO97;       /* offset: 0x0661 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO98;       /* offset: 0x0662 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO99;       /* offset: 0x0663 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO100;      /* offset: 0x0664 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO101;      /* offset: 0x0665 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO102;      /* offset: 0x0666 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO103;      /* offset: 0x0667 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO104;      /* offset: 0x0668 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO105;      /* offset: 0x0669 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO106;      /* offset: 0x066A size: 8 bit */
            SIUL_GPDO_8B_tag GPDO107;      /* offset: 0x066B size: 8 bit */
            SIUL_GPDO_8B_tag GPDO108;      /* offset: 0x066C size: 8 bit */
            SIUL_GPDO_8B_tag GPDO109;      /* offset: 0x066D size: 8 bit */
            SIUL_GPDO_8B_tag GPDO110;      /* offset: 0x066E size: 8 bit */
            SIUL_GPDO_8B_tag GPDO111;      /* offset: 0x066F size: 8 bit */
            SIUL_GPDO_8B_tag GPDO112;      /* offset: 0x0670 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO113;      /* offset: 0x0671 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO114;      /* offset: 0x0672 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO115;      /* offset: 0x0673 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO116;      /* offset: 0x0674 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO117;      /* offset: 0x0675 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO118;      /* offset: 0x0676 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO119;      /* offset: 0x0677 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO120;      /* offset: 0x0678 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO121;      /* offset: 0x0679 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO122;      /* offset: 0x067A size: 8 bit */
            SIUL_GPDO_8B_tag GPDO123;      /* offset: 0x067B size: 8 bit */
            SIUL_GPDO_8B_tag GPDO124;      /* offset: 0x067C size: 8 bit */
            SIUL_GPDO_8B_tag GPDO125;      /* offset: 0x067D size: 8 bit */
            SIUL_GPDO_8B_tag GPDO126;      /* offset: 0x067E size: 8 bit */
            SIUL_GPDO_8B_tag GPDO127;      /* offset: 0x067F size: 8 bit */
            SIUL_GPDO_8B_tag GPDO128;      /* offset: 0x0680 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO129;      /* offset: 0x0681 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO130;      /* offset: 0x0682 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO131;      /* offset: 0x0683 size: 8 bit */
            SIUL_GPDO_8B_tag GPDO132;      /* offset: 0x0684 size: 8 bit */
            int8_t SIUL_reserved_0685_E3[3];
         };

      };
      int8_t SIUL_reserved_0688[376];
      union {
               /* GPIO Pad Data Input Register (combined 32 bit version) */
         SIUL_GPDI_32B_tag GPDI_32B[34];    /* offset: 0x0800  (0x0004 x 34) */

         struct {
                                         /* GPIO Pad Data Input Register */
            SIUL_GPDI_8B_tag GPDI[133];    /* offset: 0x0800  (0x0001 x 133) */
            int8_t SIUL_reserved_0885_E1[3];
         };

         struct {
               /* GPIO Pad Data Input Register (combined 32 bit version) */
            SIUL_GPDI_32B_tag GPDI0_3;     /* offset: 0x0800 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI4_7;     /* offset: 0x0804 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI8_11;    /* offset: 0x0808 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI12_15;   /* offset: 0x080C size: 32 bit */
            SIUL_GPDI_32B_tag GPDI16_19;   /* offset: 0x0810 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI20_23;   /* offset: 0x0814 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI24_27;   /* offset: 0x0818 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI28_31;   /* offset: 0x081C size: 32 bit */
            SIUL_GPDI_32B_tag GPDI32_35;   /* offset: 0x0820 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI36_39;   /* offset: 0x0824 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI40_43;   /* offset: 0x0828 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI44_47;   /* offset: 0x082C size: 32 bit */
            SIUL_GPDI_32B_tag GPDI48_51;   /* offset: 0x0830 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI52_55;   /* offset: 0x0834 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI56_59;   /* offset: 0x0838 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI60_63;   /* offset: 0x083C size: 32 bit */
            SIUL_GPDI_32B_tag GPDI64_67;   /* offset: 0x0840 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI68_71;   /* offset: 0x0844 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI72_75;   /* offset: 0x0848 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI76_79;   /* offset: 0x084C size: 32 bit */
            SIUL_GPDI_32B_tag GPDI80_83;   /* offset: 0x0850 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI84_87;   /* offset: 0x0854 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI88_91;   /* offset: 0x0858 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI92_95;   /* offset: 0x085C size: 32 bit */
            SIUL_GPDI_32B_tag GPDI96_99;   /* offset: 0x0860 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI100_103;  /* offset: 0x0864 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI104_107;  /* offset: 0x0868 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI108_111;  /* offset: 0x086C size: 32 bit */
            SIUL_GPDI_32B_tag GPDI112_115;  /* offset: 0x0870 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI116_119;  /* offset: 0x0874 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI120_123;  /* offset: 0x0878 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI124_127;  /* offset: 0x087C size: 32 bit */
            SIUL_GPDI_32B_tag GPDI128_131;  /* offset: 0x0880 size: 32 bit */
            SIUL_GPDI_32B_tag GPDI132_135;  /* offset: 0x0884 size: 32 bit */
         };

         struct {
                                         /* GPIO Pad Data Input Register */
            SIUL_GPDI_8B_tag GPDI0;        /* offset: 0x0800 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI1;        /* offset: 0x0801 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI2;        /* offset: 0x0802 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI3;        /* offset: 0x0803 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI4;        /* offset: 0x0804 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI5;        /* offset: 0x0805 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI6;        /* offset: 0x0806 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI7;        /* offset: 0x0807 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI8;        /* offset: 0x0808 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI9;        /* offset: 0x0809 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI10;       /* offset: 0x080A size: 8 bit */
            SIUL_GPDI_8B_tag GPDI11;       /* offset: 0x080B size: 8 bit */
            SIUL_GPDI_8B_tag GPDI12;       /* offset: 0x080C size: 8 bit */
            SIUL_GPDI_8B_tag GPDI13;       /* offset: 0x080D size: 8 bit */
            SIUL_GPDI_8B_tag GPDI14;       /* offset: 0x080E size: 8 bit */
            SIUL_GPDI_8B_tag GPDI15;       /* offset: 0x080F size: 8 bit */
            SIUL_GPDI_8B_tag GPDI16;       /* offset: 0x0810 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI17;       /* offset: 0x0811 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI18;       /* offset: 0x0812 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI19;       /* offset: 0x0813 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI20;       /* offset: 0x0814 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI21;       /* offset: 0x0815 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI22;       /* offset: 0x0816 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI23;       /* offset: 0x0817 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI24;       /* offset: 0x0818 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI25;       /* offset: 0x0819 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI26;       /* offset: 0x081A size: 8 bit */
            SIUL_GPDI_8B_tag GPDI27;       /* offset: 0x081B size: 8 bit */
            SIUL_GPDI_8B_tag GPDI28;       /* offset: 0x081C size: 8 bit */
            SIUL_GPDI_8B_tag GPDI29;       /* offset: 0x081D size: 8 bit */
            SIUL_GPDI_8B_tag GPDI30;       /* offset: 0x081E size: 8 bit */
            SIUL_GPDI_8B_tag GPDI31;       /* offset: 0x081F size: 8 bit */
            SIUL_GPDI_8B_tag GPDI32;       /* offset: 0x0820 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI33;       /* offset: 0x0821 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI34;       /* offset: 0x0822 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI35;       /* offset: 0x0823 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI36;       /* offset: 0x0824 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI37;       /* offset: 0x0825 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI38;       /* offset: 0x0826 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI39;       /* offset: 0x0827 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI40;       /* offset: 0x0828 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI41;       /* offset: 0x0829 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI42;       /* offset: 0x082A size: 8 bit */
            SIUL_GPDI_8B_tag GPDI43;       /* offset: 0x082B size: 8 bit */
            SIUL_GPDI_8B_tag GPDI44;       /* offset: 0x082C size: 8 bit */
            SIUL_GPDI_8B_tag GPDI45;       /* offset: 0x082D size: 8 bit */
            SIUL_GPDI_8B_tag GPDI46;       /* offset: 0x082E size: 8 bit */
            SIUL_GPDI_8B_tag GPDI47;       /* offset: 0x082F size: 8 bit */
            SIUL_GPDI_8B_tag GPDI48;       /* offset: 0x0830 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI49;       /* offset: 0x0831 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI50;       /* offset: 0x0832 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI51;       /* offset: 0x0833 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI52;       /* offset: 0x0834 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI53;       /* offset: 0x0835 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI54;       /* offset: 0x0836 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI55;       /* offset: 0x0837 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI56;       /* offset: 0x0838 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI57;       /* offset: 0x0839 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI58;       /* offset: 0x083A size: 8 bit */
            SIUL_GPDI_8B_tag GPDI59;       /* offset: 0x083B size: 8 bit */
            SIUL_GPDI_8B_tag GPDI60;       /* offset: 0x083C size: 8 bit */
            SIUL_GPDI_8B_tag GPDI61;       /* offset: 0x083D size: 8 bit */
            SIUL_GPDI_8B_tag GPDI62;       /* offset: 0x083E size: 8 bit */
            SIUL_GPDI_8B_tag GPDI63;       /* offset: 0x083F size: 8 bit */
            SIUL_GPDI_8B_tag GPDI64;       /* offset: 0x0840 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI65;       /* offset: 0x0841 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI66;       /* offset: 0x0842 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI67;       /* offset: 0x0843 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI68;       /* offset: 0x0844 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI69;       /* offset: 0x0845 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI70;       /* offset: 0x0846 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI71;       /* offset: 0x0847 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI72;       /* offset: 0x0848 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI73;       /* offset: 0x0849 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI74;       /* offset: 0x084A size: 8 bit */
            SIUL_GPDI_8B_tag GPDI75;       /* offset: 0x084B size: 8 bit */
            SIUL_GPDI_8B_tag GPDI76;       /* offset: 0x084C size: 8 bit */
            SIUL_GPDI_8B_tag GPDI77;       /* offset: 0x084D size: 8 bit */
            SIUL_GPDI_8B_tag GPDI78;       /* offset: 0x084E size: 8 bit */
            SIUL_GPDI_8B_tag GPDI79;       /* offset: 0x084F size: 8 bit */
            SIUL_GPDI_8B_tag GPDI80;       /* offset: 0x0850 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI81;       /* offset: 0x0851 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI82;       /* offset: 0x0852 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI83;       /* offset: 0x0853 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI84;       /* offset: 0x0854 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI85;       /* offset: 0x0855 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI86;       /* offset: 0x0856 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI87;       /* offset: 0x0857 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI88;       /* offset: 0x0858 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI89;       /* offset: 0x0859 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI90;       /* offset: 0x085A size: 8 bit */
            SIUL_GPDI_8B_tag GPDI91;       /* offset: 0x085B size: 8 bit */
            SIUL_GPDI_8B_tag GPDI92;       /* offset: 0x085C size: 8 bit */
            SIUL_GPDI_8B_tag GPDI93;       /* offset: 0x085D size: 8 bit */
            SIUL_GPDI_8B_tag GPDI94;       /* offset: 0x085E size: 8 bit */
            SIUL_GPDI_8B_tag GPDI95;       /* offset: 0x085F size: 8 bit */
            SIUL_GPDI_8B_tag GPDI96;       /* offset: 0x0860 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI97;       /* offset: 0x0861 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI98;       /* offset: 0x0862 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI99;       /* offset: 0x0863 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI100;      /* offset: 0x0864 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI101;      /* offset: 0x0865 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI102;      /* offset: 0x0866 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI103;      /* offset: 0x0867 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI104;      /* offset: 0x0868 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI105;      /* offset: 0x0869 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI106;      /* offset: 0x086A size: 8 bit */
            SIUL_GPDI_8B_tag GPDI107;      /* offset: 0x086B size: 8 bit */
            SIUL_GPDI_8B_tag GPDI108;      /* offset: 0x086C size: 8 bit */
            SIUL_GPDI_8B_tag GPDI109;      /* offset: 0x086D size: 8 bit */
            SIUL_GPDI_8B_tag GPDI110;      /* offset: 0x086E size: 8 bit */
            SIUL_GPDI_8B_tag GPDI111;      /* offset: 0x086F size: 8 bit */
            SIUL_GPDI_8B_tag GPDI112;      /* offset: 0x0870 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI113;      /* offset: 0x0871 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI114;      /* offset: 0x0872 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI115;      /* offset: 0x0873 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI116;      /* offset: 0x0874 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI117;      /* offset: 0x0875 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI118;      /* offset: 0x0876 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI119;      /* offset: 0x0877 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI120;      /* offset: 0x0878 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI121;      /* offset: 0x0879 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI122;      /* offset: 0x087A size: 8 bit */
            SIUL_GPDI_8B_tag GPDI123;      /* offset: 0x087B size: 8 bit */
            SIUL_GPDI_8B_tag GPDI124;      /* offset: 0x087C size: 8 bit */
            SIUL_GPDI_8B_tag GPDI125;      /* offset: 0x087D size: 8 bit */
            SIUL_GPDI_8B_tag GPDI126;      /* offset: 0x087E size: 8 bit */
            SIUL_GPDI_8B_tag GPDI127;      /* offset: 0x087F size: 8 bit */
            SIUL_GPDI_8B_tag GPDI128;      /* offset: 0x0880 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI129;      /* offset: 0x0881 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI130;      /* offset: 0x0882 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI131;      /* offset: 0x0883 size: 8 bit */
            SIUL_GPDI_8B_tag GPDI132;      /* offset: 0x0884 size: 8 bit */
            int8_t SIUL_reserved_0885_E3[3];
         };

      };
      int8_t SIUL_reserved_0888[888];
      union {
                                  /* Parallel GPIO Pad Data Out Register */
         SIUL_PGPDO_16B_tag PGPDO[9];      /* offset: 0x0C00  (0x0002 x 9) */

         struct {
                                  /* Parallel GPIO Pad Data Out Register */
            SIUL_PGPDO_16B_tag PGPDO0;     /* offset: 0x0C00 size: 16 bit */
            SIUL_PGPDO_16B_tag PGPDO1;     /* offset: 0x0C02 size: 16 bit */
            SIUL_PGPDO_16B_tag PGPDO2;     /* offset: 0x0C04 size: 16 bit */
            SIUL_PGPDO_16B_tag PGPDO3;     /* offset: 0x0C06 size: 16 bit */
            SIUL_PGPDO_16B_tag PGPDO4;     /* offset: 0x0C08 size: 16 bit */
            SIUL_PGPDO_16B_tag PGPDO5;     /* offset: 0x0C0A size: 16 bit */
            SIUL_PGPDO_16B_tag PGPDO6;     /* offset: 0x0C0C size: 16 bit */
            SIUL_PGPDO_16B_tag PGPDO7;     /* offset: 0x0C0E size: 16 bit */
            SIUL_PGPDO_16B_tag PGPDO8;     /* offset: 0x0C10 size: 16 bit */
         };

      };
      int8_t SIUL_reserved_0C12[46];
      union {
                                   /* Parallel GPIO Pad Data In Register */
         SIUL_PGPDI_16B_tag PGPDI[9];      /* offset: 0x0C40  (0x0002 x 9) */

         struct {
                                   /* Parallel GPIO Pad Data In Register */
            SIUL_PGPDI_16B_tag PGPDI0;     /* offset: 0x0C40 size: 16 bit */
            SIUL_PGPDI_16B_tag PGPDI1;     /* offset: 0x0C42 size: 16 bit */
            SIUL_PGPDI_16B_tag PGPDI2;     /* offset: 0x0C44 size: 16 bit */
            SIUL_PGPDI_16B_tag PGPDI3;     /* offset: 0x0C46 size: 16 bit */
            SIUL_PGPDI_16B_tag PGPDI4;     /* offset: 0x0C48 size: 16 bit */
            SIUL_PGPDI_16B_tag PGPDI5;     /* offset: 0x0C4A size: 16 bit */
            SIUL_PGPDI_16B_tag PGPDI6;     /* offset: 0x0C4C size: 16 bit */
            SIUL_PGPDI_16B_tag PGPDI7;     /* offset: 0x0C4E size: 16 bit */
            SIUL_PGPDI_16B_tag PGPDI8;     /* offset: 0x0C50 size: 16 bit */
         };

      };
      int8_t SIUL_reserved_0C52[46];
      union {
                           /* Masked Parallel GPIO Pad Data Out Register */
         SIUL_MPGPDO_32B_tag MPGPDO[9];    /* offset: 0x0C80  (0x0004 x 9) */

         struct {
                           /* Masked Parallel GPIO Pad Data Out Register */
            SIUL_MPGPDO_32B_tag MPGPDO0;   /* offset: 0x0C80 size: 32 bit */
            SIUL_MPGPDO_32B_tag MPGPDO1;   /* offset: 0x0C84 size: 32 bit */
            SIUL_MPGPDO_32B_tag MPGPDO2;   /* offset: 0x0C88 size: 32 bit */
            SIUL_MPGPDO_32B_tag MPGPDO3;   /* offset: 0x0C8C size: 32 bit */
            SIUL_MPGPDO_32B_tag MPGPDO4;   /* offset: 0x0C90 size: 32 bit */
            SIUL_MPGPDO_32B_tag MPGPDO5;   /* offset: 0x0C94 size: 32 bit */
            SIUL_MPGPDO_32B_tag MPGPDO6;   /* offset: 0x0C98 size: 32 bit */
            SIUL_MPGPDO_32B_tag MPGPDO7;   /* offset: 0x0C9C size: 32 bit */
            SIUL_MPGPDO_32B_tag MPGPDO8;   /* offset: 0x0CA0 size: 32 bit */
         };

      };
      int8_t SIUL_reserved_0CA4[860];
      union {
                            /* Interrupt Filter Maximum Counter Register */
         SIUL_IFMCR_32B_tag IFMCR[32];     /* offset: 0x1000  (0x0004 x 32) */

         struct {
                            /* Interrupt Filter Maximum Counter Register */
            SIUL_IFMCR_32B_tag IFMCR0;     /* offset: 0x1000 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR1;     /* offset: 0x1004 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR2;     /* offset: 0x1008 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR3;     /* offset: 0x100C size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR4;     /* offset: 0x1010 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR5;     /* offset: 0x1014 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR6;     /* offset: 0x1018 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR7;     /* offset: 0x101C size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR8;     /* offset: 0x1020 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR9;     /* offset: 0x1024 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR10;    /* offset: 0x1028 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR11;    /* offset: 0x102C size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR12;    /* offset: 0x1030 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR13;    /* offset: 0x1034 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR14;    /* offset: 0x1038 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR15;    /* offset: 0x103C size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR16;    /* offset: 0x1040 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR17;    /* offset: 0x1044 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR18;    /* offset: 0x1048 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR19;    /* offset: 0x104C size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR20;    /* offset: 0x1050 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR21;    /* offset: 0x1054 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR22;    /* offset: 0x1058 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR23;    /* offset: 0x105C size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR24;    /* offset: 0x1060 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR25;    /* offset: 0x1064 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR26;    /* offset: 0x1068 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR27;    /* offset: 0x106C size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR28;    /* offset: 0x1070 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR29;    /* offset: 0x1074 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR30;    /* offset: 0x1078 size: 32 bit */
            SIUL_IFMCR_32B_tag IFMCR31;    /* offset: 0x107C size: 32 bit */
         };

      };
                            /* Interrupt Filter Clock Prescaler Register */
      SIUL_IFCPR_32B_tag IFCPR;            /* offset: 0x1080 size: 32 bit */
      int8_t SIUL_reserved_1084[12156];

   } SIUL_tag;


#define SIUL_BASEADDRESS 0xC3F90000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define SIUL  (*(volatile SIUL_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3F90000UL))
#define SIU SIUL  // added define to simplify code reuse



/****************************************************************/
/*                                                              */
/* Module: WKPU  */
/*                                                              */
/****************************************************************/

   typedef union {   /* WKPU_NSR - NMI Status Flag Register */
      vuint32_t R;
      struct {
         vuint32_t  NIF0:1;            /* NMI Status Flag 0 */
         vuint32_t  NOVF0:1;           /* NMI Overrun Status Flag 0 */
         vuint32_t:30;
      } B;
   } WKPU_NSR_32B_tag;

   typedef union {   /* NMI Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t  NLOCK0:1;          /* NMI Configuration Lock Register 0 */
         vuint32_t  NDSS0:2;           /* NMI Destination Source Select 0 */
         vuint32_t  NWRE0:1;           /* NMI Wakeup Request Enable 0 */
         vuint32_t:1;
         vuint32_t  NREE0:1;           /* NMI Rising Edge Events Enable 0 */
         vuint32_t  NFEE0:1;           /* NMI Falling Edge Events Enable 0 */
         vuint32_t  NFE0:1;            /* NMI Filter Enable 0 */
         vuint32_t:24;
      } B;
   } WKPU_NCR_32B_tag;


   typedef struct WKPU_struct_tag {

                                  /* WKPU_NSR - NMI Status Flag Register */
      WKPU_NSR_32B_tag NSR;                /* offset: 0x0000 size: 32 bit */
      int8_t WKPU_reserved_0004[4];
                                           /* NMI Configuration Register */
      WKPU_NCR_32B_tag NCR;                /* offset: 0x0008 size: 32 bit */
      int8_t WKPU_reserved_000C[16372];

   } WKPU_tag;


#define WKPU_BASEADDRESS 0xC3F94000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define WKPU  (*(volatile WKPU_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3F94000UL))



/****************************************************************/
/*                                                              */
/* Module: SSCM  */
/*                                                              */
/****************************************************************/

   typedef union {   /* SSCM_STATUS - System Status Register */
      vuint16_t R;
      struct {
         vuint16_t  LSM:1;             /* Lock Step Mode */
         vuint16_t  CER:1;             /* Configuration Error */
         vuint16_t:1;
         vuint16_t  NXEN1:1;           /* Processor 1 Nexus enabled */
         vuint16_t  NXEN:1;            /* Processor 0 Nexus enabled */
         vuint16_t  PUB:1;             /* Public Serial Access Status */
         vuint16_t  SEC:1;             /* Security Status */
         vuint16_t:1;
         vuint16_t  BMODE:3;           /* Device Boot Mode */
         vuint16_t  VLE:1;             /* Variable Length Instruction Mode */
         vuint16_t  ABD:1;             /* Autobaud detection */
         vuint16_t:3;
      } B;
   } SSCM_STATUS_16B_tag;

   typedef union {   /* System Memory and ID Register */
      vuint16_t R;
      struct {
         vuint16_t  JPIN:10;           /* JTAG Part ID Number */
         vuint16_t  IVLD:1;            /* Instruction Flash Valid */
         vuint16_t  MREV:4;            /* Minor Mask Revision */
         vuint16_t:1;
      } B;
   } SSCM_MEMCONFIG_16B_tag;

   typedef union {   /* Error Configuration */
      vuint16_t R;
      struct {
         vuint16_t:14;
         vuint16_t  PAE:1;             /* Peripheral Bus Abort Enable */
         vuint16_t  RAE:1;             /* Register Bus Abort Enable */
      } B;
   } SSCM_ERROR_16B_tag;

   typedef union {   /* Debug Status Port Register */
      vuint16_t R;
      struct {
         vuint16_t:13;
         vuint16_t  DEBUG_MODE:3;      /* Debug Status Port Mode */
      } B;
   } SSCM_DEBUGPORT_16B_tag;

   typedef union {   /* DPM Boot Register */
      vuint32_t R;
      struct {
         vuint32_t  P2BOOT:30;         /* boot location 2nd processor */
         vuint32_t  DVLE:1;            /* VLE mode for 2nd processor */
         vuint32_t:1;
      } B;
   } SSCM_DPMBOOT_32B_tag;

   typedef union {   /* DPM Boot Key Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  KEY:16;            /* Control Key */
      } B;
   } SSCM_DPMKEY_32B_tag;

   typedef union {   /* User Option Status Register */
      vuint32_t R;
      struct {
         vuint32_t  FCCU_CFG:12;       /* FCCU configuration FOP.FOM.PS.SM.CM */
         vuint32_t:10;
         vuint32_t  LSM_DPMB:1;        /* Lock-step/Decoupled parallel mode */
         vuint32_t:7;
         vuint32_t  XOSC_MARGIN:1;     /* Higher/Lower XOSC consumption and oscillator margin */
         vuint32_t  WATCHDOG_ENABLE:1;   /* Enable/Disable SWT */
      } B;
   } SSCM_UOPS_32B_tag;

   typedef union {   /* SSCM_SCTR - SSCM Control Register */
      vuint32_t R;
      struct {
         vuint32_t:29;
         vuint32_t  TFE:1;             /* Test Flash Enable */
         vuint32_t:2;
      } B;
   } SSCM_SCTR_32B_tag;


   typedef struct SSCM_struct_tag {

                                 /* SSCM_STATUS - System Status Register */
      SSCM_STATUS_16B_tag STATUS;          /* offset: 0x0000 size: 16 bit */
                                        /* System Memory and ID Register */
      SSCM_MEMCONFIG_16B_tag MEMCONFIG;    /* offset: 0x0002 size: 16 bit */
      int8_t SSCM_reserved_0004[2];
                                                  /* Error Configuration */
      SSCM_ERROR_16B_tag ERROR;            /* offset: 0x0006 size: 16 bit */
                                           /* Debug Status Port Register */
      SSCM_DEBUGPORT_16B_tag DEBUGPORT;    /* offset: 0x0008 size: 16 bit */
      int8_t SSCM_reserved_000A[14];
                                                    /* DPM Boot Register */
      SSCM_DPMBOOT_32B_tag DPMBOOT;        /* offset: 0x0018 size: 32 bit */
                                                /* DPM Boot Key Register */
      SSCM_DPMKEY_32B_tag DPMKEY;          /* offset: 0x001C size: 32 bit */
                                          /* User Option Status Register */
      SSCM_UOPS_32B_tag UOPS;              /* offset: 0x0020 size: 32 bit */
                                    /* SSCM_SCTR - SSCM Control Register */
      SSCM_SCTR_32B_tag SCTR;              /* offset: 0x0024 size: 32 bit */
      int8_t SSCM_reserved_0028[16344];

   } SSCM_tag;


#define SSCM_BASEADDRESS 0xC3FD8000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define SSCM  (*(volatile SSCM_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FD8000UL))



/****************************************************************/
/*                                                              */
/* Module: ME  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Global Status Register */
      vuint32_t R;
      struct {
         vuint32_t  S_CURRENTMODE:4;   /* Current device mode status */
         vuint32_t  S_MTRANS:1;        /* Mode transition status */
         vuint32_t:3;
         vuint32_t  S_PDO:1;           /* Output power-down status */
         vuint32_t:2;
         vuint32_t  S_MVR:1;           /* Main voltage regulator status */
         vuint32_t:2;
         vuint32_t  S_FLA:2;           /* Flash availability status */
         vuint32_t:8;
         vuint32_t  S_PLL1:1;          /* Secondary PLL status */
         vuint32_t  S_PLL0:1;          /* System PLL status */
         vuint32_t  S_XOSC:1;          /* System crystal oscillator status */
         vuint32_t  S_IRCOSC:1;        /* System RC oscillator status */
         vuint32_t  S_SYSCLK:4;        /* System clock switch status */
      } B;
   } ME_GS_32B_tag;

   typedef union {   /* Mode Control Register */
      vuint32_t R;
      struct {
         vuint32_t  TARGET_MODE:4;     /* Target device mode */
         vuint32_t:12;
         vuint32_t  KEY:16;            /* Control key */
      } B;
   } ME_MCTL_32B_tag;

   typedef union {   /* Mode Enable Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  RESET_DEST:1;      /* Destructive RESET mode enable */
         vuint32_t:4;
         vuint32_t  STOP0:1;           /* STOP0 mode enable */
         vuint32_t:1;
         vuint32_t  HALT0:1;           /* HALT0 mode enable */
         vuint32_t  RUN3:1;            /* RUN3 mode enable */
         vuint32_t  RUN2:1;            /* RUN2 mode enable */
         vuint32_t  RUN1:1;            /* RUN1 mode enable */
         vuint32_t  RUN0:1;            /* RUN0 mode enable */
         vuint32_t  DRUN:1;            /* DRUN mode enable */
         vuint32_t  SAFE:1;            /* SAFE mode enable */
         vuint32_t  TEST:1;            /* TEST mode enable */
         vuint32_t  RESET_FUNC:1;      /* Functional RESET mode enable */
      } B;
   } ME_MEN_32B_tag;

   typedef union {   /* Interrupt Status Register */
      vuint32_t R;
      struct {
         vuint32_t:27;
         vuint32_t  I_ICONF_CU:1;      /* Invalid mode configuration interrupt (clock usage) */
         vuint32_t  I_ICONF:1;         /* Invalid mode configuration interrupt */
         vuint32_t  I_IMODE:1;         /* Invalid mode interrupt */
         vuint32_t  I_SAFE:1;          /* SAFE mode interrupt */
         vuint32_t  I_MTC:1;           /* Mode transition complete interrupt */
      } B;
   } ME_IS_32B_tag;

   typedef union {   /* Interrupt Mask Register */
      vuint32_t R;
      struct {
         vuint32_t:27;
         vuint32_t  M_ICONF_CU:1;      /* Invalid mode configuration interrupt mask (clock usage) */
         vuint32_t  M_ICONF:1;         /* Invalid mode configuration interrupt mask */
         vuint32_t  M_IMODE:1;         /* Invalid mode interrupt mask */
         vuint32_t  M_SAFE:1;          /* SAFE mode interrupt mask */
         vuint32_t  M_MTC:1;           /* Mode transition complete interrupt mask */
      } B;
   } ME_IM_32B_tag;

   typedef union {   /* Invalid Mode Transition Status Register */
      vuint32_t R;
      struct {
         vuint32_t:27;
         vuint32_t  S_MTI:1;           /* Mode Transition Illegal status */
         vuint32_t  S_MRI:1;           /* Mode Request Illegal status */
         vuint32_t  S_DMA:1;           /* Disabled Mode Access status */
         vuint32_t  S_NMA:1;           /* Non-existing Mode Access status */
         vuint32_t  S_SEA:1;           /* SAFE Event Active status */
      } B;
   } ME_IMTS_32B_tag;

   typedef union {   /* Debug Mode Transition Status Register */
      vuint32_t R;
      struct {
         vuint32_t  PREVIOUS_MODE:4;   /* Previous Device Mode */
         vuint32_t:4;
         vuint32_t  MPH_BUSY:1;        /* MC_ME/MC_PCU Handshake Busy indicator */
         vuint32_t:2;
         vuint32_t  PMC_PROG:1;        /* MC_PCU Mode Change in Progress indicator */
         vuint32_t  CORE_DBG:1;        /* Processor is in Debug mode indicator */
         vuint32_t:2;
         vuint32_t  SMR:1;             /* SAFE mode request is active indicator */
         vuint32_t:1;
         vuint32_t  VREG_CSRC_SC:1;    /* Main VREG Clock Source State Change indicator */
         vuint32_t  CSRC_CSRC_SC:1;    /* (Other) Clock Source dependent Clock Source State Change indicator */
         vuint32_t  IRCOSC_SC:1;       /* IRCOSC State Change indicator */
         vuint32_t  SCSRC_SC:1;        /* Secondary Clock Sources State Change during mode transition indicator */
         vuint32_t  SYSCLK_SW:1;       /* System Clock Switching pending status */
         vuint32_t:1;
         vuint32_t  FLASH_SC:1;        /* FLASH State Change indicator */
         vuint32_t  CDP_PRPH_0_143:1;   /* Clock Disable Process Pending Status for Periph. 0-143 */
         vuint32_t:4;
         vuint32_t  CDP_PRPH_64_95:1;   /* Clock Disable Process Pending Status for Periph. 64-95 */
         vuint32_t  CDP_PRPH_32_63:1;   /* Clock Disable Process Pending Status for Periph. 32-63 */
         vuint32_t  CDP_PRPH_0_31:1;   /* Clock Disable Process Pending Status for Periph. 0-31 */
      } B;
   } ME_DMTS_32B_tag;

   typedef union {   /* RESET Mode Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t:8;
         vuint32_t  PDO:1;             /* IOs output power-down control */
         vuint32_t:2;
         vuint32_t  MVRON:1;           /* Main voltage regulator control */
         vuint32_t:2;
         vuint32_t  FLAON:2;           /* Flash power-down control */
         vuint32_t:8;
         vuint32_t  PLL1ON:1;          /* Secondary PLL control */
         vuint32_t  PLL0ON:1;          /* System PLL control */
         vuint32_t  XOSCON:1;          /* System crystal oscillator control */
         vuint32_t  IRCOSCON:1;        /* System RC oscillator control */
         vuint32_t  SYSCLK:4;          /* System clock switch control */
      } B;
   } ME_RESET_MC_32B_tag;

   typedef union {   /* TEST Mode Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t:8;
         vuint32_t  PDO:1;             /* IOs output power-down control */
         vuint32_t:2;
         vuint32_t  MVRON:1;           /* Main voltage regulator control */
         vuint32_t:2;
         vuint32_t  FLAON:2;           /* Flash power-down control */
         vuint32_t:8;
         vuint32_t  PLL1ON:1;          /* Secondary PLL control */
         vuint32_t  PLL0ON:1;          /* System PLL control */
         vuint32_t  XOSCON:1;          /* System crystal oscillator control */
         vuint32_t  IRCOSCON:1;        /* System RC oscillator control */
         vuint32_t  SYSCLK:4;          /* System clock switch control */
      } B;
   } ME_TEST_MC_32B_tag;

   typedef union {   /* SAFE Mode Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t:8;
         vuint32_t  PDO:1;             /* IOs output power-down control */
         vuint32_t:2;
         vuint32_t  MVRON:1;           /* Main voltage regulator control */
         vuint32_t:2;
         vuint32_t  FLAON:2;           /* Flash power-down control */
         vuint32_t:8;
         vuint32_t  PLL1ON:1;          /* Secondary PLL control */
         vuint32_t  PLL0ON:1;          /* System PLL control */
         vuint32_t  XOSCON:1;          /* System crystal oscillator control */
         vuint32_t  IRCOSCON:1;        /* System RC oscillator control */
         vuint32_t  SYSCLK:4;          /* System clock switch control */
      } B;
   } ME_SAFE_MC_32B_tag;

   typedef union {   /* DRUN Mode Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t:8;
         vuint32_t  PDO:1;             /* IOs output power-down control */
         vuint32_t:2;
         vuint32_t  MVRON:1;           /* Main voltage regulator control */
         vuint32_t:2;
         vuint32_t  FLAON:2;           /* Flash power-down control */
         vuint32_t:8;
         vuint32_t  PLL1ON:1;          /* Secondary PLL control */
         vuint32_t  PLL0ON:1;          /* System PLL control */
         vuint32_t  XOSCON:1;          /* System crystal oscillator control */
         vuint32_t  IRCOSCON:1;        /* System RC oscillator control */
         vuint32_t  SYSCLK:4;          /* System clock switch control */
      } B;
   } ME_DRUN_MC_32B_tag;

   typedef union {   /* RUNn Mode Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t:8;
         vuint32_t  PDO:1;             /* IOs output power-down control */
         vuint32_t:2;
         vuint32_t  MVRON:1;           /* Main voltage regulator control */
         vuint32_t:2;
         vuint32_t  FLAON:2;           /* Flash power-down control */
         vuint32_t:8;
         vuint32_t  PLL1ON:1;          /* Secondary PLL control */
         vuint32_t  PLL0ON:1;          /* System PLL control */
         vuint32_t  XOSCON:1;          /* System crystal oscillator control */
         vuint32_t  IRCOSCON:1;        /* System RC oscillator control */
         vuint32_t  SYSCLK:4;          /* System clock switch control */
      } B;
   } ME_RUN_MC_32B_tag;

   typedef union {   /* HALT0 Mode Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t:8;
         vuint32_t  PDO:1;             /* IOs output power-down control */
         vuint32_t:2;
         vuint32_t  MVRON:1;           /* Main voltage regulator control */
         vuint32_t:2;
         vuint32_t  FLAON:2;           /* Flash power-down control */
         vuint32_t:8;
         vuint32_t  PLL1ON:1;          /* Secondary PLL control */
         vuint32_t  PLL0ON:1;          /* System PLL control */
         vuint32_t  XOSCON:1;          /* System crystal oscillator control */
         vuint32_t  IRCOSCON:1;        /* System RC oscillator control */
         vuint32_t  SYSCLK:4;          /* System clock switch control */
      } B;
   } ME_HALT0_MC_32B_tag;

   typedef union {   /* STOP0 Mode Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t:8;
         vuint32_t  PDO:1;             /* IOs output power-down control */
         vuint32_t:2;
         vuint32_t  MVRON:1;           /* Main voltage regulator control */
         vuint32_t:2;
         vuint32_t  FLAON:2;           /* Flash power-down control */
         vuint32_t:8;
         vuint32_t  PLL1ON:1;          /* Secondary PLL control */
         vuint32_t  PLL0ON:1;          /* System PLL control */
         vuint32_t  XOSCON:1;          /* System crystal oscillator control */
         vuint32_t  IRCOSCON:1;        /* System RC oscillator control */
         vuint32_t  SYSCLK:4;          /* System clock switch control */
      } B;
   } ME_STOP0_MC_32B_tag;

   typedef union {   /* Peripheral Status Register 0 */
      vuint32_t R;
      struct {
         vuint32_t:7;
         vuint32_t  S_FLEXRAY:1;       /* FlexRay status */
         vuint32_t:5;
         vuint32_t  S_FLEXCAN2:1;      /* FlexCAN2 status */
         vuint32_t  S_FLEXCAN1:1;      /* FlexCAN1 status */
         vuint32_t  S_FLEXCAN0:1;      /* FlexCAN0 status */
         vuint32_t:9;
         vuint32_t  S_DSPI2:1;         /* DSPI2 status */
         vuint32_t  S_DSPI1:1;         /* DSPI1 status */
         vuint32_t  S_DSPI0:1;         /* DSPI0 status */
         vuint32_t:4;
      } B;
   } ME_PS0_32B_tag;

   typedef union {   /* Peripheral Status Register 1 */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  S_SWG:1;           /* SWG status */
         vuint32_t:3;
         vuint32_t  S_CRC:1;           /* CRC status */
         vuint32_t:8;
         vuint32_t  S_LINFLEX1:1;      /* LINFlex1 status */
         vuint32_t  S_LINFLEX0:1;      /* LINFlex0 status */
         vuint32_t:5;
         vuint32_t  S_FLEXPWM1:1;      /* FlexPWM1 status */
         vuint32_t  S_FLEXPWM0:1;      /* FlexPWM0 status */
         vuint32_t  S_ETIMER2:1;       /* eTimer2 status */
         vuint32_t  S_ETIMER1:1;       /* eTimer1 status */
         vuint32_t  S_ETIMER0:1;       /* eTimer0 status */
         vuint32_t:2;
         vuint32_t  S_CTU:1;           /* CTU status */
         vuint32_t:1;
         vuint32_t  S_ADC1:1;          /* ADC1 status */
         vuint32_t  S_ADC0:1;          /* ADC0 status */
      } B;
   } ME_PS1_32B_tag;

   typedef union {   /* Peripheral Status Register 2 */
      vuint32_t R;
      struct {
         vuint32_t:3;
         vuint32_t  S_PIT:1;           /* PIT status */
         vuint32_t:28;
      } B;
   } ME_PS2_32B_tag;


   /* Register layout for all registers RUN_PC ... */

   typedef union {   /* ME_RUN_PC[0...7] - RUN Peripheral Configuration Registers */
      vuint32_t R;
      struct {
         vuint32_t:24;
         vuint32_t  RUN3:1;            /* Peripheral control during RUN3 */
         vuint32_t  RUN2:1;            /* Peripheral control during RUN2 */
         vuint32_t  RUN1:1;            /* Peripheral control during RUN1 */
         vuint32_t  RUN0:1;            /* Peripheral control during RUN0 */
         vuint32_t  DRUN:1;            /* Peripheral control during DRUN */
         vuint32_t  SAFE:1;            /* Peripheral control during SAFE */
         vuint32_t  TEST:1;            /* Peripheral control during TEST */
         vuint32_t  RESET:1;           /* Peripheral control during RESET */
      } B;
   } ME_RUN_PC_32B_tag;


   /* Register layout for all registers LP_PC ... */

   typedef union {   /* ME_LP_PC[0...7] - Low Power Peripheral Configuration Registers */
      vuint32_t R;
      struct {
         vuint32_t:21;
         vuint32_t  STOP0:1;           /* Peripheral control during STOP0 */
         vuint32_t:1;
         vuint32_t  HALT0:1;           /* Peripheral control during HALT0 */
         vuint32_t:8;
      } B;
   } ME_LP_PC_32B_tag;

   typedef union {   /* Peripheral Control Register 4 (DSPI0) */
      vuint8_t R;
      struct {
         vuint8_t:1;
         vuint8_t   DBG_F:1;           /* Peripheral control in debug mode */
         vuint8_t   LP_CFG:3;          /* Peripheral configuration select for non-RUN modes */
         vuint8_t   RUN_CFG:3;         /* Peripheral configuration select for RUN modes */
      } B;
   } ME_PCTL_8B_tag;


   typedef struct ME_struct_tag {

                                               /* Global Status Register */
      ME_GS_32B_tag GS;                    /* offset: 0x0000 size: 32 bit */
                                                /* Mode Control Register */
      ME_MCTL_32B_tag MCTL;                /* offset: 0x0004 size: 32 bit */
                                                 /* Mode Enable Register */
      ME_MEN_32B_tag MEN;                  /* offset: 0x0008 size: 32 bit */
                                            /* Interrupt Status Register */
      ME_IS_32B_tag IS;                    /* offset: 0x000C size: 32 bit */
                                              /* Interrupt Mask Register */
      ME_IM_32B_tag IM;                    /* offset: 0x0010 size: 32 bit */
                              /* Invalid Mode Transition Status Register */
      ME_IMTS_32B_tag IMTS;                /* offset: 0x0014 size: 32 bit */
                                /* Debug Mode Transition Status Register */
      ME_DMTS_32B_tag DMTS;                /* offset: 0x0018 size: 32 bit */
      int8_t ME_reserved_001C[4];
                                    /* RESET Mode Configuration Register */
      ME_RESET_MC_32B_tag RESET_MC;        /* offset: 0x0020 size: 32 bit */
                                     /* TEST Mode Configuration Register */
      ME_TEST_MC_32B_tag TEST_MC;          /* offset: 0x0024 size: 32 bit */
                                     /* SAFE Mode Configuration Register */
      ME_SAFE_MC_32B_tag SAFE_MC;          /* offset: 0x0028 size: 32 bit */
                                     /* DRUN Mode Configuration Register */
      ME_DRUN_MC_32B_tag DRUN_MC;          /* offset: 0x002C size: 32 bit */
      union {
         ME_RUN_MC_32B_tag RUN_MC[4];      /* offset: 0x0030  (0x0004 x 4) */

         struct {
                                     /* RUNn Mode Configuration Register */
            ME_RUN_MC_32B_tag RUN0_MC;     /* offset: 0x0030 size: 32 bit */
                                     /* RUNn Mode Configuration Register */
            ME_RUN_MC_32B_tag RUN1_MC;     /* offset: 0x0034 size: 32 bit */
                                     /* RUNn Mode Configuration Register */
            ME_RUN_MC_32B_tag RUN2_MC;     /* offset: 0x0038 size: 32 bit */
                                     /* RUNn Mode Configuration Register */
            ME_RUN_MC_32B_tag RUN3_MC;     /* offset: 0x003C size: 32 bit */
         };

      };
                                    /* HALT0 Mode Configuration Register */
      ME_HALT0_MC_32B_tag HALT0_MC;        /* offset: 0x0040 size: 32 bit */
      int8_t ME_reserved_0044[4];
                                    /* STOP0 Mode Configuration Register */
      ME_STOP0_MC_32B_tag STOP0_MC;        /* offset: 0x0048 size: 32 bit */
      int8_t ME_reserved_004C[20];
                                         /* Peripheral Status Register 0 */
      ME_PS0_32B_tag PS0;                  /* offset: 0x0060 size: 32 bit */
                                         /* Peripheral Status Register 1 */
      ME_PS1_32B_tag PS1;                  /* offset: 0x0064 size: 32 bit */
                                         /* Peripheral Status Register 2 */
      ME_PS2_32B_tag PS2;                  /* offset: 0x0068 size: 32 bit */
      int8_t ME_reserved_006C[20];
      union {
            /* ME_RUN_PC[0...7] - RUN Peripheral Configuration Registers */
         ME_RUN_PC_32B_tag RUN_PC[8];      /* offset: 0x0080  (0x0004 x 8) */

         struct {
            /* ME_RUN_PC[0...7] - RUN Peripheral Configuration Registers */
            ME_RUN_PC_32B_tag RUN_PC0;     /* offset: 0x0080 size: 32 bit */
            ME_RUN_PC_32B_tag RUN_PC1;     /* offset: 0x0084 size: 32 bit */
            ME_RUN_PC_32B_tag RUN_PC2;     /* offset: 0x0088 size: 32 bit */
            ME_RUN_PC_32B_tag RUN_PC3;     /* offset: 0x008C size: 32 bit */
            ME_RUN_PC_32B_tag RUN_PC4;     /* offset: 0x0090 size: 32 bit */
            ME_RUN_PC_32B_tag RUN_PC5;     /* offset: 0x0094 size: 32 bit */
            ME_RUN_PC_32B_tag RUN_PC6;     /* offset: 0x0098 size: 32 bit */
            ME_RUN_PC_32B_tag RUN_PC7;     /* offset: 0x009C size: 32 bit */
         };

      };
      union {
       /* ME_LP_PC[0...7] - Low Power Peripheral Configuration Registers */
         ME_LP_PC_32B_tag LP_PC[8];        /* offset: 0x00A0  (0x0004 x 8) */

         struct {
           /* ME_LP_PC[0...7] - Low Power Peripheral Configuration Registers */
            ME_LP_PC_32B_tag LP_PC0;       /* offset: 0x00A0 size: 32 bit */
            ME_LP_PC_32B_tag LP_PC1;       /* offset: 0x00A4 size: 32 bit */
            ME_LP_PC_32B_tag LP_PC2;       /* offset: 0x00A8 size: 32 bit */
            ME_LP_PC_32B_tag LP_PC3;       /* offset: 0x00AC size: 32 bit */
            ME_LP_PC_32B_tag LP_PC4;       /* offset: 0x00B0 size: 32 bit */
            ME_LP_PC_32B_tag LP_PC5;       /* offset: 0x00B4 size: 32 bit */
            ME_LP_PC_32B_tag LP_PC6;       /* offset: 0x00B8 size: 32 bit */
            ME_LP_PC_32B_tag LP_PC7;       /* offset: 0x00BC size: 32 bit */
         };

      };
      union {
         ME_PCTL_8B_tag PCTL[144];         /* offset: 0x00C0  (0x0001 x 144) */

         struct {
            int8_t ME_reserved_00C0_I1[4];
                                /* Peripheral Control Register 4 (DSPI0) */
            ME_PCTL_8B_tag PCTL4;          /* offset: 0x00C4 size: 8 bit */
                                /* Peripheral Control Register 5 (DSPI1) */
            ME_PCTL_8B_tag PCTL5;          /* offset: 0x00C5 size: 8 bit */
                                /* Peripheral Control Register 6 (DSPI2) */
            ME_PCTL_8B_tag PCTL6;          /* offset: 0x00C6 size: 8 bit */
            int8_t ME_reserved_00C7_I1[9];
                            /* Peripheral Control Register 16 (FLEXCAN0) */
            ME_PCTL_8B_tag PCTL16;         /* offset: 0x00D0 size: 8 bit */
                            /* Peripheral Control Register 17 (FLEXCAN1) */
            ME_PCTL_8B_tag PCTL17;         /* offset: 0x00D1 size: 8 bit */
                            /* Peripheral Control Register 18 (FLEXCAN2) */
            ME_PCTL_8B_tag PCTL18;         /* offset: 0x00D2 size: 8 bit */
            int8_t ME_reserved_00D2_I1[5];
                             /* Peripheral Control Register 24 (FLEXRAY) */
            ME_PCTL_8B_tag PCTL24;         /* offset: 0x00D8 size: 8 bit */
            int8_t ME_reserved_00D9_I1[7];
                                /* Peripheral Control Register 32 (ADC0) */
            ME_PCTL_8B_tag PCTL32;         /* offset: 0x00E0 size: 8 bit */
                                /* Peripheral Control Register 33 (ADC1) */
            ME_PCTL_8B_tag PCTL33;         /* offset: 0x00E1 size: 8 bit */
            int8_t ME_reserved_00E2_I1;
                                 /* Peripheral Control Register 35 (CTU) */
            ME_PCTL_8B_tag PCTL35;         /* offset: 0x00E3 size: 8 bit */
            int8_t ME_reserved_00E4_I1[2];
                             /* Peripheral Control Register 38 (ETIMER0) */
            ME_PCTL_8B_tag PCTL38;         /* offset: 0x00E6 size: 8 bit */
                             /* Peripheral Control Register 39 (ETIMER1) */
            ME_PCTL_8B_tag PCTL39;         /* offset: 0x00E7 size: 8 bit */
                             /* Peripheral Control Register 40 (ETIMER2) */
            ME_PCTL_8B_tag PCTL40;         /* offset: 0x00E8 size: 8 bit */
                            /* Peripheral Control Register 41 (FLEXPWM0) */
            ME_PCTL_8B_tag PCTL41;         /* offset: 0x00E9 size: 8 bit */
                            /* Peripheral Control Register 42 (FLEXPWM1) */
            ME_PCTL_8B_tag PCTL42;         /* offset: 0x00EA size: 8 bit */
            int8_t ME_reserved_00EB_I1[5];
                            /* Peripheral Control Register 48 (LINFLEX0) */
            ME_PCTL_8B_tag PCTL48;         /* offset: 0x00F0 size: 8 bit */
                            /* Peripheral Control Register 49 (LINFLEX1) */
            ME_PCTL_8B_tag PCTL49;         /* offset: 0x00F1 size: 8 bit */
            int8_t ME_reserved_00F2_I1[8];
                                 /* Peripheral Control Register 58 (CRC) */
            ME_PCTL_8B_tag PCTL58;         /* offset: 0x00FA size: 8 bit */
            int8_t ME_reserved_00FB_I1[3];
                                 /* Peripheral Control Register 62 (SWG) */
            ME_PCTL_8B_tag PCTL62;         /* offset: 0x00FE size: 8 bit */
            int8_t ME_reserved_00FF_I1[29];
                                 /* Peripheral Control Register 92 (PIT) */
            ME_PCTL_8B_tag PCTL92;         /* offset: 0x011C size: 8 bit */
            int8_t ME_reserved_011D_E1[51];
         };

      };
      int8_t ME_reserved_0150[16048];

   } ME_tag;


#define ME_BASEADDRESS 0xC3FDC000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define ME    (*(volatile ME_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FDC000UL))



/****************************************************************/
/*                                                              */
/* Module: OSC  */
/*                                                              */
/****************************************************************/

   typedef union {   /* OSC_CTL - Control Register */
      vuint32_t R;
      struct {
         vuint32_t  OSCBYP:1;          /* External crystal oscillator bypass */
         vuint32_t:7;
         vuint32_t  EOCV:8;            /* End of Count Value */
         vuint32_t  M_OSC:1;           /* External Crystal oscillator clock interrupt mask */
         vuint32_t:7;
         vuint32_t  I_OSC:1;           /* External Crystal oscillator clock interrupt */
         vuint32_t:7;
      } B;
   } OSC_CTL_32B_tag;


   typedef struct OSC_struct_tag {

                                           /* OSC_CTL - Control Register */
      OSC_CTL_32B_tag CTL;                 /* offset: 0x0000 size: 32 bit */
      int8_t OSC_reserved_0004[92];

   } OSC_tag;


#define OSC_BASEADDRESS 0xC3FE0000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define OSC   (*(volatile OSC_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FE0000UL))



/****************************************************************/
/*                                                              */
/* Module: RC  */
/*                                                              */
/****************************************************************/

   typedef union {   /* RC_CTL - Control Register */
      vuint32_t R;
      struct {
         vuint32_t:10;
         vuint32_t  RCTRIM:6;          /* Main RC Trimming Bits */
         vuint32_t:3;
         vuint32_t  RCDIV:5;           /* Main RC Clock Division Factor */
         vuint32_t:2;
         vuint32_t  S_RC_STDBY:1;      /* MRC Oscillator Powerdown Status */
         vuint32_t:5;
      } B;
   } RC_CTL_32B_tag;


   typedef struct RC_struct_tag {

                                            /* RC_CTL - Control Register */
      RC_CTL_32B_tag CTL;                  /* offset: 0x0000 size: 32 bit */
      int8_t RC_reserved_0004[16380];

   } RC_tag;


#define RC_BASEADDRESS 0xC3FE0060UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define RC    (*(volatile RC_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FE0060UL))



/****************************************************************/
/*                                                              */
/* Module: PLLD  */
/*                                                              */
/****************************************************************/

   typedef union {   /* PLLD_CR - Control Register */
      vuint32_t R;
      struct {
         vuint32_t:2;
         vuint32_t  IDF:4;             /* PLL Input Division Factor */
         vuint32_t  ODF:2;             /* PLL Output Division Factor */
         vuint32_t:1;
         vuint32_t  NDIV:7;            /* PLL Loop Division Factor */
         vuint32_t:7;
         vuint32_t  EN_PLL_SW:1;       /* Enable Progressive Clock Switching */
         vuint32_t  MODE:1;            /* Activate 1:1 Mode */
         vuint32_t  UNLOCK_ONCE:1;     /* PLL Loss of Lock */
         vuint32_t  M_LOCK:1;          /* Mask for the i_lock Output Interrupt */
         vuint32_t  I_LOCK:1;          /* PLL Lock Signal Toggle Indicator */
         vuint32_t  S_LOCK:1;          /* PLL has Aquired Lock */
         vuint32_t  PLL_FAIL_MASK:1;   /* PLL Fail Mask */
         vuint32_t  PLL_FAIL_FLAG:1;   /* PLL Fail Flag */
         vuint32_t:1;
      } B;
   } PLLD_CR_32B_tag;

   typedef union {   /* PLLD_MR - PLLD Modulation Register */
      vuint32_t R;
      struct {
         vuint32_t  STRB_BYPASS:1;     /* Strobe Bypass */
         vuint32_t:1;
         vuint32_t  SPRD_SEL:1;        /* Spread Type Selection */
         vuint32_t  MOD_PERIOD:13;     /* Modulation Period */
         vuint32_t  SSCG_EN:1;         /* Spread Spectrum Clock Generation Enable */
         vuint32_t  INC_STEP:15;       /* Increment Step */
      } B;
   } PLLD_MR_32B_tag;


   typedef struct PLLD_struct_tag {

                                           /* PLLD_CR - Control Register */
      PLLD_CR_32B_tag CR;                  /* offset: 0x0000 size: 32 bit */
                                   /* PLLD_MR - PLLD Modulation Register */
      PLLD_MR_32B_tag MR;                  /* offset: 0x0004 size: 32 bit */
      int8_t PLLD_reserved_0008[24];

   } PLLD_tag;


#define PLLD0_BASEADDRESS 0xC3FE00A0UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define PLLD0 (*(volatile PLLD_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FE00A0UL))
#define PLLD1_BASEADDRESS 0xC3FE00C0UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define PLLD1 (*(volatile PLLD_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FE00C0UL))



/****************************************************************/
/*                                                              */
/* Module: CMU  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Control Status Register */
      vuint32_t R;
      struct {
         vuint32_t:8;
         vuint32_t  SFM:1;             /* Start frequency measure */
         vuint32_t:13;
         vuint32_t  CKSEL1:2;          /* Frequency measure clock selection */
         vuint32_t:5;
         vuint32_t  RCDIV:2;           /* Clock division factor */
         vuint32_t  CME_A:1;           /* Clock monitor enable */
      } B;
   } CMU_CSR_32B_tag;

   typedef union {   /* Frequency Display Register */
      vuint32_t R;
      struct {
         vuint32_t:12;
         vuint32_t  FD:20;             /* Measured Frequency Bits */
      } B;
   } CMU_FDR_32B_tag;

   typedef union {   /* High Frequency Reference Register */
      vuint32_t R;
      struct {
         vuint32_t:20;
         vuint32_t  HFREF_A:12;        /* High Frequency reference value */
      } B;
   } CMU_HFREFR_A_32B_tag;

   typedef union {   /* Low Frequency Reference Register */
      vuint32_t R;
      struct {
         vuint32_t:20;
         vuint32_t  LFREF_A:12;        /* Low Frequency reference value */
      } B;
   } CMU_LFREFR_A_32B_tag;

   typedef union {   /* CMU_ISR - Interrupt Status Register */
      vuint32_t R;
      struct {
         vuint32_t:28;
         vuint32_t  FLCI_A:1;          /* CLKMN1 clock frequency less than reference clock interrupt */
         vuint32_t  FHHI_A:1;          /* CLKMN1 clock frequency higher than high reference interrupt */
         vuint32_t  FLLI_A:1;          /* CLKMN1 clock frequency less than low reference interrupt */
         vuint32_t  OLRI:1;            /* Oscillator frequency less than RC frequency interrupt */
      } B;
   } CMU_ISR_32B_tag;

   typedef union {   /* Interrupt Mask Register */
      vuint32_t R;
   } CMU_IMR_32B_tag;

   typedef union {   /* Measurement Duration Register */
      vuint32_t R;
      struct {
         vuint32_t:12;
         vuint32_t  MD:20;             /* Measurment Duration Bits */
      } B;
   } CMU_MDR_32B_tag;


   typedef struct CMU_struct_tag {

                                              /* Control Status Register */
      CMU_CSR_32B_tag CSR;                 /* offset: 0x0000 size: 32 bit */
                                           /* Frequency Display Register */
      CMU_FDR_32B_tag FDR;                 /* offset: 0x0004 size: 32 bit */
                                    /* High Frequency Reference Register */
      CMU_HFREFR_A_32B_tag HFREFR_A;       /* offset: 0x0008 size: 32 bit */
                                     /* Low Frequency Reference Register */
      CMU_LFREFR_A_32B_tag LFREFR_A;       /* offset: 0x000C size: 32 bit */
                                  /* CMU_ISR - Interrupt Status Register */
      CMU_ISR_32B_tag ISR;                 /* offset: 0x0010 size: 32 bit */
                                              /* Interrupt Mask Register */
      CMU_IMR_32B_tag IMR;                 /* offset: 0x0014 size: 32 bit */
                                        /* Measurement Duration Register */
      CMU_MDR_32B_tag MDR;                 /* offset: 0x0018 size: 32 bit */
      int8_t CMU_reserved_001C[16356];

   } CMU_tag;


#define CMU0_BASEADDRESS 0xC3FE0100UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define CMU0  (*(volatile CMU_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FE0100UL))
#define CMU1_BASEADDRESS 0xC3FE0120UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define CMU1  (*(volatile CMU_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FE0120UL))
#define CMU2_BASEADDRESS 0xC3FE0140UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define CMU2  (*(volatile CMU_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FE0140UL))



/****************************************************************/
/*                                                              */
/* Module: CGM  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Output Clock Enable Register */
      vuint32_t R;
      vuint8_t   BYTE[4];    /* individual bytes can be accessed */
      vuint16_t  HALF[2];    /* individual halfwords can be accessed */
      vuint32_t  WORD;       /* individual words can be accessed */
      struct {
         vuint32_t:31;
         vuint32_t  EN:1;              /* Clock Enable Bit */
      } B;
   } CGM_OC_EN_32B_tag;

   typedef union {   /* Output Clock Division Select Register */
      vuint32_t R;
      vuint8_t   BYTE[4];    /* individual bytes can be accessed */
      vuint16_t  HALF[2];    /* individual halfwords can be accessed */
      vuint32_t  WORD;       /* individual words can be accessed */
      struct {
         vuint32_t:2;
         vuint32_t  SELDIV:2;          /* Output Clock Division Select */
         vuint32_t  SELCTL:4;          /* Output Clock Source Selection Control */
         vuint32_t:24;
      } B;
   } CGM_OCDS_SC_32B_tag;

   typedef union {   /* System Clock Select Status Register */
      vuint32_t R;
      vuint8_t   BYTE[4];    /* individual bytes can be accessed */
      vuint16_t  HALF[2];    /* individual halfwords can be accessed */
      vuint32_t  WORD;       /* individual words can be accessed */
      struct {
         vuint32_t:4;
         vuint32_t  SELSTAT:4;         /* System Clock Source Selection Status */
         vuint32_t:24;
      } B;
   } CGM_SC_SS_32B_tag;

   typedef union {   /* Combined System Clock Divider Configuration Register */
      vuint32_t R;
      vuint8_t   BYTE[4];    /* individual bytes can be accessed */
      vuint16_t  HALF[2];    /* individual halfwords can be accessed */
      vuint32_t  WORD;       /* individual words can be accessed */
      struct {
         vuint32_t  DE0:1;             /* Divider 0 Enable */
         vuint32_t:3;
         vuint32_t  DIV0:4;            /* Divider 0 Value */
         vuint32_t:24;
      } B;
   } CGM_SC_DC0_3_32B_tag;

   typedef union {   /* System Clock Divider Configuration Register */
      vuint8_t R;
      struct {
         vuint8_t   DE:1;              /* Divider Enable */
         vuint8_t:3;
         vuint8_t   DIV:4;             /* Divider Division Value */
      } B;
   } CGM_SC_DC0_8B_tag;

   typedef union {   /* Auxiliary Clock #0 Select Control Register */
      vuint32_t R;
      struct {
         vuint32_t:4;
         vuint32_t  SELCTL:4;          /* Auxiliary Clock Source Selection Control */
         vuint32_t:24;
      } B;
   } CGM_AC0_SC_32B_tag;

   typedef union {   /*  */
      vuint8_t R;
      struct {
         vuint8_t   DE:1;              /* Divider Enable */
         vuint8_t:3;
         vuint8_t   DIV:4;             /* Divider Division Value */
      } B;
   } CGM_AC_DC_8B_tag;

   typedef union {   /* Combined Auxiliary Clock Divider Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t  DE0:1;             /* Divider 0 Enable */
         vuint32_t:3;
         vuint32_t  DIV0:4;            /* Divider 0 Value */
         vuint32_t  DE1:1;             /* Divider 1 Enable */
         vuint32_t:3;
         vuint32_t  DIV1:4;            /* Divider 1 Value */
         vuint32_t:16;
      } B;
   } CGM_AC0_DC0_3_32B_tag;

   typedef union {   /* Auxiliary Clock #1 Select Control Register */
      vuint32_t R;
      struct {
         vuint32_t:4;
         vuint32_t  SELCTL:4;          /* Auxiliary Clock Source Selection Control */
         vuint32_t:24;
      } B;
   } CGM_AC1_SC_32B_tag;

   typedef union {   /* Combined Auxiliary Clock Divider Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t  DE0:1;             /* Divider 0 Enable */
         vuint32_t:3;
         vuint32_t  DIV0:4;            /* Divider 0 Value */
         vuint32_t:24;
      } B;
   } CGM_AC1_DC0_3_32B_tag;

   typedef union {   /* Auxiliary Clock #2 Select Control Register */
      vuint32_t R;
      struct {
         vuint32_t:4;
         vuint32_t  SELCTL:4;          /* Auxiliary Clock Source Selection Control */
         vuint32_t:24;
      } B;
   } CGM_AC2_SC_32B_tag;

   typedef union {   /* Combined Auxiliary Clock Divider Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t  DE0:1;             /* Divider 0 Enable */
         vuint32_t:3;
         vuint32_t  DIV0:4;            /* Divider 0 Value */
         vuint32_t:24;
      } B;
   } CGM_AC2_DC0_3_32B_tag;

   typedef union {   /* Auxiliary Clock #3 Select Control Register */
      vuint32_t R;
      struct {
         vuint32_t:7;
         vuint32_t  SELCTL:1;          /* Auxiliary Clock Source Selection Control */
         vuint32_t:24;
      } B;
   } CGM_AC3_SC_32B_tag;

   typedef union {   /* Auxiliary Clock #4 Select Control Register */
      vuint32_t R;
      struct {
         vuint32_t:7;
         vuint32_t  SELCTL:1;          /* Auxiliary Clock Source Selection Control */
         vuint32_t:24;
      } B;
   } CGM_AC4_SC_32B_tag;


   typedef struct CGM_struct_tag {

      OSC_CTL_32B_tag OSC_CTL;             /* offset: 0x0000 size: 32 bit */
      int8_t CGM_reserved_0004[92];
      RC_CTL_32B_tag RC_CTL;               /* offset: 0x0060 size: 32 bit */
      int8_t CGM_reserved_0064[60];
      PLLD_tag FMPLL[2];                   /* offset: 0x00A0  (0x0020 x 2) */
      int8_t CGM_reserved_00E0[32];
      CMU_CSR_32B_tag CMU_0_CSR;           /* offset: 0x0100 size: 32 bit */
      CMU_FDR_32B_tag CMU_0_FDR;           /* offset: 0x0104 size: 32 bit */
      CMU_HFREFR_A_32B_tag CMU_0_HFREFR_A;  /* offset: 0x0108 size: 32 bit */
      CMU_LFREFR_A_32B_tag CMU_0_LFREFR_A;  /* offset: 0x010C size: 32 bit */
      CMU_ISR_32B_tag CMU_0_ISR;           /* offset: 0x0110 size: 32 bit */
      CMU_IMR_32B_tag CMU_0_IMR;           /* offset: 0x0114 size: 32 bit */
      CMU_MDR_32B_tag CMU_0_MDR;           /* offset: 0x0118 size: 32 bit */
      int8_t CGM_reserved_011C[4];
      CMU_CSR_32B_tag CMU_1_CSR;           /* offset: 0x0120 size: 32 bit */
      int8_t CGM_reserved_0124[4];
      CMU_HFREFR_A_32B_tag CMU_1_HFREFR_A;  /* offset: 0x0128 size: 32 bit */
      CMU_LFREFR_A_32B_tag CMU_1_LFREFR_A;  /* offset: 0x012C size: 32 bit */
      CMU_ISR_32B_tag CMU_1_ISR;           /* offset: 0x0130 size: 32 bit */
      int8_t CGM_reserved_0134[572];
                                         /* Output Clock Enable Register */
      CGM_OC_EN_32B_tag OC_EN;             /* offset: 0x0370 size: 32 bit */
                                /* Output Clock Division Select Register */
      CGM_OCDS_SC_32B_tag OCDS_SC;         /* offset: 0x0374 size: 32 bit */
                                  /* System Clock Select Status Register */
      CGM_SC_SS_32B_tag SC_SS;             /* offset: 0x0378 size: 32 bit */
      union {
                 /* Combined System Clock Divider Configuration Register */
         CGM_SC_DC0_3_32B_tag SC_DC0_3;    /* offset: 0x037C size: 32 bit */

         struct {
                          /* System Clock Divider Configuration Register */
            CGM_SC_DC0_8B_tag SC_DC0;      /* offset: 0x037C size: 8 bit */
            int8_t CGM_reserved_037D_E1[3];
         };

      };
                           /* Auxiliary Clock #0 Select Control Register */
      CGM_AC0_SC_32B_tag AC0_SC;           /* offset: 0x0380 size: 32 bit */
      union {
              /* Combined Auxiliary Clock Divider Configuration Register */
         CGM_AC0_DC0_3_32B_tag AC0_DC0_3;  /* offset: 0x0384 size: 32 bit */

         struct {
            CGM_AC_DC_8B_tag AC0_DC0;      /* offset: 0x0384 size: 8 bit */
            CGM_AC_DC_8B_tag AC0_DC1;      /* offset: 0x0385 size: 8 bit */
            int8_t CGM_reserved_0386_E1[2];
         };

      };
                           /* Auxiliary Clock #1 Select Control Register */
      CGM_AC1_SC_32B_tag AC1_SC;           /* offset: 0x0388 size: 32 bit */
      union {
              /* Combined Auxiliary Clock Divider Configuration Register */
         CGM_AC1_DC0_3_32B_tag AC1_DC0_3;  /* offset: 0x038C size: 32 bit */

         struct {
            CGM_AC_DC_8B_tag AC1_DC0;      /* offset: 0x038C size: 8 bit */
            int8_t CGM_reserved_038D_E1[3];
         };

      };
                           /* Auxiliary Clock #2 Select Control Register */
      CGM_AC2_SC_32B_tag AC2_SC;           /* offset: 0x0390 size: 32 bit */
      union {
              /* Combined Auxiliary Clock Divider Configuration Register */
         CGM_AC2_DC0_3_32B_tag AC2_DC0_3;  /* offset: 0x0394 size: 32 bit */

         struct {
            CGM_AC_DC_8B_tag AC2_DC0;      /* offset: 0x0394 size: 8 bit */
            int8_t CGM_reserved_0395_E1[3];
         };

      };
                           /* Auxiliary Clock #3 Select Control Register */
      CGM_AC3_SC_32B_tag AC3_SC;           /* offset: 0x0398 size: 32 bit */
      int8_t CGM_reserved_039C[4];
                           /* Auxiliary Clock #4 Select Control Register */
      CGM_AC4_SC_32B_tag AC4_SC;           /* offset: 0x03A0 size: 32 bit */
      int8_t CGM_reserved_03A4[15452];

   } CGM_tag;


#define CGM_BASEADDRESS 0xC3FE0000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define CGM   (*(volatile CGM_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FE0000UL))



/****************************************************************/
/*                                                              */
/* Module: RGM  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Functional Event Status Register */
      vuint16_t R;
      struct {
         vuint16_t  F_EXR:1;           /* Flag for external reset */
         vuint16_t  F_FCCU_HARD:1;     /* Flag for FCCU hard reaction request */
         vuint16_t  F_FCCU_SOFT:1;     /* Flag for FCCU soft reaction request */
         vuint16_t  F_ST_DONE:1;       /* Flag for self-test completed */
         vuint16_t  F_CMU12_FHL:1;     /* Flag for motor control/FlexRay clock freq. too high/low */
         vuint16_t  F_FL_ECC_RCC:1;    /* Flag for Flash, ECC, or lock-step error */
         vuint16_t  F_PLL1:1;          /* Flag for PLL1 fail */
         vuint16_t  F_SWT:1;           /* Flag for software watchdog timer */
         vuint16_t  F_FCCU_SAFE:1;     /* Flag for FCCU SAFE mode request */
         vuint16_t  F_CMU0_FHL:1;      /* Flag for system clock freq. too high/low */
         vuint16_t  F_CMU0_OLR:1;      /* Flag for XOSC freq. too low */
         vuint16_t  F_PLL0:1;          /* Flag for PLL0 fail */
         vuint16_t  F_CWD:1;           /* Flag for core watchdog reset */
         vuint16_t  F_SOFT_FUNC:1;     /* Flag for software 'functional' reset */
         vuint16_t  F_CORE:1;          /* Flag for core reset */
         vuint16_t  F_JTAG:1;          /* Flag for JTAG initiated reset */
      } B;
   } RGM_FES_16B_tag;

   typedef union {   /* Destructive Event Status Register */
      vuint16_t R;
      struct {
         vuint16_t  F_POR:1;           /* Flag for power-on reset */
         vuint16_t  F_SOFT_DEST:1;     /* Flag for software 'destructive' reset */
         vuint16_t:7;
         vuint16_t  F_LVD27_IO:1;      /* Flag for 2.7V low-voltage detected (IO) */
         vuint16_t  F_LVD27_FLASH:1;   /* Flag for 2.7V low-voltage detected (Flash) */
         vuint16_t  F_LVD27_VREG:1;    /* Flag for 2.7V low-voltage detected (VREG) */
         vuint16_t:2;
         vuint16_t  F_HVD12:1;         /* Flag for 1.2V high-voltage detected */
         vuint16_t  F_LVD12:1;         /* Flag for 1.2V low-voltage detected */
      } B;
   } RGM_DES_16B_tag;

   typedef union {   /* Functional Event Reset Disable Register */
      vuint16_t R;
      struct {
         vuint16_t  D_EXR:1;           /* Disable external reset */
         vuint16_t  D_FCCU_HARD:1;     /* Disable FCCU hard reaction request */
         vuint16_t  D_FCCU_SOFT:1;     /* Disable FCCU soft reaction request */
         vuint16_t  D_ST_DONE:1;       /* Disable self-test completed */
         vuint16_t  D_CMU12_FHL:1;     /* Disable motor control/FlexRay clock freq. too high/low */
         vuint16_t  D_FL_ECC_RCC:1;    /* Disable Flash, ECC, or lock-step error */
         vuint16_t  D_PLL1:1;          /* Disable PLL1 fail */
         vuint16_t  D_SWT:1;           /* Disable software watchdog timer */
         vuint16_t  D_FCCU_SAFE:1;     /* Disable FCCU SAFE mode request */
         vuint16_t  D_CMU0_FHL:1;      /* Disable system clock freq. too high/low */
         vuint16_t  D_CMU0_OLR:1;      /* Disable XOSC freq. too low */
         vuint16_t  D_PLL0:1;          /* Disable PLL0 fail */
         vuint16_t  D_CWD:1;           /* Disable core watchdog reset */
         vuint16_t  D_SOFT_FUNC:1;     /* Disable software 'functional' reset */
         vuint16_t  D_CORE:1;          /* Disable core reset */
         vuint16_t  D_JTAG:1;          /* Disable JTAG initiated reset */
      } B;
   } RGM_FERD_16B_tag;

   typedef union {   /* Destructive Event Reset Disable Register */
      vuint16_t R;
      struct {
         vuint16_t:1;
         vuint16_t  D_SOFT_DEST:1;     /* Disable software 'destructive' reset */
         vuint16_t:7;
         vuint16_t  D_LVD27_IO:1;      /* Disable 2.7V low-voltage detected (IO) */
         vuint16_t  D_LVD27_FLASH:1;   /* Disable 2.7V low-voltage detected (Flash) */
         vuint16_t  D_LVD27_VREG:1;    /* Disable 2.7V low-voltage detected (VREG) */
         vuint16_t:2;
         vuint16_t  D_HVD12:1;         /* Disable 1.2V high-voltage detected */
         vuint16_t  D_LVD12:1;         /* Disable 1.2V low-voltage detected */
      } B;
   } RGM_DERD_16B_tag;

   typedef union {   /* Functional Event Alternate Request Register */
      vuint16_t R;
      struct {
         vuint16_t:4;
         vuint16_t  AR_CMU12_FHL:1;    /* Alternate Request for motor control/FlexRay clock freq. too high/low */
         vuint16_t:1;
         vuint16_t  AR_PLL1:1;         /* Alternate Request for PLL1 fail */
         vuint16_t:1;
         vuint16_t  AR_FCCU_SAFE:1;    /* Alternate Request for FCCU SAFE mode request */
         vuint16_t  AR_CMU0_FHL:1;     /* Alternate Request for system clock freq. too high/low */
         vuint16_t  AR_CMU0_OLR:1;     /* Alternate Request for XOSC freq. too low */
         vuint16_t  AR_PLL0:1;         /* Alternate Request for PLL0 fail */
         vuint16_t  AR_CWD:1;          /* Alternate Request for core watchdog reset */
         vuint16_t:3;
      } B;
   } RGM_FEAR_16B_tag;

   typedef union {   /* Functional Event Short Sequence Register */
      vuint16_t R;
      struct {
         vuint16_t  SS_EXR:1;          /* Short Sequence for external reset */
         vuint16_t  SS_FCCU_HARD:1;    /* Short Sequence for FCCU hard reaction request */
         vuint16_t  SS_FCCU_SOFT:1;    /* Short Sequence for FCCU soft reaction request */
         vuint16_t  SS_ST_DONE:1;      /* Short Sequence for self-test completed */
         vuint16_t  SS_CMU12_FHL:1;    /* Short Sequence for motor control/FlexRay clock freq. too high/low */
         vuint16_t  SS_FL_ECC_RCC:1;   /* Short Sequence for Flash, ECC, or lock-step error */
         vuint16_t  SS_PLL1:1;         /* Short Sequence for PLL1 fail */
         vuint16_t  SS_SWT:1;          /* Short Sequence for software watchdog timer */
         vuint16_t:1;
         vuint16_t  SS_CMU0_FHL:1;     /* Short Sequence for system clock freq. too high/low */
         vuint16_t  SS_CMU0_OLR:1;     /* Short Sequence for XOSC freq. too low */
         vuint16_t  SS_PLL0:1;         /* Short Sequence for PLL0 fail */
         vuint16_t  SS_CWD:1;          /* Short Sequence for core watchdog reset */
         vuint16_t  SS_SOFT_FUNC:1;    /* Short Sequence for software 'functional' reset */
         vuint16_t  SS_CORE:1;         /* Short Sequence for core reset */
         vuint16_t  SS_JTAG:1;         /* Short Sequence for JTAG initiated reset */
      } B;
   } RGM_FESS_16B_tag;

   typedef union {   /* Functional Bidirectional Reset Enable Register */
      vuint16_t R;
      struct {
         vuint16_t  BE_EXR:1;          /* Bidirectional Reset Enable for  external reset */
         vuint16_t  BE_FCCU_HARD:1;    /* Bidirectional Reset Enable for  FCCU hard reaction request */
         vuint16_t  BE_FCCU_SOFT:1;    /* Bidirectional Reset Enable for  FCCU soft reaction request */
         vuint16_t  BE_ST_DONE:1;      /* Bidirectional Reset Enable for  self-test completed */
         vuint16_t  BE_CMU12_FHL:1;    /* Bidirectional Reset Enable for  motor control/FlexRay clock freq. too high/low */
         vuint16_t  BE_FL_ECC_RCC:1;   /* Bidirectional Reset Enable for  Flash, ECC, or lock-step error */
         vuint16_t  BE_PLL1:1;         /* Bidirectional Reset Enable for  PLL1 fail */
         vuint16_t  BE_SWT:1;          /* Bidirectional Reset Enable for  software watchdog timer */
         vuint16_t:1;
         vuint16_t  BE_CMU0_FHL:1;     /* Bidirectional Reset Enable for  system clock freq. too high/low */
         vuint16_t  BE_CMU0_OLR:1;     /* Bidirectional Reset Enable for  XOSC freq. too low */
         vuint16_t  BE_PLL0:1;         /* Bidirectional Reset Enable for  PLL0 fail */
         vuint16_t  BE_CWD:1;          /* Bidirectional Reset Enable for  core watchdog reset */
         vuint16_t  BE_SOFT_FUNC:1;    /* Bidirectional Reset Enable for  software 'functional' reset */
         vuint16_t  BE_CORE:1;         /* Bidirectional Reset Enable for  core reset */
         vuint16_t  BE_JTAG:1;         /* Bidirectional Reset Enable for  JTAG initiated reset */
      } B;
   } RGM_FBRE_16B_tag;


   typedef struct RGM_struct_tag {

                                     /* Functional Event Status Register */
      RGM_FES_16B_tag FES;                 /* offset: 0x0000 size: 16 bit */
                                    /* Destructive Event Status Register */
      RGM_DES_16B_tag DES;                 /* offset: 0x0002 size: 16 bit */
                              /* Functional Event Reset Disable Register */
      RGM_FERD_16B_tag FERD;               /* offset: 0x0004 size: 16 bit */
                             /* Destructive Event Reset Disable Register */
      RGM_DERD_16B_tag DERD;               /* offset: 0x0006 size: 16 bit */
      int8_t RGM_reserved_0008[8];
                          /* Functional Event Alternate Request Register */
      RGM_FEAR_16B_tag FEAR;               /* offset: 0x0010 size: 16 bit */
      int8_t RGM_reserved_0012[6];
                             /* Functional Event Short Sequence Register */
      RGM_FESS_16B_tag FESS;               /* offset: 0x0018 size: 16 bit */
      int8_t RGM_reserved_001A[2];
                       /* Functional Bidirectional Reset Enable Register */
      RGM_FBRE_16B_tag FBRE;               /* offset: 0x001C size: 16 bit */
      int8_t RGM_reserved_001E[16354];

   } RGM_tag;


#define RGM_BASEADDRESS 0xC3FE4000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define RGM   (*(volatile RGM_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FE4000UL))



/****************************************************************/
/*                                                              */
/* Module: PCU  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Power domain #0 configuration register */
      vuint32_t R;
      struct {
         vuint32_t:18;
         vuint32_t  STBY0:1;           /* Power domain control during STBY0 */
         vuint32_t:2;
         vuint32_t  STOP0:1;           /* Power domain control during STOP0 */
         vuint32_t:1;
         vuint32_t  HALT0:1;           /* Power domain control during HALT0 */
         vuint32_t  RUN3:1;            /* Power domain control during RUN3 */
         vuint32_t  RUN2:1;            /* Power domain control during RUN2 */
         vuint32_t  RUN1:1;            /* Power domain control during RUN1 */
         vuint32_t  RUN0:1;            /* Power domain control during RUN0 */
         vuint32_t  DRUN:1;            /* Power domain control during DRUN */
         vuint32_t  SAFE:1;            /* Power domain control during SAFE */
         vuint32_t  TEST:1;            /* Power domain control during TEST */
         vuint32_t  RST:1;             /* Power domain control during RST */
      } B;
   } PCU_PCU_CONF0_32B_tag;

   typedef union {   /* Power Domain Status Register */
      vuint32_t R;
      struct {
         vuint32_t:31;
         vuint32_t  PD0:1;             /* Power status for power domain #0 */
      } B;
   } PCU_PSTAT_32B_tag;


   typedef struct PCU_struct_tag {

                               /* Power domain #0 configuration register */
      PCU_PCU_CONF0_32B_tag PCU_CONF0;     /* offset: 0x0000 size: 32 bit */
      int8_t PCU_reserved_0004[60];
                                         /* Power Domain Status Register */
      PCU_PSTAT_32B_tag PSTAT;             /* offset: 0x0040 size: 32 bit */
      int8_t PCU_reserved_0044[16316];

   } PCU_tag;


#define PCU_BASEADDRESS 0xC3FE8000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define PCU   (*(volatile PCU_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FE8000UL))



/****************************************************************/
/*                                                              */
/* Module: PIT_RTI  */
/*                                                              */
/****************************************************************/

   typedef union {   /* PIT Module Control Register */
      vuint32_t R;
      struct {
         vuint32_t:30;
         vuint32_t  MDIS:1;            /* Module Disable */
         vuint32_t  FRZ:1;             /* Freeze */
      } B;
   } PIT_RTI_PITMCR_32B_tag;


   /* Register layout for all registers LDVAL ... */

   typedef union {   /* Timer Load Value Register */
      vuint32_t R;
      struct {
         vuint32_t  TSV:32;            /* Time Start Value Bits */
      } B;
   } PIT_RTI_LDVAL_32B_tag;


   /* Register layout for all registers CVAL ... */

   typedef union {   /* Current Timer Value Register */
      vuint32_t R;
      struct {
         vuint32_t  TVL:32;            /* Current Timer Value Bits */
      } B;
   } PIT_RTI_CVAL_32B_tag;


   /* Register layout for all registers TCTRL ... */

   typedef union {   /* Timer Control Register */
      vuint32_t R;
      struct {
         vuint32_t:30;
         vuint32_t  TIE:1;             /* Timer Interrupt Enable Bit */
         vuint32_t  TEN:1;             /* Timer Enable Bit */
      } B;
   } PIT_RTI_TCTRL_32B_tag;


   /* Register layout for all registers TFLG ... */

   typedef union {   /* Timer Flag Register */
      vuint32_t R;
      struct {
         vuint32_t:31;
         vuint32_t  TIF:1;             /* Timer Interrupt Flag */
      } B;
   } PIT_RTI_TFLG_32B_tag;


   typedef struct PIT_RTI_CHANNEL_struct_tag {

                                            /* Timer Load Value Register */
      PIT_RTI_LDVAL_32B_tag LDVAL;         /* relative offset: 0x0000 */
                                         /* Current Timer Value Register */
      PIT_RTI_CVAL_32B_tag CVAL;           /* relative offset: 0x0004 */
                                               /* Timer Control Register */
      PIT_RTI_TCTRL_32B_tag TCTRL;         /* relative offset: 0x0008 */
                                                  /* Timer Flag Register */
      PIT_RTI_TFLG_32B_tag TFLG;           /* relative offset: 0x000C */

   } PIT_RTI_CHANNEL_tag;



   typedef struct PIT_RTI_struct_tag {

                                          /* PIT Module Control Register */
      PIT_RTI_PITMCR_32B_tag MCR;         /* offset: 0x0000 size: 32 bit */ /* Renamed from "PITMCR" to be able to reuse code */
      int8_t PIT_RTI_reserved_0004[252];
      union {
                                                /*  Register set CHANNEL */
         PIT_RTI_CHANNEL_tag CHANNEL[4];   /* offset: 0x0100  (0x0010 x 4) */

                                              /*  Alias name for CHANNEL */
         PIT_RTI_CHANNEL_tag CH[4];        /* deprecated - please avoid */

         struct {
                                            /* Timer Load Value Register */
            PIT_RTI_LDVAL_32B_tag LDVAL0;  /* offset: 0x0100 size: 32 bit */
                                         /* Current Timer Value Register */
            PIT_RTI_CVAL_32B_tag CVAL0;    /* offset: 0x0104 size: 32 bit */
                                               /* Timer Control Register */
            PIT_RTI_TCTRL_32B_tag TCTRL0;  /* offset: 0x0108 size: 32 bit */
                                                  /* Timer Flag Register */
            PIT_RTI_TFLG_32B_tag TFLG0;    /* offset: 0x010C size: 32 bit */
                                            /* Timer Load Value Register */
            PIT_RTI_LDVAL_32B_tag LDVAL1;  /* offset: 0x0110 size: 32 bit */
                                         /* Current Timer Value Register */
            PIT_RTI_CVAL_32B_tag CVAL1;    /* offset: 0x0114 size: 32 bit */
                                               /* Timer Control Register */
            PIT_RTI_TCTRL_32B_tag TCTRL1;  /* offset: 0x0118 size: 32 bit */
                                                  /* Timer Flag Register */
            PIT_RTI_TFLG_32B_tag TFLG1;    /* offset: 0x011C size: 32 bit */
                                            /* Timer Load Value Register */
            PIT_RTI_LDVAL_32B_tag LDVAL2;  /* offset: 0x0120 size: 32 bit */
                                         /* Current Timer Value Register */
            PIT_RTI_CVAL_32B_tag CVAL2;    /* offset: 0x0124 size: 32 bit */
                                               /* Timer Control Register */
            PIT_RTI_TCTRL_32B_tag TCTRL2;  /* offset: 0x0128 size: 32 bit */
                                                  /* Timer Flag Register */
            PIT_RTI_TFLG_32B_tag TFLG2;    /* offset: 0x012C size: 32 bit */
                                            /* Timer Load Value Register */
            PIT_RTI_LDVAL_32B_tag LDVAL3;  /* offset: 0x0130 size: 32 bit */
                                         /* Current Timer Value Register */
            PIT_RTI_CVAL_32B_tag CVAL3;    /* offset: 0x0134 size: 32 bit */
                                               /* Timer Control Register */
            PIT_RTI_TCTRL_32B_tag TCTRL3;  /* offset: 0x0138 size: 32 bit */
                                                  /* Timer Flag Register */
            PIT_RTI_TFLG_32B_tag TFLG3;    /* offset: 0x013C size: 32 bit */
         };

      };
      int8_t PIT_RTI_reserved_0140[16064];

   } PIT_RTI_tag;


#define PIT_RTI_BASEADDRESS 0xC3FF0000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define PIT_RTI (*(volatile PIT_RTI_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FF0000UL))
#define PIT PIT_RTI


/****************************************************************/
/*                                                              */
/* Module: PMUCTRL  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Status Register HVD */
      vuint32_t R;
      struct {
         vuint32_t:11;
         vuint32_t  HVDT_LPB:5;        /* High Voltage Detector trimming bits LPB bus */
         vuint32_t:6;
         vuint32_t  HVD_M:1;           /* High Voltage Detector Main */
         vuint32_t  HVD_B:1;           /* High Voltage Detector Backup */
         vuint32_t:4;
         vuint32_t  HVD_LP:4;          /* High Voltage Detector trimming bits LP bus */
      } B;
   } PMUCTRL_STATHVD_32B_tag;

   typedef union {   /* Status Register LVD */
      vuint32_t R;
      struct {
         vuint32_t:11;
         vuint32_t  LVDT_LPB:5;        /* Low Voltage Detector trimming bits LPB bus */
         vuint32_t:6;
         vuint32_t  LVD_M:1;           /* Low Voltage Detector Main */
         vuint32_t  LVD_B:1;           /* Low Voltage Detector Backup */
         vuint32_t:4;
         vuint32_t  LVD_LP:4;          /* Low Voltage Detector trimming bits LP bus */
      } B;
   } PMUCTRL_STATLVD_32B_tag;

   typedef union {   /* Status Register IREG */
      vuint32_t R;
      struct {
         vuint32_t:28;
         vuint32_t  IREG_HP:4;         /* Internal ballast REGulator hpreg1 trimming bits */
      } B;
   } PMUCTRL_STATIREG_32B_tag;

   typedef union {   /* PMUCTRL_STATEREG - PMU Status Register EREG */
      vuint32_t R;
      struct {
         vuint32_t:28;
         vuint32_t  EREG_HP:4;         /* External ballast REGulator hpreg1 trimming bits */
      } B;
   } PMUCTRL_STATEREG_32B_tag;

   typedef union {   /* Status Register */
      vuint32_t R;
      struct {
         vuint32_t:2;
         vuint32_t  ENPN:1;            /* External NPN status flag */
         vuint32_t:13;
         vuint32_t  CTB:2;             /* Configuration Trace Bits */
         vuint32_t:14;
      } B;
   } PMUCTRL_STATUS_32B_tag;

   typedef union {   /* Control Register */
      vuint32_t R;
      struct {
         vuint32_t:30;
         vuint32_t  SILHT:2;           /* Start Idle or LVD or HVD BIST Test */
      } B;
   } PMUCTRL_CTRL_32B_tag;

   typedef union {   /* Mask Fault Register */
      vuint32_t R;
      struct {
         vuint32_t  MF_BB:4;           /* Mask Fault Bypass Balast */
         vuint32_t:28;
      } B;
   } PMUCTRL_MASKF_32B_tag;

   typedef union {   /* Fault Monitor Register */
      vuint32_t R;
      struct {
         vuint32_t  BB_LV:4;           /* Bypass Ballast Low Voltage */
         vuint32_t:9;
         vuint32_t  FLNCF:1;           /* FLash voltage monitor Non Critical Fault */
         vuint32_t  IONCF:1;           /* IO voltage monitor Non Critical Fault */
         vuint32_t  RENCF:1;           /* REgulator voltage monitor Non Critical Fault */
         vuint32_t:13;
         vuint32_t  LHCF:1;            /* Low High voltage detector Critical Fault */
         vuint32_t  LNCF:1;            /* Low  voltage detector Non Critical Fault */
         vuint32_t  HNCF:1;            /* High voltage detector Non Critical Fault */
      } B;
   } PMUCTRL_FAULT_32B_tag;

   typedef union {   /* Interrupt Request Status Register */
      vuint32_t R;
      struct {
         vuint32_t:10;
         vuint32_t  MFVMP:1;           /* Main   Flash     Voltage Monitor interrupt Pending */
         vuint32_t  BFVMP:1;           /* Backup Flash     Voltage Monitor interrupt Pending */
         vuint32_t  MIVMP:1;           /* MAin   IO        Voltage Monitor interrupt Pending */
         vuint32_t  BIVMP:1;           /* Backup IO        Voltage Monitor interrupt Pending */
         vuint32_t  MRVMP:1;           /* Main   Regulator Voltage Monitor interrupt Pending */
         vuint32_t  BRVMP:1;           /* Backup Regulator Voltage Monitor interrupt Pending */
         vuint32_t:12;
         vuint32_t  MLVDP:1;           /* Main   Low  Voltage Detector error interrupt Pending */
         vuint32_t  BLVDP:1;           /* Backup Low  Voltage Detector error interrupt Pending */
         vuint32_t  MHVDP:1;           /* Main   High Voltage Detector error interrupt Pending */
         vuint32_t  BHVDP:1;           /* Backup High Voltage Detector error interrupt Pending */
      } B;
   } PMUCTRL_IRQS_32B_tag;

   typedef union {   /* Interrupt Request Enable Register */
      vuint32_t R;
      struct {
         vuint32_t:10;
         vuint32_t  MFVME:1;           /* Main   Flash     Voltage Monitor interrupt Enable */
         vuint32_t  BFVME:1;           /* Backup Flash     Voltage Monitor interrupt Enable */
         vuint32_t  MIVME:1;           /* Main   IO        Voltage Monitor interrupt Enable */
         vuint32_t  BIVME:1;           /* Backup IO        Voltage Monitor interrupt Enable */
         vuint32_t  MRVME:1;           /* Main   Regulator Voltage Monitor interrupt Enable */
         vuint32_t  BRVME:1;           /* Backup Regulator Voltage Monitor interrupt Enable */
         vuint32_t:12;
         vuint32_t  MLVDE:1;           /* Main   Low  Voltage Detector error interrupt Enable */
         vuint32_t  BLVDE:1;           /* Backup Low  Voltage Detector error interrupt Enable */
         vuint32_t  MHVDE:1;           /* Main   High Voltage Detector error interrupt Enable */
         vuint32_t  BHVDE:1;           /* Backup High Voltage Detector error interrupt Enable */
      } B;
   } PMUCTRL_IRQE_32B_tag;


   typedef struct PMUCTRL_struct_tag {

      int8_t PMUCTRL_reserved_0000[4];
                                                  /* Status Register HVD */
      PMUCTRL_STATHVD_32B_tag STATHVD;     /* offset: 0x0004 size: 32 bit */
                                                  /* Status Register LVD */
      PMUCTRL_STATLVD_32B_tag STATLVD;     /* offset: 0x0008 size: 32 bit */
      int8_t PMUCTRL_reserved_000C[20];
                                                 /* Status Register IREG */
      PMUCTRL_STATIREG_32B_tag STATIREG;   /* offset: 0x0020 size: 32 bit */
                          /* PMUCTRL_STATEREG - PMU Status Register EREG */
      PMUCTRL_STATEREG_32B_tag STATEREG;   /* offset: 0x0024 size: 32 bit */
      int8_t PMUCTRL_reserved_0028[24];
                                                      /* Status Register */
      PMUCTRL_STATUS_32B_tag STATUS;       /* offset: 0x0040 size: 32 bit */
                                                     /* Control Register */
      PMUCTRL_CTRL_32B_tag CTRL;           /* offset: 0x0044 size: 32 bit */
      int8_t PMUCTRL_reserved_0048[40];
                                                  /* Mask Fault Register */
      PMUCTRL_MASKF_32B_tag MASKF;         /* offset: 0x0070 size: 32 bit */
                                               /* Fault Monitor Register */
      PMUCTRL_FAULT_32B_tag FAULT;         /* offset: 0x0074 size: 32 bit */
                                    /* Interrupt Request Status Register */
      PMUCTRL_IRQS_32B_tag IRQS;           /* offset: 0x0078 size: 32 bit */
                                    /* Interrupt Request Enable Register */
      PMUCTRL_IRQE_32B_tag IRQE;           /* offset: 0x007C size: 32 bit */
      int8_t PMUCTRL_reserved_0080[16256];

   } PMUCTRL_tag;


#define PMUCTRL_BASEADDRESS 0xC3FE8080UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define PMUCTRL (*(volatile PMUCTRL_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FE8080UL))



/****************************************************************/
/*                                                              */
/* Module: STCU  */
/*                                                              */
/****************************************************************/

   typedef union {   /* STCU Error Register -- status flags related to internal error conditions */
      vuint32_t R;
      struct {
         vuint32_t:4;
         vuint32_t  WDTOSFM:1;         /* Watchdog time-out Stay In Reset Fault Mapping */
         vuint32_t  CRCSSFM:1;         /* CRC Stay In Reset Fault Mapping */
         vuint32_t  ENGESFM:1;         /* Engine Error Stay In Reset Fault Mapping */
         vuint32_t  INVPSFM:1;         /* Invalid Pointer Stay In Reset Fault Mapping */
         vuint32_t:4;
         vuint32_t  WDTOCFM:1;         /* Watchdog time-out Critical Fault Mapping */
         vuint32_t  CRCSCFM:1;         /* CRC Status Critical Fault Mapping */
         vuint32_t  ENGECFM:1;         /* Engine Error Critial Fault Mapping */
         vuint32_t  INVPCFM:1;         /* Invalid Pointer Critical Fault Mapping */
         vuint32_t:5;
         vuint32_t  CFSF:1;            /* Critical Faults Status Flag */
         vuint32_t  NCFSF:1;           /* Non Critical Faults Status Flag */
         vuint32_t  SIRSF:1;           /* Stay In Reset Faults Status Flag */
         vuint32_t:4;
         vuint32_t  WDTO:1;            /* Watchdog time-out */
         vuint32_t  CRCS:1;            /* CRC status */
         vuint32_t  ENGE:1;            /* Engine Error */
         vuint32_t  INVP:1;            /* Invalid pointer */
      } B;
   } STCU_ERR_32B_tag;

   typedef union {   /* STCU Error Key Register - write key 0xF1759034 before clearing of status bits in ERR */
      vuint32_t R;
   } STCU_ERRK_32B_tag;

   typedef union {   /* STCU LBIST Status Register */
      vuint32_t R;
      struct {
         vuint32_t:29;
         vuint32_t  LBS2:1;            /* LBIST #2 status - (1=successful,0=fail) */
         vuint32_t  LBS1:1;            /* LBIST #1 status - (1=successful,0=fail) */
         vuint32_t  LBS0:1;            /* LBIST #0 status - (1=successful,0=fail) */
      } B;
   } STCU_LBS_32B_tag;

   typedef union {   /* STCU LBIST End Flag Register */
      vuint32_t R;
      struct {
         vuint32_t:29;
         vuint32_t  LBE2:1;            /* LBIST #2 end status (1=finished,0=ongoing) */
         vuint32_t  LBE1:1;            /* LBIST #1 end status (1=finished,0=ongoing) */
         vuint32_t  LBE0:1;            /* LBIST #0 end status (1=finished,0=ongoing) */
      } B;
   } STCU_LBE_32B_tag;

   typedef union {   /* STCU  MBIST Status Low Register */
      vuint32_t R;
      struct {
         vuint32_t  MBS31:1;           /* MBIST #31  status (1=successful,0=fail) */
         vuint32_t  MBS30:1;           /* MBIST #30  status (1=successful,0=fail) */
         vuint32_t  MBS29:1;           /* MBIST #29  status (1=successful,0=fail) */
         vuint32_t  MBS28:1;           /* MBIST #28  status (1=successful,0=fail) */
         vuint32_t  MBS27:1;           /* MBIST #27  status (1=successful,0=fail) */
         vuint32_t  MBS26:1;           /* MBIST #26  status (1=successful,0=fail) */
         vuint32_t  MBS25:1;           /* MBIST #25  status (1=successful,0=fail) */
         vuint32_t  MBS24:1;           /* MBIST #24  status (1=successful,0=fail) */
         vuint32_t  MBS23:1;           /* MBIST #23  status (1=successful,0=fail) */
         vuint32_t  MBS22:1;           /* MBIST #22  status (1=successful,0=fail) */
         vuint32_t  MBS21:1;           /* MBIST #21  status (1=successful,0=fail) */
         vuint32_t  MBS20:1;           /* MBIST #20  status (1=successful,0=fail) */
         vuint32_t  MBS19:1;           /* MBIST #19  status (1=successful,0=fail) */
         vuint32_t  MBS18:1;           /* MBIST #18  status (1=successful,0=fail) */
         vuint32_t  MBS17:1;           /* MBIST #17  status (1=successful,0=fail) */
         vuint32_t  MBS16:1;           /* MBIST #16  status (1=successful,0=fail) */
         vuint32_t  MBS15:1;           /* MBIST #15  status (1=successful,0=fail) */
         vuint32_t  MBS14:1;           /* MBIST #14  status (1=successful,0=fail) */
         vuint32_t  MBS13:1;           /* MBIST #13  status (1=successful,0=fail) */
         vuint32_t  MBS12:1;           /* MBIST #12  status (1=successful,0=fail) */
         vuint32_t  MBS11:1;           /* MBIST #11  status (1=successful,0=fail) */
         vuint32_t  MBS10:1;           /* MBIST #10  status (1=successful,0=fail) */
         vuint32_t  MBS9:1;            /* MBIST #9  status (1=successful,0=fail) */
         vuint32_t  MBS8:1;            /* MBIST #8  status (1=successful,0=fail) */
         vuint32_t  MBS7:1;            /* MBIST #7  status (1=successful,0=fail) */
         vuint32_t  MBS6:1;            /* MBIST #6  status (1=successful,0=fail) */
         vuint32_t  MBS5:1;            /* MBIST #5  status (1=successful,0=fail) */
         vuint32_t  MBS4:1;            /* MBIST #4  status (1=successful,0=fail) */
         vuint32_t  MBS3:1;            /* MBIST #3  status (1=successful,0=fail) */
         vuint32_t  MBS2:1;            /* MBIST #2  status (1=successful,0=fail) */
         vuint32_t  MBS1:1;            /* MBIST #1  status (1=successful,0=fail) */
         vuint32_t  MBS0:1;            /* MBIST #0  status (1=successful,0=fail) */
      } B;
   } STCU_MBSL_32B_tag;

   typedef union {   /* STCU  MBIST Status High Register */
      vuint32_t R;
      struct {
         vuint32_t:29;
         vuint32_t  MBS34:1;           /* MBIST #34  status (1=successful,0=fail) */
         vuint32_t  MBS33:1;           /* MBIST #33  status (1=successful,0=fail) */
         vuint32_t  MBS32:1;           /* MBIST #32  status (1=successful,0=fail) */
      } B;
   } STCU_MBSH_32B_tag;

   typedef union {   /* STCU  MBIST End Flag Low Register */
      vuint32_t R;
      struct {
         vuint32_t  MBE31:1;           /* MBIST #31  end status (1=finished,0=ongoing) */
         vuint32_t  MBE30:1;           /* MBIST #30  end status (1=finished,0=ongoing) */
         vuint32_t  MBE29:1;           /* MBIST #29  end status (1=finished,0=ongoing) */
         vuint32_t  MBE28:1;           /* MBIST #28  end status (1=finished,0=ongoing) */
         vuint32_t  MBE27:1;           /* MBIST #27  end status (1=finished,0=ongoing) */
         vuint32_t  MBE26:1;           /* MBIST #26  end status (1=finished,0=ongoing) */
         vuint32_t  MBE25:1;           /* MBIST #25  end status (1=finished,0=ongoing) */
         vuint32_t  MBE24:1;           /* MBIST #24  end status (1=finished,0=ongoing) */
         vuint32_t  MBE23:1;           /* MBIST #23  end status (1=finished,0=ongoing) */
         vuint32_t  MBE22:1;           /* MBIST #22  end status (1=finished,0=ongoing) */
         vuint32_t  MBE21:1;           /* MBIST #21  end status (1=finished,0=ongoing) */
         vuint32_t  MBE20:1;           /* MBIST #20  end status (1=finished,0=ongoing) */
         vuint32_t  MBE19:1;           /* MBIST #19  end status (1=finished,0=ongoing) */
         vuint32_t  MBE18:1;           /* MBIST #18  end status (1=finished,0=ongoing) */
         vuint32_t  MBE17:1;           /* MBIST #17  end status (1=finished,0=ongoing) */
         vuint32_t  MBE16:1;           /* MBIST #16  end status (1=finished,0=ongoing) */
         vuint32_t  MBE15:1;           /* MBIST #15  end status (1=finished,0=ongoing) */
         vuint32_t  MBE14:1;           /* MBIST #14  end status (1=finished,0=ongoing) */
         vuint32_t  MBE13:1;           /* MBIST #13  end status (1=finished,0=ongoing) */
         vuint32_t  MBE12:1;           /* MBIST #12  end status (1=finished,0=ongoing) */
         vuint32_t  MBE11:1;           /* MBIST #11  end status (1=finished,0=ongoing) */
         vuint32_t  MBE10:1;           /* MBIST #10  end status (1=finished,0=ongoing) */
         vuint32_t  MBE9:1;            /* MBIST #9  end status (1=finished,0=ongoing) */
         vuint32_t  MBE8:1;            /* MBIST #8  end status (1=finished,0=ongoing) */
         vuint32_t  MBE7:1;            /* MBIST #7  end status (1=finished,0=ongoing) */
         vuint32_t  MBE6:1;            /* MBIST #6  end status (1=finished,0=ongoing) */
         vuint32_t  MBE5:1;            /* MBIST #5  end status (1=finished,0=ongoing) */
         vuint32_t  MBE4:1;            /* MBIST #4  end status (1=finished,0=ongoing) */
         vuint32_t  MBE3:1;            /* MBIST #3  end status (1=finished,0=ongoing) */
         vuint32_t  MBE2:1;            /* MBIST #2  end status (1=finished,0=ongoing) */
         vuint32_t  MBE1:1;            /* MBIST #1  end status (1=finished,0=ongoing) */
         vuint32_t  MBE0:1;            /* MBIST #0  end status (1=finished,0=ongoing) */
      } B;
   } STCU_MBEL_32B_tag;

   typedef union {   /* STCU  MBIST End Flag High Register */
      vuint32_t R;
      struct {
         vuint32_t:29;
         vuint32_t  MBE34:1;           /* MBIST #34  end status (1=finished,0=ongoing) */
         vuint32_t  MBE33:1;           /* MBIST #33  end status (1=finished,0=ongoing) */
         vuint32_t  MBE32:1;           /* MBIST #32  end status (1=finished,0=ongoing) */
      } B;
   } STCU_MBEH_32B_tag;


   /* Register layout for all registers LB_MISREL ... */

   typedef union {   /* STCU LBIST n MISR Expected Low Register */
      vuint32_t R;
      struct {
         vuint32_t  MISREL:32;         /* MISR Expected low part */
      } B;
   } STCU_LB_MISREL_32B_tag;


   /* Register layout for all registers LB_MISREH ... */

   typedef union {   /* STCU LBIST n MISR Expected High Register */
      vuint32_t R;
      struct {
         vuint32_t  MISREH:32;         /* MISR Expected high part */
      } B;
   } STCU_LB_MISREH_32B_tag;


   /* Register layout for all registers LB_MISRRL ... */

   typedef union {   /* STCU LBIST n MISR Read Low Register */
      vuint32_t R;
      struct {
         vuint32_t  MISRRL:32;         /* MISR Read low part */
      } B;
   } STCU_LB_MISRRL_32B_tag;


   /* Register layout for all registers LB_MISRRH ... */

   typedef union {   /* STCU LBIST n MISR Read High Register */
      vuint32_t R;
      struct {
         vuint32_t  MISRRH:32;         /* MISR Read high part */
      } B;
   } STCU_LB_MISRRH_32B_tag;


   typedef struct STCU_LBIST_PART_struct_tag {

      int8_t STCU_LBIST_PART_reserved_0000[8];
                              /* STCU LBIST n MISR Expected Low Register */
      STCU_LB_MISREL_32B_tag LB_MISREL;    /* relative offset: 0x0008 */
                             /* STCU LBIST n MISR Expected High Register */
      STCU_LB_MISREH_32B_tag LB_MISREH;    /* relative offset: 0x000C */
                                  /* STCU LBIST n MISR Read Low Register */
      STCU_LB_MISRRL_32B_tag LB_MISRRL;    /* relative offset: 0x0010 */
                                 /* STCU LBIST n MISR Read High Register */
      STCU_LB_MISRRH_32B_tag LB_MISRRH;    /* relative offset: 0x0014 */
      int8_t STCU_LBIST_PART_reserved_0018[8];

   } STCU_LBIST_PART_tag;



   typedef struct STCU_struct_tag {

      int8_t STCU_reserved_0000[28];
    /* STCU Error Register -- status flags related to internal error conditions */
      STCU_ERR_32B_tag ERR;                /* offset: 0x001C size: 32 bit */
    /* STCU Error Key Register - write key 0xF1759034 before clearing of status bits in ERR */
      STCU_ERRK_32B_tag ERRK;              /* offset: 0x0020 size: 32 bit */
                                           /* STCU LBIST Status Register */
      STCU_LBS_32B_tag LBS;                /* offset: 0x0024 size: 32 bit */
                                         /* STCU LBIST End Flag Register */
      STCU_LBE_32B_tag LBE;                /* offset: 0x0028 size: 32 bit */
      int8_t STCU_reserved_002C[16];
                                      /* STCU  MBIST Status Low Register */
      STCU_MBSL_32B_tag MBSL;              /* offset: 0x003C size: 32 bit */
                                     /* STCU  MBIST Status High Register */
      STCU_MBSH_32B_tag MBSH;              /* offset: 0x0040 size: 32 bit */
                                    /* STCU  MBIST End Flag Low Register */
      STCU_MBEL_32B_tag MBEL;              /* offset: 0x0044 size: 32 bit */
                                   /* STCU  MBIST End Flag High Register */
      STCU_MBEH_32B_tag MBEH;              /* offset: 0x0048 size: 32 bit */
      int8_t STCU_reserved_004C[60];
      union {
                                             /*  Register set LBIST_PART */
         STCU_LBIST_PART_tag LBIST_PART[3];  /* offset: 0x0088  (0x0020 x 3) */

         struct {
                              /* STCU LBIST n MISR Expected Low Register */
            STCU_LB_MISREL_32B_tag LB0_MISREL;  /* offset: 0x0088 size: 32 bit */
                             /* STCU LBIST n MISR Expected High Register */
            STCU_LB_MISREH_32B_tag LB0_MISREH;  /* offset: 0x008C size: 32 bit */
                                  /* STCU LBIST n MISR Read Low Register */
            STCU_LB_MISRRL_32B_tag LB0_MISRRL;  /* offset: 0x0090 size: 32 bit */
                                 /* STCU LBIST n MISR Read High Register */
            STCU_LB_MISRRH_32B_tag LB0_MISRRH;  /* offset: 0x0094 size: 32 bit */
            int8_t STCU_reserved_0098_I1[16];
                              /* STCU LBIST n MISR Expected Low Register */
            STCU_LB_MISREL_32B_tag LB1_MISREL;  /* offset: 0x00A8 size: 32 bit */
                             /* STCU LBIST n MISR Expected High Register */
            STCU_LB_MISREH_32B_tag LB1_MISREH;  /* offset: 0x00AC size: 32 bit */
                                  /* STCU LBIST n MISR Read Low Register */
            STCU_LB_MISRRL_32B_tag LB1_MISRRL;  /* offset: 0x00B0 size: 32 bit */
                                 /* STCU LBIST n MISR Read High Register */
            STCU_LB_MISRRH_32B_tag LB1_MISRRH;  /* offset: 0x00B4 size: 32 bit */
            int8_t STCU_reserved_00B8_I1[16];
                              /* STCU LBIST n MISR Expected Low Register */
            STCU_LB_MISREL_32B_tag LB2_MISREL;  /* offset: 0x00C8 size: 32 bit */
                             /* STCU LBIST n MISR Expected High Register */
            STCU_LB_MISREH_32B_tag LB2_MISREH;  /* offset: 0x00CC size: 32 bit */
                                  /* STCU LBIST n MISR Read Low Register */
            STCU_LB_MISRRL_32B_tag LB2_MISRRL;  /* offset: 0x00D0 size: 32 bit */
                                 /* STCU LBIST n MISR Read High Register */
            STCU_LB_MISRRH_32B_tag LB2_MISRRH;  /* offset: 0x00D4 size: 32 bit */
            int8_t STCU_reserved_00D8_E1[16];
         };

      };
      int8_t STCU_reserved_00E8[16152];

   } STCU_tag;


#define STCU_BASEADDRESS 0xC3FF4000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define STCU  (*(volatile STCU_tag *)(volatile void*) ((vuint8_t*)0UL + 0xC3FF4000UL))



/****************************************************************/
/*                                                              */
/* Module: ADC  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Main Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t  OWREN:1;           /* Overwrite enable */
         vuint32_t  WLSIDE:1;          /* Write left/right aligned */
         vuint32_t  MODE:1;            /* Mode selection: 0=one shot/1=scan */
         vuint32_t:4;
         vuint32_t  NSTART:1;          /* Start normal conversion */
         vuint32_t:1;
         vuint32_t  JTRGEN:1;          /* Injection external trigger enable */
         vuint32_t  JEDGE:1;           /* Injection trigger edge selection */
         vuint32_t  JSTART:1;          /* Injection conversion start */
         vuint32_t  REF_RANGE_EXP:1;   /* Expected value of REF_RANGE in MSR */
         vuint32_t:1;
         vuint32_t  CTUEN:1;           /* Crosstrigger Unit Enable */
         vuint32_t:1;
         vuint32_t  STCL:1;            /* Self Testing Configuration Lock */
         vuint32_t:6;
         vuint32_t  ADCLKSEL:1;        /* Analog Clock Frequency Selector */
         vuint32_t  ABORTCHAIN:1;      /* Abort Chain Conversion */
         vuint32_t  ABORT:1;           /* Abort Current Conversion */
         vuint32_t  ACKO:1;            /* Auto Clock Off Enable */
         vuint32_t:4;
         vuint32_t  PWDN:1;            /* Power Down Enable */
      } B;
   } ADC_MCR_32B_tag;

   typedef union {   /* Main Status Register */
      vuint32_t R;
      struct {
         vuint32_t:7;
         vuint32_t  NSTART:1;          /* Normal conversion started */
         vuint32_t  JABORT:1;          /* Injected conversion aborted */
         vuint32_t:2;
         vuint32_t  JSTART:1;          /* Injected conversion started */
         vuint32_t  REF_RANGE:1;       /* Voltage range for ADC analog operation */
         vuint32_t  SELF_TEST_S:1;     /* Self test conversion started */
         vuint32_t:1;
         vuint32_t  CTUSTART:1;        /* CTU conversion started */
         vuint32_t  CHADDR:7;          /* Channel under measure address */
         vuint32_t:3;
         vuint32_t  ACKO:1;            /* Auto clock off enable */
         vuint32_t:2;
         vuint32_t  ADCSTATUS:3;       /* Status of ADC FSM */
      } B;
   } ADC_MSR_32B_tag;

   typedef union {   /* Interrupt Status Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  REF_RANGE:1;       /* REF_RANGE output does not match expected value programmed in MCR */
         vuint32_t:10;
         vuint32_t  EOCTU:1;           /* End of CTU channel conversion */
         vuint32_t  JEOC:1;            /* End of injected channel conversion */
         vuint32_t  JECH:1;            /* End of injected chain conversion */
         vuint32_t  EOC:1;             /* End of channel conversion */
         vuint32_t  ECH:1;             /* End of chain conversion */
      } B;
   } ADC_ISR_32B_tag;

   typedef union {   /* Channel Pending Register 0 (Precision channels) */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  EOC_CH15:1;        /* End of Conversion Pending Interrupt for channel 15 */
         vuint32_t  EOC_CH14:1;        /* End of Conversion Pending Interrupt for channel 14 */
         vuint32_t  EOC_CH13:1;        /* End of Conversion Pending Interrupt for channel 13 */
         vuint32_t  EOC_CH12:1;        /* End of Conversion Pending Interrupt for channel 12 */
         vuint32_t  EOC_CH11:1;        /* End of Conversion Pending Interrupt for channel 11 */
         vuint32_t  EOC_CH10:1;        /* End of Conversion Pending Interrupt for channel 10 */
         vuint32_t  EOC_CH9:1;         /* End of Conversion Pending Interrupt for channel 9 */
         vuint32_t  EOC_CH8:1;         /* End of Conversion Pending Interrupt for channel 8 */
         vuint32_t  EOC_CH7:1;         /* End of Conversion Pending Interrupt for channel 7 */
         vuint32_t  EOC_CH6:1;         /* End of Conversion Pending Interrupt for channel 6 */
         vuint32_t  EOC_CH5:1;         /* End of Conversion Pending Interrupt for channel 5 */
         vuint32_t  EOC_CH4:1;         /* End of Conversion Pending Interrupt for channel 4 */
         vuint32_t  EOC_CH3:1;         /* End of Conversion Pending Interrupt for channel 3 */
         vuint32_t  EOC_CH2:1;         /* End of Conversion Pending Interrupt for channel 2 */
         vuint32_t  EOC_CH1:1;         /* End of Conversion Pending Interrupt for channel 1 */
         vuint32_t  EOC_CH0:1;         /* End of Conversion Pending Interrupt for channel 0 */
      } B;
   } ADC_CEOCFR0_32B_tag;

   typedef union {   /* Interrupt Mask Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  MSK_REF_RANGE:1;   /* Interrupt enable for REF_RANGE mismatch */
         vuint32_t:10;
         vuint32_t  MSKEOCTU:1;        /* Interrupt enable for EOCTU */
         vuint32_t  MSKJEOC:1;         /* Interrupt enable for JEOC */
         vuint32_t  MSKJECH:1;         /* Interrupt enable for JECH */
         vuint32_t  MSKEOC:1;          /* Interrupt enable for EOC */
         vuint32_t  MSKECH:1;          /* Interrupt enable for ECH */
      } B;
   } ADC_IMR_32B_tag;

   typedef union {   /* Channel Interrupt Mask Register 0 (Precision channels) */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  CIM15:1;           /* Interrupt Enable Mask for channel 15 */
         vuint32_t  CIM14:1;           /* Interrupt Enable Mask for channel 14 */
         vuint32_t  CIM13:1;           /* Interrupt Enable Mask for channel 13 */
         vuint32_t  CIM12:1;           /* Interrupt Enable Mask for channel 12 */
         vuint32_t  CIM11:1;           /* Interrupt Enable Mask for channel 11 */
         vuint32_t  CIM10:1;           /* Interrupt Enable Mask for channel 10 */
         vuint32_t  CIM9:1;            /* Interrupt Enable Mask for channel 9 */
         vuint32_t  CIM8:1;            /* Interrupt Enable Mask for channel 8 */
         vuint32_t  CIM7:1;            /* Interrupt Enable Mask for channel 7 */
         vuint32_t  CIM6:1;            /* Interrupt Enable Mask for channel 6 */
         vuint32_t  CIM5:1;            /* Interrupt Enable Mask for channel 5 */
         vuint32_t  CIM4:1;            /* Interrupt Enable Mask for channel 4 */
         vuint32_t  CIM3:1;            /* Interrupt Enable Mask for channel 3 */
         vuint32_t  CIM2:1;            /* Interrupt Enable Mask for channel 2 */
         vuint32_t  CIM1:1;            /* Interrupt Enable Mask for channel 1 */
         vuint32_t  CIM0:1;            /* Interrupt Enable Mask for channel 0 */
      } B;
   } ADC_CIMR0_32B_tag;

   typedef union {   /* Watchdog Threshold Interrupt Status Register */
      vuint32_t R;
      struct {
         vuint32_t  WDG15H:1;          /* Interrupt when conversion value is higher than the programmed threshold HTHV15 */
         vuint32_t  WDG15L:1;          /* Interrupt when conversion value is lower than the programmed threshold LTHV15 */
         vuint32_t  WDG14H:1;          /* Interrupt when conversion value is higher than the programmed threshold HTHV14 */
         vuint32_t  WDG14L:1;          /* Interrupt when conversion value is lower than the programmed threshold LTHV14 */
         vuint32_t  WDG13H:1;          /* Interrupt when conversion value is higher than the programmed threshold HTHV13 */
         vuint32_t  WDG13L:1;          /* Interrupt when conversion value is lower than the programmed threshold LTHV13 */
         vuint32_t  WDG12H:1;          /* Interrupt when conversion value is higher than the programmed threshold HTHV12 */
         vuint32_t  WDG12L:1;          /* Interrupt when conversion value is lower than the programmed threshold LTHV12 */
         vuint32_t  WDG11H:1;          /* Interrupt when conversion value is higher than the programmed threshold HTHV11 */
         vuint32_t  WDG11L:1;          /* Interrupt when conversion value is lower than the programmed threshold LTHV11 */
         vuint32_t  WDG10H:1;          /* Interrupt when conversion value is higher than the programmed threshold HTHV10 */
         vuint32_t  WDG10L:1;          /* Interrupt when conversion value is lower than the programmed threshold LTHV10 */
         vuint32_t  WDG9H:1;           /* Interrupt when conversion value is higher than the programmed threshold HTHV9 */
         vuint32_t  WDG9L:1;           /* Interrupt when conversion value is lower than the programmed threshold LTHV9 */
         vuint32_t  WDG8H:1;           /* Interrupt when conversion value is higher than the programmed threshold HTHV8 */
         vuint32_t  WDG8L:1;           /* Interrupt when conversion value is lower than the programmed threshold LTHV8 */
         vuint32_t  WDG7H:1;           /* Interrupt when conversion value is higher than the programmed threshold HTHV7 */
         vuint32_t  WDG7L:1;           /* Interrupt when conversion value is lower than the programmed threshold LTHV7 */
         vuint32_t  WDG6H:1;           /* Interrupt when conversion value is higher than the programmed threshold HTHV6 */
         vuint32_t  WDG6L:1;           /* Interrupt when conversion value is lower than the programmed threshold LTHV6 */
         vuint32_t  WDG5H:1;           /* Interrupt when conversion value is higher than the programmed threshold HTHV5 */
         vuint32_t  WDG5L:1;           /* Interrupt when conversion value is lower than the programmed threshold LTHV5 */
         vuint32_t  WDG4H:1;           /* Interrupt when conversion value is higher than the programmed threshold HTHV4 */
         vuint32_t  WDG4L:1;           /* Interrupt when conversion value is lower than the programmed threshold LTHV4 */
         vuint32_t  WDG3H:1;           /* Interrupt when conversion value is higher than the programmed threshold HTHV3 */
         vuint32_t  WDG3L:1;           /* Interrupt when conversion value is lower than the programmed threshold LTHV3 */
         vuint32_t  WDG2H:1;           /* Interrupt when conversion value is higher than the programmed threshold HTHV2 */
         vuint32_t  WDG2L:1;           /* Interrupt when conversion value is lower than the programmed threshold LTHV2 */
         vuint32_t  WDG1H:1;           /* Interrupt when conversion value is higher than the programmed threshold HTHV1 */
         vuint32_t  WDG1L:1;           /* Interrupt when conversion value is lower than the programmed threshold LTHV1 */
         vuint32_t  WDG0H:1;           /* Interrupt when conversion value is higher than the programmed threshold HTHV0 */
         vuint32_t  WDG0L:1;           /* Interrupt when conversion value is lower than the programmed threshold LTHV0 */
      } B;
   } ADC_WTISR_32B_tag;

   typedef union {   /* Watchdog Threshold Interrupt Mask register */
      vuint32_t R;
      struct {
         vuint32_t  MSKWDG15H:1;       /* Enables interrupt when conversion value is higher than the programmed threshold HTHV15 */
         vuint32_t  MSKWDG15L:1;       /* Enables interrupt when conversion value is lower than the programmed threshold LTHV15 */
         vuint32_t  MSKWDG14H:1;       /* Enables interrupt when conversion value is higher than the programmed threshold HTHV14 */
         vuint32_t  MSKWDG14L:1;       /* Enables interrupt when conversion value is lower than the programmed threshold LTHV14 */
         vuint32_t  MSKWDG13H:1;       /* Enables interrupt when conversion value is higher than the programmed threshold HTHV13 */
         vuint32_t  MSKWDG13L:1;       /* Enables interrupt when conversion value is lower than the programmed threshold LTHV13 */
         vuint32_t  MSKWDG12H:1;       /* Enables interrupt when conversion value is higher than the programmed threshold HTHV12 */
         vuint32_t  MSKWDG12L:1;       /* Enables interrupt when conversion value is lower than the programmed threshold LTHV12 */
         vuint32_t  MSKWDG11H:1;       /* Enables interrupt when conversion value is higher than the programmed threshold HTHV11 */
         vuint32_t  MSKWDG11L:1;       /* Enables interrupt when conversion value is lower than the programmed threshold LTHV11 */
         vuint32_t  MSKWDG10H:1;       /* Enables interrupt when conversion value is higher than the programmed threshold HTHV10 */
         vuint32_t  MSKWDG10L:1;       /* Enables interrupt when conversion value is lower than the programmed threshold LTHV10 */
         vuint32_t  MSKWDG9H:1;        /* Enables interrupt when conversion value is higher than the programmed threshold HTHV9 */
         vuint32_t  MSKWDG9L:1;        /* Enables interrupt when conversion value is lower than the programmed threshold LTHV9 */
         vuint32_t  MSKWDG8H:1;        /* Enables interrupt when conversion value is higher than the programmed threshold HTHV8 */
         vuint32_t  MSKWDG8L:1;        /* Enables interrupt when conversion value is lower than the programmed threshold LTHV8 */
         vuint32_t  MSKWDG7H:1;        /* Enables interrupt when conversion value is higher than the programmed threshold HTHV7 */
         vuint32_t  MSKWDG7L:1;        /* Enables interrupt when conversion value is lower than the programmed threshold LTHV7 */
         vuint32_t  MSKWDG6H:1;        /* Enables interrupt when conversion value is higher than the programmed threshold HTHV6 */
         vuint32_t  MSKWDG6L:1;        /* Enables interrupt when conversion value is lower than the programmed threshold LTHV6 */
         vuint32_t  MSKWDG5H:1;        /* Enables interrupt when conversion value is higher than the programmed threshold HTHV5 */
         vuint32_t  MSKWDG5L:1;        /* Enables interrupt when conversion value is lower than the programmed threshold LTHV5 */
         vuint32_t  MSKWDG4H:1;        /* Enables interrupt when conversion value is higher than the programmed threshold HTHV4 */
         vuint32_t  MSKWDG4L:1;        /* Enables interrupt when conversion value is lower than the programmed threshold LTHV4 */
         vuint32_t  MSKWDG3H:1;        /* Enables interrupt when conversion value is higher than the programmed threshold HTHV3 */
         vuint32_t  MSKWDG3L:1;        /* Enables interrupt when conversion value is lower than the programmed threshold LTHV3 */
         vuint32_t  MSKWDG2H:1;        /* Enables interrupt when conversion value is higher than the programmed threshold HTHV2 */
         vuint32_t  MSKWDG2L:1;        /* Enables interrupt when conversion value is lower than the programmed threshold LTHV2 */
         vuint32_t  MSKWDG1H:1;        /* Enables interrupt when conversion value is higher than the programmed threshold HTHV1 */
         vuint32_t  MSKWDG1L:1;        /* Enables interrupt when conversion value is lower than the programmed threshold LTHV1 */
         vuint32_t  MSKWDG0H:1;        /* Enables interrupt when conversion value is higher than the programmed threshold HTHV0 */
         vuint32_t  MSKWDG0L:1;        /* Enables interrupt when conversion value is lower than the programmed threshold LTHV0 */
      } B;
   } ADC_WTIMR_32B_tag;

   typedef union {   /* DMAE register */
      vuint32_t R;
      struct {
         vuint32_t:30;
         vuint32_t  DCLR:1;            /* DMA Clear sequence enable */
         vuint32_t  DMAEN:1;           /* DMA global enable */
      } B;
   } ADC_DMAE_32B_tag;

   typedef union {   /* DMA Register 0 (Precision channels) */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  DMA15:1;           /* Channel 15 DMA Enable */
         vuint32_t  DMA14:1;           /* Channel 14 DMA Enable */
         vuint32_t  DMA13:1;           /* Channel 13 DMA Enable */
         vuint32_t  DMA12:1;           /* Channel 12 DMA Enable */
         vuint32_t  DMA11:1;           /* Channel 11 DMA Enable */
         vuint32_t  DMA10:1;           /* Channel 10 DMA Enable */
         vuint32_t  DMA9:1;            /* Channel 9 DMA Enable */
         vuint32_t  DMA8:1;            /* Channel 8 DMA Enable */
         vuint32_t  DMA7:1;            /* Channel 7 DMA Enable */
         vuint32_t  DMA6:1;            /* Channel 6 DMA Enable */
         vuint32_t  DMA5:1;            /* Channel 5 DMA Enable */
         vuint32_t  DMA4:1;            /* Channel 4 DMA Enable */
         vuint32_t  DMA3:1;            /* Channel 3 DMA Enable */
         vuint32_t  DMA2:1;            /* Channel 2 DMA Enable */
         vuint32_t  DMA1:1;            /* Channel 1 DMA Enable */
         vuint32_t  DMA0:1;            /* Channel 0 DMA Enable */
      } B;
   } ADC_DMAR0_32B_tag;


   /* Register layout for all registers THRHLR ... */

   typedef union {   /* Threshold Register */
      vuint32_t R;
      struct {
         vuint32_t:4;
         vuint32_t  THRH:12;           /* High threshold value */
         vuint32_t:4;
         vuint32_t  THRL:12;           /* Low threshold value */
      } B;
   } ADC_THRHLR_32B_tag;

   typedef union {   /* Presampling Control Register */
      vuint32_t R;
      struct {
         vuint32_t:27;
         vuint32_t  PREVAL1:2;         /* Internal voltage selection for presampling (temp sensor channel) */
         vuint32_t  PREVAL0:2;         /* Internal voltage selection for presampling (internal precision channels) */
         vuint32_t  PRECONV:1;         /* Convert presampled value */
      } B;
   } ADC_PSCR_32B_tag;

   typedef union {   /* Presampling  Register  0 (Precision channels) */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  PRES15:1;          /* Channel 15 Presampling Enable */
         vuint32_t  PRES14:1;          /* Channel 14 Presampling Enable */
         vuint32_t  PRES13:1;          /* Channel 13 Presampling Enable */
         vuint32_t  PRES12:1;          /* Channel 12 Presampling Enable */
         vuint32_t  PRES11:1;          /* Channel 11 Presampling Enable */
         vuint32_t  PRES10:1;          /* Channel 10 Presampling Enable */
         vuint32_t  PRES9:1;           /* Channel 9 Presampling Enable */
         vuint32_t  PRES8:1;           /* Channel 8 Presampling Enable */
         vuint32_t  PRES7:1;           /* Channel 7 Presampling Enable */
         vuint32_t  PRES6:1;           /* Channel 6 Presampling Enable */
         vuint32_t  PRES5:1;           /* Channel 5 Presampling Enable */
         vuint32_t  PRES4:1;           /* Channel 4 Presampling Enable */
         vuint32_t  PRES3:1;           /* Channel 3 Presampling Enable */
         vuint32_t  PRES2:1;           /* Channel 2 Presampling Enable */
         vuint32_t  PRES1:1;           /* Channel 1 Presampling Enable */
         vuint32_t  PRES0:1;           /* Channel 0 Presampling Enable */
      } B;
   } ADC_PSR0_32B_tag;

   typedef union {   /* Conversion Timing Register 0 */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  INPLATCH:1;        /* Configuration of latching phase duration */
         vuint32_t:1;
         vuint32_t  OFFSHIFT:2;        /* Offset shift characteristics */
         vuint32_t:1;
         vuint32_t  INPCMP:2;          /* Comparison duration */
         vuint32_t:1;
         vuint32_t  INSAMP:8;          /* Configuration of sampling phase duration */
      } B;
   } ADC_CTR0_32B_tag;

   typedef union {   /* Conversion Timing Register 1 */
      vuint32_t R;
      struct {
         vuint32_t:24;
         vuint32_t  INSAMP:7;          /* Sampling phase duration */
         vuint32_t  TSENSOR_SEL:1;     /* Voltage select for temperature sensor */
      } B;
   } ADC_CTR1_32B_tag;

   typedef union {   /* Normal Conversion Mask Register  0 (Precision channels) */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  CH15:1;            /* Channel 15 Normal Sampling Enable */
         vuint32_t  CH14:1;            /* Channel 14 Normal Sampling Enable */
         vuint32_t  CH13:1;            /* Channel 13 Normal Sampling Enable */
         vuint32_t  CH12:1;            /* Channel 12 Normal Sampling Enable */
         vuint32_t  CH11:1;            /* Channel 11 Normal Sampling Enable */
         vuint32_t  CH10:1;            /* Channel 10 Normal Sampling Enable */
         vuint32_t  CH9:1;             /* Channel 9 Normal Sampling Enable */
         vuint32_t  CH8:1;             /* Channel 8 Normal Sampling Enable */
         vuint32_t  CH7:1;             /* Channel 7 Normal Sampling Enable */
         vuint32_t  CH6:1;             /* Channel 6 Normal Sampling Enable */
         vuint32_t  CH5:1;             /* Channel 5 Normal Sampling Enable */
         vuint32_t  CH4:1;             /* Channel 4 Normal Sampling Enable */
         vuint32_t  CH3:1;             /* Channel 3 Normal Sampling Enable */
         vuint32_t  CH2:1;             /* Channel 2 Normal Sampling Enable */
         vuint32_t  CH1:1;             /* Channel 1 Normal Sampling Enable */
         vuint32_t  CH0:1;             /* Channel 0 Normal Sampling Enable */
      } B;
   } ADC_NCMR0_32B_tag;

   typedef union {   /* Injected Conversion Mask Register  0 (Precision channels) */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  CH15:1;            /* Channel 15 Injected Sampling Enable */
         vuint32_t  CH14:1;            /* Channel 14 Injected Sampling Enable */
         vuint32_t  CH13:1;            /* Channel 13 Injected Sampling Enable */
         vuint32_t  CH12:1;            /* Channel 12 Injected Sampling Enable */
         vuint32_t  CH11:1;            /* Channel 11 Injected Sampling Enable */
         vuint32_t  CH10:1;            /* Channel 10 Injected Sampling Enable */
         vuint32_t  CH9:1;             /* Channel 9 Injected Sampling Enable */
         vuint32_t  CH8:1;             /* Channel 8 Injected Sampling Enable */
         vuint32_t  CH7:1;             /* Channel 7 Injected Sampling Enable */
         vuint32_t  CH6:1;             /* Channel 6 Injected Sampling Enable */
         vuint32_t  CH5:1;             /* Channel 5 Injected Sampling Enable */
         vuint32_t  CH4:1;             /* Channel 4 Injected Sampling Enable */
         vuint32_t  CH3:1;             /* Channel 3 Injected Sampling Enable */
         vuint32_t  CH2:1;             /* Channel 2 Injected Sampling Enable */
         vuint32_t  CH1:1;             /* Channel 1 Injected Sampling Enable */
         vuint32_t  CH0:1;             /* Channel 0 Injected Sampling Enable */
      } B;
   } ADC_JCMR0_32B_tag;

   typedef union {   /* Power Down Exit Delay Register */
      vuint32_t R;
      struct {
         vuint32_t:24;
         vuint32_t  PDED:8;            /* Delay between power down bit reset and starting of conversion */
      } B;
   } ADC_PDEDR_32B_tag;


   /* Register layout for all registers PRECDATAREG_WLSIDE1 ... */

   typedef union {   /* Channel Data Register (Precision channel) */
      vuint32_t R;
      struct {
         vuint32_t:12;
         vuint32_t  VALID:1;           /* Data is valid, clear on read */
         vuint32_t  OVERW:1;           /* Overwritten data */
         vuint32_t  RESULT:2;          /* Conversion mode of current result */
         vuint32_t  CDATA_WLSIDE1:12;   /* Converted data */
         vuint32_t:4;
      } B;
   } ADC_PRECDATAREG_WLSIDE1_32B_tag;


   /* Register layout for all registers PRECDATAREG ... */

   typedef union {   /* Channel Data Register */
      vuint32_t R;
      struct {
         vuint32_t:12;
         vuint32_t  VALID:1;           /* Data is valid, clear on read */
         vuint32_t  OVERW:1;           /* Overwritten data */
         vuint32_t  RESULT:2;          /* Conversion mode of current result */
         vuint32_t:4;
         vuint32_t  CDATA:12;          /* Converted data */
      } B;
   } ADC_CDR_32B_tag;

   typedef union {   /* Channel Data Register #0 */
      vuint32_t R;
      struct {
         vuint32_t:12;
         vuint32_t  VALID:1;           /* Data is valid, clear on read */
         vuint32_t  OVERW:1;           /* Overwritten data */
         vuint32_t  RESULT:2;          /* Conversion mode of current result */
         vuint32_t  CDATA_WLSIDE1:12;   /* Converted data */
         vuint32_t:4;
      } B;
   } ADC_CDR_WLSIDE1_32B_tag;

   typedef union {   /* Channel Watchdog Select Register 0 */
      vuint32_t R;
      struct {
         vuint32_t  WSEL_CH7:4;        /* Channel Watchdog select for channel 7 */
         vuint32_t  WSEL_CH6:4;        /* Channel Watchdog select for channel 6 */
         vuint32_t  WSEL_CH5:4;        /* Channel Watchdog select for channel 5 */
         vuint32_t  WSEL_CH4:4;        /* Channel Watchdog select for channel 4 */
         vuint32_t  WSEL_CH3:4;        /* Channel Watchdog select for channel 3 */
         vuint32_t  WSEL_CH2:4;        /* Channel Watchdog select for channel 2 */
         vuint32_t  WSEL_CH1:4;        /* Channel Watchdog select for channel 1 */
         vuint32_t  WSEL_CH0:4;        /* Channel Watchdog select for channel 0 */
      } B;
   } ADC_CWSELR0_32B_tag;

   typedef union {   /* Channel Watchdog Select Register 1 */
      vuint32_t R;
      struct {
         vuint32_t  WSEL_CH15:4;       /* Channel Watchdog select for channel 15 */
         vuint32_t  WSEL_CH14:4;       /* Channel Watchdog select for channel 14 */
         vuint32_t  WSEL_CH13:4;       /* Channel Watchdog select for channel 13 */
         vuint32_t  WSEL_CH12:4;       /* Channel Watchdog select for channel 12 */
         vuint32_t  WSEL_CH11:4;       /* Channel Watchdog select for channel 11 */
         vuint32_t  WSEL_CH10:4;       /* Channel Watchdog select for channel 10 */
         vuint32_t  WSEL_CH9:4;        /* Channel Watchdog select for channel 9 */
         vuint32_t  WSEL_CH8:4;        /* Channel Watchdog select for channel 8 */
      } B;
   } ADC_CWSELR1_32B_tag;

   typedef union {   /* Channel Watchdog Enable Register 0 (Precision channels) */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  CWEN15:1;          /* Watchdog feature enable for channel 15 */
         vuint32_t  CWEN14:1;          /* Watchdog feature enable for channel 14 */
         vuint32_t  CWEN13:1;          /* Watchdog feature enable for channel 13 */
         vuint32_t  CWEN12:1;          /* Watchdog feature enable for channel 12 */
         vuint32_t  CWEN11:1;          /* Watchdog feature enable for channel 11 */
         vuint32_t  CWEN10:1;          /* Watchdog feature enable for channel 10 */
         vuint32_t  CWEN9:1;           /* Watchdog feature enable for channel 9 */
         vuint32_t  CWEN8:1;           /* Watchdog feature enable for channel 8 */
         vuint32_t  CWEN7:1;           /* Watchdog feature enable for channel 7 */
         vuint32_t  CWEN6:1;           /* Watchdog feature enable for channel 6 */
         vuint32_t  CWEN5:1;           /* Watchdog feature enable for channel 5 */
         vuint32_t  CWEN4:1;           /* Watchdog feature enable for channel 4 */
         vuint32_t  CWEN3:1;           /* Watchdog feature enable for channel 3 */
         vuint32_t  CWEN2:1;           /* Watchdog feature enable for channel 2 */
         vuint32_t  CWEN1:1;           /* Watchdog feature enable for channel 1 */
         vuint32_t  CWEN0:1;           /* Watchdog feature enable for channel 0 */
      } B;
   } ADC_CWENR0_32B_tag;

   typedef union {   /* Analog Watchdog Out of Range Register 0 (Precision channels) */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  AWOR_CH15:1;       /* Channel 15 converted data out of range */
         vuint32_t  AWOR_CH14:1;       /* Channel 14 converted data out of range */
         vuint32_t  AWOR_CH13:1;       /* Channel 13 converted data out of range */
         vuint32_t  AWOR_CH12:1;       /* Channel 12 converted data out of range */
         vuint32_t  AWOR_CH11:1;       /* Channel 11 converted data out of range */
         vuint32_t  AWOR_CH10:1;       /* Channel 10 converted data out of range */
         vuint32_t  AWOR_CH9:1;        /* Channel 9 converted data out of range */
         vuint32_t  AWOR_CH8:1;        /* Channel 8 converted data out of range */
         vuint32_t  AWOR_CH7:1;        /* Channel 7 converted data out of range */
         vuint32_t  AWOR_CH6:1;        /* Channel 6 converted data out of range */
         vuint32_t  AWOR_CH5:1;        /* Channel 5 converted data out of range */
         vuint32_t  AWOR_CH4:1;        /* Channel 4 converted data out of range */
         vuint32_t  AWOR_CH3:1;        /* Channel 3 converted data out of range */
         vuint32_t  AWOR_CH2:1;        /* Channel 2 converted data out of range */
         vuint32_t  AWOR_CH1:1;        /* Channel 1 converted data out of range */
         vuint32_t  AWOR_CH0:1;        /* Channel 0 converted data out of range */
      } B;
   } ADC_AWORR0_32B_tag;

   typedef union {   /* Self Test Configuration Register 1 */
      vuint32_t R;
      struct {
         vuint32_t  INPSAMP_C:8;       /* Sampling phase duration for test conversions - algorithm C */
         vuint32_t  INPSAMP_CR:8;      /* Sampling phase duration for test conversions - algorithm RC */
         vuint32_t  INPSAMP_S:8;       /* Sampling phase duration for test conversions - algorithm S */
         vuint32_t:5;
         vuint32_t  ST_INPCMP:2;       /* Configuration bits for comparison phase duration for self test channel */
         vuint32_t  ST_INPLATCH:1;     /* Configuration bit for latching phase duration for self test channel */
      } B;
   } ADC_STCR1_32B_tag;

   typedef union {   /* Self Test Configuration Register 2 */
      vuint32_t R;
      struct {
         vuint32_t:4;
         vuint32_t  MSKWDSERR:1;       /* Interrupt enable (STSR1.WDSERR status bit) */
         vuint32_t  SERR:1;            /* Error fault injection */
         vuint32_t  MSKWDTERR:1;       /* Interrupt enable (STSR1.WDTERR status bit) */
         vuint32_t:1;
         vuint32_t  MSKST_EOC:1;       /* Interrupt enable bit for STSR1.ST_EOC */
         vuint32_t:4;
         vuint32_t  MSKWDG_EOA_C:1;    /* Interrupt enable (STSR1.WDG_EOA_C status bit) */
         vuint32_t  MSKWDG_EOA_RC:1;   /* Interrupt enable (STSR1.WDG_EOA_RC status bit) */
         vuint32_t  MSKWDG_EOA_S:1;    /* Interrupt enable (STSR1.WDG_EOA_S status bit) */
         vuint32_t  MSKERR_C:1;        /* Interrupt enable (STSR1.ERR_C status bit) */
         vuint32_t  MSKERR_RC:1;       /* Interrupt enable (STSR1.ERR_RC status bit) */
         vuint32_t  MSKERR_S2:1;       /* Interrupt enable (STSR1.ERR_S2 status bit) */
         vuint32_t  MSKERR_S1:1;       /* Interrupt enable (STSR1.ERR_S1 status bit) */
         vuint32_t  MSKERR_S0:1;       /* Interrupt enable (STSR1.ERR_S0 status bit) */
         vuint32_t:3;
         vuint32_t  EN:1;              /* Self testing channel enable */
         vuint32_t:2;
         vuint32_t  FMA_WDSERR:1;      /* Fault mapping for the Watchdog Sequence error */
         vuint32_t  FMA_WDTERR:1;      /* Fault mapping for the Watchdog Timer error */
         vuint32_t  FMA_C:1;           /* Fault mapping for the algorithm C */
         vuint32_t  FMA_RC:1;          /* Fault mapping for the algorithm RC */
         vuint32_t  FMA_S:1;           /* Fault mapping for the algorithm BGAP */
      } B;
   } ADC_STCR2_32B_tag;

   typedef union {   /* Self Test Configuration Register 3 */
      vuint32_t R;
      struct {
         vuint32_t:22;
         vuint32_t  ALG:2;             /* Algorithm scheduling */
         vuint32_t:3;
         vuint32_t  MSTEP:5;           /* Current step for algorithms S/RC/C */
      } B;
   } ADC_STCR3_32B_tag;

   typedef union {   /* Self Test Baud Rate Register */
      vuint32_t R;
      struct {
         vuint32_t:13;
         vuint32_t  WDT:3;             /* Watchdog timer value */
         vuint32_t:8;
         vuint32_t  BR:8;              /* Baud rate for the selected algorithm in SCAN mode */
      } B;
   } ADC_STBRR_32B_tag;

   typedef union {   /* Self Test Status Register 1 */
      vuint32_t R;
      struct {
         vuint32_t:4;
         vuint32_t  WDSERR:1;          /* Watchdog sequence error */
         vuint32_t:1;
         vuint32_t  WDTERR:1;          /* Watchdog timer error */
         vuint32_t  OVERWR:1;          /* Overwrite error */
         vuint32_t  ST_EOC:1;          /* Self test EOC bit */
         vuint32_t:4;
         vuint32_t  WDG_EOA_C:1;       /* Algorithm  C completed */
         vuint32_t  WDG_EOA_RC:1;      /* Algorithm RC completed */
         vuint32_t  WDG_EOA_S:1;       /* Algorithm  S completed */
         vuint32_t  ERR_C:1;           /* Error on self testing channel (algorithm  C) */
         vuint32_t  ERR_RC:1;          /* Error on self testing channel (algorithm RC) */
         vuint32_t  ERR_S2:1;          /* Error on self testing channel (algorithm SUPPLY, step 2) */
         vuint32_t  ERR_S1:1;          /* Error on self testing channel (algorithm SUPPLY, step 1) */
         vuint32_t  ERR_S0:1;          /* Error on self testing channel (algorithm SUPPLY, step 0) */
         vuint32_t:1;
         vuint32_t  STEP_C:5;          /* Step of algorithm  C when ERR_C  has occurred */
         vuint32_t  STEP_RC:5;         /* Step of algorithm RC when ERR_RC has occurred */
      } B;
   } ADC_STSR1_32B_tag;

   typedef union {   /* Self Test Status Register 2 */
      vuint32_t R;
      struct {
         vuint32_t  OVFL:1;            /* Overflow bit */
         vuint32_t:3;
         vuint32_t  DATA1:12;          /* Test channel converted data when ERR_S1 has occurred */
         vuint32_t:4;
         vuint32_t  DATA0:12;          /* Test channel converted data when ERR_S1 has occurred */
      } B;
   } ADC_STSR2_32B_tag;

   typedef union {   /* Self Test Status Register 3 */
      vuint32_t R;
      struct {
         vuint32_t:4;
         vuint32_t  DATA1:12;          /* Test channel converted data when ERR_S2 has occurred */
         vuint32_t:4;
         vuint32_t  DATA0:12;          /* Test channel converted data when ERR_S0 has occurred */
      } B;
   } ADC_STSR3_32B_tag;

   typedef union {   /* Self Test Status Register 4 */
      vuint32_t R;
      struct {
         vuint32_t:4;
         vuint32_t  DATA1:12;          /* Test channel converted data when ERR_C has occurred */
         vuint32_t:4;
         vuint32_t  DATA0:12;          /* Test channel converted data when ERR_RC has occurred */
      } B;
   } ADC_STSR4_32B_tag;

   typedef union {   /* Self Test Data Register 1 */
      vuint32_t R;
      struct {
         vuint32_t:12;
         vuint32_t  VALID:1;           /* Valid data */
         vuint32_t  OVERWR:1;          /* Overwrite data */
         vuint32_t:6;
         vuint32_t  TCDATA:12;         /* Test channel converted data */
      } B;
   } ADC_STDR1_32B_tag;

   typedef union {   /* Self Test Data Register 2 */
      vuint32_t R;
      struct {
         vuint32_t  FDATA:12;          /* Fractional part of the ratio TEST(step1)/TEST(step0) = VDD/VBGAP for algorithm S */
         vuint32_t  VALID:1;           /* Valid data */
         vuint32_t  OVERWR:1;          /* Overwrite data */
         vuint32_t:6;
         vuint32_t  IDATA:12;          /* Integer part of the ratio TEST(step1)/TEST(step0) = VDD/VBGAP for algorithm S */
      } B;
   } ADC_STDR2_32B_tag;

   typedef union {   /* Self Test Analog Watchdog Register 0 (algorithm S) */
      vuint32_t R;
      struct {
         vuint32_t  AWDE:1;            /* Analog WatchDog Enable */
         vuint32_t  WDTE:1;            /* WatchDog Timer Enable */
         vuint32_t:2;
         vuint32_t  THRH:12;           /* High threshold value for channel x */
         vuint32_t:4;
         vuint32_t  THRL:12;           /* Low threshold value for channel x */
      } B;
   } ADC_STAW0R_32B_tag;

   typedef union {   /* Self Test Analog Watchdog Register 1A */
      vuint32_t R;
      struct {
         vuint32_t  AWDE:1;            /* Analog WatchDog Enable (algorithm S - step 1) */
         vuint32_t:3;
         vuint32_t  THRH:12;           /* High threshold value (integer part) for test channel (algorithm S - step 1) */
         vuint32_t:4;
         vuint32_t  THRL:12;           /* Low threshold value (integer part) for test channel (algorithm S - step 1) */
      } B;
   } ADC_STAW1AR_32B_tag;

   typedef union {   /* Self Test Analog Watchdog Register 1B */
      vuint32_t R;
      struct {
         vuint32_t:4;
         vuint32_t  THRH:12;           /* High threshold value (fractional part) for test channel (algorithm S - step 1) */
         vuint32_t:4;
         vuint32_t  THRL:12;           /* Low threshold value (fractional part) for test channel (algorithm S - step 1) */
      } B;
   } ADC_STAW1BR_32B_tag;

   typedef union {   /* Self Test Analog Watchdog Register 2 */
      vuint32_t R;
      struct {
         vuint32_t  AWDE:1;            /* Analog WatchDog Enable (algorithm S - step 2) */
         vuint32_t:19;
         vuint32_t  THRL:12;           /* Low threshold value for channel x */
      } B;
   } ADC_STAW2R_32B_tag;

   typedef union {   /* Self Test Analog Watchdog Register 3 (algorithm RC) */
      vuint32_t R;
      struct {
         vuint32_t  AWDE:1;            /* Analog WatchDog Enable */
         vuint32_t  WDTE:1;            /* WatchDog Timer Enable */
         vuint32_t:2;
         vuint32_t  THRH:12;           /* High threshold value for channel x */
         vuint32_t:4;
         vuint32_t  THRL:12;           /* Low threshold value for channel x */
      } B;
   } ADC_STAW3R_32B_tag;

   typedef union {   /* Self Test Analog Watchdog Register 4 (algorithm C) */
      vuint32_t R;
      struct {
         vuint32_t  AWDE:1;            /* Analog WatchDog Enable */
         vuint32_t  WDTE:1;            /* WatchDog Timer Enable */
         vuint32_t:2;
         vuint32_t  THRH:12;           /* High threshold value for channel x */
         vuint32_t:4;
         vuint32_t  THRL:12;           /* Low threshold value for channel x */
      } B;
   } ADC_STAW4R_32B_tag;

   typedef union {   /* Self Test Analog Watchdog Register 5 */
      vuint32_t R;
      struct {
         vuint32_t:4;
         vuint32_t  THRH:12;           /* High threshold value for algorithm C (step 1 to step CS-1) */
         vuint32_t:4;
         vuint32_t  THRL:12;           /* Low threshold value for algorithm C (step 1 to step CS-1) */
      } B;
   } ADC_STAW5R_32B_tag;


   /* Register layout for generated register(s) CTR... */

   typedef union {   /*  */
      vuint32_t R;
   } ADC_CTR_32B_tag;


   /* Register layout for generated register(s) CWSELR... */

   typedef union {   /*  */
      vuint32_t R;
   } ADC_CWSELR_32B_tag;


   /* Register layout for generated register(s) CWENR... */

   typedef union {   /*  */
      vuint32_t R;
   } ADC_CWENR_32B_tag;


   /* Register layout for generated register(s) AWORR... */

   typedef union {   /*  */
      vuint32_t R;
   } ADC_AWORR_32B_tag;


   struct ADC_tag { /* Changed from "typedef struct ADC_struct_tag" to be able to reuse code */

                                          /* Main Configuration Register */
      ADC_MCR_32B_tag MCR;                 /* offset: 0x0000 size: 32 bit */
                                                 /* Main Status Register */
      ADC_MSR_32B_tag MSR;                 /* offset: 0x0004 size: 32 bit */
      int8_t ADC_reserved_0008[8];
                                            /* Interrupt Status Register */
      ADC_ISR_32B_tag ISR_STATUS;                 /* offset: 0x0010 size: 32 bit */ /* Renamed from ISR due to name clash in OS */
      union {
         ADC_CEOCFR0_32B_tag CEOCFR[3];    /* offset: 0x0014  (0x0004 x 3) */

         struct {
                      /* Channel Pending Register 0 (Precision channels) */
            ADC_CEOCFR0_32B_tag CEOCFR0;   /* offset: 0x0014 size: 32 bit */
            int8_t ADC_reserved_0018_E1[8];
         };

      };
                                              /* Interrupt Mask Register */
      ADC_IMR_32B_tag IMR;                 /* offset: 0x0020 size: 32 bit */
      union {
         ADC_CIMR0_32B_tag CIMR[3];        /* offset: 0x0024  (0x0004 x 3) */

         struct {
               /* Channel Interrupt Mask Register 0 (Precision channels) */
            ADC_CIMR0_32B_tag CIMR0;       /* offset: 0x0024 size: 32 bit */
            int8_t ADC_reserved_0028_E1[8];
         };

      };
                         /* Watchdog Threshold Interrupt Status Register */
      ADC_WTISR_32B_tag WTISR;             /* offset: 0x0030 size: 32 bit */
                           /* Watchdog Threshold Interrupt Mask register */
      ADC_WTIMR_32B_tag WTIMR;             /* offset: 0x0034 size: 32 bit */
      int8_t ADC_reserved_0038[8];
                                                        /* DMAE register */
      ADC_DMAE_32B_tag DMAE;               /* offset: 0x0040 size: 32 bit */
      union {
         ADC_DMAR0_32B_tag DMAR[3];        /* offset: 0x0044  (0x0004 x 3) */

         struct {
                                  /* DMA Register 0 (Precision channels) */
            ADC_DMAR0_32B_tag DMAR0;       /* offset: 0x0044 size: 32 bit */
            int8_t ADC_reserved_0048_E1[8];
         };

      };
      int8_t ADC_reserved_0050[16];
      union {
                                                   /* Threshold Register */
         ADC_THRHLR_32B_tag THRHLR[4];     /* offset: 0x0060  (0x0004 x 4) */

         struct {
                                                   /* Threshold Register */
            ADC_THRHLR_32B_tag THRHLR0;    /* offset: 0x0060 size: 32 bit */
            ADC_THRHLR_32B_tag THRHLR1;    /* offset: 0x0064 size: 32 bit */
            ADC_THRHLR_32B_tag THRHLR2;    /* offset: 0x0068 size: 32 bit */
            ADC_THRHLR_32B_tag THRHLR3;    /* offset: 0x006C size: 32 bit */
         };

      };
      int8_t ADC_reserved_0070[16];
                                         /* Presampling Control Register */
      ADC_PSCR_32B_tag PSCR;               /* offset: 0x0080 size: 32 bit */
      union {
         ADC_PSR0_32B_tag PSR[3];          /* offset: 0x0084  (0x0004 x 3) */

         struct {
                        /* Presampling  Register  0 (Precision channels) */
            ADC_PSR0_32B_tag PSR0;         /* offset: 0x0084 size: 32 bit */
            int8_t ADC_reserved_0088_E1[8];
         };

      };
      int8_t ADC_reserved_0090[4];
      union {
         ADC_CTR_32B_tag CTR[3];           /* offset: 0x0094  (0x0004 x 3) */

         struct {
                                         /* Conversion Timing Register 0 */
            ADC_CTR0_32B_tag CTR0;         /* offset: 0x0094 size: 32 bit */
                                         /* Conversion Timing Register 1 */
            ADC_CTR1_32B_tag CTR1;         /* offset: 0x0098 size: 32 bit */
            int8_t ADC_reserved_009C_E1[4];
         };

      };
      int8_t ADC_reserved_00A0[4];
      union {
         ADC_NCMR0_32B_tag NCMR[3];        /* offset: 0x00A4  (0x0004 x 3) */

         struct {
              /* Normal Conversion Mask Register  0 (Precision channels) */
            ADC_NCMR0_32B_tag NCMR0;       /* offset: 0x00A4 size: 32 bit */
            int8_t ADC_reserved_00A8_E1[8];
         };

      };
      int8_t ADC_reserved_00B0[4];
      union {
         ADC_JCMR0_32B_tag JCMR[3];        /* offset: 0x00B4  (0x0004 x 3) */

         struct {
            /* Injected Conversion Mask Register  0 (Precision channels) */
            ADC_JCMR0_32B_tag JCMR0;       /* offset: 0x00B4 size: 32 bit */
            int8_t ADC_reserved_00B8_E1[8];
         };

      };
      int8_t ADC_reserved_00C0[8];
                                       /* Power Down Exit Delay Register */
      ADC_PDEDR_32B_tag PDEDR;             /* offset: 0x00C8 size: 32 bit */
      int8_t ADC_reserved_00CC[52];
      union {
         struct {
                            /* Channel Data Register (Precision channel) */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG0_WLSIDE1;  /* offset: 0x0100 size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG1_WLSIDE1;  /* offset: 0x0104 size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG2_WLSIDE1;  /* offset: 0x0108 size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG3_WLSIDE1;  /* offset: 0x010C size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG4_WLSIDE1;  /* offset: 0x0110 size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG5_WLSIDE1;  /* offset: 0x0114 size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG6_WLSIDE1;  /* offset: 0x0118 size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG7_WLSIDE1;  /* offset: 0x011C size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG8_WLSIDE1;  /* offset: 0x0120 size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG9_WLSIDE1;  /* offset: 0x0124 size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG10_WLSIDE1;  /* offset: 0x0128 size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG11_WLSIDE1;  /* offset: 0x012C size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG12_WLSIDE1;  /* offset: 0x0130 size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG13_WLSIDE1;  /* offset: 0x0134 size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG14_WLSIDE1;  /* offset: 0x0138 size: 32 bit */
            ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG15_WLSIDE1;  /* offset: 0x013C size: 32 bit */
         };

                            /* Channel Data Register (Precision channel) */
         ADC_PRECDATAREG_WLSIDE1_32B_tag PRECDATAREG_WLSIDE1[16];  /* offset: 0x0100  (0x0004 x 16) */

                                                /* Channel Data Register */
         ADC_CDR_32B_tag PRECDATAREG[16];  /* offset: 0x0100  (0x0004 x 16) */

         struct {
                                                /* Channel Data Register */
            ADC_CDR_32B_tag PRECDATAREG0;  /* offset: 0x0100 size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG1;  /* offset: 0x0104 size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG2;  /* offset: 0x0108 size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG3;  /* offset: 0x010C size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG4;  /* offset: 0x0110 size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG5;  /* offset: 0x0114 size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG6;  /* offset: 0x0118 size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG7;  /* offset: 0x011C size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG8;  /* offset: 0x0120 size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG9;  /* offset: 0x0124 size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG10;  /* offset: 0x0128 size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG11;  /* offset: 0x012C size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG12;  /* offset: 0x0130 size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG13;  /* offset: 0x0134 size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG14;  /* offset: 0x0138 size: 32 bit */
            ADC_CDR_32B_tag PRECDATAREG15;  /* offset: 0x013C size: 32 bit */
         };

         struct {
                                             /* Channel Data Register #0 */
            ADC_CDR_WLSIDE1_32B_tag CDR0_WLSIDE1;  /* offset: 0x0100 size: 32 bit */
                                             /* Channel Data Register #1 */
            ADC_CDR_WLSIDE1_32B_tag CDR1_WLSIDE1;  /* offset: 0x0104 size: 32 bit */
                                             /* Channel Data Register #2 */
            ADC_CDR_WLSIDE1_32B_tag CDR2_WLSIDE1;  /* offset: 0x0108 size: 32 bit */
                                             /* Channel Data Register #3 */
            ADC_CDR_WLSIDE1_32B_tag CDR3_WLSIDE1;  /* offset: 0x010C size: 32 bit */
                                             /* Channel Data Register #4 */
            ADC_CDR_WLSIDE1_32B_tag CDR4_WLSIDE1;  /* offset: 0x0110 size: 32 bit */
                                             /* Channel Data Register #5 */
            ADC_CDR_WLSIDE1_32B_tag CDR5_WLSIDE1;  /* offset: 0x0114 size: 32 bit */
                                             /* Channel Data Register #6 */
            ADC_CDR_WLSIDE1_32B_tag CDR6_WLSIDE1;  /* offset: 0x0118 size: 32 bit */
                                             /* Channel Data Register #7 */
            ADC_CDR_WLSIDE1_32B_tag CDR7_WLSIDE1;  /* offset: 0x011C size: 32 bit */
                                             /* Channel Data Register #8 */
            ADC_CDR_WLSIDE1_32B_tag CDR8_WLSIDE1;  /* offset: 0x0120 size: 32 bit */
                                             /* Channel Data Register #9 */
            ADC_CDR_WLSIDE1_32B_tag CDR9_WLSIDE1;  /* offset: 0x0124 size: 32 bit */
                                            /* Channel Data Register #10 */
            ADC_CDR_WLSIDE1_32B_tag CDR10_WLSIDE1;  /* offset: 0x0128 size: 32 bit */
                                            /* Channel Data Register #11 */
            ADC_CDR_WLSIDE1_32B_tag CDR11_WLSIDE1;  /* offset: 0x012C size: 32 bit */
                                            /* Channel Data Register #12 */
            ADC_CDR_WLSIDE1_32B_tag CDR12_WLSIDE1;  /* offset: 0x0130 size: 32 bit */
                                            /* Channel Data Register #13 */
            ADC_CDR_WLSIDE1_32B_tag CDR13_WLSIDE1;  /* offset: 0x0134 size: 32 bit */
                                            /* Channel Data Register #14 */
            ADC_CDR_WLSIDE1_32B_tag CDR14_WLSIDE1;  /* offset: 0x0138 size: 32 bit */
                                            /* Channel Data Register #15 */
            ADC_CDR_WLSIDE1_32B_tag CDR15_WLSIDE1;  /* offset: 0x013C size: 32 bit */
         };

         struct {
#if 0
                                             /* Channel Data Register #0 */
            ADC_CDR_32B_tag CDR0;          /* offset: 0x0100 size: 32 bit */
                                             /* Channel Data Register #1 */
            ADC_CDR_32B_tag CDR1;          /* offset: 0x0104 size: 32 bit */
                                             /* Channel Data Register #2 */
            ADC_CDR_32B_tag CDR2;          /* offset: 0x0108 size: 32 bit */
                                             /* Channel Data Register #3 */
            ADC_CDR_32B_tag CDR3;          /* offset: 0x010C size: 32 bit */
                                             /* Channel Data Register #4 */
            ADC_CDR_32B_tag CDR4;          /* offset: 0x0110 size: 32 bit */
                                             /* Channel Data Register #5 */
            ADC_CDR_32B_tag CDR5;          /* offset: 0x0114 size: 32 bit */
                                             /* Channel Data Register #6 */
            ADC_CDR_32B_tag CDR6;          /* offset: 0x0118 size: 32 bit */
                                             /* Channel Data Register #7 */
            ADC_CDR_32B_tag CDR7;          /* offset: 0x011C size: 32 bit */
                                             /* Channel Data Register #8 */
            ADC_CDR_32B_tag CDR8;          /* offset: 0x0120 size: 32 bit */
                                             /* Channel Data Register #9 */
            ADC_CDR_32B_tag CDR9;          /* offset: 0x0124 size: 32 bit */
                                            /* Channel Data Register #10 */
            ADC_CDR_32B_tag CDR10;         /* offset: 0x0128 size: 32 bit */
                                            /* Channel Data Register #11 */
            ADC_CDR_32B_tag CDR11;         /* offset: 0x012C size: 32 bit */
                                            /* Channel Data Register #12 */
            ADC_CDR_32B_tag CDR12;         /* offset: 0x0130 size: 32 bit */
                                            /* Channel Data Register #13 */
            ADC_CDR_32B_tag CDR13;         /* offset: 0x0134 size: 32 bit */
                                            /* Channel Data Register #14 */
            ADC_CDR_32B_tag CDR14;         /* offset: 0x0138 size: 32 bit */
                                            /* Channel Data Register #15 */
            ADC_CDR_32B_tag CDR15;         /* offset: 0x013C size: 32 bit */
#else
            /* Using array instead to be able to reuse code*/
            ADC_CDR_32B_tag CDR[16];
#endif
         };

      };
      int8_t ADC_reserved_0140[320];
                                             /* Upper Threshold register */
      ADC_THRHLR_32B_tag THRHLR4;          /* offset: 0x0280 size: 32 bit */
                                             /* Upper Threshold register */
      ADC_THRHLR_32B_tag THRHLR5;          /* offset: 0x0284 size: 32 bit */
                                             /* Upper Threshold register */
      ADC_THRHLR_32B_tag THRHLR6;          /* offset: 0x0288 size: 32 bit */
                                             /* Upper Threshold register */
      ADC_THRHLR_32B_tag THRHLR7;          /* offset: 0x028C size: 32 bit */
                                             /* Upper Threshold register */
      ADC_THRHLR_32B_tag THRHLR8;          /* offset: 0x0290 size: 32 bit */
                                             /* Upper Threshold register */
      ADC_THRHLR_32B_tag THRHLR9;          /* offset: 0x0294 size: 32 bit */
                                             /* Upper Threshold register */
      ADC_THRHLR_32B_tag THRHLR10;         /* offset: 0x0298 size: 32 bit */
                                             /* Upper Threshold register */
      ADC_THRHLR_32B_tag THRHLR11;         /* offset: 0x029C size: 32 bit */
                                             /* Upper Threshold register */
      ADC_THRHLR_32B_tag THRHLR12;         /* offset: 0x02A0 size: 32 bit */
                                             /* Upper Threshold register */
      ADC_THRHLR_32B_tag THRHLR13;         /* offset: 0x02A4 size: 32 bit */
                                             /* Upper Threshold register */
      ADC_THRHLR_32B_tag THRHLR14;         /* offset: 0x02A8 size: 32 bit */
                                             /* Upper Threshold register */
      ADC_THRHLR_32B_tag THRHLR15;         /* offset: 0x02AC size: 32 bit */
      union {
         ADC_CWSELR_32B_tag CWSELR[12];    /* offset: 0x02B0  (0x0004 x 12) */

         struct {
                                   /* Channel Watchdog Select Register 0 */
            ADC_CWSELR0_32B_tag CWSELR0;   /* offset: 0x02B0 size: 32 bit */
                                   /* Channel Watchdog Select Register 1 */
            ADC_CWSELR1_32B_tag CWSELR1;   /* offset: 0x02B4 size: 32 bit */
            int8_t ADC_reserved_02B8_E1[40];
         };

      };
      union {
         ADC_CWENR_32B_tag CWENR[3];       /* offset: 0x02E0  (0x0004 x 3) */

         struct {
              /* Channel Watchdog Enable Register 0 (Precision channels) */
            ADC_CWENR0_32B_tag CWENR0;     /* offset: 0x02E0 size: 32 bit */
            int8_t ADC_reserved_02E4_E1[8];
         };

      };
      int8_t ADC_reserved_02EC[4];
      union {
         ADC_AWORR_32B_tag AWORR[3];       /* offset: 0x02F0  (0x0004 x 3) */

         struct {
          /* Analog Watchdog Out of Range Register 0 (Precision channels) */
            ADC_AWORR0_32B_tag AWORR0;     /* offset: 0x02F0 size: 32 bit */
            int8_t ADC_reserved_02F4_E1[8];
         };

      };
      int8_t ADC_reserved_02FC[68];
                                   /* Self Test Configuration Register 1 */
      ADC_STCR1_32B_tag STCR1;             /* offset: 0x0340 size: 32 bit */
                                   /* Self Test Configuration Register 2 */
      ADC_STCR2_32B_tag STCR2;             /* offset: 0x0344 size: 32 bit */
                                   /* Self Test Configuration Register 3 */
      ADC_STCR3_32B_tag STCR3;             /* offset: 0x0348 size: 32 bit */
                                         /* Self Test Baud Rate Register */
      ADC_STBRR_32B_tag STBRR;             /* offset: 0x034C size: 32 bit */
                                          /* Self Test Status Register 1 */
      ADC_STSR1_32B_tag STSR1;             /* offset: 0x0350 size: 32 bit */
                                          /* Self Test Status Register 2 */
      ADC_STSR2_32B_tag STSR2;             /* offset: 0x0354 size: 32 bit */
                                          /* Self Test Status Register 3 */
      ADC_STSR3_32B_tag STSR3;             /* offset: 0x0358 size: 32 bit */
                                          /* Self Test Status Register 4 */
      ADC_STSR4_32B_tag STSR4;             /* offset: 0x035C size: 32 bit */
      int8_t ADC_reserved_0360[16];
                                            /* Self Test Data Register 1 */
      ADC_STDR1_32B_tag STDR1;             /* offset: 0x0370 size: 32 bit */
                                            /* Self Test Data Register 2 */
      ADC_STDR2_32B_tag STDR2;             /* offset: 0x0374 size: 32 bit */
      int8_t ADC_reserved_0378[8];
                   /* Self Test Analog Watchdog Register 0 (algorithm S) */
      ADC_STAW0R_32B_tag STAW0R;           /* offset: 0x0380 size: 32 bit */
                                /* Self Test Analog Watchdog Register 1A */
      ADC_STAW1AR_32B_tag STAW1AR;         /* offset: 0x0384 size: 32 bit */
                                /* Self Test Analog Watchdog Register 1B */
      ADC_STAW1BR_32B_tag STAW1BR;         /* offset: 0x0388 size: 32 bit */
                                 /* Self Test Analog Watchdog Register 2 */
      ADC_STAW2R_32B_tag STAW2R;           /* offset: 0x038C size: 32 bit */
                  /* Self Test Analog Watchdog Register 3 (algorithm RC) */
      ADC_STAW3R_32B_tag STAW3R;           /* offset: 0x0390 size: 32 bit */
                   /* Self Test Analog Watchdog Register 4 (algorithm C) */
      ADC_STAW4R_32B_tag STAW4R;           /* offset: 0x0394 size: 32 bit */
                                 /* Self Test Analog Watchdog Register 5 */
      ADC_STAW5R_32B_tag STAW5R;           /* offset: 0x0398 size: 32 bit */
      int8_t ADC_reserved_039C[15460];

   };/* ADC_tag */


#define ADC0_BASEADDRESS 0xFFE00000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define ADC0  (*(volatile ADC_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE00000UL))
#define ADC1_BASEADDRESS 0xFFE04000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define ADC1  (*(volatile ADC_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE04000UL))



/****************************************************************/
/*                                                              */
/* Module: CTU  */
/*                                                              */
/****************************************************************/

   typedef union {   /* CTU Trigger Generator Subunit Input Selection register */
      vuint32_t R;
      struct {
         vuint32_t  I15_FE:1;          /* Input 15 ext_signal Falling Edge Enable */
         vuint32_t  I15_RE:1;          /* Input 15 ext_signal Rising Edge Enable */
         vuint32_t  I14_FE:1;          /* Input 14 eTimer2 Falling Edge Enable */
         vuint32_t  I14_RE:1;          /* Input 14 eTimer2 Rising Edge Enable */
         vuint32_t  I13_FE:1;          /* Input 13 eTimer1 Falling Edge Enable */
         vuint32_t  I13_RE:1;          /* Input 13 eTimer1 Rising Edge Enable */
         vuint32_t  I12_FE:1;          /* Input 12 Real PWM ch.3 Falling Edge Enable */
         vuint32_t  I12_RE:1;          /* Input 12 Real PWM ch.3 Rising Edge Enable */
         vuint32_t  I11_FE:1;          /* Input 11 Real PWM ch.2 Falling Edge Enable */
         vuint32_t  I11_RE:1;          /* Input 11 Real PWM ch.2 Rising Edge Enable */
         vuint32_t  I10_FE:1;          /* Input 10 Real PWM ch.1 Falling Edge Enable */
         vuint32_t  I10_RE:1;          /* Input 10 Real PWM ch.1 Rising Edge Enable */
         vuint32_t  I9_FE:1;           /* Input 9 Real PWM ch.0 Falling Edge Enable */
         vuint32_t  I9_RE:1;           /* Input 9 Real PWM ch.0 Rising Edge Enable */
         vuint32_t  I8_FE:1;           /* Input 8 PWM ch.3 even Falling Edge Enable */
         vuint32_t  I8_RE:1;           /* Input 8 PWM ch.3 even Rising Edge Enable */
         vuint32_t  I7_FE:1;           /* Input 7 PWM ch.2 even Falling Edge Enable */
         vuint32_t  I7_RE:1;           /* Input 7 PWM ch.2 even Rising Edge Enable */
         vuint32_t  I6_FE:1;           /* Input 6 PWM ch.1 even Falling Edge Enable */
         vuint32_t  I6_RE:1;           /* Input 6 PWM ch.1 even Rising Edge Enable */
         vuint32_t  I5_FE:1;           /* Input 5 PWM ch.0 even Falling Edge Enable */
         vuint32_t  I5_RE:1;           /* Input 5 PWM ch.0 even Rising Edge Enable */
         vuint32_t  I4_FE:1;           /* Input 4 PWM ch.3 odd Falling Edge Enable */
         vuint32_t  I4_RE:1;           /* Input 4 PWM ch.3 odd Rising Edge Enable */
         vuint32_t  I3_FE:1;           /* Input 3 PWM ch.2 odd Falling Edge Enable */
         vuint32_t  I3_RE:1;           /* Input 3 PWM ch.2 odd Rising Edge Enable */
         vuint32_t  I2_FE:1;           /* Input 2 PWM ch.1 odd Falling Edge Enable */
         vuint32_t  I2_RE:1;           /* Input 2 PWM ch.1 odd Rising Edge Enable */
         vuint32_t  I1_FE:1;           /* Input 1 PWM ch.0 odd Falling Edge Enable */
         vuint32_t  I1_RE:1;           /* Input 1 PWM ch.0 odd Rising Edge Enable */
         vuint32_t  I0_FE:1;           /* Input 0 PWM reload Falling Edge Enable */
         vuint32_t  I0_RE:1;           /* Input 0 PWM reload Rising Edge Enable */
      } B;
   } CTU_TGSISR_32B_tag;

   typedef union {   /* CTU Trigger Generator Subunit Control Register */
      vuint16_t R;
      struct {
         vuint16_t:7;
         vuint16_t  ET_TM:1;           /* External Trigger Toggle Mode Enable */
         vuint16_t  PRES:2;            /* TGS and SU Prescaler Selection */
         vuint16_t  MRS_SM:5;          /* MRS Selection in Sequential Mode */
         vuint16_t  TGS_M:1;           /* Trigger Generator Subunit Mode */
      } B;
   } CTU_TGSCR_16B_tag;


   /* Register layout for all registers TCR ... */

   typedef union {   /* Trigger n Compare Register */
      vuint16_t R;
   } CTU_TCR_16B_tag;

   typedef union {   /* TGS Counter Compare Register */
      vuint16_t R;
      struct {
         vuint16_t  TGSCCV:16;         /* TGS Counter Compare Value */
      } B;
   } CTU_TGSCCR_16B_tag;

   typedef union {   /* TGS Counter Reload Register */
      vuint16_t R;
      struct {
         vuint16_t  TGSCRV:16;         /* TGS Counter Reload Value */
      } B;
   } CTU_TGSCRR_16B_tag;

   typedef union {   /* Commands List Control Register 1 */
      vuint32_t R;
      struct {
         vuint32_t:3;
         vuint32_t  T3INDEX:5;         /* Trigger 3 First Command address */
         vuint32_t:3;
         vuint32_t  T2INDEX:5;         /* Trigger 2 First Command address */
         vuint32_t:3;
         vuint32_t  T1INDEX:5;         /* Trigger 1 First Command address */
         vuint32_t:3;
         vuint32_t  T0INDEX:5;         /* Trigger 0 First Command address */
      } B;
   } CTU_CLCR1_32B_tag;

   typedef union {   /* Commands List Control Register 2 */
      vuint32_t R;
      struct {
         vuint32_t:3;
         vuint32_t  T7INDEX:5;         /* Trigger 7 First Command address */
         vuint32_t:3;
         vuint32_t  T6INDEX:5;         /* Trigger 6 First Command address */
         vuint32_t:3;
         vuint32_t  T5INDEX:5;         /* Trigger 5 First Command address */
         vuint32_t:3;
         vuint32_t  T4INDEX:5;         /* Trigger 4 First Command address */
      } B;
   } CTU_CLCR2_32B_tag;

   typedef union {   /* Trigger Handler Control Register 1 */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  T3_E:1;            /* Trigger 3  enable */
         vuint32_t  T3_ETE:1;          /* Trigger 3 Ext Trigger output enable */
         vuint32_t  T3_T4E:1;          /* Trigger 3 Timer4 output enable */
         vuint32_t  T3_T3E:1;          /* Trigger 3 Timer3 output enable */
         vuint32_t  T3_T2E:1;          /* Trigger 3 Timer2 output enable */
         vuint32_t  T3_T1E:1;          /* Trigger 3 Timer1 output enable */
         vuint32_t  T3_ADCE:1;         /* Trigger 3 ADC command output enable */
         vuint32_t:1;
         vuint32_t  T2_E:1;            /* Trigger 2  enable */
         vuint32_t  T2_ETE:1;          /* Trigger 2 Ext Trigger output enable */
         vuint32_t  T2_T4E:1;          /* Trigger 2 Timer4 output enable */
         vuint32_t  T2_T3E:1;          /* Trigger 2 Timer3 output enable */
         vuint32_t  T2_T2E:1;          /* Trigger 2 Timer2 output enable */
         vuint32_t  T2_T1E:1;          /* Trigger 2 Timer1 output enable */
         vuint32_t  T2_ADCE:1;         /* Trigger 2 ADC command output enable */
         vuint32_t:1;
         vuint32_t  T1_E:1;            /* Trigger 1  enable */
         vuint32_t  T1_ETE:1;          /* Trigger 1 Ext Trigger output enable */
         vuint32_t  T1_T4E:1;          /* Trigger 1 Timer4 output enable */
         vuint32_t  T1_T3E:1;          /* Trigger 1 Timer3 output enable */
         vuint32_t  T1_T2E:1;          /* Trigger 1 Timer2 output enable */
         vuint32_t  T1_T1E:1;          /* Trigger 1 Timer1 output enable */
         vuint32_t  T1_ADCE:1;         /* Trigger 1 ADC command output enable */
         vuint32_t:1;
         vuint32_t  T0_E:1;            /* Trigger 0  enable */
         vuint32_t  T0_ETE:1;          /* Trigger 0 Ext Trigger output enable */
         vuint32_t  T0_T4E:1;          /* Trigger 0 Timer4 output enable */
         vuint32_t  T0_T3E:1;          /* Trigger 0 Timer3 output enable */
         vuint32_t  T0_T2E:1;          /* Trigger 0 Timer2 output enable */
         vuint32_t  T0_T1E:1;          /* Trigger 0 Timer1 output enable */
         vuint32_t  T0_ADCE:1;         /* Trigger 0 ADC command output enable */
      } B;
   } CTU_THCR1_32B_tag;

   typedef union {   /* Trigger Handler Control Register 2 */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  T7_E:1;            /* Trigger 7  enable */
         vuint32_t  T7_ETE:1;          /* Trigger 7 Ext Trigger output enable */
         vuint32_t  T7_T4E:1;          /* Trigger 7 Timer4 output enable */
         vuint32_t  T7_T3E:1;          /* Trigger 7 Timer3 output enable */
         vuint32_t  T7_T2E:1;          /* Trigger 7 Timer2 output enable */
         vuint32_t  T7_T1E:1;          /* Trigger 7 Timer1 output enable */
         vuint32_t  T7_ADCE:1;         /* Trigger 7 ADC command output enable */
         vuint32_t:1;
         vuint32_t  T6_E:1;            /* Trigger 6  enable */
         vuint32_t  T6_ETE:1;          /* Trigger 6 Ext Trigger output enable */
         vuint32_t  T6_T4E:1;          /* Trigger 6 Timer4 output enable */
         vuint32_t  T6_T3E:1;          /* Trigger 6 Timer3 output enable */
         vuint32_t  T6_T2E:1;          /* Trigger 6 Timer2 output enable */
         vuint32_t  T6_T1E:1;          /* Trigger 6 Timer1 output enable */
         vuint32_t  T6_ADCE:1;         /* Trigger 6 ADC command output enable */
         vuint32_t:1;
         vuint32_t  T5_E:1;            /* Trigger 5  enable */
         vuint32_t  T5_ETE:1;          /* Trigger 5 Ext Trigger output enable */
         vuint32_t  T5_T4E:1;          /* Trigger 5 Timer4 output enable */
         vuint32_t  T5_T3E:1;          /* Trigger 5 Timer3 output enable */
         vuint32_t  T5_T2E:1;          /* Trigger 5 Timer2 output enable */
         vuint32_t  T5_T1E:1;          /* Trigger 5 Timer1 output enable */
         vuint32_t  T5_ADCE:1;         /* Trigger 5 ADC command output enable */
         vuint32_t:1;
         vuint32_t  T4_E:1;            /* Trigger 4  enable */
         vuint32_t  T4_ETE:1;          /* Trigger 4 Ext Trigger output enable */
         vuint32_t  T4_T4E:1;          /* Trigger 4 Timer4 output enable */
         vuint32_t  T4_T3E:1;          /* Trigger 4 Timer3 output enable */
         vuint32_t  T4_T2E:1;          /* Trigger 4 Timer2 output enable */
         vuint32_t  T4_T1E:1;          /* Trigger 4 Timer1 output enable */
         vuint32_t  T4_ADCE:1;         /* Trigger 4 ADC command output enable */
      } B;
   } CTU_THCR2_32B_tag;


   /* Register layout for all registers CLR_SCM ... */

   typedef union {   /* Command List Register - single conversion mode */
      vuint16_t R;
      struct {
         vuint16_t  CIR:1;             /* Command Execution Interrupt Request enable */
         vuint16_t  FC:1;              /* First Command */
         vuint16_t  CMS:1;             /* Conversion Mode Selection (0: single conversion) */
         vuint16_t  FIFO:3;            /* FIFO for ADC A/B */
         vuint16_t  ST0:1;             /* Self Test Mode Control (=0) */
         vuint16_t:3;
         vuint16_t  SU:1;              /* Selection Unit */
         vuint16_t:1;
         vuint16_t  CH:4;              /* ADC unit channel number */
      } B;
   } CTU_CLR_SCM_16B_tag;


   /* Register layout for all registers CLR_DCM ... */

   typedef union {   /* Command List Register - dual Conversion Mode */
      vuint16_t R;
      struct {
         vuint16_t  CIR:1;             /* Command Execution Interrupt Request enable */
         vuint16_t  FC:1;              /* First Command */
         vuint16_t  CMS:1;             /* Conversion Mode Selection (1: dual conversion) */
         vuint16_t  FIFO:3;            /* FIFO for ADC A/B */
         vuint16_t  ST0:1;             /* Self Test Mode Control (=0) */
         vuint16_t  CH_B:4;            /* ADC unit B channel number */
         vuint16_t:1;
         vuint16_t  CH_A:4;            /* ADC unit A channel number */
      } B;
   } CTU_CLR_DCM_16B_tag;


   /* Register layout for all registers CLR ... */

   typedef union {   /* Command List Register. View: BIT13, BIT9 */
      vuint16_t R;
      struct {
         vuint16_t:2;
         vuint16_t  ST1:1;             /* Self test mode bit 1 */
         vuint16_t:3;
         vuint16_t  ST0:1;             /* Self test mode bit 0 */
         vuint16_t:9;
      } B;
   } CTU_CLR_16B_tag;

   typedef union {   /* FIFO DMA Control Register */
      vuint16_t R;
      struct {
         vuint16_t:12;
         vuint16_t  DE3:1;             /* FIFO 3 DMA enable */
         vuint16_t  DE2:1;             /* FIFO 2 DMA enable */
         vuint16_t  DE1:1;             /* FIFO 1 DMA enable */
         vuint16_t  DE0:1;             /* FIFO 0 DMA enable */
      } B;
   } CTU_FDCR_16B_tag;

   typedef union {   /* FIFO Control Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  OR_EN3:1;          /* FIFO 3 Overrun interrupt enable */
         vuint32_t  OF_EN3:1;          /* FIFO 3 Threshold Overflow interrupt enable */
         vuint32_t  EMPTY_EN3:1;       /* FIFO 3 Empty interrupt enable */
         vuint32_t  FULL_EN3:1;        /* FIFO 3 Full interrupt enable */
         vuint32_t  OR_EN2:1;          /* FIFO 2 Overrun interrupt enable */
         vuint32_t  OF_EN2:1;          /* FIFO 2 Threshold Overflow interrupt enable */
         vuint32_t  EMPTY_EN2:1;       /* FIFO 2 Empty interrupt enable */
         vuint32_t  FULL_EN2:1;        /* FIFO 2 Full interrupt enable */
         vuint32_t  OR_EN1:1;          /* FIFO 1 Overrun interrupt enable */
         vuint32_t  OF_EN1:1;          /* FIFO 1 Threshold Overflow interrupt enable */
         vuint32_t  EMPTY_EN1:1;       /* FIFO 1 Empty interrupt enable */
         vuint32_t  FULL_EN1:1;        /* FIFO 1 Full interrupt enable */
         vuint32_t  OR_EN0:1;          /* FIFO 0 Overrun interrupt enable */
         vuint32_t  OF_EN0:1;          /* FIFO 0 Threshold Overflow interrupt enable */
         vuint32_t  EMPTY_EN0:1;       /* FIFO 0 Empty interrupt enable */
         vuint32_t  FULL_EN0:1;        /* FIFO 0 Full interrupt enable */
      } B;
   } CTU_FCR_32B_tag;

   typedef union {   /* FIFO Threshold Register 1 */
      vuint32_t R;
      struct {
         vuint32_t  TH3:8;             /* FIFO 3 Threshold */
         vuint32_t  TH2:8;             /* FIFO 2 Threshold */
         vuint32_t  TH1:8;             /* FIFO 1 Threshold */
         vuint32_t  TH0:8;             /* FIFO 0 Threshold */
      } B;
   } CTU_FTH1_32B_tag;

   typedef union {   /* FIFO Threshold Register */
      vuint32_t R;
      struct {
         vuint32_t  TH3:8;             /* FIFO 3 Threshold */
         vuint32_t  TH2:8;             /* FIFO 2 Threshold */
         vuint32_t  TH1:8;             /* FIFO 1 Threshold */
         vuint32_t  TH0:8;             /* FIFO 0 Threshold */
      } B;
   } CTU_FTH_32B_tag;

   typedef union {   /* FIFO Status Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  OR3:1;             /* FIFO 3 Overrun interrupt flag */
         vuint32_t  OF3:1;             /* FIFO 3 Threshold Overflow interrupt flag */
         vuint32_t  EMP3:1;            /* FIFO 3 Empty interrupt flag */
         vuint32_t  FULL3:1;           /* FIFO 3 Full interrupt flag */
         vuint32_t  OR2:1;             /* FIFO 2 Overrun interrupt flag */
         vuint32_t  OF2:1;             /* FIFO 2 Threshold Overflow interrupt flag */
         vuint32_t  EMP2:1;            /* FIFO 2 Empty interrupt flag */
         vuint32_t  FULL2:1;           /* FIFO 2 Full interrupt flag */
         vuint32_t  OR1:1;             /* FIFO 1 Overrun interrupt flag */
         vuint32_t  OF1:1;             /* FIFO 1 Threshold Overflow interrupt flag */
         vuint32_t  EMP1:1;            /* FIFO 1 Empty interrupt flag */
         vuint32_t  FULL1:1;           /* FIFO 1 Full interrupt flag */
         vuint32_t  OR0:1;             /* FIFO 0 Overrun interrupt flag */
         vuint32_t  OF0:1;             /* FIFO 0 Threshold Overflow interrupt flag */
         vuint32_t  EMP0:1;            /* FIFO 0 Empty interrupt flag */
         vuint32_t  FULL0:1;           /* FIFO 0 Full interrupt flag */
      } B;
   } CTU_FST_32B_tag;


   /* Register layout for all registers FR ... */

   typedef union {   /* FIFO Right Aligned register */
      vuint32_t R;
      struct {
         vuint32_t:11;
         vuint32_t  ADC:1;             /* ADC that supplied DATA 1=A,0=B */
         vuint32_t  N_CH:4;            /* Number of the channel that DATA field corresponds to */
         vuint32_t:4;
         vuint32_t  DATA:12;           /* Data of stored channel */
      } B;
   } CTU_FR_32B_tag;


   /* Register layout for all registers FL ... */

   typedef union {   /* FIFO Left Aligned register */
      vuint32_t R;
      struct {
         vuint32_t:11;
         vuint32_t  ADC:1;             /* ADC that supplied DATA 1=A,0=B */
         vuint32_t  N_CH:4;            /* Number of the channel that DATA field corresponds to */
         vuint32_t:1;
         vuint32_t  LA_DATA:12;        /* Data of stored channel (left aligned) */
         vuint32_t:3;
      } B;
   } CTU_FL_32B_tag;

   typedef union {   /* CTU Error Flag Register */
      vuint16_t R;
      struct {
         vuint16_t:4;
         vuint16_t  ET_OE:1;           /* External Trigger generation Overrun Error */
         vuint16_t  ERRCMP:1;          /* TGS Counter have reached TGSCCR value */
         vuint16_t  T4_OE:1;           /* Timer 4 generation Overrun Error */
         vuint16_t  T3_OE:1;           /* Timer 3 generation Overrun Error */
         vuint16_t  T2_OE:1;           /* Timer 2 generation Overrun Error */
         vuint16_t  T1_OE:1;           /* Timer 1 generation Overrun Error */
         vuint16_t  ADC_OE:1;          /* ADC command generation Overrun Error */
         vuint16_t  TGS_OSM:1;         /* TGS Overrun in Sequential Mode */
         vuint16_t  MRS_O:1;           /* Master Reload Signal Overrun */
         vuint16_t  ICE:1;             /* Invalid Command Error */
         vuint16_t  SM_TO:1;           /* Trigger Overrun in TGS Sequential Mode */
         vuint16_t  MRS_RE:1;          /* Master Reload Signal Reload Error */
      } B;
   } CTU_EFR_16B_tag;

   typedef union {   /* CTU Interrupt Flag Register */
      vuint16_t R;
      struct {
         vuint16_t:4;
         vuint16_t  SERR_B:1;          /* Slice time OK */
         vuint16_t  SERR_A:1;          /* Slice time OK */
         vuint16_t  ADC_I:1;           /* ADC Command Interrupt Flag */
         vuint16_t  T7_I:1;            /* Trigger 7 Interrupt Flag */
         vuint16_t  T6_I:1;            /* Trigger 6 Interrupt Flag */
         vuint16_t  T5_I:1;            /* Trigger 5 Interrupt Flag */
         vuint16_t  T4_I:1;            /* Trigger 4 Interrupt Flag */
         vuint16_t  T3_I:1;            /* Trigger 3 Interrupt Flag */
         vuint16_t  T2_I:1;            /* Trigger 2 Interrupt Flag */
         vuint16_t  T1_I:1;            /* Trigger 1 Interrupt Flag */
         vuint16_t  T0_I:1;            /* Trigger 0 Interrupt Flag */
         vuint16_t  MRS_I:1;           /* Master Reload Signal Interrupt Flag */
      } B;
   } CTU_IFR_16B_tag;

   typedef union {   /* Interrupt/DMA Register */
      vuint16_t R;
      struct {
         vuint16_t  T7_IE:1;           /* Trigger 7 Interrupt Enable */
         vuint16_t  T6_IE:1;           /* Trigger 6 Interrupt Enable */
         vuint16_t  T5_IE:1;           /* Trigger 5 Interrupt Enable */
         vuint16_t  T4_IE:1;           /* Trigger 4 Interrupt Enable */
         vuint16_t  T3_IE:1;           /* Trigger 3 Interrupt Enable */
         vuint16_t  T2_IE:1;           /* Trigger 2 Interrupt Enable */
         vuint16_t  T1_IE:1;           /* Trigger 1 Interrupt Enable */
         vuint16_t  T0_IE:1;           /* Trigger 0 Interrupt Enable */
         vuint16_t:2;
         vuint16_t  SAF_CNT_B_EN:1;    /* Conversion time check counter B enabled */
         vuint16_t  SAF_CNT_A_EN:1;    /* Conversion time check counter A enabled */
         vuint16_t  DMA_DE:1;          /* DMA Done => GRE bit write */
         vuint16_t  MRS_DMAE:1;        /* DMA Transfer Enable */
         vuint16_t  MRS_IE:1;          /* MRS Interrupt Enable */
         vuint16_t  IEE:1;             /* Interrupt Error Enable */
      } B;
   } CTU_IR_16B_tag;

   typedef union {   /* Control ON Time Register */
      vuint16_t R;
      struct {
         vuint16_t:8;
         vuint16_t  COTGT:8;           /* Control On-Time and Guard Time */
      } B;
   } CTU_COTR_16B_tag;

   typedef union {   /* CTU Control Register */
      vuint16_t R;
      struct {
         vuint16_t  T7_SG:1;           /* Trigger 7 Software Generated */
         vuint16_t  T6_SG:1;           /* Trigger 6 Software Generated */
         vuint16_t  T5_SG:1;           /* Trigger 5 Software Generated */
         vuint16_t  T4_SG:1;           /* Trigger 4 Software Generated */
         vuint16_t  T3_SG:1;           /* Trigger 3 Software Generated */
         vuint16_t  T2_SG:1;           /* Trigger 2 Software Generated */
         vuint16_t  T1_SG:1;           /* Trigger 1 Software Generated */
         vuint16_t  T0_SG:1;           /* Trigger 0 Software Generated */
         vuint16_t  CTU_ADC_R:1;       /* CTU ADC State Machine Reset */
         vuint16_t  CTU_ODIS:1;        /* CTU Output Disable */
         vuint16_t  DFE:1;             /* Digital Filter Enable */
         vuint16_t  CGRE:1;            /* Clear GRE */
         vuint16_t  FGRE:1;            /* GRE Flag */
         vuint16_t  MRS_SG:1;          /* MRS Software Generated */
         vuint16_t  GRE:1;             /* General Reload Enable */
         vuint16_t  TGSISR_RE:1;       /* TGS Input Selection Register Reload Enable */
      } B;
   } CTU_CR_16B_tag;

   typedef union {   /* Digital Filter Register */
      vuint16_t R;
      struct {
         vuint16_t:8;
         vuint16_t  FILTER_N:8;        /* Digital Filter Value */
      } B;
   } CTU_DFR_16B_tag;

   typedef union {   /* Expected Value A Register */
      vuint16_t R;
   } CTU_EXP_A_16B_tag;

   typedef union {   /* Expected Value B Register */
      vuint16_t R;
   } CTU_EXP_B_16B_tag;

   typedef union {   /* Counter Range Register */
      vuint16_t R;
      struct {
         vuint16_t:8;
         vuint16_t  CNTRNG:8;          /* Counter Range Mask */
      } B;
   } CTU_CNTRNGR_16B_tag;


   typedef struct CTU_struct_tag {

               /* CTU Trigger Generator Subunit Input Selection register */
      CTU_TGSISR_32B_tag TGSISR;           /* offset: 0x0000 size: 32 bit */
                       /* CTU Trigger Generator Subunit Control Register */
      CTU_TGSCR_16B_tag TGSCR;             /* offset: 0x0004 size: 16 bit */
      union {
                                           /* Trigger n Compare Register */
         CTU_TCR_16B_tag TCR[8];           /* offset: 0x0006  (0x0002 x 8) */

         struct {
                                           /* Trigger n Compare Register */
            CTU_TCR_16B_tag T0CR;          /* offset: 0x0006 size: 16 bit */
            CTU_TCR_16B_tag T1CR;          /* offset: 0x0008 size: 16 bit */
            CTU_TCR_16B_tag T2CR;          /* offset: 0x000A size: 16 bit */
            CTU_TCR_16B_tag T3CR;          /* offset: 0x000C size: 16 bit */
            CTU_TCR_16B_tag T4CR;          /* offset: 0x000E size: 16 bit */
            CTU_TCR_16B_tag T5CR;          /* offset: 0x0010 size: 16 bit */
            CTU_TCR_16B_tag T6CR;          /* offset: 0x0012 size: 16 bit */
            CTU_TCR_16B_tag T7CR;          /* offset: 0x0014 size: 16 bit */
         };

      };
                                         /* TGS Counter Compare Register */
      CTU_TGSCCR_16B_tag TGSCCR;           /* offset: 0x0016 size: 16 bit */
                                          /* TGS Counter Reload Register */
      CTU_TGSCRR_16B_tag TGSCRR;           /* offset: 0x0018 size: 16 bit */
      int8_t CTU_reserved_001A[2];
                                     /* Commands List Control Register 1 */
      CTU_CLCR1_32B_tag CLCR1;             /* offset: 0x001C size: 32 bit */
                                     /* Commands List Control Register 2 */
      CTU_CLCR2_32B_tag CLCR2;             /* offset: 0x0020 size: 32 bit */
                                   /* Trigger Handler Control Register 1 */
      CTU_THCR1_32B_tag THCR1;             /* offset: 0x0024 size: 32 bit */
                                   /* Trigger Handler Control Register 2 */
      CTU_THCR2_32B_tag THCR2;             /* offset: 0x0028 size: 32 bit */
      union {
                       /* Command List Register - single conversion mode */
         CTU_CLR_SCM_16B_tag CLR_SCM[24];  /* offset: 0x002C  (0x0002 x 24) */

                         /* Command List Register - dual Conversion Mode */
         CTU_CLR_DCM_16B_tag CLR_DCM[24];  /* offset: 0x002C  (0x0002 x 24) */

                             /* Command List Register. View: BIT13, BIT9 */
         CTU_CLR_16B_tag CLR[24];          /* offset: 0x002C  (0x0002 x 24) */

         struct {
                       /* Command List Register - single conversion mode */
            CTU_CLR_SCM_16B_tag CLR_SCM1;  /* offset: 0x002C size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM2;  /* offset: 0x002E size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM3;  /* offset: 0x0030 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM4;  /* offset: 0x0032 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM5;  /* offset: 0x0034 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM6;  /* offset: 0x0036 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM7;  /* offset: 0x0038 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM8;  /* offset: 0x003A size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM9;  /* offset: 0x003C size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM10;  /* offset: 0x003E size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM11;  /* offset: 0x0040 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM12;  /* offset: 0x0042 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM13;  /* offset: 0x0044 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM14;  /* offset: 0x0046 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM15;  /* offset: 0x0048 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM16;  /* offset: 0x004A size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM17;  /* offset: 0x004C size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM18;  /* offset: 0x004E size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM19;  /* offset: 0x0050 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM20;  /* offset: 0x0052 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM21;  /* offset: 0x0054 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM22;  /* offset: 0x0056 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM23;  /* offset: 0x0058 size: 16 bit */
            CTU_CLR_SCM_16B_tag CLR_SCM24;  /* offset: 0x005A size: 16 bit */
         };

         struct {
                         /* Command List Register - dual Conversion Mode */
            CTU_CLR_DCM_16B_tag CLR_DCM1;  /* offset: 0x002C size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM2;  /* offset: 0x002E size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM3;  /* offset: 0x0030 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM4;  /* offset: 0x0032 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM5;  /* offset: 0x0034 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM6;  /* offset: 0x0036 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM7;  /* offset: 0x0038 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM8;  /* offset: 0x003A size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM9;  /* offset: 0x003C size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM10;  /* offset: 0x003E size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM11;  /* offset: 0x0040 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM12;  /* offset: 0x0042 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM13;  /* offset: 0x0044 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM14;  /* offset: 0x0046 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM15;  /* offset: 0x0048 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM16;  /* offset: 0x004A size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM17;  /* offset: 0x004C size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM18;  /* offset: 0x004E size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM19;  /* offset: 0x0050 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM20;  /* offset: 0x0052 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM21;  /* offset: 0x0054 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM22;  /* offset: 0x0056 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM23;  /* offset: 0x0058 size: 16 bit */
            CTU_CLR_DCM_16B_tag CLR_DCM24;  /* offset: 0x005A size: 16 bit */
         };

         struct {
                             /* Command List Register. View: BIT13, BIT9 */
            CTU_CLR_16B_tag CLR1;          /* offset: 0x002C size: 16 bit */
            CTU_CLR_16B_tag CLR2;          /* offset: 0x002E size: 16 bit */
            CTU_CLR_16B_tag CLR3;          /* offset: 0x0030 size: 16 bit */
            CTU_CLR_16B_tag CLR4;          /* offset: 0x0032 size: 16 bit */
            CTU_CLR_16B_tag CLR5;          /* offset: 0x0034 size: 16 bit */
            CTU_CLR_16B_tag CLR6;          /* offset: 0x0036 size: 16 bit */
            CTU_CLR_16B_tag CLR7;          /* offset: 0x0038 size: 16 bit */
            CTU_CLR_16B_tag CLR8;          /* offset: 0x003A size: 16 bit */
            CTU_CLR_16B_tag CLR9;          /* offset: 0x003C size: 16 bit */
            CTU_CLR_16B_tag CLR10;         /* offset: 0x003E size: 16 bit */
            CTU_CLR_16B_tag CLR11;         /* offset: 0x0040 size: 16 bit */
            CTU_CLR_16B_tag CLR12;         /* offset: 0x0042 size: 16 bit */
            CTU_CLR_16B_tag CLR13;         /* offset: 0x0044 size: 16 bit */
            CTU_CLR_16B_tag CLR14;         /* offset: 0x0046 size: 16 bit */
            CTU_CLR_16B_tag CLR15;         /* offset: 0x0048 size: 16 bit */
            CTU_CLR_16B_tag CLR16;         /* offset: 0x004A size: 16 bit */
            CTU_CLR_16B_tag CLR17;         /* offset: 0x004C size: 16 bit */
            CTU_CLR_16B_tag CLR18;         /* offset: 0x004E size: 16 bit */
            CTU_CLR_16B_tag CLR19;         /* offset: 0x0050 size: 16 bit */
            CTU_CLR_16B_tag CLR20;         /* offset: 0x0052 size: 16 bit */
            CTU_CLR_16B_tag CLR21;         /* offset: 0x0054 size: 16 bit */
            CTU_CLR_16B_tag CLR22;         /* offset: 0x0056 size: 16 bit */
            CTU_CLR_16B_tag CLR23;         /* offset: 0x0058 size: 16 bit */
            CTU_CLR_16B_tag CLR24;         /* offset: 0x005A size: 16 bit */
         };

      };
      int8_t CTU_reserved_005C[16];
                                            /* FIFO DMA Control Register */
      CTU_FDCR_16B_tag FDCR;               /* offset: 0x006C size: 16 bit */
      int8_t CTU_reserved_006E[2];
                                                /* FIFO Control Register */
      CTU_FCR_32B_tag FCR;                 /* offset: 0x0070 size: 32 bit */
      union {
                                              /* FIFO Threshold Register */
         CTU_FTH_32B_tag FTH;              /* offset: 0x0074 size: 32 bit */

                                            /* FIFO Threshold Register 1 */
         CTU_FTH1_32B_tag FTH1;            /* offset: 0x0074 size: 32 bit */

      };
      int8_t CTU_reserved_0078[4];
                                                 /* FIFO Status Register */
      CTU_FST_32B_tag FST;                 /* offset: 0x007C size: 32 bit */
      union {
                                          /* FIFO Right Aligned register */
         CTU_FR_32B_tag FR[4];             /* offset: 0x0080  (0x0004 x 4) */

         struct {
                                          /* FIFO Right Aligned register */
            CTU_FR_32B_tag FR0;            /* offset: 0x0080 size: 32 bit */
            CTU_FR_32B_tag FR1;            /* offset: 0x0084 size: 32 bit */
            CTU_FR_32B_tag FR2;            /* offset: 0x0088 size: 32 bit */
            CTU_FR_32B_tag FR3;            /* offset: 0x008C size: 32 bit */
         };

      };
      int8_t CTU_reserved_0090[16];
      union {
                                           /* FIFO Left Aligned register */
         CTU_FL_32B_tag FL[4];             /* offset: 0x00A0  (0x0004 x 4) */

         struct {
                                           /* FIFO Left Aligned register */
            CTU_FL_32B_tag FL0;            /* offset: 0x00A0 size: 32 bit */
            CTU_FL_32B_tag FL1;            /* offset: 0x00A4 size: 32 bit */
            CTU_FL_32B_tag FL2;            /* offset: 0x00A8 size: 32 bit */
            CTU_FL_32B_tag FL3;            /* offset: 0x00AC size: 32 bit */
         };

      };
      int8_t CTU_reserved_00B0[16];
                                              /* CTU Error Flag Register */
      CTU_EFR_16B_tag EFR;                 /* offset: 0x00C0 size: 16 bit */
                                          /* CTU Interrupt Flag Register */
      CTU_IFR_16B_tag IFR;                 /* offset: 0x00C2 size: 16 bit */
                                               /* Interrupt/DMA Register */
      CTU_IR_16B_tag IR;                   /* offset: 0x00C4 size: 16 bit */
                                             /* Control ON Time Register */
      CTU_COTR_16B_tag COTR;               /* offset: 0x00C6 size: 16 bit */
                                                 /* CTU Control Register */
      CTU_CR_16B_tag CR;                   /* offset: 0x00C8 size: 16 bit */
                                              /* Digital Filter Register */
      CTU_DFR_16B_tag DFR;                 /* offset: 0x00CA size: 16 bit */
                                            /* Expected Value A Register */
      CTU_EXP_A_16B_tag EXP_A;             /* offset: 0x00CC size: 16 bit */
                                            /* Expected Value B Register */
      CTU_EXP_B_16B_tag EXP_B;             /* offset: 0x00CE size: 16 bit */
                                               /* Counter Range Register */
      CTU_CNTRNGR_16B_tag CNTRNGR;         /* offset: 0x00D0 size: 16 bit */
      int8_t CTU_reserved_00D2[16174];

   } CTU_tag;


#define CTU_BASEADDRESS 0xFFE0C000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define CTU   (*(volatile CTU_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE0C000UL))



/****************************************************************/
/*                                                              */
/* Module: eTIMER0  */
/*                                                              */
/****************************************************************/


   /* Register layout for all registers COMP1 ... */

   typedef union {   /* Compare Register 1 */
      vuint16_t R;
   } eTIMER0_COMP1_16B_tag;


   /* Register layout for all registers COMP2 ... */

   typedef union {   /* Compare Register 2 */
      vuint16_t R;
   } eTIMER0_COMP2_16B_tag;


   /* Register layout for all registers CAPT1 ... */

   typedef union {   /* Capture Register 1 */
      vuint16_t R;
   } eTIMER0_CAPT1_16B_tag;


   /* Register layout for all registers CAPT2 ... */

   typedef union {   /* Capture Register 2 */
      vuint16_t R;
   } eTIMER0_CAPT2_16B_tag;


   /* Register layout for all registers LOAD ... */

   typedef union {   /* Load Register */
      vuint16_t R;
   } eTIMER0_LOAD_16B_tag;


   /* Register layout for all registers HOLD ... */

   typedef union {   /* Hold Register */
      vuint16_t R;
   } eTIMER0_HOLD_16B_tag;


   /* Register layout for all registers CNTR ... */

   typedef union {   /* Counter Register */
      vuint16_t R;
   } eTIMER0_CNTR_16B_tag;


   /* Register layout for all registers CTRL1 ... */

   typedef union {   /* Control Register */
      vuint16_t R;
      struct {
         vuint16_t  CNTMODE:3;         /* Count Mode */
         vuint16_t  PRISRC:5;          /* Primary Count Source */
         vuint16_t  ONCE:1;            /* Count Once */
         vuint16_t  LENGTH:1;          /* Count Length */
         vuint16_t  DIR:1;             /* Count Direction */
         vuint16_t  SECSRC:5;          /* Secondary Count Source */
      } B;
   } eTIMER0_CTRL1_16B_tag;


   /* Register layout for all registers CTRL2 ... */

   typedef union {   /* Control Register 2 */
      vuint16_t R;
      struct {
         vuint16_t  OEN:1;             /* Output Enable */
         vuint16_t  RDNT:1;            /* Redundant Channel Enable */
         vuint16_t  INPUT:1;           /* External Input Signal */
         vuint16_t  VAL:1;             /* Forced OFLAG Value */
         vuint16_t  FORCE:1;           /* Force the OFLAG output */
         vuint16_t  COFRC:1;           /* Co-channel OFLAG Force */
         vuint16_t  COINIT:2;          /* Co-channel Initialization */
         vuint16_t  SIPS:1;            /* Secondary Source Input Polarity Select */
         vuint16_t  PIPS:1;            /* Primary Source Input Polarity Select */
         vuint16_t  OPS:1;             /* Output Polarity Select */
         vuint16_t  MSTR:1;            /* Master Mode */
         vuint16_t  OUTMODE:4;         /* Output Mode */
      } B;
   } eTIMER0_CTRL2_16B_tag;


   /* Register layout for all registers CTRL3 ... */

   typedef union {   /* Control Register 3 */
      vuint16_t R;
      struct {
         vuint16_t  STPEN:1;           /* Stop Action Enable */
         vuint16_t  ROC:2;             /* Reload On Capture */
         vuint16_t:5;
         vuint16_t  C2FCNT:3;          /* CAPT2 FIFO Word Count */
         vuint16_t  C1FCNT:3;          /* CAPT1 FIFO Word Count */
         vuint16_t  DBGEN:2;           /* Debug Actions Enable */
      } B;
   } eTIMER0_CTRL3_16B_tag;


   /* Register layout for all registers STS ... */

   typedef union {   /* Status Register */
      vuint16_t R;
      struct {
         vuint16_t:6;
         vuint16_t  WDF:1;             /* Watchdog Time-out Flag */
         vuint16_t  RCF:1;             /* Redundant Channel Flag */
         vuint16_t  ICF2:1;            /* Input Capture 2 Flag */
         vuint16_t  ICF1:1;            /* Input Capture 1 Flag */
         vuint16_t  IEHF:1;            /* Input Edge High Flag */
         vuint16_t  IELF:1;            /* Input Edge Low Flag */
         vuint16_t  TOF:1;             /* Timer Overflow Flag */
         vuint16_t  TCF2:1;            /* Timer Compare 2 Flag */
         vuint16_t  TCF1:1;            /* Timer Compare 1 Flag */
         vuint16_t  TCF:1;             /* Timer Compare Flag */
      } B;
   } eTIMER0_STS_16B_tag;


   /* Register layout for all registers INTDMA ... */

   typedef union {   /* Interrupt and DMA Enable Register */
      vuint16_t R;
      struct {
         vuint16_t  ICF2DE:1;          /* Input Capture 2 Flag DMA Enable */
         vuint16_t  ICF1DE:1;          /* Input Capture 1 Flag DMA Enable */
         vuint16_t  CMPLD2DE:1;        /* Comparator Load Register 2 Flag DMA Enable */
         vuint16_t  CMPLD1DE:1;        /* Comparator Load Register 1 Flag DMA Enable */
         vuint16_t:2;
         vuint16_t  WDFIE:1;           /* Watchdog Flag Interrupt Enable */
         vuint16_t  RCFIE:1;           /* Redundant Channel Flag Interrupt Enable */
         vuint16_t  ICF2IE:1;          /* Input Capture 2 Flag Interrupt Enable */
         vuint16_t  ICF1IE:1;          /* Input Capture 1 Flag Interrupt Enable */
         vuint16_t  IEHFIE:1;          /* Input Edge High Flag Interrupt Enable */
         vuint16_t  IELFIE:1;          /* Input Edge Low Flag Interrupt Enable */
         vuint16_t  TOFIE:1;           /* Timer Overflow Flag Interrupt Enable */
         vuint16_t  TCF2IE:1;          /* Timer Compare 2 Flag Interrupt Enable */
         vuint16_t  TCF1IE:1;          /* Timer Compare 1 Flag Interrupt Enable */
         vuint16_t  TCFIE:1;           /* Timer Compare Flag Interrupt Enable */
      } B;
   } eTIMER0_INTDMA_16B_tag;


   /* Register layout for all registers CMPLD1 ... */

   typedef union {   /* Comparator Load Register 1 */
      vuint16_t R;
   } eTIMER0_CMPLD1_16B_tag;


   /* Register layout for all registers CMPLD2 ... */

   typedef union {   /* Comparator Load Register 2 */
      vuint16_t R;
   } eTIMER0_CMPLD2_16B_tag;


   /* Register layout for all registers CCCTRL ... */

   typedef union {   /* Compare and Capture Control Register */
      vuint16_t R;
      struct {
         vuint16_t  CLC2:3;            /* Compare Load Control 2 */
         vuint16_t  CLC1:3;            /* Compare Load Control 1 */
         vuint16_t  CMPMODE:2;         /* Compare Mode */
         vuint16_t  CPT2MODE:2;        /* Capture 2 Mode Control */
         vuint16_t  CPT1MODE:2;        /* Capture 1 Mode Control */
         vuint16_t  CFWM:2;            /* Capture FIFO Water Mark */
         vuint16_t  ONESHOT:1;         /* One Shot Capture Mode */
         vuint16_t  ARM:1;             /* Arm Capture */
      } B;
   } eTIMER0_CCCTRL_16B_tag;


   /* Register layout for all registers FILT ... */

   typedef union {   /* Input Filter Register */
      vuint16_t R;
      struct {
         vuint16_t:5;
         vuint16_t  FILT_CNT:3;        /* Input Filter Sample Count */
         vuint16_t  FILT_PER:8;        /* Input Filter Sample Period */
      } B;
   } eTIMER0_FILT_16B_tag;

   typedef union {   /* Watchdog Time-out Register */
      vuint16_t R;
   } eTIMER0_WDTOL_16B_tag;

   typedef union {   /* Watchdog Time-out Register */
      vuint16_t R;
   } eTIMER0_WDTOH_16B_tag;

   typedef union {   /* Channel Enable Register */
      vuint16_t R;
      struct {
         vuint16_t:10;
         vuint16_t  ENBL5:1;           /* Enable for timer channel #5 */
         vuint16_t  ENBL4:1;           /* Enable for timer channel #4 */
         vuint16_t  ENBL3:1;           /* Enable for timer channel #3 */
         vuint16_t  ENBL2:1;           /* Enable for timer channel #2 */
         vuint16_t  ENBL1:1;           /* Enable for timer channel #1 */
         vuint16_t  ENBL0:1;           /* Enable for timer channel #0 */
      } B;
   } eTIMER0_ENBL_16B_tag;

   typedef union {   /* DMA Request 0 Select Registers */
      vuint16_t R;
      struct {
         vuint16_t  DREQ0_EN:1;        /* DMA Request Enable */
         vuint16_t:10;
         vuint16_t  DREQ0V:5;          /* DMA Request Select */
      } B;
   } eTIMER0_DREQ0_16B_tag;

   typedef union {   /* DMA Request 1 Select Registers */
      vuint16_t R;
      struct {
         vuint16_t  DREQ1_EN:1;        /* DMA Request Enable */
         vuint16_t:10;
         vuint16_t  DREQ1V:5;          /* DMA Request Select */
      } B;
   } eTIMER0_DREQ1_16B_tag;


   typedef struct eTIMER0_CHANNEL_struct_tag {

                                                   /* Compare Register 1 */
      eTIMER0_COMP1_16B_tag COMP1;         /* relative offset: 0x0000 */
                                                   /* Compare Register 2 */
      eTIMER0_COMP2_16B_tag COMP2;         /* relative offset: 0x0002 */
                                                   /* Capture Register 1 */
      eTIMER0_CAPT1_16B_tag CAPT1;         /* relative offset: 0x0004 */
                                                   /* Capture Register 2 */
      eTIMER0_CAPT2_16B_tag CAPT2;         /* relative offset: 0x0006 */
                                                        /* Load Register */
      eTIMER0_LOAD_16B_tag LOAD;           /* relative offset: 0x0008 */
                                                        /* Hold Register */
      eTIMER0_HOLD_16B_tag HOLD;           /* relative offset: 0x000A */
                                                     /* Counter Register */
      eTIMER0_CNTR_16B_tag CNTR;           /* relative offset: 0x000C */
                                                     /* Control Register */
      eTIMER0_CTRL1_16B_tag CTRL1;         /* relative offset: 0x000E */
                                                   /* Control Register 2 */
      eTIMER0_CTRL2_16B_tag CTRL2;         /* relative offset: 0x0010 */
                                                   /* Control Register 3 */
      eTIMER0_CTRL3_16B_tag CTRL3;         /* relative offset: 0x0012 */
                                                      /* Status Register */
      eTIMER0_STS_16B_tag STS;             /* relative offset: 0x0014 */
                                    /* Interrupt and DMA Enable Register */
      eTIMER0_INTDMA_16B_tag INTDMA;       /* relative offset: 0x0016 */
                                           /* Comparator Load Register 1 */
      eTIMER0_CMPLD1_16B_tag CMPLD1;       /* relative offset: 0x0018 */
                                           /* Comparator Load Register 2 */
      eTIMER0_CMPLD2_16B_tag CMPLD2;       /* relative offset: 0x001A */
                                 /* Compare and Capture Control Register */
      eTIMER0_CCCTRL_16B_tag CCCTRL;       /* relative offset: 0x001C */
                                                /* Input Filter Register */
      eTIMER0_FILT_16B_tag FILT;           /* relative offset: 0x001E */

   } eTIMER0_CHANNEL_tag;



   typedef struct eTIMER0_struct_tag {

      union {
                                                /*  Register set CHANNEL */
         eTIMER0_CHANNEL_tag CHANNEL[6];   /* offset: 0x0000  (0x0020 x 6) */

         struct {
                                                   /* Compare Register 1 */
            eTIMER0_COMP1_16B_tag COMP10;  /* offset: 0x0000 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER0_COMP2_16B_tag COMP20;  /* offset: 0x0002 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER0_CAPT1_16B_tag CAPT10;  /* offset: 0x0004 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER0_CAPT2_16B_tag CAPT20;  /* offset: 0x0006 size: 16 bit */
                                                        /* Load Register */
            eTIMER0_LOAD_16B_tag LOAD0;    /* offset: 0x0008 size: 16 bit */
                                                        /* Hold Register */
            eTIMER0_HOLD_16B_tag HOLD0;    /* offset: 0x000A size: 16 bit */
                                                     /* Counter Register */
            eTIMER0_CNTR_16B_tag CNTR0;    /* offset: 0x000C size: 16 bit */
                                                     /* Control Register */
            eTIMER0_CTRL1_16B_tag CTRL10;  /* offset: 0x000E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER0_CTRL2_16B_tag CTRL20;  /* offset: 0x0010 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER0_CTRL3_16B_tag CTRL30;  /* offset: 0x0012 size: 16 bit */
                                                      /* Status Register */
            eTIMER0_STS_16B_tag STS0;      /* offset: 0x0014 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER0_INTDMA_16B_tag INTDMA0;  /* offset: 0x0016 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER0_CMPLD1_16B_tag CMPLD10;  /* offset: 0x0018 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER0_CMPLD2_16B_tag CMPLD20;  /* offset: 0x001A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER0_CCCTRL_16B_tag CCCTRL0;  /* offset: 0x001C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER0_FILT_16B_tag FILT0;    /* offset: 0x001E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER0_COMP1_16B_tag COMP11;  /* offset: 0x0020 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER0_COMP2_16B_tag COMP21;  /* offset: 0x0022 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER0_CAPT1_16B_tag CAPT11;  /* offset: 0x0024 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER0_CAPT2_16B_tag CAPT21;  /* offset: 0x0026 size: 16 bit */
                                                        /* Load Register */
            eTIMER0_LOAD_16B_tag LOAD1;    /* offset: 0x0028 size: 16 bit */
                                                        /* Hold Register */
            eTIMER0_HOLD_16B_tag HOLD1;    /* offset: 0x002A size: 16 bit */
                                                     /* Counter Register */
            eTIMER0_CNTR_16B_tag CNTR1;    /* offset: 0x002C size: 16 bit */
                                                     /* Control Register */
            eTIMER0_CTRL1_16B_tag CTRL11;  /* offset: 0x002E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER0_CTRL2_16B_tag CTRL21;  /* offset: 0x0030 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER0_CTRL3_16B_tag CTRL31;  /* offset: 0x0032 size: 16 bit */
                                                      /* Status Register */
            eTIMER0_STS_16B_tag STS1;      /* offset: 0x0034 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER0_INTDMA_16B_tag INTDMA1;  /* offset: 0x0036 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER0_CMPLD1_16B_tag CMPLD11;  /* offset: 0x0038 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER0_CMPLD2_16B_tag CMPLD21;  /* offset: 0x003A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER0_CCCTRL_16B_tag CCCTRL1;  /* offset: 0x003C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER0_FILT_16B_tag FILT1;    /* offset: 0x003E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER0_COMP1_16B_tag COMP12;  /* offset: 0x0040 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER0_COMP2_16B_tag COMP22;  /* offset: 0x0042 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER0_CAPT1_16B_tag CAPT12;  /* offset: 0x0044 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER0_CAPT2_16B_tag CAPT22;  /* offset: 0x0046 size: 16 bit */
                                                        /* Load Register */
            eTIMER0_LOAD_16B_tag LOAD2;    /* offset: 0x0048 size: 16 bit */
                                                        /* Hold Register */
            eTIMER0_HOLD_16B_tag HOLD2;    /* offset: 0x004A size: 16 bit */
                                                     /* Counter Register */
            eTIMER0_CNTR_16B_tag CNTR2;    /* offset: 0x004C size: 16 bit */
                                                     /* Control Register */
            eTIMER0_CTRL1_16B_tag CTRL12;  /* offset: 0x004E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER0_CTRL2_16B_tag CTRL22;  /* offset: 0x0050 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER0_CTRL3_16B_tag CTRL32;  /* offset: 0x0052 size: 16 bit */
                                                      /* Status Register */
            eTIMER0_STS_16B_tag STS2;      /* offset: 0x0054 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER0_INTDMA_16B_tag INTDMA2;  /* offset: 0x0056 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER0_CMPLD1_16B_tag CMPLD12;  /* offset: 0x0058 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER0_CMPLD2_16B_tag CMPLD22;  /* offset: 0x005A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER0_CCCTRL_16B_tag CCCTRL2;  /* offset: 0x005C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER0_FILT_16B_tag FILT2;    /* offset: 0x005E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER0_COMP1_16B_tag COMP13;  /* offset: 0x0060 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER0_COMP2_16B_tag COMP23;  /* offset: 0x0062 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER0_CAPT1_16B_tag CAPT13;  /* offset: 0x0064 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER0_CAPT2_16B_tag CAPT23;  /* offset: 0x0066 size: 16 bit */
                                                        /* Load Register */
            eTIMER0_LOAD_16B_tag LOAD3;    /* offset: 0x0068 size: 16 bit */
                                                        /* Hold Register */
            eTIMER0_HOLD_16B_tag HOLD3;    /* offset: 0x006A size: 16 bit */
                                                     /* Counter Register */
            eTIMER0_CNTR_16B_tag CNTR3;    /* offset: 0x006C size: 16 bit */
                                                     /* Control Register */
            eTIMER0_CTRL1_16B_tag CTRL13;  /* offset: 0x006E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER0_CTRL2_16B_tag CTRL23;  /* offset: 0x0070 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER0_CTRL3_16B_tag CTRL33;  /* offset: 0x0072 size: 16 bit */
                                                      /* Status Register */
            eTIMER0_STS_16B_tag STS3;      /* offset: 0x0074 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER0_INTDMA_16B_tag INTDMA3;  /* offset: 0x0076 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER0_CMPLD1_16B_tag CMPLD13;  /* offset: 0x0078 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER0_CMPLD2_16B_tag CMPLD23;  /* offset: 0x007A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER0_CCCTRL_16B_tag CCCTRL3;  /* offset: 0x007C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER0_FILT_16B_tag FILT3;    /* offset: 0x007E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER0_COMP1_16B_tag COMP14;  /* offset: 0x0080 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER0_COMP2_16B_tag COMP24;  /* offset: 0x0082 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER0_CAPT1_16B_tag CAPT14;  /* offset: 0x0084 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER0_CAPT2_16B_tag CAPT24;  /* offset: 0x0086 size: 16 bit */
                                                        /* Load Register */
            eTIMER0_LOAD_16B_tag LOAD4;    /* offset: 0x0088 size: 16 bit */
                                                        /* Hold Register */
            eTIMER0_HOLD_16B_tag HOLD4;    /* offset: 0x008A size: 16 bit */
                                                     /* Counter Register */
            eTIMER0_CNTR_16B_tag CNTR4;    /* offset: 0x008C size: 16 bit */
                                                     /* Control Register */
            eTIMER0_CTRL1_16B_tag CTRL14;  /* offset: 0x008E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER0_CTRL2_16B_tag CTRL24;  /* offset: 0x0090 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER0_CTRL3_16B_tag CTRL34;  /* offset: 0x0092 size: 16 bit */
                                                      /* Status Register */
            eTIMER0_STS_16B_tag STS4;      /* offset: 0x0094 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER0_INTDMA_16B_tag INTDMA4;  /* offset: 0x0096 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER0_CMPLD1_16B_tag CMPLD14;  /* offset: 0x0098 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER0_CMPLD2_16B_tag CMPLD24;  /* offset: 0x009A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER0_CCCTRL_16B_tag CCCTRL4;  /* offset: 0x009C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER0_FILT_16B_tag FILT4;    /* offset: 0x009E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER0_COMP1_16B_tag COMP15;  /* offset: 0x00A0 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER0_COMP2_16B_tag COMP25;  /* offset: 0x00A2 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER0_CAPT1_16B_tag CAPT15;  /* offset: 0x00A4 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER0_CAPT2_16B_tag CAPT25;  /* offset: 0x00A6 size: 16 bit */
                                                        /* Load Register */
            eTIMER0_LOAD_16B_tag LOAD5;    /* offset: 0x00A8 size: 16 bit */
                                                        /* Hold Register */
            eTIMER0_HOLD_16B_tag HOLD5;    /* offset: 0x00AA size: 16 bit */
                                                     /* Counter Register */
            eTIMER0_CNTR_16B_tag CNTR5;    /* offset: 0x00AC size: 16 bit */
                                                     /* Control Register */
            eTIMER0_CTRL1_16B_tag CTRL15;  /* offset: 0x00AE size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER0_CTRL2_16B_tag CTRL25;  /* offset: 0x00B0 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER0_CTRL3_16B_tag CTRL35;  /* offset: 0x00B2 size: 16 bit */
                                                      /* Status Register */
            eTIMER0_STS_16B_tag STS5;      /* offset: 0x00B4 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER0_INTDMA_16B_tag INTDMA5;  /* offset: 0x00B6 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER0_CMPLD1_16B_tag CMPLD15;  /* offset: 0x00B8 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER0_CMPLD2_16B_tag CMPLD25;  /* offset: 0x00BA size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER0_CCCTRL_16B_tag CCCTRL5;  /* offset: 0x00BC size: 16 bit */
                                                /* Input Filter Register */
            eTIMER0_FILT_16B_tag FILT5;    /* offset: 0x00BE size: 16 bit */
         };

      };
      int8_t eTIMER0_reserved_00C0[64];
                                           /* Watchdog Time-out Register */
      eTIMER0_WDTOL_16B_tag WDTOL;         /* offset: 0x0100 size: 16 bit */
                                           /* Watchdog Time-out Register */
      eTIMER0_WDTOH_16B_tag WDTOH;         /* offset: 0x0102 size: 16 bit */
      int8_t eTIMER0_reserved_0104[8];
                                              /* Channel Enable Register */
      eTIMER0_ENBL_16B_tag ENBL;           /* offset: 0x010C size: 16 bit */
      int8_t eTIMER0_reserved_010E[2];
                                       /* DMA Request 0 Select Registers */
      eTIMER0_DREQ0_16B_tag DREQ0;         /* offset: 0x0110 size: 16 bit */
                                       /* DMA Request 1 Select Registers */
      eTIMER0_DREQ1_16B_tag DREQ1;         /* offset: 0x0112 size: 16 bit */
      int8_t eTIMER0_reserved_0114[16108];

   } eTIMER0_tag;


#define eTIMER0_BASEADDRESS 0xFFE18000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define eTIMER0 (*(volatile eTIMER0_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE18000UL))



/****************************************************************/
/*                                                              */
/* Module: eTIMER1  */
/*                                                              */
/****************************************************************/


   /* Register layout for all registers COMP1 ... */

   typedef union {   /* Compare Register 1 */
      vuint16_t R;
   } eTIMER1_COMP1_16B_tag;


   /* Register layout for all registers COMP2 ... */

   typedef union {   /* Compare Register 2 */
      vuint16_t R;
   } eTIMER1_COMP2_16B_tag;


   /* Register layout for all registers CAPT1 ... */

   typedef union {   /* Capture Register 1 */
      vuint16_t R;
   } eTIMER1_CAPT1_16B_tag;


   /* Register layout for all registers CAPT2 ... */

   typedef union {   /* Capture Register 2 */
      vuint16_t R;
   } eTIMER1_CAPT2_16B_tag;


   /* Register layout for all registers LOAD ... */

   typedef union {   /* Load Register */
      vuint16_t R;
   } eTIMER1_LOAD_16B_tag;


   /* Register layout for all registers HOLD ... */

   typedef union {   /* Hold Register */
      vuint16_t R;
   } eTIMER1_HOLD_16B_tag;


   /* Register layout for all registers CNTR ... */

   typedef union {   /* Counter Register */
      vuint16_t R;
   } eTIMER1_CNTR_16B_tag;


   /* Register layout for all registers CTRL1 ... */

   typedef union {   /* Control Register */
      vuint16_t R;
      struct {
         vuint16_t  CNTMODE:3;         /* Count Mode */
         vuint16_t  PRISRC:5;          /* Primary Count Source */
         vuint16_t  ONCE:1;            /* Count Once */
         vuint16_t  LENGTH:1;          /* Count Length */
         vuint16_t  DIR:1;             /* Count Direction */
         vuint16_t  SECSRC:5;          /* Secondary Count Source */
      } B;
   } eTIMER1_CTRL1_16B_tag;


   /* Register layout for all registers CTRL2 ... */

   typedef union {   /* Control Register 2 */
      vuint16_t R;
      struct {
         vuint16_t  OEN:1;             /* Output Enable */
         vuint16_t  RDNT:1;            /* Redundant Channel Enable */
         vuint16_t  INPUT:1;           /* External Input Signal */
         vuint16_t  VAL:1;             /* Forced OFLAG Value */
         vuint16_t  FORCE:1;           /* Force the OFLAG output */
         vuint16_t  COFRC:1;           /* Co-channel OFLAG Force */
         vuint16_t  COINIT:2;          /* Co-channel Initialization */
         vuint16_t  SIPS:1;            /* Secondary Source Input Polarity Select */
         vuint16_t  PIPS:1;            /* Primary Source Input Polarity Select */
         vuint16_t  OPS:1;             /* Output Polarity Select */
         vuint16_t  MSTR:1;            /* Master Mode */
         vuint16_t  OUTMODE:4;         /* Output Mode */
      } B;
   } eTIMER1_CTRL2_16B_tag;


   /* Register layout for all registers CTRL3 ... */

   typedef union {   /* Control Register 3 */
      vuint16_t R;
      struct {
         vuint16_t  STPEN:1;           /* Stop Action Enable */
         vuint16_t  ROC:2;             /* Reload On Capture */
         vuint16_t:5;
         vuint16_t  C2FCNT:3;          /* CAPT2 FIFO Word Count */
         vuint16_t  C1FCNT:3;          /* CAPT1 FIFO Word Count */
         vuint16_t  DBGEN:2;           /* Debug Actions Enable */
      } B;
   } eTIMER1_CTRL3_16B_tag;


   /* Register layout for all registers STS ... */

   typedef union {   /* Status Register */
      vuint16_t R;
      struct {
         vuint16_t:6;
         vuint16_t  WDF:1;             /* Watchdog Time-out Flag */
         vuint16_t  RCF:1;             /* Redundant Channel Flag */
         vuint16_t  ICF2:1;            /* Input Capture 2 Flag */
         vuint16_t  ICF1:1;            /* Input Capture 1 Flag */
         vuint16_t  IEHF:1;            /* Input Edge High Flag */
         vuint16_t  IELF:1;            /* Input Edge Low Flag */
         vuint16_t  TOF:1;             /* Timer Overflow Flag */
         vuint16_t  TCF2:1;            /* Timer Compare 2 Flag */
         vuint16_t  TCF1:1;            /* Timer Compare 1 Flag */
         vuint16_t  TCF:1;             /* Timer Compare Flag */
      } B;
   } eTIMER1_STS_16B_tag;


   /* Register layout for all registers INTDMA ... */

   typedef union {   /* Interrupt and DMA Enable Register */
      vuint16_t R;
      struct {
         vuint16_t  ICF2DE:1;          /* Input Capture 2 Flag DMA Enable */
         vuint16_t  ICF1DE:1;          /* Input Capture 1 Flag DMA Enable */
         vuint16_t  CMPLD2DE:1;        /* Comparator Load Register 2 Flag DMA Enable */
         vuint16_t  CMPLD1DE:1;        /* Comparator Load Register 1 Flag DMA Enable */
         vuint16_t:2;
         vuint16_t  WDFIE:1;           /* Watchdog Flag Interrupt Enable */
         vuint16_t  RCFIE:1;           /* Redundant Channel Flag Interrupt Enable */
         vuint16_t  ICF2IE:1;          /* Input Capture 2 Flag Interrupt Enable */
         vuint16_t  ICF1IE:1;          /* Input Capture 1 Flag Interrupt Enable */
         vuint16_t  IEHFIE:1;          /* Input Edge High Flag Interrupt Enable */
         vuint16_t  IELFIE:1;          /* Input Edge Low Flag Interrupt Enable */
         vuint16_t  TOFIE:1;           /* Timer Overflow Flag Interrupt Enable */
         vuint16_t  TCF2IE:1;          /* Timer Compare 2 Flag Interrupt Enable */
         vuint16_t  TCF1IE:1;          /* Timer Compare 1 Flag Interrupt Enable */
         vuint16_t  TCFIE:1;           /* Timer Compare Flag Interrupt Enable */
      } B;
   } eTIMER1_INTDMA_16B_tag;


   /* Register layout for all registers CMPLD1 ... */

   typedef union {   /* Comparator Load Register 1 */
      vuint16_t R;
   } eTIMER1_CMPLD1_16B_tag;


   /* Register layout for all registers CMPLD2 ... */

   typedef union {   /* Comparator Load Register 2 */
      vuint16_t R;
   } eTIMER1_CMPLD2_16B_tag;


   /* Register layout for all registers CCCTRL ... */

   typedef union {   /* Compare and Capture Control Register */
      vuint16_t R;
      struct {
         vuint16_t  CLC2:3;            /* Compare Load Control 2 */
         vuint16_t  CLC1:3;            /* Compare Load Control 1 */
         vuint16_t  CMPMODE:2;         /* Compare Mode */
         vuint16_t  CPT2MODE:2;        /* Capture 2 Mode Control */
         vuint16_t  CPT1MODE:2;        /* Capture 1 Mode Control */
         vuint16_t  CFWM:2;            /* Capture FIFO Water Mark */
         vuint16_t  ONESHOT:1;         /* One Shot Capture Mode */
         vuint16_t  ARM:1;             /* Arm Capture */
      } B;
   } eTIMER1_CCCTRL_16B_tag;


   /* Register layout for all registers FILT ... */

   typedef union {   /* Input Filter Register */
      vuint16_t R;
      struct {
         vuint16_t:5;
         vuint16_t  FILT_CNT:3;        /* Input Filter Sample Count */
         vuint16_t  FILT_PER:8;        /* Input Filter Sample Period */
      } B;
   } eTIMER1_FILT_16B_tag;

   typedef union {   /* Channel Enable Register */
      vuint16_t R;
      struct {
         vuint16_t:10;
         vuint16_t  ENBL5:1;           /* Enable for timer channel #5 */
         vuint16_t  ENBL4:1;           /* Enable for timer channel #4 */
         vuint16_t  ENBL3:1;           /* Enable for timer channel #3 */
         vuint16_t  ENBL2:1;           /* Enable for timer channel #2 */
         vuint16_t  ENBL1:1;           /* Enable for timer channel #1 */
         vuint16_t  ENBL0:1;           /* Enable for timer channel #0 */
      } B;
   } eTIMER1_ENBL_16B_tag;

   typedef union {   /* DMA Request 0 Select Registers */
      vuint16_t R;
      struct {
         vuint16_t  DREQ0_EN:1;        /* DMA Request Enable */
         vuint16_t:10;
         vuint16_t  DREQ0V:5;          /* DMA Request Select */
      } B;
   } eTIMER1_DREQ0_16B_tag;

   typedef union {   /* DMA Request 1 Select Registers */
      vuint16_t R;
      struct {
         vuint16_t  DREQ1_EN:1;        /* DMA Request Enable */
         vuint16_t:10;
         vuint16_t  DREQ1V:5;          /* DMA Request Select */
      } B;
   } eTIMER1_DREQ1_16B_tag;


   typedef struct eTIMER1_CHANNEL_struct_tag {

                                                   /* Compare Register 1 */
      eTIMER1_COMP1_16B_tag COMP1;         /* relative offset: 0x0000 */
                                                   /* Compare Register 2 */
      eTIMER1_COMP2_16B_tag COMP2;         /* relative offset: 0x0002 */
                                                   /* Capture Register 1 */
      eTIMER1_CAPT1_16B_tag CAPT1;         /* relative offset: 0x0004 */
                                                   /* Capture Register 2 */
      eTIMER1_CAPT2_16B_tag CAPT2;         /* relative offset: 0x0006 */
                                                        /* Load Register */
      eTIMER1_LOAD_16B_tag LOAD;           /* relative offset: 0x0008 */
                                                        /* Hold Register */
      eTIMER1_HOLD_16B_tag HOLD;           /* relative offset: 0x000A */
                                                     /* Counter Register */
      eTIMER1_CNTR_16B_tag CNTR;           /* relative offset: 0x000C */
                                                     /* Control Register */
      eTIMER1_CTRL1_16B_tag CTRL1;         /* relative offset: 0x000E */
                                                   /* Control Register 2 */
      eTIMER1_CTRL2_16B_tag CTRL2;         /* relative offset: 0x0010 */
                                                   /* Control Register 3 */
      eTIMER1_CTRL3_16B_tag CTRL3;         /* relative offset: 0x0012 */
                                                      /* Status Register */
      eTIMER1_STS_16B_tag STS;             /* relative offset: 0x0014 */
                                    /* Interrupt and DMA Enable Register */
      eTIMER1_INTDMA_16B_tag INTDMA;       /* relative offset: 0x0016 */
                                           /* Comparator Load Register 1 */
      eTIMER1_CMPLD1_16B_tag CMPLD1;       /* relative offset: 0x0018 */
                                           /* Comparator Load Register 2 */
      eTIMER1_CMPLD2_16B_tag CMPLD2;       /* relative offset: 0x001A */
                                 /* Compare and Capture Control Register */
      eTIMER1_CCCTRL_16B_tag CCCTRL;       /* relative offset: 0x001C */
                                                /* Input Filter Register */
      eTIMER1_FILT_16B_tag FILT;           /* relative offset: 0x001E */

   } eTIMER1_CHANNEL_tag;



   typedef struct eTIMER1_struct_tag {

      union {
                                                /*  Register set CHANNEL */
         eTIMER1_CHANNEL_tag CHANNEL[6];   /* offset: 0x0000  (0x0020 x 6) */

         struct {
                                                   /* Compare Register 1 */
            eTIMER1_COMP1_16B_tag COMP10;  /* offset: 0x0000 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER1_COMP2_16B_tag COMP20;  /* offset: 0x0002 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER1_CAPT1_16B_tag CAPT10;  /* offset: 0x0004 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER1_CAPT2_16B_tag CAPT20;  /* offset: 0x0006 size: 16 bit */
                                                        /* Load Register */
            eTIMER1_LOAD_16B_tag LOAD0;    /* offset: 0x0008 size: 16 bit */
                                                        /* Hold Register */
            eTIMER1_HOLD_16B_tag HOLD0;    /* offset: 0x000A size: 16 bit */
                                                     /* Counter Register */
            eTIMER1_CNTR_16B_tag CNTR0;    /* offset: 0x000C size: 16 bit */
                                                     /* Control Register */
            eTIMER1_CTRL1_16B_tag CTRL10;  /* offset: 0x000E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER1_CTRL2_16B_tag CTRL20;  /* offset: 0x0010 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER1_CTRL3_16B_tag CTRL30;  /* offset: 0x0012 size: 16 bit */
                                                      /* Status Register */
            eTIMER1_STS_16B_tag STS0;      /* offset: 0x0014 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER1_INTDMA_16B_tag INTDMA0;  /* offset: 0x0016 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER1_CMPLD1_16B_tag CMPLD10;  /* offset: 0x0018 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER1_CMPLD2_16B_tag CMPLD20;  /* offset: 0x001A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER1_CCCTRL_16B_tag CCCTRL0;  /* offset: 0x001C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER1_FILT_16B_tag FILT0;    /* offset: 0x001E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER1_COMP1_16B_tag COMP11;  /* offset: 0x0020 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER1_COMP2_16B_tag COMP21;  /* offset: 0x0022 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER1_CAPT1_16B_tag CAPT11;  /* offset: 0x0024 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER1_CAPT2_16B_tag CAPT21;  /* offset: 0x0026 size: 16 bit */
                                                        /* Load Register */
            eTIMER1_LOAD_16B_tag LOAD1;    /* offset: 0x0028 size: 16 bit */
                                                        /* Hold Register */
            eTIMER1_HOLD_16B_tag HOLD1;    /* offset: 0x002A size: 16 bit */
                                                     /* Counter Register */
            eTIMER1_CNTR_16B_tag CNTR1;    /* offset: 0x002C size: 16 bit */
                                                     /* Control Register */
            eTIMER1_CTRL1_16B_tag CTRL11;  /* offset: 0x002E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER1_CTRL2_16B_tag CTRL21;  /* offset: 0x0030 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER1_CTRL3_16B_tag CTRL31;  /* offset: 0x0032 size: 16 bit */
                                                      /* Status Register */
            eTIMER1_STS_16B_tag STS1;      /* offset: 0x0034 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER1_INTDMA_16B_tag INTDMA1;  /* offset: 0x0036 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER1_CMPLD1_16B_tag CMPLD11;  /* offset: 0x0038 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER1_CMPLD2_16B_tag CMPLD21;  /* offset: 0x003A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER1_CCCTRL_16B_tag CCCTRL1;  /* offset: 0x003C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER1_FILT_16B_tag FILT1;    /* offset: 0x003E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER1_COMP1_16B_tag COMP12;  /* offset: 0x0040 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER1_COMP2_16B_tag COMP22;  /* offset: 0x0042 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER1_CAPT1_16B_tag CAPT12;  /* offset: 0x0044 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER1_CAPT2_16B_tag CAPT22;  /* offset: 0x0046 size: 16 bit */
                                                        /* Load Register */
            eTIMER1_LOAD_16B_tag LOAD2;    /* offset: 0x0048 size: 16 bit */
                                                        /* Hold Register */
            eTIMER1_HOLD_16B_tag HOLD2;    /* offset: 0x004A size: 16 bit */
                                                     /* Counter Register */
            eTIMER1_CNTR_16B_tag CNTR2;    /* offset: 0x004C size: 16 bit */
                                                     /* Control Register */
            eTIMER1_CTRL1_16B_tag CTRL12;  /* offset: 0x004E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER1_CTRL2_16B_tag CTRL22;  /* offset: 0x0050 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER1_CTRL3_16B_tag CTRL32;  /* offset: 0x0052 size: 16 bit */
                                                      /* Status Register */
            eTIMER1_STS_16B_tag STS2;      /* offset: 0x0054 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER1_INTDMA_16B_tag INTDMA2;  /* offset: 0x0056 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER1_CMPLD1_16B_tag CMPLD12;  /* offset: 0x0058 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER1_CMPLD2_16B_tag CMPLD22;  /* offset: 0x005A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER1_CCCTRL_16B_tag CCCTRL2;  /* offset: 0x005C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER1_FILT_16B_tag FILT2;    /* offset: 0x005E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER1_COMP1_16B_tag COMP13;  /* offset: 0x0060 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER1_COMP2_16B_tag COMP23;  /* offset: 0x0062 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER1_CAPT1_16B_tag CAPT13;  /* offset: 0x0064 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER1_CAPT2_16B_tag CAPT23;  /* offset: 0x0066 size: 16 bit */
                                                        /* Load Register */
            eTIMER1_LOAD_16B_tag LOAD3;    /* offset: 0x0068 size: 16 bit */
                                                        /* Hold Register */
            eTIMER1_HOLD_16B_tag HOLD3;    /* offset: 0x006A size: 16 bit */
                                                     /* Counter Register */
            eTIMER1_CNTR_16B_tag CNTR3;    /* offset: 0x006C size: 16 bit */
                                                     /* Control Register */
            eTIMER1_CTRL1_16B_tag CTRL13;  /* offset: 0x006E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER1_CTRL2_16B_tag CTRL23;  /* offset: 0x0070 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER1_CTRL3_16B_tag CTRL33;  /* offset: 0x0072 size: 16 bit */
                                                      /* Status Register */
            eTIMER1_STS_16B_tag STS3;      /* offset: 0x0074 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER1_INTDMA_16B_tag INTDMA3;  /* offset: 0x0076 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER1_CMPLD1_16B_tag CMPLD13;  /* offset: 0x0078 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER1_CMPLD2_16B_tag CMPLD23;  /* offset: 0x007A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER1_CCCTRL_16B_tag CCCTRL3;  /* offset: 0x007C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER1_FILT_16B_tag FILT3;    /* offset: 0x007E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER1_COMP1_16B_tag COMP14;  /* offset: 0x0080 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER1_COMP2_16B_tag COMP24;  /* offset: 0x0082 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER1_CAPT1_16B_tag CAPT14;  /* offset: 0x0084 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER1_CAPT2_16B_tag CAPT24;  /* offset: 0x0086 size: 16 bit */
                                                        /* Load Register */
            eTIMER1_LOAD_16B_tag LOAD4;    /* offset: 0x0088 size: 16 bit */
                                                        /* Hold Register */
            eTIMER1_HOLD_16B_tag HOLD4;    /* offset: 0x008A size: 16 bit */
                                                     /* Counter Register */
            eTIMER1_CNTR_16B_tag CNTR4;    /* offset: 0x008C size: 16 bit */
                                                     /* Control Register */
            eTIMER1_CTRL1_16B_tag CTRL14;  /* offset: 0x008E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER1_CTRL2_16B_tag CTRL24;  /* offset: 0x0090 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER1_CTRL3_16B_tag CTRL34;  /* offset: 0x0092 size: 16 bit */
                                                      /* Status Register */
            eTIMER1_STS_16B_tag STS4;      /* offset: 0x0094 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER1_INTDMA_16B_tag INTDMA4;  /* offset: 0x0096 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER1_CMPLD1_16B_tag CMPLD14;  /* offset: 0x0098 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER1_CMPLD2_16B_tag CMPLD24;  /* offset: 0x009A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER1_CCCTRL_16B_tag CCCTRL4;  /* offset: 0x009C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER1_FILT_16B_tag FILT4;    /* offset: 0x009E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER1_COMP1_16B_tag COMP15;  /* offset: 0x00A0 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER1_COMP2_16B_tag COMP25;  /* offset: 0x00A2 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER1_CAPT1_16B_tag CAPT15;  /* offset: 0x00A4 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER1_CAPT2_16B_tag CAPT25;  /* offset: 0x00A6 size: 16 bit */
                                                        /* Load Register */
            eTIMER1_LOAD_16B_tag LOAD5;    /* offset: 0x00A8 size: 16 bit */
                                                        /* Hold Register */
            eTIMER1_HOLD_16B_tag HOLD5;    /* offset: 0x00AA size: 16 bit */
                                                     /* Counter Register */
            eTIMER1_CNTR_16B_tag CNTR5;    /* offset: 0x00AC size: 16 bit */
                                                     /* Control Register */
            eTIMER1_CTRL1_16B_tag CTRL15;  /* offset: 0x00AE size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER1_CTRL2_16B_tag CTRL25;  /* offset: 0x00B0 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER1_CTRL3_16B_tag CTRL35;  /* offset: 0x00B2 size: 16 bit */
                                                      /* Status Register */
            eTIMER1_STS_16B_tag STS5;      /* offset: 0x00B4 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER1_INTDMA_16B_tag INTDMA5;  /* offset: 0x00B6 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER1_CMPLD1_16B_tag CMPLD15;  /* offset: 0x00B8 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER1_CMPLD2_16B_tag CMPLD25;  /* offset: 0x00BA size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER1_CCCTRL_16B_tag CCCTRL5;  /* offset: 0x00BC size: 16 bit */
                                                /* Input Filter Register */
            eTIMER1_FILT_16B_tag FILT5;    /* offset: 0x00BE size: 16 bit */
         };

      };
      int8_t eTIMER1_reserved_00C0[76];
                                              /* Channel Enable Register */
      eTIMER1_ENBL_16B_tag ENBL;           /* offset: 0x010C size: 16 bit */
      int8_t eTIMER1_reserved_010E[2];
                                       /* DMA Request 0 Select Registers */
      eTIMER1_DREQ0_16B_tag DREQ0;         /* offset: 0x0110 size: 16 bit */
                                       /* DMA Request 1 Select Registers */
      eTIMER1_DREQ1_16B_tag DREQ1;         /* offset: 0x0112 size: 16 bit */
      int8_t eTIMER1_reserved_0114[16108];

   } eTIMER1_tag;


#define eTIMER1_BASEADDRESS 0xFFE1C000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define eTIMER1 (*(volatile eTIMER1_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE1C000UL))



/****************************************************************/
/*                                                              */
/* Module: eTIMER2  */
/*                                                              */
/****************************************************************/


   /* Register layout for all registers COMP1 ... */

   typedef union {   /* Compare Register 1 */
      vuint16_t R;
   } eTIMER2_COMP1_16B_tag;


   /* Register layout for all registers COMP2 ... */

   typedef union {   /* Compare Register 2 */
      vuint16_t R;
   } eTIMER2_COMP2_16B_tag;


   /* Register layout for all registers CAPT1 ... */

   typedef union {   /* Capture Register 1 */
      vuint16_t R;
   } eTIMER2_CAPT1_16B_tag;


   /* Register layout for all registers CAPT2 ... */

   typedef union {   /* Capture Register 2 */
      vuint16_t R;
   } eTIMER2_CAPT2_16B_tag;


   /* Register layout for all registers LOAD ... */

   typedef union {   /* Load Register */
      vuint16_t R;
   } eTIMER2_LOAD_16B_tag;


   /* Register layout for all registers HOLD ... */

   typedef union {   /* Hold Register */
      vuint16_t R;
   } eTIMER2_HOLD_16B_tag;


   /* Register layout for all registers CNTR ... */

   typedef union {   /* Counter Register */
      vuint16_t R;
   } eTIMER2_CNTR_16B_tag;


   /* Register layout for all registers CTRL1 ... */

   typedef union {   /* Control Register */
      vuint16_t R;
      struct {
         vuint16_t  CNTMODE:3;         /* Count Mode */
         vuint16_t  PRISRC:5;          /* Primary Count Source */
         vuint16_t  ONCE:1;            /* Count Once */
         vuint16_t  LENGTH:1;          /* Count Length */
         vuint16_t  DIR:1;             /* Count Direction */
         vuint16_t  SECSRC:5;          /* Secondary Count Source */
      } B;
   } eTIMER2_CTRL1_16B_tag;


   /* Register layout for all registers CTRL2 ... */

   typedef union {   /* Control Register 2 */
      vuint16_t R;
      struct {
         vuint16_t  OEN:1;             /* Output Enable */
         vuint16_t  RDNT:1;            /* Redundant Channel Enable */
         vuint16_t  INPUT:1;           /* External Input Signal */
         vuint16_t  VAL:1;             /* Forced OFLAG Value */
         vuint16_t  FORCE:1;           /* Force the OFLAG output */
         vuint16_t  COFRC:1;           /* Co-channel OFLAG Force */
         vuint16_t  COINIT:2;          /* Co-channel Initialization */
         vuint16_t  SIPS:1;            /* Secondary Source Input Polarity Select */
         vuint16_t  PIPS:1;            /* Primary Source Input Polarity Select */
         vuint16_t  OPS:1;             /* Output Polarity Select */
         vuint16_t  MSTR:1;            /* Master Mode */
         vuint16_t  OUTMODE:4;         /* Output Mode */
      } B;
   } eTIMER2_CTRL2_16B_tag;


   /* Register layout for all registers CTRL3 ... */

   typedef union {   /* Control Register 3 */
      vuint16_t R;
      struct {
         vuint16_t  STPEN:1;           /* Stop Action Enable */
         vuint16_t  ROC:2;             /* Reload On Capture */
         vuint16_t:5;
         vuint16_t  C2FCNT:3;          /* CAPT2 FIFO Word Count */
         vuint16_t  C1FCNT:3;          /* CAPT1 FIFO Word Count */
         vuint16_t  DBGEN:2;           /* Debug Actions Enable */
      } B;
   } eTIMER2_CTRL3_16B_tag;


   /* Register layout for all registers STS ... */

   typedef union {   /* Status Register */
      vuint16_t R;
      struct {
         vuint16_t:6;
         vuint16_t  WDF:1;             /* Watchdog Time-out Flag */
         vuint16_t  RCF:1;             /* Redundant Channel Flag */
         vuint16_t  ICF2:1;            /* Input Capture 2 Flag */
         vuint16_t  ICF1:1;            /* Input Capture 1 Flag */
         vuint16_t  IEHF:1;            /* Input Edge High Flag */
         vuint16_t  IELF:1;            /* Input Edge Low Flag */
         vuint16_t  TOF:1;             /* Timer Overflow Flag */
         vuint16_t  TCF2:1;            /* Timer Compare 2 Flag */
         vuint16_t  TCF1:1;            /* Timer Compare 1 Flag */
         vuint16_t  TCF:1;             /* Timer Compare Flag */
      } B;
   } eTIMER2_STS_16B_tag;


   /* Register layout for all registers INTDMA ... */

   typedef union {   /* Interrupt and DMA Enable Register */
      vuint16_t R;
      struct {
         vuint16_t  ICF2DE:1;          /* Input Capture 2 Flag DMA Enable */
         vuint16_t  ICF1DE:1;          /* Input Capture 1 Flag DMA Enable */
         vuint16_t  CMPLD2DE:1;        /* Comparator Load Register 2 Flag DMA Enable */
         vuint16_t  CMPLD1DE:1;        /* Comparator Load Register 1 Flag DMA Enable */
         vuint16_t:2;
         vuint16_t  WDFIE:1;           /* Watchdog Flag Interrupt Enable */
         vuint16_t  RCFIE:1;           /* Redundant Channel Flag Interrupt Enable */
         vuint16_t  ICF2IE:1;          /* Input Capture 2 Flag Interrupt Enable */
         vuint16_t  ICF1IE:1;          /* Input Capture 1 Flag Interrupt Enable */
         vuint16_t  IEHFIE:1;          /* Input Edge High Flag Interrupt Enable */
         vuint16_t  IELFIE:1;          /* Input Edge Low Flag Interrupt Enable */
         vuint16_t  TOFIE:1;           /* Timer Overflow Flag Interrupt Enable */
         vuint16_t  TCF2IE:1;          /* Timer Compare 2 Flag Interrupt Enable */
         vuint16_t  TCF1IE:1;          /* Timer Compare 1 Flag Interrupt Enable */
         vuint16_t  TCFIE:1;           /* Timer Compare Flag Interrupt Enable */
      } B;
   } eTIMER2_INTDMA_16B_tag;


   /* Register layout for all registers CMPLD1 ... */

   typedef union {   /* Comparator Load Register 1 */
      vuint16_t R;
   } eTIMER2_CMPLD1_16B_tag;


   /* Register layout for all registers CMPLD2 ... */

   typedef union {   /* Comparator Load Register 2 */
      vuint16_t R;
   } eTIMER2_CMPLD2_16B_tag;


   /* Register layout for all registers CCCTRL ... */

   typedef union {   /* Compare and Capture Control Register */
      vuint16_t R;
      struct {
         vuint16_t  CLC2:3;            /* Compare Load Control 2 */
         vuint16_t  CLC1:3;            /* Compare Load Control 1 */
         vuint16_t  CMPMODE:2;         /* Compare Mode */
         vuint16_t  CPT2MODE:2;        /* Capture 2 Mode Control */
         vuint16_t  CPT1MODE:2;        /* Capture 1 Mode Control */
         vuint16_t  CFWM:2;            /* Capture FIFO Water Mark */
         vuint16_t  ONESHOT:1;         /* One Shot Capture Mode */
         vuint16_t  ARM:1;             /* Arm Capture */
      } B;
   } eTIMER2_CCCTRL_16B_tag;


   /* Register layout for all registers FILT ... */

   typedef union {   /* Input Filter Register */
      vuint16_t R;
      struct {
         vuint16_t:5;
         vuint16_t  FILT_CNT:3;        /* Input Filter Sample Count */
         vuint16_t  FILT_PER:8;        /* Input Filter Sample Period */
      } B;
   } eTIMER2_FILT_16B_tag;

   typedef union {   /* Channel Enable Register */
      vuint16_t R;
      struct {
         vuint16_t:10;
         vuint16_t  ENBL5:1;           /* Enable for timer channel #5 */
         vuint16_t  ENBL4:1;           /* Enable for timer channel #4 */
         vuint16_t  ENBL3:1;           /* Enable for timer channel #3 */
         vuint16_t  ENBL2:1;           /* Enable for timer channel #2 */
         vuint16_t  ENBL1:1;           /* Enable for timer channel #1 */
         vuint16_t  ENBL0:1;           /* Enable for timer channel #0 */
      } B;
   } eTIMER2_ENBL_16B_tag;

   typedef union {   /* DMA Request 0 Select Registers */
      vuint16_t R;
      struct {
         vuint16_t  DREQ0_EN:1;        /* DMA Request Enable */
         vuint16_t:10;
         vuint16_t  DREQ0V:5;          /* DMA Request Select */
      } B;
   } eTIMER2_DREQ0_16B_tag;

   typedef union {   /* DMA Request 1 Select Registers */
      vuint16_t R;
      struct {
         vuint16_t  DREQ1_EN:1;        /* DMA Request Enable */
         vuint16_t:10;
         vuint16_t  DREQ1V:5;          /* DMA Request Select */
      } B;
   } eTIMER2_DREQ1_16B_tag;


   typedef struct eTIMER2_CHANNEL_struct_tag {

                                                   /* Compare Register 1 */
      eTIMER2_COMP1_16B_tag COMP1;         /* relative offset: 0x0000 */
                                                   /* Compare Register 2 */
      eTIMER2_COMP2_16B_tag COMP2;         /* relative offset: 0x0002 */
                                                   /* Capture Register 1 */
      eTIMER2_CAPT1_16B_tag CAPT1;         /* relative offset: 0x0004 */
                                                   /* Capture Register 2 */
      eTIMER2_CAPT2_16B_tag CAPT2;         /* relative offset: 0x0006 */
                                                        /* Load Register */
      eTIMER2_LOAD_16B_tag LOAD;           /* relative offset: 0x0008 */
                                                        /* Hold Register */
      eTIMER2_HOLD_16B_tag HOLD;           /* relative offset: 0x000A */
                                                     /* Counter Register */
      eTIMER2_CNTR_16B_tag CNTR;           /* relative offset: 0x000C */
                                                     /* Control Register */
      eTIMER2_CTRL1_16B_tag CTRL1;         /* relative offset: 0x000E */
                                                   /* Control Register 2 */
      eTIMER2_CTRL2_16B_tag CTRL2;         /* relative offset: 0x0010 */
                                                   /* Control Register 3 */
      eTIMER2_CTRL3_16B_tag CTRL3;         /* relative offset: 0x0012 */
                                                      /* Status Register */
      eTIMER2_STS_16B_tag STS;             /* relative offset: 0x0014 */
                                    /* Interrupt and DMA Enable Register */
      eTIMER2_INTDMA_16B_tag INTDMA;       /* relative offset: 0x0016 */
                                           /* Comparator Load Register 1 */
      eTIMER2_CMPLD1_16B_tag CMPLD1;       /* relative offset: 0x0018 */
                                           /* Comparator Load Register 2 */
      eTIMER2_CMPLD2_16B_tag CMPLD2;       /* relative offset: 0x001A */
                                 /* Compare and Capture Control Register */
      eTIMER2_CCCTRL_16B_tag CCCTRL;       /* relative offset: 0x001C */
                                                /* Input Filter Register */
      eTIMER2_FILT_16B_tag FILT;           /* relative offset: 0x001E */

   } eTIMER2_CHANNEL_tag;



   typedef struct eTIMER2_struct_tag {

      union {
                                                /*  Register set CHANNEL */
         eTIMER2_CHANNEL_tag CHANNEL[6];   /* offset: 0x0000  (0x0020 x 6) */

         struct {
                                                   /* Compare Register 1 */
            eTIMER2_COMP1_16B_tag COMP10;  /* offset: 0x0000 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER2_COMP2_16B_tag COMP20;  /* offset: 0x0002 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER2_CAPT1_16B_tag CAPT10;  /* offset: 0x0004 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER2_CAPT2_16B_tag CAPT20;  /* offset: 0x0006 size: 16 bit */
                                                        /* Load Register */
            eTIMER2_LOAD_16B_tag LOAD0;    /* offset: 0x0008 size: 16 bit */
                                                        /* Hold Register */
            eTIMER2_HOLD_16B_tag HOLD0;    /* offset: 0x000A size: 16 bit */
                                                     /* Counter Register */
            eTIMER2_CNTR_16B_tag CNTR0;    /* offset: 0x000C size: 16 bit */
                                                     /* Control Register */
            eTIMER2_CTRL1_16B_tag CTRL10;  /* offset: 0x000E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER2_CTRL2_16B_tag CTRL20;  /* offset: 0x0010 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER2_CTRL3_16B_tag CTRL30;  /* offset: 0x0012 size: 16 bit */
                                                      /* Status Register */
            eTIMER2_STS_16B_tag STS0;      /* offset: 0x0014 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER2_INTDMA_16B_tag INTDMA0;  /* offset: 0x0016 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER2_CMPLD1_16B_tag CMPLD10;  /* offset: 0x0018 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER2_CMPLD2_16B_tag CMPLD20;  /* offset: 0x001A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER2_CCCTRL_16B_tag CCCTRL0;  /* offset: 0x001C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER2_FILT_16B_tag FILT0;    /* offset: 0x001E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER2_COMP1_16B_tag COMP11;  /* offset: 0x0020 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER2_COMP2_16B_tag COMP21;  /* offset: 0x0022 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER2_CAPT1_16B_tag CAPT11;  /* offset: 0x0024 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER2_CAPT2_16B_tag CAPT21;  /* offset: 0x0026 size: 16 bit */
                                                        /* Load Register */
            eTIMER2_LOAD_16B_tag LOAD1;    /* offset: 0x0028 size: 16 bit */
                                                        /* Hold Register */
            eTIMER2_HOLD_16B_tag HOLD1;    /* offset: 0x002A size: 16 bit */
                                                     /* Counter Register */
            eTIMER2_CNTR_16B_tag CNTR1;    /* offset: 0x002C size: 16 bit */
                                                     /* Control Register */
            eTIMER2_CTRL1_16B_tag CTRL11;  /* offset: 0x002E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER2_CTRL2_16B_tag CTRL21;  /* offset: 0x0030 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER2_CTRL3_16B_tag CTRL31;  /* offset: 0x0032 size: 16 bit */
                                                      /* Status Register */
            eTIMER2_STS_16B_tag STS1;      /* offset: 0x0034 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER2_INTDMA_16B_tag INTDMA1;  /* offset: 0x0036 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER2_CMPLD1_16B_tag CMPLD11;  /* offset: 0x0038 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER2_CMPLD2_16B_tag CMPLD21;  /* offset: 0x003A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER2_CCCTRL_16B_tag CCCTRL1;  /* offset: 0x003C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER2_FILT_16B_tag FILT1;    /* offset: 0x003E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER2_COMP1_16B_tag COMP12;  /* offset: 0x0040 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER2_COMP2_16B_tag COMP22;  /* offset: 0x0042 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER2_CAPT1_16B_tag CAPT12;  /* offset: 0x0044 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER2_CAPT2_16B_tag CAPT22;  /* offset: 0x0046 size: 16 bit */
                                                        /* Load Register */
            eTIMER2_LOAD_16B_tag LOAD2;    /* offset: 0x0048 size: 16 bit */
                                                        /* Hold Register */
            eTIMER2_HOLD_16B_tag HOLD2;    /* offset: 0x004A size: 16 bit */
                                                     /* Counter Register */
            eTIMER2_CNTR_16B_tag CNTR2;    /* offset: 0x004C size: 16 bit */
                                                     /* Control Register */
            eTIMER2_CTRL1_16B_tag CTRL12;  /* offset: 0x004E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER2_CTRL2_16B_tag CTRL22;  /* offset: 0x0050 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER2_CTRL3_16B_tag CTRL32;  /* offset: 0x0052 size: 16 bit */
                                                      /* Status Register */
            eTIMER2_STS_16B_tag STS2;      /* offset: 0x0054 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER2_INTDMA_16B_tag INTDMA2;  /* offset: 0x0056 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER2_CMPLD1_16B_tag CMPLD12;  /* offset: 0x0058 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER2_CMPLD2_16B_tag CMPLD22;  /* offset: 0x005A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER2_CCCTRL_16B_tag CCCTRL2;  /* offset: 0x005C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER2_FILT_16B_tag FILT2;    /* offset: 0x005E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER2_COMP1_16B_tag COMP13;  /* offset: 0x0060 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER2_COMP2_16B_tag COMP23;  /* offset: 0x0062 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER2_CAPT1_16B_tag CAPT13;  /* offset: 0x0064 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER2_CAPT2_16B_tag CAPT23;  /* offset: 0x0066 size: 16 bit */
                                                        /* Load Register */
            eTIMER2_LOAD_16B_tag LOAD3;    /* offset: 0x0068 size: 16 bit */
                                                        /* Hold Register */
            eTIMER2_HOLD_16B_tag HOLD3;    /* offset: 0x006A size: 16 bit */
                                                     /* Counter Register */
            eTIMER2_CNTR_16B_tag CNTR3;    /* offset: 0x006C size: 16 bit */
                                                     /* Control Register */
            eTIMER2_CTRL1_16B_tag CTRL13;  /* offset: 0x006E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER2_CTRL2_16B_tag CTRL23;  /* offset: 0x0070 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER2_CTRL3_16B_tag CTRL33;  /* offset: 0x0072 size: 16 bit */
                                                      /* Status Register */
            eTIMER2_STS_16B_tag STS3;      /* offset: 0x0074 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER2_INTDMA_16B_tag INTDMA3;  /* offset: 0x0076 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER2_CMPLD1_16B_tag CMPLD13;  /* offset: 0x0078 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER2_CMPLD2_16B_tag CMPLD23;  /* offset: 0x007A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER2_CCCTRL_16B_tag CCCTRL3;  /* offset: 0x007C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER2_FILT_16B_tag FILT3;    /* offset: 0x007E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER2_COMP1_16B_tag COMP14;  /* offset: 0x0080 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER2_COMP2_16B_tag COMP24;  /* offset: 0x0082 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER2_CAPT1_16B_tag CAPT14;  /* offset: 0x0084 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER2_CAPT2_16B_tag CAPT24;  /* offset: 0x0086 size: 16 bit */
                                                        /* Load Register */
            eTIMER2_LOAD_16B_tag LOAD4;    /* offset: 0x0088 size: 16 bit */
                                                        /* Hold Register */
            eTIMER2_HOLD_16B_tag HOLD4;    /* offset: 0x008A size: 16 bit */
                                                     /* Counter Register */
            eTIMER2_CNTR_16B_tag CNTR4;    /* offset: 0x008C size: 16 bit */
                                                     /* Control Register */
            eTIMER2_CTRL1_16B_tag CTRL14;  /* offset: 0x008E size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER2_CTRL2_16B_tag CTRL24;  /* offset: 0x0090 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER2_CTRL3_16B_tag CTRL34;  /* offset: 0x0092 size: 16 bit */
                                                      /* Status Register */
            eTIMER2_STS_16B_tag STS4;      /* offset: 0x0094 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER2_INTDMA_16B_tag INTDMA4;  /* offset: 0x0096 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER2_CMPLD1_16B_tag CMPLD14;  /* offset: 0x0098 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER2_CMPLD2_16B_tag CMPLD24;  /* offset: 0x009A size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER2_CCCTRL_16B_tag CCCTRL4;  /* offset: 0x009C size: 16 bit */
                                                /* Input Filter Register */
            eTIMER2_FILT_16B_tag FILT4;    /* offset: 0x009E size: 16 bit */
                                                   /* Compare Register 1 */
            eTIMER2_COMP1_16B_tag COMP15;  /* offset: 0x00A0 size: 16 bit */
                                                   /* Compare Register 2 */
            eTIMER2_COMP2_16B_tag COMP25;  /* offset: 0x00A2 size: 16 bit */
                                                   /* Capture Register 1 */
            eTIMER2_CAPT1_16B_tag CAPT15;  /* offset: 0x00A4 size: 16 bit */
                                                   /* Capture Register 2 */
            eTIMER2_CAPT2_16B_tag CAPT25;  /* offset: 0x00A6 size: 16 bit */
                                                        /* Load Register */
            eTIMER2_LOAD_16B_tag LOAD5;    /* offset: 0x00A8 size: 16 bit */
                                                        /* Hold Register */
            eTIMER2_HOLD_16B_tag HOLD5;    /* offset: 0x00AA size: 16 bit */
                                                     /* Counter Register */
            eTIMER2_CNTR_16B_tag CNTR5;    /* offset: 0x00AC size: 16 bit */
                                                     /* Control Register */
            eTIMER2_CTRL1_16B_tag CTRL15;  /* offset: 0x00AE size: 16 bit */
                                                   /* Control Register 2 */
            eTIMER2_CTRL2_16B_tag CTRL25;  /* offset: 0x00B0 size: 16 bit */
                                                   /* Control Register 3 */
            eTIMER2_CTRL3_16B_tag CTRL35;  /* offset: 0x00B2 size: 16 bit */
                                                      /* Status Register */
            eTIMER2_STS_16B_tag STS5;      /* offset: 0x00B4 size: 16 bit */
                                    /* Interrupt and DMA Enable Register */
            eTIMER2_INTDMA_16B_tag INTDMA5;  /* offset: 0x00B6 size: 16 bit */
                                           /* Comparator Load Register 1 */
            eTIMER2_CMPLD1_16B_tag CMPLD15;  /* offset: 0x00B8 size: 16 bit */
                                           /* Comparator Load Register 2 */
            eTIMER2_CMPLD2_16B_tag CMPLD25;  /* offset: 0x00BA size: 16 bit */
                                 /* Compare and Capture Control Register */
            eTIMER2_CCCTRL_16B_tag CCCTRL5;  /* offset: 0x00BC size: 16 bit */
                                                /* Input Filter Register */
            eTIMER2_FILT_16B_tag FILT5;    /* offset: 0x00BE size: 16 bit */
         };

      };
      int8_t eTIMER2_reserved_00C0[76];
                                              /* Channel Enable Register */
      eTIMER2_ENBL_16B_tag ENBL;           /* offset: 0x010C size: 16 bit */
      int8_t eTIMER2_reserved_010E[2];
                                       /* DMA Request 0 Select Registers */
      eTIMER2_DREQ0_16B_tag DREQ0;         /* offset: 0x0110 size: 16 bit */
                                       /* DMA Request 1 Select Registers */
      eTIMER2_DREQ1_16B_tag DREQ1;         /* offset: 0x0112 size: 16 bit */
      int8_t eTIMER2_reserved_0114[16108];

   } eTIMER2_tag;


#define eTIMER2_BASEADDRESS 0xFFE20000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define eTIMER2 (*(volatile eTIMER2_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE20000UL))



/****************************************************************/
/*                                                              */
/* Module: mcPWM  */
/*                                                              */
/****************************************************************/


   /* Register layout for all registers CNT ... */

   typedef union {   /* Counter Register */
      vuint16_t R;
   } mcPWM_CNT_16B_tag;


   /* Register layout for all registers INIT ... */

   typedef union {   /* Initial Counter Register */
      vuint16_t R;
   } mcPWM_INIT_16B_tag;


   /* Register layout for all registers CTRL2 ... */

   typedef union {   /* Control 2 Register */
      vuint16_t R;
      struct {
         vuint16_t  DBGEN:1;           /* Debug Enable */
         vuint16_t  WAITEN:1;          /* Wait Enable */
         vuint16_t  INDEP:1;           /* Independent or Complementary Pair Operation */
         vuint16_t  PWM23_INIT:1;      /* PWM23 Initial Value */
         vuint16_t  PWM45_INIT:1;      /* PWM45 Initial Value */
         vuint16_t  PWMX_INIT:1;       /* PWMX Initial Value */
         vuint16_t  INIT_SEL:2;        /* Initialization Control Select */
         vuint16_t  FRCEN:1;           /* Force Initialization Enable */
         vuint16_t  FORCE:1;           /* Force Initialization */
         vuint16_t  FORCE_SEL:3;       /* Force Source Select */
         vuint16_t  RELOAD_SEL:1;      /* Reload Source Select */
         vuint16_t  CLK_SEL:2;         /* Clock Source Select */
      } B;
   } mcPWM_CTRL2_16B_tag;


   /* Register layout for all registers CTRL1 ... */

   typedef union {   /* Control Register */
      vuint16_t R;
      struct {
         vuint16_t  LDFQ:4;            /* Load Frequency */
         vuint16_t  HALF:1;            /* Half Cycle Reload */
         vuint16_t  FULL:1;            /* Full Cycle Reload */
         vuint16_t  DT:2;              /* Deadtime */
         vuint16_t:1;
         vuint16_t  PRSC:3;            /* Prescaler */
         vuint16_t:1;
         vuint16_t  LDMOD:1;           /* Load Mode Select */
         vuint16_t:1;
         vuint16_t  DBL_EN:1;          /* Double Switching Enable */
      } B;
   } mcPWM_CTRL1_16B_tag;


   /* Register layout for all registers VAL_0 ... */

   typedef union {   /* Value Register */
      vuint16_t R;
   } mcPWM_VAL_16B_tag;

   /* Register layout for all registers VAL_1 matches VAL */

   /* Register layout for all registers VAL_2 matches VAL */

   /* Register layout for all registers VAL_3 matches VAL */

   /* Register layout for all registers VAL_4 matches VAL */

   /* Register layout for all registers VAL_5 matches VAL */


   /* Register layout for all registers OCTRL ... */

   typedef union {   /* Output Control Register */
      vuint16_t R;
      struct {
         vuint16_t  PWMA_IN:1;         /* PWMA Input */
         vuint16_t  PWMB_IN:1;         /* PWMB Input */
         vuint16_t  PWMX_IN:1;         /* PWMX Input */
         vuint16_t:2;
         vuint16_t  POLA:1;            /* PWMA Output Polarity */
         vuint16_t  POLB:1;            /* PWMB Output Polarity */
         vuint16_t  POLX:1;            /* PWMX Output Polarity */
         vuint16_t:2;
         vuint16_t  PWMAFS:2;          /* PWMA Fault State */
         vuint16_t  PWMBFS:2;          /* PWMB Fault State */
         vuint16_t  PWMXFS:2;          /* PWMX Fault State */
      } B;
   } mcPWM_OCTRL_16B_tag;


   /* Register layout for all registers STS ... */

   typedef union {   /* Status Register */
      vuint16_t R;
      struct {
         vuint16_t:1;
         vuint16_t  RUF:1;             /* Registers Updated Flag */
         vuint16_t  REF:1;             /* Reload Error Flag */
         vuint16_t  RF:1;              /* Reload Flag */
         vuint16_t:4;
         vuint16_t  CFX1:1;            /* Capture Flag X1 */
         vuint16_t  CFX0:1;            /* Capture Flag X0 */
         vuint16_t  CMPF:6;            /* Compare Flags */
      } B;
   } mcPWM_STS_16B_tag;


   /* Register layout for all registers INTEN ... */

   typedef union {   /* Interrupt Enable Registers */
      vuint16_t R;
      struct {
         vuint16_t:2;
         vuint16_t  REIE:1;            /* Reload Error Interrupt Enable */
         vuint16_t  RIE:1;             /* Reload Interrupt Enable */
         vuint16_t:4;
         vuint16_t  CX1IE:1;           /* Capture X1 Interrupt Enable */
         vuint16_t  CX0IE:1;           /* Capture X0 Interrupt Enable */
         vuint16_t  CMPIE:6;           /* Compare Interrupt Enables */
      } B;
   } mcPWM_INTEN_16B_tag;


   /* Register layout for all registers DMAEN ... */

   typedef union {   /* DMA Enable Registers */
      vuint16_t R;
      struct {
         vuint16_t:6;
         vuint16_t  VALDE:1;           /* Value Register DMA Enable */
         vuint16_t  FAND:1;            /* FIFO Watermark AND Control */
         vuint16_t  CAPTDE:2;          /* Capture DMA Enable Source Select */
         vuint16_t:4;
         vuint16_t  CX1DE:1;           /* Capture X1 FIFO DMA Enable */
         vuint16_t  CX0DE:1;           /* Capture X0 FIFO DMA Enable */
      } B;
   } mcPWM_DMAEN_16B_tag;


   /* Register layout for all registers TCTRL ... */

   typedef union {   /* Output Trigger Control  Registers */
      vuint16_t R;
      struct {
         vuint16_t:10;
         vuint16_t  OUT_TRIG_EN:6;     /* Output Trigger Enables */
      } B;
   } mcPWM_TCTRL_16B_tag;


   /* Register layout for all registers DISMAP ... */

   typedef union {   /* Fault Disable Mapping   Registers */
      vuint16_t R;
      struct {
         vuint16_t:4;
         vuint16_t  DISX:4;            /* PWMX Fault Disable Mask */
         vuint16_t  DISB:4;            /* PWMB Fault Disable Mask */
         vuint16_t  DISA:4;            /* PWMA Fault Disable Mask */
      } B;
   } mcPWM_DISMAP_16B_tag;


   /* Register layout for all registers DTCNT0 ... */

   typedef union {   /* Deadtime Count Register 0 */
      vuint16_t R;
      struct {
         vuint16_t:5;
         vuint16_t  DTCNT0:11;         /* Deadtime Count 0 */
      } B;
   } mcPWM_DTCNT0_16B_tag;


   /* Register layout for all registers DTCNT1 ... */

   typedef union {   /* Deadtime Count Register 1 */
      vuint16_t R;
      struct {
         vuint16_t:5;
         vuint16_t  DTCNT1:11;         /* Deadtime Count 1 */
      } B;
   } mcPWM_DTCNT1_16B_tag;


   /* Register layout for all registers CAPTCTRLX ... */

   typedef union {   /* Capture Control X Register */
      vuint16_t R;
      struct {
         vuint16_t  CX1CNT:3;          /* Capture X1 FIFO Word Count */
         vuint16_t  CX0CNT:3;          /* Capture X0 FIFO Word Count */
         vuint16_t  CFXWM:2;           /* Capture X FIFOs Water Mark */
         vuint16_t  EDGCNTX_EN:1;      /* Edge Counter X Enable */
         vuint16_t  INP_SELX:1;        /* Input Select X */
         vuint16_t  EDGX1:2;           /* Edge X 1 */
         vuint16_t  EDGX0:2;           /* Edge X 0 */
         vuint16_t  ONESHOTX:1;        /* One Shot Mode X */
         vuint16_t  ARMX:1;            /* Arm X */
      } B;
   } mcPWM_CAPTCTRLX_16B_tag;


   /* Register layout for all registers CAPTCMPX ... */

   typedef union {   /* Capture Compare X Register */
      vuint16_t R;
      struct {
         vuint16_t  EDGCNTX:8;         /* Edge Counter X */
         vuint16_t  EDGCMPX:8;         /* Edge Compare X */
      } B;
   } mcPWM_CAPTCMPX_16B_tag;


   /* Register layout for all registers CVAL0 ... */

   typedef union {   /* Capture Value 0 Register */
      vuint16_t R;
      struct {
         vuint16_t  CAPTVAL0:16;       /* Captured value from submodule counter */
      } B;
   } mcPWM_CVAL0_16B_tag;


   /* Register layout for all registers CVAL0CYC ... */

   typedef union {   /* Capture Value 0 Cycle Register */
      vuint16_t R;
      struct {
         vuint16_t:13;
         vuint16_t  CVAL0CYC:3;        /* Capture Value 0 Cycle */
      } B;
   } mcPWM_CVAL0CYC_16B_tag;


   /* Register layout for all registers CVAL1 ... */

   typedef union {   /* Capture Value 1 Register */
      vuint16_t R;
      struct {
         vuint16_t  CAPTVAL1:16;       /* Captured value from submodule counter */
      } B;
   } mcPWM_CVAL1_16B_tag;


   /* Register layout for all registers CVAL1CYC ... */

   typedef union {   /* Capture Value 1 Cycle Register */
      vuint16_t R;
      struct {
         vuint16_t:13;
         vuint16_t  CVAL1CYC:3;        /* Capture Value 1 Cycle */
      } B;
   } mcPWM_CVAL1CYC_16B_tag;

   typedef union {   /* Output Enable Register */
      vuint16_t R;
      struct {
         vuint16_t:4;
         vuint16_t  PWMA_EN:4;         /* PWMA Output Enables */
         vuint16_t  PWMB_EN:4;         /* PWMB Output Enables */
         vuint16_t  PWMX_EN:4;         /* PWMX Output Enables */
      } B;
   } mcPWM_OUTEN_16B_tag;

   typedef union {   /* Mask Register */
      vuint16_t R;
      struct {
         vuint16_t:4;
         vuint16_t  MASKA:4;           /* PWMA Masks */
         vuint16_t  MASKB:4;           /* PWMB Masks */
         vuint16_t  MASKX:4;           /* PWMX Masks */
      } B;
   } mcPWM_MASK_16B_tag;

   typedef union {   /* Software Controlled Output Register */
      vuint16_t R;
      struct {
         vuint16_t:8;
         vuint16_t  OUT23_3:1;         /* Software Controlled Output 23_3 */
         vuint16_t  OUT45_3:1;         /* Software Controlled Output 45_3 */
         vuint16_t  OUT23_2:1;         /* Software Controlled Output 23_2 */
         vuint16_t  OUT45_2:1;         /* Software Controlled Output 45_2 */
         vuint16_t  OUT23_1:1;         /* Software Controlled Output 23_1 */
         vuint16_t  OUT45_1:1;         /* Software Controlled Output 45_1 */
         vuint16_t  OUT23_0:1;         /* Software Controlled Output 23_0 */
         vuint16_t  OUT45_0:1;         /* Software Controlled Output 45_0 */
      } B;
   } mcPWM_SWCOUT_16B_tag;

   typedef union {   /* Deadtime Source Select Register */
      vuint16_t R;
      struct {
         vuint16_t  SEL23_3:2;         /* PWM23_3 Control Select */
         vuint16_t  SEL45_3:2;         /* PWM45_3 Control Select */
         vuint16_t  SEL23_2:2;         /* PWM23_2 Control Select */
         vuint16_t  SEL45_2:2;         /* PWM45_2 Control Select */
         vuint16_t  SEL23_1:2;         /* PWM23_1 Control Select */
         vuint16_t  SEL45_1:2;         /* PWM45_1 Control Select */
         vuint16_t  SEL23_0:2;         /* PWM23_0 Control Select */
         vuint16_t  SEL45_0:2;         /* PWM45_0 Control Select */
      } B;
   } mcPWM_DTSRCSEL_16B_tag;

   typedef union {   /* Master Control Register */
      vuint16_t R;
      struct {
         vuint16_t  IPOL:4;            /* Current Polarity */
         vuint16_t  RUN:4;             /* Run */
         vuint16_t  CLDOK:4;            /* Clear Load Okay *//* Renamed from CLOK for code reuse */
         vuint16_t  LDOK:4;            /* Load Okay */
      } B;
   } mcPWM_MCTRL_16B_tag;

   typedef union {   /* Fault Control Register */
      vuint16_t R;
      struct {
         vuint16_t  FLVL:4;            /* Fault Level */
         vuint16_t  FAUTO:4;           /* Automatic Fault Clearing */
         vuint16_t  FSAFE:4;           /* Fault Safety Mode */
         vuint16_t  FIE:4;             /* Fault Interrupt Enables */
      } B;
   } mcPWM_FCTRL_16B_tag;

   typedef union {   /* Fault Status Register */
      vuint16_t R;
      struct {
         vuint16_t:3;
         vuint16_t  FTEST:1;           /* Fault Test */
         vuint16_t  FFPIN:4;           /* Filtered Fault Pins */
         vuint16_t  FFULL:4;           /* Full Cycle */
         vuint16_t  FFLAG:4;           /* Fault Flags */
      } B;
   } mcPWM_FSTS_16B_tag;

   typedef union {   /* Fault Filter Register */
      vuint16_t R;
      struct {
         vuint16_t  GSTR:1;            /* Fault Glitch Stretch Enable */
         vuint16_t:4;
         vuint16_t  FILT_CNT:3;        /* Fault Filter Count */
         vuint16_t  FILT_PER:8;        /* Fault Filter Period */
      } B;
   } mcPWM_FFILT_16B_tag;


   typedef struct mcPWM_SUBMOD_struct_tag {

                                                     /* Counter Register */
      mcPWM_CNT_16B_tag CNT;               /* relative offset: 0x0000 */
                                             /* Initial Counter Register */
      mcPWM_INIT_16B_tag INIT;             /* relative offset: 0x0002 */
                                                   /* Control 2 Register */
      mcPWM_CTRL2_16B_tag CTRL2;           /* relative offset: 0x0004 */
                                                     /* Control Register */
      mcPWM_CTRL1_16B_tag CTRL;           /* relative offset: 0x0006 *//* Renamed from CTRL1 to be able to reuse code */
      union {
         mcPWM_VAL_16B_tag VAL[6];         /* relative offset: 0x0008 */

         struct {
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_0;       /* relative offset: 0x0008 */
            mcPWM_VAL_16B_tag VAL_1;       /* relative offset: 0x000A */
            mcPWM_VAL_16B_tag VAL_2;       /* relative offset: 0x000C */
            mcPWM_VAL_16B_tag VAL_3;       /* relative offset: 0x000E */
            mcPWM_VAL_16B_tag VAL_4;       /* relative offset: 0x0010 */
            mcPWM_VAL_16B_tag VAL_5;       /* relative offset: 0x0012 */
         };

      };
      int8_t mcPWM_SUBMOD_reserved_0014[4];
                                              /* Output Control Register */
      mcPWM_OCTRL_16B_tag OCTRL;           /* relative offset: 0x0018 */
                                                      /* Status Register */
      mcPWM_STS_16B_tag STS;               /* relative offset: 0x001A */
                                           /* Interrupt Enable Registers */
      mcPWM_INTEN_16B_tag INTEN;           /* relative offset: 0x001C */
                                                 /* DMA Enable Registers */
      mcPWM_DMAEN_16B_tag DMAEN;           /* relative offset: 0x001E */
                                    /* Output Trigger Control  Registers */
      mcPWM_TCTRL_16B_tag TCTRL;           /* relative offset: 0x0020 */
                                    /* Fault Disable Mapping   Registers */
      mcPWM_DISMAP_16B_tag DISMAP;         /* relative offset: 0x0022 */
                                            /* Deadtime Count Register 0 */
      mcPWM_DTCNT0_16B_tag DTCNT0;         /* relative offset: 0x0024 */
                                            /* Deadtime Count Register 1 */
      mcPWM_DTCNT1_16B_tag DTCNT1;         /* relative offset: 0x0026 */
      int8_t mcPWM_SUBMOD_reserved_0028[8];
                                           /* Capture Control X Register */
      mcPWM_CAPTCTRLX_16B_tag CAPTCTRLX;   /* relative offset: 0x0030 */
                                           /* Capture Compare X Register */
      mcPWM_CAPTCMPX_16B_tag CAPTCMPX;     /* relative offset: 0x0032 */
                                             /* Capture Value 0 Register */
      mcPWM_CVAL0_16B_tag CVAL0;           /* relative offset: 0x0034 */
                                       /* Capture Value 0 Cycle Register */
      mcPWM_CVAL0CYC_16B_tag CVAL0CYC;     /* relative offset: 0x0036 */
                                             /* Capture Value 1 Register */
      mcPWM_CVAL1_16B_tag CVAL1;           /* relative offset: 0x0038 */
                                       /* Capture Value 1 Cycle Register */
      mcPWM_CVAL1CYC_16B_tag CVAL1CYC;     /* relative offset: 0x003A */
      int8_t mcPWM_SUBMOD_reserved_003C[20];

   } mcPWM_SUBMOD_tag;



   struct FLEXPWM_tag { /* Changed from "typedef struct mcPWM_struct_tag" to be able to reuse code */

      union {
                                                 /*  Register set SUBMOD */
         mcPWM_SUBMOD_tag SUBMOD[4];       /* offset: 0x0000  (0x0050 x 4) */

                                               /*  Alias name for SUBMOD */
         mcPWM_SUBMOD_tag SUB[4];          /* deprecated - please avoid */

         struct {
                                                     /* Counter Register */
            mcPWM_CNT_16B_tag CNT0;        /* offset: 0x0000 size: 16 bit */
                                             /* Initial Counter Register */
            mcPWM_INIT_16B_tag INIT0;      /* offset: 0x0002 size: 16 bit */
                                                   /* Control 2 Register */
            mcPWM_CTRL2_16B_tag CTRL20;    /* offset: 0x0004 size: 16 bit */
                                                     /* Control Register */
            mcPWM_CTRL1_16B_tag CTRL10;    /* offset: 0x0006 size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_00;      /* offset: 0x0008 size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_10;      /* offset: 0x000A size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_20;      /* offset: 0x000C size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_30;      /* offset: 0x000E size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_40;      /* offset: 0x0010 size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_50;      /* offset: 0x0012 size: 16 bit */
            int8_t mcPWM_reserved_0014_I2[4];
                                              /* Output Control Register */
            mcPWM_OCTRL_16B_tag OCTRL0;    /* offset: 0x0018 size: 16 bit */
                                                      /* Status Register */
            mcPWM_STS_16B_tag STS0;        /* offset: 0x001A size: 16 bit */
                                           /* Interrupt Enable Registers */
            mcPWM_INTEN_16B_tag INTEN0;    /* offset: 0x001C size: 16 bit */
                                                 /* DMA Enable Registers */
            mcPWM_DMAEN_16B_tag DMAEN0;    /* offset: 0x001E size: 16 bit */
                                    /* Output Trigger Control  Registers */
            mcPWM_TCTRL_16B_tag TCTRL0;    /* offset: 0x0020 size: 16 bit */
                                    /* Fault Disable Mapping   Registers */
            mcPWM_DISMAP_16B_tag DISMAP0;  /* offset: 0x0022 size: 16 bit */
                                            /* Deadtime Count Register 0 */
            mcPWM_DTCNT0_16B_tag DTCNT00;  /* offset: 0x0024 size: 16 bit */
                                            /* Deadtime Count Register 1 */
            mcPWM_DTCNT1_16B_tag DTCNT10;  /* offset: 0x0026 size: 16 bit */
            int8_t mcPWM_reserved_0028_I2[8];
                                           /* Capture Control X Register */
            mcPWM_CAPTCTRLX_16B_tag CAPTCTRLX0;  /* offset: 0x0030 size: 16 bit */
                                           /* Capture Compare X Register */
            mcPWM_CAPTCMPX_16B_tag CAPTCMPX0;  /* offset: 0x0032 size: 16 bit */
                                             /* Capture Value 0 Register */
            mcPWM_CVAL0_16B_tag CVAL00;    /* offset: 0x0034 size: 16 bit */
                                       /* Capture Value 0 Cycle Register */
            mcPWM_CVAL0CYC_16B_tag CVAL0CYC0;  /* offset: 0x0036 size: 16 bit */
                                             /* Capture Value 1 Register */
            mcPWM_CVAL1_16B_tag CVAL10;    /* offset: 0x0038 size: 16 bit */
                                       /* Capture Value 1 Cycle Register */
            mcPWM_CVAL1CYC_16B_tag CVAL1CYC0;  /* offset: 0x003A size: 16 bit */
            int8_t mcPWM_reserved_003C_I2[20];
                                                     /* Counter Register */
            mcPWM_CNT_16B_tag CNT1;        /* offset: 0x0050 size: 16 bit */
                                             /* Initial Counter Register */
            mcPWM_INIT_16B_tag INIT1;      /* offset: 0x0052 size: 16 bit */
                                                   /* Control 2 Register */
            mcPWM_CTRL2_16B_tag CTRL21;    /* offset: 0x0054 size: 16 bit */
                                                     /* Control Register */
            mcPWM_CTRL1_16B_tag CTRL11;    /* offset: 0x0056 size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_01;      /* offset: 0x0058 size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_11;      /* offset: 0x005A size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_21;      /* offset: 0x005C size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_31;      /* offset: 0x005E size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_41;      /* offset: 0x0060 size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_51;      /* offset: 0x0062 size: 16 bit */
            int8_t mcPWM_reserved_0064_I2[4];
                                              /* Output Control Register */
            mcPWM_OCTRL_16B_tag OCTRL1;    /* offset: 0x0068 size: 16 bit */
                                                      /* Status Register */
            mcPWM_STS_16B_tag STS1;        /* offset: 0x006A size: 16 bit */
                                           /* Interrupt Enable Registers */
            mcPWM_INTEN_16B_tag INTEN1;    /* offset: 0x006C size: 16 bit */
                                                 /* DMA Enable Registers */
            mcPWM_DMAEN_16B_tag DMAEN1;    /* offset: 0x006E size: 16 bit */
                                    /* Output Trigger Control  Registers */
            mcPWM_TCTRL_16B_tag TCTRL1;    /* offset: 0x0070 size: 16 bit */
                                    /* Fault Disable Mapping   Registers */
            mcPWM_DISMAP_16B_tag DISMAP1;  /* offset: 0x0072 size: 16 bit */
                                            /* Deadtime Count Register 0 */
            mcPWM_DTCNT0_16B_tag DTCNT01;  /* offset: 0x0074 size: 16 bit */
                                            /* Deadtime Count Register 1 */
            mcPWM_DTCNT1_16B_tag DTCNT11;  /* offset: 0x0076 size: 16 bit */
            int8_t mcPWM_reserved_0078_I2[8];
                                           /* Capture Control X Register */
            mcPWM_CAPTCTRLX_16B_tag CAPTCTRLX1;  /* offset: 0x0080 size: 16 bit */
                                           /* Capture Compare X Register */
            mcPWM_CAPTCMPX_16B_tag CAPTCMPX1;  /* offset: 0x0082 size: 16 bit */
                                             /* Capture Value 0 Register */
            mcPWM_CVAL0_16B_tag CVAL01;    /* offset: 0x0084 size: 16 bit */
                                       /* Capture Value 0 Cycle Register */
            mcPWM_CVAL0CYC_16B_tag CVAL0CYC1;  /* offset: 0x0086 size: 16 bit */
                                             /* Capture Value 1 Register */
            mcPWM_CVAL1_16B_tag CVAL11;    /* offset: 0x0088 size: 16 bit */
                                       /* Capture Value 1 Cycle Register */
            mcPWM_CVAL1CYC_16B_tag CVAL1CYC1;  /* offset: 0x008A size: 16 bit */
            int8_t mcPWM_reserved_008C_I2[20];
                                                     /* Counter Register */
            mcPWM_CNT_16B_tag CNT2;        /* offset: 0x00A0 size: 16 bit */
                                             /* Initial Counter Register */
            mcPWM_INIT_16B_tag INIT2;      /* offset: 0x00A2 size: 16 bit */
                                                   /* Control 2 Register */
            mcPWM_CTRL2_16B_tag CTRL22;    /* offset: 0x00A4 size: 16 bit */
                                                     /* Control Register */
            mcPWM_CTRL1_16B_tag CTRL12;    /* offset: 0x00A6 size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_02;      /* offset: 0x00A8 size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_12;      /* offset: 0x00AA size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_22;      /* offset: 0x00AC size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_32;      /* offset: 0x00AE size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_42;      /* offset: 0x00B0 size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_52;      /* offset: 0x00B2 size: 16 bit */
            int8_t mcPWM_reserved_00B4_I2[4];
                                              /* Output Control Register */
            mcPWM_OCTRL_16B_tag OCTRL2;    /* offset: 0x00B8 size: 16 bit */
                                                      /* Status Register */
            mcPWM_STS_16B_tag STS2;        /* offset: 0x00BA size: 16 bit */
                                           /* Interrupt Enable Registers */
            mcPWM_INTEN_16B_tag INTEN2;    /* offset: 0x00BC size: 16 bit */
                                                 /* DMA Enable Registers */
            mcPWM_DMAEN_16B_tag DMAEN2;    /* offset: 0x00BE size: 16 bit */
                                    /* Output Trigger Control  Registers */
            mcPWM_TCTRL_16B_tag TCTRL2;    /* offset: 0x00C0 size: 16 bit */
                                    /* Fault Disable Mapping   Registers */
            mcPWM_DISMAP_16B_tag DISMAP2;  /* offset: 0x00C2 size: 16 bit */
                                            /* Deadtime Count Register 0 */
            mcPWM_DTCNT0_16B_tag DTCNT02;  /* offset: 0x00C4 size: 16 bit */
                                            /* Deadtime Count Register 1 */
            mcPWM_DTCNT1_16B_tag DTCNT12;  /* offset: 0x00C6 size: 16 bit */
            int8_t mcPWM_reserved_00C8_I2[8];
                                           /* Capture Control X Register */
            mcPWM_CAPTCTRLX_16B_tag CAPTCTRLX2;  /* offset: 0x00D0 size: 16 bit */
                                           /* Capture Compare X Register */
            mcPWM_CAPTCMPX_16B_tag CAPTCMPX2;  /* offset: 0x00D2 size: 16 bit */
                                             /* Capture Value 0 Register */
            mcPWM_CVAL0_16B_tag CVAL02;    /* offset: 0x00D4 size: 16 bit */
                                       /* Capture Value 0 Cycle Register */
            mcPWM_CVAL0CYC_16B_tag CVAL0CYC2;  /* offset: 0x00D6 size: 16 bit */
                                             /* Capture Value 1 Register */
            mcPWM_CVAL1_16B_tag CVAL12;    /* offset: 0x00D8 size: 16 bit */
                                       /* Capture Value 1 Cycle Register */
            mcPWM_CVAL1CYC_16B_tag CVAL1CYC2;  /* offset: 0x00DA size: 16 bit */
            int8_t mcPWM_reserved_00DC_I2[20];
                                                     /* Counter Register */
            mcPWM_CNT_16B_tag CNT3;        /* offset: 0x00F0 size: 16 bit */
                                             /* Initial Counter Register */
            mcPWM_INIT_16B_tag INIT3;      /* offset: 0x00F2 size: 16 bit */
                                                   /* Control 2 Register */
            mcPWM_CTRL2_16B_tag CTRL23;    /* offset: 0x00F4 size: 16 bit */
                                                     /* Control Register */
            mcPWM_CTRL1_16B_tag CTRL13;    /* offset: 0x00F6 size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_03;      /* offset: 0x00F8 size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_13;      /* offset: 0x00FA size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_23;      /* offset: 0x00FC size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_33;      /* offset: 0x00FE size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_43;      /* offset: 0x0100 size: 16 bit */
                                                       /* Value Register */
            mcPWM_VAL_16B_tag VAL_53;      /* offset: 0x0102 size: 16 bit */
            int8_t mcPWM_reserved_0104_I2[4];
                                              /* Output Control Register */
            mcPWM_OCTRL_16B_tag OCTRL3;    /* offset: 0x0108 size: 16 bit */
                                                      /* Status Register */
            mcPWM_STS_16B_tag STS3;        /* offset: 0x010A size: 16 bit */
                                           /* Interrupt Enable Registers */
            mcPWM_INTEN_16B_tag INTEN3;    /* offset: 0x010C size: 16 bit */
                                                 /* DMA Enable Registers */
            mcPWM_DMAEN_16B_tag DMAEN3;    /* offset: 0x010E size: 16 bit */
                                    /* Output Trigger Control  Registers */
            mcPWM_TCTRL_16B_tag TCTRL3;    /* offset: 0x0110 size: 16 bit */
                                    /* Fault Disable Mapping   Registers */
            mcPWM_DISMAP_16B_tag DISMAP3;  /* offset: 0x0112 size: 16 bit */
                                            /* Deadtime Count Register 0 */
            mcPWM_DTCNT0_16B_tag DTCNT03;  /* offset: 0x0114 size: 16 bit */
                                            /* Deadtime Count Register 1 */
            mcPWM_DTCNT1_16B_tag DTCNT13;  /* offset: 0x0116 size: 16 bit */
            int8_t mcPWM_reserved_0118_I2[8];
                                           /* Capture Control X Register */
            mcPWM_CAPTCTRLX_16B_tag CAPTCTRLX3;  /* offset: 0x0120 size: 16 bit */
                                           /* Capture Compare X Register */
            mcPWM_CAPTCMPX_16B_tag CAPTCMPX3;  /* offset: 0x0122 size: 16 bit */
                                             /* Capture Value 0 Register */
            mcPWM_CVAL0_16B_tag CVAL03;    /* offset: 0x0124 size: 16 bit */
                                       /* Capture Value 0 Cycle Register */
            mcPWM_CVAL0CYC_16B_tag CVAL0CYC3;  /* offset: 0x0126 size: 16 bit */
                                             /* Capture Value 1 Register */
            mcPWM_CVAL1_16B_tag CVAL13;    /* offset: 0x0128 size: 16 bit */
                                       /* Capture Value 1 Cycle Register */
            mcPWM_CVAL1CYC_16B_tag CVAL1CYC3;  /* offset: 0x012A size: 16 bit */
            int8_t mcPWM_reserved_012C_E2[20];
         };

      };
                                               /* Output Enable Register */
      mcPWM_OUTEN_16B_tag OUTEN;           /* offset: 0x0140 size: 16 bit */
                                                        /* Mask Register */
      mcPWM_MASK_16B_tag MASK;             /* offset: 0x0142 size: 16 bit */
                                  /* Software Controlled Output Register */
      mcPWM_SWCOUT_16B_tag SWCOUT;         /* offset: 0x0144 size: 16 bit */
                                      /* Deadtime Source Select Register */
      mcPWM_DTSRCSEL_16B_tag DTSRCSEL;     /* offset: 0x0146 size: 16 bit */
                                              /* Master Control Register */
      mcPWM_MCTRL_16B_tag MCTRL;           /* offset: 0x0148 size: 16 bit */
      int8_t mcPWM_reserved_014A[2];
                                               /* Fault Control Register */
      mcPWM_FCTRL_16B_tag FCTRL;           /* offset: 0x014C size: 16 bit */
                                                /* Fault Status Register */
      mcPWM_FSTS_16B_tag FSTS;             /* offset: 0x014E size: 16 bit */
                                                /* Fault Filter Register */
      mcPWM_FFILT_16B_tag FFILT;           /* offset: 0x0150 size: 16 bit */
      int8_t mcPWM_reserved_0152[16046];

   } /*mcPWM_tag*/;

#if 0
#define mcPWM_A_BASEADDRESS 0xFFE24000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define mcPWM_A (*(volatile mcPWM_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE24000UL))
#define mcPWM_B_BASEADDRESS 0xFFE28000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define mcPWM_B (*(volatile mcPWM_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE28000UL))
#endif
/* Added to be able to reuse code */
#define FLEXPWM_0_BASEADDRESS 0xFFE24000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define FLEXPWM_0 (*(volatile struct FLEXPWM_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE24000UL))
#define FLEXPWM_1_BASEADDRESS 0xFFE28000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define FLEXPWM_1 (*(volatile struct FLEXPWM_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE28000UL))



/****************************************************************/
/*                                                              */
/* Module: LINFLEX  */
/*                                                              */
/****************************************************************/

   typedef union {   /* LIN Control Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  CCD:1;             /* Checksum Calculation disable */
         vuint32_t  CFD:1;             /* Checksum field disable */
         vuint32_t  LASE:1;            /* LIN Slave Auto Synchronization enable */
         vuint32_t  AWUM:1;            /* Automatic Wake-Up Mode */
         vuint32_t  MBL:4;             /* LIN Master Break Length */
         vuint32_t  BF:1;              /* Bypass Filter */
         vuint32_t  SLFM:1;            /* Self Test Mode *//* Renamed from "SFTM" to be able to reuse code */
         vuint32_t  LBKM:1;            /* Loopback Mode */
         vuint32_t  MME:1;             /* Master Mode Enable */
         vuint32_t  SBDT:1;            /* Slave Mode Break Detection Threshold */
         vuint32_t  RBLM:1;            /* Receiver Buffer Locked Mode */
         vuint32_t  SLEEP:1;           /* Sleep Mode Request */
         vuint32_t  INIT:1;            /* Initialization Mode Request */
      } B;
   } LINFLEX_LINCR1_32B_tag;

   typedef union {   /* LIN Interrupt Enable Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  SZIE:1;            /* Stuck at Zero Interrupt Enable */
         vuint32_t  OCIE:1;            /* Output Compare Interrupt Enable */
         vuint32_t  BEIE:1;            /* Bit Error Interrupt Enable */
         vuint32_t  CEIE:1;            /* Checksum Error Interrupt Enable */
         vuint32_t  HEIE:1;            /* Header Error Interrupt Enable */
         vuint32_t:2;
         vuint32_t  FEIE:1;            /* Framing Error Interrupt Enable */
         vuint32_t  BOIE:1;            /* Buffer Overrun Interrupt Enable */
         vuint32_t  LSIE:1;            /* LIN State Interrupt Enable */
         vuint32_t  WUIE:1;            /* Wake-up Interrupt Enable */
         vuint32_t  DBFIE:1;           /* Data Buffer Full Interrupt Enable */
         vuint32_t  DBEIETOIE:1;       /* Data Buffer Empty Interrupt Enable / Timeout Interrupt Enable */
         vuint32_t  DRIE:1;            /* Data Reception complete Interrupt Enable */
         vuint32_t  DTIE:1;            /* Data Transmitted Interrupt Enable */
         vuint32_t  HRIE:1;            /* Header Received Interrupt Enable */
      } B;
   } LINFLEX_LINIER_32B_tag;

   typedef union {   /* LIN Status Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  LINS:4;            /* LIN State */
         vuint32_t:2;
         vuint32_t  RMB:1;             /* Release Message Buffer */
         vuint32_t:1;
         vuint32_t  RBSY:1;            /* Receiver Busy Flag */
         vuint32_t  RPS:1;             /* LIN Receive Pin State */
         vuint32_t  WUF:1;             /* Wake Up Flag */
         vuint32_t  DBFF:1;            /* Data Buffer Full Flag */
         vuint32_t  DBEF:1;            /* Data Buffer Empty Flag */
         vuint32_t  DRF:1;             /* Data Reception Completed Flag */
         vuint32_t  DTF:1;             /* Data Transmission Completed Flag */
         vuint32_t  HRF:1;             /* Header Received Flag */
      } B;
   } LINFLEX_LINSR_32B_tag;

   typedef union {   /* LIN Error Status Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  SZF:1;             /* Stuck at Zero Flag */
         vuint32_t  OCF:1;             /* Output Compare Flag */
         vuint32_t  BEF:1;             /* Bit Error Flag */
         vuint32_t  CEF:1;             /* Checksum Error Flag */
         vuint32_t  SFEF:1;            /* Sync Field Error Flag */
         vuint32_t  BDEF:1;            /* Break Delimiter Error Flag */
         vuint32_t  IDPEF:1;           /* Identifier Parity Error Flag */
         vuint32_t  FEF:1;             /* Framing Error Flag */
         vuint32_t  BOF:1;             /* Buffer Overrun Flag */
         vuint32_t:6;
         vuint32_t  NF:1;              /* Noise Flag */
      } B;
   } LINFLEX_LINESR_32B_tag;

   typedef union {   /* UART Mode Control Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  TDFLTFC:3;         /* Transmitter Data Field Length/TX FIFO Counter */
         vuint32_t  RDFLRFC:3;         /* Reception Data Field Length/RX FIFO Counter */
         vuint32_t  RFBM:1;            /* RX FIFO/Buffer Mode */
         vuint32_t  TFBM:1;            /* TX FIFO/Buffer Mode */
         vuint32_t  WL1:1;             /* Word Length in UART mode - bit 1 */
         vuint32_t  PC1:1;             /* Parity Check - bit 1 */
         vuint32_t  RXEN:1;            /* Receiver Enable */
         vuint32_t  TXEN:1;            /* Transmitter Enable */
#ifndef USE_FIELD_ALIASES_LINFLEX
         vuint32_t  PC0:1;             /* Parity Check - bit 0 */
#else
         vuint32_t  OP:1;                /* deprecated name - please avoid */
#endif
         vuint32_t  PCE:1;             /* Parity Control Enable */
#ifndef USE_FIELD_ALIASES_LINFLEX
         vuint32_t  WL0:1;             /* Word Length in UART Mode - bit 0 */
#else
         vuint32_t  WL:1;                /* deprecated name - please avoid */
#endif
         vuint32_t  UART:1;            /* UART Mode */
      } B;
   } LINFLEX_UARTCR_32B_tag;

   typedef union {   /* UART Mode Status Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  SZF:1;             /* Stuck at Zero Flag */
         vuint32_t  OCF:1;             /* Output Compare Flag */
         vuint32_t  PE3:1;             /* Parity Error Flag Rx3 */
         vuint32_t  PE2:1;             /* Parity Error Flag Rx2 */
         vuint32_t  PE1:1;             /* Parity Error Flag Rx1 */
         vuint32_t  PE0:1;             /* Parity Error Flag Rx0 */
         vuint32_t  RMB:1;             /* Release Message Buffer */
         vuint32_t  FEF:1;             /* Framing Error Flag */
         vuint32_t  BOF:1;             /* FIFO/Buffer Overrun Flag */
         vuint32_t  RPS:1;             /* LIN Receive Pin State */
         vuint32_t  WUF:1;             /* Wakeup Flag */
         vuint32_t:1;
         vuint32_t  TO:1;              /* Time Out */
#ifndef USE_FIELD_ALIASES_LINFLEX
         vuint32_t  DRF_RFE:1;         /* Data Reception Completed Flag/RX FIFO Empty Flag */
#else
         vuint32_t  DRF:1;               /* deprecated name - please avoid */
#endif
#ifndef USE_FIELD_ALIASES_LINFLEX
         vuint32_t  DTF_TFF:1;         /* Data Transmission Completed Flag/TX FIFO Full Flag */
#else
         vuint32_t  DTF:1;               /* deprecated name - please avoid */
#endif
         vuint32_t  NF:1;              /* Noise Flag */
      } B;
   } LINFLEX_UARTSR_32B_tag;

   typedef union {   /* LIN Time-Out Control Status Register */
      vuint32_t R;
      struct {
         vuint32_t:21;
         vuint32_t  LTOM:1;            /* LIN Timeout Mode */
         vuint32_t  IOT:1;             /* Idle on Timeout */
         vuint32_t  TOCE:1;            /* Timeout Counter Enable */
         vuint32_t  CNT:8;             /* Counter Value */
      } B;
   } LINFLEX_LINTCSR_32B_tag;

   typedef union {   /* LIN Output Compare Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  OC2:8;             /* Output Compare Value 2 */
         vuint32_t  OC1:8;             /* Output Compare Value 1 */
      } B;
   } LINFLEX_LINOCR_32B_tag;

   typedef union {   /* LIN Time-Out Control Register */
      vuint32_t R;
      struct {
         vuint32_t:20;
         vuint32_t  RTO:4;             /* Response Time-Out Value */
         vuint32_t:1;
         vuint32_t  HTO:7;             /* Header Time-Out Value */
      } B;
   } LINFLEX_LINTOCR_32B_tag;

   typedef union {   /* LIN Fractional Baud Rate Register */
      vuint32_t R;
      struct {
         vuint32_t:28;
         vuint32_t  DIV_F:4;           /* Fraction bits of LFDIV */
      } B;
   } LINFLEX_LINFBRR_32B_tag;

   typedef union {   /* LIN Integer Baud Rate Register */
      vuint32_t R;
      struct {
         vuint32_t:13;
         vuint32_t  DIV_M:19;          /* LFDIV mantissa */
      } B;
   } LINFLEX_LINIBRR_32B_tag;

   typedef union {   /* LIN Checksum Field Register */
      vuint32_t R;
      struct {
         vuint32_t:24;
         vuint32_t  CF:8;              /* Checksum Bits */
      } B;
   } LINFLEX_LINCFR_32B_tag;

   typedef union {   /* LIN Control Register 2 */
      vuint32_t R;
      struct {
         vuint32_t:17;
         vuint32_t  IOBE:1;            /* Idle on Bit Error */
         vuint32_t  IOPE:1;            /* Idle on Identifier Parity Error */
         vuint32_t  WURQ:1;            /* Wakeup Generate Request */
         vuint32_t  DDRQ:1;            /* Data Discard Request */
         vuint32_t  DTRQ:1;            /* Data Transmission Request */
         vuint32_t  ABRQ:1;            /* Abort Request */
         vuint32_t  HTRQ:1;            /* Header Transmission Request */
         vuint32_t:8;
      } B;
   } LINFLEX_LINCR2_32B_tag;

   typedef union {   /* Buffer Identifier Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  DFL:6;             /* Data Field Length */
         vuint32_t  DIR:1;             /* Direction */
         vuint32_t  CCS:1;             /* Classic Checksum */
         vuint32_t:2;
         vuint32_t  ID:6;              /* Identifier */
      } B;
   } LINFLEX_BIDR_32B_tag;

   typedef union {   /* Buffer Data Register Least Significant */
      vuint32_t R;
      struct {
         vuint32_t  DATA3:8;           /* Data3 */
         vuint32_t  DATA2:8;           /* Data2 */
         vuint32_t  DATA1:8;           /* Data1 */
         vuint32_t  DATA0:8;           /* Data0 */
      } B;
   } LINFLEX_BDRL_32B_tag;

   typedef union {   /* Buffer Data Register Most Significant */
      vuint32_t R;
      struct {
         vuint32_t  DATA7:8;           /* Data7 */
         vuint32_t  DATA6:8;           /* Data6 */
         vuint32_t  DATA5:8;           /* Data5 */
         vuint32_t  DATA4:8;           /* Data4 */
      } B;
   } LINFLEX_BDRM_32B_tag;

   typedef union {   /* Identifier Filter Enable Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  FACT:16;           /* Filter Active */
      } B;
   } LINFLEX_IFER_32B_tag;

   typedef union {   /* Identifier Filter Match Index */
      vuint32_t R;
      struct {
         vuint32_t:27;
         vuint32_t  FMI:5;             /* Filter Match Index */
      } B;
   } LINFLEX_IFMI_32B_tag;

   typedef union {   /* Identifier Filter Mode Register */
      vuint32_t R;
      struct {
         vuint32_t:28;
         vuint32_t  IFM:4;             /* Filter Mode */
      } B;
   } LINFLEX_IFMR_32B_tag;


   /* Register layout for all registers IFCR ... */

   typedef union {   /* Identifier Filter Control Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  DFL:6;             /* Data Field Length */
         vuint32_t  DIR:1;             /* Direction */
         vuint32_t  CCS:1;             /* Classic Checksum */
         vuint32_t:2;
         vuint32_t  ID:6;              /* Identifier */
      } B;
   } LINFLEX_IFCR_32B_tag;

   typedef union {   /* Global Control Register */
      vuint32_t R;
      struct {
         vuint32_t:26;
         vuint32_t  TDFBM:1;           /* Transmit Data First Bit MSB */
         vuint32_t  RDFBM:1;           /* Received Data First Bit MSB */
         vuint32_t  TDLIS:1;           /* Transmit Data Level Inversion Selection */
         vuint32_t  RDLIS:1;           /* Received Data Level Inversion Selection */
         vuint32_t  STOP:1;            /* 1/2 stop bit configuration */
         vuint32_t  SR:1;              /* Soft Reset */
      } B;
   } LINFLEX_GCR_32B_tag;

   typedef union {   /* UART Preset Time Out Register */
      vuint32_t R;
      struct {
         vuint32_t:20;
         vuint32_t  PTO:12;            /* Preset Time Out */
      } B;
   } LINFLEX_UARTPTO_32B_tag;

   typedef union {   /* UART Current Time Out Register */
      vuint32_t R;
      struct {
         vuint32_t:20;
         vuint32_t  CTO:12;            /* Current value of the Time Out counter */
      } B;
   } LINFLEX_UARTCTO_32B_tag;

   typedef union {   /* DMA TX Enable Register */
      vuint32_t R;
   } LINFLEX_DMATXE_32B_tag;

   typedef union {   /* DMA RX Enable Register */
      vuint32_t R;
   } LINFLEX_DMARXE_32B_tag;


   struct LINFLEX_tag {/* Changed from "typedef struct LINFLEX_struct_tag" to be able to reuse code */

                                                 /* LIN Control Register */
      LINFLEX_LINCR1_32B_tag LINCR1;       /* offset: 0x0000 size: 32 bit */
                                        /* LIN Interrupt Enable Register */
      LINFLEX_LINIER_32B_tag LINIER;       /* offset: 0x0004 size: 32 bit */
                                                  /* LIN Status Register */
      LINFLEX_LINSR_32B_tag LINSR;         /* offset: 0x0008 size: 32 bit */
                                            /* LIN Error Status Register */
      LINFLEX_LINESR_32B_tag LINESR;       /* offset: 0x000C size: 32 bit */
                                           /* UART Mode Control Register */
      LINFLEX_UARTCR_32B_tag UARTCR;       /* offset: 0x0010 size: 32 bit */
                                            /* UART Mode Status Register */
      LINFLEX_UARTSR_32B_tag UARTSR;       /* offset: 0x0014 size: 32 bit */
                                 /* LIN Time-Out Control Status Register */
      LINFLEX_LINTCSR_32B_tag LINTCSR;     /* offset: 0x0018 size: 32 bit */
                                          /* LIN Output Compare Register */
      LINFLEX_LINOCR_32B_tag LINOCR;       /* offset: 0x001C size: 32 bit */
                                        /* LIN Time-Out Control Register */
      LINFLEX_LINTOCR_32B_tag LINTOCR;     /* offset: 0x0020 size: 32 bit */
                                    /* LIN Fractional Baud Rate Register */
      LINFLEX_LINFBRR_32B_tag LINFBRR;     /* offset: 0x0024 size: 32 bit */
                                       /* LIN Integer Baud Rate Register */
      LINFLEX_LINIBRR_32B_tag LINIBRR;     /* offset: 0x0028 size: 32 bit */
                                          /* LIN Checksum Field Register */
      LINFLEX_LINCFR_32B_tag LINCFR;       /* offset: 0x002C size: 32 bit */
                                               /* LIN Control Register 2 */
      LINFLEX_LINCR2_32B_tag LINCR2;       /* offset: 0x0030 size: 32 bit */
                                           /* Buffer Identifier Register */
      LINFLEX_BIDR_32B_tag BIDR;           /* offset: 0x0034 size: 32 bit */
                               /* Buffer Data Register Least Significant */
      LINFLEX_BDRL_32B_tag BDRL;           /* offset: 0x0038 size: 32 bit */
                                /* Buffer Data Register Most Significant */
      LINFLEX_BDRM_32B_tag BDRM;           /* offset: 0x003C size: 32 bit */
                                    /* Identifier Filter Enable Register */
      LINFLEX_IFER_32B_tag IFER;           /* offset: 0x0040 size: 32 bit */
                                        /* Identifier Filter Match Index */
      LINFLEX_IFMI_32B_tag IFMI;           /* offset: 0x0044 size: 32 bit */
                                      /* Identifier Filter Mode Register */
      LINFLEX_IFMR_32B_tag IFMR;           /* offset: 0x0048 size: 32 bit */
      union {
                                   /* Identifier Filter Control Register */
         LINFLEX_IFCR_32B_tag IFCR[16];    /* offset: 0x004C  (0x0004 x 16) */

         struct {
                                   /* Identifier Filter Control Register */
            LINFLEX_IFCR_32B_tag IFCR0;    /* offset: 0x004C size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR1;    /* offset: 0x0050 size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR2;    /* offset: 0x0054 size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR3;    /* offset: 0x0058 size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR4;    /* offset: 0x005C size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR5;    /* offset: 0x0060 size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR6;    /* offset: 0x0064 size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR7;    /* offset: 0x0068 size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR8;    /* offset: 0x006C size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR9;    /* offset: 0x0070 size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR10;   /* offset: 0x0074 size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR11;   /* offset: 0x0078 size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR12;   /* offset: 0x007C size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR13;   /* offset: 0x0080 size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR14;   /* offset: 0x0084 size: 32 bit */
            LINFLEX_IFCR_32B_tag IFCR15;   /* offset: 0x0088 size: 32 bit */
         };

      };
                                              /* Global Control Register */
      LINFLEX_GCR_32B_tag GCR;             /* offset: 0x008C size: 32 bit */
                                        /* UART Preset Time Out Register */
      LINFLEX_UARTPTO_32B_tag UARTPTO;     /* offset: 0x0090 size: 32 bit */
                                       /* UART Current Time Out Register */
      LINFLEX_UARTCTO_32B_tag UARTCTO;     /* offset: 0x0094 size: 32 bit */
                                               /* DMA TX Enable Register */
      LINFLEX_DMATXE_32B_tag DMATXE;       /* offset: 0x0098 size: 32 bit */
                                               /* DMA RX Enable Register */
      LINFLEX_DMARXE_32B_tag DMARXE;       /* offset: 0x009C size: 32 bit */
      int8_t LINFLEX_reserved_00A0[16224];

   } /*LINFLEX_tag*/;


#define LINFLEX0_BASEADDRESS 0xFFE40000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define LINFLEX0 (*(volatile LINFLEX_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE40000UL))
#define LINFLEX1_BASEADDRESS 0xFFE44000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define LINFLEX1 (*(volatile LINFLEX_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE44000UL))



/****************************************************************/
/*                                                              */
/* Module: CRC  */
/*                                                              */
/****************************************************************/


   /* Register layout for all registers CFG ... */

   typedef union {   /* CRC configuration register */
      vuint32_t R;
      vuint8_t   BYTE[4];    /* individual bytes can be accessed */
      vuint16_t  HALF[2];    /* individual halfwords can be accessed */
      vuint32_t  WORD;       /* individual words can be accessed */
      struct {
         vuint32_t:28;
         vuint32_t  POLYG:2;           /* Polynomal selection: 00- CRC-CCITT, 01- CRC-32, 1x- CRC-8 */
         vuint32_t  SWAP:1;            /* SWAP selection */
         vuint32_t  INV:1;             /* INV selection */
      } B;
   } CRC_CFG_32B_tag;


   /* Register layout for all registers INP ... */

   typedef union {   /* CRC input register */
      vuint32_t R;
      vuint8_t   BYTE[4];    /* individual bytes can be accessed */
      vuint16_t  HALF[2];    /* individual halfwords can be accessed */
      vuint32_t  WORD;       /* individual words can be accessed */
   } CRC_INP_32B_tag;


   /* Register layout for all registers CSTAT ... */

   typedef union {   /* CRC status register */
      vuint32_t R;
      vuint8_t   BYTE[4];    /* individual bytes can be accessed */
      vuint16_t  HALF[2];    /* individual halfwords can be accessed */
      vuint32_t  WORD;       /* individual words can be accessed */
   } CRC_CSTAT_32B_tag;


   /* Register layout for all registers OUTP ... */

   typedef union {   /* CRC output register */
      vuint32_t R;
      vuint8_t   BYTE[4];    /* individual bytes can be accessed */
      vuint16_t  HALF[2];    /* individual halfwords can be accessed */
      vuint32_t  WORD;       /* individual words can be accessed */
   } CRC_OUTP_32B_tag;


   typedef struct CRC_CNTX_struct_tag {

                                           /* CRC configuration register */
      CRC_CFG_32B_tag CFG;                 /* relative offset: 0x0000 */
                                                   /* CRC input register */
      CRC_INP_32B_tag INP;                 /* relative offset: 0x0004 */
                                                  /* CRC status register */
      CRC_CSTAT_32B_tag CSTAT;             /* relative offset: 0x0008 */
                                                  /* CRC output register */
      CRC_OUTP_32B_tag OUTP;               /* relative offset: 0x000C */

   } CRC_CNTX_tag;



   typedef struct CRC_struct_tag {

      union {
                                                   /*  Register set CNTX */
         CRC_CNTX_tag CNTX[3];             /* offset: 0x0000  (0x0010 x 3) */

         struct {
                                           /* CRC configuration register */
            CRC_CFG_32B_tag CFG0;          /* offset: 0x0000 size: 32 bit */
                                                   /* CRC input register */
            CRC_INP_32B_tag INP0;          /* offset: 0x0004 size: 32 bit */
                                                  /* CRC status register */
            CRC_CSTAT_32B_tag CSTAT0;      /* offset: 0x0008 size: 32 bit */
                                                  /* CRC output register */
            CRC_OUTP_32B_tag OUTP0;        /* offset: 0x000C size: 32 bit */
                                           /* CRC configuration register */
            CRC_CFG_32B_tag CFG1;          /* offset: 0x0010 size: 32 bit */
                                                   /* CRC input register */
            CRC_INP_32B_tag INP1;          /* offset: 0x0014 size: 32 bit */
                                                  /* CRC status register */
            CRC_CSTAT_32B_tag CSTAT1;      /* offset: 0x0018 size: 32 bit */
                                                  /* CRC output register */
            CRC_OUTP_32B_tag OUTP1;        /* offset: 0x001C size: 32 bit */
                                           /* CRC configuration register */
            CRC_CFG_32B_tag CFG2;          /* offset: 0x0020 size: 32 bit */
                                                   /* CRC input register */
            CRC_INP_32B_tag INP2;          /* offset: 0x0024 size: 32 bit */
                                                  /* CRC status register */
            CRC_CSTAT_32B_tag CSTAT2;      /* offset: 0x0028 size: 32 bit */
                                                  /* CRC output register */
            CRC_OUTP_32B_tag OUTP2;        /* offset: 0x002C size: 32 bit */
         };

      };
      int8_t CRC_reserved_0030[16336];

   } CRC_tag;


#define CRC_BASEADDRESS 0xFFE68000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define CRC   (*(volatile CRC_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE68000UL))



/****************************************************************/
/*                                                              */
/* Module: FCCU  */
/*                                                              */
/****************************************************************/

   typedef union {   /* FCCU Control Register */
      vuint32_t R;
      struct {
         vuint32_t:23;
         vuint32_t  NVML:1;            /* NVM configuration loaded */
         vuint32_t  OPS:2;             /* Operation status */
         vuint32_t:1;
         vuint32_t  OPR:5;             /* Operation run */
      } B;
   } FCCU_CTRL_32B_tag;

   typedef union {   /* FCCU CTRL Key Register */
      vuint32_t R;
   } FCCU_CTRLK_32B_tag;

   typedef union {   /* FCCU Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t:10;
         vuint32_t  RCCE1:1;           /* RCC1 enable */
         vuint32_t  RCCE0:1;           /* RCC0 enable */
         vuint32_t  SMRT:4;            /* Safe Mode Request Timer */
         vuint32_t:4;
         vuint32_t  CM:1;              /* Config mode */
         vuint32_t  SM:1;              /* Switching mode */
         vuint32_t  PS:1;              /* Polarity Selection */
         vuint32_t  FOM:3;             /* Fault Output Mode Selection */
         vuint32_t  FOP:6;             /* Fault Output Prescaler */
      } B;
   } FCCU_CFG_32B_tag;

   typedef union {   /* FCCU CF Configuration Register 0 */
      vuint32_t R;
      struct {
         vuint32_t  CFC31:1;           /* Critical fault 31 configuration */
         vuint32_t  CFC30:1;           /* Critical fault 30 configuration */
         vuint32_t  CFC29:1;           /* Critical fault 29 configuration */
         vuint32_t  CFC28:1;           /* Critical fault 28 configuration */
         vuint32_t  CFC27:1;           /* Critical fault 27 configuration */
         vuint32_t:2;
         vuint32_t  CFC24:1;           /* Critical fault 24 configuration */
         vuint32_t  CFC23:1;           /* Critical fault 23 configuration */
         vuint32_t  CFC22:1;           /* Critical fault 22 configuration */
         vuint32_t  CFC21:1;           /* Critical fault 21 configuration */
         vuint32_t  CFC20:1;           /* Critical fault 20 configuration */
         vuint32_t  CFC19:1;           /* Critical fault 19 configuration */
         vuint32_t  CFC18:1;           /* Critical fault 18 configuration */
         vuint32_t  CFC17:1;           /* Critical fault 17 configuration */
         vuint32_t  CFC16:1;           /* Critical fault 16 configuration */
         vuint32_t  CFC15:1;           /* Critical fault 15 configuration */
         vuint32_t  CFC14:1;           /* Critical fault 14 configuration */
         vuint32_t:2;
         vuint32_t  CFC11:1;           /* Critical fault 11 configuration */
         vuint32_t  CFC10:1;           /* Critical fault 10 configuration */
         vuint32_t  CFC9:1;            /* Critical fault 9 configuration */
         vuint32_t  CFC8:1;            /* Critical fault 8 configuration */
         vuint32_t  CFC7:1;            /* Critical fault 7 configuration */
         vuint32_t  CFC6:1;            /* Critical fault 6 configuration */
         vuint32_t  CFC5:1;            /* Critical fault 5 configuration */
         vuint32_t  CFC4:1;            /* Critical fault 4 configuration */
         vuint32_t  CFC3:1;            /* Critical fault 3 configuration */
         vuint32_t  CFC2:1;            /* Critical fault 2 configuration */
         vuint32_t  CFC1:1;            /* Critical fault 1 configuration */
         vuint32_t  CFC0:1;            /* Critical fault 0 configuration */
      } B;
   } FCCU_CF_CFG0_32B_tag;

   typedef union {   /* FCCU CF Configuration Register 1 */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  CFC47:1;           /* Critical fault 47 configuration */
         vuint32_t  CFC46:1;           /* Critical fault 46 configuration */
         vuint32_t  CFC45:1;           /* Critical fault 45 configuration */
         vuint32_t  CFC44:1;           /* Critical fault 44 configuration */
         vuint32_t  CFC43:1;           /* Critical fault 43 configuration */
         vuint32_t:5;
         vuint32_t  CFC37:1;           /* Critical fault 37 configuration */
         vuint32_t:5;
      } B;
   } FCCU_CF_CFG1_32B_tag;

   typedef union {   /* FCCU NCF Configuration Register 0 */
      vuint32_t R;
      struct {
         vuint32_t:7;
         vuint32_t  NCFC24:1;          /* Non-critical fault 24 configuration */
         vuint32_t  NCFC23:1;          /* Non-critical fault 23 configuration */
         vuint32_t  NCFC22:1;          /* Non-critical fault 22 configuration */
         vuint32_t  NCFC21:1;          /* Non-critical fault 21 configuration */
         vuint32_t  NCFC20:1;          /* Non-critical fault 20 configuration */
         vuint32_t  NCFC19:1;          /* Non-critical fault 19 configuration */
         vuint32_t:1;
         vuint32_t  NCFC17:1;          /* Non-critical fault 17 configuration */
         vuint32_t  NCFC16:1;          /* Non-critical fault 16 configuration */
         vuint32_t  NCFC15:1;          /* Non-critical fault 15 configuration */
         vuint32_t  NCFC14:1;          /* Non-critical fault 14 configuration */
         vuint32_t  NCFC13:1;          /* Non-critical fault 13 configuration */
         vuint32_t  NCFC12:1;          /* Non-critical fault 12 configuration */
         vuint32_t  NCFC11:1;          /* Non-critical fault 11 configuration */
         vuint32_t  NCFC10:1;          /* Non-critical fault 10 configuration */
         vuint32_t  NCFC9:1;           /* Non-critical fault 9 configuration */
         vuint32_t  NCFC8:1;           /* Non-critical fault 8 configuration */
         vuint32_t  NCFC7:1;           /* Non-critical fault 7 configuration */
         vuint32_t  NCFC6:1;           /* Non-critical fault 6 configuration */
         vuint32_t  NCFC5:1;           /* Non-critical fault 5 configuration */
         vuint32_t  NCFC4:1;           /* Non-critical fault 4 configuration */
         vuint32_t  NCFC3:1;           /* Non-critical fault 3 configuration */
         vuint32_t  NCFC2:1;           /* Non-critical fault 2 configuration */
         vuint32_t  NCFC1:1;           /* Non-critical fault 1 configuration */
         vuint32_t  NCFC0:1;           /* Non-critical fault 0 configuration */
      } B;
   } FCCU_NCF_CFG0_32B_tag;

   typedef union {   /* FCCU CFS Configuration Register 0 */
      vuint32_t R;
      struct {
         vuint32_t  CFSC15:2;          /* Critical fault 15 state configuration */
         vuint32_t  CFSC14:2;          /* Critical fault 14 state configuration */
         vuint32_t:4;
         vuint32_t  CFSC11:2;          /* Critical fault 11 state configuration */
         vuint32_t  CFSC10:2;          /* Critical fault 10 state configuration */
         vuint32_t  CFSC9:2;           /* Critical fault 9 state configuration */
         vuint32_t  CFSC8:2;           /* Critical fault 8 state configuration */
         vuint32_t  CFSC7:2;           /* Critical fault 7 state configuration */
         vuint32_t  CFSC6:2;           /* Critical fault 6 state configuration */
         vuint32_t  CFSC5:2;           /* Critical fault 5 state configuration */
         vuint32_t  CFSC4:2;           /* Critical fault 4 state configuration */
         vuint32_t  CFSC3:2;           /* Critical fault 3 state configuration */
         vuint32_t  CFSC2:2;           /* Critical fault 2 state configuration */
         vuint32_t  CFSC1:2;           /* Critical fault 1 state configuration */
         vuint32_t  CFSC0:2;           /* Critical fault 0 state configuration */
      } B;
   } FCCU_CFS_CFG0_32B_tag;

   typedef union {   /* FCCU CFS Configuration Register 1 */
      vuint32_t R;
      struct {
         vuint32_t  CFSC31:2;          /* Critical fault 31 state configuration */
         vuint32_t  CFSC30:2;          /* Critical fault 30 state configuration */
         vuint32_t  CFSC29:2;          /* Critical fault 29 state configuration */
         vuint32_t  CFSC28:2;          /* Critical fault 28 state configuration */
         vuint32_t  CFSC27:2;          /* Critical fault 27 state configuration */
         vuint32_t:4;
         vuint32_t  CFSC24:2;          /* Critical fault 24 state configuration */
         vuint32_t  CFSC23:2;          /* Critical fault 23 state configuration */
         vuint32_t  CFSC22:2;          /* Critical fault 22 state configuration */
         vuint32_t  CFSC21:2;          /* Critical fault 21 state configuration */
         vuint32_t  CFSC20:2;          /* Critical fault 20 state configuration */
         vuint32_t  CFSC19:2;          /* Critical fault 19 state configuration */
         vuint32_t  CFSC18:2;          /* Critical fault 18 state configuration */
         vuint32_t  CFSC17:2;          /* Critical fault 17 state configuration */
         vuint32_t  CFSC16:2;          /* Critical fault 16 state configuration */
      } B;
   } FCCU_CFS_CFG1_32B_tag;

   typedef union {   /* FCCU CFS Configuration Register 2 */
      vuint32_t R;
      struct {
         vuint32_t  CFSC47:2;          /* Critical fault 47 state configuration */
         vuint32_t  CFSC46:2;          /* Critical fault 46 state configuration */
         vuint32_t  CFSC45:2;          /* Critical fault 45 state configuration */
         vuint32_t  CFSC44:2;          /* Critical fault 44 state configuration */
         vuint32_t  CFSC43:2;          /* Critical fault 43 state configuration */
         vuint32_t:10;
         vuint32_t  CFSC37:2;          /* Critical fault 37 state configuration */
         vuint32_t:10;
      } B;
   } FCCU_CFS_CFG2_32B_tag;

   typedef union {   /* FCCU NCFS Configuration Register 0 */
      vuint32_t R;
      struct {
         vuint32_t  NCFSC15:2;         /* Non-critical fault 15 state configuration */
         vuint32_t  NCFSC14:2;         /* Non-critical fault 14 state configuration */
         vuint32_t  NCFSC13:2;         /* Non-critical fault 13 state configuration */
         vuint32_t  NCFSC12:2;         /* Non-critical fault 12 state configuration */
         vuint32_t  NCFSC11:2;         /* Non-critical fault 11 state configuration */
         vuint32_t  NCFSC10:2;         /* Non-critical fault 10 state configuration */
         vuint32_t  NCFSC9:2;          /* Non-critical fault 9 state configuration */
         vuint32_t  NCFSC8:2;          /* Non-critical fault 8 state configuration */
         vuint32_t  NCFSC7:2;          /* Non-critical fault 7 state configuration */
         vuint32_t  NCFSC6:2;          /* Non-critical fault 6 state configuration */
         vuint32_t  NCFSC5:2;          /* Non-critical fault 5 state configuration */
         vuint32_t  NCFSC4:2;          /* Non-critical fault 4 state configuration */
         vuint32_t  NCFSC3:2;          /* Non-critical fault 3 state configuration */
         vuint32_t  NCFSC2:2;          /* Non-critical fault 2 state configuration */
         vuint32_t  NCFSC1:2;          /* Non-critical fault 1 state configuration */
         vuint32_t  NCFSC0:2;          /* Non-critical fault 0 state configuration */
      } B;
   } FCCU_NCFS_CFG0_32B_tag;

   typedef union {   /* FCCU NCFS Configuration Register 1 */
      vuint32_t R;
      struct {
         vuint32_t:14;
         vuint32_t  NCFSC24:2;         /* Non-critical fault 24 state configuration */
         vuint32_t  NCFSC23:2;         /* Non-critical fault 23 state configuration */
         vuint32_t  NCFSC22:2;         /* Non-critical fault 22 state configuration */
         vuint32_t  NCFSC21:2;         /* Non-critical fault 21 state configuration */
         vuint32_t  NCFSC20:2;         /* Non-critical fault 20 state configuration */
         vuint32_t  NCFSC19:2;         /* Non-critical fault 19 state configuration */
         vuint32_t:2;
         vuint32_t  NCFSC17:2;         /* Non-critical fault 17 state configuration */
         vuint32_t  NCFSC16:2;         /* Non-critical fault 16 state configuration */
      } B;
   } FCCU_NCFS_CFG1_32B_tag;

   typedef union {   /* FCCU CF Status Register 0 */
      vuint32_t R;
      struct {
         vuint32_t  CFS31:1;           /* Critical fault 31 status */
         vuint32_t  CFS30:1;           /* Critical fault 30 status */
         vuint32_t  CFS29:1;           /* Critical fault 29 status */
         vuint32_t  CFS28:1;           /* Critical fault 28 status */
         vuint32_t  CFS27:1;           /* Critical fault 27 status */
         vuint32_t:2;
         vuint32_t  CFS24:1;           /* Critical fault 24 status */
         vuint32_t  CFS23:1;           /* Critical fault 23 status */
         vuint32_t  CFS22:1;           /* Critical fault 22 status */
         vuint32_t  CFS21:1;           /* Critical fault 21 status */
         vuint32_t  CFS20:1;           /* Critical fault 20 status */
         vuint32_t  CFS19:1;           /* Critical fault 19 status */
         vuint32_t  CFS18:1;           /* Critical fault 18 status */
         vuint32_t  CFS17:1;           /* Critical fault 17 status */
         vuint32_t  CFS16:1;           /* Critical fault 16 status */
         vuint32_t  CFS15:1;           /* Critical fault 15 status */
         vuint32_t  CFS14:1;           /* Critical fault 14 status */
         vuint32_t:2;
         vuint32_t  CFS11:1;           /* Critical fault 11 status */
         vuint32_t  CFS10:1;           /* Critical fault 10 status */
         vuint32_t  CFS9:1;            /* Critical fault 9 status */
         vuint32_t  CFS8:1;            /* Critical fault 8 status */
         vuint32_t  CFS7:1;            /* Critical fault 7 status */
         vuint32_t  CFS6:1;            /* Critical fault 6 status */
         vuint32_t  CFS5:1;            /* Critical fault 5 status */
         vuint32_t  CFS4:1;            /* Critical fault 4 status */
         vuint32_t  CFS3:1;            /* Critical fault 3 status */
         vuint32_t  CFS2:1;            /* Critical fault 2 status */
         vuint32_t  CFS1:1;            /* Critical fault 1 status */
         vuint32_t  CFS0:1;            /* Critical fault 0 status */
      } B;
   } FCCU_CF_S0_32B_tag;

   typedef union {   /* FCCU CF Status Register 1 */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  CFS47:1;           /* Critical fault 47 status */
         vuint32_t  CFS46:1;           /* Critical fault 46 status */
         vuint32_t  CFS45:1;           /* Critical fault 45 status */
         vuint32_t  CFS44:1;           /* Critical fault 44 status */
         vuint32_t  CFS43:1;           /* Critical fault 43 status */
         vuint32_t:5;
         vuint32_t  CFS37:1;           /* Critical fault 37 status */
         vuint32_t:5;
      } B;
   } FCCU_CF_S1_32B_tag;

   typedef union {   /* FCCU CF Key Register */
      vuint32_t R;
   } FCCU_CFK_32B_tag;

   typedef union {   /* FCCU NCF Status Register 0 */
      vuint32_t R;
      struct {
         vuint32_t:7;
         vuint32_t  NCFS24:1;          /* Non-critical fault 24 status */
         vuint32_t  NCFS23:1;          /* Non-critical fault 23 status */
         vuint32_t  NCFS22:1;          /* Non-critical fault 22 status */
         vuint32_t  NCFS21:1;          /* Non-critical fault 21 status */
         vuint32_t  NCFS20:1;          /* Non-critical fault 20 status */
         vuint32_t  NCFS19:1;          /* Non-critical fault 19 status */
         vuint32_t:1;
         vuint32_t  NCFS17:1;          /* Non-critical fault 17 status */
         vuint32_t  NCFS16:1;          /* Non-critical fault 16 status */
         vuint32_t  NCFS15:1;          /* Non-critical fault 15 status */
         vuint32_t  NCFS14:1;          /* Non-critical fault 14 status */
         vuint32_t  NCFS13:1;          /* Non-critical fault 13 status */
         vuint32_t  NCFS12:1;          /* Non-critical fault 12 status */
         vuint32_t  NCFS11:1;          /* Non-critical fault 11 status */
         vuint32_t  NCFS10:1;          /* Non-critical fault 10 status */
         vuint32_t  NCFS9:1;           /* Non-critical fault 9 status */
         vuint32_t  NCFS8:1;           /* Non-critical fault 8 status */
         vuint32_t  NCFS7:1;           /* Non-critical fault 7 status */
         vuint32_t  NCFS6:1;           /* Non-critical fault 6 status */
         vuint32_t  NCFS5:1;           /* Non-critical fault 5 status */
         vuint32_t  NCFS4:1;           /* Non-critical fault 4 status */
         vuint32_t  NCFS3:1;           /* Non-critical fault 3 status */
         vuint32_t  NCFS2:1;           /* Non-critical fault 2 status */
         vuint32_t  NCFS1:1;           /* Non-critical fault 1 status */
         vuint32_t  NCFS0:1;           /* Non-critical fault 0 status */
      } B;
   } FCCU_NCF_S0_32B_tag;

   typedef union {   /* FCCU NCF Key Register */
      vuint32_t R;
   } FCCU_NCFK_32B_tag;

   typedef union {   /* FCCU NCF Enable Register 0 */
      vuint32_t R;
      struct {
         vuint32_t:7;
         vuint32_t  NCFE24:1;          /* Non-critical fault 24 enable */
         vuint32_t  NCFE23:1;          /* Non-critical fault 23 enable */
         vuint32_t  NCFE22:1;          /* Non-critical fault 22 enable */
         vuint32_t  NCFE21:1;          /* Non-critical fault 21 enable */
         vuint32_t  NCFE20:1;          /* Non-critical fault 20 enable */
         vuint32_t  NCFE19:1;          /* Non-critical fault 19 enable */
         vuint32_t:1;
         vuint32_t  NCFE17:1;          /* Non-critical fault 17 enable */
         vuint32_t  NCFE16:1;          /* Non-critical fault 16 enable */
         vuint32_t  NCFE15:1;          /* Non-critical fault 15 enable */
         vuint32_t  NCFE14:1;          /* Non-critical fault 14 enable */
         vuint32_t  NCFE13:1;          /* Non-critical fault 13 enable */
         vuint32_t  NCFE12:1;          /* Non-critical fault 12 enable */
         vuint32_t  NCFE11:1;          /* Non-critical fault 11 enable */
         vuint32_t  NCFE10:1;          /* Non-critical fault 10 enable */
         vuint32_t  NCFE9:1;           /* Non-critical fault 9 enable */
         vuint32_t  NCFE8:1;           /* Non-critical fault 8 enable */
         vuint32_t  NCFE7:1;           /* Non-critical fault 7 enable */
         vuint32_t  NCFE6:1;           /* Non-critical fault 6 enable */
         vuint32_t  NCFE5:1;           /* Non-critical fault 5 enable */
         vuint32_t  NCFE4:1;           /* Non-critical fault 4 enable */
         vuint32_t  NCFE3:1;           /* Non-critical fault 3 enable */
         vuint32_t  NCFE2:1;           /* Non-critical fault 2 enable */
         vuint32_t  NCFE1:1;           /* Non-critical fault 1 enable */
         vuint32_t  NCFE0:1;           /* Non-critical fault 0 enable */
      } B;
   } FCCU_NCF_E0_32B_tag;

   typedef union {   /* FCCU NCF Time-out Enable Register 0 */
      vuint32_t R;
      struct {
         vuint32_t:7;
         vuint32_t  NCFTOE24:1;        /* Non-critical fault 24 time-out enable */
         vuint32_t  NCFTOE23:1;        /* Non-critical fault 23 time-out enable */
         vuint32_t  NCFTOE22:1;        /* Non-critical fault 22 time-out enable */
         vuint32_t  NCFTOE21:1;        /* Non-critical fault 21 time-out enable */
         vuint32_t  NCFTOE20:1;        /* Non-critical fault 20 time-out enable */
         vuint32_t  NCFTOE19:1;        /* Non-critical fault 19 time-out enable */
         vuint32_t:1;
         vuint32_t  NCFTOE17:1;        /* Non-critical fault 17 time-out enable */
         vuint32_t  NCFTOE16:1;        /* Non-critical fault 16 time-out enable */
         vuint32_t  NCFTOE15:1;        /* Non-critical fault 15 time-out enable */
         vuint32_t  NCFTOE14:1;        /* Non-critical fault 14 time-out enable */
         vuint32_t  NCFTOE13:1;        /* Non-critical fault 13 time-out enable */
         vuint32_t  NCFTOE12:1;        /* Non-critical fault 12 time-out enable */
         vuint32_t  NCFTOE11:1;        /* Non-critical fault 11 time-out enable */
         vuint32_t  NCFTOE10:1;        /* Non-critical fault 10 time-out enable */
         vuint32_t  NCFTOE9:1;         /* Non-critical fault 9 time-out enable */
         vuint32_t  NCFTOE8:1;         /* Non-critical fault 8 time-out enable */
         vuint32_t  NCFTOE7:1;         /* Non-critical fault 7 time-out enable */
         vuint32_t  NCFTOE6:1;         /* Non-critical fault 6 time-out enable */
         vuint32_t  NCFTOE5:1;         /* Non-critical fault 5 time-out enable */
         vuint32_t  NCFTOE4:1;         /* Non-critical fault 4 time-out enable */
         vuint32_t  NCFTOE3:1;         /* Non-critical fault 3 time-out enable */
         vuint32_t  NCFTOE2:1;         /* Non-critical fault 2 time-out enable */
         vuint32_t  NCFTOE1:1;         /* Non-critical fault 1 time-out enable */
         vuint32_t  NCFTOE0:1;         /* Non-critical fault 0 time-out enable */
      } B;
   } FCCU_NCF_TOE0_32B_tag;

   typedef union {   /* FCCU NCF Time-out Register */
      vuint32_t R;
   } FCCU_NCF_TO_32B_tag;

   typedef union {   /* FCCU CFG Timeout Register */
      vuint32_t R;
      struct {
         vuint32_t:29;
         vuint32_t  TO:3;              /* Configuration time-out */
      } B;
   } FCCU_CFG_TO_32B_tag;

   typedef union {   /* FCCU IO Control Register */
      vuint32_t R;
      struct {
         vuint32_t:26;
         vuint32_t  EIN1:1;            /* Error input 1 */
         vuint32_t  EIN0:1;            /* Error input 0 */
         vuint32_t:2;
         vuint32_t  EOUT1:1;           /* Error out 1 */
         vuint32_t  EOUT0:1;           /* Error out 0 */
      } B;
   } FCCU_EINOUT_32B_tag;

   typedef union {   /* FCCU Status Register */
      vuint32_t R;
      struct {
         vuint32_t:29;
         vuint32_t  STATUS:3;          /* FCCU status */
      } B;
   } FCCU_STAT_32B_tag;

   typedef union {   /* FCCU SC Freeze Status Register */
      vuint32_t R;
      struct {
         vuint32_t:30;
         vuint32_t  RCCS1:1;           /* RCC1 Status */
         vuint32_t  RCCS0:1;           /* RCC0 Status */
      } B;
   } FCCU_SCFS_32B_tag;

   typedef union {   /* FCCU CF Fake Register */
      vuint32_t R;
      struct {
         vuint32_t:25;
         vuint32_t  FCFC:7;            /* Fake Critical fault code */
      } B;
   } FCCU_CFF_32B_tag;

   typedef union {   /* FCCU NCF Fake Register */
      vuint32_t R;
      struct {
         vuint32_t:25;
         vuint32_t  FNCFC:7;           /* Fake Non-critical fault code */
      } B;
   } FCCU_NCFF_32B_tag;

   typedef union {   /* FCCU IRQ Status Register */
      vuint32_t R;
      struct {
         vuint32_t:29;
         vuint32_t  NMI_STAT:1;        /* NMI Interrupt Status */
         vuint32_t  ALRM_STAT:1;       /* Alarm Interrupt Status */
         vuint32_t  CFG_TO_STAT:1;     /* Configuration Time-out Status */
      } B;
   } FCCU_IRQ_STAT_32B_tag;

   typedef union {   /* FCCU IRQ Enable Register */
      vuint32_t R;
      struct {
         vuint32_t:31;
         vuint32_t  CFG_TO_IEN:1;      /* Configuration Time-out Interrupt Enable */
      } B;
   } FCCU_IRQ_EN_32B_tag;

   typedef union {   /* FCCU XTMR Register */
      vuint32_t R;
      struct {
         vuint32_t  XTMR_XTMR:32;      /* Alarm/Watchdog/Safe mode request timer */
      } B;
   } FCCU_XTMR_32B_tag;

   typedef union {   /* FCCU_MCS - FCCU MCS Register */
      vuint32_t R;
      struct {
         vuint32_t  VL3:1;             /* Valid */
         vuint32_t  FS3:1;             /* Fault Status */
         vuint32_t:2;
         vuint32_t  MCS3:4;            /* Magic Carpet oldest state */
         vuint32_t  VL2:1;             /* Valid */
         vuint32_t  FS2:1;             /* Fault Status */
         vuint32_t:2;
         vuint32_t  MCS2:4;            /* Magic Carpet previous-previous state */
         vuint32_t  VL1:1;             /* Valid */
         vuint32_t  FS1:1;             /* Fault Status */
         vuint32_t:2;
         vuint32_t  MCS1:4;            /* Magic Carpet previous state */
         vuint32_t  VL0:1;             /* Valid */
         vuint32_t  FS0:1;             /* Fault Status */
         vuint32_t:2;
         vuint32_t  MCS0:4;            /* Magic Carpet latest state */
      } B;
   } FCCU_MCS_32B_tag;


   /* Register layout for generated register(s) CF_CFG... */

   typedef union {   /*  */
      vuint32_t R;
   } FCCU_CF_CFG_32B_tag;


   /* Register layout for generated register(s) NCF_CFG... */

   typedef union {   /*  */
      vuint32_t R;
   } FCCU_NCF_CFG_32B_tag;


   /* Register layout for generated register(s) CFS_CFG... */

   typedef union {   /*  */
      vuint32_t R;
   } FCCU_CFS_CFG_32B_tag;


   /* Register layout for generated register(s) NCFS_CFG... */

   typedef union {   /*  */
      vuint32_t R;
   } FCCU_NCFS_CFG_32B_tag;


   /* Register layout for generated register(s) CF_S... */

   typedef union {   /*  */
      vuint32_t R;
   } FCCU_CF_S_32B_tag;


   /* Register layout for generated register(s) NCF_S... */

   typedef union {   /*  */
      vuint32_t R;
   } FCCU_NCF_S_32B_tag;


   /* Register layout for generated register(s) NCF_E... */

   typedef union {   /*  */
      vuint32_t R;
   } FCCU_NCF_E_32B_tag;


   /* Register layout for generated register(s) NCF_TOE... */

   typedef union {   /*  */
      vuint32_t R;
   } FCCU_NCF_TOE_32B_tag;


   typedef struct FCCU_struct_tag {

                                                /* FCCU Control Register */
      FCCU_CTRL_32B_tag CTRL;              /* offset: 0x0000 size: 32 bit */
                                               /* FCCU CTRL Key Register */
      FCCU_CTRLK_32B_tag CTRLK;            /* offset: 0x0004 size: 32 bit */
                                          /* FCCU Configuration Register */
      FCCU_CFG_32B_tag CFG;                /* offset: 0x0008 size: 32 bit */
      union {
         FCCU_CF_CFG_32B_tag CF_CFG[4];    /* offset: 0x000C  (0x0004 x 4) */

         struct {
                                     /* FCCU CF Configuration Register 0 */
            FCCU_CF_CFG0_32B_tag CF_CFG0;  /* offset: 0x000C size: 32 bit */
                                     /* FCCU CF Configuration Register 1 */
            FCCU_CF_CFG1_32B_tag CF_CFG1;  /* offset: 0x0010 size: 32 bit */
            int8_t FCCU_reserved_0014_E1[8];
         };

      };
      union {
         FCCU_NCF_CFG_32B_tag NCF_CFG[4];  /* offset: 0x001C  (0x0004 x 4) */

         struct {
                                    /* FCCU NCF Configuration Register 0 */
            FCCU_NCF_CFG0_32B_tag NCF_CFG0;  /* offset: 0x001C size: 32 bit */
            int8_t FCCU_reserved_0020_E1[12];
         };

      };
      union {
         FCCU_CFS_CFG_32B_tag CFS_CFG[8];  /* offset: 0x002C  (0x0004 x 8) */

         struct {
                                    /* FCCU CFS Configuration Register 0 */
            FCCU_CFS_CFG0_32B_tag CFS_CFG0;  /* offset: 0x002C size: 32 bit */
                                    /* FCCU CFS Configuration Register 1 */
            FCCU_CFS_CFG1_32B_tag CFS_CFG1;  /* offset: 0x0030 size: 32 bit */
                                    /* FCCU CFS Configuration Register 2 */
            FCCU_CFS_CFG2_32B_tag CFS_CFG2;  /* offset: 0x0034 size: 32 bit */
            int8_t FCCU_reserved_0038_E1[20];
         };

      };
      union {
         FCCU_NCFS_CFG_32B_tag NCFS_CFG[8];  /* offset: 0x004C  (0x0004 x 8) */

         struct {
                                   /* FCCU NCFS Configuration Register 0 */
            FCCU_NCFS_CFG0_32B_tag NCFS_CFG0;  /* offset: 0x004C size: 32 bit */
                                   /* FCCU NCFS Configuration Register 1 */
            FCCU_NCFS_CFG1_32B_tag NCFS_CFG1;  /* offset: 0x0050 size: 32 bit */
            int8_t FCCU_reserved_0054_E1[24];
         };

      };
      union {
         FCCU_CF_S_32B_tag CF_S[4];        /* offset: 0x006C  (0x0004 x 4) */

         struct {
                                            /* FCCU CF Status Register 0 */
            FCCU_CF_S0_32B_tag CF_S0;      /* offset: 0x006C size: 32 bit */
                                            /* FCCU CF Status Register 1 */
            FCCU_CF_S1_32B_tag CF_S1;      /* offset: 0x0070 size: 32 bit */
            int8_t FCCU_reserved_0074_E1[8];
         };

      };
                                                 /* FCCU CF Key Register */
      FCCU_CFK_32B_tag CFK;                /* offset: 0x007C size: 32 bit */
      union {
         FCCU_NCF_S_32B_tag NCF_S[4];      /* offset: 0x0080  (0x0004 x 4) */

         struct {
                                           /* FCCU NCF Status Register 0 */
            FCCU_NCF_S0_32B_tag NCF_S0;    /* offset: 0x0080 size: 32 bit */
            int8_t FCCU_reserved_0084_E1[12];
         };

      };
                                                /* FCCU NCF Key Register */
      FCCU_NCFK_32B_tag NCFK;              /* offset: 0x0090 size: 32 bit */
      union {
         FCCU_NCF_E_32B_tag NCF_E[4];      /* offset: 0x0094  (0x0004 x 4) */

         struct {
                                           /* FCCU NCF Enable Register 0 */
            FCCU_NCF_E0_32B_tag NCF_E0;    /* offset: 0x0094 size: 32 bit */
            int8_t FCCU_reserved_0098_E1[12];
         };

      };
      union {
         FCCU_NCF_TOE_32B_tag NCF_TOE[4];  /* offset: 0x00A4  (0x0004 x 4) */

         struct {
                                  /* FCCU NCF Time-out Enable Register 0 */
            FCCU_NCF_TOE0_32B_tag NCF_TOE0;  /* offset: 0x00A4 size: 32 bit */
            int8_t FCCU_reserved_00A8_E1[12];
         };

      };
                                           /* FCCU NCF Time-out Register */
      FCCU_NCF_TO_32B_tag NCF_TO;          /* offset: 0x00B4 size: 32 bit */
                                            /* FCCU CFG Timeout Register */
      FCCU_CFG_TO_32B_tag CFG_TO;          /* offset: 0x00B8 size: 32 bit */
                                             /* FCCU IO Control Register */
      FCCU_EINOUT_32B_tag EINOUT;          /* offset: 0x00BC size: 32 bit */
                                                 /* FCCU Status Register */
      FCCU_STAT_32B_tag STAT;              /* offset: 0x00C0 size: 32 bit */
      int8_t FCCU_reserved_00C4[16];
                                       /* FCCU SC Freeze Status Register */
      FCCU_SCFS_32B_tag SCFS;              /* offset: 0x00D4 size: 32 bit */
                                                /* FCCU CF Fake Register */
      FCCU_CFF_32B_tag CFF;                /* offset: 0x00D8 size: 32 bit */
                                               /* FCCU NCF Fake Register */
      FCCU_NCFF_32B_tag NCFF;              /* offset: 0x00DC size: 32 bit */
                                             /* FCCU IRQ Status Register */
      FCCU_IRQ_STAT_32B_tag IRQ_STAT;      /* offset: 0x00E0 size: 32 bit */
                                             /* FCCU IRQ Enable Register */
      FCCU_IRQ_EN_32B_tag IRQ_EN;          /* offset: 0x00E4 size: 32 bit */
                                                   /* FCCU XTMR Register */
      FCCU_XTMR_32B_tag XTMR;              /* offset: 0x00E8 size: 32 bit */
                                         /* FCCU_MCS - FCCU MCS Register */
      FCCU_MCS_32B_tag MCS;                /* offset: 0x00EC size: 32 bit */
      int8_t FCCU_reserved_00F0[16144];

   } FCCU_tag;


#define FCCU_BASEADDRESS 0xFFE6C000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define FCCU  (*(volatile FCCU_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE6C000UL))



/****************************************************************/
/*                                                              */
/* Module: SWG  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Control Register */
      vuint32_t R;
      struct {
         vuint32_t  LDOS:1;            /* Load on Set Status */
         vuint32_t  NRO:1;             /* Noise reduction enable */
         vuint32_t  IOAMPL:4;          /* Define the AMPLitude value on I/O pad */
         vuint32_t:2;
         vuint32_t  SEMASK:1;          /* Sine wave generator Error MASK interrupt register */
         vuint32_t:5;
         vuint32_t  S0H1:1;            /* Operation Status: enter PD in Stop Mode */
         vuint32_t  PDS:1;             /* Operation Status: Power Down Mode */
         vuint32_t  IOFREQ:16;         /* Define the frequency value on I/O pad */
      } B;
   } SWG_CTRL_32B_tag;

   typedef union {   /* Status Register */
      vuint32_t R;
      struct {
         vuint32_t:8;
         vuint32_t  SERR:1;            /* Sine wave generator Status Error */
         vuint32_t:3;
         vuint32_t  FERR:1;            /* Sine wave generator Force Error bit */
         vuint32_t:19;
      } B;
   } SWG_STAT_32B_tag;


   typedef struct SWG_struct_tag {

                                                     /* Control Register */
      SWG_CTRL_32B_tag CTRL;               /* offset: 0x0000 size: 32 bit */
                                                      /* Status Register */
      SWG_STAT_32B_tag STAT;               /* offset: 0x0004 size: 32 bit */
      int8_t SWG_reserved_0008[16376];

   } SWG_tag;


#define SWG_BASEADDRESS 0xFFE78000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define SWG   (*(volatile SWG_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE78000UL))



/****************************************************************/
/*                                                              */
/* Module: SEMA4  */
/*                                                              */
/****************************************************************/


   /* Register layout for all registers GATE ... */

   typedef union {   /* Semaphores Gate n Register */
      vuint8_t R;
      struct {
         vuint8_t:6;
         vuint8_t   GTFSM:2;           /* Gate Finite State machine */
      } B;
   } SEMA4_GATE_8B_tag;

   typedef union {   /* Semaphores Processor n IRQ Notification Enable */
      vuint16_t R;
      struct {
         vuint16_t  INE:16;            /* Interrupt Request Notification Enable n */
      } B;
   } SEMA4_CPINE_16B_tag;

   typedef union {   /* Semaphores Processor n IRQ Notification */
      vuint16_t R;
      struct {
         vuint16_t  GN:16;             /* Gate n Notification */
      } B;
   } SEMA4_CPNTF_16B_tag;

   typedef union {   /* Semaphores (secure) reset gate n (read) */
      vuint16_t R;
      struct {
         vuint16_t:2;
         vuint16_t  RSTGSM:2;          /* Reset Gate Finite State Machine */
         vuint16_t:1;
         vuint16_t  RSTGMS:3;          /* Reset Gate Bus Master */
         vuint16_t  RSTGTN:8;          /* Reset Gate Number */
      } B;
   } SEMA4_RSTGT_16B_tag;

   typedef union {   /* Semaphores (secure) reset gate n (write) */
      vuint16_t R;
      struct {
         vuint16_t:1;
         vuint16_t  RSTGDP:7;          /* Reset Gate Data Pattern; 0xE2 first, 0x1D second */
         vuint16_t  RSTGTN:8;          /* Reset Gate Number; only relevant for second write */
      } B;
   } SEMA4_RSTGT_WRITE_16B_tag;

   typedef union {   /* Semaphores (secure) reset IRQ notification (read) */
      vuint16_t R;
      struct {
         vuint16_t:2;
         vuint16_t  RSTNSM:2;          /* Reset Gate Finite State Machine */
         vuint16_t:1;
         vuint16_t  RSTNMS:3;          /* Reset Gate Bus Master */
         vuint16_t  RSTNTN:8;          /* Reset Gate Number */
      } B;
   } SEMA4_RSTNTF_16B_tag;

   typedef union {   /* Semaphores (secure) reset IRQ notification (write) */
      vuint16_t R;
      struct {
         vuint16_t:1;
         vuint16_t  RSTNDP:7;          /* Reset Gate Data Pattern; 0x47 first, 0xB8 second */
         vuint16_t  RSTNTN:8;          /* Reset Gate Number; only relevant for second write */
      } B;
   } SEMA4_RSTNTF_WRITE_16B_tag;


   typedef struct SEMA4_struct_tag {

      union {
                                           /* Semaphores Gate n Register */
         SEMA4_GATE_8B_tag GATE[16];       /* offset: 0x0000  (0x0001 x 16) */

         struct {
                                           /* Semaphores Gate n Register */
            SEMA4_GATE_8B_tag GATE0;       /* offset: 0x0000 size: 8 bit */
            SEMA4_GATE_8B_tag GATE1;       /* offset: 0x0001 size: 8 bit */
            SEMA4_GATE_8B_tag GATE2;       /* offset: 0x0002 size: 8 bit */
            SEMA4_GATE_8B_tag GATE3;       /* offset: 0x0003 size: 8 bit */
            SEMA4_GATE_8B_tag GATE4;       /* offset: 0x0004 size: 8 bit */
            SEMA4_GATE_8B_tag GATE5;       /* offset: 0x0005 size: 8 bit */
            SEMA4_GATE_8B_tag GATE6;       /* offset: 0x0006 size: 8 bit */
            SEMA4_GATE_8B_tag GATE7;       /* offset: 0x0007 size: 8 bit */
            SEMA4_GATE_8B_tag GATE8;       /* offset: 0x0008 size: 8 bit */
            SEMA4_GATE_8B_tag GATE9;       /* offset: 0x0009 size: 8 bit */
            SEMA4_GATE_8B_tag GATE10;      /* offset: 0x000A size: 8 bit */
            SEMA4_GATE_8B_tag GATE11;      /* offset: 0x000B size: 8 bit */
            SEMA4_GATE_8B_tag GATE12;      /* offset: 0x000C size: 8 bit */
            SEMA4_GATE_8B_tag GATE13;      /* offset: 0x000D size: 8 bit */
            SEMA4_GATE_8B_tag GATE14;      /* offset: 0x000E size: 8 bit */
            SEMA4_GATE_8B_tag GATE15;      /* offset: 0x000F size: 8 bit */
         };

      };
      int8_t SEMA4_reserved_0010[48];
                       /* Semaphores Processor n IRQ Notification Enable */
      SEMA4_CPINE_16B_tag CP0INE;          /* offset: 0x0040 size: 16 bit */
      int8_t SEMA4_reserved_0042[6];
                       /* Semaphores Processor n IRQ Notification Enable */
      SEMA4_CPINE_16B_tag CP1INE;          /* offset: 0x0048 size: 16 bit */
      int8_t SEMA4_reserved_004A[54];
                              /* Semaphores Processor n IRQ Notification */
      SEMA4_CPNTF_16B_tag CP0NTF;          /* offset: 0x0080 size: 16 bit */
      int8_t SEMA4_reserved_0082[6];
                              /* Semaphores Processor n IRQ Notification */
      SEMA4_CPNTF_16B_tag CP1NTF;          /* offset: 0x0088 size: 16 bit */
      int8_t SEMA4_reserved_008A[118];
      union {
                             /* Semaphores (secure) reset gate n (write) */
         SEMA4_RSTGT_WRITE_16B_tag RSTGT_WRITE;  /* offset: 0x0100 size: 16 bit */

                              /* Semaphores (secure) reset gate n (read) */
         SEMA4_RSTGT_16B_tag RSTGT;        /* offset: 0x0100 size: 16 bit */

      };
      int8_t SEMA4_reserved_0102[2];
      union {
                   /* Semaphores (secure) reset IRQ notification (write) */
         SEMA4_RSTNTF_WRITE_16B_tag RSTNTF_WRITE;  /* offset: 0x0104 size: 16 bit */

                    /* Semaphores (secure) reset IRQ notification (read) */
         SEMA4_RSTNTF_16B_tag RSTNTF;      /* offset: 0x0104 size: 16 bit */

      };
      int8_t SEMA4_reserved_0106[16122];

   } SEMA4_tag;


#define SEMA4_BASEADDRESS 0xFFF24000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define SEMA4 (*(volatile SEMA4_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFF24000UL))



/****************************************************************/
/*                                                              */
/* Module: PFLASH2P  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Platform Flash Configuration Register 0 */
      vuint32_t R;
      struct {
         vuint32_t:2;
         vuint32_t  B02_APC:3;         /* Bank0+2 Address Pipelining Control */
         vuint32_t:3;
         vuint32_t  B02_WWSC:2;        /* Bank0+2 Write Wait State Control */
         vuint32_t:2;
         vuint32_t  B02_RWSC:3;        /* Bank0+2 Read Wait State Control */
         vuint32_t:2;
         vuint32_t  B02_P1_BCFG:2;     /* Bank0+2 Port 1 Page Buffer Configuration */
         vuint32_t  B02_P1_DPFE:1;     /* Bank0+2 Port 1 Data Prefetch Enable */
         vuint32_t  B02_P1_IPFE:1;     /* Bank0+2 Port 1 Inst Prefetch Enable */
         vuint32_t  B02_P1_PFLM:2;     /* Bank0+2 Port 1 Prefetch Limit */
         vuint32_t  B02_P1_BFE:1;      /* Bank0+2 Port 1 Buffer Enable */
         vuint32_t:1;
         vuint32_t  B02_P0_BCFG:2;     /* Bank0+2 Port 0 Page Buffer Configuration */
         vuint32_t  B02_P0_DPFE:1;     /* Bank0+2 Port 0 Data Prefetch Enable */
         vuint32_t  B02_P0_IPFE:1;     /* Bank0+2 Port 0 Inst Prefetch Enable */
         vuint32_t  B02_P0_PFLM:2;     /* Bank0+2 Port 0 Prefetch Limit */
         vuint32_t  B02_P0_BFE:1;      /* Bank0+2 Port 0 Buffer Enable */
      } B;
   } PFLASH2P_PFCR0_32B_tag;

   typedef union {   /* Platform Flash Access Protection Register */
      vuint32_t R;
      struct {
         vuint32_t:6;
         vuint32_t  ARBM:2;            /* Arbitration Mode */
         vuint32_t:1;
         vuint32_t  M6PFD:1;           /* Master x Prefetch Disable */
         vuint32_t  M5PFD:1;           /* Master x Prefetch Disable */
         vuint32_t:1;
         vuint32_t  M3PFD:1;           /* Master x Prefetch Disable */
         vuint32_t  M2PFD:1;           /* Master x Prefetch Disable */
         vuint32_t  M1PFD:1;           /* Master x Prefetch Disable */
         vuint32_t  M0PFD:1;           /* Master x Prefetch Disable */
         vuint32_t:2;
         vuint32_t  M6AP:2;            /* Master 6 Access Protection */
         vuint32_t  M5AP:2;            /* Master 5 Access Protection */
         vuint32_t:2;
         vuint32_t  M3AP:2;            /* Master 3 Access Protection */
         vuint32_t  M2AP:2;            /* Master 2 Access Protection */
         vuint32_t  M1AP:2;            /* Master 1 Access Protection */
         vuint32_t  M0AP:2;            /* Master 0 Access Protection */
      } B;
   } PFLASH2P_PFAPR_32B_tag;


   typedef struct PFLASH2P_struct_tag {

      int8_t PFLASH2P_reserved_0000[28];
                              /* Platform Flash Configuration Register 0 */
      PFLASH2P_PFCR0_32B_tag PFCR0;        /* offset: 0x001C size: 32 bit */
      int8_t PFLASH2P_reserved_0020[4];
                            /* Platform Flash Access Protection Register */
      PFLASH2P_PFAPR_32B_tag PFAPR;        /* offset: 0x0024 size: 32 bit */
      int8_t PFLASH2P_reserved_0028[16344];

   } PFLASH2P_tag;


#define PFLASH2P_BASEADDRESS 0xFFE88000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define PFLASH2P (*(volatile PFLASH2P_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFE88000UL))



/****************************************************************/
/*                                                              */
/* Module: PBRIDGE  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Master Privilege Registers */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  MPROT0_MTR:1;      /* Master Trusted for Reads */
         vuint32_t  MPROT0_MTW:1;      /* Master Trusted for Writes */
         vuint32_t  MPROT0_MPL:1;      /* Master Priviledge Level */
         vuint32_t:1;
         vuint32_t  MPROT1_MTR:1;      /* Master Trusted for Reads */
         vuint32_t  MPROT1_MTW:1;      /* Master Trusted for Writes */
         vuint32_t  MPROT1_MPL:1;      /* Master Priviledge Level */
         vuint32_t:1;
         vuint32_t  MPROT2_MTR:1;      /* Master Trusted for Reads */
         vuint32_t  MPROT2_MTW:1;      /* Master Trusted for Writes */
         vuint32_t  MPROT2_MPL:1;      /* Master Priviledge Level */
         vuint32_t:1;
         vuint32_t  MPROT3_MTR:1;      /* Master Trusted for Reads */
         vuint32_t  MPROT3_MTW:1;      /* Master Trusted for Writes */
         vuint32_t  MPROT3_MPL:1;      /* Master Priviledge Level */
         vuint32_t:9;
         vuint32_t  MPROT6_MTR:1;      /* Master Trusted for Reads */
         vuint32_t  MPROT6_MTW:1;      /* Master Trusted for Writes */
         vuint32_t  MPROT6_MPL:1;      /* Master Priviledge Level */
         vuint32_t:4;
      } B;
   } PBRIDGE_MPROT0_7_32B_tag;

   typedef union {   /* Master Privilege Registers */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  MPROT8_MTR:1;      /* Master Trusted for Reads */
         vuint32_t  MPROT8_MTW:1;      /* Master Trusted for Writes */
         vuint32_t  MPROT8_MPL:1;      /* Master Priviledge Level */
         vuint32_t:1;
         vuint32_t  MPROT9_MTR:1;      /* Master Trusted for Reads */
         vuint32_t  MPROT9_MTW:1;      /* Master Trusted for Writes */
         vuint32_t  MPROT9_MPL:1;      /* Master Priviledge Level */
         vuint32_t:24;
      } B;
   } PBRIDGE_MPROT8_15_32B_tag;

   typedef union {   /* On-Platform Peripheral Access Control Registers */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  PACR0_SP:1;        /* Supervisor Protect */
         vuint32_t  PACR0_WP:1;        /* Write Protect */
         vuint32_t  PACR0_TP:1;        /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  PACR1_SP:1;        /* Supervisor Protect */
         vuint32_t  PACR1_WP:1;        /* Write Protect */
         vuint32_t  PACR1_TP:1;        /* Trusted Protect */
         vuint32_t:9;
         vuint32_t  PACR4_SP:1;        /* Supervisor Protect */
         vuint32_t  PACR4_WP:1;        /* Write Protect */
         vuint32_t  PACR4_TP:1;        /* Trusted Protect */
         vuint32_t:12;
      } B;
   } PBRIDGE_PACR0_7_32B_tag;

   typedef union {   /* On-Platform Peripheral Access Control Registers */
      vuint32_t R;
      struct {
         vuint32_t:5;
         vuint32_t  PACR9_SP:1;        /* Supervisor Protect */
         vuint32_t  PACR9_WP:1;        /* Write Protect */
         vuint32_t  PACR9_TP:1;        /* Trusted Protect */
         vuint32_t:17;
         vuint32_t  PACR14_SP:1;       /* Supervisor Protect */
         vuint32_t  PACR14_WP:1;       /* Write Protect */
         vuint32_t  PACR14_TP:1;       /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  PACR15_SP:1;       /* Supervisor Protect */
         vuint32_t  PACR15_WP:1;       /* Write Protect */
         vuint32_t  PACR15_TP:1;       /* Trusted Protect */
      } B;
   } PBRIDGE_PACR8_15_32B_tag;

   typedef union {   /* On-Platform Peripheral Access Control Registers */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  PACR16_SP:1;       /* Supervisor Protect */
         vuint32_t  PACR16_WP:1;       /* Write Protect */
         vuint32_t  PACR16_TP:1;       /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  PACR17_SP:1;       /* Supervisor Protect */
         vuint32_t  PACR17_WP:1;       /* Write Protect */
         vuint32_t  PACR17_TP:1;       /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  PACR18_SP:1;       /* Supervisor Protect */
         vuint32_t  PACR18_WP:1;       /* Write Protect */
         vuint32_t  PACR18_TP:1;       /* Trusted Protect */
         vuint32_t:20;
      } B;
   } PBRIDGE_PACR16_23_32B_tag;

   typedef union {   /* Off-Platform Peripheral Access Control Registers */
      vuint32_t R;
      struct {
         vuint32_t:17;
         vuint32_t  OPACR4_SP:1;       /* Supervisor Protect */
         vuint32_t  OPACR4_WP:1;       /* Write Protect */
         vuint32_t  OPACR4_TP:1;       /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  OPACR5_SP:1;       /* Supervisor Protect */
         vuint32_t  OPACR5_WP:1;       /* Write Protect */
         vuint32_t  OPACR5_TP:1;       /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  OPACR6_SP:1;       /* Supervisor Protect */
         vuint32_t  OPACR6_WP:1;       /* Write Protect */
         vuint32_t  OPACR6_TP:1;       /* Trusted Protect */
         vuint32_t:4;
      } B;
   } PBRIDGE_OPACR0_7_32B_tag;

   typedef union {   /* Off-Platform Peripheral Access Control Registers */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  OPACR16_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR16_WP:1;      /* Write Protect */
         vuint32_t  OPACR16_TP:1;      /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  OPACR17_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR17_WP:1;      /* Write Protect */
         vuint32_t  OPACR17_TP:1;      /* Trusted Protect */
         vuint32_t:21;
         vuint32_t  OPACR23_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR23_WP:1;      /* Write Protect */
         vuint32_t  OPACR23_TP:1;      /* Trusted Protect */
      } B;
   } PBRIDGE_OPACR16_23_32B_tag;

   typedef union {   /* Off-Platform Peripheral Access Control Registers */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  OPACR24_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR24_WP:1;      /* Write Protect */
         vuint32_t  OPACR24_TP:1;      /* Trusted Protect */
         vuint32_t:25;
         vuint32_t  OPACR31_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR31_WP:1;      /* Write Protect */
         vuint32_t  OPACR31_TP:1;      /* Trusted Protect */
      } B;
   } PBRIDGE_OPACR24_31_32B_tag;

   typedef union {   /* Off-Platform Peripheral Access Control Registers */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  OPACR32_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR32_WP:1;      /* Write Protect */
         vuint32_t  OPACR32_TP:1;      /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  OPACR33_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR33_WP:1;      /* Write Protect */
         vuint32_t  OPACR33_TP:1;      /* Trusted Protect */
         vuint32_t:5;
         vuint32_t  OPACR35_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR35_WP:1;      /* Write Protect */
         vuint32_t  OPACR35_TP:1;      /* Trusted Protect */
         vuint32_t:9;
         vuint32_t  OPACR38_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR38_WP:1;      /* Write Protect */
         vuint32_t  OPACR38_TP:1;      /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  OPACR39_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR39_WP:1;      /* Write Protect */
         vuint32_t  OPACR39_TP:1;      /* Trusted Protect */
      } B;
   } PBRIDGE_OPACR32_39_32B_tag;

   typedef union {   /* Off-Platform Peripheral Access Control Registers */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  OPACR40_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR40_WP:1;      /* Write Protect */
         vuint32_t  OPACR40_TP:1;      /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  OPACR41_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR41_WP:1;      /* Write Protect */
         vuint32_t  OPACR41_TP:1;      /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  OPACR42_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR42_WP:1;      /* Write Protect */
         vuint32_t  OPACR42_TP:1;      /* Trusted Protect */
         vuint32_t:20;
      } B;
   } PBRIDGE_OPACR40_47_32B_tag;

   typedef union {   /* Off-Platform Peripheral Access Control Registers */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  OPACR48_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR48_WP:1;      /* Write Protect */
         vuint32_t  OPACR48_TP:1;      /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  OPACR49_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR49_WP:1;      /* Write Protect */
         vuint32_t  OPACR49_TP:1;      /* Trusted Protect */
         vuint32_t:24;
      } B;
   } PBRIDGE_OPACR48_55_32B_tag;

   typedef union {   /* Off-Platform Peripheral Access Control Registers */
      vuint32_t R;
      struct {
         vuint32_t:9;
         vuint32_t  OPACR58_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR58_WP:1;      /* Write Protect */
         vuint32_t  OPACR58_TP:1;      /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  OPACR59_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR59_WP:1;      /* Write Protect */
         vuint32_t  OPACR59_TP:1;      /* Trusted Protect */
         vuint32_t:9;
         vuint32_t  OPACR62_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR62_WP:1;      /* Write Protect */
         vuint32_t  OPACR62_TP:1;      /* Trusted Protect */
         vuint32_t:4;
      } B;
   } PBRIDGE_OPACR56_63_32B_tag;

   typedef union {   /* Off-Platform Peripheral Access Control Registers */
      vuint32_t R;
      struct {
         vuint32_t:9;
         vuint32_t  OPACR66_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR66_WP:1;      /* Write Protect */
         vuint32_t  OPACR66_TP:1;      /* Trusted Protect */
         vuint32_t:5;
         vuint32_t  OPACR68_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR68_WP:1;      /* Write Protect */
         vuint32_t  OPACR68_TP:1;      /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  OPACR69_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR69_WP:1;      /* Write Protect */
         vuint32_t  OPACR69_TP:1;      /* Trusted Protect */
         vuint32_t:8;
      } B;
   } PBRIDGE_OPACR64_71_32B_tag;

   typedef union {   /* Off-Platform Peripheral Access Control Registers */
      vuint32_t R;
      struct {
         vuint32_t:25;
         vuint32_t  OPACR86_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR86_WP:1;      /* Write Protect */
         vuint32_t  OPACR86_TP:1;      /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  OPACR87_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR87_WP:1;      /* Write Protect */
         vuint32_t  OPACR87_TP:1;      /* Trusted Protect */
      } B;
   } PBRIDGE_OPACR80_87_32B_tag;

   typedef union {   /* Off-Platform Peripheral Access Control Registers */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  OPACR88_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR88_WP:1;      /* Write Protect */
         vuint32_t  OPACR88_TP:1;      /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  OPACR89_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR89_WP:1;      /* Write Protect */
         vuint32_t  OPACR89_TP:1;      /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  OPACR90_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR90_WP:1;      /* Write Protect */
         vuint32_t  OPACR90_TP:1;      /* Trusted Protect */
         vuint32_t:5;
         vuint32_t  OPACR92_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR92_WP:1;      /* Write Protect */
         vuint32_t  OPACR92_TP:1;      /* Trusted Protect */
         vuint32_t:1;
         vuint32_t  OPACR93_SP:1;      /* Supervisor Protect */
         vuint32_t  OPACR93_WP:1;      /* Write Protect */
         vuint32_t  OPACR93_TP:1;      /* Trusted Protect */
         vuint32_t:8;
      } B;
   } PBRIDGE_OPACR88_95_32B_tag;


   typedef struct PBRIDGE_struct_tag {

                                           /* Master Privilege Registers */
      PBRIDGE_MPROT0_7_32B_tag MPROT0_7;   /* offset: 0x0000 size: 32 bit */
                                           /* Master Privilege Registers */
      PBRIDGE_MPROT8_15_32B_tag MPROT8_15;  /* offset: 0x0004 size: 32 bit */
      int8_t PBRIDGE_reserved_0008[24];
                      /* On-Platform Peripheral Access Control Registers */
      PBRIDGE_PACR0_7_32B_tag PACR0_7;     /* offset: 0x0020 size: 32 bit */
                      /* On-Platform Peripheral Access Control Registers */
      PBRIDGE_PACR8_15_32B_tag PACR8_15;   /* offset: 0x0024 size: 32 bit */
                      /* On-Platform Peripheral Access Control Registers */
      PBRIDGE_PACR16_23_32B_tag PACR16_23;  /* offset: 0x0028 size: 32 bit */
      int8_t PBRIDGE_reserved_002C[20];
                     /* Off-Platform Peripheral Access Control Registers */
      PBRIDGE_OPACR0_7_32B_tag OPACR0_7;   /* offset: 0x0040 size: 32 bit */
      int8_t PBRIDGE_reserved_0044[4];
                     /* Off-Platform Peripheral Access Control Registers */
      PBRIDGE_OPACR16_23_32B_tag OPACR16_23;  /* offset: 0x0048 size: 32 bit */
                     /* Off-Platform Peripheral Access Control Registers */
      PBRIDGE_OPACR24_31_32B_tag OPACR24_31;  /* offset: 0x004C size: 32 bit */
                     /* Off-Platform Peripheral Access Control Registers */
      PBRIDGE_OPACR32_39_32B_tag OPACR32_39;  /* offset: 0x0050 size: 32 bit */
                     /* Off-Platform Peripheral Access Control Registers */
      PBRIDGE_OPACR40_47_32B_tag OPACR40_47;  /* offset: 0x0054 size: 32 bit */
                     /* Off-Platform Peripheral Access Control Registers */
      PBRIDGE_OPACR48_55_32B_tag OPACR48_55;  /* offset: 0x0058 size: 32 bit */
                     /* Off-Platform Peripheral Access Control Registers */
      PBRIDGE_OPACR56_63_32B_tag OPACR56_63;  /* offset: 0x005C size: 32 bit */
                     /* Off-Platform Peripheral Access Control Registers */
      PBRIDGE_OPACR64_71_32B_tag OPACR64_71;  /* offset: 0x0060 size: 32 bit */
      int8_t PBRIDGE_reserved_0064[4];
                     /* Off-Platform Peripheral Access Control Registers */
      PBRIDGE_OPACR80_87_32B_tag OPACR80_87;  /* offset: 0x0068 size: 32 bit */
                     /* Off-Platform Peripheral Access Control Registers */
      PBRIDGE_OPACR88_95_32B_tag OPACR88_95;  /* offset: 0x006C size: 32 bit */
      int8_t PBRIDGE_reserved_0070[16272];

   } PBRIDGE_tag;


#define PBRIDGE_BASEADDRESS 0xFFF00000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define PBRIDGE (*(volatile PBRIDGE_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFF00000UL))



/****************************************************************/
/*                                                              */
/* Module: XBAR  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Priority register for slave port 0 */
      vuint32_t R;
      struct {
         vuint32_t:5;
         vuint32_t  MSTR_6:3;          /* Master 6 Priority */
         vuint32_t:1;
         vuint32_t  MSTR_5:3;          /* Master 5 Priority */
         vuint32_t:5;
         vuint32_t  MSTR_3:3;          /* Master 3 Priority */
         vuint32_t:1;
         vuint32_t  MSTR_2:3;          /* Master 2 Priority */
         vuint32_t:1;
         vuint32_t  MSTR_1:3;          /* Master 1 Priority */
         vuint32_t:1;
         vuint32_t  MSTR_0:3;          /* Master 0 Priority */
      } B;
   } XBAR_MPR_32B_tag;

   typedef union {   /* General purpose control register for slave port 0 */
      vuint32_t R;
      struct {
         vuint32_t  RO:1;              /* Read Only */
         vuint32_t  HLP:1;             /* Halt Low Priority */
         vuint32_t:7;
         vuint32_t  HPE6:1;            /* Enable priority elevation for master 6 */
         vuint32_t  HPE5:1;            /* Enable priority elevation for master 5 */
         vuint32_t:1;
         vuint32_t  HPE3:1;            /* Enable priority elevation for master 3 */
         vuint32_t  HPE2:1;            /* Enable priority elevation for master 2 */
         vuint32_t  HPE1:1;            /* Enable priority elevation for master 1 */
         vuint32_t  HPE0:1;            /* Enable priority elevation for master 0 */
         vuint32_t:6;
         vuint32_t  ARB:2;             /* Arbitration Mode */
         vuint32_t:2;
         vuint32_t  PCTL:2;            /* Parking Control */
         vuint32_t:1;
         vuint32_t  PARK:3;            /* Park */
      } B;
   } XBAR_SGPCR_32B_tag;

   typedef union {   /* General purpose control Register for master 0 */
      vuint32_t R;
      struct {
         vuint32_t:29;
         vuint32_t  AULB:3;            /* Arbitrate on Undefined Length Bursts */
      } B;
   } XBAR_MGPCR_32B_tag;


   typedef struct XBAR_struct_tag {

                                   /* Priority register for slave port 0 */
      XBAR_MPR_32B_tag MPR0;               /* offset: 0x0000 size: 32 bit */
      int8_t XBAR_reserved_0004[12];
                    /* General purpose control register for slave port 0 */
      XBAR_SGPCR_32B_tag SGPCR0;           /* offset: 0x0010 size: 32 bit */
      int8_t XBAR_reserved_0014[492];
                                   /* Priority register for slave port 2 */
      XBAR_MPR_32B_tag MPR2;               /* offset: 0x0200 size: 32 bit */
      int8_t XBAR_reserved_0204[12];
                    /* General purpose control register for slave port 2 */
      XBAR_SGPCR_32B_tag SGPCR2;           /* offset: 0x0210 size: 32 bit */
      int8_t XBAR_reserved_0214[1260];
                                   /* Priority register for slave port 7 */
      XBAR_MPR_32B_tag MPR7;               /* offset: 0x0700 size: 32 bit */
      int8_t XBAR_reserved_0704[12];
                    /* General purpose control register for slave port 7 */
      XBAR_SGPCR_32B_tag SGPCR7;           /* offset: 0x0710 size: 32 bit */
      int8_t XBAR_reserved_0714[236];
                        /* General purpose control Register for master 0 */
      XBAR_MGPCR_32B_tag MGPCR0;           /* offset: 0x0800 size: 32 bit */
      int8_t XBAR_reserved_0804[252];
                        /* General purpose control Register for master 1 */
      XBAR_MGPCR_32B_tag MGPCR1;           /* offset: 0x0900 size: 32 bit */
      int8_t XBAR_reserved_0904[252];
                        /* General purpose control Register for master 2 */
      XBAR_MGPCR_32B_tag MGPCR2;           /* offset: 0x0A00 size: 32 bit */
      int8_t XBAR_reserved_0A04[252];
                        /* General purpose control Register for master 3 */
      XBAR_MGPCR_32B_tag MGPCR3;           /* offset: 0x0B00 size: 32 bit */
      int8_t XBAR_reserved_0B04[508];
                        /* General purpose control Register for master 5 */
      XBAR_MGPCR_32B_tag MGPCR5;           /* offset: 0x0D00 size: 32 bit */
      int8_t XBAR_reserved_0D04[252];
                        /* General purpose control Register for master 6 */
      XBAR_MGPCR_32B_tag MGPCR6;           /* offset: 0x0E00 size: 32 bit */
      int8_t XBAR_reserved_0E04[12796];

   } XBAR_tag;


#define XBAR_BASEADDRESS 0xFFF04000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define XBAR  (*(volatile XBAR_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFF04000UL))



/****************************************************************/
/*                                                              */
/* Module: MPU  */
/*                                                              */
/****************************************************************/

   typedef union {   /* MPU Control/Error Status Register */
      vuint32_t R;
      struct {
         vuint32_t  SPERR0:1;          /* Slave Port 0 Error */
         vuint32_t  SPERR1:1;          /* Slave Port 1 Error */
         vuint32_t  SPERR2:1;          /* Slave Port 2 Error */
         vuint32_t:9;
         vuint32_t  HRL:4;             /* Hardware Revision Level */
         vuint32_t  NSP:4;             /* Number of Slave Ports */
         vuint32_t  NRGD:4;            /* Number of Region Descriptors 0=>8, 1=>12, 2=>16 */
         vuint32_t:7;
         vuint32_t  VLD:1;             /* Valid bit */
      } B;
   } MPU_CESR_32B_tag;


   /* Register layout for all registers EAR ... */

   typedef union {   /* MPU Error Address Register, Slave Port n */
      vuint32_t R;
      struct {
         vuint32_t  EADDR:32;          /* Error Address */
      } B;
   } MPU_EAR_32B_tag;


   /* Register layout for all registers EDR ... */

   typedef union {   /* MPU Error Detail Register, Slave Port n */
      vuint32_t R;
      struct {
         vuint32_t  EACD:16;           /* Error Access Control Detail */
         vuint32_t  EPID:8;            /* Error Process Identification */
         vuint32_t  EMN:4;             /* Error Master Number */
         vuint32_t  EATTR:3;           /* Error Attributes */
         vuint32_t  ERW:1;             /* Error Read/Write */
      } B;
   } MPU_EDR_32B_tag;


   /* Register layout for all registers RGD_WORD0 ... */

   typedef union {   /* MPU Region Descriptor (Word 0) */
      vuint32_t R;
      struct {
         vuint32_t  SRTADDR:27;        /* Start Address */
         vuint32_t:5;
      } B;
   } MPU_RGD_WORD0_32B_tag;


   /* Register layout for all registers RGD_WORD1 ... */

   typedef union {   /* MPU Region Descriptor (Word 1) */
      vuint32_t R;
      struct {
         vuint32_t  ENDADDR:27;        /* End Address */
         vuint32_t:5;
      } B;
   } MPU_RGD_WORD1_32B_tag;


   /* Register layout for all registers RGD_WORD2 ... */

   typedef union {   /* MPU Region Descriptor (Word 2) */
      vuint32_t R;
      struct {
         vuint32_t:8;
         vuint32_t  M3PE:1;            /* Bus Master 3 Process Identifier Enable */
         vuint32_t  M3SM:2;            /* Bus Master 3 Supervisor Mode Access Control */
         vuint32_t  M3UM:3;            /* Bus Master 3 User Mode Access Control */
         vuint32_t  M2PE:1;            /* Bus Master 2 Process Identifier Enable */
         vuint32_t  M2SM:2;            /* Bus Master 2 Supervisor Mode Access Control */
         vuint32_t  M2UM:3;            /* Bus Master 2 User Mode Access Control */
         vuint32_t  M1PE:1;            /* Bus Master 1 Process Identifier Enable */
         vuint32_t  M1SM:2;            /* Bus Master 1 Supervisor Mode Access Control */
         vuint32_t  M1UM:3;            /* Bus Master 1 User Mode Access Control */
         vuint32_t  M0PE:1;            /* Bus Master 0 Process Identifier Enable */
         vuint32_t  M0SM:2;            /* Bus Master 0 Supervisor Mode Access Control */
         vuint32_t  M0UM:3;            /* Bus Master 0 User Mode Access Control */
      } B;
   } MPU_RGD_WORD2_32B_tag;


   /* Register layout for all registers RGD_WORD3 ... */

   typedef union {   /* MPU Region Descriptor (Word 3) */
      vuint32_t R;
      struct {
         vuint32_t  PID:8;             /* Process Identifier */
         vuint32_t  PIDMASK:8;         /* Process Identifier Mask */
         vuint32_t:15;
         vuint32_t  VLD:1;             /* Valid */
      } B;
   } MPU_RGD_WORD3_32B_tag;


   /* Register layout for all registers RGDAAC ... */

   typedef union {   /* MPU Region Descriptor Alternate Access Control */
      vuint32_t R;
      struct {
         vuint32_t:8;
         vuint32_t  M3PE:1;            /* Bus Master 3 Process Identifier Enable */
         vuint32_t  M3SM:2;            /* Bus Master 3 Supervisor Mode Access Control */
         vuint32_t  M3UM:3;            /* Bus Master 3 User Mode Access Control */
         vuint32_t  M2PE:1;            /* Bus Master 2 Process Identifier Enable */
         vuint32_t  M2SM:2;            /* Bus Master 2 Supervisor Mode Access Control */
         vuint32_t  M2UM:3;            /* Bus Master 2 User Mode Access Control */
         vuint32_t  M1PE:1;            /* Bus Master 1 Process Identifier Enable */
         vuint32_t  M1SM:2;            /* Bus Master 1 Supervisor Mode Access Control */
         vuint32_t  M1UM:3;            /* Bus Master 1 User Mode Access Control */
         vuint32_t  M0PE:1;            /* Bus Master 0 Process Identifier Enable */
         vuint32_t  M0SM:2;            /* Bus Master 0 Supervisor Mode Access Control */
         vuint32_t  M0UM:3;            /* Bus Master 0 User Mode Access Control */
      } B;
   } MPU_RGDAAC_32B_tag;


   typedef struct MPU_SLAVE_PORT_struct_tag {

                             /* MPU Error Address Register, Slave Port n */
      MPU_EAR_32B_tag EAR;                 /* relative offset: 0x0000 */
                              /* MPU Error Detail Register, Slave Port n */
      MPU_EDR_32B_tag EDR;                 /* relative offset: 0x0004 */

   } MPU_SLAVE_PORT_tag;



   typedef struct MPU_REGION_struct_tag {

                                       /* MPU Region Descriptor (Word 0) */
      MPU_RGD_WORD0_32B_tag WORD0;     /* relative offset: 0x0000 *//* Renamed from "RGD_WORD0" to be able to reuse code */
                                       /* MPU Region Descriptor (Word 1) */
      MPU_RGD_WORD1_32B_tag WORD1;     /* relative offset: 0x0004 *//* Renamed from "RGD_WORD1" to be able to reuse code */
                                       /* MPU Region Descriptor (Word 2) */
      MPU_RGD_WORD2_32B_tag WORD2;     /* relative offset: 0x0008 *//* Renamed from "RGD_WORD2" to be able to reuse code */
                                       /* MPU Region Descriptor (Word 3) */
      MPU_RGD_WORD3_32B_tag WORD3;     /* relative offset: 0x000C *//* Renamed from "RGD_WORD3" to be able to reuse code */

   } MPU_REGION_tag;



   typedef struct MPU_struct_tag {

                                    /* MPU Control/Error Status Register */
      MPU_CESR_32B_tag CESR;               /* offset: 0x0000 size: 32 bit */
      int8_t MPU_reserved_0004[12];
      union {
                                             /*  Register set SLAVE_PORT */
         MPU_SLAVE_PORT_tag SLAVE_PORT[3];  /* offset: 0x0010  (0x0008 x 3) */

         struct {
                             /* MPU Error Address Register, Slave Port n */
            MPU_EAR_32B_tag EAR0;          /* offset: 0x0010 size: 32 bit */
                              /* MPU Error Detail Register, Slave Port n */
            MPU_EDR_32B_tag EDR0;          /* offset: 0x0014 size: 32 bit */
                             /* MPU Error Address Register, Slave Port n */
            MPU_EAR_32B_tag EAR1;          /* offset: 0x0018 size: 32 bit */
                              /* MPU Error Detail Register, Slave Port n */
            MPU_EDR_32B_tag EDR1;          /* offset: 0x001C size: 32 bit */
                             /* MPU Error Address Register, Slave Port n */
            MPU_EAR_32B_tag EAR2;          /* offset: 0x0020 size: 32 bit */
                              /* MPU Error Detail Register, Slave Port n */
            MPU_EDR_32B_tag EDR2;          /* offset: 0x0024 size: 32 bit */
         };

      };
      int8_t MPU_reserved_0028[984];
      union {
                                                 /*  Register set REGION */
         MPU_REGION_tag RGD[16];        /* offset: 0x0400  (0x0010 x 16) *//* Renamed from "REGION" to be able to reuse code */

         struct {
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD0_WORD0;  /* offset: 0x0400 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD0_WORD1;  /* offset: 0x0404 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD0_WORD2;  /* offset: 0x0408 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD0_WORD3;  /* offset: 0x040C size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD1_WORD0;  /* offset: 0x0410 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD1_WORD1;  /* offset: 0x0414 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD1_WORD2;  /* offset: 0x0418 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD1_WORD3;  /* offset: 0x041C size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD2_WORD0;  /* offset: 0x0420 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD2_WORD1;  /* offset: 0x0424 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD2_WORD2;  /* offset: 0x0428 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD2_WORD3;  /* offset: 0x042C size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD3_WORD0;  /* offset: 0x0430 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD3_WORD1;  /* offset: 0x0434 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD3_WORD2;  /* offset: 0x0438 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD3_WORD3;  /* offset: 0x043C size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD4_WORD0;  /* offset: 0x0440 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD4_WORD1;  /* offset: 0x0444 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD4_WORD2;  /* offset: 0x0448 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD4_WORD3;  /* offset: 0x044C size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD5_WORD0;  /* offset: 0x0450 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD5_WORD1;  /* offset: 0x0454 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD5_WORD2;  /* offset: 0x0458 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD5_WORD3;  /* offset: 0x045C size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD6_WORD0;  /* offset: 0x0460 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD6_WORD1;  /* offset: 0x0464 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD6_WORD2;  /* offset: 0x0468 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD6_WORD3;  /* offset: 0x046C size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD7_WORD0;  /* offset: 0x0470 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD7_WORD1;  /* offset: 0x0474 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD7_WORD2;  /* offset: 0x0478 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD7_WORD3;  /* offset: 0x047C size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD8_WORD0;  /* offset: 0x0480 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD8_WORD1;  /* offset: 0x0484 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD8_WORD2;  /* offset: 0x0488 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD8_WORD3;  /* offset: 0x048C size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD9_WORD0;  /* offset: 0x0490 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD9_WORD1;  /* offset: 0x0494 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD9_WORD2;  /* offset: 0x0498 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD9_WORD3;  /* offset: 0x049C size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD10_WORD0;  /* offset: 0x04A0 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD10_WORD1;  /* offset: 0x04A4 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD10_WORD2;  /* offset: 0x04A8 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD10_WORD3;  /* offset: 0x04AC size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD11_WORD0;  /* offset: 0x04B0 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD11_WORD1;  /* offset: 0x04B4 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD11_WORD2;  /* offset: 0x04B8 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD11_WORD3;  /* offset: 0x04BC size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD12_WORD0;  /* offset: 0x04C0 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD12_WORD1;  /* offset: 0x04C4 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD12_WORD2;  /* offset: 0x04C8 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD12_WORD3;  /* offset: 0x04CC size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD13_WORD0;  /* offset: 0x04D0 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD13_WORD1;  /* offset: 0x04D4 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD13_WORD2;  /* offset: 0x04D8 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD13_WORD3;  /* offset: 0x04DC size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD14_WORD0;  /* offset: 0x04E0 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD14_WORD1;  /* offset: 0x04E4 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD14_WORD2;  /* offset: 0x04E8 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD14_WORD3;  /* offset: 0x04EC size: 32 bit */
                                       /* MPU Region Descriptor (Word 0) */
            MPU_RGD_WORD0_32B_tag RGD15_WORD0;  /* offset: 0x04F0 size: 32 bit */
                                       /* MPU Region Descriptor (Word 1) */
            MPU_RGD_WORD1_32B_tag RGD15_WORD1;  /* offset: 0x04F4 size: 32 bit */
                                       /* MPU Region Descriptor (Word 2) */
            MPU_RGD_WORD2_32B_tag RGD15_WORD2;  /* offset: 0x04F8 size: 32 bit */
                                       /* MPU Region Descriptor (Word 3) */
            MPU_RGD_WORD3_32B_tag RGD15_WORD3;  /* offset: 0x04FC size: 32 bit */
         };

      };
      int8_t MPU_reserved_0500[768];
      union {
                       /* MPU Region Descriptor Alternate Access Control */
         MPU_RGDAAC_32B_tag RGDAAC[16];    /* offset: 0x0800  (0x0004 x 16) */

         struct {
                       /* MPU Region Descriptor Alternate Access Control */
            MPU_RGDAAC_32B_tag RGDAAC0;    /* offset: 0x0800 size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC1;    /* offset: 0x0804 size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC2;    /* offset: 0x0808 size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC3;    /* offset: 0x080C size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC4;    /* offset: 0x0810 size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC5;    /* offset: 0x0814 size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC6;    /* offset: 0x0818 size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC7;    /* offset: 0x081C size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC8;    /* offset: 0x0820 size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC9;    /* offset: 0x0824 size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC10;   /* offset: 0x0828 size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC11;   /* offset: 0x082C size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC12;   /* offset: 0x0830 size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC13;   /* offset: 0x0834 size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC14;   /* offset: 0x0838 size: 32 bit */
            MPU_RGDAAC_32B_tag RGDAAC15;   /* offset: 0x083C size: 32 bit */
         };

      };
      int8_t MPU_reserved_0840[14272];

   } MPU_tag;


#define MPU_BASEADDRESS 0xFFF10000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define MPU   (*(volatile MPU_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFF10000UL))



/****************************************************************/
/*                                                              */
/* Module: SWT  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Control Register */
      vuint32_t R;
      struct {
         vuint32_t  MAP0:1;            /* Master Access Protection for Master 0 */
         vuint32_t  MAP1:1;            /* Master Access Protection for Master 1 */
         vuint32_t  MAP2:1;            /* Master Access Protection for Master 2 */
         vuint32_t  MAP3:1;            /* Master Access Protection for Master 3 */
         vuint32_t:1;
         vuint32_t  MAP5:1;            /* Master Access Protection for Master 5 */
         vuint32_t  MAP6:1;            /* Master Access Protection for Master 6 */
         vuint32_t:15;
         vuint32_t  KEY:1;             /* Keyed Service Mode */
         vuint32_t  RIA:1;             /* Reset on Invalid Access */
         vuint32_t  WND:1;             /* Window Mode */
         vuint32_t  ITR:1;             /* Interrupt Then Reset */
         vuint32_t  HLK:1;             /* Hard Lock */
         vuint32_t  SLK:1;             /* Soft Lock */
         vuint32_t:1;
         vuint32_t  STP:1;             /* Stop Mode Control */
         vuint32_t  FRZ:1;             /* Debug Mode Control */
         vuint32_t  WEN:1;             /* Watchdog Enabled */
      } B;
   } SWT_CR_32B_tag;

   typedef union {   /* Interrupt Register */
      vuint32_t R;
      struct {
         vuint32_t:31;
         vuint32_t  TIF:1;             /* Time Out Interrupt Flag */
      } B;
   } SWT_IR_32B_tag;

   typedef union {   /* Time-Out Register */
      vuint32_t R;
      struct {
         vuint32_t  WTO:32;            /* Watchdog time-out period in clock cycles */
      } B;
   } SWT_TO_32B_tag;

   typedef union {   /* Window Register */
      vuint32_t R;
      struct {
         vuint32_t  WST:32;            /* Window start value */
      } B;
   } SWT_WN_32B_tag;

   typedef union {   /* Service Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  WSC:16;            /* Watchdog Service Code */
      } B;
   } SWT_SR_32B_tag;

   typedef union {   /* Counter Output Register */
      vuint32_t R;
      struct {
         vuint32_t  CNT:32;            /* Watchdog Count */
      } B;
   } SWT_CO_32B_tag;

   typedef union {   /* Service Key Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  SERVICEKEY:16;     /* Service Key */
      } B;
   } SWT_SK_32B_tag;


   typedef struct SWT_struct_tag {

                                                     /* Control Register */
      SWT_CR_32B_tag CR;                   /* offset: 0x0000 size: 32 bit */
                                                   /* Interrupt Register */
      SWT_IR_32B_tag IR;                   /* offset: 0x0004 size: 32 bit */
                                                    /* Time-Out Register */
      SWT_TO_32B_tag TO;                   /* offset: 0x0008 size: 32 bit */
                                                      /* Window Register */
      SWT_WN_32B_tag WN;                   /* offset: 0x000C size: 32 bit */
                                                     /* Service Register */
      SWT_SR_32B_tag SR;                   /* offset: 0x0010 size: 32 bit */
                                              /* Counter Output Register */
      SWT_CO_32B_tag CO;                   /* offset: 0x0014 size: 32 bit */
                                                 /* Service Key Register */
      SWT_SK_32B_tag SK;                   /* offset: 0x0018 size: 32 bit */
      int8_t SWT_reserved_001C[16356];

   } SWT_tag;


#define SWT_BASEADDRESS 0xFFF38000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define SWT   (*(volatile SWT_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFF38000UL))



/****************************************************************/
/*                                                              */
/* Module: STM  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Control Register */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  CPS:8;             /* Counter Prescaler */
         vuint32_t:6;
         vuint32_t  FRZ:1;             /* Freeze Control */
         vuint32_t  TEN:1;             /* Timer Counter Enabled */
      } B;
   } STM_CR_32B_tag;

   typedef union {   /* Count Register */
      vuint32_t R;
   } STM_CNT_32B_tag;


   /* Register layout for all registers CCR ... */

   typedef union {   /* Channel Control Register */
      vuint32_t R;
      struct {
         vuint32_t:31;
         vuint32_t  CEN:1;             /* Channel Enable */
      } B;
   } STM_CCR_32B_tag;


   /* Register layout for all registers CIR ... */

   typedef union {   /* Channel Interrupt Register */
      vuint32_t R;
      struct {
         vuint32_t:31;
         vuint32_t  CIF:1;             /* Channel Interrupt Flag */
      } B;
   } STM_CIR_32B_tag;


   /* Register layout for all registers CMP ... */

   typedef union {   /* Channel Compare Register */
      vuint32_t R;
   } STM_CMP_32B_tag;


   typedef struct STM_CHANNEL_struct_tag {

                                             /* Channel Control Register */
      STM_CCR_32B_tag CCR;                 /* relative offset: 0x0000 */
                                           /* Channel Interrupt Register */
      STM_CIR_32B_tag CIR;                 /* relative offset: 0x0004 */
                                             /* Channel Compare Register */
      STM_CMP_32B_tag CMP;                 /* relative offset: 0x0008 */
      int8_t STM_CHANNEL_reserved_000C[4];

   } STM_CHANNEL_tag;



   typedef struct STM_struct_tag {

                                                     /* Control Register */
      STM_CR_32B_tag CR;                   /* offset: 0x0000 size: 32 bit */
                                                       /* Count Register */
      STM_CNT_32B_tag CNT;                 /* offset: 0x0004 size: 32 bit */
      int8_t STM_reserved_0008[8];
      union {
                                                /*  Register set CHANNEL */
         STM_CHANNEL_tag CHANNEL[4];       /* offset: 0x0010  (0x0010 x 4) */

         struct {
                                             /* Channel Control Register */
            STM_CCR_32B_tag CCR0;          /* offset: 0x0010 size: 32 bit */
                                           /* Channel Interrupt Register */
            STM_CIR_32B_tag CIR0;          /* offset: 0x0014 size: 32 bit */
                                             /* Channel Compare Register */
            STM_CMP_32B_tag CMP0;          /* offset: 0x0018 size: 32 bit */
            int8_t STM_reserved_001C_I1[4];
                                             /* Channel Control Register */
            STM_CCR_32B_tag CCR1;          /* offset: 0x0020 size: 32 bit */
                                           /* Channel Interrupt Register */
            STM_CIR_32B_tag CIR1;          /* offset: 0x0024 size: 32 bit */
                                             /* Channel Compare Register */
            STM_CMP_32B_tag CMP1;          /* offset: 0x0028 size: 32 bit */
            int8_t STM_reserved_002C_I1[4];
                                             /* Channel Control Register */
            STM_CCR_32B_tag CCR2;          /* offset: 0x0030 size: 32 bit */
                                           /* Channel Interrupt Register */
            STM_CIR_32B_tag CIR2;          /* offset: 0x0034 size: 32 bit */
                                             /* Channel Compare Register */
            STM_CMP_32B_tag CMP2;          /* offset: 0x0038 size: 32 bit */
            int8_t STM_reserved_003C_I1[4];
                                             /* Channel Control Register */
            STM_CCR_32B_tag CCR3;          /* offset: 0x0040 size: 32 bit */
                                           /* Channel Interrupt Register */
            STM_CIR_32B_tag CIR3;          /* offset: 0x0044 size: 32 bit */
                                             /* Channel Compare Register */
            STM_CMP_32B_tag CMP3;          /* offset: 0x0048 size: 32 bit */
            int8_t STM_reserved_004C_E1[4];
         };

      };
      int8_t STM_reserved_0050[16304];

   } STM_tag;


#define STM_BASEADDRESS 0xFFF3C000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define STM   (*(volatile STM_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFF3C000UL))



/****************************************************************/
/*                                                              */
/* Module: ECSM  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Processor Core Type */
      vuint16_t R;
   } ECSM_PCT_16B_tag;

   typedef union {   /* SOC-Defined Platform Revision */
      vuint16_t R;
   } ECSM_PLREV_16B_tag;

   typedef union {   /* Platform Crossbar Master Configuration - Processor Core Type */
      vuint16_t R;
      struct {
         vuint16_t:8;
         vuint16_t  AMC7:1;            /* Bus master to XBAR input port 7 is present */
         vuint16_t  AMC6:1;            /* Bus master to XBAR input port 6 is present */
         vuint16_t  AMC5:1;            /* Bus master to XBAR input port 5 is present */
         vuint16_t  AMC4:1;            /* Bus master to XBAR input port 4 is present */
         vuint16_t  AMC3:1;            /* Bus master to XBAR input port 3 is present */
         vuint16_t  AMC2:1;            /* Bus master to XBAR input port 2 is present */
         vuint16_t  AMC1:1;            /* Bus master to XBAR input port 1 is present */
         vuint16_t  AMC0:1;            /* Bus master to XBAR input port 0 is present */
      } B;
   } ECSM_PLAMC_16B_tag;

   typedef union {   /* Platform Crossbar Slave Configuration - Processor Core Type */
      vuint16_t R;
      struct {
         vuint16_t  DP64:1;            /* 64-bit datapath 1=64bit,0=32bit */
         vuint16_t:7;
         vuint16_t  ASC7:1;            /* Bus slave to XBAR output port 7 is present */
         vuint16_t  ASC6:1;            /* Bus slave to XBAR output port 6 is present */
         vuint16_t  ASC5:1;            /* Bus slave to XBAR output port 5 is present */
         vuint16_t  ASC4:1;            /* Bus slave to XBAR output port 4 is present */
         vuint16_t  ASC3:1;            /* Bus slave to XBAR output port 3 is present */
         vuint16_t  ASC2:1;            /* Bus slave to XBAR output port 2 is present */
         vuint16_t  ASC1:1;            /* Bus slave to XBAR output port 1 is present */
         vuint16_t  ASC0:1;            /* Bus slave to XBAR output port 0 is present */
      } B;
   } ECSM_PLASC_16B_tag;

   typedef union {   /* IPS On-Platform Module Configuration */
      vuint32_t R;
      struct {
         vuint32_t  PMC31:1;           /* IPS module connection to decoded slot 31 is present */
         vuint32_t  PMC30:1;           /* IPS module connection to decoded slot 30 is present */
         vuint32_t  PMC29:1;           /* IPS module connection to decoded slot 29 is present */
         vuint32_t  PMC28:1;           /* IPS module connection to decoded slot 28 is present */
         vuint32_t  PMC27:1;           /* IPS module connection to decoded slot 27 is present */
         vuint32_t  PMC26:1;           /* IPS module connection to decoded slot 26 is present */
         vuint32_t  PMC25:1;           /* IPS module connection to decoded slot 25 is present */
         vuint32_t  PMC24:1;           /* IPS module connection to decoded slot 24 is present */
         vuint32_t  PMC23:1;           /* IPS module connection to decoded slot 23 is present */
         vuint32_t  PMC22:1;           /* IPS module connection to decoded slot 22 is present */
         vuint32_t  PMC21:1;           /* IPS module connection to decoded slot 21 is present */
         vuint32_t  PMC20:1;           /* IPS module connection to decoded slot 20 is present */
         vuint32_t  PMC19:1;           /* IPS module connection to decoded slot 19 is present */
         vuint32_t  PMC18:1;           /* IPS module connection to decoded slot 18 is present */
         vuint32_t  PMC17:1;           /* IPS module connection to decoded slot 17 is present */
         vuint32_t  PMC16:1;           /* IPS module connection to decoded slot 16 is present */
         vuint32_t  PMC15:1;           /* IPS module connection to decoded slot 15 is present */
         vuint32_t  PMC14:1;           /* IPS module connection to decoded slot 14 is present */
         vuint32_t  PMC13:1;           /* IPS module connection to decoded slot 13 is present */
         vuint32_t  PMC12:1;           /* IPS module connection to decoded slot 12 is present */
         vuint32_t  PMC11:1;           /* IPS module connection to decoded slot 11 is present */
         vuint32_t  PMC10:1;           /* IPS module connection to decoded slot 10 is present */
         vuint32_t  PMC9:1;            /* IPS module connection to decoded slot 9 is present */
         vuint32_t  PMC8:1;            /* IPS module connection to decoded slot 8 is present */
         vuint32_t  PMC7:1;            /* IPS module connection to decoded slot 7 is present */
         vuint32_t  PMC6:1;            /* IPS module connection to decoded slot 6 is present */
         vuint32_t  PMC5:1;            /* IPS module connection to decoded slot 5 is present */
         vuint32_t  PMC4:1;            /* IPS module connection to decoded slot 4 is present */
         vuint32_t  PMC3:1;            /* IPS module connection to decoded slot 3 is present */
         vuint32_t  PMC2:1;            /* IPS module connection to decoded slot 2 is present */
         vuint32_t  PMC1:1;            /* IPS module connection to decoded slot 1 is present */
         vuint32_t  PMC0:1;            /* IPS module connection to decoded slot 0 is present */
      } B;
   } ECSM_IOPMC_32B_tag;

   typedef union {   /* Miscellaneous Reset Status Register */
      vuint8_t R;
      struct {
         vuint8_t   POR:1;             /* Power on Reset */
         vuint8_t   OFPLR:1;           /* Off-Platform Reset */
         vuint8_t:6;
      } B;
   } ECSM_MRSR_8B_tag;

   typedef union {   /* Miscellaneous User Defined Control Register */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  MUDC30:1;          /* Platform RAM wait-state control */
         vuint32_t:30;
      } B;
   } ECSM_MUDCR_32B_tag;

   typedef union {   /* ECC Configuration Register */
      vuint8_t R;
      struct {
         vuint8_t:2;
         vuint8_t   EPR1BR:1;          /* Enable Platform RAM 1-bit Reporting */
         vuint8_t   EPF1BR:1;          /* Enable Platform FLASH 1-bit Reporting */
         vuint8_t:2;
         vuint8_t   EPRNCR:1;          /* Enable Platform RAM Non-Correctable Reporting */
         vuint8_t   EPFNCR:1;          /* Enable Platform FLASH Non-Correctable Reporting */
      } B;
   } ECSM_ECR_8B_tag;

   typedef union {   /* ECC Status Register */
      vuint8_t R;
      struct {
         vuint8_t:2;
         vuint8_t   PR1BC:1;           /* Platform RAM 1-bit Correction */
         vuint8_t   PF1BC:1;           /* Platform FLASH 1-bit Correction */
         vuint8_t:2;
         vuint8_t   RNCE:1;           /* Platform RAM Non-Correctable Error *//* Renamed from PRNCE to simplify code reuse */
         vuint8_t   FNCE:1;           /* Platform FLASH Non-Correctable Error *//* Renamed from PFNCE to simplify code reuse */
      } B;
   } ECSM_ESR_8B_tag;

   typedef union {   /* ECC Error Generation Register */
      vuint16_t R;
      struct {
         vuint16_t  FRCAP:1;           /* Force Platform RAM Error Injection Access Protection */
         vuint16_t:1;
         vuint16_t  FRC1BI:1;          /* Force Platform RAM Continuous 1-Bit Data Inversions */
         vuint16_t  FR11BI:1;          /* Force Platform RAM One 1-Bit Data Inversion */
         vuint16_t:2;
         vuint16_t  FRCNCI:1;          /* Force Platform RAM Continuous Noncorrectable Data Inversions */
         vuint16_t  FR1NCI:1;          /* Force Platform RAM One Noncorrectable Data Inversions */
         vuint16_t:1;
         vuint16_t  ERRBIT:7;          /* Error Bit Position */
      } B;
   } ECSM_EEGR_16B_tag;

   typedef union {   /* Platform Flash Memory ECC Address Register */
      vuint32_t R;
   } ECSM_PFEAR_32B_tag;

   typedef union {   /* Platform Flash ECC Master Number Register */
      vuint8_t R;
      struct {
         vuint8_t:4;
         vuint8_t   PFEM:4;            /* Platform Flash Memory ECC Master Number */
      } B;
   } ECSM_PFEMR_8B_tag;

   typedef union {   /* Platform Flash ECC Attributes Register */
      vuint8_t R;
      struct {
         vuint8_t   WRITE:1;           /* AMBA-AHB HWRITE */
         vuint8_t   SIZE:3;            /* AMBA-AHB HSIZE */
         vuint8_t   PROTECT:4;         /* AMBA-AHB HPROT */
      } B;
   } ECSM_PFEAT_8B_tag;

   typedef union {   /* Platform Flash ECC Data Register High Word */
      vuint32_t R;
   } ECSM_PFEDRH_32B_tag;

   typedef union {   /* Platform Flash ECC Data Register Low Word */
      vuint32_t R;
   } ECSM_PFEDRL_32B_tag;

   typedef union {   /* Platform RAM ECC Address Register */
      vuint32_t R;
   } ECSM_PREAR_32B_tag;

   typedef union {   /* Platform RAM ECC Syndrome Register */
      vuint8_t R;
   } ECSM_PRESR_8B_tag;

   typedef union {   /* Platform RAM ECC Master Number Register */
      vuint8_t R;
      struct {
         vuint8_t:4;
         vuint8_t   PR_EMR:4;          /* Platform RAM ECC Master Number */
      } B;
   } ECSM_PREMR_8B_tag;

   typedef union {   /* Platform RAM ECC Attributes Register */
      vuint8_t R;
      struct {
         vuint8_t   WRITE:1;           /* AMBA-AHBH Write */
         vuint8_t   SIZE:3;            /* AMBA-AHBH Size */
         vuint8_t   PROTECT:4;         /* AMBA-AHBH PROT */
      } B;
   } ECSM_PREAT_8B_tag;

   typedef union {   /* Platform RAM ECC Data Register High Word */
      vuint32_t R;
   } ECSM_PREDRH_32B_tag;

   typedef union {   /* Platform RAM ECC Data Register Low Word */
      vuint32_t R;
   } ECSM_PREDRL_32B_tag;


   typedef struct ECSM_struct_tag {

                                                  /* Processor Core Type */
      ECSM_PCT_16B_tag PCT;                /* offset: 0x0000 size: 16 bit */
                                        /* SOC-Defined Platform Revision */
      ECSM_PLREV_16B_tag PLREV;            /* offset: 0x0002 size: 16 bit */
         /* Platform Crossbar Master Configuration - Processor Core Type */
      ECSM_PLAMC_16B_tag PLAMC;            /* offset: 0x0004 size: 16 bit */
          /* Platform Crossbar Slave Configuration - Processor Core Type */
      ECSM_PLASC_16B_tag PLASC;            /* offset: 0x0006 size: 16 bit */
                                 /* IPS On-Platform Module Configuration */
      ECSM_IOPMC_32B_tag IOPMC;            /* offset: 0x0008 size: 32 bit */
      int8_t ECSM_reserved_000C[3];
                                  /* Miscellaneous Reset Status Register */
      ECSM_MRSR_8B_tag MRSR;               /* offset: 0x000F size: 8 bit */
      int8_t ECSM_reserved_0010[20];
                          /* Miscellaneous User Defined Control Register */
      ECSM_MUDCR_32B_tag MUDCR;            /* offset: 0x0024 size: 32 bit */
      int8_t ECSM_reserved_0028[27];
                                           /* ECC Configuration Register */
      ECSM_ECR_8B_tag ECR;                 /* offset: 0x0043 size: 8 bit */
      int8_t ECSM_reserved_0044[3];
                                                  /* ECC Status Register */
      ECSM_ESR_8B_tag ESR;                 /* offset: 0x0047 size: 8 bit */
      int8_t ECSM_reserved_0048[2];
                                        /* ECC Error Generation Register */
      ECSM_EEGR_16B_tag EEGR;              /* offset: 0x004A size: 16 bit */
      int8_t ECSM_reserved_004C[4];
                           /* Platform Flash Memory ECC Address Register */
      ECSM_PFEAR_32B_tag FEAR;            /* offset: 0x0050 size: 32 bit *//* Renamed from PFEAR to simplify code reuse */
      int8_t ECSM_reserved_0054[2];
                            /* Platform Flash ECC Master Number Register */
      ECSM_PFEMR_8B_tag PFEMR;             /* offset: 0x0056 size: 8 bit */
                               /* Platform Flash ECC Attributes Register */
      ECSM_PFEAT_8B_tag PFEAT;             /* offset: 0x0057 size: 8 bit */
                           /* Platform Flash ECC Data Register High Word */
      ECSM_PFEDRH_32B_tag PFEDRH;          /* offset: 0x0058 size: 32 bit */
                            /* Platform Flash ECC Data Register Low Word */
      ECSM_PFEDRL_32B_tag PFEDRL;          /* offset: 0x005C size: 32 bit */
                                    /* Platform RAM ECC Address Register */
      ECSM_PREAR_32B_tag PREAR;            /* offset: 0x0060 size: 32 bit */
      int8_t ECSM_reserved_0064;
                                   /* Platform RAM ECC Syndrome Register */
      ECSM_PRESR_8B_tag PRESR;             /* offset: 0x0065 size: 8 bit */
                              /* Platform RAM ECC Master Number Register */
      ECSM_PREMR_8B_tag PREMR;             /* offset: 0x0066 size: 8 bit */
                                 /* Platform RAM ECC Attributes Register */
      ECSM_PREAT_8B_tag PREAT;             /* offset: 0x0067 size: 8 bit */
                             /* Platform RAM ECC Data Register High Word */
      ECSM_PREDRH_32B_tag PREDRH;          /* offset: 0x0068 size: 32 bit */
                              /* Platform RAM ECC Data Register Low Word */
      ECSM_PREDRL_32B_tag PREDRL;          /* offset: 0x006C size: 32 bit */
      int8_t ECSM_reserved_0070[16272];

   } ECSM_tag;


#define ECSM_BASEADDRESS 0xFFF40000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define ECSM  (*(volatile ECSM_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFF40000UL))



/****************************************************************/
/*                                                              */
/* Module: eDMA  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Control Register */
      vuint32_t R;
      struct {
         vuint32_t:14;
         vuint32_t  CX:1;              /* Cancel Transfer */
         vuint32_t  ECX:1;             /* Error Cancel Transfer */
         vuint32_t:8;
         vuint32_t  EMLM:1;            /* Enable Minor Loop Mapping */
         vuint32_t  CLM:1;             /* Continuous Link Mode */
         vuint32_t  HALT:1;            /* Halt DMA Operations */
         vuint32_t  HOE:1;             /* Halt on Error */
         vuint32_t:1;
         vuint32_t  ERCA:1;            /* Enable Round Robin Channel Arbitration */
         vuint32_t  EDBG:1;            /* Enable Debug */
         vuint32_t:1;
      } B;
   } eDMA_DMACR_32B_tag;

   typedef union {   /* Error Status Register */
      vuint32_t R;
      struct {
         vuint32_t  VLD:1;             /* Logical OR of DMAERRH and DMAERRL status bits */
         vuint32_t:14;
         vuint32_t  ECX:1;             /* Transfer Cancelled */
         vuint32_t:1;
         vuint32_t  CPE:1;             /* Channel Priority Error */
         vuint32_t  ERRCHN:6;          /* Error Channel Number or Cancelled Channel Number */
         vuint32_t  SAE:1;             /* Source Address Error */
         vuint32_t  SOE:1;             /* Source Offset Error */
         vuint32_t  DAE:1;             /* Destination Address Error */
         vuint32_t  DOE:1;             /* Destination Offset Error */
         vuint32_t  NCE:1;             /* Nbytes/Citer Configuration Error */
         vuint32_t  SGE:1;             /* Scatter/Gather Configuration Error */
         vuint32_t  SBE:1;             /* Source Bus Error */
         vuint32_t  DBE:1;             /* Destination Bus Error */
      } B;
   } eDMA_DMAES_32B_tag;

   typedef union {   /* Enable Request Register Low */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  ERQ15:1;           /* Enable DMA Request 15 */
         vuint32_t  ERQ14:1;           /* Enable DMA Request 14 */
         vuint32_t  ERQ13:1;           /* Enable DMA Request 13 */
         vuint32_t  ERQ12:1;           /* Enable DMA Request 12 */
         vuint32_t  ERQ11:1;           /* Enable DMA Request 11 */
         vuint32_t  ERQ10:1;           /* Enable DMA Request 10 */
         vuint32_t  ERQ9:1;            /* Enable DMA Request 9 */
         vuint32_t  ERQ8:1;            /* Enable DMA Request 8 */
         vuint32_t  ERQ7:1;            /* Enable DMA Request 7 */
         vuint32_t  ERQ6:1;            /* Enable DMA Request 6 */
         vuint32_t  ERQ5:1;            /* Enable DMA Request 5 */
         vuint32_t  ERQ4:1;            /* Enable DMA Request 4 */
         vuint32_t  ERQ3:1;            /* Enable DMA Request 3 */
         vuint32_t  ERQ2:1;            /* Enable DMA Request 2 */
         vuint32_t  ERQ1:1;            /* Enable DMA Request 1 */
         vuint32_t  ERQ0:1;            /* Enable DMA Request 0 */
      } B;
   } eDMA_DMAERQL_32B_tag;

   typedef union {   /* Enable Error Interrupt Register Low */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  EEI15:1;           /* DMA Enable Error Interrupt 15 */
         vuint32_t  EEI14:1;           /* DMA Enable Error Interrupt 14 */
         vuint32_t  EEI13:1;           /* DMA Enable Error Interrupt 13 */
         vuint32_t  EEI12:1;           /* DMA Enable Error Interrupt 12 */
         vuint32_t  EEI11:1;           /* DMA Enable Error Interrupt 11 */
         vuint32_t  EEI10:1;           /* DMA Enable Error Interrupt 10 */
         vuint32_t  EEI9:1;            /* DMA Enable Error Interrupt 9 */
         vuint32_t  EEI8:1;            /* DMA Enable Error Interrupt 8 */
         vuint32_t  EEI7:1;            /* DMA Enable Error Interrupt 7 */
         vuint32_t  EEI6:1;            /* DMA Enable Error Interrupt 6 */
         vuint32_t  EEI5:1;            /* DMA Enable Error Interrupt 5 */
         vuint32_t  EEI4:1;            /* DMA Enable Error Interrupt 4 */
         vuint32_t  EEI3:1;            /* DMA Enable Error Interrupt 3 */
         vuint32_t  EEI2:1;            /* DMA Enable Error Interrupt 2 */
         vuint32_t  EEI1:1;            /* DMA Enable Error Interrupt 1 */
         vuint32_t  EEI0:1;            /* DMA Enable Error Interrupt 0 */
      } B;
   } eDMA_DMAEEIL_32B_tag;

   typedef union {   /* Set Enable Request Register */
      vuint8_t R;
      struct {
         vuint8_t   NOP_SERQ:1;        /* No Operation (1=no operation, ignore SERQ) */
         vuint8_t   SAER:1;            /* Set All Enable Requests */
         vuint8_t:2;
         vuint8_t   SERQ:4;            /* Set Enable Request */
      } B;
   } eDMA_DMASERQ_8B_tag;

   typedef union {   /* Clear Enable Request Register */
      vuint8_t R;
      struct {
         vuint8_t   NOP_CERQ:1;        /* No Operation (1=no operation, ignore CERQ) */
         vuint8_t   CAER:1;            /* Clear All Enable Requests */
         vuint8_t:2;
         vuint8_t   CERQ:4;            /* Clear Enable Request */
      } B;
   } eDMA_DMACERQ_8B_tag;

   typedef union {   /* Set Enable Error Interrupt Register */
      vuint8_t R;
      struct {
         vuint8_t   NOP_SEEI:1;        /* No Operation (1=no operation, ignore SEEI) */
         vuint8_t   SAEE:1;            /* Set All Enable Error Interrupts */
         vuint8_t:2;
         vuint8_t   SEEI:4;            /* Set Enable Error Interrupt */
      } B;
   } eDMA_DMASEEI_8B_tag;

   typedef union {   /* Clear Enable Error Interrupt Register */
      vuint8_t R;
      struct {
         vuint8_t   NOP_CEEI:1;        /* No Operation (1=no operation, ignore CEEI) */
         vuint8_t   CAEI:1;            /* Clear All Enable Error Interrupts */
         vuint8_t:2;
         vuint8_t   CEEI:4;            /* Clear Enable Error Interrupt */
      } B;
   } eDMA_DMACEEI_8B_tag;

   typedef union {   /* Clear Interrupt Request register */
      vuint8_t R;
      struct {
         vuint8_t   NOP_CINT:1;        /* No Operation (1=no operation, ignore CINT) */
         vuint8_t   CAIR:1;            /* Clear All Interrupt Requests */
         vuint8_t:2;
         vuint8_t   CINT:4;            /* Clear Interrupt Request */
      } B;
   } eDMA_DMACINT_8B_tag;

   typedef union {   /* Clear Error register */
      vuint8_t R;
      struct {
         vuint8_t   NOP_CERR:1;        /* No Operation (1=no operation, ignore CERR) */
         vuint8_t   CAEI:1;            /* Clear All Error Indicators */
         vuint8_t:2;
         vuint8_t   CERR:4;            /* Clear Error Indicator */
      } B;
   } eDMA_DMACERR_8B_tag;

   typedef union {   /* Set START Bit */
      vuint8_t R;
      struct {
         vuint8_t   NOP_SSRT:1;        /* No Operation (1=no operation, ignore SSRT) */
         vuint8_t   SAST:1;            /* Set All START Bits */
         vuint8_t:2;
         vuint8_t   SSRT:4;            /* Set START Bit */
      } B;
   } eDMA_DMASSRT_8B_tag;

   typedef union {   /* Clear DONE Status */
      vuint8_t R;
      struct {
         vuint8_t   NOP_CDNE:1;        /* No Operation (1=no operation, ignore CDNE) */
         vuint8_t   CADN:1;            /* Clear All DONE Status Bits */
         vuint8_t:2;
         vuint8_t   CDNE:4;            /* Clear DONE Status Bit */
      } B;
   } eDMA_DMACDNE_8B_tag;

   typedef union {   /* eDMA Interrupt Request Register Low */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  INT15:1;           /* DMA Interrupt Request 15 */
         vuint32_t  INT14:1;           /* DMA Interrupt Request 14 */
         vuint32_t  INT13:1;           /* DMA Interrupt Request 13 */
         vuint32_t  INT12:1;           /* DMA Interrupt Request 12 */
         vuint32_t  INT11:1;           /* DMA Interrupt Request 11 */
         vuint32_t  INT10:1;           /* DMA Interrupt Request 10 */
         vuint32_t  INT9:1;            /* DMA Interrupt Request 9 */
         vuint32_t  INT8:1;            /* DMA Interrupt Request 8 */
         vuint32_t  INT7:1;            /* DMA Interrupt Request 7 */
         vuint32_t  INT6:1;            /* DMA Interrupt Request 6 */
         vuint32_t  INT5:1;            /* DMA Interrupt Request 5 */
         vuint32_t  INT4:1;            /* DMA Interrupt Request 4 */
         vuint32_t  INT3:1;            /* DMA Interrupt Request 3 */
         vuint32_t  INT2:1;            /* DMA Interrupt Request 2 */
         vuint32_t  INT1:1;            /* DMA Interrupt Request 1 */
         vuint32_t  INT0:1;            /* DMA Interrupt Request 0 */
      } B;
   } eDMA_DMAINTL_32B_tag;

   typedef union {   /* eDMA Error Register Low */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  ERR15:1;           /* DMA Error 15 */
         vuint32_t  ERR14:1;           /* DMA Error 14 */
         vuint32_t  ERR13:1;           /* DMA Error 13 */
         vuint32_t  ERR12:1;           /* DMA Error 12 */
         vuint32_t  ERR11:1;           /* DMA Error 11 */
         vuint32_t  ERR10:1;           /* DMA Error 10 */
         vuint32_t  ERR9:1;            /* DMA Error 9 */
         vuint32_t  ERR8:1;            /* DMA Error 8 */
         vuint32_t  ERR7:1;            /* DMA Error 7 */
         vuint32_t  ERR6:1;            /* DMA Error 6 */
         vuint32_t  ERR5:1;            /* DMA Error 5 */
         vuint32_t  ERR4:1;            /* DMA Error 4 */
         vuint32_t  ERR3:1;            /* DMA Error 3 */
         vuint32_t  ERR2:1;            /* DMA Error 2 */
         vuint32_t  ERR1:1;            /* DMA Error 1 */
         vuint32_t  ERR0:1;            /* DMA Error 0 */
      } B;
   } eDMA_DMAERRL_32B_tag;

   typedef union {   /* eDMA Hardware Request Status Register Low */
      vuint32_t R;
      struct {
         vuint32_t:16;
         vuint32_t  HRS15:1;           /* DMA Hardware Request Status 15 */
         vuint32_t  HRS14:1;           /* DMA Hardware Request Status 14 */
         vuint32_t  HRS13:1;           /* DMA Hardware Request Status 13 */
         vuint32_t  HRS12:1;           /* DMA Hardware Request Status 12 */
         vuint32_t  HRS11:1;           /* DMA Hardware Request Status 11 */
         vuint32_t  HRS10:1;           /* DMA Hardware Request Status 10 */
         vuint32_t  HRS9:1;            /* DMA Hardware Request Status 9 */
         vuint32_t  HRS8:1;            /* DMA Hardware Request Status 8 */
         vuint32_t  HRS7:1;            /* DMA Hardware Request Status 7 */
         vuint32_t  HRS6:1;            /* DMA Hardware Request Status 6 */
         vuint32_t  HRS5:1;            /* DMA Hardware Request Status 5 */
         vuint32_t  HRS4:1;            /* DMA Hardware Request Status 4 */
         vuint32_t  HRS3:1;            /* DMA Hardware Request Status 3 */
         vuint32_t  HRS2:1;            /* DMA Hardware Request Status 2 */
         vuint32_t  HRS1:1;            /* DMA Hardware Request Status 1 */
         vuint32_t  HRS0:1;            /* DMA Hardware Request Status 0 */
      } B;
   } eDMA_DMAHRSL_32B_tag;


   /* Register layout for all registers DCHPRI ... */

   typedef union {   /* Channel n Priority */
      vuint8_t R;
      struct {
         vuint8_t   ECP:1;             /* Enable Channel Preemption */
         vuint8_t   DPA:1;             /* Disable Preempt Ability */
         vuint8_t:2;
         vuint8_t   CHPRI:4;           /* Channel n Arbitration Priority */
      } B;
   } eDMA_DCHPRI_8B_tag;


   /* Register layout for all registers TCD_SADDR ... */

   typedef union {   /* TCDn - Source Address */
      vuint32_t R;
   } eDMA_TCD_SADDR_32B_tag;


   /* Register layout for all registers TCD_ATTR ... */

   typedef union {   /* TCDn - Transfer Attributes */
      vuint16_t R;
      struct {
         vuint16_t  SMOD:5;            /* Source Address Modulo */
         vuint16_t  SSIZE:3;           /* Source Data Transfer Size */
         vuint16_t  DMOD:5;            /* Destination Address Modulo */
         vuint16_t  DSIZE:3;           /* Destination Data Transfer Size */
      } B;
   } eDMA_TCD_ATTR_16B_tag;


   /* Register layout for all registers TCD_SOFF ... */

   typedef union {   /* TCDn - Signed Source Address Offset */
      vuint16_t R;
   } eDMA_TCD_SOFF_16B_tag;


   /* Register layout for all registers TCD_NBYTES ... */

   typedef union {   /* TCDn - Minor Byte Count (Minor Loop Disabled) */
      vuint32_t R;
   } eDMA_TCD_NBYTES_32B_tag;


   /* Register layout for all registers TCD_SLAST ... */

   typedef union {   /* TCDn - Last Source Address Adjustment */
      vuint32_t R;
   } eDMA_TCD_SLAST_32B_tag;


   /* Register layout for all registers TCD_DADDR ... */

   typedef union {   /* TCDn - Destination Address */
      vuint32_t R;
   } eDMA_TCD_DADDR_32B_tag;


   /* Register layout for all registers TCD_CITER ... */

   typedef union {   /* TCDn - Current Major Iteration Count */
      vuint16_t R;
      struct {
         vuint16_t  ELINK:1;           /* Enable channel-to-channel linking on minor loop complete */
         vuint16_t  CITER:15;          /* Current Major Iteration Count */
      } B;
   } eDMA_TCD_CITER_16B_tag;


   /* Register layout for all registers TCD_DOFF ... */

   typedef union {   /* TCDn - Signed Destination Address Offset */
      vuint16_t R;
   } eDMA_TCD_DOFF_16B_tag;


   /* Register layout for all registers TCD_DLASTSGA ... */

   typedef union {   /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
      vuint32_t R;
   } eDMA_TCD_DLASTSGA_32B_tag;


   /* Register layout for all registers TCD_BITER ... */

   typedef union {   /* TCDn - Begin Major Iteration Count */
      vuint16_t R;
      struct {
         vuint16_t  ELINK:1;           /* Enables channel-to-channel linking on minor loop complete */
         vuint16_t  BITER:15;          /* Starting Major Iteration Count */
      } B;
   } eDMA_TCD_BITER_16B_tag;


   /* Register layout for all registers TCD_CSR ... */

   typedef union {   /* TCDn -  Control and Status */
      vuint16_t R;
      struct {
         vuint16_t  BWC:2;             /* Bandwidth Control */
         vuint16_t  MAJORLINKCH:6;     /* Link Channel Number */
         vuint16_t  DONE:1;            /* Channel done */
         vuint16_t  ACTIVE:1;          /* Channel Active */
         vuint16_t  MAJORELINK:1;      /* Enable channel-to-channel linking on major loop complete */
         vuint16_t  ESG:1;             /* Enable Scatter/Gather Processing */
         vuint16_t  DREQ:1;            /* Disable Request */
         vuint16_t  INTHALF:1;         /* Enable an interrupt when major counter is half complete */
         vuint16_t  INTMAJOR:1;        /* Enable an interrupt when major iteration count completes */
         vuint16_t  START:1;           /* Channel Start */
      } B;
   } eDMA_TCD_CSR_16B_tag;


   typedef struct eDMA_CHANNEL_struct_tag {

                                                /* TCDn - Source Address */
      eDMA_TCD_SADDR_32B_tag TCD_SADDR;    /* relative offset: 0x0000 */
                                           /* TCDn - Transfer Attributes */
      eDMA_TCD_ATTR_16B_tag TCD_ATTR;      /* relative offset: 0x0004 */
                                  /* TCDn - Signed Source Address Offset */
      eDMA_TCD_SOFF_16B_tag TCD_SOFF;      /* relative offset: 0x0006 */
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
      eDMA_TCD_NBYTES_32B_tag TCD_NBYTES;  /* relative offset: 0x0008 */
                                /* TCDn - Last Source Address Adjustment */
      eDMA_TCD_SLAST_32B_tag TCD_SLAST;    /* relative offset: 0x000C */
                                           /* TCDn - Destination Address */
      eDMA_TCD_DADDR_32B_tag TCD_DADDR;    /* relative offset: 0x0010 */
                                 /* TCDn - Current Major Iteration Count */
      eDMA_TCD_CITER_16B_tag TCD_CITER;    /* relative offset: 0x0014 */
                             /* TCDn - Signed Destination Address Offset */
      eDMA_TCD_DOFF_16B_tag TCD_DOFF;      /* relative offset: 0x0016 */
    /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
      eDMA_TCD_DLASTSGA_32B_tag TCD_DLASTSGA;  /* relative offset: 0x0018 */
                                   /* TCDn - Begin Major Iteration Count */
      eDMA_TCD_BITER_16B_tag TCD_BITER;    /* relative offset: 0x001C */
                                           /* TCDn -  Control and Status */
      eDMA_TCD_CSR_16B_tag TCD_CSR;        /* relative offset: 0x001E */

   } eDMA_CHANNEL_tag;



   typedef struct eDMA_struct_tag {

                                                     /* Control Register */
      eDMA_DMACR_32B_tag DMACR;            /* offset: 0x0000 size: 32 bit */
                                                /* Error Status Register */
      eDMA_DMAES_32B_tag DMAES;            /* offset: 0x0004 size: 32 bit */
      int8_t eDMA_reserved_0008[4];
                                          /* Enable Request Register Low */
      eDMA_DMAERQL_32B_tag DMAERQL;        /* offset: 0x000C size: 32 bit */
      int8_t eDMA_reserved_0010[4];
                                  /* Enable Error Interrupt Register Low */
      eDMA_DMAEEIL_32B_tag DMAEEIL;        /* offset: 0x0014 size: 32 bit */
                                          /* Set Enable Request Register */
      eDMA_DMASERQ_8B_tag DMASERQ;         /* offset: 0x0018 size: 8 bit */
                                        /* Clear Enable Request Register */
      eDMA_DMACERQ_8B_tag DMACERQ;         /* offset: 0x0019 size: 8 bit */
                                  /* Set Enable Error Interrupt Register */
      eDMA_DMASEEI_8B_tag DMASEEI;         /* offset: 0x001A size: 8 bit */
                                /* Clear Enable Error Interrupt Register */
      eDMA_DMACEEI_8B_tag DMACEEI;         /* offset: 0x001B size: 8 bit */
                                     /* Clear Interrupt Request register */
      eDMA_DMACINT_8B_tag DMACINT;         /* offset: 0x001C size: 8 bit */
                                                 /* Clear Error register */
      eDMA_DMACERR_8B_tag DMACERR;         /* offset: 0x001D size: 8 bit */
                                                        /* Set START Bit */
      eDMA_DMASSRT_8B_tag DMASSRT;         /* offset: 0x001E size: 8 bit */
                                                    /* Clear DONE Status */
      eDMA_DMACDNE_8B_tag DMACDNE;         /* offset: 0x001F size: 8 bit */
      int8_t eDMA_reserved_0020[4];
                                  /* eDMA Interrupt Request Register Low */
      eDMA_DMAINTL_32B_tag DMAINTL;        /* offset: 0x0024 size: 32 bit */
      int8_t eDMA_reserved_0028[4];
                                              /* eDMA Error Register Low */
      eDMA_DMAERRL_32B_tag DMAERRL;        /* offset: 0x002C size: 32 bit */
      int8_t eDMA_reserved_0030[4];
                            /* eDMA Hardware Request Status Register Low */
      eDMA_DMAHRSL_32B_tag DMAHRSL;        /* offset: 0x0034 size: 32 bit */
      int8_t eDMA_reserved_0038[200];
      union {
                                                   /* Channel n Priority */
         eDMA_DCHPRI_8B_tag DCHPRI[16];    /* offset: 0x0100  (0x0001 x 16) */

         struct {
                                                   /* Channel n Priority */
            eDMA_DCHPRI_8B_tag DCHPRI0;    /* offset: 0x0100 size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI1;    /* offset: 0x0101 size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI2;    /* offset: 0x0102 size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI3;    /* offset: 0x0103 size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI4;    /* offset: 0x0104 size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI5;    /* offset: 0x0105 size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI6;    /* offset: 0x0106 size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI7;    /* offset: 0x0107 size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI8;    /* offset: 0x0108 size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI9;    /* offset: 0x0109 size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI10;   /* offset: 0x010A size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI11;   /* offset: 0x010B size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI12;   /* offset: 0x010C size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI13;   /* offset: 0x010D size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI14;   /* offset: 0x010E size: 8 bit */
            eDMA_DCHPRI_8B_tag DCHPRI15;   /* offset: 0x010F size: 8 bit */
         };

      };
      int8_t eDMA_reserved_0110[3824];
      union {
                                                /*  Register set CHANNEL */
         eDMA_CHANNEL_tag CHANNEL[16];     /* offset: 0x1000  (0x0020 x 16) */

         struct {
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD0_SADDR;  /* offset: 0x1000 size: 32 bit */
            int8_t eDMA_reserved_1004_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD0_NBYTES;  /* offset: 0x1008 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD0_SLAST;  /* offset: 0x100C size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD0_DADDR;  /* offset: 0x1010 size: 32 bit */
            int8_t eDMA_reserved_1014_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD0_DLASTSGA;  /* offset: 0x1018 size: 32 bit */
            int8_t eDMA_reserved_101C_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD1_SADDR;  /* offset: 0x1020 size: 32 bit */
            int8_t eDMA_reserved_1024_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD1_NBYTES;  /* offset: 0x1028 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD1_SLAST;  /* offset: 0x102C size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD1_DADDR;  /* offset: 0x1030 size: 32 bit */
            int8_t eDMA_reserved_1034_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD1_DLASTSGA;  /* offset: 0x1038 size: 32 bit */
            int8_t eDMA_reserved_103C_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD2_SADDR;  /* offset: 0x1040 size: 32 bit */
            int8_t eDMA_reserved_1044_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD2_NBYTES;  /* offset: 0x1048 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD2_SLAST;  /* offset: 0x104C size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD2_DADDR;  /* offset: 0x1050 size: 32 bit */
            int8_t eDMA_reserved_1054_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD2_DLASTSGA;  /* offset: 0x1058 size: 32 bit */
            int8_t eDMA_reserved_105C_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD3_SADDR;  /* offset: 0x1060 size: 32 bit */
            int8_t eDMA_reserved_1064_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD3_NBYTES;  /* offset: 0x1068 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD3_SLAST;  /* offset: 0x106C size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD3_DADDR;  /* offset: 0x1070 size: 32 bit */
            int8_t eDMA_reserved_1074_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD3_DLASTSGA;  /* offset: 0x1078 size: 32 bit */
            int8_t eDMA_reserved_107C_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD4_SADDR;  /* offset: 0x1080 size: 32 bit */
            int8_t eDMA_reserved_1084_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD4_NBYTES;  /* offset: 0x1088 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD4_SLAST;  /* offset: 0x108C size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD4_DADDR;  /* offset: 0x1090 size: 32 bit */
            int8_t eDMA_reserved_1094_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD4_DLASTSGA;  /* offset: 0x1098 size: 32 bit */
            int8_t eDMA_reserved_109C_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD5_SADDR;  /* offset: 0x10A0 size: 32 bit */
            int8_t eDMA_reserved_10A4_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD5_NBYTES;  /* offset: 0x10A8 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD5_SLAST;  /* offset: 0x10AC size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD5_DADDR;  /* offset: 0x10B0 size: 32 bit */
            int8_t eDMA_reserved_10B4_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD5_DLASTSGA;  /* offset: 0x10B8 size: 32 bit */
            int8_t eDMA_reserved_10BC_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD6_SADDR;  /* offset: 0x10C0 size: 32 bit */
            int8_t eDMA_reserved_10C4_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD6_NBYTES;  /* offset: 0x10C8 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD6_SLAST;  /* offset: 0x10CC size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD6_DADDR;  /* offset: 0x10D0 size: 32 bit */
            int8_t eDMA_reserved_10D4_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD6_DLASTSGA;  /* offset: 0x10D8 size: 32 bit */
            int8_t eDMA_reserved_10DC_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD7_SADDR;  /* offset: 0x10E0 size: 32 bit */
            int8_t eDMA_reserved_10E4_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD7_NBYTES;  /* offset: 0x10E8 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD7_SLAST;  /* offset: 0x10EC size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD7_DADDR;  /* offset: 0x10F0 size: 32 bit */
            int8_t eDMA_reserved_10F4_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD7_DLASTSGA;  /* offset: 0x10F8 size: 32 bit */
            int8_t eDMA_reserved_10FC_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD8_SADDR;  /* offset: 0x1100 size: 32 bit */
            int8_t eDMA_reserved_1104_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD8_NBYTES;  /* offset: 0x1108 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD8_SLAST;  /* offset: 0x110C size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD8_DADDR;  /* offset: 0x1110 size: 32 bit */
            int8_t eDMA_reserved_1114_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD8_DLASTSGA;  /* offset: 0x1118 size: 32 bit */
            int8_t eDMA_reserved_111C_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD9_SADDR;  /* offset: 0x1120 size: 32 bit */
            int8_t eDMA_reserved_1124_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD9_NBYTES;  /* offset: 0x1128 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD9_SLAST;  /* offset: 0x112C size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD9_DADDR;  /* offset: 0x1130 size: 32 bit */
            int8_t eDMA_reserved_1134_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD9_DLASTSGA;  /* offset: 0x1138 size: 32 bit */
            int8_t eDMA_reserved_113C_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD10_SADDR;  /* offset: 0x1140 size: 32 bit */
            int8_t eDMA_reserved_1144_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD10_NBYTES;  /* offset: 0x1148 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD10_SLAST;  /* offset: 0x114C size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD10_DADDR;  /* offset: 0x1150 size: 32 bit */
            int8_t eDMA_reserved_1154_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD10_DLASTSGA;  /* offset: 0x1158 size: 32 bit */
            int8_t eDMA_reserved_115C_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD11_SADDR;  /* offset: 0x1160 size: 32 bit */
            int8_t eDMA_reserved_1164_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD11_NBYTES;  /* offset: 0x1168 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD11_SLAST;  /* offset: 0x116C size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD11_DADDR;  /* offset: 0x1170 size: 32 bit */
            int8_t eDMA_reserved_1174_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD11_DLASTSGA;  /* offset: 0x1178 size: 32 bit */
            int8_t eDMA_reserved_117C_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD12_SADDR;  /* offset: 0x1180 size: 32 bit */
            int8_t eDMA_reserved_1184_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD12_NBYTES;  /* offset: 0x1188 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD12_SLAST;  /* offset: 0x118C size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD12_DADDR;  /* offset: 0x1190 size: 32 bit */
            int8_t eDMA_reserved_1194_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD12_DLASTSGA;  /* offset: 0x1198 size: 32 bit */
            int8_t eDMA_reserved_119C_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD13_SADDR;  /* offset: 0x11A0 size: 32 bit */
            int8_t eDMA_reserved_11A4_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD13_NBYTES;  /* offset: 0x11A8 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD13_SLAST;  /* offset: 0x11AC size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD13_DADDR;  /* offset: 0x11B0 size: 32 bit */
            int8_t eDMA_reserved_11B4_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD13_DLASTSGA;  /* offset: 0x11B8 size: 32 bit */
            int8_t eDMA_reserved_11BC_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD14_SADDR;  /* offset: 0x11C0 size: 32 bit */
            int8_t eDMA_reserved_11C4_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD14_NBYTES;  /* offset: 0x11C8 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD14_SLAST;  /* offset: 0x11CC size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD14_DADDR;  /* offset: 0x11D0 size: 32 bit */
            int8_t eDMA_reserved_11D4_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD14_DLASTSGA;  /* offset: 0x11D8 size: 32 bit */
            int8_t eDMA_reserved_11DC_I1[4];
                                                /* TCDn - Source Address */
            eDMA_TCD_SADDR_32B_tag TCD15_SADDR;  /* offset: 0x11E0 size: 32 bit */
            int8_t eDMA_reserved_11E4_I1[4];
                        /* TCDn - Minor Byte Count (Minor Loop Disabled) */
            eDMA_TCD_NBYTES_32B_tag TCD15_NBYTES;  /* offset: 0x11E8 size: 32 bit */
                                /* TCDn - Last Source Address Adjustment */
            eDMA_TCD_SLAST_32B_tag TCD15_SLAST;  /* offset: 0x11EC size: 32 bit */
                                           /* TCDn - Destination Address */
            eDMA_TCD_DADDR_32B_tag TCD15_DADDR;  /* offset: 0x11F0 size: 32 bit */
            int8_t eDMA_reserved_11F4_I1[4];
          /* TCDn - Last Destination Address Adjustment/Scatter Gather Address */
            eDMA_TCD_DLASTSGA_32B_tag TCD15_DLASTSGA;  /* offset: 0x11F8 size: 32 bit */
            int8_t eDMA_reserved_11FC_E1[4];
         };

         struct {
            int8_t eDMA_reserved_1000_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD0_ATTR;  /* offset: 0x1004 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD0_SOFF;  /* offset: 0x1006 size: 16 bit */
            int8_t eDMA_reserved_1008_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD0_CITER;  /* offset: 0x1014 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD0_DOFF;  /* offset: 0x1016 size: 16 bit */
            int8_t eDMA_reserved_1018_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD0_BITER;  /* offset: 0x101C size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD0_CSR;  /* offset: 0x101E size: 16 bit */
            int8_t eDMA_reserved_1020_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD1_ATTR;  /* offset: 0x1024 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD1_SOFF;  /* offset: 0x1026 size: 16 bit */
            int8_t eDMA_reserved_1028_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD1_CITER;  /* offset: 0x1034 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD1_DOFF;  /* offset: 0x1036 size: 16 bit */
            int8_t eDMA_reserved_1038_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD1_BITER;  /* offset: 0x103C size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD1_CSR;  /* offset: 0x103E size: 16 bit */
            int8_t eDMA_reserved_1040_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD2_ATTR;  /* offset: 0x1044 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD2_SOFF;  /* offset: 0x1046 size: 16 bit */
            int8_t eDMA_reserved_1048_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD2_CITER;  /* offset: 0x1054 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD2_DOFF;  /* offset: 0x1056 size: 16 bit */
            int8_t eDMA_reserved_1058_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD2_BITER;  /* offset: 0x105C size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD2_CSR;  /* offset: 0x105E size: 16 bit */
            int8_t eDMA_reserved_1060_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD3_ATTR;  /* offset: 0x1064 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD3_SOFF;  /* offset: 0x1066 size: 16 bit */
            int8_t eDMA_reserved_1068_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD3_CITER;  /* offset: 0x1074 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD3_DOFF;  /* offset: 0x1076 size: 16 bit */
            int8_t eDMA_reserved_1078_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD3_BITER;  /* offset: 0x107C size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD3_CSR;  /* offset: 0x107E size: 16 bit */
            int8_t eDMA_reserved_1080_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD4_ATTR;  /* offset: 0x1084 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD4_SOFF;  /* offset: 0x1086 size: 16 bit */
            int8_t eDMA_reserved_1088_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD4_CITER;  /* offset: 0x1094 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD4_DOFF;  /* offset: 0x1096 size: 16 bit */
            int8_t eDMA_reserved_1098_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD4_BITER;  /* offset: 0x109C size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD4_CSR;  /* offset: 0x109E size: 16 bit */
            int8_t eDMA_reserved_10A0_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD5_ATTR;  /* offset: 0x10A4 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD5_SOFF;  /* offset: 0x10A6 size: 16 bit */
            int8_t eDMA_reserved_10A8_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD5_CITER;  /* offset: 0x10B4 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD5_DOFF;  /* offset: 0x10B6 size: 16 bit */
            int8_t eDMA_reserved_10B8_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD5_BITER;  /* offset: 0x10BC size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD5_CSR;  /* offset: 0x10BE size: 16 bit */
            int8_t eDMA_reserved_10C0_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD6_ATTR;  /* offset: 0x10C4 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD6_SOFF;  /* offset: 0x10C6 size: 16 bit */
            int8_t eDMA_reserved_10C8_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD6_CITER;  /* offset: 0x10D4 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD6_DOFF;  /* offset: 0x10D6 size: 16 bit */
            int8_t eDMA_reserved_10D8_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD6_BITER;  /* offset: 0x10DC size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD6_CSR;  /* offset: 0x10DE size: 16 bit */
            int8_t eDMA_reserved_10E0_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD7_ATTR;  /* offset: 0x10E4 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD7_SOFF;  /* offset: 0x10E6 size: 16 bit */
            int8_t eDMA_reserved_10E8_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD7_CITER;  /* offset: 0x10F4 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD7_DOFF;  /* offset: 0x10F6 size: 16 bit */
            int8_t eDMA_reserved_10F8_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD7_BITER;  /* offset: 0x10FC size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD7_CSR;  /* offset: 0x10FE size: 16 bit */
            int8_t eDMA_reserved_1100_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD8_ATTR;  /* offset: 0x1104 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD8_SOFF;  /* offset: 0x1106 size: 16 bit */
            int8_t eDMA_reserved_1108_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD8_CITER;  /* offset: 0x1114 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD8_DOFF;  /* offset: 0x1116 size: 16 bit */
            int8_t eDMA_reserved_1118_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD8_BITER;  /* offset: 0x111C size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD8_CSR;  /* offset: 0x111E size: 16 bit */
            int8_t eDMA_reserved_1120_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD9_ATTR;  /* offset: 0x1124 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD9_SOFF;  /* offset: 0x1126 size: 16 bit */
            int8_t eDMA_reserved_1128_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD9_CITER;  /* offset: 0x1134 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD9_DOFF;  /* offset: 0x1136 size: 16 bit */
            int8_t eDMA_reserved_1138_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD9_BITER;  /* offset: 0x113C size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD9_CSR;  /* offset: 0x113E size: 16 bit */
            int8_t eDMA_reserved_1140_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD10_ATTR;  /* offset: 0x1144 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD10_SOFF;  /* offset: 0x1146 size: 16 bit */
            int8_t eDMA_reserved_1148_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD10_CITER;  /* offset: 0x1154 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD10_DOFF;  /* offset: 0x1156 size: 16 bit */
            int8_t eDMA_reserved_1158_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD10_BITER;  /* offset: 0x115C size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD10_CSR;  /* offset: 0x115E size: 16 bit */
            int8_t eDMA_reserved_1160_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD11_ATTR;  /* offset: 0x1164 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD11_SOFF;  /* offset: 0x1166 size: 16 bit */
            int8_t eDMA_reserved_1168_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD11_CITER;  /* offset: 0x1174 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD11_DOFF;  /* offset: 0x1176 size: 16 bit */
            int8_t eDMA_reserved_1178_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD11_BITER;  /* offset: 0x117C size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD11_CSR;  /* offset: 0x117E size: 16 bit */
            int8_t eDMA_reserved_1180_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD12_ATTR;  /* offset: 0x1184 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD12_SOFF;  /* offset: 0x1186 size: 16 bit */
            int8_t eDMA_reserved_1188_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD12_CITER;  /* offset: 0x1194 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD12_DOFF;  /* offset: 0x1196 size: 16 bit */
            int8_t eDMA_reserved_1198_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD12_BITER;  /* offset: 0x119C size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD12_CSR;  /* offset: 0x119E size: 16 bit */
            int8_t eDMA_reserved_11A0_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD13_ATTR;  /* offset: 0x11A4 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD13_SOFF;  /* offset: 0x11A6 size: 16 bit */
            int8_t eDMA_reserved_11A8_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD13_CITER;  /* offset: 0x11B4 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD13_DOFF;  /* offset: 0x11B6 size: 16 bit */
            int8_t eDMA_reserved_11B8_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD13_BITER;  /* offset: 0x11BC size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD13_CSR;  /* offset: 0x11BE size: 16 bit */
            int8_t eDMA_reserved_11C0_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD14_ATTR;  /* offset: 0x11C4 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD14_SOFF;  /* offset: 0x11C6 size: 16 bit */
            int8_t eDMA_reserved_11C8_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD14_CITER;  /* offset: 0x11D4 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD14_DOFF;  /* offset: 0x11D6 size: 16 bit */
            int8_t eDMA_reserved_11D8_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD14_BITER;  /* offset: 0x11DC size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD14_CSR;  /* offset: 0x11DE size: 16 bit */
            int8_t eDMA_reserved_11E0_I2[4];
                                           /* TCDn - Transfer Attributes */
            eDMA_TCD_ATTR_16B_tag TCD15_ATTR;  /* offset: 0x11E4 size: 16 bit */
                                  /* TCDn - Signed Source Address Offset */
            eDMA_TCD_SOFF_16B_tag TCD15_SOFF;  /* offset: 0x11E6 size: 16 bit */
            int8_t eDMA_reserved_11E8_I2[12];
                                 /* TCDn - Current Major Iteration Count */
            eDMA_TCD_CITER_16B_tag TCD15_CITER;  /* offset: 0x11F4 size: 16 bit */
                             /* TCDn - Signed Destination Address Offset */
            eDMA_TCD_DOFF_16B_tag TCD15_DOFF;  /* offset: 0x11F6 size: 16 bit */
            int8_t eDMA_reserved_11F8_I2[4];
                                   /* TCDn - Begin Major Iteration Count */
            eDMA_TCD_BITER_16B_tag TCD15_BITER;  /* offset: 0x11FC size: 16 bit */
                                           /* TCDn -  Control and Status */
            eDMA_TCD_CSR_16B_tag TCD15_CSR;  /* offset: 0x11FE size: 16 bit */
         };

      };
      int8_t eDMA_reserved_1200[11776];

   } eDMA_tag;


#define eDMA_BASEADDRESS 0xFFF44000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define eDMA  (*(volatile eDMA_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFF44000UL))



#include "ip_intc.h"

/****************************************************************/
/*                                                              */
/* Module: DSPI  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Module Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t  MSTR:1;            /* Master/Slave mode select */
         vuint32_t  CONT_SCKE:1;       /* Continuous SCK Enable */
         vuint32_t  DCONF:2;           /* DSPI Configuration */
         vuint32_t  FRZ:1;             /* Freeze */
         vuint32_t  MTFE:1;            /* Modified Timing Format Enable */
         vuint32_t  PCSSE:1;           /* Peripheral Chip Select Strobe Enable */
         vuint32_t  ROOE:1;            /* Receive FIFO Overflow Overwrite Enable */
         vuint32_t  PCSIS7:1;          /* Peripheral Chip Select 7 Inactive State */
         vuint32_t  PCSIS6:1;          /* Peripheral Chip Select 6 Inactive State */
         vuint32_t  PCSIS5:1;          /* Peripheral Chip Select 5 Inactive State */
         vuint32_t  PCSIS4:1;          /* Peripheral Chip Select 4 Inactive State */
         vuint32_t  PCSIS3:1;          /* Peripheral Chip Select 3 Inactive State */
         vuint32_t  PCSIS2:1;          /* Peripheral Chip Select 2 Inactive State */
         vuint32_t  PCSIS1:1;          /* Peripheral Chip Select 1 Inactive State */
         vuint32_t  PCSIS0:1;          /* Peripheral Chip Select 0 Inactive State */
         vuint32_t:1;
         vuint32_t  MDIS:1;            /* Module Disable */
         vuint32_t  DIS_TXF:1;         /* Disable Transmit FIFO */
         vuint32_t  DIS_RXF:1;         /* Disable Receive FIFO */
         vuint32_t  CLR_TXF:1;         /* Clear TX FIFO */
         vuint32_t  CLR_RXF:1;         /* Flushes the RX FIFO */
         vuint32_t  SMPL_PT:2;         /* Sample Point */
         vuint32_t:6;
         vuint32_t  PES:1;             /* Parity Error Stop */
         vuint32_t  HALT:1;            /* Halt */
      } B;
   } DSPI_MCR_32B_tag;

   typedef union {   /* HCR - Hardware Configuration Register */
      vuint32_t R;
      struct {
         vuint32_t:1;
         vuint32_t  PISR:1;            /* DSPI_PISR registers implemented flag */
         vuint32_t:3;
         vuint32_t  CTAR:3;            /* Number of implemented DSPI_CTAR registers */
         vuint32_t  TXFR:4;            /* Number of implemented DSPI_TXFR registers */
         vuint32_t  RXFR:4;            /* Number of implemented DSPI_RXFR registers */
         vuint32_t:16;
      } B;
   } DSPI_HCR_32B_tag;

   typedef union {   /* Transfer Count Register */
      vuint32_t R;
      struct {
         vuint32_t  SPI_TCNT:16;       /* SPI Transfer Counter */
         vuint32_t:16;
      } B;
   } DSPI_TCR_32B_tag;


   /* Register layout for all registers SLAVE_CTAR ... */

   typedef union {   /* CTAR0-1 - Clock and Transfer Attribute Registers (in slave mode) */
      vuint32_t R;
      struct {
         vuint32_t  SLAVE_FMSZ:5;      /* Frame Size */
         vuint32_t  SLAVE_CPOL:1;      /* Clock Polarity */
         vuint32_t  SLAVE_CPHA:1;      /* Clock Phase */
         vuint32_t  SLAVE_PE:1;        /* Parity Enable */
         vuint32_t  SLAVE_PP:1;        /* Parity Polarity */
         vuint32_t:23;
      } B;
   } DSPI_SLAVE_CTAR_32B_tag;


   /* Register layout for all registers CTAR ... */

   typedef union {   /* Clock and Transfer Attribute Registers */
      vuint32_t R;
      struct {
         vuint32_t  DBR:1;             /* Double Baud Rate */
         vuint32_t  FMSZ:4;            /* Frame Size */
         vuint32_t  CPOL:1;            /* Clock Polarity */
         vuint32_t  CPHA:1;            /* Clock Phase */
         vuint32_t  LSBFE:1;           /* LSB First */
         vuint32_t  PCSSCK:2;          /* PCS to SCK Delay Prescaler */
         vuint32_t  PASC:2;            /* After SCK Delay Prescaler */
         vuint32_t  PDT:2;             /* Delay after Transfer Prescaler */
         vuint32_t  PBR:2;             /* Baud Rate Prescaler */
         vuint32_t  CSSCK:4;           /* PCS to SCK Delay Scaler */
         vuint32_t  ASC:4;             /* After SCK Delay Scaler */
         vuint32_t  DT:4;              /* Delay after Transfer Scaler */
         vuint32_t  BR:4;              /* Baud Rate Scaler */
      } B;
   } DSPI_CTAR_32B_tag;

   typedef union {   /* Status Register */
      vuint32_t R;
      struct {
         vuint32_t  TCF:1;             /* Transfer Complete Flag */
         vuint32_t  TXRXS:1;           /* TX & RX Status */
         vuint32_t:1;
         vuint32_t  EOQF:1;            /* End of Queue Flag */
         vuint32_t  TFUF:1;            /* Transmit FIFO Underflow Flag */
         vuint32_t:1;
         vuint32_t  TFFF:1;            /* Transmit FIFO FIll Flag */
         vuint32_t:3;
         vuint32_t  SPEF:1;            /* SPI Parity Error Flag */
         vuint32_t:1;
         vuint32_t  RFOF:1;            /* Receive FIFO Overflow Flag */
         vuint32_t:1;
         vuint32_t  RFDF:1;            /* Receive FIFO Drain Flag */
         vuint32_t:1;
         vuint32_t  TXCTR:4;           /* TX FIFO Counter */
         vuint32_t  TXNXTPTR:4;        /* Transmit Next Pointer */
         vuint32_t  RXCTR:4;           /* RX FIFO Counter */
         vuint32_t  POPNXTPTR:4;       /* Pop Next Pointer */
      } B;
   } DSPI_SR_32B_tag;

   typedef union {   /* DMA/Interrupt Request Register */
      vuint32_t R;
      struct {
         vuint32_t  TCF_RE:1;          /* Transmission Complete Request Enable */
         vuint32_t:2;
         vuint32_t  EOQF_RE:1;         /* DSPI Finished Request Enable */
         vuint32_t  TFUF_RE:1;         /* Transmit FIFO Underflow Request Enable */
         vuint32_t:1;
         vuint32_t  TFFF_RE:1;         /* Transmit FIFO Fill Request Enable */
         vuint32_t  TFFF_DIRS:1;       /* Transmit FIFO Fill DMA or Interrupt Request Select */
         vuint32_t:2;
         vuint32_t  SPEF_RE:1;         /* SPI Parity Error Request Enable */
         vuint32_t:1;
         vuint32_t  RFOF_RE:1;         /* Receive FIFO overflow Request Enable */
         vuint32_t:1;
         vuint32_t  RFDF_RE:1;         /* Receive FIFO Drain Request Enable */
         vuint32_t  RFDF_DIRS:1;       /* Receive FIFO Drain DMA or Interrupt Request Select */
         vuint32_t:16;
      } B;
   } DSPI_RSER_32B_tag;

   typedef union {   /* PUSH TX FIFO Register */
      vuint32_t R;
      struct {
         vuint32_t  CONT:1;            /* Continuous Peripheral Chip Select Enable */
         vuint32_t  CTAS:3;            /* Clock and Transfer Attributes Select */
         vuint32_t  EOQ:1;             /* End of Queue */
         vuint32_t  CTCNT:1;           /* Clear SPI_TCNT */
         vuint32_t  PUSHR_PE:1;        /* Parity Enable */
         vuint32_t  PUSHR_PP:1;        /* Parity Polarity */
         vuint32_t  PCS7:1;            /* Peripheral Chip Select 7 */
         vuint32_t  PCS6:1;            /* Peripheral Chip Select 6 */
         vuint32_t  PCS5:1;            /* Peripheral Chip Select 5 */
         vuint32_t  PCS4:1;            /* Peripheral Chip Select 4 */
         vuint32_t  PCS3:1;            /* Peripheral Chip Select 3 */
         vuint32_t  PCS2:1;            /* Peripheral Chip Select 2 */
         vuint32_t  PCS1:1;            /* Peripheral Chip Select 1 */
         vuint32_t  PCS0:1;            /* Peripheral Chip Select 0 */
         vuint32_t  TXDATA:16;         /* Transmit Data */
      } B;
   } DSPI_PUSHR_32B_tag;

   typedef union {   /* POPR - POP RX FIFO Register */
      vuint32_t R;
      struct {
         vuint32_t  RXDATA:32;         /* Receive Data */
      } B;
   } DSPI_POPR_32B_tag;


   /* Register layout for all registers TXFR ... */

   typedef union {   /* Transmit FIFO Registers */
      vuint32_t R;
      struct {
         vuint32_t  TXCMD_TXDATA:16;   /* Transmit Command */
         vuint32_t  TXDATA:16;         /* Transmit Data */
      } B;
   } DSPI_TXFR_32B_tag;


   /* Register layout for all registers RXFR ... */

   typedef union {   /* Receive FIFO Registers */
      vuint32_t R;
      struct {
         vuint32_t  RXDATA:32;         /* Transmit Data */
      } B;
   } DSPI_RXFR_32B_tag;


   struct DSPI_tag {/* Changed from "typedef struct DSPI_struct_tag" to be able to reuse code */

                                        /* Module Configuration Register */
      DSPI_MCR_32B_tag MCR;                /* offset: 0x0000 size: 32 bit */
                                /* HCR - Hardware Configuration Register */
      DSPI_HCR_32B_tag HCR;                /* offset: 0x0004 size: 32 bit */
                                              /* Transfer Count Register */
      DSPI_TCR_32B_tag TCR;                /* offset: 0x0008 size: 32 bit */
      union {
         struct {
           /* CTAR0-1 - Clock and Transfer Attribute Registers (in slave mode) */
            DSPI_SLAVE_CTAR_32B_tag SLAVE_CTAR[2];  /* offset: 0x000C  (0x0004 x 2) */
            int8_t DSPI_reserved_0014_E0[8];
         };

                               /* Clock and Transfer Attribute Registers */
         DSPI_CTAR_32B_tag CTAR[4];        /* offset: 0x000C  (0x0004 x 4) */

         struct {
           /* CTAR0-1 - Clock and Transfer Attribute Registers (in slave mode) */
            DSPI_SLAVE_CTAR_32B_tag SLAVE_CTAR0;  /* offset: 0x000C size: 32 bit */
            DSPI_SLAVE_CTAR_32B_tag SLAVE_CTAR1;  /* offset: 0x0010 size: 32 bit */
            int8_t DSPI_reserved_0014_E2[8];
         };

         struct {
                               /* Clock and Transfer Attribute Registers */
            DSPI_CTAR_32B_tag CTAR0;       /* offset: 0x000C size: 32 bit */
            DSPI_CTAR_32B_tag CTAR1;       /* offset: 0x0010 size: 32 bit */
            DSPI_CTAR_32B_tag CTAR2;       /* offset: 0x0014 size: 32 bit */
            DSPI_CTAR_32B_tag CTAR3;       /* offset: 0x0018 size: 32 bit */
         };

      };
      int8_t DSPI_reserved_001C[16];
                                                      /* Status Register */
      DSPI_SR_32B_tag SR;                  /* offset: 0x002C size: 32 bit */
                                       /* DMA/Interrupt Request Register */
      DSPI_RSER_32B_tag RSER;              /* offset: 0x0030 size: 32 bit */
                                                /* PUSH TX FIFO Register */
      DSPI_PUSHR_32B_tag PUSHR;            /* offset: 0x0034 size: 32 bit */
                                          /* POPR - POP RX FIFO Register */
      DSPI_POPR_32B_tag POPR;              /* offset: 0x0038 size: 32 bit */
      union {
                                              /* Transmit FIFO Registers */
         DSPI_TXFR_32B_tag TXFR[5];        /* offset: 0x003C  (0x0004 x 5) */

         struct {
                                              /* Transmit FIFO Registers */
            DSPI_TXFR_32B_tag TXFR0;       /* offset: 0x003C size: 32 bit */
            DSPI_TXFR_32B_tag TXFR1;       /* offset: 0x0040 size: 32 bit */
            DSPI_TXFR_32B_tag TXFR2;       /* offset: 0x0044 size: 32 bit */
            DSPI_TXFR_32B_tag TXFR3;       /* offset: 0x0048 size: 32 bit */
            DSPI_TXFR_32B_tag TXFR4;       /* offset: 0x004C size: 32 bit */
         };

      };
      int8_t DSPI_reserved_0050[44];
      union {
                                               /* Receive FIFO Registers */
         DSPI_RXFR_32B_tag RXFR[5];        /* offset: 0x007C  (0x0004 x 5) */

         struct {
                                               /* Receive FIFO Registers */
            DSPI_RXFR_32B_tag RXFR0;       /* offset: 0x007C size: 32 bit */
            DSPI_RXFR_32B_tag RXFR1;       /* offset: 0x0080 size: 32 bit */
            DSPI_RXFR_32B_tag RXFR2;       /* offset: 0x0084 size: 32 bit */
            DSPI_RXFR_32B_tag RXFR3;       /* offset: 0x0088 size: 32 bit */
            DSPI_RXFR_32B_tag RXFR4;       /* offset: 0x008C size: 32 bit */
         };

      };
      int8_t DSPI_reserved_0090[16240];

   } /*DSPI_tag*/;


#define DSPI_A_BASEADDRESS 0xFFF90000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define DSPI_A (*(volatile DSPI_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFF90000UL))
#define DSPI_B_BASEADDRESS 0xFFF94000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define DSPI_B (*(volatile DSPI_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFF94000UL))
#define DSPI_C_BASEADDRESS 0xFFF98000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define DSPI_C (*(volatile DSPI_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFF98000UL))



/****************************************************************/
/*                                                              */
/* Module: FLEXCAN  */
/*                                                              */
/****************************************************************/
#include "ip_flexcan.h"
/****************************************************************/
/*                                                              */
/* Module: DMAMUX  */
/*                                                              */
/****************************************************************/


   /* Register layout for all registers CHCONFIG ... */

   typedef union {   /* Channel Configuration Registers */
      vuint8_t R;
      struct {
         vuint8_t   ENBL:1;            /* DMA Channel Enable */
         vuint8_t   TRIG:1;            /* DMA Channel Trigger Enable */
         vuint8_t   SOURCE:6;          /* DMA Channel Source */
      } B;
   } DMAMUX_CHCONFIG_8B_tag;


   typedef struct DMAMUX_struct_tag {

      union {
                                      /* Channel Configuration Registers */
         DMAMUX_CHCONFIG_8B_tag CHCONFIG[16];  /* offset: 0x0000  (0x0001 x 16) */

         struct {
                                      /* Channel Configuration Registers */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG0;  /* offset: 0x0000 size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG1;  /* offset: 0x0001 size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG2;  /* offset: 0x0002 size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG3;  /* offset: 0x0003 size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG4;  /* offset: 0x0004 size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG5;  /* offset: 0x0005 size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG6;  /* offset: 0x0006 size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG7;  /* offset: 0x0007 size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG8;  /* offset: 0x0008 size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG9;  /* offset: 0x0009 size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG10;  /* offset: 0x000A size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG11;  /* offset: 0x000B size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG12;  /* offset: 0x000C size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG13;  /* offset: 0x000D size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG14;  /* offset: 0x000E size: 8 bit */
            DMAMUX_CHCONFIG_8B_tag CHCONFIG15;  /* offset: 0x000F size: 8 bit */
         };

      };
      int8_t DMAMUX_reserved_0010[16368];

   } DMAMUX_tag;


#define DMAMUX_BASEADDRESS 0xFFFDC000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define DMAMUX (*(volatile DMAMUX_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFFDC000UL))



/****************************************************************/
/*                                                              */
/* Module: FR  */
/*                                                              */
/****************************************************************/

   typedef union {   /* Module Version Number */
      vuint16_t R;
      struct {
         vuint16_t  CHIVER:8;          /* CHI Version Number */
         vuint16_t  PEVER:8;           /* PE Version Number */
      } B;
   } FR_MVR_16B_tag;

   typedef union {   /* Module Configuration Register */
      vuint16_t R;
      struct {
         vuint16_t  MEN:1;             /* Module Enable */
         vuint16_t  SBFF:1;            /* System Bus Failure Freeze */
         vuint16_t  SCM:1;             /* single channel device mode */
         vuint16_t  CHB:1;             /* Channel B enable */
         vuint16_t  CHA:1;             /* channel A enable */
         vuint16_t  SFFE:1;            /* Sync. frame filter Enable */
         vuint16_t  ECCE:1;            /* ECC Functionlity Enable */
         vuint16_t:1;
         vuint16_t  FUM:1;             /* FIFO Update Mode */
         vuint16_t  FAM:1;             /* FIFO Address Mode */
         vuint16_t:1;
         vuint16_t  CLKSEL:1;          /* Protocol Engine clock source select */
         vuint16_t  BITRATE:3;         /* Bus bit rate */
         vuint16_t:1;
      } B;
   } FR_MCR_16B_tag;

   typedef union {   /* SYSTEM MEMORY BASE ADD HIGH REG */
      vuint16_t R;
      struct {
         vuint16_t  SMBA_31_16:16;     /* SYS_MEM_BASE_ADDR[31:16] */
      } B;
   } FR_SYMBADHR_16B_tag;

   typedef union {   /* SYSTEM MEMORY BASE ADD LOW  REG */
      vuint16_t R;
      struct {
         vuint16_t  SMBA_15_4:12;      /* SYS_MEM_BASE_ADDR[15:4] */
         vuint16_t:4;
      } B;
   } FR_SYMBADLR_16B_tag;

   typedef union {   /* STROBE SIGNAL CONTROL REGISTER */
      vuint16_t R;
      struct {
         vuint16_t  WMD:1;             /* DEFINES WRITE MODE OF REG */
         vuint16_t:3;
         vuint16_t  SEL:4;             /* STROBE SIGNSL SELECT */
         vuint16_t:3;
         vuint16_t  ENB:1;             /* STROBE SIGNAL ENABLE */
         vuint16_t:2;
         vuint16_t  STBPSEL:2;         /* STROBE PORT SELECT */
      } B;
   } FR_STBSCR_16B_tag;

   typedef union {   /* MESSAGE BUFFER DATA SIZE REGISTER */
      vuint16_t R;
      struct {
         vuint16_t:1;
         vuint16_t  MBSEG2DS:7;        /* MESSAGE BUFFER SEGMENT 2 DATA SIZE */
         vuint16_t:1;
         vuint16_t  MBSEG1DS:7;        /* MESSAGE BUFFER SEGMENT 1 DATA SIZE */
      } B;
   } FR_MBDSR_16B_tag;

   typedef union {   /* MESS. BUFFER SEG. SIZE & UTILISATION REG */
      vuint16_t R;
      struct {
         vuint16_t:2;
         vuint16_t  LAST_MB_SEG1:6;    /* LAST MESSAGE BUFFER IN SEG 1 */
         vuint16_t:2;
         vuint16_t  LAST_MB_UTIL:6;    /* LAST MESSAGE BUFFER UTILISED */
      } B;
   } FR_MBSSUTR_16B_tag;

   typedef union {   /* PE DRAM ACCESS REGISTER */
      vuint16_t R;
      struct {
         vuint16_t  INST:4;            /* PE DRAM ACCESS INSTRUCTION */
         vuint16_t  ADDR:11;           /* PE DRAM ACCESS ADDRESS */
         vuint16_t  DAD:1;             /* PE DRAM ACCESS DONE */
      } B;
   } FR_PEDRAR_16B_tag;

   typedef union {   /* PE DRAM DATA REGISTER */
      vuint16_t R;
      struct {
         vuint16_t  DATA:16;           /* DATA TO BE READ OR WRITTEN */
      } B;
   } FR_PEDRDR_16B_tag;

   typedef union {   /* PROTOCOL OPERATION CONTROL REG */
      vuint16_t R;
      struct {
         vuint16_t  WME:1;             /* WRITE MODE EXTERNAL CORRECTION */
         vuint16_t:3;
         vuint16_t  EOC_AP:2;          /* EXTERNAL OFFSET CORRECTION APPLICATION */
         vuint16_t  ERC_AP:2;          /* EXTERNAL RATE CORRECTION APPLICATION */
         vuint16_t  BSY:1;             /* PROTOCOL CONTROL COMMAND WRITE BUSY */
         vuint16_t:3;
         vuint16_t  POCCMD:4;          /* PROTOCOL CONTROL COMMAND */
      } B;
   } FR_POCR_16B_tag;

   typedef union {   /* GLOBAL INTERRUPT FLAG & ENABLE REG */
      vuint16_t R;
      struct {
         vuint16_t  MIF:1;             /* MODULE INTERRUPT FLAG */
         vuint16_t  PRIF:1;            /* PROTOCOL INTERRUPT FLAG */
         vuint16_t  CHIF:1;            /* CHI INTERRUPT FLAG */
         vuint16_t  WUPIF:1;           /* WAKEUP INTERRUPT FLAG */
         vuint16_t  FAFBIF:1;          /* RECEIVE FIFO CHANNEL B ALMOST FULL INTERRUPT FLAG */
         vuint16_t  FAFAIF:1;          /* RECEIVE FIFO CHANNEL A ALMOST FULL INTERRUPT FLAG */
         vuint16_t  RBIF:1;            /* RECEIVE MESSAGE BUFFER INTERRUPT FLAG */
         vuint16_t  TBIF:1;            /* TRANSMIT BUFFER INTERRUPT FLAG */
         vuint16_t  MIE:1;             /* MODULE INTERRUPT ENABLE */
         vuint16_t  PRIE:1;            /* PROTOCOL INTERRUPT ENABLE */
         vuint16_t  CHIE:1;            /* CHI INTERRUPT ENABLE */
         vuint16_t  WUPIE:1;           /* WAKEUP INTERRUPT ENABLE */
         vuint16_t  FAFBIE:1;          /* RECEIVE FIFO CHANNEL B NOT EMPTY INTERRUPT ENABLE */
         vuint16_t  FAFAIE:1;          /* RECEIVE FIFO CHANNEL A NOT EMPTY INTERRUPT ENABLE */
         vuint16_t  RBIE:1;            /* RECEIVE BUFFER INTERRUPT ENABLE */
         vuint16_t  TBIE:1;            /* TRANSMIT BUFFER INTERRUPT ENABLE */
      } B;
   } FR_GIFER_16B_tag;

   typedef union {   /* PROTOCOL INTERRUPT FLAG REGISTER 0 */
      vuint16_t R;
      struct {
         vuint16_t  FATL_IF:1;         /* FATAL PROTOCOL ERROR INTERRUPT FLAG */
         vuint16_t  INTL_IF:1;         /* INTERNAL PROTOCOL ERROR INTERRUPT FLAG */
         vuint16_t  ILCF_IF:1;         /* ILLEGAL PROTOCOL CONFIGURATION INTERRUPT FLAG */
         vuint16_t  CSA_IF:1;          /* COLDSTART ABORT INTERRUPT FLAG */
         vuint16_t  MRC_IF:1;          /* MISSING RATE CORRECTION INTERRUPT FLAG */
         vuint16_t  MOC_IF:1;          /* MISSING OFFSET CORRECTION INTERRUPT FLAG */
         vuint16_t  CCL_IF:1;          /* CLOCK CORRECTION LIMIT REACHED INTERRUPT FLAG */
         vuint16_t  MXS_IF:1;          /* MAX SYNC FRAMES DETECTED INTERRUPT FLAG */
         vuint16_t  MTX_IF:1;          /* MEDIA ACCESS TEST SYMBOL RECEIVED INTERRUPT FLAG */
         vuint16_t  LTXB_IF:1;         /* pLATESTTX VIOLATION ON CHANNEL B INTERRUPT FLAG */
         vuint16_t  LTXA_IF:1;         /* pLATESTTX VIOLATION ON CHANNEL A INTERRUPT FLAG */
         vuint16_t  TBVB_IF:1;         /* TRANSMISSION ACROSS BOUNDARY ON CHANNEL B INTERRUPT FLAG */
         vuint16_t  TBVA_IF:1;         /* TRANSMISSION ACROSS BOUNDARY ON CHANNEL A INTERRUPT FLAG */
         vuint16_t  TI2_IF:1;          /* TIMER 2 EXPIRED INTERRUPT FLAG */
         vuint16_t  TI1_IF:1;          /* TIMER 1 EXPIRED INTERRUPT FLAG */
         vuint16_t  CYS_IF:1;          /* CYCLE START INTERRUPT FLAG */
      } B;
   } FR_PIFR0_16B_tag;

   typedef union {   /* PROTOCOL INTERRUPT FLAG REGISTER 1 */
      vuint16_t R;
      struct {
         vuint16_t  EMC_IF:1;          /* ERROR MODE CHANGED INTERRUPT FLAG */
         vuint16_t  IPC_IF:1;          /* ILLEGAL PROTOCOL CONTROL COMMAND INTERRUPT FLAG */
         vuint16_t  PECF_IF:1;         /* PROTOCOL ENGINE COMMUNICATION FAILURE INTERRUPT FLAG */
         vuint16_t  PSC_IF:1;          /* PROTOCOL STATE CHANGED INTERRUPT FLAG */
         vuint16_t  SSI3_IF:1;         /* SLOT STATUS COUNTER 3 INCREMENTED INTERRUPT FLAG */
         vuint16_t  SSI2_IF:1;         /* SLOT STATUS COUNTER 2 INCREMENTED INTERRUPT FLAG */
         vuint16_t  SSI1_IF:1;         /* SLOT STATUS COUNTER 1 INCREMENTED INTERRUPT FLAG */
         vuint16_t  SSI0_IF:1;         /* SLOT STATUS COUNTER 0 INCREMENTED INTERRUPT FLAG */
         vuint16_t:2;
         vuint16_t  EVT_IF:1;          /* EVEN CYCLE TABLE WRITTEN INTERRUPT FLAG */
         vuint16_t  ODT_IF:1;          /* ODD CYCLE TABLE WRITTEN INTERRUPT FLAG */
         vuint16_t:4;
      } B;
   } FR_PIFR1_16B_tag;

   typedef union {   /* PROTOCOL INTERRUPT ENABLE REGISTER 0 */
      vuint16_t R;
      struct {
         vuint16_t  FATL_IE:1;         /* FATAL PROTOCOL ERROR INTERRUPT ENABLE */
         vuint16_t  INTL_IE:1;         /* INTERNAL PROTOCOL ERROR INTERRUPT ENABLE */
         vuint16_t  ILCF_IE:1;         /* ILLEGAL PROTOCOL CONFIGURATION INTERRUPT ENABLE */
         vuint16_t  CSA_IE:1;          /* COLDSTART ABORT INTERRUPT ENABLE */
         vuint16_t  MRC_IE:1;          /* MISSING RATE CORRECTION INTERRUPT ENABLE */
         vuint16_t  MOC_IE:1;          /* MISSING OFFSET CORRECTION INTERRUPT ENABLE */
         vuint16_t  CCL_IE:1;          /* CLOCK CORRECTION LIMIT REACHED */
         vuint16_t  MXS_IE:1;          /* MAX SYNC FRAMES DETECTED INTERRUPT ENABLE */
         vuint16_t  MTX_IE:1;          /* MEDIA ACCESS TEST SYMBOL RECEIVED INTERRUPT ENABLE */
         vuint16_t  LTXB_IE:1;         /* pLATESTTX VIOLATION ON CHANNEL B INTERRUPT ENABLE */
         vuint16_t  LTXA_IE:1;         /* pLATESTTX VIOLATION ON CHANNEL A INTERRUPT ENABLE */
         vuint16_t  TBVB_IE:1;         /* TRANSMISSION ACROSS BOUNDARY ON CHANNEL B INTERRUPT ENABLE */
         vuint16_t  TBVA_IE:1;         /* TRANSMISSION ACROSS BOUNDARY ON CHANNEL A INTERRUPT ENABLE */
         vuint16_t  TI2_IE:1;          /* TIMER 2 EXPIRED INTERRUPT ENABLE */
         vuint16_t  TI1_IE:1;          /* TIMER 1 EXPIRED INTERRUPT ENABLE */
         vuint16_t  CYS_IE:1;          /* CYCLE START INTERRUPT ENABLE */
      } B;
   } FR_PIER0_16B_tag;

   typedef union {   /* PROTOCOL INTERRUPT ENABLE REGISTER 1 */
      vuint16_t R;
      struct {
         vuint16_t  EMC_IE:1;          /* ERROR MODE CHANGED INTERRUPT Enable */
         vuint16_t  IPC_IE:1;          /* ILLEGAL PROTOCOL CONTROL COMMAND INTERRUPT Enable */
         vuint16_t  PECF_IE:1;         /* PROTOCOL ENGINE COMMUNICATION FAILURE INTERRUPT Enable */
         vuint16_t  PSC_IE:1;          /* PROTOCOL STATE CHANGED INTERRUPT Enable */
         vuint16_t  SSI3_IE:1;         /* SLOT STATUS COUNTER 3 INCREMENTED INTERRUPT Enable */
         vuint16_t  SSI2_IE:1;         /* SLOT STATUS COUNTER 2 INCREMENTED INTERRUPT Enable */
         vuint16_t  SSI1_IE:1;         /* SLOT STATUS COUNTER 1 INCREMENTED INTERRUPT Enable */
         vuint16_t  SSI0_IE:1;         /* SLOT STATUS COUNTER 0 INCREMENTED INTERRUPT Enable */
         vuint16_t:2;
         vuint16_t  EVT_IE:1;          /* EVEN CYCLE TABLE WRITTEN INTERRUPT Enable */
         vuint16_t  ODT_IE:1;          /* ODD CYCLE TABLE WRITTEN INTERRUPT Enable */
         vuint16_t:4;
      } B;
   } FR_PIER1_16B_tag;

   typedef union {   /* CHI ERROR FLAG REGISTER */
      vuint16_t R;
      struct {
         vuint16_t  FRLB_EF:1;         /* FRAME LOST CHANNEL B ERROR FLAG */
         vuint16_t  FRLA_EF:1;         /* FRAME LOST CHANNEL A ERROR FLAG */
         vuint16_t  PCMI_EF:1;         /* PROTOCOL COMMAND IGNORED ERROR FLAG */
         vuint16_t  FOVB_EF:1;         /* RECEIVE FIFO OVERRUN CHANNEL B ERROR FLAG */
         vuint16_t  FOVA_EF:1;         /* RECEIVE FIFO OVERRUN CHANNEL A ERROR FLAG */
         vuint16_t  MBS_EF:1;          /* MESSAGE BUFFER SEARCH ERROR FLAG */
         vuint16_t  MBU_EF:1;          /* MESSAGE BUFFER UTILIZATION ERROR FLAG */
         vuint16_t  LCK_EF:1;          /* LOCK ERROR FLAG */
         vuint16_t  DBL_EF:1;          /* DOUBLE TRANSMIT MESSAGE BUFFER LOCK ERROR FLAG */
         vuint16_t  SBCF_EF:1;         /* SYSTEM BUS COMMUNICATION FAILURE ERROR FLAG */
         vuint16_t  FID_EF:1;          /* FRAME ID ERROR FLAG */
         vuint16_t  DPL_EF:1;          /* DYNAMIC PAYLOAD LENGTH ERROR FLAG */
         vuint16_t  SPL_EF:1;          /* STATIC PAYLOAD LENGTH ERROR FLAG */
         vuint16_t  NML_EF:1;          /* NETWORK MANAGEMENT LENGTH ERROR FLAG */
         vuint16_t  NMF_EF:1;          /* NETWORK MANAGEMENT FRAME ERROR FLAG */
         vuint16_t  ILSA_EF:1;         /* ILLEGAL SYSTEM MEMORY ACCESS ERROR FLAG */
      } B;
   } FR_CHIERFR_16B_tag;

   typedef union {   /* Message Buffer Interrupt Vector Register */
      vuint16_t R;
      struct {
         vuint16_t:2;
         vuint16_t  TBIVEC:6;          /* Transmit Buffer Interrupt Vector */
         vuint16_t:2;
         vuint16_t  RBIVEC:6;          /* Receive Buffer Interrupt Vector */
      } B;
   } FR_MBIVEC_16B_tag;

   typedef union {   /* Channel A Status Error Counter Register */
      vuint16_t R;
      struct {
         vuint16_t  STATUS_ERR_CNT:16;   /* Channel Status Error Counter */
      } B;
   } FR_CASERCR_16B_tag;

   typedef union {   /* Channel B Status Error Counter Register */
      vuint16_t R;
      struct {
         vuint16_t  STATUS_ERR_CNT:16;   /* Channel Status Error Counter */
      } B;
   } FR_CBSERCR_16B_tag;

   typedef union {   /* Protocol Status Register 0 */
      vuint16_t R;
      struct {
         vuint16_t  ERRMODE:2;         /* Error Mode */
         vuint16_t  SLOTMODE:2;        /* Slot Mode */
         vuint16_t:1;
         vuint16_t  PROTSTATE:3;       /* Protocol State */
         vuint16_t  STARTUPSTATE:4;    /* Startup State */
         vuint16_t  WAKEUPSTATE:4;     /* Wakeup Status */
      } B;
   } FR_PSR0_16B_tag;

   typedef union {   /* Protocol Status Register 1 */
      vuint16_t R;
      struct {
         vuint16_t  CSAA:1;            /* Coldstart Attempt Aborted Flag */
         vuint16_t  CSP:1;             /* Leading Coldstart Path */
         vuint16_t:1;
         vuint16_t  REMCSAT:5;         /* Remaining Coldstart Attempts */
         vuint16_t  CPN:1;             /* Leading Coldstart Path Noise */
         vuint16_t  HHR:1;             /* Host Halt Request Pending */
         vuint16_t  FRZ:1;             /* Freeze Occurred */
         vuint16_t  APTAC:5;           /* Allow Passive to Active Counter */
      } B;
   } FR_PSR1_16B_tag;

   typedef union {   /* Protocol Status Register 2 */
      vuint16_t R;
      struct {
         vuint16_t  NBVB:1;            /* NIT Boundary Violation on Channel B */
         vuint16_t  NSEB:1;            /* NIT Syntax Error on Channel B */
         vuint16_t  STCB:1;            /* Symbol Window Transmit Conflict on Channel B */
         vuint16_t  SSVB:1;            /* Symbol Window Boundary Violation on Channel B */
         vuint16_t  SSEB:1;            /* Symbol Window Syntax Error on Channel B */
         vuint16_t  MTB:1;             /* Media Access Test Symbol MTS Received on Channel B */
         vuint16_t  NBVA:1;            /* NIT Boundary Violation on Channel A */
         vuint16_t  NSEA:1;            /* NIT Syntax Error on Channel A */
         vuint16_t  STCA:1;            /* Symbol Window Transmit Conflict on Channel A */
         vuint16_t  SBVA:1;            /* Symbol Window Boundary Violation on Channel A */
         vuint16_t  SSEA:1;            /* Symbol Window Syntax Error on Channel A */
         vuint16_t  MTA:1;             /* Media Access Test Symbol MTS Received on Channel A */
         vuint16_t  CLKCORRFAILCNT:4;   /* Clock Correction Failed Counter */
      } B;
   } FR_PSR2_16B_tag;

   typedef union {   /* Protocol Status Register 3 */
      vuint16_t R;
      struct {
         vuint16_t:2;
         vuint16_t  WUB:1;             /* Wakeup Symbol Received on Channel B */
         vuint16_t  ABVB:1;            /* Aggregated Boundary Violation on Channel B */
         vuint16_t  AACB:1;            /* Aggregated Additional Communication on Channel B */
         vuint16_t  ACEB:1;            /* Aggregated Content Error on Channel B */
         vuint16_t  ASEB:1;            /* Aggregated Syntax Error on Channel B */
         vuint16_t  AVFB:1;            /* Aggregated Valid Frame on Channel B */
         vuint16_t:2;
         vuint16_t  WUA:1;             /* Wakeup Symbol Received on Channel A */
         vuint16_t  ABVA:1;            /* Aggregated Boundary Violation on Channel A */
         vuint16_t  AACA:1;            /* Aggregated Additional Communication on Channel A */
         vuint16_t  ACEA:1;            /* Aggregated Content Error on Channel A */
         vuint16_t  ASEA:1;            /* Aggregated Syntax Error on Channel A */
         vuint16_t  AVFA:1;            /* Aggregated Valid Frame on Channel A */
      } B;
   } FR_PSR3_16B_tag;

   typedef union {   /* Macrotick Counter Register */
      vuint16_t R;
      struct {
         vuint16_t:2;
         vuint16_t  MTCT:14;           /* Macrotick Counter */
      } B;
   } FR_MTCTR_16B_tag;

   typedef union {   /* Cycle Counter Register */
      vuint16_t R;
      struct {
         vuint16_t:10;
         vuint16_t  CYCCNT:6;          /* Cycle Counter */
      } B;
   } FR_CYCTR_16B_tag;

   typedef union {   /* Slot Counter Channel A Register */
      vuint16_t R;
      struct {
         vuint16_t:5;
         vuint16_t  SLOTCNTA:11;       /* Slot Counter Value for Channel A */
      } B;
   } FR_SLTCTAR_16B_tag;

   typedef union {   /* Slot Counter Channel B Register */
      vuint16_t R;
      struct {
         vuint16_t:5;
         vuint16_t  SLOTCNTB:11;       /* Slot Counter Value for Channel B */
      } B;
   } FR_SLTCTBR_16B_tag;

   typedef union {   /* Rate Correction Value Register */
      vuint16_t R;
      struct {
         vuint16_t  RATECORR:16;       /* Rate Correction Value */
      } B;
   } FR_RTCORVR_16B_tag;

   typedef union {   /* Offset Correction Value Register */
      vuint16_t R;
      struct {
         vuint16_t:6;
         vuint16_t  OFFSETCORR:10;     /* Offset Correction Value */
      } B;
   } FR_OFCORVR_16B_tag;

   typedef union {   /* Combined Interrupt Flag Register */
      vuint16_t R;
      struct {
         vuint16_t:8;
         vuint16_t  MIF:1;             /* Module Interrupt Flag */
         vuint16_t  PRIF:1;            /* Protocol Interrupt Flag */
         vuint16_t  CHIF:1;            /* CHI Interrupt Flag */
         vuint16_t  WUPIF:1;           /* Wakeup Interrupt Flag */
         vuint16_t  FAFBIF:1;          /* Receive FIFO channel B Almost Full Interrupt Flag */
         vuint16_t  FAFAIF:1;          /* Receive FIFO channel A Almost Full Interrupt Flag */
         vuint16_t  RBIF:1;            /* Receive Message Buffer Interrupt Flag */
         vuint16_t  TBIF:1;            /* Transmit Message Buffer Interrupt Flag */
      } B;
   } FR_CIFR_16B_tag;

   typedef union {   /* System Memory Access Time-Out Register */
      vuint16_t R;
      struct {
         vuint16_t:8;
         vuint16_t  TIMEOUT:8;         /* Time-Out */
      } B;
   } FR_SYMATOR_16B_tag;

   typedef union {   /* Sync Frame Counter Register */
      vuint16_t R;
      struct {
         vuint16_t  SFEVB:4;           /* Sync Frames Channel B, even cycle */
         vuint16_t  SFEVA:4;           /* Sync Frames Channel A, even cycle */
         vuint16_t  SFODB:4;           /* Sync Frames Channel B, odd cycle */
         vuint16_t  SFODA:4;           /* Sync Frames Channel A, odd cycle */
      } B;
   } FR_SFCNTR_16B_tag;

   typedef union {   /* Sync Frame Table Offset Register */
      vuint16_t R;
      struct {
         vuint16_t  SFT_OFFSET:15;     /* Sync Frame Table Offset */
         vuint16_t:1;
      } B;
   } FR_SFTOR_16B_tag;

   typedef union {   /* Sync Frame Table Configuration, Control, Status Register */
      vuint16_t R;
      struct {
         vuint16_t  ELKT:1;            /* Even Cycle Tables Lock/Unlock Trigger */
         vuint16_t  OLKT:1;            /* Odd Cycle Tables Lock/Unlock Trigger */
         vuint16_t  CYCNUM:6;          /* Cycle Number */
         vuint16_t  ELKS:1;            /* Even Cycle Tables Lock Status */
         vuint16_t  OLKS:1;            /* Odd Cycle Tables Lock Status */
         vuint16_t  EVAL:1;            /* Even Cycle Tables Valid */
         vuint16_t  OVAL:1;            /* Odd Cycle Tables Valid */
         vuint16_t:1;
         vuint16_t  OPT:1;             /* One Pair Trigger */
         vuint16_t  SDVEN:1;           /* Sync Frame Deviation Table Enable */
         vuint16_t  SIVEN:1;           /* Sync Frame ID Table Enable */
      } B;
   } FR_SFTCCSR_16B_tag;

   typedef union {   /* Sync Frame ID Rejection Filter */
      vuint16_t R;
      struct {
         vuint16_t:6;
         vuint16_t  SYNFRID:10;        /* Sync Frame Rejection ID */
      } B;
   } FR_SFIDRFR_16B_tag;

   typedef union {   /* Sync Frame ID Acceptance Filter Value Register */
      vuint16_t R;
      struct {
         vuint16_t:6;
         vuint16_t  FVAL:10;           /* Filter Value */
      } B;
   } FR_SFIDAFVR_16B_tag;

   typedef union {   /* Sync Frame ID Acceptance Filter Mask Register */
      vuint16_t R;
      struct {
         vuint16_t:6;
         vuint16_t  FMSK:10;           /* Filter Mask */
      } B;
   } FR_SFIDAFMR_16B_tag;


   /* Register layout for all registers NMV ... */

   typedef union {   /* Network Management Vector Byte Register */
      vuint8_t R;
   } FR_NMV_8B_tag;


   /* Register layout for all registers NMVR ... */

   typedef union {   /* Network Management Vector Register */
      vuint16_t R;
      struct {
         vuint16_t  NMVP_15_8:8;       /* Network Management Vector Part */
         vuint16_t  NMVP_7_0:8;        /* Network Management Vector Part */
      } B;
   } FR_NMVR_16B_tag;

   typedef union {   /* Network Management Vector Length Register */
      vuint16_t R;
      struct {
         vuint16_t:12;
         vuint16_t  NMVL:4;            /* Network Management Vector Length */
      } B;
   } FR_NMVLR_16B_tag;

   typedef union {   /* Timer Configuration and Control Register */
      vuint16_t R;
      struct {
         vuint16_t:2;
         vuint16_t  T2_CFG:1;          /* Timer T2 Configuration */
         vuint16_t  T2_REP:1;          /* Timer T2 Repetitive Mode */
         vuint16_t:1;
         vuint16_t  T2SP:1;            /* Timer T2 Stop */
         vuint16_t  T2TR:1;            /* Timer T2 Trigger */
         vuint16_t  T2ST:1;            /* Timer T2 State */
         vuint16_t:3;
         vuint16_t  T1_REP:1;          /* Timer T1 Repetitive Mode */
         vuint16_t:1;
         vuint16_t  T1SP:1;            /* Timer T1 Stop */
         vuint16_t  T1TR:1;            /* Timer T1 Trigger */
         vuint16_t  T1ST:1;            /* Timer T1 State */
      } B;
   } FR_TICCR_16B_tag;

   typedef union {   /* Timer 1 Cycle Set Register */
      vuint16_t R;
      struct {
         vuint16_t:2;
         vuint16_t  T1_CYC_VAL:6;      /* Timer T1 Cycle Filter Value */
         vuint16_t:2;
         vuint16_t  T1_CYC_MSK:6;      /* Timer T1 Cycle Filter Mask */
      } B;
   } FR_TI1CYSR_16B_tag;

   typedef union {   /* Timer 1 Macrotick Offset Register */
      vuint16_t R;
      struct {
         vuint16_t:2;
         vuint16_t  T1_MTOFFSET:14;    /* Timer 1 Macrotick Offset */
      } B;
   } FR_TI1MTOR_16B_tag;

   typedef union {   /* Timer 2 Configuration Register 0 */
      vuint16_t R;
      struct {
         vuint16_t:2;
         vuint16_t  T2_CYC_VAL:6;      /* Timer T2 Cycle Filter Value */
         vuint16_t:2;
         vuint16_t  T2_CYC_MSK:6;      /* Timer T2 Cycle Filter Mask */
      } B;
   } FR_TI2CR0_16B_tag;

   typedef union {   /* Timer 2 Configuration Register 1 */
      vuint16_t R;
      struct {
         vuint16_t  T2_MTCNT:16;       /* Timer T2 Macrotick Offset */
      } B;
   } FR_TI2CR1_16B_tag;

   typedef union {   /* Slot Status Selection Register */
      vuint16_t R;
      struct {
         vuint16_t  WMD:1;             /* Write Mode */
         vuint16_t:1;
         vuint16_t  SEL:2;             /* Selector */
         vuint16_t:1;
         vuint16_t  SLOTNUMBER:11;     /* Slot Number */
      } B;
   } FR_SSSR_16B_tag;

   typedef union {   /* Slot Status Counter Condition Register */
      vuint16_t R;
      struct {
         vuint16_t  WMD:1;             /* Write Mode */
         vuint16_t:1;
         vuint16_t  SEL:2;             /* Selector */
         vuint16_t:1;
         vuint16_t  CNTCFG:2;          /* Counter Configuration */
         vuint16_t  MCY:1;             /* Multi Cycle Selection */
         vuint16_t  VFR:1;             /* Valid Frame Restriction */
         vuint16_t  SYF:1;             /* Sync Frame Restriction */
         vuint16_t  NUF:1;             /* Null Frame Restriction */
         vuint16_t  SUF:1;             /* Startup Frame Restriction */
         vuint16_t  STATUSMASK:4;      /* Slot Status Mask */
      } B;
   } FR_SSCCR_16B_tag;


   /* Register layout for all registers SSR ... */

   typedef union {   /* Slot Status Register */
      vuint16_t R;
      struct {
         vuint16_t  VFB:1;             /* Valid Frame on Channel B */
         vuint16_t  SYB:1;             /* Sync Frame Indicator Channel B */
         vuint16_t  NFB:1;             /* Null Frame Indicator Channel B */
         vuint16_t  SUB:1;             /* Startup Frame Indicator Channel B */
         vuint16_t  SEB:1;             /* Syntax Error on Channel B */
         vuint16_t  CEB:1;             /* Content Error on Channel B */
         vuint16_t  BVB:1;             /* Boundary Violation on Channel B */
         vuint16_t  TCB:1;             /* Transmission Conflict on Channel B */
         vuint16_t  VFA:1;             /* Valid Frame on Channel A */
         vuint16_t  SYA:1;             /* Sync Frame Indicator Channel A */
         vuint16_t  NFA:1;             /* Null Frame Indicator Channel A */
         vuint16_t  SUA:1;             /* Startup Frame Indicator Channel A */
         vuint16_t  SEA:1;             /* Syntax Error on Channel A */
         vuint16_t  CEA:1;             /* Content Error on Channel A */
         vuint16_t  BVA:1;             /* Boundary Violation on Channel A */
         vuint16_t  TCA:1;             /* Transmission Conflict on Channel A */
      } B;
   } FR_SSR_16B_tag;


   /* Register layout for all registers SSCR ... */

   typedef union {   /* Slot Status Counter Register */
      vuint16_t R;
      struct {
         vuint16_t  SLOTSTSTUSCNT:16;   /* Slot Status Counter */
      } B;
   } FR_SSCR_16B_tag;

   typedef union {   /* MTS A Configuration Register */
      vuint16_t R;
      struct {
         vuint16_t  MTE:1;             /* Media Access Test Symbol Transmission Enable */
         vuint16_t:1;
         vuint16_t  CYCCNTMSK:6;       /* Cycle Counter Mask */
         vuint16_t:2;
         vuint16_t  CYCCNTVAL:6;       /* Cycle Counter Value */
      } B;
   } FR_MTSACFR_16B_tag;

   typedef union {   /* MTS B Configuration Register */
      vuint16_t R;
      struct {
         vuint16_t  MTE:1;             /* Media Access Test Symbol Transmission Enable */
         vuint16_t:1;
         vuint16_t  CYCCNTMSK:6;       /* Cycle Counter Mask */
         vuint16_t:2;
         vuint16_t  CYCCNTVAL:6;       /* Cycle Counter Value */
      } B;
   } FR_MTSBCFR_16B_tag;

   typedef union {   /* Receive Shadow Buffer Index Register */
      vuint16_t R;
      struct {
         vuint16_t  WMD:1;             /* Write Mode */
         vuint16_t:1;
         vuint16_t  SEL:2;             /* Selector */
         vuint16_t:5;
         vuint16_t  RSBIDX:7;          /* Receive Shadow Buffer Index */
      } B;
   } FR_RSBIR_16B_tag;

   typedef union {   /* Receive FIFO Watermark and Selection Register */
      vuint16_t R;
      struct {
         vuint16_t  WM:8;              /* Watermark Value */
         vuint16_t:7;
         vuint16_t  SEL:1;             /* Select */
      } B;
   } FR_RFWMSR_16B_tag;

   typedef union {   /* Receive FIFO Start Index Register */
      vuint16_t R;
      struct {
         vuint16_t:6;
         vuint16_t  SIDX:10;           /* Start Index */
      } B;
   } FR_RF_RFSIR_16B_tag;

   typedef union {   /* Receive FIFO Depth and Size Register */
      vuint16_t R;
      struct {
         vuint16_t  FIFO_DEPTH:8;      /* FIFO Depth */
         vuint16_t:1;
         vuint16_t  ENTRY_SIZE:7;      /* Entry Size */
      } B;
   } FR_RFDSR_16B_tag;

   typedef union {   /* Receive FIFO A Read Index Register */
      vuint16_t R;
      struct {
         vuint16_t:6;
         vuint16_t  RDIDX:10;          /* Read Index */
      } B;
   } FR_RFARIR_16B_tag;

   typedef union {   /* Receive FIFO B Read Index Register */
      vuint16_t R;
      struct {
         vuint16_t:6;
         vuint16_t  RDIDX:10;          /* Read Index */
      } B;
   } FR_RFBRIR_16B_tag;

   typedef union {   /* Receive FIFO Message ID Acceptance Filter Value Register */
      vuint16_t R;
      struct {
         vuint16_t  MIDAFVAL:16;       /* Message ID Acceptance Filter Value */
      } B;
   } FR_RFMIDAFVR_16B_tag;

   typedef union {   /* Receive FIFO Message ID Acceptance Filter Mask Register */
      vuint16_t R;
      struct {
         vuint16_t  MIDAFMSK:16;       /* Message ID Acceptance Filter Mask */
      } B;
   } FR_RFMIDAFMR_16B_tag;

   typedef union {   /* Receive FIFO Frame ID Rejection Filter Value Register */
      vuint16_t R;
      struct {
         vuint16_t:5;
         vuint16_t  FIDRFVAL:11;       /* Frame ID Rejection Filter Value */
      } B;
   } FR_RFFIDRFVR_16B_tag;

   typedef union {   /* Receive FIFO Frame ID Rejection Filter Mask Register */
      vuint16_t R;
      struct {
         vuint16_t:5;
         vuint16_t  FIDRFMSK:11;       /* Frame ID Rejection Filter Mask */
      } B;
   } FR_RFFIDRFMR_16B_tag;

   typedef union {   /* Receive FIFO Range Filter Configuration Register */
      vuint16_t R;
      struct {
         vuint16_t  WMD:1;             /* Write Mode */
         vuint16_t  IBD:1;             /* Interval Boundary */
         vuint16_t  SEL:2;             /* Filter Selector */
         vuint16_t:1;
         vuint16_t  SID:11;            /* Slot ID */
      } B;
   } FR_RFRFCFR_16B_tag;

   typedef union {   /* Receive FIFO Range Filter Control Register */
      vuint16_t R;
      struct {
         vuint16_t:4;
         vuint16_t  F3MD:1;            /* Range Filter 3 Mode */
         vuint16_t  F2MD:1;            /* Range Filter 2 Mode */
         vuint16_t  F1MD:1;            /* Range Filter 1 Mode */
         vuint16_t  F0MD:1;            /* Range Filter 0 Mode */
         vuint16_t:4;
         vuint16_t  F3EN:1;            /* Range Filter 3 Enable */
         vuint16_t  F2EN:1;            /* Range Filter 2 Enable */
         vuint16_t  F1EN:1;            /* Range Filter 1 Enable */
         vuint16_t  F0EN:1;            /* Range Filter 0 Enable */
      } B;
   } FR_RFRFCTR_16B_tag;

   typedef union {   /* Last Dynamic Transmit Slot Channel A Register */
      vuint16_t R;
      struct {
         vuint16_t:5;
         vuint16_t  LASTDYNTXSLOTA:11;   /* Last Dynamic Transmission Slot Channel A */
      } B;
   } FR_LDTXSLAR_16B_tag;

   typedef union {   /* Last Dynamic Transmit Slot Channel B Register */
      vuint16_t R;
      struct {
         vuint16_t:5;
         vuint16_t  LASTDYNTXSLOTB:11;   /* Last Dynamic Transmission Slot Channel B */
      } B;
   } FR_LDTXSLBR_16B_tag;

   typedef union {   /* Protocol Configuration Register 0 */
      vuint16_t R;
      struct {
         vuint16_t  ACTION_POINT_OFFSET:6;   /* gdActionPointOffset - 1 */
         vuint16_t  STATIC_SLOT_LENGTH:10;   /* gdStaticSlot */
      } B;
   } FR_PCR0_16B_tag;

   typedef union {   /* Protocol Configuration Register 1 */
      vuint16_t R;
      struct {
         vuint16_t:2;
         vuint16_t  MACRO_AFTER_FIRST_STATIC_SLOT:14;   /* gMacroPerCycle - gdStaticSlot */
      } B;
   } FR_PCR1_16B_tag;

   typedef union {   /* Protocol Configuration Register 2 */
      vuint16_t R;
      struct {
         vuint16_t  MINISLOT_AFTER_ACTION_POINT:6;   /* gdMinislot - gdMinislotActionPointOffset - 1 */
         vuint16_t  NUMBER_OF_STATIC_SLOTS:10;   /* gNumberOfStaticSlots */
      } B;
   } FR_PCR2_16B_tag;

   typedef union {   /* Protocol Configuration Register 3 */
      vuint16_t R;
      struct {
         vuint16_t  WAKEUP_SYMBOL_RX_LOW:6;   /* gdWakeupSymbolRxLow */
         vuint16_t  MINISLOT_ACTION_POINT_OFFSET:5;   /* gdMinislotActionPointOffset - 1 */
         vuint16_t  COLDSTART_ATTEMPTS:5;   /* gColdstartAttempts */
      } B;
   } FR_PCR3_16B_tag;

   typedef union {   /* Protocol Configuration Register 4 */
      vuint16_t R;
      struct {
         vuint16_t  CAS_RX_LOW_MAX:7;   /* gdCASRxLowMax - 1 */
         vuint16_t  WAKEUP_SYMBOL_RX_WINDOW:9;   /* gdWakeupSymbolRxWindow */
      } B;
   } FR_PCR4_16B_tag;

   typedef union {   /* Protocol Configuration Register 5 */
      vuint16_t R;
      struct {
         vuint16_t  TSS_TRANSMITTER:4;   /* gdTSSTransmitter */
         vuint16_t  WAKEUP_SYMBOL_TX_LOW:6;   /* gdWakeupSymbolTxLow */
         vuint16_t  WAKEUP_SYMBOL_RX_IDLE:6;   /* gdWakeupSymbolRxIdle */
      } B;
   } FR_PCR5_16B_tag;

   typedef union {   /* Protocol Configuration Register 6 */
      vuint16_t R;
      struct {
         vuint16_t:1;
         vuint16_t  SYMBOL_WINDOW_AFTER_ACTION_POINT:8;   /* gdSymbolWindow - gdActionPointOffset - 1 */
         vuint16_t  MACRO_INITIAL_OFFSET_A:7;   /* pMacroInitialOffset[A] */
      } B;
   } FR_PCR6_16B_tag;

   typedef union {   /* Protocol Configuration Register 7 */
      vuint16_t R;
      struct {
         vuint16_t  DECODING_CORRECTION_B:9;   /* pDecodingCorrection + pDelayCompensation[B] + 2 */
         vuint16_t  MICRO_PER_MACRO_NOM_HALF:7;   /* round(pMicroPerMacroNom / 2) */
      } B;
   } FR_PCR7_16B_tag;

   typedef union {   /* Protocol Configuration Register 8 */
      vuint16_t R;
      struct {
         vuint16_t  MAX_WITHOUT_CLOCK_CORRECTION_FATAL:4;   /* gMaxWithoutClockCorrectionFatal */
         vuint16_t  MAX_WITHOUT_CLOCK_CORRECTION_PASSIVE:4;   /* gMaxWithoutClockCorrectionPassive */
         vuint16_t  WAKEUP_SYMBOL_TX_IDLE:8;   /* gdWakeupSymbolTxIdle */
      } B;
   } FR_PCR8_16B_tag;

   typedef union {   /* Protocol Configuration Register 9 */
      vuint16_t R;
      struct {
         vuint16_t  MINISLOT_EXISTS:1;   /* gNumberOfMinislots!=0 */
         vuint16_t  SYMBOL_WINDOW_EXISTS:1;   /* gdSymbolWindow!=0 */
         vuint16_t  OFFSET_CORRECTION_OUT:14;   /* pOffsetCorrectionOut */
      } B;
   } FR_PCR9_16B_tag;

   typedef union {   /* Protocol Configuration Register 10 */
      vuint16_t R;
      struct {
         vuint16_t  SINGLE_SLOT_ENABLED:1;   /* pSingleSlotEnabled */
         vuint16_t  WAKEUP_CHANNEL:1;   /* pWakeupChannel */
         vuint16_t  MACRO_PER_CYCLE:14;   /* pMicroPerCycle */
      } B;
   } FR_PCR10_16B_tag;

   typedef union {   /* Protocol Configuration Register 11 */
      vuint16_t R;
      struct {
         vuint16_t  KEY_SLOT_USED_FOR_STARTUP:1;   /* pKeySlotUsedForStartup */
         vuint16_t  KEY_SLOT_USED_FOR_SYNC:1;   /* pKeySlotUsedForSync */
         vuint16_t  OFFSET_CORRECTION_START:14;   /* gOffsetCorrectionStart */
      } B;
   } FR_PCR11_16B_tag;

   typedef union {   /* Protocol Configuration Register 12 */
      vuint16_t R;
      struct {
         vuint16_t  ALLOW_PASSIVE_TO_ACTIVE:5;   /* pAllowPassiveToActive */
         vuint16_t  KEY_SLOT_HEADER_CRC:11;   /* header CRC for key slot */
      } B;
   } FR_PCR12_16B_tag;

   typedef union {   /* Protocol Configuration Register 13 */
      vuint16_t R;
      struct {
         vuint16_t  FIRST_MINISLOT_ACTION_POINT_OFFSET:6;   /* max(gdActionPointOffset,gdMinislotActionPointOffset) - 1 */
         vuint16_t  STATIC_SLOT_AFTER_ACTION_POINT:10;   /* gdStaticSlot - gdActionPointOffset - 1 */
      } B;
   } FR_PCR13_16B_tag;

   typedef union {   /* Protocol Configuration Register 14 */
      vuint16_t R;
      struct {
         vuint16_t  RATE_CORRECTION_OUT:11;   /* pRateCorrectionOut */
         vuint16_t  LISTEN_TIMEOUT_20_16:5;   /* pdListenTimeout - 1 */
      } B;
   } FR_PCR14_16B_tag;

   typedef union {   /* Protocol Configuration Register 15 */
      vuint16_t R;
      struct {
         vuint16_t  LISTEN_TIMEOUT_15_0:16;   /* pdListenTimeout - 1 */
      } B;
   } FR_PCR15_16B_tag;

   typedef union {   /* Protocol Configuration Register 16 */
      vuint16_t R;
      struct {
         vuint16_t  MACRO_INITIAL_OFFSET_B:7;   /* pMacroInitialOffset[B] */
         vuint16_t  NOISE_LISTEN_TIMEOUT_24_16:9;   /* (gListenNoise * pdListenTimeout) - 1 */
      } B;
   } FR_PCR16_16B_tag;

   typedef union {   /* Protocol Configuration Register 17 */
      vuint16_t R;
      struct {
         vuint16_t  NOISE_LISTEN_TIMEOUT_15_0:16;   /* (gListenNoise * pdListenTimeout) - 1 */
      } B;
   } FR_PCR17_16B_tag;

   typedef union {   /* Protocol Configuration Register 18 */
      vuint16_t R;
      struct {
         vuint16_t  WAKEUP_PATTERN:6;   /* pWakeupPattern */
         vuint16_t  KEY_SLOT_ID:10;    /* pKeySlotId */
      } B;
   } FR_PCR18_16B_tag;

   typedef union {   /* Protocol Configuration Register 19 */
      vuint16_t R;
      struct {
         vuint16_t  DECODING_CORRECTION_A:9;   /* pDecodingCorrection + pDelayCompensation[A] + 2 */
         vuint16_t  PAYLOAD_LENGTH_STATIC:7;   /* gPayloadLengthStatic */
      } B;
   } FR_PCR19_16B_tag;

   typedef union {   /* Protocol Configuration Register 20 */
      vuint16_t R;
      struct {
         vuint16_t  MICRO_INITIAL_OFFSET_B:8;   /* pMicroInitialOffset[B] */
         vuint16_t  MICRO_INITIAL_OFFSET_A:8;   /* pMicroInitialOffset[A] */
      } B;
   } FR_PCR20_16B_tag;

   typedef union {   /* Protocol Configuration Register 21 */
      vuint16_t R;
      struct {
         vuint16_t  EXTERN_RATE_CORRECTION:3;   /* pExternRateCorrection */
         vuint16_t  LATEST_TX:13;      /* gNumberOfMinislots - pLatestTx */
      } B;
   } FR_PCR21_16B_tag;

   typedef union {   /* Protocol Configuration Register 22 */
      vuint16_t R;
      struct {
         vuint16_t:1;
         vuint16_t  COMP_ACCEPTED_STARRUP_RANGE_A:11;   /* pdAcceptedStartupRange - pDelayCompensationChA */
         vuint16_t  MICRO_PER_CYCLE_19_16:4;   /* gMicroPerCycle */
      } B;
   } FR_PCR22_16B_tag;

   typedef union {   /* Protocol Configuration Register 23 */
      vuint16_t R;
      struct {
         vuint16_t  MICRO_PER_CYCLE_15_0:16;   /* pMicroPerCycle */
      } B;
   } FR_PCR23_16B_tag;

   typedef union {   /* Protocol Configuration Register 24 */
      vuint16_t R;
      struct {
         vuint16_t  CLUSTER_DRIFT_DAMPING:5;   /* pClusterDriftDamping */
         vuint16_t  MAX_PAYLOAD_LENGTH_DYNAMIC:7;   /* pPayloadLengthDynMax */
         vuint16_t  MICRO_PER_CYCLE_MIN_19_16:4;   /* pMicroPerCycle - pdMaxDrift */
      } B;
   } FR_PCR24_16B_tag;

   typedef union {   /* Protocol Configuration Register 25 */
      vuint16_t R;
      struct {
         vuint16_t  MICRO_PER_CYCLE_MIN_15_0:16;   /* pMicroPerCycle - pdMaxDrift */
      } B;
   } FR_PCR25_16B_tag;

   typedef union {   /* Protocol Configuration Register 26 */
      vuint16_t R;
      struct {
         vuint16_t  ALLOW_HALT_DUE_TO_CLOCK:1;   /* pAllowHaltDueToClock */
         vuint16_t  COMP_ACCEPTED_STARTUP_RANGE_B:11;   /* pdAcceptedStartupRange - pDelayCompensationChB */
         vuint16_t  MICRO_PER_CYCLE_MAX_19_16:4;   /* pMicroPerCycle + pdMaxDrift */
      } B;
   } FR_PCR26_16B_tag;

   typedef union {   /* Protocol Configuration Register 27 */
      vuint16_t R;
      struct {
         vuint16_t  MICRO_PER_CYCLE_MAX_15_0:16;   /* pMicroPerCycle + pdMaxDrift */
      } B;
   } FR_PCR27_16B_tag;

   typedef union {   /* Protocol Configuration Register 28 */
      vuint16_t R;
      struct {
         vuint16_t  DYNAMIC_SLOT_IDLE_PHASE:2;   /* gdDynamicSlotIdlePhase */
         vuint16_t  MACRO_AFTER_OFFSET_CORRECTION:14;   /* gMacroPerCycle - gOffsetCorrectionStart */
      } B;
   } FR_PCR28_16B_tag;

   typedef union {   /* Protocol Configuration Register 29 */
      vuint16_t R;
      struct {
         vuint16_t  EXTERN_OFFSET_CORRECTION:3;   /* pExternOffsetCorrection */
         vuint16_t  MINISLOTS_MAX:13;   /* gNumberOfMinislots - 1 */
      } B;
   } FR_PCR29_16B_tag;

   typedef union {   /* Protocol Configuration Register 30 */
      vuint16_t R;
      struct {
         vuint16_t:12;
         vuint16_t  SYNC_NODE_MAX:4;   /* gSyncNodeMax */
      } B;
   } FR_PCR30_16B_tag;

   typedef union {   /* Receive FIFO System Memory Base Address High Register */
      vuint16_t R;
      struct {
         vuint16_t  SMBA_31_16:16;     /* System Memory Base Address */
      } B;
   } FR_RFSYMBHADR_16B_tag;

   typedef union {   /* Receive FIFO System Memory Base Address Low Register */
      vuint16_t R;
      struct {
         vuint16_t  SMBA_15_4:12;      /* System Memory Base Address */
         vuint16_t:4;
      } B;
   } FR_RFSYMBLADR_16B_tag;

   typedef union {   /* Receive FIFO Periodic Timer Register */
      vuint16_t R;
      struct {
         vuint16_t:2;
         vuint16_t  PTD:14;            /* Periodic Timer Duration */
      } B;
   } FR_RFPTR_16B_tag;

   typedef union {   /* Receive FIFO Fill Level and Pop Count Register */
      vuint16_t R;
      struct {
         vuint16_t  FLPCB:8;           /* Fill Level and Pop Count Channel B */
         vuint16_t  FLPCA:8;           /* Fill Level and Pop Count Channel A */
      } B;
   } FR_RFFLPCR_16B_tag;

   typedef union {   /* ECC Error Interrupt Flag and Enable Register */
      vuint16_t R;
      struct {
         vuint16_t  LRNE_OF:1;         /* LRAM Non-Corrected Error Overflow Flag */
         vuint16_t  LRCE_OF:1;         /* LRAM Corrected Error Overflow Flag */
         vuint16_t  DRNE_OF:1;         /* DRAM Non-Corrected Error Overflow Flag */
         vuint16_t  DRCE_OF:1;         /* DRAM Corrected Error Overflow Flag */
         vuint16_t  LRNE_IF:1;         /* LRAM Non-Corrected Error Interrupt Flag */
         vuint16_t  LRCE_IF:1;         /* LRAM Corrected Error Interrupt Flag */
         vuint16_t  DRNE_IF:1;         /* DRAM Non-Corrected Error Interrupt Flag */
         vuint16_t  DRCE_IF:1;         /* DRAM Corrected Error Interrupt Flag */
         vuint16_t:4;
         vuint16_t  LRNE_IE:1;         /* LRAM Non-Corrected Error Interrupt Enable */
         vuint16_t  LRCE_IE:1;         /* LRAM Corrected Error Interrupt Enable */
         vuint16_t  DRNE_IE:1;         /* DRAM Non-Corrected Error Interrupt Enable */
         vuint16_t  DRCE_IE:1;         /* DRAM Corrected Error Interrupt Enable */
      } B;
   } FR_EEIFER_16B_tag;

   typedef union {   /* ECC Error Report and Injection Control Register */
      vuint16_t R;
      struct {
         vuint16_t  BSY:1;             /* Register Update Busy */
         vuint16_t:5;
         vuint16_t  ERS:2;             /* Error Report Select */
         vuint16_t:3;
         vuint16_t  ERM:1;             /* Error Report Mode */
         vuint16_t:2;
         vuint16_t  EIM:1;             /* Error Injection Mode */
         vuint16_t  EIE:1;             /* Error Injection Enable */
      } B;
   } FR_EERICR_16B_tag;

   typedef union {   /* ECC Error Report Adress Register */
      vuint16_t R;
      struct {
         vuint16_t  MID:1;             /* Memory Identifier */
         vuint16_t  BANK:3;            /* Memory Bank */
         vuint16_t  ADDR:12;           /* Memory Address */
      } B;
   } FR_EERAR_16B_tag;

   typedef union {   /* ECC Error Report Data Register */
      vuint16_t R;
      struct {
         vuint16_t  DATA:16;           /* Data */
      } B;
   } FR_EERDR_16B_tag;

   typedef union {   /* ECC Error Report Code Register */
      vuint16_t R;
      struct {
         vuint16_t:11;
         vuint16_t  CODE:5;            /* Code */
      } B;
   } FR_EERCR_16B_tag;

   typedef union {   /* ECC Error Injection Address Register */
      vuint16_t R;
      struct {
         vuint16_t  MID:1;             /* Memory Identifier */
         vuint16_t  BANK:3;            /* Memory Bank */
         vuint16_t  ADDR:12;           /* Memory Address */
      } B;
   } FR_EEIAR_16B_tag;

   typedef union {   /* ECC Error Injection Data Register */
      vuint16_t R;
      struct {
         vuint16_t  DATA:16;           /* Data */
      } B;
   } FR_EEIDR_16B_tag;

   typedef union {   /* ECC Error Injection Code Register */
      vuint16_t R;
      struct {
         vuint16_t:11;
         vuint16_t  CODE:5;            /* Code */
      } B;
   } FR_EEICR_16B_tag;


   /* Register layout for all registers MBCCSR ... */

   typedef union {   /* Message Buffer Configuration Control Status Register */
      vuint16_t R;
      struct {
         vuint16_t:1;
         vuint16_t  MCM:1;             /* Message Buffer Commit Mode */
         vuint16_t  MBT:1;             /* Message Buffer Type */
         vuint16_t  MTD:1;             /* Message Buffer Transfer Direction */
         vuint16_t  CMT:1;             /* Commit for Transmission */
         vuint16_t  EDT:1;             /* Enable/Disable Trigger */
         vuint16_t  LCKT:1;            /* Lock/Unlock Trigger */
         vuint16_t  MBIE:1;            /* Message Buffer Interrupt Enable */
         vuint16_t:3;
         vuint16_t  DUP:1;             /* Data Updated */
         vuint16_t  DVAL:1;            /* DataValid */
         vuint16_t  EDS:1;             /* Enable/Disable Status */
         vuint16_t  LCKS:1;            /* LockStatus */
         vuint16_t  MBIF:1;            /* Message Buffer Interrupt Flag */
      } B;
   } FR_MBCCSR_16B_tag;


   /* Register layout for all registers MBCCFR ... */

   typedef union {   /* Message Buffer Cycle Counter Filter Register */
      vuint16_t R;
      struct {
         vuint16_t  MTM:1;             /* Message Buffer Transmission Mode */
         vuint16_t  CHA:1;             /* Channel Assignment */
         vuint16_t  CHB:1;             /* Channel Assignment */
         vuint16_t  CCFE:1;            /* Cycle Counter Filtering Enable */
         vuint16_t  CCFMSK:6;          /* Cycle Counter Filtering Mask */
         vuint16_t  CCFVAL:6;          /* Cycle Counter Filtering Value */
      } B;
   } FR_MBCCFR_16B_tag;


   /* Register layout for all registers MBFIDR ... */

   typedef union {   /* Message Buffer Frame ID Register */
      vuint16_t R;
      struct {
         vuint16_t:5;
         vuint16_t  FID:11;            /* Frame ID */
      } B;
   } FR_MBFIDR_16B_tag;


   /* Register layout for all registers MBIDXR ... */

   typedef union {   /* Message Buffer Index Register */
      vuint16_t R;
      struct {
         vuint16_t:9;
         vuint16_t  MBIDX:7;           /* Message Buffer Index */
      } B;
   } FR_MBIDXR_16B_tag;


   typedef struct FR_MB_struct_tag {

                 /* Message Buffer Configuration Control Status Register */
      FR_MBCCSR_16B_tag MBCCSR;            /* relative offset: 0x0000 */
                         /* Message Buffer Cycle Counter Filter Register */
      FR_MBCCFR_16B_tag MBCCFR;            /* relative offset: 0x0002 */
                                     /* Message Buffer Frame ID Register */
      FR_MBFIDR_16B_tag MBFIDR;            /* relative offset: 0x0004 */
                                        /* Message Buffer Index Register */
      FR_MBIDXR_16B_tag MBIDXR;            /* relative offset: 0x0006 */

   } FR_MB_tag;



   typedef struct FR_struct_tag {

                                                /* Module Version Number */
      FR_MVR_16B_tag MVR;                  /* offset: 0x0000 size: 16 bit */
                                        /* Module Configuration Register */
      FR_MCR_16B_tag MCR;                  /* offset: 0x0002 size: 16 bit */
                                      /* SYSTEM MEMORY BASE ADD HIGH REG */
      FR_SYMBADHR_16B_tag SYMBADHR;        /* offset: 0x0004 size: 16 bit */
                                      /* SYSTEM MEMORY BASE ADD LOW  REG */
      FR_SYMBADLR_16B_tag SYMBADLR;        /* offset: 0x0006 size: 16 bit */
                                       /* STROBE SIGNAL CONTROL REGISTER */
      FR_STBSCR_16B_tag STBSCR;            /* offset: 0x0008 size: 16 bit */
      int8_t FR_reserved_000A[2];
                                    /* MESSAGE BUFFER DATA SIZE REGISTER */
      FR_MBDSR_16B_tag MBDSR;              /* offset: 0x000C size: 16 bit */
                             /* MESS. BUFFER SEG. SIZE & UTILISATION REG */
      FR_MBSSUTR_16B_tag MBSSUTR;          /* offset: 0x000E size: 16 bit */
                                              /* PE DRAM ACCESS REGISTER */
      FR_PEDRAR_16B_tag PEDRAR;            /* offset: 0x0010 size: 16 bit */
                                                /* PE DRAM DATA REGISTER */
      FR_PEDRDR_16B_tag PEDRDR;            /* offset: 0x0012 size: 16 bit */
                                       /* PROTOCOL OPERATION CONTROL REG */
      FR_POCR_16B_tag POCR;                /* offset: 0x0014 size: 16 bit */
                                   /* GLOBAL INTERRUPT FLAG & ENABLE REG */
      FR_GIFER_16B_tag GIFER;              /* offset: 0x0016 size: 16 bit */
                                   /* PROTOCOL INTERRUPT FLAG REGISTER 0 */
      FR_PIFR0_16B_tag PIFR0;              /* offset: 0x0018 size: 16 bit */
                                   /* PROTOCOL INTERRUPT FLAG REGISTER 1 */
      FR_PIFR1_16B_tag PIFR1;              /* offset: 0x001A size: 16 bit */
                                 /* PROTOCOL INTERRUPT ENABLE REGISTER 0 */
      FR_PIER0_16B_tag PIER0;              /* offset: 0x001C size: 16 bit */
                                 /* PROTOCOL INTERRUPT ENABLE REGISTER 1 */
      FR_PIER1_16B_tag PIER1;              /* offset: 0x001E size: 16 bit */
                                              /* CHI ERROR FLAG REGISTER */
      FR_CHIERFR_16B_tag CHIERFR;          /* offset: 0x0020 size: 16 bit */
                             /* Message Buffer Interrupt Vector Register */
      FR_MBIVEC_16B_tag MBIVEC;            /* offset: 0x0022 size: 16 bit */
                              /* Channel A Status Error Counter Register */
      FR_CASERCR_16B_tag CASERCR;          /* offset: 0x0024 size: 16 bit */
                              /* Channel B Status Error Counter Register */
      FR_CBSERCR_16B_tag CBSERCR;          /* offset: 0x0026 size: 16 bit */
                                           /* Protocol Status Register 0 */
      FR_PSR0_16B_tag PSR0;                /* offset: 0x0028 size: 16 bit */
                                           /* Protocol Status Register 1 */
      FR_PSR1_16B_tag PSR1;                /* offset: 0x002A size: 16 bit */
                                           /* Protocol Status Register 2 */
      FR_PSR2_16B_tag PSR2;                /* offset: 0x002C size: 16 bit */
                                           /* Protocol Status Register 3 */
      FR_PSR3_16B_tag PSR3;                /* offset: 0x002E size: 16 bit */
                                           /* Macrotick Counter Register */
      FR_MTCTR_16B_tag MTCTR;              /* offset: 0x0030 size: 16 bit */
                                               /* Cycle Counter Register */
      FR_CYCTR_16B_tag CYCTR;              /* offset: 0x0032 size: 16 bit */
                                      /* Slot Counter Channel A Register */
      FR_SLTCTAR_16B_tag SLTCTAR;          /* offset: 0x0034 size: 16 bit */
                                      /* Slot Counter Channel B Register */
      FR_SLTCTBR_16B_tag SLTCTBR;          /* offset: 0x0036 size: 16 bit */
                                       /* Rate Correction Value Register */
      FR_RTCORVR_16B_tag RTCORVR;          /* offset: 0x0038 size: 16 bit */
                                     /* Offset Correction Value Register */
      FR_OFCORVR_16B_tag OFCORVR;          /* offset: 0x003A size: 16 bit */
                                     /* Combined Interrupt Flag Register */
      FR_CIFR_16B_tag CIFR;                /* offset: 0x003C size: 16 bit */
                               /* System Memory Access Time-Out Register */
      FR_SYMATOR_16B_tag SYMATOR;          /* offset: 0x003E size: 16 bit */
                                          /* Sync Frame Counter Register */
      FR_SFCNTR_16B_tag SFCNTR;            /* offset: 0x0040 size: 16 bit */
                                     /* Sync Frame Table Offset Register */
      FR_SFTOR_16B_tag SFTOR;              /* offset: 0x0042 size: 16 bit */
             /* Sync Frame Table Configuration, Control, Status Register */
      FR_SFTCCSR_16B_tag SFTCCSR;          /* offset: 0x0044 size: 16 bit */
                                       /* Sync Frame ID Rejection Filter */
      FR_SFIDRFR_16B_tag SFIDRFR;          /* offset: 0x0046 size: 16 bit */
                       /* Sync Frame ID Acceptance Filter Value Register */
      FR_SFIDAFVR_16B_tag SFIDAFVR;        /* offset: 0x0048 size: 16 bit */
                        /* Sync Frame ID Acceptance Filter Mask Register */
      FR_SFIDAFMR_16B_tag SFIDAFMR;        /* offset: 0x004A size: 16 bit */
      union {
                                   /* Network Management Vector Register */
         FR_NMVR_16B_tag NMVR[6];          /* offset: 0x004C  (0x0002 x 6) */

                              /* Network Management Vector Byte Register */
         FR_NMV_8B_tag NMV[12];            /* offset: 0x004C  (0x0001 x 12) */

         struct {
                                   /* Network Management Vector Register */
            FR_NMVR_16B_tag NMVR0;         /* offset: 0x004C size: 16 bit */
            FR_NMVR_16B_tag NMVR1;         /* offset: 0x004E size: 16 bit */
            FR_NMVR_16B_tag NMVR2;         /* offset: 0x0050 size: 16 bit */
            FR_NMVR_16B_tag NMVR3;         /* offset: 0x0052 size: 16 bit */
            FR_NMVR_16B_tag NMVR4;         /* offset: 0x0054 size: 16 bit */
            FR_NMVR_16B_tag NMVR5;         /* offset: 0x0056 size: 16 bit */
         };

         struct {
                              /* Network Management Vector Byte Register */
            FR_NMV_8B_tag NMV0;            /* offset: 0x004C size: 8 bit */
            FR_NMV_8B_tag NMV1;            /* offset: 0x004D size: 8 bit */
            FR_NMV_8B_tag NMV2;            /* offset: 0x004E size: 8 bit */
            FR_NMV_8B_tag NMV3;            /* offset: 0x004F size: 8 bit */
            FR_NMV_8B_tag NMV4;            /* offset: 0x0050 size: 8 bit */
            FR_NMV_8B_tag NMV5;            /* offset: 0x0051 size: 8 bit */
            FR_NMV_8B_tag NMV6;            /* offset: 0x0052 size: 8 bit */
            FR_NMV_8B_tag NMV7;            /* offset: 0x0053 size: 8 bit */
            FR_NMV_8B_tag NMV8;            /* offset: 0x0054 size: 8 bit */
            FR_NMV_8B_tag NMV9;            /* offset: 0x0055 size: 8 bit */
            FR_NMV_8B_tag NMV10;           /* offset: 0x0056 size: 8 bit */
            FR_NMV_8B_tag NMV11;           /* offset: 0x0057 size: 8 bit */
         };

      };
                            /* Network Management Vector Length Register */
      FR_NMVLR_16B_tag NMVLR;              /* offset: 0x0058 size: 16 bit */
                             /* Timer Configuration and Control Register */
      FR_TICCR_16B_tag TICCR;              /* offset: 0x005A size: 16 bit */
                                           /* Timer 1 Cycle Set Register */
      FR_TI1CYSR_16B_tag TI1CYSR;          /* offset: 0x005C size: 16 bit */
                                    /* Timer 1 Macrotick Offset Register */
      FR_TI1MTOR_16B_tag TI1MTOR;          /* offset: 0x005E size: 16 bit */
                                     /* Timer 2 Configuration Register 0 */
      FR_TI2CR0_16B_tag TI2CR0;            /* offset: 0x0060 size: 16 bit */
                                     /* Timer 2 Configuration Register 1 */
      FR_TI2CR1_16B_tag TI2CR1;            /* offset: 0x0062 size: 16 bit */
                                       /* Slot Status Selection Register */
      FR_SSSR_16B_tag SSSR;                /* offset: 0x0064 size: 16 bit */
                               /* Slot Status Counter Condition Register */
      FR_SSCCR_16B_tag SSCCR;              /* offset: 0x0066 size: 16 bit */
      union {
                                                 /* Slot Status Register */
         FR_SSR_16B_tag SSR[8];            /* offset: 0x0068  (0x0002 x 8) */

         struct {
                                                 /* Slot Status Register */
            FR_SSR_16B_tag SSR0;           /* offset: 0x0068 size: 16 bit */
            FR_SSR_16B_tag SSR1;           /* offset: 0x006A size: 16 bit */
            FR_SSR_16B_tag SSR2;           /* offset: 0x006C size: 16 bit */
            FR_SSR_16B_tag SSR3;           /* offset: 0x006E size: 16 bit */
            FR_SSR_16B_tag SSR4;           /* offset: 0x0070 size: 16 bit */
            FR_SSR_16B_tag SSR5;           /* offset: 0x0072 size: 16 bit */
            FR_SSR_16B_tag SSR6;           /* offset: 0x0074 size: 16 bit */
            FR_SSR_16B_tag SSR7;           /* offset: 0x0076 size: 16 bit */
         };

      };
      union {
                                         /* Slot Status Counter Register */
         FR_SSCR_16B_tag SSCR[4];          /* offset: 0x0078  (0x0002 x 4) */

         struct {
                                         /* Slot Status Counter Register */
            FR_SSCR_16B_tag SSCR0;         /* offset: 0x0078 size: 16 bit */
            FR_SSCR_16B_tag SSCR1;         /* offset: 0x007A size: 16 bit */
            FR_SSCR_16B_tag SSCR2;         /* offset: 0x007C size: 16 bit */
            FR_SSCR_16B_tag SSCR3;         /* offset: 0x007E size: 16 bit */
         };

      };
                                         /* MTS A Configuration Register */
      FR_MTSACFR_16B_tag MTSACFR;          /* offset: 0x0080 size: 16 bit */
                                         /* MTS B Configuration Register */
      FR_MTSBCFR_16B_tag MTSBCFR;          /* offset: 0x0082 size: 16 bit */
                                 /* Receive Shadow Buffer Index Register */
      FR_RSBIR_16B_tag RSBIR;              /* offset: 0x0084 size: 16 bit */
                        /* Receive FIFO Watermark and Selection Register */
      FR_RFWMSR_16B_tag RFWMSR;            /* offset: 0x0086 size: 16 bit */
                                    /* Receive FIFO Start Index Register */
      FR_RF_RFSIR_16B_tag RF_RFSIR;        /* offset: 0x0088 size: 16 bit */
                                 /* Receive FIFO Depth and Size Register */
      FR_RFDSR_16B_tag RFDSR;              /* offset: 0x008A size: 16 bit */
                                   /* Receive FIFO A Read Index Register */
      FR_RFARIR_16B_tag RFARIR;            /* offset: 0x008C size: 16 bit */
                                   /* Receive FIFO B Read Index Register */
      FR_RFBRIR_16B_tag RFBRIR;            /* offset: 0x008E size: 16 bit */
             /* Receive FIFO Message ID Acceptance Filter Value Register */
      FR_RFMIDAFVR_16B_tag RFMIDAFVR;      /* offset: 0x0090 size: 16 bit */
              /* Receive FIFO Message ID Acceptance Filter Mask Register */
      FR_RFMIDAFMR_16B_tag RFMIDAFMR;      /* offset: 0x0092 size: 16 bit */
                /* Receive FIFO Frame ID Rejection Filter Value Register */
      FR_RFFIDRFVR_16B_tag RFFIDRFVR;      /* offset: 0x0094 size: 16 bit */
                 /* Receive FIFO Frame ID Rejection Filter Mask Register */
      FR_RFFIDRFMR_16B_tag RFFIDRFMR;      /* offset: 0x0096 size: 16 bit */
                     /* Receive FIFO Range Filter Configuration Register */
      FR_RFRFCFR_16B_tag RFRFCFR;          /* offset: 0x0098 size: 16 bit */
                           /* Receive FIFO Range Filter Control Register */
      FR_RFRFCTR_16B_tag RFRFCTR;          /* offset: 0x009A size: 16 bit */
                        /* Last Dynamic Transmit Slot Channel A Register */
      FR_LDTXSLAR_16B_tag LDTXSLAR;        /* offset: 0x009C size: 16 bit */
                        /* Last Dynamic Transmit Slot Channel B Register */
      FR_LDTXSLBR_16B_tag LDTXSLBR;        /* offset: 0x009E size: 16 bit */
                                    /* Protocol Configuration Register 0 */
      FR_PCR0_16B_tag PCR0;                /* offset: 0x00A0 size: 16 bit */
                                    /* Protocol Configuration Register 1 */
      FR_PCR1_16B_tag PCR1;                /* offset: 0x00A2 size: 16 bit */
                                    /* Protocol Configuration Register 2 */
      FR_PCR2_16B_tag PCR2;                /* offset: 0x00A4 size: 16 bit */
                                    /* Protocol Configuration Register 3 */
      FR_PCR3_16B_tag PCR3;                /* offset: 0x00A6 size: 16 bit */
                                    /* Protocol Configuration Register 4 */
      FR_PCR4_16B_tag PCR4;                /* offset: 0x00A8 size: 16 bit */
                                    /* Protocol Configuration Register 5 */
      FR_PCR5_16B_tag PCR5;                /* offset: 0x00AA size: 16 bit */
                                    /* Protocol Configuration Register 6 */
      FR_PCR6_16B_tag PCR6;                /* offset: 0x00AC size: 16 bit */
                                    /* Protocol Configuration Register 7 */
      FR_PCR7_16B_tag PCR7;                /* offset: 0x00AE size: 16 bit */
                                    /* Protocol Configuration Register 8 */
      FR_PCR8_16B_tag PCR8;                /* offset: 0x00B0 size: 16 bit */
                                    /* Protocol Configuration Register 9 */
      FR_PCR9_16B_tag PCR9;                /* offset: 0x00B2 size: 16 bit */
                                   /* Protocol Configuration Register 10 */
      FR_PCR10_16B_tag PCR10;              /* offset: 0x00B4 size: 16 bit */
                                   /* Protocol Configuration Register 11 */
      FR_PCR11_16B_tag PCR11;              /* offset: 0x00B6 size: 16 bit */
                                   /* Protocol Configuration Register 12 */
      FR_PCR12_16B_tag PCR12;              /* offset: 0x00B8 size: 16 bit */
                                   /* Protocol Configuration Register 13 */
      FR_PCR13_16B_tag PCR13;              /* offset: 0x00BA size: 16 bit */
                                   /* Protocol Configuration Register 14 */
      FR_PCR14_16B_tag PCR14;              /* offset: 0x00BC size: 16 bit */
                                   /* Protocol Configuration Register 15 */
      FR_PCR15_16B_tag PCR15;              /* offset: 0x00BE size: 16 bit */
                                   /* Protocol Configuration Register 16 */
      FR_PCR16_16B_tag PCR16;              /* offset: 0x00C0 size: 16 bit */
                                   /* Protocol Configuration Register 17 */
      FR_PCR17_16B_tag PCR17;              /* offset: 0x00C2 size: 16 bit */
                                   /* Protocol Configuration Register 18 */
      FR_PCR18_16B_tag PCR18;              /* offset: 0x00C4 size: 16 bit */
                                   /* Protocol Configuration Register 19 */
      FR_PCR19_16B_tag PCR19;              /* offset: 0x00C6 size: 16 bit */
                                   /* Protocol Configuration Register 20 */
      FR_PCR20_16B_tag PCR20;              /* offset: 0x00C8 size: 16 bit */
                                   /* Protocol Configuration Register 21 */
      FR_PCR21_16B_tag PCR21;              /* offset: 0x00CA size: 16 bit */
                                   /* Protocol Configuration Register 22 */
      FR_PCR22_16B_tag PCR22;              /* offset: 0x00CC size: 16 bit */
                                   /* Protocol Configuration Register 23 */
      FR_PCR23_16B_tag PCR23;              /* offset: 0x00CE size: 16 bit */
                                   /* Protocol Configuration Register 24 */
      FR_PCR24_16B_tag PCR24;              /* offset: 0x00D0 size: 16 bit */
                                   /* Protocol Configuration Register 25 */
      FR_PCR25_16B_tag PCR25;              /* offset: 0x00D2 size: 16 bit */
                                   /* Protocol Configuration Register 26 */
      FR_PCR26_16B_tag PCR26;              /* offset: 0x00D4 size: 16 bit */
                                   /* Protocol Configuration Register 27 */
      FR_PCR27_16B_tag PCR27;              /* offset: 0x00D6 size: 16 bit */
                                   /* Protocol Configuration Register 28 */
      FR_PCR28_16B_tag PCR28;              /* offset: 0x00D8 size: 16 bit */
                                   /* Protocol Configuration Register 29 */
      FR_PCR29_16B_tag PCR29;              /* offset: 0x00DA size: 16 bit */
                                   /* Protocol Configuration Register 30 */
      FR_PCR30_16B_tag PCR30;              /* offset: 0x00DC size: 16 bit */
      int8_t FR_reserved_00DE[10];
                /* Receive FIFO System Memory Base Address High Register */
      FR_RFSYMBHADR_16B_tag RFSYMBHADR;    /* offset: 0x00E8 size: 16 bit */
                 /* Receive FIFO System Memory Base Address Low Register */
      FR_RFSYMBLADR_16B_tag RFSYMBLADR;    /* offset: 0x00EA size: 16 bit */
                                 /* Receive FIFO Periodic Timer Register */
      FR_RFPTR_16B_tag RFPTR;              /* offset: 0x00EC size: 16 bit */
                       /* Receive FIFO Fill Level and Pop Count Register */
      FR_RFFLPCR_16B_tag RFFLPCR;          /* offset: 0x00EE size: 16 bit */
                         /* ECC Error Interrupt Flag and Enable Register */
      FR_EEIFER_16B_tag EEIFER;            /* offset: 0x00F0 size: 16 bit */
                      /* ECC Error Report and Injection Control Register */
      FR_EERICR_16B_tag EERICR;            /* offset: 0x00F2 size: 16 bit */
                                     /* ECC Error Report Adress Register */
      FR_EERAR_16B_tag EERAR;              /* offset: 0x00F4 size: 16 bit */
                                       /* ECC Error Report Data Register */
      FR_EERDR_16B_tag EERDR;              /* offset: 0x00F6 size: 16 bit */
                                       /* ECC Error Report Code Register */
      FR_EERCR_16B_tag EERCR;              /* offset: 0x00F8 size: 16 bit */
                                 /* ECC Error Injection Address Register */
      FR_EEIAR_16B_tag EEIAR;              /* offset: 0x00FA size: 16 bit */
                                    /* ECC Error Injection Data Register */
      FR_EEIDR_16B_tag EEIDR;              /* offset: 0x00FC size: 16 bit */
                                    /* ECC Error Injection Code Register */
      FR_EEICR_16B_tag EEICR;              /* offset: 0x00FE size: 16 bit */
      union {
                                                     /*  Register set MB */
         FR_MB_tag MB[64];                 /* offset: 0x0100  (0x0008 x 64) */

                                                   /*  Alias name for MB */
         FR_MB_tag MBCCS[64];              /* deprecated - please avoid */

         struct {
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR0;     /* offset: 0x0100 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR0;     /* offset: 0x0102 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR0;     /* offset: 0x0104 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR0;     /* offset: 0x0106 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR1;     /* offset: 0x0108 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR1;     /* offset: 0x010A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR1;     /* offset: 0x010C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR1;     /* offset: 0x010E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR2;     /* offset: 0x0110 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR2;     /* offset: 0x0112 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR2;     /* offset: 0x0114 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR2;     /* offset: 0x0116 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR3;     /* offset: 0x0118 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR3;     /* offset: 0x011A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR3;     /* offset: 0x011C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR3;     /* offset: 0x011E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR4;     /* offset: 0x0120 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR4;     /* offset: 0x0122 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR4;     /* offset: 0x0124 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR4;     /* offset: 0x0126 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR5;     /* offset: 0x0128 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR5;     /* offset: 0x012A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR5;     /* offset: 0x012C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR5;     /* offset: 0x012E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR6;     /* offset: 0x0130 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR6;     /* offset: 0x0132 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR6;     /* offset: 0x0134 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR6;     /* offset: 0x0136 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR7;     /* offset: 0x0138 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR7;     /* offset: 0x013A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR7;     /* offset: 0x013C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR7;     /* offset: 0x013E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR8;     /* offset: 0x0140 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR8;     /* offset: 0x0142 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR8;     /* offset: 0x0144 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR8;     /* offset: 0x0146 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR9;     /* offset: 0x0148 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR9;     /* offset: 0x014A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR9;     /* offset: 0x014C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR9;     /* offset: 0x014E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR10;    /* offset: 0x0150 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR10;    /* offset: 0x0152 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR10;    /* offset: 0x0154 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR10;    /* offset: 0x0156 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR11;    /* offset: 0x0158 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR11;    /* offset: 0x015A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR11;    /* offset: 0x015C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR11;    /* offset: 0x015E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR12;    /* offset: 0x0160 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR12;    /* offset: 0x0162 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR12;    /* offset: 0x0164 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR12;    /* offset: 0x0166 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR13;    /* offset: 0x0168 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR13;    /* offset: 0x016A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR13;    /* offset: 0x016C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR13;    /* offset: 0x016E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR14;    /* offset: 0x0170 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR14;    /* offset: 0x0172 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR14;    /* offset: 0x0174 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR14;    /* offset: 0x0176 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR15;    /* offset: 0x0178 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR15;    /* offset: 0x017A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR15;    /* offset: 0x017C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR15;    /* offset: 0x017E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR16;    /* offset: 0x0180 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR16;    /* offset: 0x0182 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR16;    /* offset: 0x0184 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR16;    /* offset: 0x0186 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR17;    /* offset: 0x0188 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR17;    /* offset: 0x018A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR17;    /* offset: 0x018C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR17;    /* offset: 0x018E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR18;    /* offset: 0x0190 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR18;    /* offset: 0x0192 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR18;    /* offset: 0x0194 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR18;    /* offset: 0x0196 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR19;    /* offset: 0x0198 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR19;    /* offset: 0x019A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR19;    /* offset: 0x019C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR19;    /* offset: 0x019E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR20;    /* offset: 0x01A0 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR20;    /* offset: 0x01A2 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR20;    /* offset: 0x01A4 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR20;    /* offset: 0x01A6 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR21;    /* offset: 0x01A8 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR21;    /* offset: 0x01AA size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR21;    /* offset: 0x01AC size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR21;    /* offset: 0x01AE size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR22;    /* offset: 0x01B0 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR22;    /* offset: 0x01B2 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR22;    /* offset: 0x01B4 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR22;    /* offset: 0x01B6 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR23;    /* offset: 0x01B8 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR23;    /* offset: 0x01BA size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR23;    /* offset: 0x01BC size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR23;    /* offset: 0x01BE size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR24;    /* offset: 0x01C0 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR24;    /* offset: 0x01C2 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR24;    /* offset: 0x01C4 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR24;    /* offset: 0x01C6 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR25;    /* offset: 0x01C8 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR25;    /* offset: 0x01CA size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR25;    /* offset: 0x01CC size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR25;    /* offset: 0x01CE size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR26;    /* offset: 0x01D0 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR26;    /* offset: 0x01D2 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR26;    /* offset: 0x01D4 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR26;    /* offset: 0x01D6 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR27;    /* offset: 0x01D8 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR27;    /* offset: 0x01DA size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR27;    /* offset: 0x01DC size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR27;    /* offset: 0x01DE size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR28;    /* offset: 0x01E0 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR28;    /* offset: 0x01E2 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR28;    /* offset: 0x01E4 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR28;    /* offset: 0x01E6 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR29;    /* offset: 0x01E8 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR29;    /* offset: 0x01EA size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR29;    /* offset: 0x01EC size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR29;    /* offset: 0x01EE size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR30;    /* offset: 0x01F0 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR30;    /* offset: 0x01F2 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR30;    /* offset: 0x01F4 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR30;    /* offset: 0x01F6 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR31;    /* offset: 0x01F8 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR31;    /* offset: 0x01FA size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR31;    /* offset: 0x01FC size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR31;    /* offset: 0x01FE size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR32;    /* offset: 0x0200 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR32;    /* offset: 0x0202 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR32;    /* offset: 0x0204 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR32;    /* offset: 0x0206 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR33;    /* offset: 0x0208 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR33;    /* offset: 0x020A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR33;    /* offset: 0x020C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR33;    /* offset: 0x020E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR34;    /* offset: 0x0210 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR34;    /* offset: 0x0212 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR34;    /* offset: 0x0214 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR34;    /* offset: 0x0216 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR35;    /* offset: 0x0218 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR35;    /* offset: 0x021A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR35;    /* offset: 0x021C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR35;    /* offset: 0x021E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR36;    /* offset: 0x0220 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR36;    /* offset: 0x0222 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR36;    /* offset: 0x0224 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR36;    /* offset: 0x0226 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR37;    /* offset: 0x0228 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR37;    /* offset: 0x022A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR37;    /* offset: 0x022C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR37;    /* offset: 0x022E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR38;    /* offset: 0x0230 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR38;    /* offset: 0x0232 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR38;    /* offset: 0x0234 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR38;    /* offset: 0x0236 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR39;    /* offset: 0x0238 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR39;    /* offset: 0x023A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR39;    /* offset: 0x023C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR39;    /* offset: 0x023E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR40;    /* offset: 0x0240 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR40;    /* offset: 0x0242 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR40;    /* offset: 0x0244 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR40;    /* offset: 0x0246 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR41;    /* offset: 0x0248 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR41;    /* offset: 0x024A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR41;    /* offset: 0x024C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR41;    /* offset: 0x024E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR42;    /* offset: 0x0250 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR42;    /* offset: 0x0252 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR42;    /* offset: 0x0254 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR42;    /* offset: 0x0256 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR43;    /* offset: 0x0258 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR43;    /* offset: 0x025A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR43;    /* offset: 0x025C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR43;    /* offset: 0x025E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR44;    /* offset: 0x0260 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR44;    /* offset: 0x0262 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR44;    /* offset: 0x0264 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR44;    /* offset: 0x0266 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR45;    /* offset: 0x0268 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR45;    /* offset: 0x026A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR45;    /* offset: 0x026C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR45;    /* offset: 0x026E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR46;    /* offset: 0x0270 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR46;    /* offset: 0x0272 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR46;    /* offset: 0x0274 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR46;    /* offset: 0x0276 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR47;    /* offset: 0x0278 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR47;    /* offset: 0x027A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR47;    /* offset: 0x027C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR47;    /* offset: 0x027E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR48;    /* offset: 0x0280 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR48;    /* offset: 0x0282 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR48;    /* offset: 0x0284 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR48;    /* offset: 0x0286 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR49;    /* offset: 0x0288 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR49;    /* offset: 0x028A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR49;    /* offset: 0x028C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR49;    /* offset: 0x028E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR50;    /* offset: 0x0290 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR50;    /* offset: 0x0292 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR50;    /* offset: 0x0294 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR50;    /* offset: 0x0296 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR51;    /* offset: 0x0298 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR51;    /* offset: 0x029A size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR51;    /* offset: 0x029C size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR51;    /* offset: 0x029E size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR52;    /* offset: 0x02A0 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR52;    /* offset: 0x02A2 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR52;    /* offset: 0x02A4 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR52;    /* offset: 0x02A6 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR53;    /* offset: 0x02A8 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR53;    /* offset: 0x02AA size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR53;    /* offset: 0x02AC size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR53;    /* offset: 0x02AE size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR54;    /* offset: 0x02B0 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR54;    /* offset: 0x02B2 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR54;    /* offset: 0x02B4 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR54;    /* offset: 0x02B6 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR55;    /* offset: 0x02B8 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR55;    /* offset: 0x02BA size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR55;    /* offset: 0x02BC size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR55;    /* offset: 0x02BE size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR56;    /* offset: 0x02C0 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR56;    /* offset: 0x02C2 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR56;    /* offset: 0x02C4 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR56;    /* offset: 0x02C6 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR57;    /* offset: 0x02C8 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR57;    /* offset: 0x02CA size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR57;    /* offset: 0x02CC size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR57;    /* offset: 0x02CE size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR58;    /* offset: 0x02D0 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR58;    /* offset: 0x02D2 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR58;    /* offset: 0x02D4 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR58;    /* offset: 0x02D6 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR59;    /* offset: 0x02D8 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR59;    /* offset: 0x02DA size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR59;    /* offset: 0x02DC size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR59;    /* offset: 0x02DE size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR60;    /* offset: 0x02E0 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR60;    /* offset: 0x02E2 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR60;    /* offset: 0x02E4 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR60;    /* offset: 0x02E6 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR61;    /* offset: 0x02E8 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR61;    /* offset: 0x02EA size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR61;    /* offset: 0x02EC size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR61;    /* offset: 0x02EE size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR62;    /* offset: 0x02F0 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR62;    /* offset: 0x02F2 size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR62;    /* offset: 0x02F4 size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR62;    /* offset: 0x02F6 size: 16 bit */
                 /* Message Buffer Configuration Control Status Register */
            FR_MBCCSR_16B_tag MBCCSR63;    /* offset: 0x02F8 size: 16 bit */
                         /* Message Buffer Cycle Counter Filter Register */
            FR_MBCCFR_16B_tag MBCCFR63;    /* offset: 0x02FA size: 16 bit */
                                     /* Message Buffer Frame ID Register */
            FR_MBFIDR_16B_tag MBFIDR63;    /* offset: 0x02FC size: 16 bit */
                                        /* Message Buffer Index Register */
            FR_MBIDXR_16B_tag MBIDXR63;    /* offset: 0x02FE size: 16 bit */
         };

      };
      int8_t FR_reserved_0300[15616];

   } FR_tag;


#define FR_BASEADDRESS 0xFFFE0000UL
/* the crazy cast below is needed to fool the MISRA tool checker */
#define FR    (*(volatile FR_tag *)(volatile void*) ((vuint8_t*)0UL + 0xFFFE0000UL))




/*****************************************************************************\
 ***************************************************************************** 
 **********   GENERIC REGISTER PROTECTION MACROS AND VERIFICATION   **********
 ***************************************************************************** 
\*****************************************************************************/

/*
   MJR 16-Oct-2007:

   When writing these macros I have included some doxygen like comments into
   the corresponding definition. I hope this is useful information and does 
   help in using them. Please direct any suggestions for improvements to me.

   These macros are designed to be used in conjunction with the definitions
   in the #define based header file. Therefore, whenever they need a register 
   definition they expect a dereferenced pointer value; all macros using this 
   form of a register value use the parameter <thereg> for the register. 
   There is a second set of macros that work with an address value (numerical 
   value); these macros have the special suffix _ADDRESS and use a parameter 
   <reg_addr>. There are currently no macros for usage with structures.
 */

/*****************************************************************************\
 * REGISTER PROTECTION: Level1 Macros - this is the user interface
\*****************************************************************************/

/*! Modify the register content while concurrently setting the soft lock bit.

    A macro of type WRITE_WITH_LOCK<size> with <size> = { 8, 16, 32 } writes
    the given register <thereg> with the new value <newvalue>. Concurrently
    it sets the corresponding soft lock bit(s) assigned to this register.
    The value of size selects the access width for this register, which must
    be one of 8, 16, or 32 bits.

    @PARAM thereg     Pointer to the given register
    @PARAM newvalue   Value to be written to the given register
 */

#define WRITE_WITH_LOCK8(thereg,newvalue) \
   WRITE_WITH_LOCK8_ADDRESS(LOCK__REG2ADDR(thereg),(newvalue))

#define WRITE_WITH_LOCK8_ADDRESS(reg_addr,newvalue) \
   ((*((vuint8_t*)((reg_addr)+LOCK__OFFSET))) = (newvalue))


#define WRITE_WITH_LOCK16(thereg,newvalue) \
   WRITE_WITH_LOCK16_ADDRESS(LOCK__REG2ADDR(thereg),(newvalue))

#define WRITE_WITH_LOCK16_ADDRESS(reg_addr,newvalue) \
   ((*((vuint16_t*)((reg_addr)+LOCK__OFFSET))) = (newvalue))


#define WRITE_WITH_LOCK32(thereg,newvalue) \
   WRITE_WITH_LOCK32_ADDRESS(LOCK__REG2ADDR(thereg),(newvalue))

#define WRITE_WITH_LOCK32_ADDRESS(reg_addr,newvalue) \
   ((*((vuint32_t*)((reg_addr)+LOCK__OFFSET))) = (newvalue))


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *\
   REGISTER PROTECTION: Working with Soft Lock Bits
\* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*! Retrieves the soft lock bits assigned to the given register.

    The macro GET_SOFTLOCK determines the soft lock bits assigned to the given
    register specified with <thereg> and assignes them to the variable <dest>; 
    this variable should receive an eight bit value, which is the maximum size
    for the soft lock bits for a single register.

    @PARAM thereg   Pointer to the given register
    @PARAM dest     Variable receiving the soft lock bit information

    @SEE SET_SOFTLOCK8 SET_SOFTLOCK16 SET_SOFTLOCK32 
         CLR_SOFTLOCK8 CLR_SOFTLOCK16 CLR_SOFTLOCK32
 */

// Retrieves the soft lock bits for a given register and stores it into dest
#define GET_SOFTLOCK(thereg,dest) \
   GET_SOFTLOCK_ADDRESS(LOCK__REG2ADDR(thereg),(dest))

#define GET_SOFTLOCK_ADDRESS(reg_addr,dest) \
   ((dest) = (*(LOCK__SLB_REGISTER(reg_addr))))


/*! Sets the soft lock bits assigned to the given register.

    A macro of type SET_SOFTLOCK<size> with <size> = { 8, 16, 32 } sets the
    soft lock bits assigned to the given register <thereg>. The value of size 
    selects the access width (and also the amount of affected bits) for this 
    register, which must be one of 8, 16, or 32 bits.

    @NOTE Soft lock bits can only be written in supervisor mode only 
   
    @PARAM thereg   Pointer to the given register

    @SEE GET_SOFTLOCK CLR_SOFTLOCK8 CLR_SOFTLOCK16 CLR_SOFTLOCK32
 */

// Sets the soft lock bit for the given (8 bit wide) register
#define SET_SOFTLOCK8(thereg) \
   SET_SOFTLOCK8_ADDRESS(LOCK__REG2ADDR(thereg))

#define SET_SOFTLOCK8_ADDRESS(reg_addr) \
   ((*LOCK__SLB_REGISTER(reg_addr)) = LOCK__WRITE_MASK08(reg_addr,LOCK__SET_MASK))


// Sets the soft lock bit for the given (16 bit wide) register
#define SET_SOFTLOCK16(thereg) \
   SET_SOFTLOCK16_ADDRESS(LOCK__REG2ADDR(thereg))

#define SET_SOFTLOCK16_ADDRESS(reg_addr) \
   ((*LOCK__SLB_REGISTER(reg_addr)) = LOCK__WRITE_MASK16(reg_addr,LOCK__SET_MASK))


// Sets the soft lock bit for the given (32 bit wide) register
#define SET_SOFTLOCK32(thereg) \
   SET_SOFTLOCK32_ADDRESS(LOCK__REG2ADDR(thereg))

#define SET_SOFTLOCK32_ADDRESS(reg_addr) \
   ((*LOCK__SLB_REGISTER(reg_addr)) = LOCK__WRITE_MASK32(reg_addr,LOCK__SET_MASK))


/*! Clears the soft lock bits assigned to the given register.

    A macro of type CLR_SOFTLOCK<size> with <size> = { 8, 16, 32 } clears the
    soft lock bits assigned to the given register <thereg>. The value of size 
    selects the access width (and also the amount of affected bits) for this 
    register, which must be one of 8, 16, or 32 bits.

    @NOTE Soft lock bits can only be written in supervisor mode only 
   
    @PARAM thereg   Pointer to the given register

    @SEE GET_SOFTLOCK SET_SOFTLOCK8 SET_SOFTLOCK16 SET_SOFTLOCK32
 */

// Clears the soft lock bit for the given (8 bit wide) register
#define CLR_SOFTLOCK8(thereg) \
   CLR_SOFTLOCK8_ADDRESS(LOCK__REG2ADDR(thereg))

#define CLR_SOFTLOCK8_ADDRESS(reg_addr) \
   ((*LOCK__SLB_REGISTER(reg_addr)) = LOCK__WRITE_MASK08(reg_addr,LOCK__CLR_MASK))


// Clears the soft lock bit for the given (16 bit wide) register
#define CLR_SOFTLOCK16(thereg) \
   CLR_SOFTLOCK16_ADDRESS(LOCK__REG2ADDR(thereg))

#define CLR_SOFTLOCK16_ADDRESS(reg_addr) \
   ((*LOCK__SLB_REGISTER(reg_addr)) = LOCK__WRITE_MASK16(reg_addr,LOCK__CLR_MASK))


// Clears the soft lock bit for the given (32 bit wide) register
#define CLR_SOFTLOCK32(thereg) \
   CLR_SOFTLOCK32_ADDRESS(LOCK__REG2ADDR(thereg))

#define CLR_SOFTLOCK32_ADDRESS(reg_addr) \
   ((*LOCK__SLB_REGISTER(reg_addr)) = LOCK__WRITE_MASK32(reg_addr,LOCK__CLR_MASK))


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *\
   REGISTER PROTECTION: Accessing the Global Control Register (GCR)
\* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*! Sets the hardlock bit HLB in the module's Global Control Register GCR.

    The macro SET_HARDLOCK sets the hard lock bit in the module specific Global
    Control Register (GCR). Setting this bit will block the modification of all
    soft lock bits, effectively freezing the actual lock state of the module.
    This bit can only be cleared by a system reset.

    @PARAM base   Base address of the given module

    @NOTE: This macro must be executed in supervisor mode only

    @SEE  USER_ACCESS_FORBIDDEN USER_ACCESS_ALLOWED
 */

#define SET_HARDLOCK(base) \
   ((*LOCK__GCR_REGISTER(base)) = ((*LOCK__GCR_REGISTER(base)) | LOCK__GCR_HLB))

/*! Clears the UAA bit in the module's Global Control Register GCR.

    The macro USER_ACCESS_FORBIDDEN clears the User Access Allowed bit in the
    module's Global Control Register GCR; permitting access only in supervisor
    mode. 

    @PARAM base   Base address of the given module

    @NOTE: This macro must be executed in supervisor mode only

    @SEE  SET_HARDLOCK USER_ACCESS_ALLOWED
 */

#define USER_ACCESS_FORBIDDEN(base) \
   ((*LOCK__GCR_REGISTER(base)) = ((*LOCK__GCR_REGISTER(base)) & (~LOCK__GCR_UAA)))

/*! Sets the UAA bit in the module's Global Control Register GCR.

    The macro USER_ACCESS_ALLOWED sets the User Access Allowed bit in the
    module's Global Control Register GCR; permitting access to the module
    register in any mode defined by the module's protection scheme.

    @PARAM base   Base address of the given module

    @NOTE: This macro must be executed in supervisor mode only

    @SEE  SET_HARDLOCK USER_ACCESS_FORBIDDEN
 */

#define USER_ACCESS_ALLOWED(base) \
   ((*LOCK__GCR_REGISTER(base)) = ((*LOCK__GCR_REGISTER(base)) | LOCK__GCR_UAA))

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *\
   REGISTER PROTECTION: Global Control Register (GCR) field definitions
\* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#define LOCK__GCR_HLB_VALUE(x)  (((x)&1) << LOCK__GCR_HLB_BIT)
#define LOCK__GCR_HLB_BIT       (31)
#define LOCK__GCR_HLB           (1 << LOCK__GCR_HLB_BIT)

#define LOCK__GCR_UAA_VALUE(x)  (((x)&1) << LOCK__GCR_UAA_BIT)
#define LOCK__GCR_UAA_BIT       (23)
#define LOCK__GCR_UAA           (1 << LOCK__GCR_UAA_BIT)

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *\
   REGISTER PROTECTION: Direct access to register protection gasket registers
\* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// Provides the content of the SLB register for a given module register; here
//  it is possible to either use the register pointer or the related address.
//  Please note that a SLB register is always 8 bit wide as is the result.
#define LOCK_SLB(thereg) \
   LOCK_SLB_ADDRESS(LOCK__REG2ADDR(thereg))

#define LOCK_SLB_ADDRESS(reg_addr) \
   (*LOCK__SLB_REGISTER(reg_addr))

// Provides the content of the GCR register of the protection register gasket;
//  this macro requires the base address of the corresponding module
#define LOCK_GCR(base) \
   (*LOCK__GCR_REGISTER(base))

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *\
   REGISTER PROTECTION: Helper macros for Level1 macros
\* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* 
   !!! CAUTION !!! CAUTION !!! CAUTION !!! CAUTION !!! CAUTION !!! CAUTION !!! 
   Never use any of these macros directly; they may change without notice
   !!! CAUTION !!! CAUTION !!! CAUTION !!! CAUTION !!! CAUTION !!! CAUTION !!! 
 */

// Provides a pointer to the SLB register from a given module register addr; 
//  please note that a SLB register is always 8 bit wide
#define LOCK__SLB_REGISTER(reg_addr) \
   ((vuint8_t*) LOCK__SLB_REG_ADDR(reg_addr))

// Provides a pointer to the GCR register of the protection register gasket;
//  this macro requires the base address of the corresponding module 
#define LOCK__GCR_REGISTER(base) \
   ((vuint32_t*) LOCK__GCR_REG_ADDR(base))


// Determines the address of the given register from the given pointer
#define LOCK__REG2ADDR(thereg) \
   ((uint32_t) &(thereg))


// Mask that extracts address bits available for registers within a block
#define LOCK__BLOCK_MASK 0x3FFF

// Offset into the mirrored address range that locks as a side effect
#define LOCK__OFFSET 0x2000

// Start address of the soft lock bit (SLB) registers
#define LOCK__SLB_OFFSET 0x3800

// Offset of the GCR register from the base address of the block
#define LOCK__GCR_OFFSET 0x3FFC


// Determines the base address of the current block from a given register addr
#define LOCK__BLOCK_BASE(reg_addr) \
   ((reg_addr) & (~LOCK__BLOCK_MASK))

// Determines the address offset of the related SLBR from a given register addr
//  NOTE: there is one 8 bit SLB register per 32 bit module register 
#define LOCK__SLB_REG_OFFSET(reg_addr) \
   (LOCK__SLB_OFFSET + (((reg_addr) & LOCK__BLOCK_MASK) >> 2))

// Calculates the address of the corresponding SLB register for a given module
//  register address
#define LOCK__SLB_REG_ADDR(reg_addr) \
   (LOCK__BLOCK_BASE(reg_addr) + LOCK__SLB_REG_OFFSET(reg_addr))

// Determines the address of the GCR register from the base address of a block
//  -- any register address would work either, but this is just for stability
#define LOCK__GCR_REG_ADDR(base) \
   (LOCK__BLOCK_BASE(base) + LOCK__GCR_OFFSET)


// Masks used to identify a SLB clear or set operation 
#define LOCK__CLR_MASK 0xF0
#define LOCK__SET_MASK 0xFF

// Determines the write enables and soft lock bits for a given 8 bit register
#define LOCK__WRITE_MASK08(reg_addr,mask) \
   ((0x11 & (mask)) << (3 - ((reg_addr) & 3)))

// Determines the write enables and soft lock bits for a given 16 bit register
#define LOCK__WRITE_MASK16(reg_addr,mask) \
   ((0x33 & (mask)) << (2 - ((reg_addr) & 2)))

// Determines the write enables and soft lock bits for a given 32 bit register
#define LOCK__WRITE_MASK32(reg_addr,mask) \
   (mask)

/*****************************************************************************\
 ***************************************************************************** 
 **********   INFORMATION EXTRACTED FROM TEST FLASH                 **********
 ***************************************************************************** 
\*****************************************************************************/

/*
   MJR 11-May-2010, 23-Oct-2012:

   These definitions below are designed to deliver some basic functionality 
   for retrieving the actual Test Flash content by calling a BAM function. 

   !!!!!!!!!!!!!!!!!!!!!!!!!!!!! IMPORTANT NOTE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   The usage of the function READ_FROM_TF(buffer_loc,result) is not permitted
    by the Safety Application Guide. Usage of this function is only permitted
    when the calling application asserts appropriate countermeasures.

   !!!!!!!!!!!!!!!!!!!!!!!!!!!!! IMPORTANT NOTE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

/*****************************************************************************\
 * TEST FLASH EXTRACTION FUNCTION (located in BAM and must be called here)
\*****************************************************************************/

   /* Structure definition for the data that is being extracted from the Test
      Flash. Attention: only the first 128 words are copied by the BAM code.
        0x000 - 0x007: Temperature Sensor 0/1 calibration word at cold 
        0x008 - 0x00F: Temperature Sensor 0/1 calibration word at hot 
        0x010 - 0x02F: ADC 0 Calibration Word 1 - 8 (32 bit)
        0x034 - 0x053: ADC 1 Calibration Word 1 - 8 (32 bit)
      The following words are only implemented in case of Known Good Die 
        0x058 - 0x05F: PART ID 1 L/H
        0x060 - 0x063: PART ID 2
    */

#if 0 /* MjR - disabled, because not yet verified */

   typedef struct READ_TEST_FLASH_BUFFER_struct_tag {

      union {   /* Temperature Sensor 0/1 Calibration data at cold temperature */
         uint16_t TSENS_CAL_COLD[4];   /* Array of 16 bit words */
         struct {
            uint32_t TSENS0_CAL_W24;  /* TSENS 0 calibration data W2 (P2/PTAT) and W4 (C2/CTAT) at cold temperature */
            uint32_t TSENS1_CAL_W24;  /* TSENS 1 calibration data W2 (P2/PTAT) and W4 (C2/CTAT) at cold temperature */
         };
      };

      union {   /* Temperature Sensor 0/1 Calibration data at hot temperature */
         uint16_t TSENS2_CAL_HOT[4];   /* Array of 16 bit words */
         struct {
            uint32_t TSENS0_CAL_W13;  /* TSENS 0 calibration data W1 (P1/PTAT) and W3 (C2/CTAT) at hot temperature */
            uint32_t TSENS1_CAL_W13;  /* TSENS 1 calibration data W1 (P1/PTAT) and W3 (C2/CTAT) at hot temperature */
         };
      };

      union {   /* ADC 0 Calibration Word 1 - 8 */
         uint32_t ADC0_CAL_W[8];
         struct {
            uint32_t ADC0_CAL_W1;  /* ADC0 Self-Test calibration - RC algo */
            uint32_t ADC0_CAL_W2;  /* ADC0 Self-Test calibration - C algo S0 step */
            uint32_t ADC0_CAL_W3;  /* ADC0 Self-Test calibration - C algo Sn step */
            uint32_t ADC0_CAL_W4;  /* ADC0 Self-Test calibration - S algo S0 step - 3.3V */
            uint32_t ADC0_CAL_W5;  /* ADC0 Self-Test calibration - S algo S0 step - 5.0V */
            uint32_t ADC0_CAL_W6;  /* ADC0 Self-Test calibration - S algo S1 step - integer */
            uint32_t ADC0_CAL_W7;  /* ADC0 Self-Test calibration - S algo S1 step - float */
            uint32_t ADC0_CAL_W8;  /* ADC0 Self-Test calibration - S algo S2 step */
         }; 
      };
      uint8_t reserved_0x030[4];

      union {   /* ADC 1 Calibration Word 1 - 8 */
         uint32_t ADC1_CAL_W[8];
         struct {
            uint32_t ADC1_CAL_W1;  /* ADC1 Self-Test calibration - RC algo */
            uint32_t ADC1_CAL_W2;  /* ADC1 Self-Test calibration - C algo S0 step */
            uint32_t ADC1_CAL_W3;  /* ADC1 Self-Test calibration - C algo Sn step */
            uint32_t ADC1_CAL_W4;  /* ADC1 Self-Test calibration - S algo S0 step - 3.3V */
            uint32_t ADC1_CAL_W5;  /* ADC1 Self-Test calibration - S algo S0 step - 5.0V */
            uint32_t ADC1_CAL_W6;  /* ADC1 Self-Test calibration - S algo S1 step - integer */
            uint32_t ADC1_CAL_W7;  /* ADC1 Self-Test calibration - S algo S1 step - float */
            uint32_t ADC1_CAL_W8;  /* ADC1 Self-Test calibration - S algo S2 step */
         };
      };
      uint8_t reserved_0x54[4];

/* Know Good Die only
      union {
         uint32_t PART_ID1[2];
         struct {
            uint32_t PART_ID1L;
            uint32_t PART_ID1H;
         };
      };
 */

      uint32_t PART_ID2; 

      uint8_t reserved_0x64[412];

   } READ_TEST_FLASH_BUFFER_tag;
#endif


/* 
   Define based accesses
 */

#define TF_CONTENT_TSENS0_CAL_W24(buf)  (*((uint32_t*)((buf)+0x00)))
#define TF_CONTENT_TSENS1_CAL_W24(buf)  (*((uint32_t*)((buf)+0x04)))
#define TF_CONTENT_TSENS0_CAL_W13(buf)  (*((uint32_t*)((buf)+0x08)))
#define TF_CONTENT_TSENS1_CAL_W13(buf)  (*((uint32_t*)((buf)+0x0C)))
#define TF_CONTENT_ADC0_CAL_W1(buf)     (*((uint32_t*)((buf)+0x10)))
#define TF_CONTENT_ADC0_CAL_W2(buf)     (*((uint32_t*)((buf)+0x14)))
#define TF_CONTENT_ADC0_CAL_W3(buf)     (*((uint32_t*)((buf)+0x18)))
#define TF_CONTENT_ADC0_CAL_W4(buf)     (*((uint32_t*)((buf)+0x1C)))
#define TF_CONTENT_ADC0_CAL_W5(buf)     (*((uint32_t*)((buf)+0x20)))
#define TF_CONTENT_ADC0_CAL_W6(buf)     (*((uint32_t*)((buf)+0x24)))
#define TF_CONTENT_ADC0_CAL_W7(buf)     (*((uint32_t*)((buf)+0x28)))
#define TF_CONTENT_ADC0_CAL_W8(buf)     (*((uint32_t*)((buf)+0x2C)))
#define TF_CONTENT_ADC1_CAL_W1(buf)     (*((uint32_t*)((buf)+0x34)))
#define TF_CONTENT_ADC1_CAL_W2(buf)     (*((uint32_t*)((buf)+0x38)))
#define TF_CONTENT_ADC1_CAL_W3(buf)     (*((uint32_t*)((buf)+0x3C)))
#define TF_CONTENT_ADC1_CAL_W4(buf)     (*((uint32_t*)((buf)+0x40)))
#define TF_CONTENT_ADC1_CAL_W5(buf)     (*((uint32_t*)((buf)+0x44)))
#define TF_CONTENT_ADC1_CAL_W6(buf)     (*((uint32_t*)((buf)+0x48)))
#define TF_CONTENT_ADC1_CAL_W7(buf)     (*((uint32_t*)((buf)+0x4C)))
#define TF_CONTENT_ADC1_CAL_W8(buf)     (*((uint32_t*)((buf)+0x50)))

/* Know Good Die only

#define TF_CONTENT_PART_ID1L(buf)       (*((uint32_t*)((buf)+0x58)))
#define TF_CONTENT_PART_ID1H(buf)       (*((uint32_t*)((buf)+0x5C)))
#define TF_CONTENT_PART_ID2(buf)        (*((uint32_t*)((buf)+0x60)))

*/

/*! Macro to invoke a BAM function that will retrieve the TestFlash content.

    The macro below will invoke a BAM function that retrieves the content 
     of the TestFlash and puts it into the provided buffer <buffer_loc>.
     This buffer must have a size of at least 1024 bytes for receiving the
     data stored within the Test Flash.
    The BAM function is identified by a Hook, which is located at the end of
     the BAM ROM to assert a stable location for calling the BAM function. 

    The return value from this function identifies whether the copy operation
     was successful. The following return values are possible:
      0x00000008   Test Flash is not available, can not be accessed (ERROR)
      0x00000004   Test Flash has already been accessed             (ERROR)
      0x00000000   Test Flash content successfully copied          (SUCCESS)

   !!!!!!!!!!!!!!!!!!!!!!!!!!!!! IMPORTANT NOTE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   The usage of the function READ_FROM_TF(buffer_loc,result) is not permitted
    by the Safety Application Guide. Usage of this function is only permitted
    when the calling application asserts appropriate countermeasures.

   !!!!!!!!!!!!!!!!!!!!!!!!!!!!! IMPORTANT NOTE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

#define READ_FROM_TF(buffer_loc,result) \
   result = ((uint32_t(*)(uint32_t*)) (*((uint32_t*) 0xFFFFDFF0))) ((uint32_t*)buffer_loc)

/*
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!! IMPORTANT NOTE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   The usage of the function READ_FROM_TF(buffer_loc,result) is not permitted
    by the Safety Application Guide. Usage of this function is only permitted
    when the calling application asserts appropriate countermeasures.

   !!!!!!!!!!!!!!!!!!!!!!!!!!!!! IMPORTANT NOTE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

#ifdef __MWERKS__
#pragma pop
#endif

#ifdef __cplusplus
}
#endif
#endif /* _leopard_H_ */

/* End of file */

