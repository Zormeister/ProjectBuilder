// Copyright (c) 2026, Samuel Zormeister. All rights reserved. SPDX: BSD-3-Clause

#ifndef __PROJECTBUILDER_PBBASE__
#define __PROJECTBUILDER_PBBASE__

#include <CoreFoundation/CoreFoundation.h>

#if !defined(__has_include)
        #define __has_include(a) 0
#endif

#ifdef __cplusplus
#define PB_EXPORT extern "C"
#else
#define PB_EXPORT extern
#endif

#define PB_DECLARE_CLASS(class) typedef struct __##class * class##Ref

#endif /* __PROJECTBUILDER_PBBASE__ */
