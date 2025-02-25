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
    CFArrayRef _projectArray; /* Sorting mechanism TBD. */
};
