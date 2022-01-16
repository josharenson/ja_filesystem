// Copyright (c) 2022 Josh Arenson

#include <catch2/catch.hpp>

#include <algorithm>
#include <string>
#include <vector>

// Under test
#include <private/ja/filesystem/path_impl.hpp>
#include <private/ja/filesystem/path_impl_ja.hpp>

using namespace ja::filesystem;

// FIXME: Remove when join is implemented
std::string Join(std::vector<std::string> path, const std::string separator) {
    std::string result;
    std::for_each(path.cbegin(), path.cend(), [&] (const auto &s) {
        result += separator + s;
    });
    return result;
}

TEST_CASE("PathImplJa::Normpath", "[unit]") {

    const std::string kRoot = "lengua";
    const std::string kLeaf = "taco";
    const std::string kExpected = Join({{kRoot}, {kLeaf}}, PathImpl::kPathSeparator());

    SECTION("Empty path returns empty path") {
        PathImplJa path("");
        REQUIRE(path.Normpath().empty());
    }

    SECTION("Path 2 consecutive separators") {
        auto test_val = Join({{kRoot}, {kLeaf}}, PathImpl::kPathSeparator() + PathImpl::kPathSeparator());
        PathImplJa path(test_val);
        REQUIRE(path.Normpath() == kExpected);
    }

    SECTION("Path 3 consecutive separators") {
        auto test_val = Join({{kRoot}, {kLeaf}}, PathImpl::kPathSeparator() + PathImpl::kPathSeparator()) + PathImpl::kPathSeparator();
        PathImplJa path(test_val);
        REQUIRE(path.Normpath() == kExpected);
    }

    SECTION("Path ending in separator has it removed") {
        const std::string kExpected_ = "taco";
        PathImplJa path("taco" + PathImpl::kPathSeparator());
        REQUIRE(path.Normpath() == kExpected_);
    }
}
