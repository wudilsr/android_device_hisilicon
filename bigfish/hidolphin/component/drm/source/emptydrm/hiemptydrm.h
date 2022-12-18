#ifndef __HI_EMPTYDRM_H__
#define __HI_EMPTYDRM_H__

#include <media/drm/DrmAPI.h>
#include <media/hardware/CryptoAPI.h>
#include <media/stagefright/foundation/ABase.h>



namespace android {

/************************ factory ***************************/

/**media drm plugin*/
class HiEmptyDrmFactory : public DrmFactory {
public:
    HiEmptyDrmFactory() {}

    virtual bool isCryptoSchemeSupported(const uint8_t uuid[16]);
    virtual bool isContentTypeSupported(const String8& contentType);
    virtual status_t createDrmPlugin(const uint8_t uuid[16],
                                     DrmPlugin** plugin);

private:
    DISALLOW_EVIL_CONSTRUCTORS(HiEmptyDrmFactory);
};


/** media crypto plugin factory***/
class HiEmptyDrmCryptoFactory : public CryptoFactory {
public:
    HiEmptyDrmCryptoFactory() {}

    virtual bool isCryptoSchemeSupported(const uint8_t uuid[16]) const;
    virtual status_t createPlugin(const uint8_t uuid[16],
                                  const void* data, size_t size,
                                  CryptoPlugin** plugin);

private:
    DISALLOW_EVIL_CONSTRUCTORS(HiEmptyDrmCryptoFactory);
};


/*********************plugin***************************/
struct HiEmptyDrmCryptoPlugin : public CryptoPlugin {
public:
    HiEmptyDrmCryptoPlugin(){}

    virtual bool requiresSecureDecoderComponent(const char *mime) const;
    virtual ssize_t decrypt(bool secure,
                            const uint8_t key[16], const uint8_t iv[16],
                            Mode mode,
                            const void *srcPtr,
                            const SubSample *subSamples, size_t numSubSamples,
                            void *dstPtr,
                            AString *errorDetailMsg);

private:

    DISALLOW_EVIL_CONSTRUCTORS(HiEmptyDrmCryptoPlugin);
};



class HiEmptyDrmPlugin : public DrmPlugin {
public:
   HiEmptyDrmPlugin(){}

    virtual status_t openSession(Vector<uint8_t>& sessionId);
    virtual status_t closeSession(const Vector<uint8_t>& sessionId);
    virtual status_t getKeyRequest(const Vector<uint8_t>& scope,
                                   const Vector<uint8_t>& initData,
                                   const String8& mimeType,
                                   KeyType keyType,
                                   const KeyedVector<String8, String8>&
                                           optionalParameters,
                                   Vector<uint8_t>& request,
                                   String8& defaultUrl);
    virtual status_t provideKeyResponse(const Vector<uint8_t>& scope,
                                        const Vector<uint8_t>& response,
                                        Vector<uint8_t>& keySetId);
    virtual status_t removeKeys(const Vector<uint8_t>& sessionId);
    virtual status_t restoreKeys(const Vector<uint8_t>& sessionId,
                                 const Vector<uint8_t>& keySetId);
    virtual status_t queryKeyStatus(const Vector<uint8_t>& sessionId,
                                    KeyedVector<String8, String8>& infoMap)
            const;
    #if defined(ANDROID_5_X)
    virtual status_t getProvisionRequest(const String8& certType,
                                         const String8& certAuthority,
                                         Vector<uint8_t>& request,
                                         String8& defaultUrl);
    virtual status_t provideProvisionResponse(const Vector<uint8_t>& response,
                                              Vector<uint8_t>& certificate,
                                              Vector<uint8_t>& wrappedKey);
    virtual status_t unprovisionDevice();
    virtual status_t getSecureStop(Vector<uint8_t> const &ssid, Vector<uint8_t> &secureStop);
    virtual status_t releaseAllSecureStops();
    /*just implement the interface in android 4.4*/
    #else
    virtual status_t getProvisionRequest(Vector<uint8_t> &request,
                                         String8 &defaultUrl);
    // After a provision response is received by the app, it is provided to the
    // Drm plugin using provideProvisionResponse.
    virtual status_t provideProvisionResponse(Vector<uint8_t> const &response);
            /*implenment all tha virtual interfaces of class DrmPlugin in android 5.0*/
    #endif
    virtual status_t getSecureStops(List<Vector<uint8_t> >& secureStops);
    virtual status_t releaseSecureStops(const Vector<uint8_t>& ssRelease);
    virtual status_t getPropertyString(const String8& name,
                                       String8& value) const;
    virtual status_t getPropertyByteArray(const String8& name,
                                          Vector<uint8_t>& value) const;
    virtual status_t setPropertyString(const String8& name,
                                       const String8& value);
    virtual status_t setPropertyByteArray(const String8& name,
                                          const Vector<uint8_t>& value);
    virtual status_t setCipherAlgorithm(const Vector<uint8_t>& sessionId,
                                        const String8& algorithm);
    virtual status_t setMacAlgorithm(const Vector<uint8_t>& sessionId,
                                     const String8& algorithm);
    virtual status_t encrypt(const Vector<uint8_t>& sessionId,
                             const Vector<uint8_t>& keyId,
                             const Vector<uint8_t>& input,
                             const Vector<uint8_t>& iv,
                             Vector<uint8_t>& output);
    virtual status_t decrypt(const Vector<uint8_t>& sessionId,
                             const Vector<uint8_t>& keyId,
                             const Vector<uint8_t>& input,
                             const Vector<uint8_t>& iv,
                             Vector<uint8_t>& output);
    virtual status_t sign(const Vector<uint8_t>& sessionId,
                          const Vector<uint8_t>& keyId,
                          const Vector<uint8_t>& message,
                          Vector<uint8_t>& signature);
    virtual status_t verify(const Vector<uint8_t>& sessionId,
                            const Vector<uint8_t>& keyId,
                            const Vector<uint8_t>& message,
                            const Vector<uint8_t>& signature,
                            bool& match);
    virtual status_t signRSA(Vector<uint8_t> const &sessionId,
                             String8 const &algorithm,
                             Vector<uint8_t> const &message,
                             Vector<uint8_t> const &wrappedKey,
                             Vector<uint8_t> &signature);

private:
    void removeAllLicenses(const String8& sessionId);


    DISALLOW_EVIL_CONSTRUCTORS(HiEmptyDrmPlugin);
};




} // namespace android

extern "C" {

android::DrmFactory* createDrmFactory();
android::CryptoFactory* createCryptoFactory();
android::DrmFactory* createDrmFactory();

} // extern "C"


#endif
