// Copyright (c) 2022 Josh Arenson

#pragma once

#include <ja/filesystem/file.hpp>

namespace ja { namespace filesystem {
class File::Impl {
public:
    virtual ~Impl() = default;
};
}}
