// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PBEXTERNALREPO_H
#define PROJECTBUILDER_PBEXTERNALREPO_H

#include <PBProject.h>

/*
 * External Repository:
 * - A representation of the ExternalRepository settings.
 */

typedef struct _PBExternalRepository *PBExternalRepositoryRef;

PBExternalRepositoryRef PBExternalRepositoryCreateWithURL(CFURLRef url, CFStringRef tag, CFStringRef commitsha, CFStringRef dest);

bool PBExternalRepositorySyncRepository(PBExternalRepositoryRef externalRepo);

#endif /* PROJECTBUILDER_PBEXTERNALREPO_H */
