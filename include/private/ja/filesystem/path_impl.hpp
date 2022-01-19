// Copyright (c) 2022 Josh Arenson

#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace ja { namespace filesystem {
class Path;
class PathImpl {
public:
  virtual ~PathImpl() = default;

  virtual std::unique_ptr<PathImpl> Abspath() const = 0;

  virtual std::unique_ptr<PathImpl> Basename() const = 0;

  virtual std::unique_ptr<PathImpl>
  Commonpath(const std::vector<std::string> &paths) const = 0;

  virtual std::unique_ptr<PathImpl> Copy() const = 0;

  virtual bool Exists() const = 0;

  virtual std::unique_ptr<PathImpl> Join(const std::string &) const = 0;

  virtual std::string Normpath() const = 0;

  virtual std::pair<std::string, std::string> Split() const = 0;

  virtual std::string ToString() const = 0;

  static const std::string &kPathSeparator();
};
}}
