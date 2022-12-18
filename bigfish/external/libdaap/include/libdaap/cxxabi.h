#ifndef __CXXABI_H__
#define __CXXABI_H__

extern "C" {
    void __cxa_pure_virtual();
    // 2.6 Auxiliary Runtime APIs
    // added by d47906
    void __cxa_bad_cast();
    void __cxa_bad_typeid();
}

#endif
