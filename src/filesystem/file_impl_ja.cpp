#include <private/ja/filesystem/file_impl_ja.hpp>

#include <cstdio>

using namespace ja::filesystem;

FileImplJa::FileImplJa(std::string path,
                       std::string mode)
: path_(std::move(path))
, mode_(std::move(mode))
, file_(fopen(path.c_str(), mode.c_str())) {}

FileImplJa::~FileImplJa() {
    fclose(file_);
}

int32_t FileImplJa::Remove() const {
    return remove(path_.c_str());
}
