message("-- Check for ffmpeg include file ...")

find_path(
    LIBAVFORMAT_INCLUDE_DIR
    avformat.h
    ${FFMPEG_DIR}/libavformat/
)

find_path(
    LIBAVCODEC_INCLUDE_DIR
    avcodec.h
    ${FFMPEG_DIR}/libavcodec/
)

#Put other head file checking here!
