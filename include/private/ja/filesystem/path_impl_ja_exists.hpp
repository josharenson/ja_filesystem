// Copyright (c) 2022 Josh Arenson

#pragma once

#include <string>

#if defined(HAS_SYS_STAT_H)

#include <sys/stat.h>

namespace ja { namespace filesystem { namespace xplat {
inline bool Exists(const std::string &path) {
    struct stat buffer;
    return(stat(path.c_str(), &buffer) == 0);
}
}}}

#else
#error "Only POSIX platform supported for now."
#endif
