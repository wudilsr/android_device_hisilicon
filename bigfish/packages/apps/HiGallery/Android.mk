LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src)
LOCAL_JAVA_LIBRARIES :=

LOCAL_STATIC_JAVA_LIBRARIES += HiMediaPlayer
LOCAL_STATIC_JAVA_LIBRARIES += hiani
LOCAL_STATIC_JAVA_LIBRARIES += SDKInvoke

LOCAL_JNI_SHARED_LIBRARIES := libandroid_runtime

LOCAL_PACKAGE_NAME := HiGallery

ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)

LOCAL_OVERRIDES_PACKAGES := Gallery Gallery3D GalleryNew3D
LOCAL_CERTIFICATE := platform

# We mark this out until Mtp and MediaMetadataRetriever is unhidden.




LOCAL_PROGUARD_ENABLED := disabled

include $(BUILD_PACKAGE)

# Use the following include to make our test apk.
include $(call all-makefiles-under,$(LOCAL_PATH))
