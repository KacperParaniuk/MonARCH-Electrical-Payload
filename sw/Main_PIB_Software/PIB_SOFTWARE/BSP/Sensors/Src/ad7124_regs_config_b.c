/*!
 *****************************************************************************
  @file:  ad7124_regs_config_b.c

  @brief: Configuration file B for AD7124

  @details:
 -----------------------------------------------------------------------------
Copyright (c) 2019 Analog Devices, Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
	and/or other materials provided with the distribution.
  - Modified versions of the software must be conspicuously marked as such.
  - This software is licensed solely and exclusively for use with processors/
    products manufactured by or for Analog Devices, Inc.
  - This software may not be combined or merged with other code in any manner
    that would cause the software to become subject to terms and conditions
	which differ from those listed here.
  - Neither the name of Analog Devices, Inc. nor the names of its contributors
    may be used to endorse or promote products derived from this software without
    specific prior written permission.
  - The use of this software may or may not infringe the patent rights of one
    or more patent holders.  This license does not release you from the
	requirement that you obtain separate licenses from these patent holders
	to use this software.

THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES, INC. AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-
INFRINGEMENT, TITLE, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL ANALOG DEVICES, INC. OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, PUNITIVE OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, DAMAGES ARISING OUT OF
CLAIMS OF INTELLECTUAL PROPERTY RIGHTS INFRINGEMENT; PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

20180927-7CBSD SLA

*****************************************************************************/

#include "ad7124_regs.h"

const struct ad7124_st_reg ad7124_regs_config_b[AD7124_REG_NO] = {
		{0x00, 0x00, 1, 2},/* AD7124_Status */
		{0x01, 0x0708, 2, 1},
		{0x02, 0x000000, 3, 2},/* AD7124_Data */
		{0x03, 0x000000, 3, 1}, /* AD7124_IOCon1 */
		{0x04, 0x0000, 2, 1},
		{0x05, 0x00, 1, 2}, /* AD7124_ID */
		{0x06, 0x000000, 3, 2}, /* AD7124_Error */
		{0x07, 0x000044, 3, 1},  /* AD7124_Error_En */
		{0x08, 0x00, 1, 2}, /* AD7124_Mclk_Count */
		{0x09, 0x8001, 2, 1},  /* AD7124_Channel_0 */ // AINP = 0 AINM = 1 Setup = 0
		{0x0A, 0x0001, 2, 1}, // 1
		{0x0B, 0x8043, 2, 1}, // 2
		{0x0C, 0x0001, 2, 1}, // 3
		{0x0D, 0x8085, 2, 1}, // 4 AINP = 4 AINM = 5 Setup = 0
		{0x0E, 0x0001, 2, 1}, // 5 off
		{0x0F, 0x80C7, 2, 1}, // 6 AINP = 6 AINM = 7 Setup = 0 1000 0000 1100 0111 80C7
		{0x10, 0x0001, 2, 1}, // 7 off
		{0x11, 0x8109, 2, 1}, // 8 1000 0001 0000 1001
		{0x12, 0x0001, 2, 1}, // 9
		{0x13, 0x814B, 2, 1}, // 10 1000 0001 0100 1011
		{0x14, 0x0001, 2, 1}, // 11
		{0x15, 0x818D, 2, 1}, // 12 1000 0001 1000 1101
		{0x16, 0x0001, 2, 1}, // 13
		{0x17, 0x81CF, 2, 1}, // 14 1000 0001 1100 1111
		{0x18, 0x0001, 2, 1}, /* AD7124_Channel_15 */
		{0x19, 0x0860, 2, 1}, /* AD7124_Config_0 */ // set 8 to 0 if you want unipolar ( I do want to test this ) x0060
		{0x1A, 0x0860, 2, 1},
		{0x1B, 0x0860, 2, 1},
		{0x1C, 0x0860, 2, 1},
		{0x1D, 0x0860, 2, 1},
		{0x1E, 0x0860, 2, 1},
		{0x1F, 0x0860, 2, 1},
		{0x20, 0x0860, 2, 1},
		{0x21, 0x060014, 3, 1}, /* AD7124_Filter_0 */ // I want to also test to see what changes when I set REF+ REF- to Internal Reference (10)
		{0x22, 0x060180, 3, 1},
		{0x23, 0x060180, 3, 1},
		{0x24, 0x060180, 3, 1},
		{0x25, 0x060180, 3, 1},
		{0x26, 0x060180, 3, 1},
		{0x27, 0x060180, 3, 1},
		{0x28, 0x060180, 3, 1},
		{0x29, 0x800000, 3, 1}, /* AD7124_Offset_0 */ // no offset
		{0x2A, 0x800000, 3, 1},
		{0x2B, 0x800000, 3, 1},
		{0x2C, 0x800000, 3, 1},
		{0x2D, 0x800000, 3, 1},
		{0x2E, 0x800000, 3, 1},
		{0x2F, 0x800000, 3, 1},
		{0x30, 0x800000, 3, 1},
		{0x31, 0x500000, 3, 1},  /* AD7124_Gain_0 */ // gain = 1
		{0x32, 0x500000, 3, 1},
		{0x33, 0x500000, 3, 1},
		{0x34, 0x500000, 3, 1},
		{0x35, 0x500000, 3, 1},
		{0x36, 0x500000, 3, 1},
		{0x37, 0x500000, 3, 1},
		{0x38, 0x500000, 3, 1},
};
