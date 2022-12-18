/*
 * This file is part of libbluray
 * Copyright (C) 2009-2012  Petri Hintukainen <phintuka@users.sourceforge.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "util/macro.h"

#include "mobj_parse.h"
#include "hdmv_insn.h"

#include <stdio.h>

#ifndef HI_ADVCA_FUNCTION_RELEASE
static const char * const psr_info[128] = {
    "/*     PSR0:  Interactive graphics stream number */",
    "/*     PSR1:  Primary audio stream number */",
    "/*     PSR2:  PG TextST stream number and PiP PG stream number */",
    "/*     PSR3:  Angle number */",
    "/*     PSR4:  Title number */",
    "/*     PSR5:  Chapter number */",
    "/*     PSR6:  PlayList ID */",
    "/*     PSR7:  PlayItem ID */",
    "/*     PSR8:  Presentation time */",
    "/*     PSR9:  Navigation timer */",
    "/*     PSR10: Selected button ID */",
    "/*     PSR11: Page ID */",
    "/*     PSR12: User style number */",
    "/* RO: PSR13: User age */",
    "/*     PSR14: Secondary audio stream number and secondary video stream number */",
    "/* RO: PSR15: player capability for audio */",
    "/* RO: PSR16: Language code for audio */",
    "/* RO: PSR17: Language code for PG and Text subtitles */",
    "/* RO: PSR18: Menu description language code */",
    "/* RO: PSR19: Country code */",
    "/* RO: PSR20: Region code */ /* 1 - A, 2 - B, 4 - C */",
    "/* RO: PSR21: Output Mode Preference */ /* 0 - 2D, 1 - 3D */",
    "/*     PSR22: Stereoscopic status */ /* 2D / 3D */ ",
    "/* RO: PSR23: display capablity */",
    "/* RO: PSR24: 3D capability */",
    "/*     PSR25 */",
    "/*     PSR26 */",
    "/*     PSR27 */",
    "/*     PSR28 */",
    "/* RO: PSR29: player capability for video */",
    "/* RO: PSR30: player capability for text subtitle */",
    "/* RO: PSR31: Player profile and version */",
    "/*     PSR32 */",
    "/*     PSR33 */",
    "/*     PSR34 */",
    "/*     PSR35 */",
    "/*     PSR36: backup PSR4 */",
    "/*     PSR37: backup PSR5 */",
    "/*     PSR38: backup PSR6 */",
    "/*     PSR39: backup PSR7 */",
    "/*     PSR40: backup PSR8 */",
    "/*     PSR41: */",
    "/*     PSR42: backup PSR10 */",
    "/*     PSR43: backup PSR11 */",
    "/*     PSR44: backup PSR12 */",
    "/*     PSR45: */",
    "/*     PSR46: */",
    "/*     PSR47: */",
    "/* RO: PSR48: Characteristic text caps */",
    "/* RO: PSR49: Characteristic text caps */",
    "/* RO: PSR50: Characteristic text caps */",
    "/* RO: PSR51: Characteristic text caps */",
    "/* RO: PSR52: Characteristic text caps */",
    "/* RO: PSR53: Characteristic text caps */",
    "/* RO: PSR54: Characteristic text caps */",
    "/* RO: PSR55: Characteristic text caps */",
    "/* RO: PSR56: Characteristic text caps */",
    "/* RO: PSR57: Characteristic text caps */",
    "/* RO: PSR58: Characteristic text caps */",
    "/* RO: PSR59: Characteristic text caps */",
    "/* RO: PSR60: Characteristic text caps */",
    "/* RO: PSR61: Characteristic text caps */",
};
#endif

static const char * const insn_groups[4] = {
    "BRANCH",
    "COMPARE",
    "SET",
};

static const char * const insn_group_branch[8] = {
    "GOTO",
    "JUMP",
    "PLAY",
};

static const char * const insn_group_set[8] = {
    "SET",
    "SETSYSTEM",
};

static const char * const insn_opt_set[32] = {
    NULL,
    "move",
    "swap",
    "add",
    "sub",
    "mul",
    "div",
    "mod",
    "rnd",
    "and",
    "or",
    "xor",
    "bset",
    "bclr",
    "shl",
    "shr",
};

static const char * const insn_opt_setsys[32] = {
    NULL,
    "SET_STREAM",
    "SET_NV_TIMER",
    "SET_BUTTON_PAGE",
    "ENABLE_BUTTON",
    "DISABLE_BUTTON",
    "SET_SEC_STREAM",
    "POPUP_OFF",
    "STILL_ON",
    "STILL_OFF",
    "SET_OUTPUT_MODE",
    "SET_STREAM_SS",
};

static const char * const insn_opt_cmp[16] = {
    NULL,
    "bc",
    "eq",
    "ne",
    "ge",
    "gt",
    "le",
    "lt",
};

static const char * const insn_opt_goto[16] = {
    "nop",
    "goto",
    "break",
};

