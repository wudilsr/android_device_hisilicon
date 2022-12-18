/*
 * This file is part of libbluray
 * Copyright (C) 2009-2010  John Stebbins
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

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "libbluray/bluray.h"
#include "libbluray/bdnav/clpi_data.h"
#include "util/macro.h"
#include "util/strutl.h"
#include "util.h"

#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <inttypes.h>

#define PKT_SIZE 192
#define BUF_SIZE (PKT_SIZE * 1024)
#define MIN(a,b) (((a) < (b)) ? a : b)
#define LOGD(fmt, args...) \
        printf("DEBUG [%s,%d]"#fmt"\n", __FILE__, __LINE__, ##args)

static int verbose = 1;

static void
_usage(char *cmd)
{
    fprintf(stderr,
"Usage: %s -t title    [-c first[-last]] [-k keyfile] [-a angle]  <bd path> [dest]\n"
"       %s -p playlist [-c first[-last]] [-k keyfile] [-a angle]  <bd path> [dest]\n"
"Summary:\n"
"    Given a title or playlist number and Blu-Ray directory tree,\n"
"    find the clips that compose the movie and splice\n"
"    them together in the destination file\n"
"Options:\n"
"    t N         - Index of title to splice. First title is 1.\n"
"    p N         - Playlist to splice.\n"
"    a N         - Angle. First angle is 1.\n"
"    c N or N-M  - Chapter or chapter range. First chapter is 1.\n"
"    k keyfile   - AACS keyfile path.\n"
"    <bd path>   - Path to root of Blu-Ray directory tree.\n"
"    [dest]      - Destination of spliced clips. stdout if not specified.\n"
, cmd, cmd);

    exit(EXIT_FAILURE);
}

#define OPTS "c:vt:p:k:a:"


static void blurayHandleEvent(const BD_EVENT *e )
{
    LOGD("event:%d", e->event);
    switch (e->event)
    {
        case BD_EVENT_TITLE:

            break;
        case BD_EVENT_PLAYITEM:
            break;
        case BD_EVENT_AUDIO_STREAM:
            break;
        case BD_EVENT_CHAPTER:
            break;
        case BD_EVENT_ANGLE:
        case BD_EVENT_IG_STREAM:
        default:
            break;
    }
}

static void blurayHandleEvents(BLURAY *bluray)
{
    BD_EVENT e;

    while (bd_get_event(bluray, &e))
    {
        blurayHandleEvent(&e);
    }
}


static void
_show_clip_info(CLPI_CLIP_INFO *ci, int level)
{
    int ii;

    indent_printf(level, "Clip Info");
    indent_printf(level+1, "Clip Stream Type: %02x", ci->clip_stream_type);
    indent_printf(level+1, "Clip Application Type: %02x",
                ci->application_type);
    indent_printf(level+1, "is_ATC_delta: %s", ci->is_atc_delta ? "True" : "False");
    indent_printf(level+1, "ATC delta count: %d", ci->atc_delta_count);
    indent_printf(level+1, "TS Recording Rate: %u", ci->ts_recording_rate);
    indent_printf(level+1, "Number Source Packets: %u", ci->num_source_packets);
    // Show ts type info
    indent_printf(level+1, "TS Type Info");
    indent_printf(level+2, "Validity Flags %02x", ci->ts_type_info.validity);
    indent_printf(level+2, "Format Id %s", ci->ts_type_info.format_id);
    // Show cc5 thing
    for (ii = 0; ii < ci->atc_delta_count; ii++) {
        indent_printf(level+1, "ATC delta[ %d ]", ii);
        indent_printf(level+2, "Delta %08x", ci->atc_delta[ii].delta);
        indent_printf(level+2, "File Id %s", ci->atc_delta[ii].file_id);
        indent_printf(level+2, "File Code %s", ci->atc_delta[ii].file_code);
    }
    printf("\n");
}

static void
_show_seq_info(CLPI_SEQ_INFO *si, int level)
{
    CLPI_ATC_SEQ *atc;
    CLPI_STC_SEQ *stc;
    int ii, jj;

    indent_printf(level, "Sequence Info");
    indent_printf(level+1, "Number ATC Sequences: %d", si->num_atc_seq);
    for (ii = 0; ii < si->num_atc_seq; ii++) {
        atc = &si->atc_seq[ii];
        indent_printf(level+1, "ATC Sequence %d", ii);
        indent_printf(level+2, "SPN ATC Start: %u", atc->spn_atc_start);
        indent_printf(level+2, "Offset STC Id: %d", atc->offset_stc_id);
        indent_printf(level+2, "Number STC Sequences: %d", atc->num_stc_seq);
        for (jj = 0; jj < atc->num_stc_seq; jj++) {
            stc = &atc->stc_seq[jj];
            indent_printf(level+2, "ATC Sequence %d", jj);
            indent_printf(level+3, "SPN STC Start: %u", stc->spn_stc_start);
            indent_printf(level+3, "PCR PID: %04x", stc->pcr_pid);
            indent_printf(level+3, "Presentation Start: %u",
                            stc->presentation_start_time);
            indent_printf(level+3, "Presentation End: %u",
                            stc->presentation_end_time);
        }
    }
}

static void
_show_prog_info(CLPI_PROG_INFO *pi, int level)
{
    CLPI_PROG *prog;
    int ii, jj;

    indent_printf(level, "Program Info");
    indent_printf(level+1, "Number Programs: %d", pi->num_prog);
    for (ii = 0; ii < pi->num_prog; ii++) {
        prog = &pi->progs[ii];
        indent_printf(level+1, "Program %d", ii);
        indent_printf(level+2, "SPN Program Sequence Start: %d",
                        prog->spn_program_sequence_start);
        indent_printf(level+2, "Program Map PID: %d", prog->program_map_pid);
        indent_printf(level+2, "Number Streams: %d", prog->num_streams);
        indent_printf(level+2, "Number Groups: %d", prog->num_groups);
        for (jj = 0; jj < prog->num_streams; jj++) {
            indent_printf(level+2, "Stream %d", jj);
//            _show_stream(&prog->streams[jj], level+3);
        }
    }
}

static void
_show_extent_start(CLPI_EXTENT_START *es, int level)
{
    unsigned int ii;

    indent_printf(level, "Extension data: Extent Start Point");

    if (!es->num_point) {
        indent_printf(level+1, "(no data)");

    } else {
        indent_printf(level+1, "Number of Start Points: %d", es->num_point);

        if (verbose) {
            for (ii = 0; ii < es->num_point; ii++) {
                indent_printf(level+1, "Extent %5d: SPN 0x%08X", ii, es->point[ii]);
            }
        }
    }
}

static void
_show_cpi_info(CLPI_CPI *cpi, int level)
{
    CLPI_EP_MAP_ENTRY *entry;
    CLPI_EP_COARSE *coarse;
    CLPI_EP_FINE *fine;
    int ii, jj, kk;

    indent_printf(level, "CPI");
    indent_printf(level+1, "Number Stream PID: %d", cpi->num_stream_pid);
    for (ii = 0; ii < cpi->num_stream_pid; ii++) {
        entry = &cpi->entry[ii];
        indent_printf(level+1, "Stream: %d", ii);
        indent_printf(level+2, "PID: %04x", entry->pid);
        indent_printf(level+2, "EP Stream Type: %d", entry->ep_stream_type);
        indent_printf(level+2, "Number EP Coarse: %d", entry->num_ep_coarse);
        indent_printf(level+2, "Number EP Fine: %d", entry->num_ep_fine);
        indent_printf(level+2, "EP Map Start: %d",
                        entry->ep_map_stream_start_addr);
        for (jj = 0; jj < entry->num_ep_coarse; jj++) {
            coarse = &entry->coarse[jj];
            indent_printf(level+2, "Coarse: %d", jj);
            indent_printf(level+3, "Ref EP Fine: %d", coarse->ref_ep_fine_id);
            indent_printf(level+3, "PTS EP: %d", coarse->pts_ep);
            indent_printf(level+3, "SPN EP: %d", coarse->spn_ep);
        }
        for (jj = 0; jj < entry->num_ep_fine; jj++) {
            fine = &entry->fine[jj];
            indent_printf(level+2, "Fine: %d", jj);
            indent_printf(level+3, "Angle Change Point: %s",
                fine->is_angle_change_point ? "True":"False");
            indent_printf(level+3, "I End Offset: %d",
                fine->i_end_position_offset);
            indent_printf(level+3, "PTS EP: %d", fine->pts_ep);
            indent_printf(level+3, "SPN EP: %d", fine->spn_ep);
        }
        if (verbose) {
            uint64_t pts;
            uint32_t spn;

            indent_printf(level+2, "PTS - SPN Map");
            for (jj = 0; jj < entry->num_ep_coarse; jj++) {
                int start, end;

                indent_printf(level+3, "Coarse: %d", jj);
                coarse = &entry->coarse[jj];
                start = coarse->ref_ep_fine_id;
                if (jj < entry->num_ep_coarse - 1) {
                    end = entry->coarse[jj+1].ref_ep_fine_id;
                } else {
                    end = entry->num_ep_fine;
                }
                for (kk = start; kk < end; kk++) {
                    fine = &entry->fine[kk];
                    pts = ((uint64_t) (coarse->pts_ep & ~0x01) << 19) +
                            ((uint64_t)fine->pts_ep << 9);
                    spn = (coarse->spn_ep & ~0x1FFFF) + fine->spn_ep;
                    indent_printf(level+4, "PTS %8"PRIu64"/%8"PRIu64" -- SPN %u",
                        pts, pts >> 1, spn);
                }
            }
        }
    }
}


static void dump_title_info(BLURAY *bd, BLURAY_TITLE_INFO *ti)
{
    int i;
    for (i = 0; i < ti->clip_count; i++)
    {
        printf(
       "index: %d duration: %02"PRIu64":%02"PRIu64":%02"PRIu64" chapters: %3d angles: %2u clips: %3u (playlist: %05d.mpls) "
       "V:%d A:%-2d PG:%-2d IG:%-2d SV:%d SA:%d\n",
              1,
              (ti->duration / 90000) / (3600),
              ((ti->duration / 90000) % 3600) / 60,
              ((ti->duration / 90000) % 60),
              ti->chapter_count, ti->angle_count, ti->clip_count, ti->playlist,
              ti->clips[i].video_stream_count,
              ti->clips[i].audio_stream_count,
              ti->clips[i].pg_stream_count,
              ti->clips[i].ig_stream_count,
              ti->clips[i].sec_video_stream_count,
              ti->clips[i].sec_audio_stream_count

        );
        CLPI_CL* cl = bd_get_clpi(bd, i);
        if (cl)
        {
            printf("id1:%d, id2:%d\n", cl->type_indicator, cl->type_indicator2);
            _show_clip_info(&cl->clip, 1);
            _show_seq_info(&cl->sequence, 1);
            _show_prog_info(&cl->program, 1);
            _show_cpi_info(&cl->cpi, 1);
            if (cl->program_ss.num_prog) {
                printf("\n");
                indent_printf(1, "Extension: Program Info SS");
                _show_prog_info(&cl->program_ss, 1);
            }
            if (cl->program_ss.num_prog) {
                printf("\n");
                indent_printf(1, "Extension: CPI SS");
                _show_cpi_info(&cl->cpi_ss, 1);
            }
            if (cl->extent_start.num_point > 0) {
                _show_extent_start(&cl->extent_start, 1);
            }
            bd_free_clpi(cl);
        }
    }
    for (i = 0; i < ti->mark_count; i++)
    {
        printf("Mark idx:%d, type:%d, clip_ref:%d\n",
            ti->marks[i].idx, ti->marks[i].type, ti->marks[i].clip_ref);
    }
}

int
main(int argc, char *argv[])
{
    int title_no = -1;
    int playlist = -1;
    int angle = 0;
    char *bdpath = NULL, *dest = NULL;
    FILE *out;
    int opt;
    int verbose = 0;
    int64_t total = 0;
    int64_t pos, end_pos = -1;
    size_t size, wrote;
    int bytes;
    int title_count;
    BLURAY *bd;
    int chapter_start = 0;
    int chapter_end = -1;
    uint8_t buf[BUF_SIZE];
    char *keyfile = NULL;
    BLURAY_TITLE_INFO *ti;

    do {
        opt = getopt(argc, argv, OPTS);
        switch (opt) {
            case -1:
                if (optind < argc && bdpath == NULL) {
                    bdpath = argv[optind];
                    optind++;
                    opt = 1;
                }
                else if (optind < argc && dest == NULL) {
                    dest = argv[optind];
                    optind++;
                    opt = 1;
                }
                break;

            case 'c': {
                int match;
                match = sscanf(optarg, "%d-%d", &chapter_start, &chapter_end);
                if (match == 1) {
                    chapter_end = chapter_start + 1;
                }
                chapter_start--;
                chapter_end--;
            } break;

            case 'k':
                keyfile = optarg;
                break;

            case 'a':
                angle = atoi(optarg);
                angle--;
                break;

            case 't':
                if (playlist >= 0) {
                    _usage(argv[0]);
                }
                title_no = atoi(optarg);
                title_no--;
                break;

            case 'p':
                if (title_no >= 0) {
                    _usage(argv[0]);
                }
                playlist = atoi(optarg);
                break;

            case 'v':
                verbose = 1;
                break;

            default:
                _usage(argv[0]);
                break;
        }
    } while (opt != -1);

    if (title_no < 0 && playlist < 0) {
        _usage(argv[0]);
    }
    if (optind < argc) {
        _usage(argv[0]);
    }

    bd = bd_open(bdpath, keyfile);
    if (bd == NULL) {
        fprintf(stderr, "Failed to open disc: %s\n", bdpath);
        return 1;
    }

    title_count = bd_get_titles(bd, TITLES_RELEVANT, 0);
    if (title_count <= 0) {
        fprintf(stderr, "No titles found: %s\n", bdpath);
        return 1;
    }

    if (title_no >= 0) {
        if (!bd_select_title(bd, title_no)) {
            fprintf(stderr, "Failed to open title: %d\n", title_no);
            return 1;
        }
        ti = bd_get_title_info(bd, title_no, angle);

    } else {
        if (!bd_select_playlist(bd, playlist)) {
            fprintf(stderr, "Failed to open playlist: %d\n", playlist);
            return 1;
        }
        ti = bd_get_playlist_info(bd, playlist, angle);
    }

    if (dest) {
        out = fopen(dest, "wb");
        if (out == NULL) {
            fprintf(stderr, "Failed to open destination: %s\n", dest);
            return 1;
        }
    } else {
        out = stdout;
    }

    if (angle >= (int)ti->angle_count) {
        fprintf(stderr, "Invalid angle %d > angle count %d. Using angle 1.\n",
                angle+1, ti->angle_count);
        angle = 0;
    }
    bd_select_angle(bd, angle);

    if (chapter_start >= (int)ti->chapter_count) {
        fprintf(stderr, "First chapter %d > chapter count %d\n",
                chapter_start+1, ti->chapter_count);
        return 1;
    }
    if (chapter_end >= (int)ti->chapter_count) {
        chapter_end = -1;
    }
    if (chapter_end >= 0) {
        end_pos = bd_chapter_pos(bd, chapter_end);
    }

    dump_title_info(bd, ti);

    bd_free_title_info(ti);

    bd_seek_chapter(bd, chapter_start);
    pos = bd_tell(bd);
    blurayHandleEvents(bd);
    while (end_pos < 0 || pos < end_pos) {
        size = BUF_SIZE;
        if (size > (size_t)(end_pos - pos)) {
            size = end_pos - pos;
        }
        bytes = bd_read(bd, buf, size);
        blurayHandleEvents(bd);
        if (bytes <= 0) {
            break;
        }
        pos = bd_tell(bd);
        wrote = fwrite(buf, 1, bytes, out);
        if (wrote != (size_t)bytes) {
            fprintf(stderr, "read/write sizes do not match: %d/%zu\n", bytes, wrote);
        }
        if (wrote == 0) {
            if (ferror(out)) {
                perror("Write error");
            }
            break;
        }
        total += PKT_SIZE * wrote;
    }
    if (verbose) {
        fprintf(stderr, "Wrote %"PRId64" bytes\n", total);
    }
    bd_close(bd);
    fclose(out);
    return 0;
}
