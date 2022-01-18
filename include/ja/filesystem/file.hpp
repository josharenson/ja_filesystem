// Copyright (c) 2022 Josh Arenson

#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace ja { namespace filesystem {
class FileImpl;
class File {
public:
  File(std::string path, std::string mode);

  ~File();

  int32_t Remove() const;

protected:
  explicit File(std::unique_ptr<FileImpl> pimpl);

private:
  std::unique_ptr<FileImpl> pimpl_;
};
}}
