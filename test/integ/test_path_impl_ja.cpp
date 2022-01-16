// Test Framework
#include <catch2/catch.hpp>

// System Dependencies
#include <string>

// Project Dependencies
#include <ja/filesystem/file.hpp>

// Under Test
#include <private/ja/filesystem/path_impl_ja.hpp>

using namespace ja::filesystem;

TEST_CASE("PathImplJa::Ctor", "[integ][bootstrap]") {

    SECTION("Can compile") {
        PathImplJa p("/tmp/carne_asada.taco");
    }
}

TEST_CASE("PathImplJa::Exists", "[integ]") {

    const std::string kFilepath = "/tmp/lengua.taco";
    File f(kFilepath, "w");

    SECTION("Returns true if file exists") {
        REQUIRE(PathImplJa(kFilepath).Exists());
    }

    SECTION("Returns false if file doesn't exist") {
        REQUIRE_FALSE(PathImplJa(kFilepath + ".fake").Exists());
    }

    f.Remove();
}
