#include "type.h"


BOOL MakeKeyAreaFile(char *strKeyFile, int strMSID, char *strKeyAreaFile);
BOOL MakeParamAreaFile(unsigned int* pstrParams, char *strConfigFile, char *strParamAreaFile);
BOOL MakeBootAreaFile(char *strBootFile, unsigned int* pstrParams, char *strBootAreaFile, char *strUncheckedAreaFile);
BOOL MakeSignFile(char *strSrcFile, char *strKeyFile, char *strDestFile);
BOOL MakeFinalBootFile(char *strKeyAreaFile, char *strKeyAreaSigFile,
                                                                                    char *strParamAreaFile, char
                                                                                    *strParamAreaSigFile,
                                                                                    char *strBootAreaFile, char
                                                                                    *strBootAreaSigFile,
                                                                                    char *strUncheckedAreaFile,
                                                                                    char *strFinalBootFile);
