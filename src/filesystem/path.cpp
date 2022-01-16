// Copyright (c) 2022 Josh Arenson

#include <ja/filesystem/path.hpp>

#include <private/ja/filesystem/path_impl_ja.hpp>

#include <utility>

using namespace ja::filesystem;

Path::Path(std::string path)
: Path(std::make_unique<PathImplJa>(std::move(path))) {}

Path::~Path() = default;

bool Path::Exists() const {
    return pimpl_->Exists();
}

std::string Path::Normpath() const {
    return pimpl_->Normpath();
}

Path::Path(std::unique_ptr<PathImpl> pimpl)
: pimpl_(std::move(pimpl)) {}
