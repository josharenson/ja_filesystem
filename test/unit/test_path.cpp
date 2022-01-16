// Copyright (c) 2022 Josh Arenson

// Test framework dependencies
#include <catch2/catch.hpp>
#include <catch/fakeit.hpp>

// Under test
#include <ja/filesystem/path.hpp>
#include <private/ja/filesystem/path_impl.hpp>

namespace ja { namespace filesystem {
class TestPath : public Path {
public:
    TestPath(std::unique_ptr<PathImpl> pimpl)
    : Path(std::move(pimpl)) {}
};
}}

using namespace ja::filesystem;

TEST_CASE("Path API", "[unit]") {

    fakeit::Mock<PathImpl> mockPath;
    fakeit::Fake(Dtor(mockPath));
    fakeit::Fake(Method(mockPath, Exists));
    fakeit::Fake(Method(mockPath, Normpath));

    std::unique_ptr<PathImpl> mockPathPtr(&mockPath.get());

    SECTION("Exists calls pimpl") {
        TestPath path(std::move(mockPathPtr));
        path.Exists();
        fakeit::Verify(Method(mockPath, Exists));
    }

    SECTION("Normpath calls pimpl") {
        TestPath path(std::move(mockPathPtr));
        path.Normpath();
        fakeit::Verify(Method(mockPath, Normpath));
    }
}
