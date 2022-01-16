// Copyright (c) 2022 Josh Arenson

#pragma once

#include <private/ja/filesystem/path_impl.hpp>

#include <string>

namespace ja { namespace filesystem {
class PathImplJa : public PathImpl {
public:
    PathImplJa(std::string path);

    ~PathImplJa() override = default;

    bool Exists() const override;
    std::string Normpath() const override;

private:
    std::string path_;
};
}}
