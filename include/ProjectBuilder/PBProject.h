//
//  PBProject.h
//  ProjectBuilder
//
//  Created by Samuel Zormeister on 24/1/2026.
//

#ifndef __PROJECTBUILDER_PBPROJECT__
#define __PROJECTBUILDER_PBPROJECT__

#include <ProjectBuilder/PBBase.h>

CF_EXTERN_C_BEGIN

PB_DECLARE_CLASS(PBProject);

PBProjectRef PBProjectCreateWithDictionary(CFAllocatorRef allocator, CFDictionaryRef dictionary);

CF_EXTERN_C_END

#endif /* __PROJECTBUILDER_PBPROJECT__ */
