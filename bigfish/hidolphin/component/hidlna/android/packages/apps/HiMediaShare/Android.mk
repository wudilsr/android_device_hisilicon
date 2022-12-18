ifneq ($(HI_DLNA_DISABLE_DMS),y)
    LOCAL_PATH:= $(call my-dir)
    include $(CLEAR_VARS)

    LOCAL_PACKAGE_NAME := HiMediaShare
    ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)
    LOCAL_CERTIFICATE := platform

    LOCAL_SRC_FILES := $(call all-java-files-under, src)

    LOCAL_MODULE_TAGS := optional
    LOCAL_PROGUARD_ENABLED := disabled
    LOCAL_STATIC_JAVA_LIBRARIES := static-hidlna-mediashare
    LOCAL_JNI_SHARED_LIBRARIES := libvppdlna
    LOCAL_JNI_SHARED_LIBRARIES += libdmp_jni libdms_jni libdmr_jni libimagedec libupnp libixml libthreadutil
    LOCAL_32_BIT_ONLY := true
    include $(BUILD_PACKAGE)

    include $(CLEAR_VARS)
    LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES := static-hidlna-mediashare:libs/HiDLNA.jar
    LOCAL_MODULE_TAGS := optional
    include $(BUILD_MULTI_PREBUILT)
endif
