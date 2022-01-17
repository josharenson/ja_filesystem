// Copyright (c) 2022 Josh Arenson

#pragma once

#include <string>

#if defined(HAS_UNISTD_H)

#include <cstdlib>
#include <unistd.h>

namespace ja { namespace filesystem { namespace xplat {
inline std::string GetCwd() {
    auto *cwd = get_current_dir_name();
    std::string result(cwd);
    free(cwd);
    return result;
}
}}}

#else
#error "Only POSIX platform supported for now."
#endif
