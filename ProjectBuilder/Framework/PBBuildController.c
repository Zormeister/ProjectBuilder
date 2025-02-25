//
//  PBBuildController.c
//  ProjectBuilder
//
//  Created by Zormeister on 24/2/2025.
//

#include "PBBuildController.h"
#include "Private/PBRuntime.h"

struct _PBBuildController {
    struct __PBRuntime rt;
    
    /* our data */
    CFURLRef _buildRootURL; /* /Library/BuildRoots/ or ~/Library/BuildRoots if running in the Standalone build. */
    CFArrayRef _projectArray;
};

/*
 * Actually, here's food for thought:
 *
 * What if I just do the same as old PB and just run the dependencies as I need them done?
 * EG: Project `xnu` needs project `libfirehose_kernel`, `libfirehose_kernel` wants `libpthread_headers`,
 * This will eventually spiral to project `sdk_init` in the run of `Libc_headers`.
 * Weird, but if I run the check at pre-flight then maybe I can avoid a shitshow where we're caught in a dependency loop.
 * Readup on the legacy source code (currently in the main/master branch) for more details
 */
