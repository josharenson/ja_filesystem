// Copyright (c) 2022 Josh Arenson

#pragma once

#include <memory>
#include <string>

namespace ja { namespace filesystem {
class Path;
class PathImpl {
public:
    virtual ~PathImpl() = default;

    virtual std::unique_ptr<PathImpl> Copy() const = 0;

    virtual bool Exists() const = 0;

    virtual std::unique_ptr<PathImpl> Join(const std::string&) const = 0;
    virtual std::string Normpath() const = 0;

    static const std::string &kPathSeparator();

private:
    std::string path_separator_;
};
}}
