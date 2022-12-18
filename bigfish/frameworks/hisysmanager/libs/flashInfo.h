#ifndef FLASHINFO_H_
#define FLASHINFO_H_

#ifdef __cplusplus
extern "C" {
#endif

	extern int get_flash_info_all(const char *mtdname);
	extern int set_flash_info_all(const char *mtdname, const char *mtdinfo);
	extern int set_flash_info(const char *mtdname, unsigned long offset, unsigned int offlen, const char *mtdinfo);
	extern int get_flash_info(const char *mtdname, unsigned long offset, unsigned int offlen);

    extern int set_HDCP2x_Key(const char *mtdname, unsigned long offset, char *pBuffer, unsigned long uBufferSize);
    extern int get_HDCP2x_Key(const char *mtdname, unsigned long offset, char *pBuffer, unsigned long offlen);

    extern int set_DRM_Key(const char *mtdname, unsigned long offset, char *pBuffer, unsigned long uBufferSize);
    extern int get_DRM_Key(const char *mtdname, unsigned long offset, char *pBuffer, unsigned long offlen);

#ifdef __cplusplus
}
#endif

#endif