static const char * const insn_opt_jump[16] = {
    "JUMP_OBJECT",
    "JUMP_TITLE",
    "CALL_OBJECT",
    "CALL_TITLE",
    "RESUME"
};

static const char * const insn_opt_play[16] = {
    "PLAY_PL",
    "PLAY_PL_PI",
    "PLAY_PL_MK",
    "TERMINATE_PL",
    "LINK_PI",
    "LINK_MK"
};

#define CHECK_SIZE_RETURN(sum_ptr, len, size) \
    do { \
        *sum_ptr += len; \
        if (*sum_ptr >= size) { \
            return *sum_ptr; \
        } \
    }while(0)

static int _sprint_operand(char *buf, int size, int imm, uint32_t op, int *psr)
{
    char *start = buf;
    int len, sum = 0;

    if (!imm) {
        if (op & 0x80000000) {
            len = snprintf(buf, (size - sum), "PSR%-3u", op & 0x7f);
            CHECK_SIZE_RETURN(&sum, len, size);
            buf += len;
            *psr = op & 0x7f;
        } else {
            len = snprintf(buf, (size - sum), "r%-5u", op & 0xfff);
            CHECK_SIZE_RETURN(&sum, len, size);
            buf += len;
        }
    } else {
        if (op < 99999) {
            len = snprintf(buf, (size - sum), "%-6u", op);
            CHECK_SIZE_RETURN(&sum, len, size);
            buf += len;
        }
        else {
            len = snprintf(buf, (size - sum), "0x%-4x", op);
            CHECK_SIZE_RETURN(&sum, len, size);
            buf += len;
        }
    }

    return buf - start;
}

static int _sprint_operands(char *buf, int size, MOBJ_CMD *cmd)
{
    char      *start = buf;
#ifndef HI_ADVCA_FUNCTION_RELEASE
    HDMV_INSN *insn  = &cmd->insn;
    int psr1 = -1, psr2 = -1;
    int len, sum = 0;

    if (insn->op_cnt > 0) {
        len = _sprint_operand(buf, (size - sum), insn->imm_op1, cmd->dst, &psr1);
        CHECK_SIZE_RETURN(&sum, len, size);
        buf += len;

        if (insn->op_cnt > 1) {
            len = snprintf(buf, (size - sum), ",\t");
            CHECK_SIZE_RETURN(&sum, len, size);
            buf += len;
            len = _sprint_operand(buf, (size - sum), insn->imm_op2, cmd->src, &psr2);
            CHECK_SIZE_RETURN(&sum, len, size);
            buf += len;
        } else {
            len = snprintf(buf, (size - sum), " \t      ");
            CHECK_SIZE_RETURN(&sum, len, size);
            buf += len;
        }
    } else {
        len = snprintf(buf, (size - sum), "       \t      ");
        CHECK_SIZE_RETURN(&sum, len, size);
        buf += len;
    }

    if (psr1 >= 0) {
        len = snprintf(buf, (size - sum), " %s", psr_info[psr1]);
        CHECK_SIZE_RETURN(&sum, len, size);
        buf += len;
    }
    if (psr2 >= 0 && psr2 != psr1) {
        len = snprintf(buf, (size - sum), " %s", psr_info[psr2]);
        CHECK_SIZE_RETURN(&sum, len, size);
        buf += len;
    }
#endif

    return buf - start;
}

static int _sprint_operands_hex(char *buf, int size, MOBJ_CMD *cmd)
{
    char      *start = buf;
    HDMV_INSN *insn  = &cmd->insn;
    int len, sum = 0;

    if (insn->op_cnt > 0) {
        len = snprintf(buf, (size - sum), "0x%-4x", cmd->dst);
        CHECK_SIZE_RETURN(&sum, len, size);
        buf += len;
    }
    if (insn->op_cnt > 1) {
        len = snprintf(buf, (size - sum), ",\t0x%-4x", cmd->src);
        CHECK_SIZE_RETURN(&sum, len, size);
        buf += len;
    }

    return buf - start;
}

