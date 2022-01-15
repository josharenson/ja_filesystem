#include <catch2/catch.hpp>

#include <private/ja/filesystem/file_impl_ja.hpp>

using namespace ja::filesystem;

TEST_CASE("FileImplJa::Ctor", "[integ]") {
    SECTION("Ctor creates file") {
        FileImplJa f("/tmp/carne_asada.taco", "w");
        f.Remove();
    }
}
