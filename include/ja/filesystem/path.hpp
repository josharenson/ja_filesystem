// Copyright (c) 2022 Josh Arenson

#pragma once

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

namespace ja { namespace filesystem {
class PathImpl;
class Path {
public:
    Path();
    explicit Path(std::string path);
    Path(const Path &other);
    Path(Path &&other) noexcept;

    ~Path();

    bool Exists() const;

    Path Join(const std::string &suffix) const;

    std::string Normpath() const;

    Path &operator=(Path other);
    Path &operator+=(const Path &rhs);

protected:
    Path(std::unique_ptr<PathImpl> pimpl);

private:
    std::unique_ptr<PathImpl> pimpl_;
};

Path operator+(Path lhs, const Path &rhs);

}}
