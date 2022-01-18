// Copyright (c) 2022 Josh Arenson

#pragma once

#include <climits>
#include <string>

#if defined(HAS_UNISTD_H)

#include <cstdlib>
#include <unistd.h>

namespace ja { namespace filesystem { namespace xplat {
inline std::string GetCwd() {
  char buffer[PATH_MAX + 1];
  auto *cwd = getcwd(buffer, PATH_MAX + 1);
  std::string result(cwd);
  return result;
}
}}}

#else
#error "Only POSIX platform supported for now."
#endif
