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




#ifndef MM_H_
#define MM_H_

/* [address: XXXXXX/auto]
 * 
 * application: xx
 * allocation: [auto/manual]
 *   - allocates text,data,bsss
 * [segment: text]
 * size: rolldown with sizes... auto??
 *
 * application: xx
 * segment: special
 *   address: [auto/manual]
 *   permissions: 
 * size: 
 * 
 * CPU dependent
 * -------------------------------
 * ENUM [
 *   PU,
 *   MMU,
 * ] MM_TYPE
 *
 * ENUM [
 *  PSIZE_PU_????
 * 
 * ] MM_PU_PSIZE;
 *  
 * ENUM [
 *   PSIZE_1K,
 *   PSIZE_4K,
 *   PSIZE_64K,
 *   PSIZE_1M, 
 * ] MM_MMU_PSIZE; 
 * 
 * ENUM [
 *   PERM_S_R,
 * 	 PERM_S_RW,
 *   ....
 * ] MM_PERMISSIONS
 * 
 * NOT CPU dependent
 * -------------------------------
 * 
 * For each application.
 * 
 * ENUM [
 *   AUTO {
 *   }
 *   MANUAL {
 *     ADDRESS,
 *     PERMISSION,
 *     SIZE,  
 *   }
 * ] ALLOCATION;
 */





#if !defined(_ASSEMBLER_)

/* C-code */

struct TlbEntry {
    uint32_t entry;
    uint32_t mas0;
    uint32_t mas1;
    uint32_t mas2;
    uint32_t mas3;
};

void MM_TlbSetup( const struct TlbEntry *tblTable  );
/* "naked" funciton written in assembler */
void MM_TlbSetupOne( uint32_t mas0, uint32_t mas1, uint32_t mas2, uint32_t mas3 );

#endif



#endif /*MM_H_*/
