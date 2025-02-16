// Copyright (C) 2024-2025 Zormeister, All rights reserved. Licensed under the BSD-3 Clause License.

#include <ProjectBuilder/PBProject.h>
#include <ProjectBuilder/PBRuntime.h>
#include <ProjectBuilder/PBExternalRepository.h>

struct _PBProject {
    // runtime 
    struct __PBRuntime rt;
    
    CFStringRef _name;
    CFArrayRef _dependencies;
    PBExternalRepositoryRef _externalRepo;
};


bool PBProjectIsExternalRepo(PBProjectRef project) { return project->_externalRepo != NULL; }
