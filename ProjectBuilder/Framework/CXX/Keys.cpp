// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <string>

/* is this how i make constant C++ strings */

const std::string kPBDiskImageDiskLayoutKey = "Layout";
const std::string kPBDiskImageDiskSizeKey = "Size";
const std::string kPBDiskImageDiskTypeKey = "Type";

const std::string kPBDiskImageVolumeNameKey = "VolumeName";


#if TARGET_OS_MAC
/* reasoning: there's no r/w OSS APFS driver (yet) */
const std::string kPBDiskImageDefaultFileSystem = "Journaled HFS+";
#elif TARGET_OS_LINUX
/* ext4 seems appropriate given it's the default filesystem for a lot of distros */
const std::string kPBDiskImageDefaultFileSystem = "ext4";
#endif