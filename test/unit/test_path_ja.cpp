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
std::string Join(std::vector<std::string> path) {
    std::string result;
    std::for_each(path.cbegin(), path.cend(), [&] (const auto &s) {
        result += PathImpl::kPathSeparator() + s;
    });
    return result;
}

TEST_CASE("PathImplJa::Normpath", "[unit]") {

    SECTION("Path ending in a separator has it removed") {
        const std::string kExpected = Join({{"chorizo"}, {"taco"}});
        PathImplJa path(kExpected + PathImpl::kPathSeparator());
        REQUIRE(path.Normpath() == kExpected);
    }
}
