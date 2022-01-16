// Copyright (c) 2022 Josh Arenson

#include <ja/filesystem/path.hpp>

#include <private/ja/filesystem/path_impl_ja.hpp>

#include <utility>

using namespace ja::filesystem;

Path::Path()
: Path("") {}

Path::Path(std::string path)
: Path(std::make_unique<PathImplJa>(std::move(path))) {}

Path::Path(const Path &other)
: pimpl_(other.pimpl_->Copy()) {}

Path::Path(Path &&other) noexcept
: pimpl_(std::move(other.pimpl_)) {}

Path::~Path() = default;

bool Path::Exists() const {
    return pimpl_->Exists();
}

std::string Path::Normpath() const {
    return pimpl_->Normpath();
}

Path &Path::operator=(Path other) {
    std::swap(pimpl_, other.pimpl_);
    return *this;
}

Path Path::operator+(const Path &rhs) {
    *this += rhs;
    return Path(*this);
}

Path &Path::operator+=(const Path &rhs) {
    return *this;
}

Path::Path(std::unique_ptr<PathImpl> pimpl)
: pimpl_(std::move(pimpl)) {}

Path operator+(Path lhs, const Path &rhs) {
    return Path("");
}
