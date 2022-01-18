// Copyright (c) 2022 Josh Arenson

#pragma once

#include <private/ja/filesystem/path_impl.hpp>

#include <string>

namespace ja { namespace filesystem {
class PathImplJa : public PathImpl {
public:
  explicit PathImplJa(std::string path);

  ~PathImplJa() override = default;

  std::unique_ptr<PathImpl> Abspath() const override;
  std::unique_ptr<PathImpl> Basename() const override;
  std::unique_ptr<PathImpl> Copy() const override;
  bool Exists() const override;
  std::unique_ptr<PathImpl> Join(const std::string &suffix) const override;
  std::string Normpath() const override;
  std::pair<std::string, std::string> Split() const override;
  std::string ToString() const override;

private:
  std::string path_;
};
}}
