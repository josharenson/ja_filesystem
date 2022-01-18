// Copyright (c) 2022 Josh Arenson

#pragma once

#include <private/ja/filesystem/file_impl.hpp>

#include <cstdio>
#include <memory>
#include <string>

namespace ja { namespace filesystem {
class FileImplJa : public FileImpl {
public:
  FileImplJa(std::string path, std::string mode);

  ~FileImplJa() override;

  int32_t Remove() const override;

private:
  std::string path_;
  std::string mode_;
  FILE *file_;
};
}}
