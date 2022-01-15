// Copyright (c) 2022 Josh Arenson

#pragma once

#include <cstdint>

namespace ja { namespace filesystem {
class FileImpl {
public:
    virtual ~FileImpl() = default;

    virtual int32_t Remove() const = 0;
};
}}
