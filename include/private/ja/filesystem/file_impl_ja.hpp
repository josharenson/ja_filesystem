// Copyright (c) 2022 Josh Arenson

#pragma once

#include <private/ja/filesystem/file_impl.hpp>

#include <cstdio>
#include <memory>
#include <string>

namespace ja { namespace filesystem {
class FileImplJa : public FileImpl {
public:
    FileImplJa(const std::string &path,
               const std::string &mode);

    ~FileImplJa() override;

private:
    FILE *file_;
};
}}
