#define LOG_NDEBUG 0

#define LOG_TAG "EMPTYDRM"
#include <utils/Log.h>


#include <utils/Errors.h>
#include "hiemptydrm.h"
#include "emptycpy.h"

#include <media/stagefright/MediaErrors.h>
#include <media/stagefright/foundation/ABuffer.h>
#include <media/stagefright/foundation/base64.h>

#include <sys/endian.h>

namespace android {

bool isEmptyUuid(const uint8_t uuid[16]) {
    static const uint8_t kEmptyUUID[16] = {
            0x9a, 0x04, 0xF0, 0x79, 0x98, 0x40, 0x42, 0x86,
            0xAB, 0x92, 0xE6, 0x5B, 0xE0,  0x11, 0x11, 0x11
    };
    return !memcmp(uuid, kEmptyUUID, 16);
}

/**************************media drm factory ***********************/
bool HiEmptyDrmFactory::isCryptoSchemeSupported(const uint8_t uuid[16]) {
    ALOGV("%s >>", __FUNCTION__);
    return isEmptyUuid(uuid);
}

bool HiEmptyDrmFactory::isContentTypeSupported(const String8& contentType) {
    ALOGV("%s >> mimeType = %s", __FUNCTION__, contentType.string());
    // TODO(OEM): set return value properly, depending on platform support.
    // To achieve level-1 security, video mim type should return true.
    return true;
}

status_t HiEmptyDrmFactory::createDrmPlugin(const uint8_t uuid[16],
                                              DrmPlugin** plugin) {
    if (!isCryptoSchemeSupported(uuid)) {
        *plugin = NULL;
        return BAD_VALUE;
    }

    ALOGV("%s >>", __FUNCTION__);
    *plugin = new HiEmptyDrmPlugin();
    return OK;
}


}

android::DrmFactory* createDrmFactory() {
    ALOGV("%s >>", __FUNCTION__);
    return new android::HiEmptyDrmFactory();
}

/**************************end media drm factory ***********************/


/**************************media crypto factory ***********************/
namespace android {

bool HiEmptyDrmCryptoFactory::isCryptoSchemeSupported(const uint8_t uuid[16]) const {
    bool isSupported = isEmptyUuid(uuid);
    ALOGV("%s >> isSupported = %s", __FUNCTION__, isSupported ? "true" : "false");
    return isSupported;
}

status_t HiEmptyDrmCryptoFactory::createPlugin(const uint8_t uuid[16],
                                              const void* data,
                                              size_t size,
                                              CryptoPlugin** plugin) {
    *plugin = new HiEmptyDrmCryptoPlugin();
    return OK;
}

} // namespace android

/***************************external c****************************/
android::CryptoFactory* createCryptoFactory() {
    ALOGV("%s >>", __FUNCTION__);
    return new android::HiEmptyDrmCryptoFactory();
}

/**************************end media crypto factory ***********************/

/**************************media crypto ***********************/
namespace android {

bool HiEmptyDrmCryptoPlugin::requiresSecureDecoderComponent(const char *mime) const {
    // TODO(OEM): return true here for video mime type,
    // which should go through trusted video path, calling decrypt() with
    // "true" for secure argument.
    // return !strncasecmp(mime, "video/", 6);
    ALOGI("%s >> mime = %s", __FUNCTION__, mime);
    return true;
}

ssize_t HiEmptyDrmCryptoPlugin::decrypt(bool secure,
                                       const uint8_t key[16],
                                       const uint8_t iv[16],
                                       Mode mode,
                                       const void* srcPtr,
                                       const SubSample* subSamples,
                                       size_t numSubSamples,
                                       void* dstPtr,
                                       AString* errorDetailMsg) {


size_t destSize = 0;
bool haveEncryptedSubsamples = false;
const uint8_t* const source = static_cast<const uint8_t*>(srcPtr);
uint8_t* const dest = static_cast<uint8_t*>(dstPtr);

for (size_t i = 0; i < numSubSamples; i++) {
  const SubSample &subSample = subSamples[i];
  destSize += subSample.mNumBytesOfClearData;
  destSize += subSample.mNumBytesOfEncryptedData;
  if (subSample.mNumBytesOfEncryptedData > 0) {
    haveEncryptedSubsamples = true;
  }
}
size_t offset = 0;
emptyca2ta(source,(unsigned long)(dest),destSize);

return destSize;
}




}    // namespace android


