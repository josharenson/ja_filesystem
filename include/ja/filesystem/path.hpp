// Copyright (c) 2022 Josh Arenson

#pragma once

#include <memory>
#include <string>

namespace ja { namespace filesystem {
class PathImpl;
class Path {
public:
    explicit Path(std::string path);

    ~Path();

    bool Exists() const;
    std::string Normpath() const;

protected:
    Path(std::unique_ptr<PathImpl> pimpl);

private:
    std::unique_ptr<PathImpl> pimpl_;
};
}}
