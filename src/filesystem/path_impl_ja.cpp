// Copyright (c) 2022 Josh Arenson

#include <private/ja/filesystem/path_impl_ja.hpp>
#include <private/ja/filesystem/path_impl_ja_exists.hpp>
#include <private/ja/filesystem/path_impl_ja_getcwd.hpp>

#include <cassert>
#include <regex>
#include <utility>

using namespace ja::filesystem;

namespace {
const std::regex &duplicate_separators_re() {
  static std::regex re(PathImpl::kPathSeparator() + "{2,}");
  return re;
}

const std::regex &trailing_separator_re() {
  static std::regex re(PathImpl::kPathSeparator() + "$");
  return re;
}

auto StartsWith = [](const std::string &str, const std::string &start){
  if (str.length() >= start.length()) {
    return (0 == str.compare(0, start.length(), start));
  } else {
    return false;
  }
};

auto EndsWith = [](const std::string &str, const std::string &ending) {
  if (str.length() >= ending.length()) {
    return (0 == str.compare(str.length() - ending.length(), ending.length(),
                             ending));
  } else {
    return false;
  }
};
}

PathImplJa::PathImplJa(std::string path) : path_(std::move(path)) {}

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
  auto prefix =
      Normpath().empty() ? "" : Normpath() + PathImpl::kPathSeparator();

  // If a component is an absolute path, all previous components are thrown away
  // and joining continues from the absolute path component.
  if (suffix.substr(0, PathImpl::kPathSeparator().size()) ==
      PathImpl::kPathSeparator()) {
    return std::make_unique<PathImplJa>(suffix);
  }

  auto result = std::make_unique<PathImplJa>(prefix + suffix);
  result->path_ = result->Normpath();
  return result;
}

bool PathImplJa::Exists() const { return xplat::Exists(path_); }

std::string PathImplJa::Normpath() const {
  if (path_.empty()) return path_;

  // Remove duplicates
  std::string result = std::regex_replace(path_, duplicate_separators_re(),
                                          PathImpl::kPathSeparator());

  // Remove trailing separator
  result = std::regex_replace(result, trailing_separator_re(), "");

  // TODO: If windows, replace / with \

  return result;
}

std::pair<std::string, std::string> PathImplJa::Split() const {
  std::string head;
  std::string tail;

  auto path = Normpath();
  auto leadingSlash = StartsWith(path, PathImpl::kPathSeparator())
                          ? PathImpl::kPathSeparator().length()
                          : 0;
  head = path.substr(0, path.rfind(kPathSeparator()) + leadingSlash);
  tail = path.substr(head.size());

  // Remove trailing slash from head
  if (head.length() > 1 && EndsWith(head, PathImpl::kPathSeparator())) head.pop_back();

  // Remove leading slash from tali
  if (StartsWith(tail, PathImpl::kPathSeparator())) tail.erase(0, 1);

  return std::make_pair(head, tail);
}

std::string PathImplJa::ToString() const { return path_; }

