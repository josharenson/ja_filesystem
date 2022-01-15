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

    int32_t Remove() const;

    ~File();

protected:
    File(std::unique_ptr<FileImpl> pimpl);

private:
    std::unique_ptr<FileImpl> pimpl_;
};
}}
