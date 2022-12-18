cmake_minimum_required(VERSION 2.8)

PROJECT(MPEG-DASH)
#SET(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER arm-hisiv200-linux-g++)
set(CMAKE_CROSSCOMPILING true)

set(PLAYREADY_SUPPORT 1)
set(HISUB_SUPPORT 1)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb")

if(NOT FFMPEG_PATH)
    message(FATAL_ERROR "
    'FFMPEG_PATH' is not set!
    Usage:
    cmake ../ -DFFMPEG_PATH=XXX -DVER=V1R1/V1R2
    Only Relative Path is OK. Base Dir is libdash!")
else()
   #check ffmpeg include file
   set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")

   #FFMPEG_DIR: where the ffmpeg directory is
   #set(FFMPEG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..) for test!
   set(FFMPEG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${FFMPEG_PATH}/ffmpeg)

   find_package(ffmpeg REQUIRED)

   if (NOT LIBAVFORMAT_INCLUDE_DIR OR NOT LIBAVCODEC_INCLUDE_DIR)
   message(FATAL_ERROR "
   Check for ffmpeg include file failed!
   FFMPEG_PATH:'${FFMPEG_PATH}' is not correct!")
   else()
       message("-- Check for ffmpeg include file - done")
   endif()
endif()

if(NOT VER)
    message(FATAL_ERROR "
    'VER' is not set!
    Usage:
    cmake ../ -DFFMPEG_PATH=XXX -DVER=V1R1/V1R2")
else()
    if(NOT (VER MATCHES "V1R1" OR VER MATCHES "V1R2"))
    message(FATAL_ERROR "
    VER:'${VER}' is not correct!")
    endif()
endif()

#CMAKE_CURRENT_SOURCE_DIR: this is the directory where the currently processed CMakeLists.txt is located in
#see more info at: http://www.cmake.org/Wiki/CMake_Useful_Variables
set(CMAKE_INSTALL_PREFIX ${FFMPEG_DIR}/libffmpegadp)

#Copy the compile-option from SDK
add_definitions(-O2 -march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16 -fPIC)
if(HISUB_SUPPORT)
add_definitions(-DHISUB_SUPPORT)
endif()

if(PLAYREADY_SUPPORT)
add_definitions(-DPLAYREADY_SUPPORT)
endif()

include_directories(libcurl/include)
include_directories(libxml2/include)
include_directories(libdash/include)
include_directories(${FFMPEG_DIR})
include_directories(${FFMPEG_DIR}/libffmpegadp/platform/include)

if(VER MATCHES "V1R1")
include_directories(${FFMPEG_DIR}/libffmpegadp/platform/include/ver_v100r001)
endif()

if(VER MATCHES "V1R2")
include_directories(${FFMPEG_DIR}/libffmpegadp/platform/include/ver_v100r002)
endif()

if(PLAYREADY_SUPPORT)
include_directories(libplayready/include)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/zlib/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libxml2/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libcurl/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/build/lib)
if(PLAYREADY_SUPPORT)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libplayready/lib)
endif()

add_subdirectory(libdash)
add_subdirectory(libdashadp)


install(FILES libdashadp/dashadp.h
              DESTINATION platform/include
              PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE WORLD_READ GROUP_READ GROUP_WRITE)

install(FILES libcurl/lib/libcurl.so.4
              libxml2/lib/libxml2.so.2
              build/lib/libdash.so
              build/lib/libdashadp.so
              DESTINATION libadp/
              PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE WORLD_READ WORLD_EXECUTE)
