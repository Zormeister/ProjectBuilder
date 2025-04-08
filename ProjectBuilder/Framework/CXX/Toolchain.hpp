// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_SDK_HPP
#define PROJECTBUILDER_SDK_HPP

#include "Base.hpp"

#if __APPLE__
#include <PBSupport/PBSupport.h>
#else
#include "CXXSupport/PropertyList.hpp"
#endif

PB_BEGIN_NS

using namespace PBSupport;

class Toolchain {
    Toolchain(PropertyList::Dictionary toolchainInfo);

    /*!
      @function GetToolchainPath
      @return Path to the active toolchain, IE: /Applications/Xcode.app/Developer/Toolchains/XcodeDefault.xctoolchain
     */
    const std::filesystem::path &GetToolchainPath();

    /*!
      @function GetLinkerName
      @return Usually ld64 under normal macOS circumstances.
     */
    const std::string &GetLinkerName();

    /*!
      @function GetCompilerName
      @return Usually clang under normal macOS circumstances.
     */
     const std::string &GetCompilerName();

    /*!
      @function GetIdentifier
      @return This corresponds to the Xcode toolchain identifier, which is usually com.apple.dt.toolchains.XcodeDefault
     */
    const std::string &GetIdentifier();

    private:
};

PB_END_NS

#endif
