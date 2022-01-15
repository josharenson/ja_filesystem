#include <ja/filesystem/file.hpp>

#include <utility>

#include <private/ja/filesystem/file_impl.hpp>
#include <private/ja/filesystem/file_impl_ja.hpp>

using namespace ja::filesystem;

File::File(const std::string &path,
           const std::string &mode,
           std::unique_ptr<File::Impl> pimpl)
    :pimpl_(std::make_unique<FileImplJa>(path, mode)) {}

File::~File() = default;
