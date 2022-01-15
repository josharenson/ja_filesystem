#include <ja/filesystem/file.hpp>

#include <private/ja/filesystem/file_impl.hpp>
#include <private/ja/filesystem/file_impl_ja.hpp>

using namespace ja::filesystem;

File::File(const std::string &path,
           const std::string &mode,
           std::unique_ptr<FileImpl> pimpl)
    : pimpl_(pimpl ? std::move(pimpl) : std::make_unique<FileImplJa>(path, mode)) {}
