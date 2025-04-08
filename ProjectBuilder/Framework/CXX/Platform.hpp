// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PLATFORM_HPP
#define PROJECTBUILDER_PLATFORM_HPP

#include "Base.hpp"
#include <vector>

#if __APPLE__
#include <PBSupport/PBSupport.h>
#else
#include "CXXSupport/PropertyList.hpp"
#endif

#include <uuid/uuid.h>

#include "SDK.hpp"

/*
 * UNDER CONSTRUCTION!!!
 */

PB_BEGIN_NS

using namespace PBSupport;

class Platform {
    public:
    static std::vector<Platform> GetAvailablePlatforms();

    Platform(PropertyList::File PlatformPlist);
    Platform(const std::filesystem::path &PlatformPath, const std::string &Name);

    /*!
      @function GetSDKs
      @return Get the SDKs that are within this platform.
     */
    const std::vector<SDK> &GetSDKs();

    /*!
      @function GetName
      @return Xcode platform, so names like iOS, MacOSX, (maybe even Darwin, though Xcode seems to have a stroke if I dare try to use it)
     */
    const std::string &GetName();

    /*!
      @function GetIdentifier
      @return Xcode platform identifier, eg: com.apple.platform.macosx
     */
    const std::string &GetIdentifier();

    /*!
      @function GetVersion
      @return Returns the CFBundleVersion key of the SDK Info.plist
     */
    const std::string &GetVersion();

    /*!
      @function GetMinSDKVersion
      @return Returns the Minimum SDK Version specified in the Info.plist
     */
    const std::string &GetMinSDKVersion();

    private:
    std::vector<SDK> m_availableSDKs;
    PropertyList::File m_platformInfoFile;
    std::string m_name;
    std::string m_minSDKVersion;
    std::string m_platformIdentifier;
    std::string m_version;
};

PB_END_NS

#endif