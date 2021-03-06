/*!
* Copyright (c) 2015, NXP Semiconductor, Inc.
* All rights reserved.
*
* \file flash_boot_kinetis.h.
* \version 1.00
* \brief This file this file contains internal flash functionality
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of NXP Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

/** includes */
#include "EmbeddedTypes.h"
#include "HEXIWEAR_types.h"

#ifdef __cplusplus
    extern "C" {
#endif

/** public macros */

/** FLASH hardware algorithm operation commands */

#define FLASH_PROGRAM_BYTE        0x04
#define FLASH_PROGRAM_WORD        0x05
#define FLASH_PROGRAM_LONGWORD    0x06
#define FLASH_PROGRAM_PHRASE      0x07
#define FLASH_ERASE_BLOCK         0x08
#define FLASH_ERASE_SECTOR        0x09
#define FLASH_PROGRAM_SECTION     0x0B
#define FLASH_READ_ONCE           0x41
#define FLASH_ERASE_ALL_BLOCK     0x44
#define FLASH_SET_EERAM           0x81
#define FLASH_READ_RESOURCE       0x03
#define FLASH_PROGRAM_ONCE        0x43

#define FLASH_LONG_WORD_SEZE     4
#define FLASH_PHASE_SEZE         8
#define FLASH_DOUBLE_PHASE_SEZE 16

#define FCCOB_REGS  12
#define INTFLASH_OK     0
#define INTFLASH_FAIL   1

#define FLASH_DFLASH_IFR_READRESOURCE_ADDRESS   0x8000FC

#define ERASE_MASS_INDEX       4
#define ERASE_BLOCK_INDEX      4
#define PROGRAM_BYTE_INDEX     5
#define PROGRAM_SECTION_INDEX  7
#define PROGRAM_LONGWORD_INDEX 8
#define SET_EERAM_INDEX        4

#define FLASH_FLEXRAM_FNC_CTRL_CODE    0x00

#define FLASH_HW_VER_RECORD ( 0 )


/** public type definitions */

/** FCOOB register structure */
typedef union
{
  uint8_t all[FCCOB_REGS];

  struct
  {
    uint8_t fccob3;
    uint8_t fccob2;
    uint8_t fccob1;
    uint8_t fccob0;
    uint8_t fccob7;
    uint8_t fccob6;
    uint8_t fccob5;
    uint8_t fccob4;
    uint8_t fccobB;
    uint8_t fccobA;
    uint8_t fccob9;
    uint8_t fccob8;
  }regs;

  struct
  {
    uint32_t fccob3210;
    uint32_t fccob7654;
    uint32_t fccobBA98;
  }regsLong;

} FCC0B_STR;

/**
 * initialize the FLASH module
 */
void INTFLASH_Init();

/**
 * generically program FLASH
 * @param  dest   FLASH address
 * @param  source data address
 * @param  size   data size to program
 * @return        status flag
 */
uint8_t INTFLASH_Program(uint32_t dest, uint32_t source, uint32_t size);

/**
 * program multiple long words
 * @param  dest   FLASH address
 * @param  source data address
 * @param  size   data size to program
 * @return        status flag
 */
uint8_t INTFLASH_ProgramLongWords(uint32_t destination, uint32_t source, uint32_t size);

/**
 * program one long word
 * @param  dest   FLASH address
 * @param  source data address
 * @param  size   data size to program
 * @return        status flag
 */
uint8_t INTFLASH_ProgramLongWord(uint32_t destination, uint32_t data32b);

/**
 * program one section (maximum is 2048 Bytes);

 * @param  destination FLASH address
 * @param  pSource     data address
 * @param  size        data size to program
 * @return             status flag
 */
uint8_t INTFLASH_ProgramSection(uint32_t destination, uint32_t* pSource, uint32_t size);

/**
 * program section phrases
 * @param  destination FLASH address
 * @param  pSource     data address
 * @param  size        data size to program
 * @return             status flag
 */
uint8_t INTFLASH_ProgramSectionPhrases(uint32_t destination, uint32_t* pSource, uint32_t size);

/**
 * program one byte
 * @param  destination FLASH address
 * @param  data8b      byte to program
 * @return             status flag
 */
uint8_t INTFLASH_ProgramByte(uint32_t destination, uint8_t data8b);

/**
 * program HW revision structure
 * @param  source HW revision structure's address
 * @return        status flag
 */
uint8_t INTFLASH_ProgramHwRev( hexiwear_hw_rev_t* source );

/**
 * read HW revision
 * @param  dst HW revision structure to populate with info
 * @return     status flag
 */
uint8_t INTFLASH_ReadHwRev( hexiwear_hw_rev_t* dst );

/**
 * erase FLASH memory sector (0x800);

 * @param  destination FLASH address
 * @return             status flag
 */
uint8_t INTFLASH_EraseSector(uint32_t destination);

/**
 * erase of all block of memory
 */
uint8_t INTFLASH_MassErase(void);

/**
 * enable the EERAM
 */
uint8_t INTFLASH_SetEEEEnable(uint8_t ctrl_code);

/**
 * program HW revision structure
 * @param  source HW revision structure's address
 * @return        status flag
 */
uint8_t INTFLASH_ProgramHwRev( hexiwear_hw_rev_t* source );

/**
 * read HW revision
 * @param  dst HW revision structure to populate with info
 * @return     status flag
 */
uint8_t INTFLASH_ReadHwRev( hexiwear_hw_rev_t* dst );

#ifdef __cplusplus
}
#endif