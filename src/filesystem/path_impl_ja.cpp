// Copyright (c) 2022 Josh Arenson

#include <private/ja/filesystem/path_impl_ja.hpp>
#include <private/ja/filesystem/path_impl_ja_exists.hpp>

#include <regex>

using namespace ja::filesystem;

namespace {
    std::regex duplicate_separators_re(
        "\\" + PathImpl::kPathSeparator() + "{2,}");
}

PathImplJa::PathImplJa(std::string path)
: path_(std::move(path)) {}

bool PathImplJa::Exists() const {
    return xplat::Exists(path_);
}

std::string PathImplJa::Normpath() const {
    std::string result(path_);
    // Remove duplicates
    std::regex_replace(result, duplicate_separators_re, PathImpl::kPathSeparator());
    return result;
}
