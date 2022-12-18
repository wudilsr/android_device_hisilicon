/*
 **************************************************************************************
 *       Filename:  CameraVender.h
 *    Description:  Camera Vender header file
 *
 *        Version:  1.0
 *        Created:  2012-09-24 09:11:39
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#ifndef CAMERAVENDER_H_INCLUDED
#define CAMERAVENDER_H_INCLUDED

#define CAMERA_PRODUCT_ID_BNT       0x093a2700
#define CAMERA_PRODUCT_ID_GSOU      0x0ac8c428

enum cameraVender
{
    CAMERA_VENDER_COMMON = 0x00,
    CAMERA_VENDER_BNT    = 0x01,
    CAMERA_VENDER_GSOU   = 0x02,
};

#endif /*CAMERAVENDER_H_INCLUDED*/

/********************************* END ***********************************************/
