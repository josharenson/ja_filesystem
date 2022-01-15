#include <ja/filesystem/file.hpp>

#include <utility>

#include <private/ja/filesystem/file_impl.hpp>
#include <private/ja/filesystem/file_impl_ja.hpp>

using namespace ja::filesystem;

File::File(std::string path, std::string mode)
: File(std::make_unique<FileImplJa>(std::move(path), std::move(mode))) {}

File::~File() = default;

int32_t File::Remove() const {
    return pimpl_->Remove();
}

File::File(std::unique_ptr<FileImpl> pimpl)
: pimpl_(std::move(pimpl)) {}

