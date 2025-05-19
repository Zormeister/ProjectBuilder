// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "SDK.hpp"

using namespace ProjectBuilder;
using namespace PBSupport;

SDK::SDK(PropertyList::Dictionary sdkInfo) {

}

std::vector<SDK> SDK::GetAvailableSDKs() {
    static const char *SearchPaths[] = {
        "/Applications/Xcode.app/",
    };
}
