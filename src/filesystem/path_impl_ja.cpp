// Copyright (c) 2022 Josh Arenson

#include <private/ja/filesystem/path_impl_ja.hpp>
#include <private/ja/filesystem/path_impl_ja_exists.hpp>

#include <regex>
#include <utility>

using namespace ja::filesystem;

namespace {
    std::regex duplicate_separators_re(PathImpl::kPathSeparator() + "{2,}");
    std::regex trailing_separator_re(PathImpl::kPathSeparator() + "$");
}

PathImplJa::PathImplJa(std::string path)
: path_(std::move(path)) {}

std::unique_ptr<PathImpl> PathImplJa::Copy() const {
    return std::make_unique<PathImplJa>(path_);
}

std::unique_ptr<PathImpl> PathImplJa::Join(const std::string &suffix) const {
    auto result = std::make_unique<PathImplJa>(Normpath() + PathImpl::kPathSeparator() + suffix);
    result->path_ = result->Normpath();
    return result;
}

bool PathImplJa::Exists() const {
    return xplat::Exists(path_);
}

std::string PathImplJa::Normpath() const {
    if (path_.empty()) return path_;

    // Remove duplicates
    std::string result = std::regex_replace(path_, duplicate_separators_re, PathImpl::kPathSeparator());

    // Remove trailing separator
    result = std::regex_replace(result, trailing_separator_re, "");

    // TODO: If windows, replace / with \

    return result;
}
