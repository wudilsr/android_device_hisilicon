/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by Czyong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
******************************************************************************/


#include <stddef.h>
#include <compile.h>
#include <match.h>
#include <stdio.h>
#include <asm/io.h>

#include "nand_ctrl.h"
#include "nand_chip.h"

/*****************************************************************************/

static struct match_t match_ecc[] = {
	MATCH_SET_TYPE_DATA(NAND_ECC_NONE, "none"),
	MATCH_SET_TYPE_DATA(NAND_ECC_1BIT_512, "1bit/512" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_4BIT_512, "4bit/512" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_8BIT, "4bit/512" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_8BIT_512, "8bit/512" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_24BIT, "24bit/1k" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_40BIT, "40bit/1k" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_4BYTE, "4byte/1k" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_8BYTE, "8byte/1K" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_13BIT, "13bit/1k" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_16BIT, "16bit/1k" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_18BIT, "18bit/1k" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_27BIT, "27bit/1k" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_32BIT, "32bit/1k" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_41BIT, "41bit/1k" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_42BIT, "42bit/1k" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_48BIT, "48bit/1k" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_60BIT, "60bit/1k" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_72BIT, "72bit/1k" ),
	MATCH_SET_TYPE_DATA(NAND_ECC_80BIT, "80bit/1k" ),
};

const char *nand_ecc_name(int type)
{
	return (char *)match_type_to_data(match_ecc, ARRAY_SIZE(match_ecc),
					  type, "unknown");
}
/*****************************************************************************/
