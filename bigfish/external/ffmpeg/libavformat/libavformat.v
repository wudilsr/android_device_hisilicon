LIBAVFORMAT_$MAJOR {
        global: av*;
                ff_*;
                ffurl_*;
                ff_blurayplay_demuxer;
                ff_dash_demuxer;
                ff_ttml_demuxer;
                #FIXME those are for ffserver
                ff_inet_aton;
                ff_socket_nonblock;
                ffm_set_write_index;
                ffm_read_write_index;
                ffm_write_write_index;
                ff_rtsp_parse_line;
                ff_rtmp_receiveAudio;
                ff_rtmp_receiveVideo;
                ff_rtp_get_local_rtp_port;
                ff_rtp_get_local_rtcp_port;
                ffio_open_dyn_packet_buf;
                ffurl_close;
                ffurl_open;
                ffurl_write;
                ffurl_seek;
                ffurl_read_complete;
                ffurl_get_seekable;
                ffurl_get_file_handle;
                ffurl_size;
                ff_url_join;
                url_open;
                url_close;
                url_write;
                url_get_max_packet_size;
                #those are deprecated, remove on next bump
                find_info_tag;
                parse_date;
                dump_format;
                url_*;
                ff_timefilter_destroy;
                ff_timefilter_new;
                ff_timefilter_update;
                ff_timefilter_reset;
                get_*;
                put_*;
                udp_set_remote_url;
                udp_get_local_port;
                init_checksum;
                init_put_byte;
                g_adapt_protocol;
                ff_read_frame_flush;
                ffurl_register_protocol;
                ffurl_unregister_protocol;
                ff_mov_get_sidx_data;
                ff_mov_get_pssh;
                ff_mov_get_tenc;
                ff_index_search_timestamp;
                ff_add_index_entry;
                ff_dash_interrupt;
        local: *;
};
