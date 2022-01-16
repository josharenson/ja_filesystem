// Copyright (c) 2022 Josh Arenson

#pragma once

#include <string>

namespace ja { namespace filesystem { namespace xplat {
#if defined(WIN32) || defined(_WIN32)
const std::string &kPathSeparator() {
    static std::string s = "\\";
    return s;
}
#else
const std::string &kPathSeparator() {
    static std::string s = "/";
    return s;
}
#endif

}}}
