// Copyright (c) 2022 Josh Arenson

#include <private/ja/filesystem/path_impl.hpp>
#include <private/ja/filesystem/path_impl_separator.hpp>

using namespace ja::filesystem;

const std::string &PathImpl::kPathSeparator() {
  return xplat::kPathSeparator();
}
