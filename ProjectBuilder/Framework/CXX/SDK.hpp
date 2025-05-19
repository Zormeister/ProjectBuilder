// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_SDK_HPP
#define PROJECTBUILDER_SDK_HPP

#include "Base.hpp"
#include <vector>

#if __APPLE__
#include <PBSupport/PBSupport.h>
#else
#include "CXXSupport/PropertyList.hpp"
#endif

#include <uuid/uuid.h>

/*
 * UNDER CONSTRUCTION!!!
 */

namespace ProjectBuilder {

using namespace PBSupport;

class SDK {
    SDK(PropertyList::Dictionary sdkInfo);
    SDK(const std::filesystem::path &SDKRoot, const std::string &PlatformName);

    /*!
      @function GetSDKRoot
      @return SDK path root path, or it'll return the SDK canonical name
     */
    const std::filesystem::path &GetSDKRoot();

    /*!
      @function GetPlatformName
      @return SDK platform, so names like iOS, MacOSX, (maybe even Darwin, though Xcode seems to have a stroke if I dare try to use it)
     */
    const std::string &GetPlatformName();

    /*!
      @function GetToolchainIdentifier
      @return This corresponds to the Xcode toolchain identifier, which is usually com.apple.dt.toolchains.XcodeDefault
     */
    const std::string &GetToolchainIdentifier();

    /*!
      @function GetCompilerIdentifier
      @abstract Should this return "com.apple.compilers.gcc.4_2" on Linux? I doubt XC would be used anywhere, but...
      @return This corresponds to the Xcode compiler identifier, which is usually com.apple.compilers.llvm.clang.1_0
     */
    const std::string &GetCompilerIdentifier();

    /*!
      @function GetMinDeploymentTarget
      @abstract Returns the minimum deployment target of the SDK
      @return Returns a string such as "10.15" or "10.11" or "12.3", etc.
     */
    const std::string &GetMinDeploymentTarget();

    /*!
      @function GetDeploymentTarget
      @abstract Returns the deployment target of the SDK
      @return Returns a string such as "10.15" or "10.11" or "12.3", etc.
     */
    const std::string &GetDeploymentTarget();

    /*!
      @function HasVariants
      @return Returns true based on if it has variant plists
     */
    bool HasVariants();

    /*!
      @class Variant
      @abstract Representation of an SDK variant entry
     */
    class Variant {
        public:
        Variant(PropertyList::Dictionary variantEntry);

        /*!
          @function GetName
          @return Returns the name of the variant, such as "macos" or "iosmac"
         */
        const std::string &GetName();
    };

    class Version {
        public:
        Version(PropertyList::Dictionary versionRoot);
        Version(const std::string &Version, const std::string &ProductName, const std::string &BuildVersion, const uuid_t &BuildUUID);
    };

    private:
    static std::vector<SDK> GetAvailableSDKs();
};

}

#endif
