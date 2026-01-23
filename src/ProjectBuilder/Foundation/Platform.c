//
//  Platform.c
//  ProjectBuilder
//
//  Created by Samuel Zormeister on 24/1/2026.
//

#include <CoreFoundation/CFRuntime.h>
#include <ProjectBuilder/PBPlatform.h>

struct __PBPlatform {
    struct __CFRuntimeBase cfBase;
    
    CFStringRef name;
    CFStringRef llvmOsTarget;
    CFStringRef llvmOsEnv;
    CFArrayRef archs;
};
