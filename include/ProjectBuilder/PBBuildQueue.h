//
//  PBBuildQueue.h
//  ProjectBuilder
//
//  Created by Samuel Zormeister on 24/1/2026.
//

#ifndef __PROJECTBUILDER_PBBUILDQUEUE__
#define __PROJECTBUILDER_PBBUILDQUEUE__

#include <CoreFoundation/CFArray.h>
#include <ProjectBuilder/PBBase.h>
#include <ProjectBuilder/PBProject.h>
#include <ProjectBuilder/PBPlatform.h>

PB_DECLARE_CLASS(PBBuildQueue);

//
// TODO: libdispatch
//

PBBuildQueueRef PBBuildQueueCreateWithProjects(CFArrayRef projects);

#endif /* __PROJECTBUILDER_PBBUILDQUEUE__ */
