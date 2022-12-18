#ifndef __SRE_SYSCALLS_ID_H__
#define __SRE_SYSCALLS_ID_H__

#define SW_SYSCALL_CIPHER_INIT				0xc800
#define SW_SYSCALL_CIPHER_DEINIT			0xc804
#define SW_SYSCALL_CIPHER_CREATEHANDLE			0xc808
#define SW_SYSCALL_CIPHER_DESTROYHANDLE			0xc80c
#define SW_SYSCALL_CIPHER_CONFIGHANDLE			0xc810
#define SW_SYSCALL_CIPHER_GETHANDLECONFIG		0xc814
#define SW_SYSCALL_VDEC_SUSPEND		        0xc84c
#define SW_SYSCALL_VDEC_INIT		        0xc850
#define SW_SYSCALL_VDEC_RESUME              0xc854
#define SW_SYSCALL_VFMW_THREADPROC          0xc858
#define SW_SYSCALL_VDEC_CONTROL             0xc85c
#define SW_SYSCALL_VDEC_INITWITHOPERATION   0xc860
#define SW_SYSCALL_VFMW_WRITEPROC           0xc864
#define SW_SYSCALL_VFMW_READPROC            0xc868
#define SW_SYSCALL_VCTRL_SETDBGOPTION       0xc86c
#define SW_SYSCALL_VFMW_GETCHANIMAGE        0xc870
#define SW_SYSCALL_VFMW_RELEASECHANIMAGE    0xc874
#define SW_SYSCALL_VDEC_EXIT                0xc878
#define SW_SYSCALL_VDEC_INTLOCK             0xc87C
#define SW_SYSCALL_VDEC_INTUNLOCK           0xc880
#define SW_SYSCALL_CIPHER_ENCRYPT				0xc818
#define SW_SYSCALL_CIPHER_DECRYPT				0xc81c
#define SW_SYSCALL_CIPHER_ENCRYPTMULTI			0xc820
#define SW_SYSCALL_CIPHER_DECRYPTMULTI			0xc824
#define SW_SYSCALL_CIPHER_HASHINIT			0xc828
#define SW_SYSCALL_CIPHER_HASHUPDATE			0xc82c
#define SW_SYSCALL_CIPHER_HASHFINAL			0xc830
#define SW_SYSCALL_CIPHER_GETRANDOMNUMBER		0xc834
#define SW_SYSCALL_CIPHER_GETIVOUT			0xc838
#define SW_SYSCALL_CIPHER_ECNCRYPTHDCPKEY		0xc894
#define SW_SYSCALL_CIPHER_LOADHDCPKEY			0xc898
#define SW_SYSCALL_CIPHER_TEST				0xc890

#define SW_SYSCALL_MMZ_NEW                              0xc900
#define SW_SYSCALL_MMZ_DEL                              0xc901
#define SW_SYSCALL_MMZ_MALLOC                           0xc902
#define SW_SYSCALL_MMZ_FREE                             0xc903
#define SW_SYSCALL_MMZ_MAP                              0xc904
#define SW_SYSCALL_MMZ_UNMAP                            0xc905
#define SW_SYSCALL_MMZ_FLUSH                            0xc906
#define SW_SYSCALL_MEM_COPY                             0xc908

#define SW_SYSCALL_TEE_ISSECMEM                         0xc920
#define SW_SYSCALL_TEE_ISNONSECMEM                      0xc924
#define SW_SYSCALL_DEBUG                                0xc928

#define SW_SYSCALL_CC_CRYS_HMAC_INIT             0xc018
#define SW_SYSCALL_CC_CRYS_HMAC_UPDATE           0xc01c
#define SW_SYSCALL_CC_CRYS_HMAC_FINISH           0xc020
#define SW_SYSCALL_CC_CRYS_AES_INIT              0xc038
#define SW_SYSCALL_CC_CRYS_AES_BLOCK             0xc03c
#define SW_SYSCALL_CC_CRYS_AES_FINISH            0xc040
#define SW_SYSCALL_CC__DX_RSA_SCHEMES_DECRYPT                   0xc0c0
#define SW_SYSCALL_CC__DX_RSA_SCHEMES_ENCRYPT                   0xc0a0
#define SW_SYSCALL_CC__DX_RSA_SIGN                              0xc0a4
#define SW_SYSCALL_CC__DX_RSA_VERIFY                            0xc0a8
#define SW_SYSCALL_CC_CRYS_RSA_KG_GENERATEKEYPAIRCRT            0xc0b8
#define SW_SYSCALL_CC_CRYS_RSA_KG_GENERATEKEYPAIR               0xc0bc
#define SW_SYSCALL_CC_CRYS_RSA_BUILD_PUBKEY                     0xc07c
#define SW_SYSCALL_CC_CRYS_RSA_BUILD_PRIVKEY                    0xc080
#define SW_SYSCALL_CC_CRYS_RSA_BUILD_PRIVKEYCRT                 0xc084
#define SW_SYSCALL_CC_CRYS_RSA_PRIM_ENCRYPT                     0xc0ac
#define SW_SYSCALL_CC_CRYS_RSA_PRIM_DECRYPT                     0xc0b0
#define SW_SYSCALL_CC_CRYS_HASH_INIT                            0xc004
#define SW_SYSCALL_CC_CRYS_DES_FREE                             0xc0b4
#define SW_SYSCALL_CC_CRYS_RND_GENERATEVECTOR                   0xc068
#endif
