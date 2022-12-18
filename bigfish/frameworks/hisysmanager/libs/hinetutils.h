#ifndef HINETUTILS_H_
#define HINETUTILS_H_

#ifdef __cplusplus
extern "C" {
#endif
    extern int enableInterface(const char *interface);
    extern int disableInterface(const char *interface);
    extern int addRoute(const char *interface, const char *dst, int prefix_length, const char *gw);
    extern int setDefaultRoute(const char *interface, int gw);
    extern int removeDefaultRoute(const char *interface);
    extern int removeNetRoute(const char *interface);
    extern int removeRoute(const char *interface, const char *dst, int prefix_length, const char *gw);
#ifdef __cplusplus
}
#endif

#endif
