#ifndef RECOVERY_H_
#define RECOVERY_H_

#ifdef __cplusplus
extern "C" {
#endif

    extern int rebootForReset();
    extern int rebootForUpgrade(char* path);

#ifdef __cplusplus
}
#endif

#endif  // RECOVERY_H_
