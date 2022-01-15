#include <private/ja/filesystem/file_impl_ja.hpp>

using namespace ja::filesystem;

FileImplJa::FileImplJa(const std::string &path,
                           const std::string &mode)
    : file_(fopen(path.c_str(), mode.c_str())) {}

FileImplJa::~FileImplJa() {
    fclose(file_);
}
