// Test Framework
#include <catch2/catch.hpp>

// System Dependencies
#include <string>

// Project Dependencies
#include <ja/filesystem/file.hpp>

// Under Test
#include <ja/filesystem/path.hpp>
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

TEST_CASE("Path::Join", "[integ]") {
    const std::string kPrefix = "taco";
    const std::string kSuffix = "suadero";
    const std::string kExpected = kPrefix + PathImpl::kPathSeparator() + kSuffix;

    SECTION("Straightforward join") {
        Path p0(kPrefix);
        auto p1 = p0.Join(kSuffix);
        REQUIRE(p1.Normpath() == kExpected);
    }

    SECTION("Leading separator only") {
        Path p0(PathImpl::kPathSeparator() + kPrefix);
        auto p1 = p0.Join(kSuffix);
        REQUIRE(p1.Normpath() == PathImpl::kPathSeparator() + kExpected);
    }

    SECTION("Leading and trailing separators prefix") {
        Path p0(PathImpl::kPathSeparator() + kPrefix + PathImpl::kPathSeparator());
        auto p1 = p0.Join(kSuffix);
        REQUIRE(p1.Normpath() == PathImpl::kPathSeparator() + kExpected);
    }

    SECTION("Prefix ending and suffix leading") {
        Path p0(kPrefix + PathImpl::kPathSeparator());
        auto p1 = p0.Join(PathImpl::kPathSeparator() + kSuffix);
        REQUIRE(p1.Normpath() == kExpected);
    }
}

TEST_CASE("Path::operator=", "[integ]") {
    SECTION("Normalized paths are the same after assignment") {
        Path p0("p0");
        Path p1("p1");

        // Precondition
        REQUIRE_FALSE(p0.Normpath() == p1.Normpath());

        // Test
        p0 = p1;

        // Post condition
        REQUIRE(p0.Normpath() == p1.Normpath());
    }
}

TEST_CASE("Path::operator+=", "[integ]") {
    
}
