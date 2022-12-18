/*
 * hi_bluray.h
 *
 *  Created on: 2013-3-30
 *      Author: z00187490
 */

#ifndef HI_BLURAY_H_
#define HI_BLURAY_H_

BD_FILE_H *file_open_udf(const char* filename, const char *mode);
BD_DIR_H *dir_open_udf(const char* dirname);

#endif /* HI_BLURAY_H_ */
