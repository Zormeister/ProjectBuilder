//
//  PBPlatform.h
//  ProjectBuilder
//
//  Created by Samuel Zormeister on 24/1/2026.
//

#ifndef __PROJECTBUILDER_PBPLATFORM__
#define __PROJECTBUILDER_PBPLATFORM__

#include <ProjectBuilder/PBBase.h>

CF_EXTERN_C_BEGIN

PB_DECLARE_CLASS(PBPlatform);

PBPlatformRef PBPlatformCreateWithDictionary(CFAllocatorRef allocator, CFDictionaryRef dictionary);

CFArrayRef PBPlatformGetSupportedArchs(PBPlatformRef platform);


//
// keys
//
const CFStringRef kPBPlatformNameKey;
const CFStringRef kPBPlatformLLVMTargetOSKey;
const CFStringRef kPBPlatformLLVMTargetEnvironmentKey;
const CFStringRef kPBPlatformSDKRootKey;

CF_EXTERN_C_END

#endif /* __PROJECTBUILDER_PBPLATFORM__ */
