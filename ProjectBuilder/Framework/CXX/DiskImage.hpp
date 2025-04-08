// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_DISKIMAGE_HPP
#define PROJECTBUILDER_DISKIMAGE_HPP

#include "Base.hpp"

#if __APPLE__
#include <PBSupport/PBSupport.h>
#else
#include "CXXSupport/PropertyList.hpp"
#endif

PB_BEGIN_NS

using namespace PBSupport;

class DiskImage {
    public:
    DiskImage(PropertyList::Dictionary imageInfo);

    /* Disk Image services */
    bool MountImage();
    bool UnmountImage();

    private:
    bool CreateImage();

    std::string m_volumeName;
    std::string m_imageFileSystem;
    std::string m_diskLayout;
    std::string m_diskType; // Linux will always use an IMG. Sorry but this project was always meant for macOS.
    std::filesystem::path m_diskImagePath;
};

PB_END_NS

#endif