/*************************   media drm ************************/
namespace android {



status_t HiEmptyDrmPlugin::openSession(Vector<uint8_t>& sessionId) {
    String8 sessionName = String8("HiEmptyDrm");
    int ret;
    sessionId.clear();
    sessionId.appendArray(reinterpret_cast<const uint8_t*>(sessionName.string()),
                          sessionName.size());
    ALOGV("%s << sessionID = %.*s", __FUNCTION__, sessionName.size(),
          sessionName.string());
    ret = initMMZBuffer();
    return ret;
}



status_t HiEmptyDrmPlugin::closeSession(const Vector<uint8_t>& sessionId) {
    ALOGV("%s >>", __FUNCTION__);
    int ret = deinitMMZBuffer();
    return ret;
}

void HiEmptyDrmPlugin::removeAllLicenses(const String8& sessionId) {
    return;
}

status_t HiEmptyDrmPlugin::getKeyRequest(const Vector<uint8_t>& scope,
                                           const Vector<uint8_t>& initData,
                                           const String8& mimeType,
                                           KeyType keyType,
                                           const KeyedVector<String8, String8>&
                                                   optionalParameters,
                                           Vector<uint8_t>& request,
                                           String8& defaultUrl) {
    ALOGV("%s >>", __FUNCTION__);
    return OK;
}

status_t HiEmptyDrmPlugin::provideKeyResponse(const Vector<uint8_t>& scope,
                                                const Vector<uint8_t>& response,
                                                Vector<uint8_t>& keySetId) {
    ALOGV("%s >>", __FUNCTION__);
    return OK;
}

status_t HiEmptyDrmPlugin::removeKeys(const Vector<uint8_t>& sessionId) {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}

status_t HiEmptyDrmPlugin::restoreKeys(const Vector<uint8_t>& sessionId,
                                         const Vector<uint8_t>& keySetId) {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}

status_t HiEmptyDrmPlugin::queryKeyStatus(
        const Vector<uint8_t>& sessionId,
        KeyedVector<String8, String8>& infoMap) const {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}
#if defined(ANDROID_5_X)
/*android5.x interface*/
status_t HiEmptyDrmPlugin::getProvisionRequest(const String8& certType,
                                                 const String8& certAuthority,
                                                 Vector<uint8_t>& request,
                                                 String8& defaultUrl) {
    // that credential should be reset.
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}

status_t HiEmptyDrmPlugin::provideProvisionResponse(
        const Vector<uint8_t>& response,
        Vector<uint8_t>& certificate,
        Vector<uint8_t>& wrappedKey) {
    // that credential should be reset.
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}

status_t HiEmptyDrmPlugin::unprovisionDevice() {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}
status_t HiEmptyDrmPlugin::getSecureStop(Vector<uint8_t> const &ssid, Vector<uint8_t> &secureStop){
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}
status_t HiEmptyDrmPlugin::releaseAllSecureStops(){
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}
#else
/*android4.4 interface*/
status_t HiEmptyDrmPlugin::getProvisionRequest(Vector<uint8_t> &request,
                                     String8 &defaultUrl){
    // that credential should be reset.
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}
status_t HiEmptyDrmPlugin::provideProvisionResponse(Vector<uint8_t> const &response){

    // that credential should be reset.
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}
#endif
status_t HiEmptyDrmPlugin::getSecureStops(
        List<Vector<uint8_t> >& secureStops) {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}

status_t HiEmptyDrmPlugin::releaseSecureStops(
        const Vector<uint8_t>& ssRelease) {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}

status_t HiEmptyDrmPlugin::getPropertyString(const String8& name,
                                               String8& value) const {
    status_t status = OK;
    if (name == String8("securityLevel")) {
        // TODO(OEM): return proper security level of DRM in terms WV
        // security level.
        // With "L3", CryptoPlugin::decrypt() will be called with |secure| set to false, which
        // means decrypt() can return decrypted clear stream. With "L1", decrypt() will be called
        // with |secure| set to true, which means decrypt() cannot return clear stream.
        value = "L1";
        ALOGW("%s(%s) returned %s, just not to hinder chrome's drm operation",
              __FUNCTION__, name.string(), value.string());
    } else {
        ALOGE("%s is NOT implemented.", __FUNCTION__);
        status = ERROR_DRM_CANNOT_HANDLE;
    }
    return status;
}

status_t HiEmptyDrmPlugin::getPropertyByteArray(
        const String8& name,
        Vector<uint8_t>& value) const {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}

status_t HiEmptyDrmPlugin::setPropertyString(const String8& name,
                                               const String8& value) {
    ALOGI("%s(%s, %s) was called.", __FUNCTION__,
          name.string(), value.string());
    ALOGW("Property setting was ignored");
    return OK;
}

status_t HiEmptyDrmPlugin::setPropertyByteArray(
        const String8& name,
        const Vector<uint8_t>& value) {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}

status_t HiEmptyDrmPlugin::setCipherAlgorithm(
        const Vector<uint8_t>& sessionId,
        const String8& algorithm) {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}

status_t HiEmptyDrmPlugin::setMacAlgorithm(const Vector<uint8_t>& sessionId,
                                             const String8& algorithm) {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}

status_t HiEmptyDrmPlugin::encrypt(const Vector<uint8_t>& sessionId,
                                     const Vector<uint8_t>& keyId,
                                     const Vector<uint8_t>& input,
                                     const Vector<uint8_t>& iv,
                                     Vector<uint8_t>& output) {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}

status_t HiEmptyDrmPlugin::decrypt(const Vector<uint8_t>& sessionId,
                                     const Vector<uint8_t>& keyId,
                                     const Vector<uint8_t>& input,
                                     const Vector<uint8_t>& iv,
                                     Vector<uint8_t>& output) {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}

status_t HiEmptyDrmPlugin::sign(const Vector<uint8_t>& sessionId,
                                  const Vector<uint8_t>& keyId,
                                  const Vector<uint8_t>& message,
                                  Vector<uint8_t>& signature) {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}

status_t HiEmptyDrmPlugin::verify(const Vector<uint8_t>& sessionId,
                                    const Vector<uint8_t>& keyId,
                                    const Vector<uint8_t>& message,
                                    const Vector<uint8_t>& signature,
                                    bool& match) {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}

status_t HiEmptyDrmPlugin::signRSA(const Vector<uint8_t>& sessionId,
                                     const String8& algorithm,
                                     const Vector<uint8_t>& message,
                                     const Vector<uint8_t>& wrappedKey,
                                     Vector<uint8_t>& signature) {
    ALOGE("%s is NOT implemented.", __FUNCTION__);
    return ERROR_DRM_CANNOT_HANDLE;
}




}    // namespace android




