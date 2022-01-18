// Copyright (c) 2022 Josh Arenson

#include <private/ja/filesystem/path_impl_ja.hpp>
#include <private/ja/filesystem/path_impl_ja_exists.hpp>
#include <private/ja/filesystem/path_impl_ja_getcwd.hpp>

#include <cassert>
#include <regex>
#include <utility>

using namespace ja::filesystem;

namespace {
    std::regex duplicate_separators_re(PathImpl::kPathSeparator() + "{2,}");
    std::regex trailing_separator_re(PathImpl::kPathSeparator() + "$");
}

PathImplJa::PathImplJa(std::string path)
: path_(std::move(path)) {}

std::unique_ptr<PathImpl> PathImplJa::Abspath() const {
    auto prefix = std::make_unique<PathImplJa>(xplat::GetCwd());
    return prefix->Join(path_);
}

std::unique_ptr<PathImpl> PathImplJa::Basename() const {
    // TODO: Implement when split is done
    return nullptr;
}

std::unique_ptr<PathImpl> PathImplJa::Copy() const {
    return std::make_unique<PathImplJa>(path_);
}

std::unique_ptr<PathImpl> PathImplJa::Join(const std::string &suffix) const {
    auto prefix = Normpath().empty() ? "" : Normpath() + PathImpl::kPathSeparator();

    // If a component is an absolute path, all previous components are thrown away and joining continues from the
    // absolute path component.
    if(suffix.substr(0, PathImpl::kPathSeparator().size()) == PathImpl::kPathSeparator()) {
        return std::make_unique<PathImplJa>(suffix);
    }

    auto result = std::make_unique<PathImplJa>(prefix + suffix);
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

std::string PathImplJa::ToString() const {
    return path_;
}
