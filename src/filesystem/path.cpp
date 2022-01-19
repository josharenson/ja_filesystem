// Copyright (c) 2022 Josh Arenson

#include <ja/filesystem/path.hpp>

#include <private/ja/filesystem/path_impl_ja.hpp>

#include <utility>

using namespace ja::filesystem;

Path::Path() : Path("") {}

Path::Path(std::string path)
    : Path(std::make_unique<PathImplJa>(std::move(path))) {}

Path::Path(const Path &other) : pimpl_(other.pimpl_->Copy()) {}

Path::Path(Path &&other) noexcept : pimpl_(std::move(other.pimpl_)) {}

Path::~Path() = default;

Path Path::Abspath() const { return Path(std::move(pimpl_->Abspath())); }

Path Path::Basename() const { return Path(std::move(pimpl_->Basename())); }

Path Path::Commonpath(const std::vector<std::string> &paths) const {
  return Path(std::move(pimpl_->Commonpath(paths)));
}

bool Path::Exists() const { return pimpl_->Exists(); }

Path Path::Join(const std::string &suffix) const {
  return Path(std::move(pimpl_->Join(suffix)));
}

std::string Path::Normpath() const { return pimpl_->Normpath(); }

std::pair<std::string, std::string> Path::Split() const {
  return pimpl_->Split();
}

std::string Path::ToString() const { return pimpl_->ToString(); }

Path &Path::operator=(Path other) {
  std::swap(pimpl_, other.pimpl_);
  return *this;
}

Path &Path::operator+=(const Path &rhs) {
  *this = Join(rhs.Normpath());
  return *this;
}

Path::Path(std::unique_ptr<PathImpl> pimpl) : pimpl_(std::move(pimpl)) {}

Path ja::filesystem::operator+(Path lhs, const Path &rhs) {
  lhs += rhs;
  return lhs;
}