// Copyright (c) 2022 Josh Arenson

#pragma once

#include <memory>
#include <string>

namespace ja { namespace filesystem {
class File {
public:
    class Impl;
    File(const std::string &path,
         const std::string &mode,
         std::unique_ptr<File::Impl> pimpl=nullptr);

private:
    std::unique_ptr<File::Impl> pimpl_;
};
}}
