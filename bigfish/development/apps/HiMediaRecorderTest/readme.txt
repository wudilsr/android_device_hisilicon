HiMediaRecorderTest.app

Steps:
1) Confirm HIMEDIARECORDER_ENABLE= true in "frameworks/av/media/libmediaplayerservice/Android.mk", otherwise change it first, then make libmediaplayerservice.so and put it to /system/lib, then reboot.
2) working dir is /sdcard/
3) put source videofile(mp4/wmv/ts/etc.) in /sdcard/ and make sure the fileext is mp4
4) playback sourcefile and start record
5) you can seek source file while recording
6) stop record
7) playback and review the recorded ts file

