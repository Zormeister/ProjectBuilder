// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "PBBuildController.h"
#include "Private/PBRuntime.h"

struct _PBBuildController {
    struct __PBRuntime rt;
    
    /* our data */
    CFStringRef _buildRootPath; /* /Library/BuildRoots/ or ~/Library/BuildRoots if running in the Standalone build. */
    CFArrayRef _projectArray;
    
    /* The identifier for the build. */
    CFUUIDRef _buildRootUUID;
    CFStringRef _buildRootUUIDString;
    
    CFStringRef _sdkRootPath; /* Many potential values - How do I interface with XCRun? */
    CFStringRef _toolchainName; /* com.zormeister.dt.toolchains.darwin19 when smh */
    
    PBBCNotification _notificationHandler; /* *should* get notifications from PBProject sending in status updates */
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
