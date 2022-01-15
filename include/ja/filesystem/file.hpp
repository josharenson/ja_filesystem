// Copyright (c) 2022 Josh Arenson

#pragma once

#include <memory>
#include <string>

namespace ja { namespace filesystem {
class FileImpl;
class File {
public:
    File(const std::string &path,
         const std::string &mode,
         std::unique_ptr<FileImpl> pimpl=nullptr);

private:
    std::unique_ptr<FileImpl> pimpl_;
};
}}