int mobj_sprint_cmd(char *buf, int size, MOBJ_CMD *cmd)
{
    char *start = buf;
#ifndef HI_ADVCA_FUNCTION_RELEASE
    HDMV_INSN *insn = &cmd->insn;
    int len, sum = 0;

    len = snprintf(buf, (size - sum), "%08x %08x,%08x  ", MKINT_BE32((uint8_t*)&cmd->insn), cmd->dst, cmd->src);
    CHECK_SIZE_RETURN(&sum, len, size);
    buf += len;

    switch(insn->grp) {
        case INSN_GROUP_BRANCH:
            switch(insn->sub_grp) {
                case BRANCH_GOTO:
                    if (insn_opt_goto[insn->branch_opt]) {
                        len = snprintf(buf, (size - sum), "%-10s ", insn_opt_goto[insn->branch_opt]);
                        CHECK_SIZE_RETURN(&sum, len, size);
                        buf += len;
                        len = _sprint_operands(buf, (size - sum), cmd);
                        CHECK_SIZE_RETURN(&sum, len, size);
                        buf += len;
                    } else {
                      len = snprintf(buf, (size - sum), "[unknown BRANCH/GOTO option in opcode 0x%08x] ", *(uint32_t*)insn);
                      CHECK_SIZE_RETURN(&sum, len, size);
                      buf += len;
                    }
                    break;
            case BRANCH_JUMP:
                if (insn_opt_jump[insn->branch_opt]) {
                    len = snprintf(buf, (size - sum), "%-10s ", insn_opt_jump[insn->branch_opt]);
                    CHECK_SIZE_RETURN(&sum, len, size);
                    buf += len;
                    len = _sprint_operands(buf, (size - sum), cmd);
                    CHECK_SIZE_RETURN(&sum, len, size);
                    buf += len;
                } else {
                    len = snprintf(buf, (size - sum), "[unknown BRANCH/JUMP option in opcode 0x%08x] ", *(uint32_t*)insn);
                    CHECK_SIZE_RETURN(&sum, len, size);
                    buf += len;
                }
                break;
            case BRANCH_PLAY:
                if (insn_opt_play[insn->branch_opt]) {
                    len = snprintf(buf, (size - sum), "%-10s ", insn_opt_play[insn->branch_opt]);
                    CHECK_SIZE_RETURN(&sum, len, size);
                    buf += len;
                    len = _sprint_operands(buf, (size - sum), cmd);
                    CHECK_SIZE_RETURN(&sum, len, size);
                    buf += len;
                } else {
                    len = snprintf(buf, (size - sum), "[unknown BRANCH/PLAY option in opcode 0x%08x] ", *(uint32_t*)insn);
                    CHECK_SIZE_RETURN(&sum, len, size);
                    buf += len;
                }
                break;
            default:
                len = snprintf(buf, (size - sum), "[unknown BRANCH subgroup in opcode 0x%08x] ", *(uint32_t*)insn);
                CHECK_SIZE_RETURN(&sum, len, size);
                buf += len;
                break;
            }
            break;

        case INSN_GROUP_CMP:
            if (insn_opt_cmp[insn->cmp_opt]) {
                len = snprintf(buf, (size - sum), "%-10s ", insn_opt_cmp[insn->cmp_opt]);
                CHECK_SIZE_RETURN(&sum, len, size);
                buf += len;
                len = _sprint_operands(buf, (size - sum), cmd);
                CHECK_SIZE_RETURN(&sum, len, size);
                buf += len;
            } else {
                len = snprintf(buf, (size - sum), "[unknown COMPARE option in opcode 0x%08x] ", *(uint32_t*)insn);
                CHECK_SIZE_RETURN(&sum, len, size);
                buf += len;
            }
            break;

        case INSN_GROUP_SET:
            switch (insn->sub_grp) {
                case SET_SET:
                    if (insn_opt_set[insn->set_opt]) {
                        len = snprintf(buf, (size - sum), "%-10s ", insn_opt_set[insn->set_opt]);
                        CHECK_SIZE_RETURN(&sum, len, size);
                        buf += len;
                        len = _sprint_operands(buf, (size - sum), cmd);
                        CHECK_SIZE_RETURN(&sum, len, size);
                        buf += len;
                    } else {
                        len = snprintf(buf, (size - sum), "[unknown SET option in opcode 0x%08x] ", *(uint32_t*)insn);
                        CHECK_SIZE_RETURN(&sum, len, size);
                        buf += len;
                    }
                    break;
            case SET_SETSYSTEM:
                if (insn_opt_setsys[insn->set_opt]) {
                    len = snprintf(buf, (size - sum), "%-10s ", insn_opt_setsys[insn->set_opt]);
                    CHECK_SIZE_RETURN(&sum, len, size);
                    buf += len;
                    len = _sprint_operands_hex(buf, (size - sum), cmd);
                    CHECK_SIZE_RETURN(&sum, len, size);
                    buf += len;
                } else {
                    len = snprintf(buf, (size - sum), "[unknown SETSYSTEM option in opcode 0x%08x] ", *(uint32_t*)insn);
                    CHECK_SIZE_RETURN(&sum, len, size);
                    buf += len;
                }
                break;
            default:
                len = snprintf(buf, (size - sum), "[unknown SET subgroup in opcode 0x%08x] ", *(uint32_t*)insn);
                CHECK_SIZE_RETURN(&sum, len, size);
                buf += len;
                break;
            }
            break;

        default:
            len = snprintf(buf, (size - sum), "[unknown group in opcode 0x%08x] ", *(uint32_t*)insn);
            CHECK_SIZE_RETURN(&sum, len, size);
            buf += len;
            break;
    }
#endif

    return buf - start;
}
