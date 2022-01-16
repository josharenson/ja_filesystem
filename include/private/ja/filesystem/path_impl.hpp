// Copyright (c) 2022 Josh Arenson

#pragma once

#include <string>

namespace ja { namespace filesystem {
class PathImpl {
public:
    virtual ~PathImpl() = default;

    virtual bool Exists() const = 0;
    virtual std::string Normpath() const = 0;

    static const std::string &kPathSeparator();

private:
    std::string path_separator_;
};
}}
