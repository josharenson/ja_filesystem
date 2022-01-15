#include <catch2/catch.hpp>

#include <ja/filesystem/file.hpp>

TEST_CASE("File::File", "[unit]") {

    SECTION("Write") {
        ja::filesystem::File f("/tmp/joshuaa", "w");
    }
}
